#ifndef BANY_H
#define BANY_H

#include <iostream>
#include <typeindex>
#include <memory>

namespace bh {

// 存储任何值-使用无类型指针存储数据
class Bany
{
public:
    // 类型保存-保存的基类指针-用于类型擦除
    struct type_base
    {
        virtual ~type_base() {}
        virtual type_base *get() = 0;
        virtual type_base *copy() = 0;
    };

    // 类型保存-存储具体值得模板类-用于生成指针
    template <typename T>
    struct type_pack : public type_base
    {
        type_pack(const T &val) : _val(val) {}

        // 返回自身
        inline type_base *get() override { return this; }

        // 将值内容分配到指针
        inline type_base *copy() override { return new type_pack<T>(_val); }

        T _val; // 动态保存的值
    };

public:
    Bany() : _type(&typeid(void)) {}

    template <typename T>
    Bany(const T &val)
    {
        if(_val) {
            reset();
        }
        _type = &typeid(T);
        _val = new type_pack<T>(val);
    }

    Bany(const Bany &any)
    {
        if(_val) {
            reset();
        }
        _type = any._type;
        _val = any.copy();
    }

    Bany &operator=(Bany any)
    {
        std::swap(_type, any._type);
        std::swap(_val, any._val);
        return *this;
    }

    ~Bany() { reset(); }

    // 查询使用的类型
    template <typename T>
    bool use()
    {
        return (*_type == typeid(T));
    }

    // 直接返回保存值-需要先查询
    template <typename T>
    const T &value()
    {
        return (static_cast<type_pack<T> *>(_val))->_val;
    }

protected:
    // 重置状态和释放保存值
    void reset()
    {
        _type = &typeid(void);
        if(_val) {
            delete _val;
            _val = nullptr;
        }
    }

    // 用于拷贝构造复制对象保存值
    type_base *copy() const
    {
        if(_val) {
            return _val->copy();
        }
        return nullptr;
    }

protected:
    const std::type_info *_type = nullptr; // 保存值得类型
    type_base *_val = nullptr;             // 保存值的无类型指针
};

} // namespace bh

#endif // BANY_H
