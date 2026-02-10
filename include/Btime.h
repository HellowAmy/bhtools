#ifndef BTIME_H
#define BTIME_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>

#include "Bview.h"
#include "Btype.h"
#include "Bto.h"

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
    inline static data to_data(nanoseconds loss)
    {
        data ret{0};
        ret.nan = loss.count();
        ret.mic = std::chrono::duration_cast<microseconds>(loss).count();
        ret.mil = std::chrono::duration_cast<milliseconds>(loss).count();
        ret.sec = std::chrono::duration_cast<seconds>(loss).count();
        return ret;
    }

    // 转字符显示
    inline static dstr to_str(nanoseconds loss)
    {
        // 顺序 [纳秒|微秒|毫秒|秒]
        data d = to_data(loss);
        dstr str;
        str += "[nan: ";
        str += Bto::to_str(d.nan);
        str += "|mic: ";
        str += Bto::to_str(d.mic);
        str += "|mil: ";
        str += Bto::to_str(d.mil);
        str += "|sec: ";
        str += Bto::to_str(d.sec);
        str += "]";
        return str;
    }

    // 获取当前时间显示
    inline dstr to_str() { return to_str(time_interval()); }

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
    inline static dstr to_ctime(Bview format = "%Y-%m-%d.%H:%M:%S")
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
    inline static dstr to_str(int32 UTC = 8)
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
    inline static data to_data(nanoseconds point)
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
    inline static dstr format_time(const data &d, Bview fm = "YYYY-MM-DD.HH:TT:SS.LLL.CCC.NNN")
    {
        if(fm.size() <= 0) {
            return "";
        }

        // 从尾部替换
        dstr ret(fm.data(), fm.size());
        dstr time;
        bool into = true;
        int32 rindex = ret.size() - 1;
        while(rindex >= 0) {
            into = true;
            char c = ret[rindex];
            if(c == 'Y') {
                time = Bto::to_str(d.yea);
            }
            else if(c == 'M') {
                time = Bto::to_str(d.mon);
            }
            else if(c == 'D') {
                time = Bto::to_str(d.day);
            }
            else if(c == 'H') {
                time = Bto::to_str(d.hou);
            }
            else if(c == 'T') {
                time = Bto::to_str(d.min);
            }
            else if(c == 'S') {
                time = Bto::to_str(d.sec);
            }
            else if(c == 'L') {
                time = Bto::to_str(d.mil);
            }
            else if(c == 'C') {
                time = Bto::to_str(d.mic);
            }
            else if(c == 'N') {
                time = Bto::to_str(d.nan);
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

class Btimefms : public Btimes
{
public:
    struct posdate
    {
        int32 bpos = 0;
        int32 epos = 0;
        inline int32 size() { return epos - bpos; }
    };

    struct record
    {
        posdate yea;
        posdate mon;
        posdate day;
        posdate hou;
        posdate min;
        posdate sec;
        posdate mil;
        posdate mic;
        posdate nan;
    };

public:
    Btimefms(Bview fm = "YYYY-MM-DD.HH:TT:SS.LLL.CCC.NNN") { set_format(fm); }

    inline void set_format(Bview fm)
    {
        if(_cache_date != nullptr) {
            delete[] _cache_date;
        }
        _cache_date = new char[fm.size() + 1];
        std::memset(_cache_date, 0, fm.size() + 1);
        std::memcpy(_cache_date, fm.data(), fm.size());

        // _cache_date.clear();
        // _cache_date.append(fm.data(), fm.size());

        for(int32 i = 0; i < fm.size(); i++) {
            char c = fm[i];

            if(c == 'Y') {
                if(_rec.yea.bpos != _rec.yea.epos) {
                    _rec.yea.epos++;
                }
                else {
                    _rec.yea.bpos = i;
                    _rec.yea.epos = _rec.yea.bpos + 1;
                }
            }
            else if(c == 'M') {
                if(_rec.mon.bpos != _rec.mon.epos) {
                    _rec.mon.epos++;
                }
                else {
                    _rec.mon.bpos = i;
                    _rec.mon.epos = _rec.mon.bpos + 1;
                }
            }
            else if(c == 'D') {
                if(_rec.day.bpos != _rec.day.epos) {
                    _rec.day.epos++;
                }
                else {
                    _rec.day.bpos = i;
                    _rec.day.epos = _rec.day.bpos + 1;
                }
            }
            else if(c == 'H') {
                if(_rec.hou.bpos != _rec.hou.epos) {
                    _rec.hou.epos++;
                }
                else {
                    _rec.hou.bpos = i;
                    _rec.hou.epos = _rec.hou.bpos + 1;
                }
            }
            else if(c == 'T') {

                if(_rec.min.bpos != _rec.min.epos) {
                    _rec.min.epos++;
                }
                else {
                    _rec.min.bpos = i;
                    _rec.min.epos = _rec.min.bpos + 1;
                }
            }
            else if(c == 'S') {
                if(_rec.sec.bpos != _rec.sec.epos) {
                    _rec.sec.epos++;
                }
                else {
                    _rec.sec.bpos = i;
                    _rec.sec.epos = _rec.sec.bpos + 1;
                }
            }
            else if(c == 'L') {
                if(_rec.mil.bpos != _rec.mil.epos) {
                    _rec.mil.epos++;
                }
                else {
                    _rec.mil.bpos = i;
                    _rec.mil.epos = _rec.mil.bpos + 1;
                }
            }
            else if(c == 'C') {
                if(_rec.mic.bpos != _rec.mic.epos) {
                    _rec.mic.epos++;
                }
                else {
                    _rec.mic.bpos = i;
                    _rec.mic.epos = _rec.mic.bpos + 1;
                }
            }
            else if(c == 'N') {
                if(_rec.nan.bpos != _rec.nan.epos) {
                    _rec.nan.epos++;
                }
                else {
                    _rec.nan.bpos = i;
                    _rec.nan.epos = _rec.nan.bpos + 1;
                }
            }
        }
    }

    inline dstr get_now_date() { return get_date(time_now()); }

    inline dstr get_date(nanoseconds point)
    {
        // 同一天不计算日期
        data d{0};
        int64 day = get_cur_day(point, d);
        if(_cur_day == day) {
            push_number(_rec.hou, d.hou);
            push_number(_rec.min, d.min);
            push_number(_rec.sec, d.sec);
            push_number(_rec.mil, d.mil);
            push_number(_rec.mic, d.mic);
            push_number(_rec.nan, d.nan);
            return dstr(_cache_date, strlen(_cache_date));
        }

        // 新一天重新计算日期
        d = to_data(point);
        push_number(_rec.yea, d.yea);
        push_number(_rec.mon, d.mon);
        push_number(_rec.day, d.day);
        push_number(_rec.hou, d.hou);
        push_number(_rec.min, d.min);
        push_number(_rec.sec, d.sec);
        push_number(_rec.mil, d.mil);
        push_number(_rec.mic, d.mic);
        push_number(_rec.nan, d.nan);
        _cur_day = day;
        return dstr(_cache_date, strlen(_cache_date));
    }

    // protected:

    // 计算总天数
    inline int64 get_cur_day(nanoseconds point, data &d)
    {

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
        return days;
    }

    inline dchp ptr_cache(int32 pos) { return _cache_date + pos; }

    inline int32 push_number(posdate pos, int64 val)
    {
        push_number(ptr_cache(pos.bpos), pos.size(), val);
    }

    // 推入时间缓冲区
    inline int32 push_number(dchp first, int32 len, int64 val)
    {
        uint32 vlen = get_number_len(val);
        for(int32 i = 0; i < len - vlen; i++) {
            *first = '0';
            first++;
        }
        get_number_chars(first, vlen, val);
        return len;
    }

    // 以下数字转字符代码参考 std::to_string 函数 C++11 charconv 的实现
    // 计算数字的字符长度
    template <typename T>
    static constexpr uint32 get_number_len(T value, int32 base = 10) noexcept
    {
        uint32 count = 1;
        const uint32 base2 = base * base;
        const uint32 base3 = base2 * base;
        const uint64 base4 = (uint64)base3 * base;
        while(true) {
            if(value < (uint32)base) {
                return count;
            }
            if(value < base2) {
                return count + 1;
            }
            if(value < base3) {
                return count + 2;
            }
            if(value < base4) {
                return count + 3;
            }
            value /= base4;
            count += 4;
        }
    }

    // 数字转字符
    template <typename T>
    static void get_number_chars(dchp first, uint32 len, T val) noexcept
    {
        static constexpr char digits_lut[201] = "0001020304050607080910111213141516171819"
                                                "2021222324252627282930313233343536373839"
                                                "4041424344454647484950515253545556575859"
                                                "6061626364656667686970717273747576777879"
                                                "8081828384858687888990919293949596979899";
        uint32 pos = len - 1;
        while(val >= 100) {
            const auto num = (val % 100) * 2;
            val /= 100;

            first[pos] = digits_lut[num + 1];
            first[pos - 1] = digits_lut[num];
            pos -= 2;
        }
        if(val >= 10) {
            const auto num = val * 2;
            first[1] = digits_lut[num + 1];
            first[0] = digits_lut[num];
        }
        else {
            first[0] = '0' + (char)val;
        }
    }

    // protected:
    int64 _cur_day = 0;
    dchp _cache_date = nullptr;
    record _rec;
};

} // namespace bh

#endif // BTIME_H
