#ifndef BBUF_H
#define BBUF_H

#include <cstring>

#include "Btype.h"
#include "Bview.h"

namespace bh {

// 动态字符串-不维护末尾字符
class Bbuf
{
public:
    Bbuf()
    {
        _cap = _BH_INT_64_;
        reset_data(_cap);
    }

    Bbuf(Bview d) : Bbuf(d.data(), d.size()) {}

    Bbuf(cstr d) : Bbuf(d.c_str(), d.size()) {}

    Bbuf(cchp d) : Bbuf(d, strlen(d)) {}

    Bbuf(cchp data, uint64 len)
    {
        reserve(len);
        push_data(data, len);
    }

    Bbuf(uint64 cap) { reserve(cap); }

    ~Bbuf()
    {
        delete_data(_data);
        _size = 0;
        _cap = 0;
    }

    Bbuf(const Bbuf &d)
    {
        _cap = d._cap;
        _size = d._size;
        _data = new_data(_cap);
        memcpy(_data, d._data, _size);
    }

    Bbuf &operator=(Bbuf d)
    {
        swap(d);
        return *this;
    }

    inline Bbuf &operator+=(Bbuf d)
    {
        push_data(d._data, d._size);
        return *this;
    }

    inline Bbuf &operator+=(Bview d)
    {
        push_data(d.data(), d.size());
        return *this;
    }

    inline Bbuf &operator+=(cstr d)
    {
        push_data(d.c_str(), d.size());
        return *this;
    }

    inline Bbuf &operator+=(cchp d)
    {
        push_data(d, strlen(d));
        return *this;
    }

    inline char &operator[](uint64 index) { return _data[index]; }

    inline void append(cchp data, uint64 len) { push_data(data, len); }

    inline void swap(Bbuf &d)
    {
        std::swap(_cap, d._cap);
        std::swap(_size, d._size);
        std::swap(_data, d._data);
    }

    inline void reserve(uint64 cap)
    {
        if(_cap < cap) {
            reset_data(cap);
        }
    }

    inline void resize(uint64 size) { _size = size; }

    inline void clear() { _size = 0; }

    inline bool empty() const { return _size == 0; }

    inline uint64 capacity() const { return _cap; }

    inline uint64 size() const { return _size; }

    inline dchp data() const { return _data; }

    inline dstr to_str() const { return dstr(_data, _size); }

    inline Bview to_view() const { return Bview(_data, _size, 0, 0); }

protected:
    // 分配空间
    inline void delete_data(dchp data)
    {
        delete[] data;
        data = nullptr;
    }

    // 销毁数据
    inline dchp new_data(uint64 len)
    {
        dchp p = new char[len];
        memset(p, 0, len);
        return p;
    }

    // 扩展空间
    inline void reset_data(uint64 len)
    {
        dchp old = _data;
        _data = new_data(len);
        _cap = len;

        if(old) {
            memcpy(_data, old, _size);
            delete_data(old);
        }
    }

    // 是否需要扩展空间
    inline void try_resize(uint64 len)
    {
        if(len > _cap) {
            uint64 cap = _cap * 2;
            while(cap < len) {
                cap *= 2;
            }
            reset_data(cap);
        }
    }

    // 追加数据
    inline void push_data(cchp data, uint64 len)
    {
        try_resize(_size + len);
        memcpy(_data + _size, data, len);
        _size += len;
    }

protected:
    uint64 _cap = 0;
    uint64 _size = 0;
    dchp _data = nullptr;
};

using BCbuf = const Bbuf &;

} // namespace bh

#endif // BBUF_H
