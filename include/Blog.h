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
#include "Bto.h"

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

    enum class end
    {
        e_line,
        e_flush,
        e_blank,
        e_skip,
    };
} // namespace bhenum

//
//
//
//

// 日志基本类-用于创建各种输出类型的模板-不提供打印只提供写入与缓存
template <typename Tbuf, typename Tout>
class Blog_base
{
public:
    using level = bhenum::level;
    using end = bhenum::end;

    // 设置日志等级-不显示低等级内容
    inline void set_level(level el) { _el = el; }

    // 传入等级
    inline Blog_base &operator<<(level el)
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
    inline Blog_base &operator<<(end e)
    {
        if(_pass) {
            if(e == end::e_line) {
                _buf.push("\n");
                _out.out(_buf.value());
            }
            else if(e == end::e_flush) {
                _buf.push("\n");
                _out.out(_buf.value());
                _out.flush();
            }
            else if(e == end::e_blank) {
                _buf.push(" ");
                _out.out(_buf.value());
            }
            else if(e == end::e_skip) {
                _out.out(_buf.value());
            }
            _buf.clear();
            _pass = false;
        }
        return *this;
    }

    // 传入内容
    template <typename T>
    inline Blog_base &operator<<(T &&val)
    {
        if(_pass) {
            _buf.push(std::forward<T>(val));
        }
        return *this;
    }

protected:
    bool _pass = false;       // 日志等级是否通过
    level _el = level::e_all; // 日志等级划分枚举
    Tbuf _buf;                // 日志写入缓存内容
    Tout _out;                // 日志输出类
};

//
//
//
//

// 日志缓冲区-可自定义
template <typename Tto = Bto>
class Blog_buf
{
public:
    Blog_buf() { _str.reserve(_BH_INT_1024_); }

    template <typename T>
    inline void push(T &&val)
    {
        _str += Tto::to_str(std::forward<T>(val));
    }

    inline void clear() { _str.clear(); }

    inline cstr value() const { return _str; }

protected:
    dstr _str; // 缓存内容
};

//
//
//
//

// 空打印-用于测试 << 操作的耗时
class Blog_out_null
{
public:
    inline void out(cstr buf) {}

    inline void flush() {}
};

// 命令行打印
class Blog_out_cmd
{
public:
    inline void out(cstr buf) { std::cout << buf; }

    inline void flush() { std::flush(std::cout); }
};

// 文件打印
class Blog_out_file
{
public:
    using pair_name = std::pair<dstr, dstr>;

    ~Blog_out_file() { flush(); }

    inline void out(cstr buf)
    {
        if(_fs.is_open()) {
            _fs << buf;
            update_file();
        }
        else {
            _fs.open(_file, _mode);
            if(_fs.is_open()) {
                _fs << buf;
                update_file();
            }
        }
    }

