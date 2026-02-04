#ifndef BSTR_H
#define BSTR_H

#include "Bstrbc.h"
#include "Bstrvi.h"

namespace bh {

//
static const uint32 _BH_STR_CAP_MIN_ = (1UL << 8);
static const uint32 _BH_STR_CAP_INT_ = (1UL << 4);

//
class Bstr : public Bstrbc
{
public:
    struct range
    {
        uint64 bpos = 0;
        uint64 epos = 0;
        operator bool() const { return bpos != dstr::npos && epos != dstr::npos; }
    };

public:
    using Bstrbc::Bstrbc;

    Bstr(const Bstr &d) { _data = d._data; }

    //
    inline Bstr &operator=(cstr d)
    {
        _data = d;
        return *this;
    }

    inline Bstr &operator=(const Bstr &d)
    {
        _data = d._data;
        return *this;
    }

    inline Bstr &operator=(const Bstrvi &d)
    {
        _data = Bstr(d.data(), d.size());
        return *this;
    }

    //
    inline Bstr &operator+=(dchr d)
    {
        _data.push_back(d);
        return *this;
    }

    inline Bstr &operator+=(cstr d) { return append_data(d.c_str(), d.size()); }

    inline Bstr &operator+=(const Bstr &d) { return append_data(d.data(), d.size()); }

    inline Bstr &operator+=(const Bstrvi &d) { return append_data(d.data(), d.size()); }

    //
    inline bool operator==(cstr d) { return _data == d; }

    inline bool operator==(const Bstr &d) { return compare(d._data); }

    inline bool operator==(const Bstrvi &d) { return compare_view(d); }

    //
    inline bool compare_view(const Bstrvi &d)
    {
        if(d.size() != _data.size()) {
            return false;
        }
        return std::equal(_data.c_str(), _data.c_str() + _data.size(), d.data());
    }

    //
    inline bool is_contain(cstr sub)
    {
        uint64 index = find_index(sub);
        return index != dstr::npos;
    }

    //
    inline range find_range(cstr sub, uint64 pos = 0)
    {
        range ret;
        uint64 index = find_index(sub, pos);
        ret.bpos = index;
        ret.epos = index + sub.size();
        return ret;
    }

protected:
    //
    inline void try_reserve(uint64 cap)
    {
        if(cap < _BH_STR_CAP_MIN_ && cap >= _BH_STR_CAP_INT_) {
            _data.reserve(_BH_STR_CAP_MIN_);
        }
        else {
            _data.reserve(cap);
        }
    }

    //
    inline Bstr &append_data(cchp d, uint64 len)
    {
        try_reserve(_data.size() + len);
        _data.append(d, len);
        return *this;
    }
};

} // namespace bh

#endif // BSTR_H
