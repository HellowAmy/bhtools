
#ifndef TLOG_H
#define TLOG_H

#include <functional>
#include <string>
#include <iostream>

namespace bhtools {


// 不同等级日志
namespace bhenum {
    
    enum class level4
    {
        e_debug,
        e_info,
        e_warning,
        e_error,
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


// 日志结束类标记
struct Tlog_end { };

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

    inline std::string value() 
    { return _str; }

    std::string _str;
};



// 基础打印类
template<typename Tlevel,typename Tbuf,typename Tend>
class Tlog_base
{
public:
    inline void set_level(Tlevel el) { _level = el; } 

    inline void out_end() { if(_fn_end){ _fn_end(); }  std::cout<<"buf: "<<_buf.value()<<std::endl; }

    inline Tlog_base& operator<<(Tlevel el)
    { if(el >= _level){ _ok = true; } else{ _ok = false; } return *this; };

    inline Tlog_base& operator<<(Tend end)
    { if(_ok){ out_end(); _buf.clear(); _ok = false; } return *this; };

    template<class T>
    inline Tlog_base& operator<<(const T &log)
    { if(_ok){ _buf.push(log); } return *this; };

public:
    std::function<void()> _fn_end = nullptr;

protected:
    bool _ok = false;   //判断等级是否符合
    Tlevel _level;      //最低显示的等级
    Tbuf _buf;
};


/*



template<class Tlevel>
class Tvlog
{
public:
    inline void set_level(Tlevel el){ _level = el; } //设置等级

    inline Tvlog& operator<<(Tlevel el)
    { if(el <= _level) _ok = true; else _ok = false; return *this; };

    inline Tvlog& operator<<(std::ostream& (*end)(std::ostream&))
    { if(_ok) std::cout<<end; return *this; };

    template<class T>
    inline Tvlog& operator<<(const T &log)
    { if(_ok) std::cout<<log; return *this; };

private:
    bool _ok = false;   //判断等级是否符合
    Tlevel _level;      //最低显示的等级
};



template<typename T>
inline std::string Tto_string(const T &ctx)
{
    return std::to_string(ctx);
}

inline std::string Tto_string(const char *ctx)
{
    return ctx;
}

inline std::string Tto_string(const std::string &ctx)
{
    return ctx;
}

*/






} // bhtools


#endif // TLOG_H
