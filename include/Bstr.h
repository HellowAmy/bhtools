#ifndef BSTR_H
#define BSTR_H

#include "Bstrvi.h"

namespace bh {

//
class Bstr : public dstr
{
public:
    struct range
    {
        uint64 bpos = 0;
        uint64 epos = 0;
        operator bool() const { return bpos != dstr::npos && epos != dstr::npos; }
    };

public:
    using dstr::dstr;

    Bstr(cstr d) { this->assign(d); }

    Bstr(Bstrvi d) { this->assign(d.data(), d.size()); }

    //
    bool operator==(Bstrvi d) const { return compare_view(d); }

    bool operator==(cstr d) const { return compare_view(d); }

    bool operator==(cchp d) const { return compare_view(d); }

    //
    inline Bstr &operator<<(Bstrvi d)
    {
        this->append(d.data(), d.size());
        return *this;
    }

    inline Bstr &operator<<(char d)
    {
        this->push_back(d);
        return *this;
    }

    // 临时添加===============
    inline dstr to_str() const { return *this; }

    //
    inline bool compare_view(Bstrvi d) const
    {
        if(d.size() != size()) {
            return false;
        }
        return std::equal(c_str(), c_str() + size(), d.data());
    }

    //
    inline bool is_contain(Bstrvi sub)
    {
        uint64 index = find(sub.data(), 0, sub.size());
        return index != dstr::npos;
    }

    //
    inline range find_range(Bstrvi sub, uint64 pos = 0)
    {
        range ret;
        uint64 index = find(sub.data(), pos, sub.size());
        ret.bpos = index;
        ret.epos = index + sub.size();
        return ret;
    }
};

using BCstr = const Bstr &;

} // namespace bh

#endif // BSTR_H
