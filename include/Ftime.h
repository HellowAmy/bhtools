
#ifndef FTIME_H
#define FTIME_H

#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

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
    inline void push_point(const std::string &tips = "",bool now = false,bool reset = false) 
    { 
        if(reset) { _vec.clear(); }
        _vec.push_back(tips +" "+ to_string());
        if(now) { update(); }
    }

    // 获取加入时间点-可选择清空容器
    inline std::vector<std::string> check_vec() 
    { return _vec; }

    // 线性休眠时间
    inline static void sleep(size_t ms)
    { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }


    // internal
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
    
    static constexpr int64_t _tunix_epoch = 1970;
    static constexpr int64_t _tunix_year = 365;
    static constexpr int64_t _tnan_sec = 1000 * 1000 * 1000;
    static constexpr int64_t _tnan_mil = 1000 * 1000;
    static constexpr int64_t _tnan_mic = 1000;
    static constexpr int64_t _tsec_min = 60;
    static constexpr int64_t _tsec_hou = 60 * 60;
    static constexpr int64_t _tsec_day = 60 * 60 * 24;

    // 自定义格式
    struct data
    {
        int64_t nan;
        int64_t mic;
        int64_t mil;
        int64_t sec;
        int64_t min;
        int64_t hou;
        int64_t day;
        int64_t mon;
        int64_t yea;
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
    inline static nanoseconds time_now()
    { return system_clock::now().time_since_epoch(); }

    // 默认转为中国时区显示时间
    inline static std::string to_string(size_t UTC = 8)
    { 
        data d = to_data(time_now());
        d.hou += UTC;
        return to_string(d); 
    }

    // 转为默认UTC显示时间-传入时间点
    inline static std::string to_string(const data &d)
    {
        std::string ret = "[ " + 
            std::to_string(d.yea) +"-"+
            std::to_string(d.mon) +"-"+
            std::to_string(d.day) +"."+
            std::to_string(d.hou) +":"+
            std::to_string(d.min) +":"+
            std::to_string(d.sec) +"."+
            std::to_string(d.mil) +"."+
            std::to_string(d.mic) +"."+
            std::to_string(d.nan) +" ]";
        return ret;
    }

    // 返回默认中国时区时间
    inline static data to_data(size_t UTC = 8)
    {
        data d = to_data(time_now());
        d.hou += 8;
        return d;
    }

    // 返回C++标准库的UTC时间-具体地区的时间偏移需要自行计算
    // 参考 Howard Hinnant 的时间算法-无需使用月份查表的推算日期方式
    inline static data to_data(const std::chrono::nanoseconds& point) 
    {
        // 获取自 1970-01-01 以来的总纳秒数
        data d;
        int64_t count = point.count();

        // 从纳秒中获取秒和亚秒-亚秒指不足一秒的余数
        int64_t total_sec = count / _tnan_sec;
        int64_t sub_nan = count % _tnan_sec;
        
        // 处理负时间戳-1970年以前的日期-从秒中借位到亚秒
        if (sub_nan < 0) { total_sec--; sub_nan += _tnan_sec; } 

        // 获取纳秒数-从亚秒中提取毫秒到纳秒的值
        uint32_t rem_nan = uint32_t(sub_nan % _tnan_mil);
        d.mil = sub_nan / _tnan_mil;
        d.mic = rem_nan / _tnan_mic;
        d.nan = rem_nan % _tnan_mic;

        // 从秒数中算出总天数 
        int64_t days = total_sec / _tsec_day;
        int32_t rem_sec = int32_t(total_sec % _tsec_day);

        // 获取到亚天-不足时从天中借位到亚天
        if (rem_sec < 0) { days--; rem_sec += _tsec_day; }

        // 获取分钟数-提取小时到秒的值
        uint32_t rem_m = rem_sec % _tsec_hou;
        d.hou = rem_sec / _tsec_hou;
        d.min = rem_m / _tsec_min;
        d.sec = rem_m % _tsec_min;
        
        // Howard Hinnant 算法核心
        // 从 1970-01-01 平移到 0000-03-01 的零点年份-可以避免2月闰日的天数计算
        static constexpr int64_t tzeroyear = 719468;        // 1970-01-01 到 0000-03-01 的天数差
        static constexpr int64_t t400ysum = 146097;         // 格里高利历每400年
        static constexpr int64_t t100ysum = 36524;          // 格里高利历每100年
        static constexpr int64_t t4ysum = 1460;             // 格里高利历每4年
        static constexpr int64_t t3n7sum = 153;             // 3到7月总数
        static constexpr int64_t t400ysub1 = t400ysum - 1;  // 负数修正
        
        // 计算现在是第几个400年
        days += tzeroyear; 
        int64_t era = (days >= 0 ? days : days - t400ysub1) / t400ysum;
        
        // 计算400年你的第几天
        uint32_t doe = days - era * t400ysum; 
        
        // 计算这一天属于400年里的那一天
        uint32_t yoe = (doe - doe/t4ysum + doe/t100ysum - doe/t400ysub1) / _tunix_year; 
        
        // 算出是当年的第几天-从三月起
        uint32_t doy = doe - (_tunix_year * yoe + yoe/4 - yoe/100); 
        
        // 算出这一天在哪一个月份上-从三月起-这个值的范围是今年3月到明年2月
        uint32_t mp = (5*doy + 2)/t3n7sum; 
        
        // 如果 mp < 10 说明是3月到12月-如果是 >10 说明是次年的1月或2月-需要修正月分
        uint32_t month = mp < 10 ? mp + 3 : mp - 9;
        
        // 从400年天数上计算出当年位置
        // 根据月份修正年份-月份范围是今年3月到明年二月
        int32_t y = int32_t(yoe) + int32_t(era * 400);
        uint32_t year = month <= 2 ? y + 1 : y;

        // 计算当月第几天-使用当年天数减去总月份天数
        uint32_t day = doy - (t3n7sum*mp+2)/5 + 1;

        // 获取到具体年月日
        d.yea = year;
        d.mon = month;
        d.day = day;
        return d;
    }


    // 格式化日期格式-格式的替换字符如下-[%XC][百分号加字符串长度加类型]
    // %4Y-%2M-%2D.%2H:%2T:%2S.%3L.%3C.%3N >>>> 2024-09-02.15:44:28.804.245.495
    inline static std::string format_time(const data &d,const std::string &fm = "%4Y-%2M-%2D.%2H:%2T:%2S.%3L.%3C.%3N")
    {
        std::string ret;
        for(size_t i=0;i<fm.size();i++)
        {
            char c = fm[i];
            if(c == '%')
            {
                if(i+2 >= fm.size()) { return ""; } 
                size_t n = fm[i+1] - '0';

                if(n < 1 || n > 9) { return ""; } 
                char t = fm[i+2];

                if(t == 'Y') { ret += to_time_len(d.yea,n,true); }
                else if(t == 'M') { ret += to_time_len(d.mon,n); }
                else if(t == 'D') { ret += to_time_len(d.day,n); }
                else if(t == 'H') { ret += to_time_len(d.hou,n); }
                else if(t == 'T') { ret += to_time_len(d.min,n); }
                else if(t == 'S') { ret += to_time_len(d.sec,n); }
                else if(t == 'L') { ret += to_time_len(d.mil,n); }
                else if(t == 'C') { ret += to_time_len(d.mic,n); }
                else if(t == 'N') { ret += to_time_len(d.nan,n); }
                else { return ""; } 

                i += 2;
            }
            else { ret.push_back(c); }
        }
        return ret;
    }


    // internal
    // 格式化为指定长度的字符串
    inline static std::string to_time_len(size_t time,size_t len,bool reverse = false)
    {
        std::string s = std::to_string(time);
        if(s.size() > len) 
        {
            if(reverse) { s = s.erase(0,s.size()-len); } 
            else { s.resize(len); }
        }
        else if(s.size() < len)
        {
            std::string sf;
            sf.resize(len - s.size());
            std::fill(sf.begin(),sf.end(),'0');
            s = sf + s;
        }
        return s;
    }
};


} // bhtools

#endif // FTIME_H
