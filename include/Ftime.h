
#ifndef FTIME_H
#define FTIME_H

#include <chrono>
#include <vector>
#include <string>


namespace bhtools {


// 用于记录线性流逝的时间点
struct Ftimel
{
    typedef std::chrono::nanoseconds nanoseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    typedef std::chrono::steady_clock steady_clock;
    typedef typename std::chrono::time_point<std::chrono::steady_clock,std::chrono::nanoseconds> time_point;

    // 自定义格式
    struct data
    {
        size_t nan;
        size_t mic;
        size_t mil;
        size_t sec;
    };

    // 启动时开始计时
    Ftimel() { update(); }

    // 获取从开始时的时间间隔
    inline nanoseconds time_interval()
    { return steady_clock::now() - _begin; }

    // 转自定义格式
    inline data to_data(const nanoseconds &loss)
    {
        data ret;
        ret.nan = loss.count();
        ret.mic = std::chrono::duration_cast<microseconds>(loss).count();
        ret.mil = std::chrono::duration_cast<milliseconds>(loss).count();
        ret.sec = std::chrono::duration_cast<seconds>(loss).count();
        return ret;
    }

    // 转字符显示
    inline std::string to_string(const nanoseconds &loss)
    {
        //顺序 [纳秒|微秒|毫秒|秒]
        data d = to_data(loss);
        std::string str =
                "[nan: " + std::to_string(d.nan) +
                "|mic: " + std::to_string(d.mic) +
                "|mil: " + std::to_string(d.mil) +
                "|sec: " + std::to_string(d.sec) +
                "]";
        return str;
    }

    // 获取当前时间显示
    inline std::string to_string()
    { return to_string(time_interval()); }

    // 刷新开始时间
    inline void update() { _begin = steady_clock::now(); }

    // 加入时间点-用于多点记录时一起打印-可选择清空容器-可选择重置时间
    inline void push_point(const std::string &tips = "",bool reset = false,bool now = false) 
    { 
        if(reset) { _vec.clear(); }
        if(now) { update(); }
        _vec.push_back(tips +" "+ to_string());
    }

    // 获取加入时间点-可选择清空容器
    inline std::vector<std::string> check_vec() 
    { return _vec; }

    time_point _begin;              //用于计算上一个时间点
    std::vector<std::string> _vec;  //多点打印记录
};

//
//
//
//

// 显示系统时间与日期格式
struct Ftimes
{
    typedef std::chrono::nanoseconds nanoseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    typedef std::chrono::minutes minutes;
    typedef std::chrono::hours hours;
    typedef std::chrono::duration<int64_t, std::ratio<60*60*24>>  days;
    typedef std::chrono::duration<int64_t, std::ratio<60*60*24*30>>  months;
    typedef std::chrono::duration<int64_t, std::ratio<60*60*24*30*12>>  years;
    typedef std::chrono::system_clock system_clock;
    typedef typename std::chrono::time_point<std::chrono::system_clock,std::chrono::nanoseconds> time_point;

    // 自定义格式
    struct data
    {
        size_t mil;
        size_t sec;
        size_t min;
        size_t hou;
        size_t day;
        size_t mon;
        size_t yea;
    };

    Ftimes() { _begin = system_clock::now(); }
    ~Ftimes() {}

    inline nanoseconds time_now()
    { return system_clock::now().time_since_epoch(); }

    std::string to_string()
    { return to_string(time_now()); }

    std::string to_string(const nanoseconds &point)
    {
        std::string ret;
        return ret;
    }

    data to_data(const nanoseconds &point)
    {
        data d;
        d.mil = std::chrono::duration_cast<milliseconds>(point).count();
        d.sec = std::chrono::duration_cast<seconds>(point).count();
        d.min = std::chrono::duration_cast<minutes>(point).count();
        d.hou = std::chrono::duration_cast<hours>(point).count();
        d.day = std::chrono::duration_cast<days>(point).count();
        d.mon = std::chrono::duration_cast<months>(point).count();
        d.yea = std::chrono::duration_cast<years>(point).count();
        return d;
    }

    time_point _begin;
};


} // bhtools




#endif // FTIME_H
