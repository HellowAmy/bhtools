#ifndef BDESIGN_H
#define BDESIGN_H

#include <tuple>

namespace bh {

// 模板职责链-外部接口
template <typename T>
struct Bwork_base
{
    virtual bool process(T arg) = 0;
};

//
//
//
//

// 模板职责链-递归添加所有的处理类
template <typename Tobj, typename... Tclass>
struct Bwork_chain : public Bwork_chain<Tclass...>
{
    // 开始任务-从前往后检查
    template <typename... Targ>
    bool start(Targ &&...arg)
    {
        if(_obj.process(std::forward<Targ>(arg)...)) {
            return true;
        }
        return Bwork_chain<Tclass...>::start(std::forward<Targ>(arg)...);
    }

    Tobj _obj; // 存储任务处理类对象
};

// 退出模板
template <typename Tobj>
struct Bwork_chain<Tobj>
{
    // 最后一个任务-如果无法处理则失败
    template <typename... Targ>
    bool start(Targ &&...arg)
    {
        if(_obj.process(std::forward<Targ>(arg)...)) {
            return true;
        }
        return false;
    }

    Tobj _obj; // 存储任务处理类对象
};

} // namespace bh

#endif // BDESIGN_H
