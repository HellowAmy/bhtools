#ifndef BOPT_H
#define BOPT_H

namespace bh {

//
template <typename T>
class Bopt
{
public:
    Bopt() : _use(false) {}

    template <typename... Targ>
    Bopt(Targ &&...arg) : _use(true), _val(std::forward<Targ>(arg)...)
    {
    }

    //
    operator bool() const { return _use; }

    inline const T &operator*() const { return _val; }

    inline const T *operator->() const { return &_val; }

    //
    inline bool use() const { return _use; }

    inline const T &value() const { return _val; }

protected:
    bool _use;
    T _val;
};

template <typename T>
using BCopt = const Bopt<T> &;

} // namespace bh

#endif // BOPT_H
