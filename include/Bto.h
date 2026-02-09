#ifndef BTO_H
#define BTO_H

#include <sstream>
#include <iomanip>

#include "Bstrvi.h"
#include "Btype.h"
#include "Bopt.h"

namespace bh {

// 字符串转换工具类 提供类型与字符串之间的相互转换
class Bto
{
public:
    struct float_dec
    {
        float_dec(ft64 v, int32 d) : dec(d), val(v) {}
        int32 dec = 0;
        ft64 val = 0.0;
    };

public:
    // 数字转字符
    template <typename T>
    static typename std::enable_if<std::is_arithmetic<T>::value, dstr>::type to_str(const T &val)
    {
        return std::to_string(val);
    }

    template <typename T>
    static typename std::enable_if<!std::is_arithmetic<T>::value, dstr>::type to_str(const T &val)
    {
        return val.to_str();
    }

    // 特殊格式化处理
    inline static dstr to_str(bool val)
    {
        if(val) {
            return "true";
        }
        return "false";
    }

    inline static dstr to_str(char val)
    {
        dstr ret;
        ret += '[';
        ret += val;
        ret += ": ";
        ret += to_str((int32)val);
        ret += ']';
        return ret;
    }

    inline static dstr to_str(cchp val)
    {
        if(val) {
            return val;
        }
        return "NULL";
    }

    inline static dstr to_str(Bstrvi val) { return dstr(val.data(), val.size()); }

    inline static dstr to_str(cstr val) { return val; }

    template <typename T>
    inline static dstr to_str(T *val)
    {
        std::stringstream ss;
        ss << val;
        return ss.str();
    }

    template <typename T1, typename T2>
    inline static dstr to_str(const std::pair<T1, T2> &pair)
    {
        dstr ret;
        ret += '[';
        ret += to_str(pair.first);
        ret += " : ";
        ret += to_str(pair.second);
        ret += ']';
        return ret;
    }

    inline static dstr to_str(float_dec val)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(val.dec) << val.val;
        return ss.str();
    }

    template <typename... T>
    inline static dstr to_str(const std::tuple<T...> &tup)
    {
        dstr ret;
        Bto_tup<std::tuple<T...>, std::tuple_size<std::tuple<T...>>::value, 0>::action(tup, ret);
        return ret;
    }

    // 从字符串安全解析为可选值类型
    template <typename T>
    inline static Bopt<T> from_str_opt(cstr str)
    {
        Bopt<T> ret;
        try {
            if(std::is_same<T, int32>::value) {
                ret = std::stoi(str);
            }
            else if(std::is_same<T, int64>::value) {
                ret = std::stoll(str);
            }
            else if(std::is_same<T, uint32>::value || std::is_same<T, uint64>::value) {
                ret = std::stoull(str);
            }
            else if(std::is_same<T, ft64>::value) {
                ret = std::stod(str);
            }
            else if(std::is_same<T, ft32>::value) {
                ret = std::stof(str);
            }
        }
        catch(...) {
        }
        return ret;
    }

    template <typename T>
    inline static T from_str(cstr str)
    {
        T ret;
        std::istringstream ss(str);
        ss >> ret;
        return ret;
    }

    // 元组字符串解析-中途运行
    template <typename Tclass, uint64 count, uint64 now>
    struct Bto_tup
    {
        static void action(Tclass obj, dstr &str)
        {
            if(now != (count - 1)) {
                auto val = std::get<now>(obj);
                str += to_str(val);
                str += " : ";
            }
            Bto_tup<Tclass, count, now + 1>::action(obj, str);
        }
    };

    // 元组字符串解析-退出模板
    template <typename Tclass, uint64 count>
    struct Bto_tup<Tclass, count, count>
    {
        static void action(Tclass obj, dstr &str)
        {
            if(count != 1) {
                auto val = std::get<count - 1>(obj);
                str += to_str(val);
                str += ']';
            }
        }
    };

    // 元组字符串解析-首次进入
    template <typename Tclass, uint64 count>
    struct Bto_tup<Tclass, count, 0>
    {
        static void action(Tclass obj, dstr &str)
        {
            auto val = std::get<0>(obj);
            if(count != 1) {
                str += '[';
                str += to_str(val);
                str += " : ";
            }
            else {
                str += '[';
                str += to_str(val);
                str += ']';
            }
            Bto_tup<Tclass, count, 1>::action(obj, str);
        }
    };
};

} // namespace bh

#endif // BTO_H
