
#ifndef FTIME_H
#define FTIME_H

#include <chrono>
#include <vector>
#include <string>

#include <Tlog.h>

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
    inline static data to_data(const nanoseconds &loss)
    {
        data ret;
        ret.nan = loss.count();
        ret.mic = std::chrono::duration_cast<microseconds>(loss).count();
        ret.mil = std::chrono::duration_cast<milliseconds>(loss).count();
        ret.sec = std::chrono::duration_cast<seconds>(loss).count();
        return ret;
    }

    // 转字符显示
    inline static std::string to_string(const nanoseconds &loss)
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
    typedef std::chrono::system_clock system_clock;
    typedef typename std::chrono::time_point<std::chrono::system_clock,std::chrono::nanoseconds> time_point;

    // 日期相关预设值
    inline static constexpr size_t _tunix_epoch = 1970;
    inline static constexpr size_t _tunix_year = 365;
    inline static constexpr size_t _tnan_sec = 1000 * 1000 * 1000;
    inline static constexpr size_t _tnan_mil = 1000 * 1000;
    inline static constexpr size_t _tnan_mic = 1000;
    inline static constexpr size_t _tsec_min = 60;
    inline static constexpr size_t _tsec_hou = 60 * 60;
    inline static constexpr size_t _tsec_day = 60 * 60 * 24;
    inline static std::vector<size_t> _vec_normal { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
    inline static std::vector<size_t> _vec_leap   { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

    // 自定义格式
    struct data
    {
        size_t nan;
        size_t mic;
        size_t mil;
        size_t sec;
        size_t min;
        size_t hou;
        size_t day;
        size_t mon;
        size_t yea;
    };


    // 当前时间的C-tm格式时间
    inline static std::string to_ctime(const std::string &format = "[ %Y-%m-%d.%H:%M:%S ]")
    {
        std::time_t t = system_clock::to_time_t(system_clock::now());
        std::tm *m = std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(m, format.c_str());
        return ss.str();
    }

    // 获取当前UTC时间
    inline nanoseconds time_now()
    { return system_clock::now().time_since_epoch(); }

    // 默认转为中国时区显示时间
    std::string to_string(size_t UTC = 8)
    { return to_string(time_now(),UTC); }

    // 转为默认UTC显示时间-传入时间点
    inline std::string to_string(const nanoseconds &point,size_t UTC)
    {
        data d = to_data(point);
        std::string ret = "[ " + 
            std::to_string(d.yea) +"-"+
            std::to_string(d.mon) +"-"+
            std::to_string(d.day) +"."+
            std::to_string(d.hou + UTC) +":"+
            std::to_string(d.min) +":"+
            std::to_string(d.sec) +"."+
            std::to_string(d.mil) +"."+
            std::to_string(d.mic) +"."+
            std::to_string(d.nan) +" ]";
        return ret;
    }

    // 返回C++标准库的UTC时间-具体地区的时间偏移需要自行计算
    inline data to_data(const nanoseconds &point)
    {
        // 计算秒到天的时间
        data d;
        size_t len_sec = std::chrono::duration_cast<seconds>(point).count();
        size_t len_day = len_sec / _tsec_day;
        size_t res_hou = len_sec % _tsec_day;
        size_t res_min = res_hou % _tsec_hou;
        d.hou = res_hou / _tsec_hou;
        d.min = (res_hou % _tsec_hou) / _tsec_min;
        d.sec = (res_hou % _tsec_hou) % _tsec_min;

        // 计算秒以下的时间
        size_t len_nan = len_sec * _tnan_sec; 
        size_t less_nan = point.count() - len_nan;
        d.mil = less_nan / _tnan_mil;
        d.mic = (less_nan % _tnan_mil) % _tnan_mic;
        d.nan = (less_nan % _tnan_mil) / _tnan_mic;

        // 先计算假设值一年为固定的365天-获取年份后计算纪元时间到当前时间
        // 再加上两个时间点之间存在的润日-如果加上润日超过365天则将时间推进到下一年
        // 计算出下一年所经过的天数-如果小时365天则时间被确定后退出计算
        // [代码来源借鉴 GLIBC offtime 函数]
        size_t year_next = _tunix_epoch;
        size_t days_less = len_day;
        while(days_less < 0 || days_less >= get_year_leap(year_next))
        {
            size_t year_now = year_next + days_less / _tunix_year - (days_less % _tunix_year < 0);
            days_less -= (year_now - year_next) * _tunix_year + count_leap(year_now -1) - count_leap(year_next -1);
            year_next = year_now;
        }

        // 计算日期-传入当年经过的天数-计算天数所属的月份
        auto vec = get_month_leap(year_next);
        for(int i=0;i<vec.size();i++)
        {
            if(days_less <= vec[i])
            {
                d.yea = year_next;
                d.mon = i;
                d.day = days_less - vec[i-1] + 1;
                break;
            }
        }
        return d;
    }


    // 得到传入年的每月累加分部天数-包括润年
    inline static std::vector<size_t> get_month_leap(int64_t year)
    { return (is_leap(year) ? _vec_leap : _vec_normal); }

    // 得到传入年的时间-包括润年
    inline static size_t get_year_leap(int64_t year)
    { return (is_leap(year) ? (_tunix_year +1) : _tunix_year); }

    // 判断是否为闰年
    inline static bool is_leap(int64_t year)
    { return ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0)); }

    // 计算除数-小于零则加一
    inline static int64_t calc_res(int64_t a,int64_t b)
    { return ((a) / (b) - ((a) % (b) < 0)); }

    // 计算传入时间包含的润日
    inline static int64_t count_leap(int64_t year)
    { return (calc_res(year, 4) - calc_res(year, 100) + calc_res(year, 400)); }
};


} // bhtools




#endif // FTIME_H
