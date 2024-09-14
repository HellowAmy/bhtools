
#ifndef TDESIGN_H
#define TDESIGN_H

#include <tuple>


namespace bhtools {


// 执行模板职责链判断函数-如果选择继续执行则职责链不会停止
template<typename Tclass,size_t now>
struct Twork_action
{
    // 执行类对象的next判断函数-如果为真则代表继续处理
    template<typename ...Targ>
    static bool action(Tclass obj,Targ ...arg) 
    {
        auto it = std::get<now -1>(obj);
        if(it.next(arg...)) { return Twork_action<Tclass,now -1>::action(obj,arg...); }
        return true;
    }
};
 
// 退出模板职责链
template<typename Tclass>
struct Twork_action<Tclass,0>
{
    template<typename ...Targ>
    static bool action(Tclass obj,Targ ...arg) { return false; }
};
 
// 模板职责链-可以通过实现鸭子函数来顺序处理函数
template<typename ...Tclass>
struct Twork_chain
{
    // 开始执行职责链-传入具体处理函数的参数-处理顺序为函数对象的倒序执行-确保第一个执行的函数放在最后
    // 返回值 [true: 职责被接收]-[false: 未找到处理函数]
    template<typename ...Targ>
    bool start(Targ ...arg)
    { 
        return Twork_action<
                std::tuple<Tclass...>,
                std::tuple_size<std::tuple<Tclass...>>::value
            >::action(_objs,arg...); 
    }

    std::tuple<Tclass...> _objs;    // 存储类对象模板-非类指针而是类本身
};

//
//
//
//



} // bhtools



#endif // TDESIGN_H
