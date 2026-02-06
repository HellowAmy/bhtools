#ifndef BOPT_H
#define BOPT_H

namespace bh {

// 可选值类 用于表示可能存在也可能为空的值
template <typename T>
class Bopt
{
public:
    Bopt() : _use(false) {}

    template <typename... Targ>
    Bopt(Targ &&...arg) : _use(true), _val(std::forward<Targ>(arg)...)
    {
    }

    // 类型转换操作符 检查值是否存在
    operator bool() const { return _use; }

    inline const T &operator*() const { return _val; }

    inline const T *operator->() const { return &_val; }

    // 获取是否存在标志
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