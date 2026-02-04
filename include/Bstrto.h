#ifndef BSTRTO_H
#define BSTRTO_H

#include <sstream>
#include <iomanip>

#include "Topt.h"

#include "Bstr.h"

namespace bh {

class Bstrto
{
public:
    struct float_dec
    {
        float_dec(ft64 v, int32 d) : dec(d), val(v) {}
        int32 dec = 0;
        ;
        ft64 val = 0.0;
    };

public:
    //
    template <typename T>
    static typename std::enable_if<std::is_arithmetic<T>::value, Bstr>::type to_str(const T &val)
    {
        return Bstr(std::move(std::to_string(val)));
    }

    template <typename T>
    static typename std::enable_if<!std::is_arithmetic<T>::value, Bstr>::type to_str(const T &val)
    {
        return val;
    }

    //
    inline static Bstr to_str(bool val)
    {
        if(val) {
            return Bstr("true");
        }
        return Bstr("false");
    }

    inline static Bstr to_str(dchr val)
    {
        Bstr ret;
        std::string ret = "['";
        ret += val;
        ret += "': ";
        ret += to_str((int)val);
        ret += "]";
        return ret;
    }

    inline static Bstr to_str(cchp val)
    {
        if(val) {
            return Bstr(val);
        }
        return Bstr("NULL");
    }

    inline static Bstr to_str(cstr val) { return Bstr(val); }

    template <typename T>
    inline static Bstr to_str(T *val)
    {
        std::stringstream ss;
        ss << val;
        return Bstr(std::move(ss.str()));
    }

    template <typename T1, typename T2>
    inline static Bstr to_str(const std::pair<T1, T2> &pair)
    {
        Bstr ret;
        ret = "[";
        ret += to_str(pair.first);
        ret += " : ";
        ret += to_str(pair.second);
        ret += "]";
        return ret;
    }

    inline static Bstr to_str(float_dec val)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(val.dec) << val.val;
        return Bstr(std::move(ss.str()));
    }

    template <typename... T>
    inline static Bstr to_str(const std::tuple<T...> &tup)
    {
        Bstr ret;
        Bstrto_tup<std::tuple<T...>, std::tuple_size<std::tuple<T...>>::value, 0>::action(tup, ret);
        return ret;
    }

    //
    template <typename T>
    inline static bhtools::Topt<T> from_string(cstr str)
    {
        bhtools::Topt<T> ret;
        try {
            if(std::is_same<T, ft64>::value) {
                ret = std::stod(str);
            }
            else if(std::is_same<T, ft32>::value) {
                ret = std::stof(str);
            }
            else if(std::is_same<T, int32>::value || std::is_same<T, uint32>::value) {
                ret = std::stoi(str);
            }
            else if(std::is_same<T, int64>::value || std::is_same<T, uint64>::value) {
                ret = std::stoll(str);
            }
        }
        catch(...) {
        }
        return ret;
    }

    template <typename T>
    inline static T from_string(cstr str)
    {
        T ret;
        std::istringstream ss(str);
        ss >> ret;
        return ret;
    }

    // 元组字符串解析-中途运行
    template <typename Tclass, size_t count, size_t now>
    struct Bstrto_tup
    {
        static void action(Tclass obj, Bstr &str)
        {
            if(now != (count - 1)) {
                auto val = std::get<now>(obj);
                str += to_str(val);
                str += " : ";
            }
            Bstrto_tup<Tclass, count, now + 1>::action(obj, str);
        }
    };

    // 元组字符串解析-退出模板
    template <typename Tclass, size_t count>
    struct Bstrto_tup<Tclass, count, count>
    {
        static void action(Tclass obj, Bstr &str)
        {
            if(count != 1) {
                auto val = std::get<count - 1>(obj);
                str += to_str(val);
                str += "] ";
            }
        }
    };

    // 元组字符串解析-首次进入
    template <typename Tclass, size_t count>
    struct Bstrto_tup<Tclass, count, 0>
    {
        static void action(Tclass obj, Bstr &str)
        {
            auto val = std::get<0>(obj);
            if(count != 1) {
                str += "[";
                str += to_str(val);
                str += " : ";
            }
            else {
                str += "[";
                str += to_str(val);
                str += "] ";
            }
            Bstrto_tup<Tclass, count, 1>::action(obj, str);
        }
    };
};

} // namespace bh

#endif // BSTRTO_H
