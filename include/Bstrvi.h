#ifndef BSTRVI_H
#define BSTRVI_H

#include <cstring>

#include "Btype.h"

namespace bh {

//
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

    bool operator==(const Bstrvi &d) const
    {
        if(_size != d._size) {
            return false;
        }
        return std::equal(_data, _data + _size, d._data);
    }

    ~Bstrvi() {}

    dstr to_str() const { return dstr(_data, _size); }

    cchp data() const { return _data; }

    uint64 size() const { return _size; }

    Bstrvi &move(int32 pos)
    {
        if(_data) {
            _data += pos;
        }
        return *this;
    }

    Bstrvi &move_head(int32 pos)
    {
        if(_data) {
            _data += pos;
            _size -= pos;
        }
        return *this;
    }

    Bstrvi &move_tail(int32 pos)
    {
        if(_data) {
            _size += pos;
        }
        return *this;
    }

protected:
    uint64 _size = 0;
    cchp _data = nullptr;
};

} // namespace bh

#endif // BSTRVI_H
