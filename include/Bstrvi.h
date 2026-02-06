#ifndef BSTRVI_H
#define BSTRVI_H

#include <cstring>
#include <string>

#include "Btype.h"

namespace bh {

// 字符串视图类 类似于 string_view 提供非所有权的字符串操作
class Bstrvi
{
public:
    Bstrvi() {}

    Bstrvi(const Bstrvi &d, uint64 pos, uint64 len = 0) : Bstrvi(d.data(), d.size(), pos, len) {}

    Bstrvi(cstr d, uint64 pos = 0, uint64 len = 0) : Bstrvi(d.c_str(), d.size(), pos, len) {}

    Bstrvi(cchp d, uint64 pos = 0, uint64 len = 0) : Bstrvi(d, strlen(d), pos, len) {}

    Bstrvi(cchp d, uint64 size, uint64 pos, uint64 len)
    {
        _data = d + pos;
        if(len == 0) {
            _size = size - pos;
        }
        else {
            _size = len;
        }
    }

    Bstrvi(const Bstrvi &d)
    {
        _data = d._data;
        _size = d._size;
    }

    Bstrvi &operator=(const Bstrvi &d)
    {
        _data = d._data;
        _size = d._size;
        return *this;
    }

    char operator[](uint64 index) const { return _data[index]; }

    bool operator==(const Bstrvi &d) const
    {
        if(_size != d._size) {
            return false;
        }
        return std::equal(_data, _data + _size, d._data);
    }

    ~Bstrvi() {}

    inline dstr to_str() const { return dstr(_data, _size); }

    inline cchp data() const { return _data; }

    inline uint64 size() const { return _size; }

    // 移动数据指针
    inline Bstrvi &move(int32 pos)
    {
        if(_data) {
            _data += pos;
        }
        return *this;
    }

    // 移动头部指针并缩减长度
    inline Bstrvi &move_head(int32 pos)
    {
        if(_data) {
            _data += pos;
            _size -= pos;
        }
        return *this;
    }

    // 调整尾部长度
    inline Bstrvi &move_tail(int32 pos)
    {
        if(_data) {
            _size += pos;
        }
        return *this;
    }

    // 该函数实现逻辑为仿写 std::string find 函数
    // 查找子串函数
    inline uint64 find(cchp s, uint64 pos, uint64 n) const
    {
        // 特殊情况处理-如果待找子串长度为 0
        if(n == 0) {
            return pos <= _size ? pos : dstr::npos;
        }

        // 如果起始查找位置已超出当前字符串长度-肯定找不到
        if(pos >= _size) {
            return dstr::npos;
        }

        // 优化策略-先缓存子串的第一个字符
        const char c1 = s[0];
        cchp first = _data + pos;
        cchp last = _data + _size;
        uint64 len = _size - pos;

        // 循环匹配首字符并校验全文
        while(len >= n) {
            first = std::char_traits<char>::find(first, len - n + 1, c1);

            if(!first) {
                return dstr::npos;
            }

            // 比较内存块内容
            if(std::char_traits<char>::compare(first, s, n) == 0) {
                return first - _data;
            }
            first++;
            len = last - first;
        }
        return dstr::npos;
    }

    inline uint64 find(Bstrvi d, uint64 pos) const { return find(d.data(), pos, d.size()); }

    // 仿写 std::string rfind
    // 反向查找子串函数
    inline uint64 rfind(cchp s, uint64 pos, uint64 n) const
    {
        if(n <= _size && pos <= _size) {
            // 尾部对齐-从头开始对比
            pos = std::min(uint64(_size - n), pos);
            do {
                if(std::char_traits<char>::compare(_data + pos, s, n) == 0) {
                    return pos;
                }
            } while(pos-- > 0);
        }
        return dstr::npos;
    }

    inline uint64 rfind(Bstrvi d, uint64 pos) const { return rfind(d.data(), pos, d.size()); }

protected:
    uint64 _size = 0;
    cchp _data = nullptr;
};

} // namespace bh

#endif // BSTRVI_H