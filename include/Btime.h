#ifndef BTIME_H
#define BTIME_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>

#include "Bstr.h"
#include "Bstrto.h"

namespace bh {

// 用于记录线性流逝的时间点
class Btimel
{
public:
    struct data
    {
        int64 nan;
        int64 mic;
        int64 mil;
        int64 sec;
    };

public:
    typedef std::chrono::nanoseconds nanoseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    typedef std::chrono::steady_clock steady_clock;
    typedef std::chrono::time_point<steady_clock, nanoseconds> time_point;

    // 启动时开始计时
    Btimel() { update(); }

    // 获取从开始时的时间间隔
    inline nanoseconds time_interval() { return steady_clock::now() - _begin; }

    // 转自定义格式
    inline static data to_data(const nanoseconds &loss)
    {
        data ret{0};
        ret.nan = loss.count();
        ret.mic = std::chrono::duration_cast<microseconds>(loss).count();
        ret.mil = std::chrono::duration_cast<milliseconds>(loss).count();
        ret.sec = std::chrono::duration_cast<seconds>(loss).count();
        return ret;
    }

    // 转字符显示
    inline static Bstr to_str(const nanoseconds &loss)
    {
        // 顺序 [纳秒|微秒|毫秒|秒]
        data d = to_data(loss);
        Bstr str;
        str << "[nan: " << Bstrto::to_str(d.nan) << "|mic: " << Bstrto::to_str(d.mic)
            << "|mil: " << Bstrto::to_str(d.mil) << "|sec: " << Bstrto::to_str(d.sec) << "]";
        return str;
    }

    // 获取当前时间显示
    inline Bstr to_str() { return to_str(time_interval()); }

    // 刷新开始时间
    inline void update() { _begin = steady_clock::now(); }

    // 线性休眠时间
    inline static void sleep(uint32 ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

protected:
    time_point _begin;
};

//
//
//
//

// 显示系统时间与日期格式
class Btimes
{
public:
    typedef std::chrono::nanoseconds nanoseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    typedef std::chrono::minutes minutes;
    typedef std::chrono::hours hours;
    typedef std::chrono::system_clock system_clock;

    // 日期相关预设值
    static constexpr int64 _tnan_sec = 1000 * 1000 * 1000;
    static constexpr int64 _tnan_mil = 1000 * 1000;
    static constexpr int64 _tnan_mic = 1000;
    static constexpr int64 _tsec_min = 60;
    static constexpr int64 _tsec_hou = 60 * 60;
    static constexpr int64 _tsec_day = 60 * 60 * 24;

    // 自定义格式
    struct data
    {
        int64 nan;
        int64 mic;
        int64 mil;
        int64 sec;
        int64 min;
        int64 hou;
        int64 day;
        int64 mon;
        int64 yea;
    };

public:
    // 当前时间的C-tm格式时间
    inline static Bstr to_ctime(Bstrvi format = "[ %Y-%m-%d.%H:%M:%S ]")
    {
        std::time_t t = system_clock::to_time_t(system_clock::now());
        std::tm *m = std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(m, format.data());
        return ss.str();
    }

    // 获取当前UTC时间
    inline static nanoseconds time_now() { return system_clock::now().time_since_epoch(); }

    // 默认转为中国时区显示时间
    inline static Bstr to_str(int32 UTC = 8)
    {
        data d = to_data(time_now());
        d.hou += UTC;
        return format_time(d);
    }

    // 返回默认中国时区时间
    inline static data to_data(int32 UTC)
    {
        data d = to_data(time_now());
        d.hou += UTC;
        return d;
    }

