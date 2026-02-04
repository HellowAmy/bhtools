#ifndef BSTRBC_H
#define BSTRBC_H

#include "Btype.h"

namespace bh {

//
class Bstrbc
{
public:
    template <typename... T>
    explicit Bstrbc(T &&...d) : _data(std::forward<T>(d)...)
    {
        std::cout<<"Bstrbc"<<std::endl;
    }

    ~Bstrbc() {}

    inline operator dstr() const { return to_str(); }

    inline dstr to_str() const { return _data; }

    inline cchp data() const { return _data.c_str(); }

    inline uint64 size() const { return _data.size(); }

    inline uint64 capacity() const { return _data.capacity(); }

    template <typename... T>
    inline uint64 find_index(T &&...arg) const
    {
        return _data.find(std::forward<T>(arg)...);
    }

    template <typename... T>
    inline bool compare(T &&...arg) const
    {
        return _data.compare(std::forward<T>(arg)...);
    }

protected:
    dstr _data;
};

} // namespace bh

#endif // BSTRBC_H
