
#ifndef TDESIGN_H
#define TDESIGN_H

#include <tuple>

namespace bhtools {

    
// 模板职责链-外部接口
template<typename T>
struct Twork_base
{
    virtual bool process(T arg) = 0;
};

//
//
//
//

// 模板职责链-递归添加所有的处理类
template<typename Tobj, typename... Tclass>
struct Twork_chain : public Twork_chain <Tclass...>
{
    // 开始任务-从前往后检查
    template<typename... Targ>
    bool start(Targ&&... arg) 
    { 
        if (_obj.process(std::forward<Targ>(arg)...)) { return true; }
        return Twork_chain<Tclass...>::start(std::forward<Targ>(arg)...);
    }

    Tobj _obj;  // 存储任务处理类对象
};

// 退出模板
template<typename Tobj>
struct Twork_chain<Tobj>
{
    // 最后一个任务-如果无法处理则失败
    template<typename... Targ>
    bool start(Targ&&... arg) 
    { 
        if (_obj.process(std::forward<Targ>(arg)...)) { return true; }
        return false;
    }

    Tobj _obj;  // 存储任务处理类对象
};


} // bhtools

#endif // TDESIGN_H
