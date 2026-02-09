#ifndef BLOG_H
#define BLOG_H

#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <thread>
#include <queue>
#include <mutex>
#include <memory>

#include "Btype.h"
#include "Btime.h"
#include "Bsin.h"
#include "Bdiv.h"
#include "Bstrto.h"

namespace bh {

// 不同等级日志
namespace bhenum {
    enum class level
    {
        e_all,
        e_deb,
        e_inf,
        e_war,
        e_err,
        e_fat,
    };
} // namespace bhenum

//
//
//
//

// 日志缓冲区
struct Blog_buf
{
    template <typename T>
    inline void push(const T &val)
    {
        _str += Bstrto::to_str(val);
    }

    inline void clear() { _str.clear(); }

    inline dstr value() const { return _str; }

    dstr _str; // 缓存内容
};

// 日志结束类标记
struct Blog_end
{
};

// 日志基本类-用于创建各种输出类型的模板-不提供打印只提供写入与缓存
template <typename Tbuf, typename Tend, typename Tout>
struct Blog_base
{
    using level = bhenum::level;

    // 设置日志等级-不显示低等级内容
    inline void set_level(const level &el) { _el = el; }

    // internal
    // 传入等级
    inline Blog_base &operator<<(const level &el)
    {
        if(el >= _el) {
            _pass = true;
        }
        else {
            _pass = false;
        }
        return *this;
    }

    // 打印内容
    inline Blog_base &operator<<(Tend)
    {
        if(_pass) {
            _out.out(_buf);
            _buf.clear();
            _pass = false;
        }
        return *this;
    }

    // 传入内容
    template <typename T>
    inline Blog_base &operator<<(const T &log)
    {
        if(_pass) {
            _buf.push(log);
        }
        return *this;
    }

    bool _pass = false;       // 日志等级是否通过
    level _el = level::e_all; // 日志等级划分枚举
    Tbuf _buf;                // 日志写入缓存内容
    Tout _out;                // 日志输出类
};

//
//
//
//

// 空打印-用于测试 << 操作的耗时
struct Blog_out_null
{
    void out(const Blog_buf &buf) {}
};

// 命令行打印
struct Blog_out_cmd
{
    void out(const Blog_buf &buf) { std::cout << buf.value() << "\n"; }
};

// 文件打印
struct Blog_out_file
{
    using pair_name = std::pair<dstr, dstr>;

    ~Blog_out_file()
    {
        if(_fs.is_open()) {
            _fs.flush();
        }
    }

    void out(const Blog_buf &buf)
    {
        if(_fs.is_open() == false) {
            _fs.open(_file, _mode);
        }
        if(_fs.is_open()) {
            _fs << buf.value() << "\n";
            update_file();
        }
    }

    // 初始化日志
    inline void reopen(cstr file, bool app = true)
    {
        _pname = get_pname(file);
        _file = file;
        _limit_now = 1;

        if(app) {
            _mode = std::ios::app;
        }
        else {
            _mode = std::ios::out;
        }

        if(_fs.is_open()) {
            _fs.close();
        }
    }

    // 设置循环最大文件数-默认无限
    inline void set_limit(uint64 max) { _limit_max = max; }

    // 设置单个文件最大长度-默认64M
    inline void set_length(uint64 len) { _len_max = len; }

    // 判断文件是否存在
    static bool exist_file(cstr filename)
    {
        std::ifstream f(filename);
        return f.is_open();
    }

    // internal
    // 超出最大文件限制后更新文件名
    bool update_file()
    {
        if(_len_max < (uint64)_fs.tellg()) {
            if(_limit_max == 0) {
                return write_unlimited();
            }
            else {
                return write_limit();
            }
        }
        return true;
    }

    // 无限制日志
    bool write_unlimited()
    {
        _fs.close();
        for(int32 i = _limit_now;; i++) {
            dstr file = newfile(i);
            if(exist_file(file) == false) {
                rename(_file.c_str(), file.c_str());
                _limit_now++;
                break;
            }
        }
        _fs.open(_file, _mode);
        return _fs.is_open();
    }

    // 限制日志数量
    bool write_limit()
    {
        _fs.close();
        rename(_file.c_str(), newfile(_limit_now).c_str());
        _limit_now++;
        if(_limit_now > _limit_max) {
            _limit_now = 1;
        }

        _fs.open(_file, _mode);
        return _fs.is_open();
    }

    // 得到文件与后缀信息
    pair_name get_pname(cstr file)
    {
        dstr name = Bdiv(file)(".", 0, 0);
        dstr suffix = Bdiv(file)(".", 1, 1);
        return std::make_pair(name, suffix);
    }

    // 根据数量生成文件名
    dstr newfile(uint64 num)
    {
        dstr file;
        file += _pname.first;
        file += "_" + std::to_string(num) + ".";
        file += _pname.second;
        return file;
    }

    uint64 _limit_max = 0;         // 日志文件限制数量
    uint64 _limit_now = 1;         // 当前写入日志
    uint64 _len_max = (1 << 26);   // 最大长度--64M
    pair_name _pname;              // 文件名与后缀
    dstr _file;             // 文件名
    std::fstream _fs;              // 文件对象
    std::ios_base::openmode _mode; // 文件打开模式
};

// 异步文件日志
template <typename Tbuf, uint64 Ttime = 1000>
struct Blog_out_asyn : public Blog_out_file
{
    Blog_out_asyn() {}

