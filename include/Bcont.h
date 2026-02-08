#ifndef BCONT_H
#define BCONT_H

#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <atomic>
#include <mutex>
#include <functional>

namespace bh {

// 自旋锁
class Bspinlock
{
public:
    // 上锁-循环获取标记直到成功
    void lock()
    {
        while(_flg.test_and_set(std::memory_order_acquire)) {}
    }

    // 解锁-清空标记
    void unlock() { _flg.clear(std::memory_order_release); }

protected:
    std::atomic_flag _flg = ATOMIC_FLAG_INIT; // 原子互斥标记
};

//
//
//
//

// 析构退出-自动退出上锁状态
template <typename Tlock>
class Bexit_lock
{
public:
    // 构造时上锁
    Bexit_lock(Tlock *lock)
    {
        _lock = lock;
        if(_lock) {
            _lock->lock();
        }
    }

    // 析构时解锁
    ~Bexit_lock()
    {
        if(_lock) {
            _lock->unlock();
        }
    }

protected:
    Tlock *_lock; // 上锁指针-避免不能赋值的情况
};

//
//
//
//

// 队列-线程安全
template <typename T, typename Tlock = Bspinlock>
class Bqueue
{
public:
    size_t size()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.size();
    }
    size_t empty()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.empty();
    }
    void pop()
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.pop();
    }
    void push(const T &val)
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.push(val);
    }
    T front()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.front();
    }
    T back()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.back();
    }

    T pop_front()
    {
        Bexit_lock<Tlock> e(&_lock);
        T val = _org.front();
        _org.pop();
        return val;
    }

    // 锁下操作源数据
    void safe(std::function<void(std::queue<T> &)> fn)
    {
        Bexit_lock<Tlock> e(&_lock);
        if(fn) {
            fn(_org);
        };
    }

protected:
    Tlock _lock;        // 上锁对象
    std::queue<T> _org; // 原始数据
};

//
//
//
//

// 堆栈-线程安全
template <typename T, typename Tlock = Bspinlock>
class Bstack
{
public:
    size_t size()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.size();
    }
    size_t empty()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.empty();
    }
    void pop()
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.pop();
    }
    void push(const T &val)
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.push(val);
    }
    T top()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.top();
    }

    T pop_top()
    {
        Bexit_lock<Tlock> e(&_lock);
        T val = _org.top();
        _org.pop();
        return val;
    }

    // 锁下操作源数据
    void safe(std::function<void(std::stack<T> &)> fn)
    {
        Bexit_lock<Tlock> e(&_lock);
        if(fn) {
            fn(_org);
        };
    }

protected:
    Tlock _lock;        // 上锁对象
    std::stack<T> _org; // 原始数据
};

//
//
//
//

// 数组-线程安全-迭代器不安全
template <typename T, typename Tlock = Bspinlock>
class Bvector
{
public:
    typedef typename std::vector<T>::iterator iterator;

public:
    void clear()
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.clear();
    }
    size_t size()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.size();
    }
    size_t empty()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.empty();
    }
    iterator begin()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.begin();
    }
    iterator end()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.end();
    }
    void pop_back()
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.pop_back();
    }
    void push_back(const T &val)
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.push_back(val);
    };

    iterator insert(iterator pos, const T &val)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.insert(pos, val);
    }

    iterator erase(iterator pos)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.erase(pos);
    }

    T &operator[](size_t index)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org[index];
    }

    // 锁下操作源数据
    void safe(std::function<void(std::vector<T> &)> fn)
    {
        Bexit_lock<Tlock> e(&_lock);
        if(fn) {
            fn(_org);
        };
    }

protected:
    Tlock _lock;         // 上锁对象
    std::vector<T> _org; // 原始数据
};

//
//
//
//

// 索引-线程安全-迭代器不安全
template <typename Tkey, typename Tval, typename Tlock = Bspinlock>
class Bmap
{
public:
    typedef typename std::map<Tkey, Tval>::iterator iterator;

public:
    void clear()
    {
        Bexit_lock<Tlock> e(&_lock);
        _org.clear();
    }
    size_t size()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.size();
    }
    size_t empty()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.empty();
    }
    iterator begin()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.begin();
    }
    iterator end()
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.end();
    }

    std::pair<iterator, bool> insert(std::pair<Tkey, Tval> val)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.insert(val);
    }

    iterator erase(iterator it)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.erase(it);
    }

    iterator find(const Tkey &val)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.find(val);
    }

    template <class... Args>
    std::pair<iterator, bool> emplace(Args &&...args)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org.emplace(args...);
    }

    Tval &operator[](const Tkey &key)
    {
        Bexit_lock<Tlock> e(&_lock);
        return _org[key];
    }

    // 锁下操作源数据
    void safe(std::function<void(std::map<Tkey, Tval> &)> fn)
    {
        Bexit_lock<Tlock> e(&_lock);
        if(fn) {
            fn(_org);
        };
    }

protected:
    Tlock _lock;               // 上锁对象
    std::map<Tkey, Tval> _org; // 原始数据
};

} // namespace bh

#endif // BCONT_H
