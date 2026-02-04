#ifndef BSTRVI_H
#define BSTRVI_H

#include "Btype.h"
#include "Bstrbc.h"

namespace bh {

//
class Bstrvi
{
public:
    explicit Bstrvi() {}

    explicit Bstrvi(cchp d, uint64 size)
    {
        _data = d;
        _size = size;
    }

    explicit Bstrvi(cstr d) : Bstrvi(d.c_str(), d.size()) {}

    explicit Bstrvi(const Bstrbc &d) : Bstrvi(d.data(), d.size()) {}

    explicit Bstrvi(const Bstrbc &d, uint64 pos, uint64 len = 0)
        : Bstrvi(d.data(), d.size(), pos, len)
    {
    }

    explicit Bstrvi(const Bstrvi &d, uint64 pos, uint64 len = 0)
        : Bstrvi(d.data(), d.size(), pos, len)
    {
    }

    explicit Bstrvi(cchp d, uint64 size, uint64 pos, uint64 len = 0)
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

    ~Bstrvi() {}

    inline operator dstr() const { return to_str(); }

    inline dstr to_str() const { return Bstrbc(_data, _size); }

    cchp data() const { return _data; }

    uint64 size() const { return _size; }

protected:
    uint64 _size = 0;
    cchp _data = nullptr;
};

} // namespace bh

#endif // BSTRVI_H
