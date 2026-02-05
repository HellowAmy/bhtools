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

    Bstr(BCstrvi d) { this->assign(d.data(), d.size()); }

    bool operator==(BCstrvi d) const { return compare_view(d); }

    bool operator==(cstr d) const { return compare_view(d); }

    bool operator==(cchp d) const { return compare_view(d); }

    // 
    Bstr &operator<<(BCstrvi d)
    {
        this->append(d.data(), d.size());
        return *this;
    }

    //
    inline bool compare_view(BCstrvi d) const
    {
        if(d.size() != size()) {
            return false;
        }
        return std::equal(c_str(), c_str() + size(), d.data());
    }

    //
    inline bool is_contain(BCstrvi sub)
    {
        uint64 index = find(sub.data(), 0, sub.size());
        return index != dstr::npos;
    }

    //
    inline range find_range(BCstrvi sub, uint64 pos = 0)
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
