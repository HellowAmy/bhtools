#ifndef BSIN_H
#define BSIN_H

#include <mutex>
#include <functional>

namespace bh {

// RAII机制-退出时触发
class Bexit
{
public:
    // 构造时获取退出函数
    Bexit(std::function<void()> fn) : _fn(std::move(fn)) {}

    // 析造时执行退出函数
    ~Bexit()
    {
        if(_fn) {
            _fn();
        }
    }

protected:
    Bexit(const Bexit &) = delete;
    Bexit &operator=(const Bexit &) = delete;

protected:
    std::function<void()> _fn = nullptr;
};

//
//
//
//

// 静态单例模板
// 子类需要继承单例模板-否则需要手动调用析构
template <typename T>
class Bsins
{
public:
    // 返回对象
    static T *get()
    {
        static Bexit exit([]() {
            delete _obj;
        });
        return _obj;
    }

protected:
    static T *_obj;                // 静态对象指针
    friend T;                      // 设置友元
    Bsins(const Bsins &) = delete; // 删除复制
    Bsins(Bsins &&) = delete;      // 删除复制
    Bsins() = default;             // 声明构造
    virtual ~Bsins() = default;    // 声明析构
};

//
//
//
//

// 动态单例模板-使用时生成-支持解除对象
template <typename T>
class Bsind
{
public:
    // 创建并返回对象-支持多线程获取
    static T *get()
    {
        if(_obj == nullptr) {
            _mut.lock();
            if(_obj == nullptr) {
                _obj = new T;

                static Bexit exit([]() {
                    delete _obj;
                });
            }
            _mut.unlock();
        }
        return _obj;
    }

    // 清除对象
    void clean()
    {
        if(_obj) {
            _mut.lock();
            delete _obj;
            _obj = nullptr;
            _mut.unlock();
        }
    }

protected:
    static std::mutex _mut;        // 多线程锁
    static T *_obj;                // 静态对象指针
    friend T;                      // 设置友元
    Bsind(const Bsind &) = delete; // 删除复制
    Bsind(Bsind &&) = delete;      // 删除复制
    Bsind() = default;             // 声明构造
    virtual ~Bsind() = default;    // 声明析构
};

// 静态变量外部声明
template <typename T>
T *Bsins<T>::_obj = new T;

template <typename T>
T *Bsind<T>::_obj = nullptr;

template <typename T>
std::mutex Bsind<T>::_mut;

//
//
//
//

// 单例模板限制宏-在需要生成单例模板时声明
#define BHSIN_SIN(class, single)                                                                   \
protected:                                                                                         \
    friend single<class>;                                                                          \
    class() = default;                                                                             \
    virtual ~class() = default;                                                                    \
    class(const class &) = delete;                                                                 \
    class(class &&) = delete;                                                                      \
                                                                                                   \
private:

} // namespace bh

#endif // BSIN_H
