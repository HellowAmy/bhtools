#ifndef BBYTE_H
#define BBYTE_H

#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <sstream>

#include "Btype.h"

// 使用 Linux GCC 字节序处理
#ifdef __linux__
#include <endian.h>
#endif

// 检测系统定义的字节序
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 4321
#endif

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif

#ifndef NET_ENDIAN
#define NET_ENDIAN BIG_ENDIAN
#endif

#ifndef BYTE_ORDER
#if defined(__BYTE_ORDER)
#define BYTE_ORDER __BYTE_ORDER
#elif defined(__BYTE_ORDER__)
#define BYTE_ORDER __BYTE_ORDER__
#else
#warning "Err Code Endian"
#endif
#endif

// 定义字节序判断
#ifndef BHEND_IS_BIG
#define BHEND_IS_BIG (BYTE_ORDER == BIG_ENDIAN)
#endif

#ifndef BHEND_IS_LIT
#define BHEND_IS_LIT (BYTE_ORDER == LITTLE_ENDIAN)
#endif

// 查看当前字节序
#if BHEND_IS_BIG
#define BHEND_NOW
#endif

#if BHEND_IS_LIT
#define BHEND_NOW
#endif

namespace bh {

// 字节序操作
class Bendian
{
public:
    // 字节序转换
    template <typename T>
    inline static T swap_endian(T val)
    {
        uint32 len = sizeof(val);
        dstr mem((char *)&val, len);
        for(uint32 i = 0; i < len; i++) {
            if(i >= len / 2) {
                break;
            }
            char tm = mem[i];
            mem[i] = mem[len - i - 1];
            mem[len - i - 1] = tm;
        }
        return *(T *)mem.c_str();
    };

    // 转为主机序-传入为一定是网络大端
    template <typename T>
    inline static T to_host(T val)
    {
#if BHEND_IS_BIG
        return val;
#else
        return swap_endian(val);
#endif
    };

    // 转为网络序-传入不确定
    template <typename T>
    inline static T to_net(T val)
    {
#if BHEND_IS_BIG
        return val;
#else
        return swap_endian(val);
#endif
    };
};

//
//
//
//

// 字节与进制转换
class Bbyte
{
public:
    // 2进制转2进制字符串
    template <typename T>
    inline static dstr b2_s2(T val)
    {
        dstr mem(size_byte(val), '0');
        for(uint32 i = 0; i < mem.size(); i++) {
            if(val & _BH_ONE_LOW_) {
                mem[mem.size() - i - 1] = '1';
            }
            val >>= 1;
        }
        return mem;
    }

    // 2进制转2进制字符串-返回真实的字节序排布
    template <typename T>
    inline static dstr b2_s2_true(T val)
    {
        dstr ret;
        dstr mem((char *)&val, sizeof(val));
        for(uint32 i = 0; i < sizeof(val); i++) {
            ret += b2_s2<char>(mem[i]);
        }
        return ret;
    }