    // 返回C++标准库的UTC时间-具体地区的时间偏移需要自行计算
    // 参考 Howard Hinnant 的时间算法-无需使用月份查表的推算日期方式
    inline static data to_data(const nanoseconds &point)
    {
        // 获取自 1970-01-01 以来的总纳秒数
        data d{0};
        int64 count = point.count();

        // 从纳秒中获取秒和亚秒-亚秒指不足一秒的余数
        int64 total_sec = count / _tnan_sec;
        int64 sub_nan = count % _tnan_sec;

        // 处理负时间戳-1970年以前的日期-从秒中借位到亚秒
        if(sub_nan < 0) {
            total_sec--;
            sub_nan += _tnan_sec;
        }

        // 获取纳秒数-从亚秒中提取毫秒到纳秒的值
        int64 rem_nan = sub_nan % _tnan_mil;
        d.mil = sub_nan / _tnan_mil;
        d.mic = rem_nan / _tnan_mic;
        d.nan = rem_nan % _tnan_mic;

        // 从秒数中算出总天数
        int64 days = total_sec / _tsec_day;
        int64 rem_sec = total_sec % _tsec_day;

        // 获取到亚天-不足时从天中借位到亚天
        if(rem_sec < 0) {
            days--;
            rem_sec += _tsec_day;
        }

        // 获取分钟数-提取小时到秒的值
        int64 rem_m = rem_sec % _tsec_hou;
        d.hou = rem_sec / _tsec_hou;
        d.min = rem_m / _tsec_min;
        d.sec = rem_m % _tsec_min;

        // Howard Hinnant 算法核心
        // 从 1970-01-01 平移到 0000-03-01 的零点年份-可以避免2月闰日的天数计算
        // 719468 是 1970-01-01 到 0000-03-01 的天数差
        // 146097 是 格里高利历每400年
        // 36524 是 格里高利历每100年
        // 1460 是 格里高利历每4年
        // 153 是 3到7月总数

        // 计算现在是第几个400年
        days += 719468;
        int64 era = (days >= 0 ? days : days - 146096) / 146097;

        // 计算400年你的第几天
        int64 doe = days - era * 146097;

        // 计算这一天属于400年里的那一天
        int64 yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;

        // 算出是当年的第几天-从三月起
        int64 doy = doe - (365 * yoe + yoe / 4 - yoe / 100);

        // 算出这一天在哪一个月份上-从三月起-这个值的范围是今年3月到明年2月
        int64 mp = (5 * doy + 2) / 153;

        // 如果 mp < 10 说明是3月到12月-如果是 >10 说明是次年的1月或2月-需要修正月分
        int64 month = mp < 10 ? mp + 3 : mp - 9;

        // 从400年天数上计算出当年位置
        // 根据月份修正年份-月份范围是今年3月到明年二月
        int64 y = yoe + era * 400;
        int64 year = month <= 2 ? y + 1 : y;

        // 计算当月第几天-使用当年天数减去总月份天数
        int64 day = doy - (153 * mp + 2) / 5 + 1;

        // 获取到具体年月日
        d.yea = year;
        d.mon = month;
        d.day = day;
        return d;
    }

    // 逆向运算为纳秒
    // 采用 Howard Hinnant 算法的逆推逻辑
    inline static nanoseconds from_data(const data &d)
    {
        // 平移到0000年和3月份开始
        int64 y = d.yea - (d.mon <= 2 ? 1 : 0);
        int64 m = d.mon > 2 ? d.mon - 3 : d.mon + 9;
        int64 day = d.day;

        // 从0000到这天的关键时间点-获取天数
        int64 era = (y >= 0 ? y : y - 399) / 400;
        int64 yoe = y - era * 400;
        int64 doy = (153 * m + 2) / 5 + day - 1;
        int64 doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
        int64 total_days = era * 146097 + doe;

        // 从0000年平移回1970
        int64 unix_days = total_days - 719468;

        // 转为总秒数
        int64 total_sec = unix_days * _tsec_day + d.hou * _tsec_hou + d.min * _tsec_min + d.sec;

        // 统计所有时间
        int64 total_nan = total_sec * _tnan_sec + d.mil * _tnan_mil + d.mic * _tnan_mic + d.nan;
        return nanoseconds(total_nan);
    }

    // 格式化日期格式-格式的替换字符如下-在原字符串从后向前替换-空位补零
    // YYYY-MM-DD.HH:TT:SS.LLL.CCC.NNN >>>> 2024-09-02.15:44:28.804.245.495
    inline static Bstr format_time(const data &d, Bstrvi fm = "YYYY-MM-DD.HH:TT:SS.LLL.CCC.NNN")
    {
        if(fm.size() <= 0) {
            return "";
        }

        // 从尾部替换
        Bstr ret = fm;
        Bstr time;
        bool into = true;
        int32 rindex = ret.size() - 1;
        while(rindex >= 0) {
            into = true;
            char c = ret[rindex];
            if(c == 'Y') {
                time = Bstrto::to_str(d.yea);
            }
            else if(c == 'M') {
                time = Bstrto::to_str(d.mon);
            }
            else if(c == 'D') {
                time = Bstrto::to_str(d.day);
            }
            else if(c == 'H') {
                time = Bstrto::to_str(d.hou);
            }
            else if(c == 'T') {
                time = Bstrto::to_str(d.min);
            }
            else if(c == 'S') {
                time = Bstrto::to_str(d.sec);
            }
            else if(c == 'L') {
                time = Bstrto::to_str(d.mil);
            }
            else if(c == 'C') {
                time = Bstrto::to_str(d.mic);
            }
            else if(c == 'N') {
                time = Bstrto::to_str(d.nan);
            }
            else {
                into = false;
                rindex--;
            }

            // 进入替换
            if(into) {
                char pch = c;
                int32 tidx = time.size() - 1;
                ret[rindex] = time[tidx];
                rindex--;
                tidx--;
                while(rindex >= 0) {
                    c = ret[rindex];
                    if(pch == c) {
                        if(tidx >= 0) {
                            ret[rindex] = time[tidx];
                        }
                        else {
                            ret[rindex] = '0';
                        }
                        rindex--;
                        tidx--;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        return ret;
    }
};

} // namespace bh

#endif // BTIME_H
