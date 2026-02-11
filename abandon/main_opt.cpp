
#include <iostream>

#include "bhtools.h"


// 自定义类型的使用
struct T1
{
    T1() {}
    T1(int i) :_i(i) {}
    T1(const std::string &s) :_s(s) {}
    T1(int i,const std::string &s) :_i(i),_s(s) {}
    ~T1()
    {
        vlogw($("T1") $(_i) $(_s));
    }
    int _i = -1;
    std::string _s;
};

void test_1()
{
    // 测试能否生成自定义类型
    auto w1 = bhtools::Topt<int>();
    auto w2 = bhtools::Topt<int>(123456);
    auto w3 = bhtools::Topt<T1>();
    auto w4 = bhtools::Topt<T1>(123);
    auto w5 = bhtools::Topt<T1>("s456");
    auto w6 = bhtools::Topt<T1>(11,"s22");
    auto w7 = bhtools::Topt<std::string>();
    auto w8 = bhtools::Topt<std::string>("sspp");

    vlogd($(w1.use()) $(w1.value()));
    vlogd($(w2.use()) $(w2.value()));
    vlogd($(w3.use()) $(w3.value()._i) $(w3.value()._s));
    vlogd($(w4.use()) $(w4.value()._i) $(w4.value()._s));
    vlogd($(w5.use()) $(w5.value()._i) $(w5.value()._s));
    vlogd($(w6.use()) $(w6.value()._i) $(w6.value()._s));
    vlogd($(w7.use()) $(w7.value()));
    vlogd($(w8.use()) $(w8.value()));

    {
        int i1 = sizeof(bhtools::Topt<int>());
        int i2 = sizeof(bhtools::Topt<int>(100));
        int i3 = sizeof(int);
        vlogd($(i1) $(i2) $(i3));
    }
    {
        int i1 = sizeof(bhtools::Topt<T1>());
        int i2 = sizeof(bhtools::Topt<T1>(200));
        int i3 = sizeof(T1);
        vlogd($(i1) $(i2) $(i3));
    }
}

void test_2()
{
    // 常规使用方式,用于返回值成功判断
    auto fnmax = [](int t1,int t2) -> bhtools::Topt<T1> {
        if(t1 > t2) 
        {
            return bhtools::Topt<T1>(t1,"ss"+std::to_string(t1));
        }
        return bhtools::Topt<T1>();
    };

    bhtools::Topt<T1> op1 = fnmax(100,20);
    bhtools::Topt<T1> op2 = fnmax(100,300);

    vlogd($(op1.use()) $(op1.value()._i) $(op1.value()._s));
    vlogd($(op2.use()) $(op2.value()._i) $(op2.value()._s));

    op1.reset();

    vlogd($(op1.use()) $(op1.value()._i) $(op1.value()._s));
    vlogd($(op2.use()) $(op2.value()._i) $(op2.value()._s));
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   

    return 0;
}