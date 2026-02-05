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
    operator bool() const { return use(); }

    inline bool use() const { return _use; }

    //
    inline T operator*() const { return value(); }

    inline T value() const { return _val; }

protected:
    bool _use;
    T _val;
};

} // namespace bh

#endif // BOPT_H