    // 2进制转8进制字符串
    template <typename T>
    inline static dstr b2_s8(T val)
    {
        uint32 count = 0;
        uint32 sum = 0;
        dstr ret;
        for(uint32 i = 0; i < size_byte(val); i++) {
            if(val & _BH_ONE_LOW_) {
                sum += calc_exp(2, count);
            }
            val >>= 1;
            count++;
            if(count == 3) {
                ret += std::to_string(sum);
                count = 0;
                sum = 0;
            }
        }
        ret += std::to_string(sum);
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    // 2进制转16进制字符串
    template <typename T>
    inline static dstr b2_s16(T val)
    {
        uint32 count = 0;
        uint32 sum = 0;
        dstr ret;
        for(uint32 i = 0; i < size_byte(val); i++) {
            if(val & _BH_ONE_LOW_) {
                sum += calc_exp(2, count);
            }
            val >>= 1;
            count++;
            if(count == 4) {
                ret += num_hex(sum);
                count = 0;
                sum = 0;
            }
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    // 2进制转10进制字符串
    template <typename T>
    inline static dstr b2_s10(T val)
    {
        uint32 sum = 0;
        uint32 one = 0;
        for(uint32 i = 0; i < size_byte(val); i++) {
            if(val & _BH_ONE_LOW_) {
                one = 1;
            }
            else {
                one = 0;
            }
            sum += calc_exp(2, i) * one;
            val >>= 1;
        }
        return std::to_string(sum);
    }

    // 2进制字符串转2进制
    template <typename T>
    inline static T s2_b2(cstr s)
    {
        T t = 0;
        for(uint32 i = 0; i < s.size(); i++) {
            t <<= 1;
            if(s[i] == '1') {
                t |= _BH_ONE_LOW_;
            }
        }
        return t;
    }

    // 8进制字符串转2进制
    template <typename T>
    inline static T s8_b2(cstr s)
    {
        T t = 0;
        for(uint32 i = 0; i < s.size(); i++) {
            std::vector<bool> vec = char_oct(s[i]);
            for(uint32 a = vec.size(); a > 0; a--) {
                t <<= 1;
                if(vec[a - 1]) {
                    t |= _BH_ONE_LOW_;
                }
            }
        }
        return t;
    }

    // 10进制字符串转2进制
    template <typename T>
    inline static T s10_b2(cstr s)
    {
        T ret;
        std::istringstream ss(s);
        ss >> ret;
        return ret;
    }

    // 16进制字符串转2进制
    template <typename T>
    inline static T s16_b2(cstr s)
    {
        T t = 0;
        for(uint32 i = 0; i < s.size(); i++) {
            std::vector<bool> vec = char_hex(s[i]);
            for(uint32 a = vec.size(); a > 0; a--) {
                t <<= 1;
                if(vec[a - 1]) {
                    t |= _BH_ONE_LOW_;
                }
            }
        }
        return t;
    }

    // 数字转16进制符号
    inline static char num_hex(uint32 val)
    {
        if(val > 15) {
            return '0';
        }
        if(val <= 9) {
            return val + '0';
        }
        return val = val - 10 + 'a';
    }

    // 16进制符号转数字
    inline static uint32 hex_num(char c)
    {
        if(is_hex_range(c)) {
            if(is_hex_digit(c)) {
                return c - '0';
            }
            else if(is_hex_little(c)) {
                return c - 'a' + 10;
            }
            else if(is_hex_big(c)) {
                return c - 'A' + 10;
            }
        }
        return 0;
    }

    // 8进制符号转数字
    inline static uint32 oct_num(char c)
    {
        if(is_oct_range(c)) {
            return c - '0';
        }
        return 0;
    }

    // 判断为数字
    inline static bool is_hex_digit(char c)
    {
        if((c >= '0' && c <= '9')) {
            return true;
        }
        return false;
    }

    // 判断为小写字母
    inline static bool is_hex_little(char c)
    {
        if(c >= 'a' && c <= 'f') {
            return true;
        }
        return false;
    }

    // 判断为大写字母
    inline static bool is_hex_big(char c)
    {
        if(c >= 'A' && c <= 'F') {
            return true;
        }
        return false;
    }

    // 判断为16进制字符
    inline static bool is_hex_range(char c)
    {
        if(is_hex_digit(c) || is_hex_little(c) || is_hex_big(c)) {
            return true;
        }
        return false;
    }

    // 判断为8进制字符
    inline static bool is_oct_range(char c)
    {
        if((c >= '0' && c <= '7')) {
            return true;
        }
        return false;
    }

    // 转大写-单字符
    inline static char to_upper(char c)
    {
        const int32 w = 'a' - 'A';
        if(c >= 'a' && c <= 'z') {
            c -= w;
        }
        return c;
    }

    // 转小写-单字符
    inline static char to_lower(char c)
    {
        const int32 w = 'a' - 'A';
        if(c >= 'A' && c <= 'Z') {
            c += w;
        }
        return c;
    }

    // 转大写-字符串
    inline static dstr to_upper(cstr s)
    {
        dstr ret(s.size(), '0');
        for(int32 i = 0; i < s.size(); i++) {
            ret[i] = to_upper(s[i]);
        }
        return ret;
    }

    // 转小写-字符串
    inline static dstr to_lower(cstr s)
    {
        dstr ret(s.size(), '0');
        for(int32 i = 0; i < s.size(); i++) {
            ret[i] = to_lower(s[i]);
        }

        return ret;
    }

    // 浮点转整数
    template <typename T>
    inline static auto to_integer(T val) -> typename std::conditional<
        std::is_same<T, ft64>::value, int64,
        typename std::conditional<std::is_same<T, ft32>::value, int32, T>::type>::type
    {
        if(std::is_same<T, ft64>::value) {
            int64 ret = 0;
            std::memcpy(&ret, &val, sizeof(ret));
            return ret;
        }
        else if(std::is_same<T, ft32>::value) {
            int32 ret = 0;
            std::memcpy(&ret, &val, sizeof(ret));
            return ret;
        }
        return val;
    }

    // 返回内存的bit长度
    template <typename T>
    inline static uint32 size_byte(T val)
    {
        return sizeof(val) * 8;
    }

    // 正整数的指数计算
    inline static uint32 calc_exp(uint32 val, uint32 exp)
    {
        if(exp == 0) {
            return 1;
        }
        if(exp == 1) {
            return val;
        }
        uint32 sum = val;
        for(uint32 i = 0; i < exp - 1; i++) {
            sum *= val;
        }
        return sum;
    }

protected:
    // 字节转16进制位数标记
    inline static std::vector<bool> char_hex(char c)
    {
        std::vector<bool> vec{false, false, false, false};
        uint32 num = hex_num(c);
        for(int32 i = 3; i >= 0; i--) {
            uint32 b = calc_exp(2, i);
            if(num >= b) {
                num -= b;
                vec[i] = true;
            }
        }
        return vec;
    }

    // 字节转8进制位数标记
    inline static std::vector<bool> char_oct(char c)
    {
        std::vector<bool> vec{false, false, false};
        uint32 num = oct_num(c);
        for(int32 i = 2; i >= 0; i--) {
            uint32 b = calc_exp(2, i);
            if(num >= b) {
                num -= b;
                vec[i] = true;
            }
        }
        return vec;
    }
};

} // namespace bh

#endif // BBYTE_H