    inline void flush()
    {
        if(_fs.is_open()) {
            _fs.flush();
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

protected:
    // 判断文件是否存在
    static bool exist_file(cstr filename)
    {
        std::ifstream f(filename);
        return f.is_open();
    }

    // 超出最大文件限制后更新文件名
    bool update_file()
    {
        if(_len_max < _fs.tellg()) {
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
        for(int32 i = _limit_now; i < _BH_INT_4096_; i++) {
            dstr file = newfile(i);
            if(!exist_file(file)) {
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
        dstr name = Bdiv(file)(".", 0, 0).to_str();
        dstr suffix = Bdiv(file)(".", 1, 1).to_str();
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

protected:
    uint64 _limit_max = 0;         // 日志文件限制数量
    uint64 _limit_now = 1;         // 当前写入日志
    uint64 _len_max = (1 << 26);   // 最大长度--64M
    pair_name _pname;              // 文件名与后缀
    dstr _file;                    // 文件名
    std::fstream _fs;              // 文件对象
    std::ios_base::openmode _mode; // 文件打开模式
};

// 异步文件日志
template <uint64 Ttime = 500>
class Blog_out_asyn : public Blog_out_file
{
public:
    ~Blog_out_asyn()
    {
        if(_run) {
            _run = false;
            _th->join();
            flush();
        }
    }

    inline void out(cstr buf)
    {
        _write = true;
        std::lock_guard<std::mutex> lock(_mut);
        _que.push(buf);
        _write = false;

        if(!_run) {
            run_work();
        }
    }

    inline void flush() { Blog_out_file::flush(); }

protected:
    // 启动异步写入线程
    void run_work()
    {
        _run = true;
        _th = std::make_shared<std::thread>(&Blog_out_asyn::work_write, this);
    }

    // 将队列内日志写入日志输出类
    void work_write()
    {
        while(_run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(Ttime));
            std::lock_guard<std::mutex> lock(_mut);
            while(!_que.empty() && !_write) {
                Blog_out_file::out(_que.front());
                _que.pop();
            }
        }
        while(!_que.empty()) {
            Blog_out_file::out(_que.front());
            _que.pop();
        }
    }

protected:
    bool _run = false;                // 写入线程运行标记
    bool _write = false;              // 正在写入标记
    std::mutex _mut;                  // 队列锁
    std::queue<dstr> _que;            // 写入日志队列
    std::shared_ptr<std::thread> _th; // 写入线程
};

// 空打印日志
struct Blog_null : public Blog_base<Blog_buf<>, Blog_out_null>
{
    Blog_null() {}
};

// 命令行打印日志
struct Blog_cmd : public Blog_base<Blog_buf<>, Blog_out_cmd>
{
    Blog_cmd() {}
};

// 文件打印日志
struct Blog_file : public Blog_base<Blog_buf<>, Blog_out_file>
{
    Blog_file(cstr file = "Bflog.log") { _out.reopen(file); }
    Blog_out_file *operator->() { return &_out; }
};

// 文件打印日志-异步
struct Blog_asyn : public Blog_base<Blog_buf<>, Blog_out_asyn<>>
{
    Blog_asyn(cstr file = "Balog.log") { _out.reopen(file); }
    Blog_out_file *operator->() { return &_out; }
};

//
//
//
//

// 短结构-调试打印-VSCode快捷导航
struct Blog_suffix_short
{
    Blog_suffix_short()
    {
        _buf.reserve(_BH_INT_256_);
        _time.set_format("HH:TT:SS.LLL");
    }
    inline dstr suffix(cchp file, int32 line)
    {
        _buf.clear();
        _buf += "[";
        _buf += Bdiv(file)("/", -2, -1);
        _buf += ":";
        _buf += Bto::to_str(line);
        _buf += "][";
        _buf += _time.cur_datetime();
        _buf += "]";
        return _buf.to_str();
    }
    Bbuf _buf;
    Btimefms _time;
};

// 长结构-文件打印-VSCode快捷导航
struct Blog_suffix_long
{
    Blog_suffix_long() { _buf.reserve(_BH_INT_256_); }
    inline dstr suffix(cchp file, int32 line)
    {
        _buf.clear();
        _buf += "[";
        _buf += file;
        _buf += ":";
        _buf += Bto::to_str(line);
        _buf += "][";
        _buf += _time.cur_datetime();
        _buf += "]";
        return _buf.to_str();
    }
    Bbuf _buf;
    Btimefms _time;
};

// 标准容器打印
struct Blog_con
{
    template <typename T>
    inline static dstr print(const T &con, uint64 len = 1, cstr flg = " ", cstr prev = "| ")
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
            ret += Bto::to_str(a) + flg;
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

// 显示打印
#define BHLOG_MAKE(out, el, end, sfx, ...)                                                         \
    out << el "<<<< " << __VA_ARGS__ << " >>>>" << sfx.suffix(__FILE__, __LINE__) << end

// 生成快捷打印宏-带颜色
#define BHLOG_MAKE_COLA(out, sfx, ...)                                                             \
    BHLOG_MAKE(out, bh::bhenum::level::e_all << "\033[30m[All]",                                   \
               "\033[0m" << bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKE_COLD(out, sfx, ...)                                                             \
    BHLOG_MAKE(out, bh::bhenum::level::e_deb << "\033[32m[Deb]",                                   \
               "\033[0m" << bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKE_COLI(out, sfx, ...)                                                             \
    BHLOG_MAKE(out, bh::bhenum::level::e_inf << "\033[36m[Inf]",                                   \
               "\033[0m" << bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKE_COLW(out, sfx, ...)                                                             \
    BHLOG_MAKE(out, bh::bhenum::level::e_war << "\033[33m[War]",                                   \
               "\033[0m" << bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKE_COLE(out, sfx, ...)                                                             \
    BHLOG_MAKE(out, bh::bhenum::level::e_err << "\033[31m[Err]",                                   \
               "\033[0m" << bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKE_COLF(out, sfx, ...)                                                             \
    BHLOG_MAKE(out, bh::bhenum::level::e_fat << "\033[35m[Fat]",                                   \
               "\033[0m" << bh::bhenum::end::e_line, sfx, __VA_ARGS__)

// 生成快捷打印宏
#define BHLOG_MAKEA(out, sfx, ...)                                                                 \
    BHLOG_MAKE(out, bh::bhenum::level::e_all << "[All]", bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKED(out, sfx, ...)                                                                 \
    BHLOG_MAKE(out, bh::bhenum::level::e_deb << "[Deb]", bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKEI(out, sfx, ...)                                                                 \
    BHLOG_MAKE(out, bh::bhenum::level::e_inf << "[Inf]", bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKEW(out, sfx, ...)                                                                 \
    BHLOG_MAKE(out, bh::bhenum::level::e_war << "[War]", bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKEE(out, sfx, ...)                                                                 \
    BHLOG_MAKE(out, bh::bhenum::level::e_err << "[Err]", bh::bhenum::end::e_line, sfx, __VA_ARGS__)

#define BHLOG_MAKEF(out, sfx, ...)                                                                 \
    BHLOG_MAKE(out, bh::bhenum::level::e_fat << "[Fat]", bh::bhenum::end::e_line, sfx, __VA_ARGS__)

// 开启打印
#ifndef BHLOG_CLOSE_LOG
#define BHLOG_CONF(type) bh::Bsin_conf::get()->type

// 有颜色打印
#ifndef BHLOG_CLOSE_COL
#define vloga(...) BHLOG_MAKE_COLA(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogd(...) BHLOG_MAKE_COLD(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogi(...) BHLOG_MAKE_COLI(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogw(...) BHLOG_MAKE_COLW(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vloge(...) BHLOG_MAKE_COLE(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogf(...) BHLOG_MAKE_COLF(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)

// 无颜色打印
#else
#define vloga(...) BHLOG_MAKEA(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogd(...) BHLOG_MAKED(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogi(...) BHLOG_MAKEI(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogw(...) BHLOG_MAKEW(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vloge(...) BHLOG_MAKEE(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#define vlogf(...) BHLOG_MAKEF(BHLOG_CONF(_cmd), BHLOG_CONF(_sufs), __VA_ARGS__)
#endif

// 快捷文件打印
#define floga(...) BHLOG_MAKEA(BHLOG_CONF(_file), BHLOG_CONF(_sufl), __VA_ARGS__)
#define flogd(...) BHLOG_MAKED(BHLOG_CONF(_file), BHLOG_CONF(_sufl), __VA_ARGS__)
#define flogi(...) BHLOG_MAKEI(BHLOG_CONF(_file), BHLOG_CONF(_sufl), __VA_ARGS__)
#define flogw(...) BHLOG_MAKEW(BHLOG_CONF(_file), BHLOG_CONF(_sufl), __VA_ARGS__)
#define floge(...) BHLOG_MAKEE(BHLOG_CONF(_file), BHLOG_CONF(_sufl), __VA_ARGS__)
#define flogf(...) BHLOG_MAKEF(BHLOG_CONF(_file), BHLOG_CONF(_sufl), __VA_ARGS__)

// 快捷文件打印
#define aloga(...) BHLOG_MAKEA(BHLOG_CONF(_asyn), BHLOG_CONF(_sufl), __VA_ARGS__)
#define alogd(...) BHLOG_MAKED(BHLOG_CONF(_asyn), BHLOG_CONF(_sufl), __VA_ARGS__)
#define alogi(...) BHLOG_MAKEI(BHLOG_CONF(_asyn), BHLOG_CONF(_sufl), __VA_ARGS__)
#define alogw(...) BHLOG_MAKEW(BHLOG_CONF(_asyn), BHLOG_CONF(_sufl), __VA_ARGS__)
#define aloge(...) BHLOG_MAKEE(BHLOG_CONF(_asyn), BHLOG_CONF(_sufl), __VA_ARGS__)
#define alogf(...) BHLOG_MAKEF(BHLOG_CONF(_asyn), BHLOG_CONF(_sufl), __VA_ARGS__)

// 快捷空值打印
#define nloga(...) BHLOG_MAKEA(BHLOG_CONF(_null), BHLOG_CONF(_sufl), __VA_ARGS__)
#define nlogd(...) BHLOG_MAKED(BHLOG_CONF(_null), BHLOG_CONF(_sufl), __VA_ARGS__)
#define nlogi(...) BHLOG_MAKEI(BHLOG_CONF(_null), BHLOG_CONF(_sufl), __VA_ARGS__)
#define nlogw(...) BHLOG_MAKEW(BHLOG_CONF(_null), BHLOG_CONF(_sufl), __VA_ARGS__)
#define nloge(...) BHLOG_MAKEE(BHLOG_CONF(_null), BHLOG_CONF(_sufl), __VA_ARGS__)
#define nlogf(...) BHLOG_MAKEF(BHLOG_CONF(_null), BHLOG_CONF(_sufl), __VA_ARGS__)

// 关闭打印
#else
#define vloga(...)
#define vlogd(...)
#define vlogi(...)
#define vlogw(...)
#define vloge(...)
#define vlogf(...)

#define vloga(...)
#define vlogd(...)
#define vlogi(...)
#define vlogw(...)
#define vloge(...)
#define vlogf(...)

#define floga(...)
#define flogd(...)
#define flogi(...)
#define flogw(...)
#define floge(...)
#define flogf(...)

#define aloga(...)
#define alogd(...)
#define alogi(...)
#define alogw(...)
#define aloge(...)
#define alogf(...)

#define nloga(...)
#define nlogd(...)
#define nlogi(...)
#define nlogw(...)
#define nloge(...)
#define nlogf(...)

#endif

// 默认打印宏
struct Bsin_conf : public Bsind<Bsin_conf>
{
    Blog_cmd _cmd;
    Blog_null _null;
    Blog_file _file;
    Blog_asyn _asyn;
    Blog_suffix_long _sufl;
    Blog_suffix_short _sufs;
};

// 快捷打印操作
#define $(value) "[" #value ": " << value << "] "
#define $C(value) "[" #value ": " << bh::Blog_con::print(value) << "] "
#define $T(value) "[" #value ": " << bh::Bstr::from_stringstream(value) << "] "

} // namespace bh

#endif // BLOG_H