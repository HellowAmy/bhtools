
#ifndef TLOG_H
#define TLOG_H

#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>


namespace bhtools {


// 不同等级日志
namespace bhenum {
    
    enum class level4
    {
        e_deb,
        e_inf,
        e_war,
        e_err,
    };
    enum class level8
    {
        e_all,
        e_trace,
        e_debug,
        e_info,
        e_warning,
        e_error,
        e_fatal,
        e_off,
    };
}

//
//
//
//

// 日志等级判断
template<typename Tlevel>
struct Tlog_level 
{
    Tlog_level() { }

    Tlog_level(Tlevel el) { _level = el; }

    void status(bool ok) { _ok = ok; }

    bool pass() { return _ok; }

    void comp(const Tlog_level &el) 
    { if(el._level >= _level) { _ok = true; } else{ _ok = false; } }

    inline Tlog_level& operator<<(Tlevel el)
    { _level = el; return *this; };

    bool _ok = false;   // 是否满足等级
    Tlevel _level;      // 设置等级
};


// 日志缓冲区
struct Tlog_buf 
{ 
    template<typename T>
    inline std::string Tto_string(const T &val) 
    { return std::to_string(val); }

    inline std::string Tto_string(const char *val) 
    { return val; }

    inline std::string Tto_string(const std::string &val) 
    { return val;}

    template<typename T>
    inline void push(const T &val) 
    { _str += Tto_string(val); }

    inline void clear() 
    { _str.clear(); }

    inline std::string value() const
    { return _str; }

    std::string _str;   // 缓存内容
};


// 日志结束类标记
struct Tlog_end { };


// 日志基本类-用于创建各种输出类型的模板-不提供打印只提供写入与缓存
template<typename Tlevel,typename Tbuf,typename Tend,typename Tout>
struct Tlog_base
{
    // 设置日志等级-不显示低等级内容
    inline void set_level(Tlevel el) { _el = el; } 

    // 触发换行输出
    inline void out_end() { _out.out(_buf); }

    // 传入等级
    inline Tlog_base& operator<<(Tlevel el)
    { _el.comp(el); return *this; };

    // 打印内容
    inline Tlog_base& operator<<(Tend end)
    { if(_el.pass()){ out_end(); _buf.clear(); _el.status(false); } return *this; };

    // 传入换行
    template<class T>
    inline Tlog_base& operator<<(const T &log)
    { if(_el.pass()){ _buf.push(log); } return *this; };


    Tlevel _el;     // 日志等级划分枚举
    Tbuf _buf;      // 日志写入缓存内容
    Tout _out;      // 日志输出类
};


// 命令行打印
struct Tlog_cmd 
{
    void out(const Tlog_buf &buf) { std::cout<<buf.value()<<std::endl; }    
};


// 文件打印
struct Tlog_file
{
    void out(const Tlog_buf &buf) { _fs<<buf.value()<<std::endl; update_file(); } 

    //初始化日志
    inline bool reopen(const std::string &file = "Tflog.log",bool app = true) //初始化日志
    {
        _file = file;
        if(app) { _mode = std::ios::app; } 
        else { _mode = std::ios::out; } 

        if(_fs.is_open()) { _fs.close(); }
        _fs.open(_file,_mode);
        return _fs.is_open();
    }

    //获取秒精度的日期时间
    static std::string format_time()
    {
        std::time_t t = std::time(nullptr);
        std::tm *m = std::localtime(&t);
        std::stringstream sm;
        sm << std::put_time(m,"%Y-%m-%d %H:%M:%S");
        return sm.str();
    }
    
    // 设置循环最大文件数-默认无限
    inline void set_limit(size_t max) { _limit_max = max; } 

    // 设置单个文件最大长度-默认64M
    inline void set_length(size_t len) { _len_max = len;}  

    // 关闭文件
    inline void close() { _fs.close(); } 

    // 超出最大文件限制后更新文件名
    bool update_file() 
    {
        if(_len_max < _fs.tellg())
        {
            if(_limit_max == 0) { return write_unlimited(); }
            else { return write_limit(); } 
        }
        return true;
    }