    ~Blog_out_asyn() { exit_th(); }

    void out(const Blog_buf &buf) { push_queue(buf); }

    // 重启写入线程
    void reset()
    {
        if(_run == false) {
            _run = true;
            _th = std::make_shared<std::thread>(&Blog_out_asyn::work_write, this);
        }
    }

    // 退出写入线程
    void exit_th()
    {
        if(_run) {
            _run = false;
            _th->join();
            Blog_out_file::_fs.flush();
        }
    }

    // internal
    // 将队列内日志写入日志输出类
    void work_write()
    {
        while(_run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(Ttime));
            std::unique_lock<std::mutex> lock(_mut);
            while(_que.empty() == false) {
                Blog_out_file::out(_que.front());
                _que.pop();
            }
        }
    }

    // 加入到队列
    inline void push_queue(const Tbuf &txt)
    {
        if(_run == false) {
            reset();
        }
        std::unique_lock<std::mutex> lock(_mut);
        _que.push(txt);
    }

    bool _run = false;                // 写入线程运行标记
    std::mutex _mut;                  // 队列锁
    std::queue<Tbuf> _que;            // 写入日志队列
    std::shared_ptr<std::thread> _th; // 写入线程
};

// 空打印日志
struct Blog_null : public Blog_base<Blog_buf, Blog_end, Blog_out_null>
{
    Blog_null() { set_level(bhenum::level::e_all); }
};

// 命令行打印日志
struct Blog_cmd : public Blog_base<Blog_buf, Blog_end, Blog_out_cmd>
{
    Blog_cmd() { set_level(bhenum::level::e_all); }
};

// 文件打印日志
struct Blog_file : public Blog_base<Blog_buf, Blog_end, Blog_out_file>
{
    Blog_file(cstr file = "Bflog.log")
    {
        set_level(bhenum::level::e_all);
        _out.reopen(file);
    }
};

// 文件打印日志-异步
struct Blog_afile : public Blog_base<Blog_buf, Blog_end, Blog_out_asyn<Blog_buf, 500>>
{
    Blog_afile(cstr file = "Baflog.log")
    {
        set_level(bhenum::level::e_all);
        _out.reopen(file);
    }
};

//
//
//
//

// 打印固定格式的时间
struct Blog_time
{
    inline static dstr print()
    {
        Btimes::data d = Btimes::to_data(Btimes::time_now());
        d.hou += 8;
        return Btimes::format_time(d, "YYYY-MM-DD.HH:TT:SS.LLL");
    };
};

// 标准容器打印
struct Blog_con
{
    template <typename T>
    inline static dstr print(const T &con, uint64 len = 1, cstr flg = " ",
                                    cstr prev = "| ")
    {
        dstr ret = "\n";
        ret += prev + "size: " + std::to_string(con.size());
        ret += "\n" + prev;
        uint64 count = 0;
        for(const auto &a : con) {
            if(len != 0 && count >= len) {
                count = 0;
                ret += "\n" + prev;
            }
            ret += Bstrto::to_str(a) + flg;
            count++;
        }
        ret += "\n";
        return ret;
    }
};

//
//
//
//

// 日志格式化内容
#define BHLOG_FORMAT(tips, el, ...)                                                                \
    el << tips "[" << __FILE__ << ":<" << __LINE__ << ">] <<<< " << __VA_ARGS__

// 格式化VSCode快捷导航格式
#define BHLOG_FORMAT_VSC(tips, el, ...)                                                            \
    el << tips "<<<< " << __VA_ARGS__ << " >>>>[" << __FILE__ << ":" << __LINE__                   \
       << "][" + bh::Blog_time::print() + "] "

// 生成打印字符串
#define BHLOG_PRINT(out, tips, end, BHDF_FM, el, ...) out << BHDF_FM(tips, el, __VA_ARGS__) << end

// 显示打印
#define BHLOG_MAKE(out, lab, end, el, ...)                                                         \
    BHLOG_PRINT(out, lab, end, BHLOG_FORMAT_VSC, bh::bhenum::level::el, __VA_ARGS__)

// 生成快捷打印宏-带颜色
#define BHLOG_MAKE_COLA(out, end, ...)                                                             \
    BHLOG_MAKE(out, "\033[30m[All]", "\033[0m" << end, e_all, __VA_ARGS__)
#define BHLOG_MAKE_COLD(out, end, ...)                                                             \
    BHLOG_MAKE(out, "\033[32m[Deb]", "\033[0m" << end, e_deb, __VA_ARGS__)
#define BHLOG_MAKE_COLI(out, end, ...)                                                             \
    BHLOG_MAKE(out, "\033[36m[Inf]", "\033[0m" << end, e_inf, __VA_ARGS__)
#define BHLOG_MAKE_COLW(out, end, ...)                                                             \
    BHLOG_MAKE(out, "\033[33m[War]", "\033[0m" << end, e_war, __VA_ARGS__)
