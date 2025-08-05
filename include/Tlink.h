
#ifndef TLINK_H
#define TLINK_H

#include <iostream>
#include <functional>

namespace bhtools {


// 数据链接视图
template<typename T,template<typename> class Tm>
struct Tvlink
{
    // 绑定通知
    Tvlink(Tm<T> &m) 
    { 
        _m = &m;
        _m->_fn_notify = [this](bool self) {
            if(_fn_data_change) { _fn_data_change(data(),!self); }
        }; 
    }

    // 设置数据
    void set_data(const T &val) 
    { _m->set_data_notify(val,true,false); }

    // 设置数据-不通知
    void set_data_nonotify(const T &val) 
    { _m->set_data_notify(val,false,false); }

    // 设置数据改变回调
    void set_change_cb(std::function<void(T,bool)> _fn = nullptr)
    { _fn_data_change = _fn; }

    // 返回数据
    T data() { return _m->data(); }

    // internal
    std::function<void(T,bool)> _fn_data_change = nullptr;  // 数据更改通知-外部回调

    Tm<T> *_m = nullptr;   // 模型指针
};


// 数据链接模型
template<typename T>
struct Tmlink
{
    Tmlink(const T &val) { set_data_notify(val); }

    // 设置数据
    void set_data(const T &val) { set_data_notify(val); }

    // 设置数据-不通知
    void set_data_nonotify(const T &val) 
    { set_data_notify(val,false,true); }

    // 返回数据
    T& data() { return _data; }

    // 更新数据并通知视图
    void set_data_notify(T &&val,bool notify = true,bool self = true)
    {
        _data = std::forward<T>(std::move(val));
        if(notify && _fn_data_change) { _fn_data_change(val,self); }
        if(notify && _fn_notify) { _fn_notify(self); }
    }

    std::function<void(bool)> _fn_notify = nullptr;         // 通知函数-内部回调
    std::function<void(T,bool)> _fn_data_change = nullptr;  // 数据更改通知-外部回调

    T _data;    // 存储源数据
};


} // bhtools

#endif // TLINK_H