    // 无限制日志
    bool write_unlimited()
    {
        _fs.close();
        for(int i=_limit_now;;i++)
        {
            std::string new_file = std::to_string(i) + "_" + _file;
            if(exist_file(new_file) == false)
            { 
                rename(_file.c_str(),new_file.c_str()); 
                _limit_now++;
                break;
            }
        }
        _fs.open(_file,_mode);
        return _fs.is_open();
    }

    // 限制日志数量
    bool write_limit() 
    {
        _fs.close();
        std::string new_file = std::to_string(_limit_now) + "_" + _file;
        rename(_file.c_str(),new_file.c_str());
        _limit_now++;
        if(_limit_now > _limit_max) { _limit_now = 1; }
        
        _fs.open(_file,_mode);
        return _fs.is_open();
    }

    // 判断文件是否存在
    static bool exist_file(const std::string &filename)
    { std::ifstream f(filename); return f.is_open(); }


    size_t _limit_max = 0;          //日志文件限制数量
    size_t _limit_now = 1;          //当前写入日志
    size_t _len_max = (1 << 26);    //最大长度--64M
    std::string _file;              //文件名
    std::fstream _fs;               //文件对象
    std::ios_base::openmode _mode;  //文件打开模式
};


// 命令行打印日志 等级4
struct Tlog_cmd4 : public Tlog_base <Tlog_level<bhenum::level4>,Tlog_buf,Tlog_end,Tlog_cmd> 
{
    Tlog_cmd4() { set_level(Tlog_level<bhenum::level4>(bhenum::level4::e_deb)); }
};


// 命令行打印日志 等级8
struct Tlog_cmd8 : public Tlog_base <Tlog_level<bhenum::level8>,Tlog_buf,Tlog_end,Tlog_cmd> 
{
    Tlog_cmd8() { set_level(Tlog_level<bhenum::level8>(bhenum::level8::e_all)); }
};


// 文件打印日志 等级4
struct Tlog_file4 : public Tlog_base <Tlog_level<bhenum::level4>,Tlog_buf,Tlog_end,Tlog_file> 
{
    Tlog_file4() { set_level(Tlog_level<bhenum::level4>(bhenum::level4::e_deb)); _out.reopen(); }
};

//
//
//
//

// 日志格式化内容
#define BHLOG_FORMAT(tips,el,...)                           \
    el<<tips "["<<__FILE__<<":<"<<__LINE__<<">] <<<< "      \
    <<__VA_ARGS__                                           \  


// 格式化VSCode快捷导航格式
#define BHLOG_FORMAT_VSC(tips,el,...)                       \
    el<<tips "["<<__FILE__<<":"<<__LINE__<<"] <<<< "        \
    <<__VA_ARGS__                                           \  


// 格式化VSCode快捷导航格式-文件输出
#define BHLOG_FORMAT_VSC_FILE(tips,el,...)                  \
    el<<tips<<" <<<< "<<__VA_ARGS__                         \
    <<"["<<__FILE__<<":"<<__LINE__<<"]"                     \


// 生成打印字符串
#define BHLOG_PRINT(out,tips,BHDF_FM,end,el,et,...)                                 \
    out<<BHDF_FM(tips,Tlog_level<bhenum::el>(bhenum::el::et),__VA_ARGS__)<<end      \


// 快捷打印宏
#ifndef BHLOG_CLOSE_LOG