#define BHLOG_MAKE_COLE(out, end, ...)                                                             \
    BHLOG_MAKE(out, "\033[31m[Err]", "\033[0m" << end, e_err, __VA_ARGS__)
#define BHLOG_MAKE_COLF(out, end, ...)                                                             \
    BHLOG_MAKE(out, "\033[35m[Fat]", "\033[0m" << end, e_fat, __VA_ARGS__)

// 生成快捷打印宏
#define BHLOG_MAKEA(out, end, ...) BHLOG_MAKE(out, "[All]", end, e_all, __VA_ARGS__)
#define BHLOG_MAKED(out, end, ...) BHLOG_MAKE(out, "[Deb]", end, e_deb, __VA_ARGS__)
#define BHLOG_MAKEI(out, end, ...) BHLOG_MAKE(out, "[Inf]", end, e_inf, __VA_ARGS__)
#define BHLOG_MAKEW(out, end, ...) BHLOG_MAKE(out, "[War]", end, e_war, __VA_ARGS__)
#define BHLOG_MAKEE(out, end, ...) BHLOG_MAKE(out, "[Err]", end, e_err, __VA_ARGS__)
#define BHLOG_MAKEF(out, end, ...) BHLOG_MAKE(out, "[Fat]", end, e_fat, __VA_ARGS__)

#ifndef BHLOG_CLOSE_LOG

// 设置默认打印宏
#define BHLOG_CONF_DEF(type) bh::Bsin_log_conf::get()->type

// 快捷命令行打印
#ifndef BHLOG_CLOSE_COL
#define vloga(...) BHLOG_MAKE_COLA(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vlogd(...) BHLOG_MAKE_COLD(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vlogi(...) BHLOG_MAKE_COLI(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vlogw(...) BHLOG_MAKE_COLW(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vloge(...) BHLOG_MAKE_COLE(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vlogf(...) BHLOG_MAKE_COLF(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#else
#define vlogd(...) BHLOG_MAKED(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vlogi(...) BHLOG_MAKEI(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vlogw(...) BHLOG_MAKEW(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define vloge(...) BHLOG_MAKEE(BHLOG_CONF_DEF(_cmd), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#endif

// 快捷文件打印
#define floga(...) BHLOG_MAKEA(BHLOG_CONF_DEF(_file), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define flogd(...) BHLOG_MAKED(BHLOG_CONF_DEF(_file), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define flogi(...) BHLOG_MAKEI(BHLOG_CONF_DEF(_file), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define flogw(...) BHLOG_MAKEW(BHLOG_CONF_DEF(_file), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define floge(...) BHLOG_MAKEE(BHLOG_CONF_DEF(_file), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define flogf(...) BHLOG_MAKEF(BHLOG_CONF_DEF(_file), BHLOG_CONF_DEF(_end), __VA_ARGS__)

// 快捷文件打印
#define alogd(...) BHLOG_MAKED(BHLOG_CONF_DEF(_afile), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define alogi(...) BHLOG_MAKEI(BHLOG_CONF_DEF(_afile), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define alogw(...) BHLOG_MAKEW(BHLOG_CONF_DEF(_afile), BHLOG_CONF_DEF(_end), __VA_ARGS__)
#define aloge(...) BHLOG_MAKEE(BHLOG_CONF_DEF(_afile), BHLOG_CONF_DEF(_end), __VA_ARGS__)

// 快捷空值打印
#define nlogd(...) BHLOG_MAKED(BHLOG_CONF_DEF(_null), BHLOG_CONF_DEF(_end), __VA_ARGS__)

#else
#define vloga(...)
#define vlogd(...)
#define vlogi(...)
#define vlogw(...)
#define vloge(...)
#define vlogf(...)

#define flogd(...)
#define flogi(...)
#define flogw(...)
#define floge(...)

#define alogd(...)
#define alogi(...)
#define alogw(...)
#define aloge(...)

#define nlogd(...)
#endif

// 默认打印宏
struct Bsin_log_conf
{
    Blog_end _end;
    Blog_cmd _cmd;
    Blog_null _null;
    Blog_file _file;
    Blog_afile _afile;

    // 简化日志类函数调用
    template <typename T>
    void reopen(T &ptr, cstr file, bool app = true)
    {
        ptr._out.reopen(file, app);
    }

    template <typename T>
    void set_level(T &ptr, const bhenum::level &el)
    {
        ptr.set_level(el);
    }

    template <typename T>
    void set_length(T &ptr, uint64 len)
    {
        ptr._out.set_length(len);
    }

    template <typename T>
    void set_limit(T &ptr, uint64 max)
    {
        ptr._out.set_limit(max);
    }

    void exit_flush_afile() { _afile._out.exit_th(); }

    static Bsin_log_conf *get() { return Bsind<Bsin_log_conf>::get(); }
};

// 快捷打印操作
#define $(value) "[" #value ": " << value << "] "
#define $C(value) "[" #value ": " << bh::Blog_con::print(value) << "] "
#define $S(value) "[" #value ": " << bh::Bstr::from_stringstream(value) << "] "

} // namespace bh

#endif // BLOG_H