    // 快捷命令行打印 等级4
    #ifndef BHLOG_CLOSE_COL
        #define vlogi(...) BHLOG_PRINT((*_sp_cmd4_),"\033[36m[Inf]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_inf,__VA_ARGS__<<"\033[0m")
        #define vlogd(...) BHLOG_PRINT((*_sp_cmd4_),"\033[32m[Deb]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_deb,__VA_ARGS__<<"\033[0m")
        #define vlogw(...) BHLOG_PRINT((*_sp_cmd4_),"\033[33m[War]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_war,__VA_ARGS__<<"\033[0m")
        #define vloge(...) BHLOG_PRINT((*_sp_cmd4_),"\033[31m[Err]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_err,__VA_ARGS__<<"\033[0m")
    #else
        #define vlogi(...) BHLOG_PRINT((*_sp_cmd4_),"[Inf]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_inf,__VA_ARGS__)
        #define vlogd(...) BHLOG_PRINT((*_sp_cmd4_),"[Deb]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_deb,__VA_ARGS__)
        #define vlogw(...) BHLOG_PRINT((*_sp_cmd4_),"[War]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_war,__VA_ARGS__)
        #define vloge(...) BHLOG_PRINT((*_sp_cmd4_),"[Err]",BHLOG_FORMAT_VSC,Tlog_end(),level4,e_err,__VA_ARGS__)
    #endif

    // 快捷命令行打印-自行扩展 等级8
    #ifndef BHLOG_CLOSE_COL
        #define vlogd8(...) BHLOG_PRINT((*_sp_cmd8_),"\033[32m[Deb-level8]",BHLOG_FORMAT_VSC,Tlog_end(),level8,e_debug,__VA_ARGS__<<"\033[0m")
    #else
        #define vlogd8(...) BHLOG_PRINT((*_sp_cmd8_),"[Deb-level8]",BHLOG_FORMAT_VSC,Tlog_end(),level8,e_debug,__VA_ARGS__)
    #endif

    // 快捷文件打印 等级4
    #define flogi(...) BHLOG_PRINT((*_sp_file4_),"[Inf] ["+_sp_file4_->_out.format_time()+"]",BHLOG_FORMAT_VSC_FILE,Tlog_end(),level4,e_inf,__VA_ARGS__)
    #define flogd(...) BHLOG_PRINT((*_sp_file4_),"[Deb] ["+_sp_file4_->_out.format_time()+"]",BHLOG_FORMAT_VSC_FILE,Tlog_end(),level4,e_deb,__VA_ARGS__)
    #define flogw(...) BHLOG_PRINT((*_sp_file4_),"[War] ["+_sp_file4_->_out.format_time()+"]",BHLOG_FORMAT_VSC_FILE,Tlog_end(),level4,e_war,__VA_ARGS__)
    #define floge(...) BHLOG_PRINT((*_sp_file4_),"[Err] ["+_sp_file4_->_out.format_time()+"]",BHLOG_FORMAT_VSC_FILE,Tlog_end(),level4,e_err,__VA_ARGS__)

#else
    #define vlogi(...)
    #define vlogd(...)
    #define vlogw(...)
    #define vloge(...)

    #define vlogd8(...)

    #define flogi(...) 
    #define flogd(...) 
    #define flogw(...) 
    #define floge(...) 
#endif

//
//
//
//

// 标准容器打印
template<class T>
std::string Tlog_con(const T& con,const std::string &prve = "| ",const std::string &flg = " ",size_t len = 10)
{
    std::string ret = "\n";
    ret += prve + "size: " + std::to_string(con.size());
    ret += "\n" + prve;
    size_t count = 0;
    Tlog_buf buf;
    for(const auto &a:con)
    {
        if(len != 0 && count >= len) { count = 0; ret += "\n" + prve; }
        ret += buf.Tto_string(a) + flg;
        count++;
    }
    ret += "\n";
    return ret;
}

//
//
//
//

// 快捷使用定义
typedef Tlog_level<bhenum::level4> logel4;
typedef bhenum::level4 el4;

static Tlog_cmd4 *_sp_cmd4_ = new Tlog_cmd4;
static Tlog_cmd8 *_sp_cmd8_ = new Tlog_cmd8;
static Tlog_file4 *_sp_file4_ = new Tlog_file4;

#define $(value) "["#value": "<<value<<"] "
#define $C(value) "["#value": "<<Tlog_con(value)<<"] "



} // bhtools


#endif // TLOG_H
