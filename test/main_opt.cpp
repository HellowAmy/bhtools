
#include <iostream>

#include "Tlog.h"
#include "Topt.h"
#include "Ftest.h"

using namespace bhtools;
using namespace std;

struct T1
{
    T1() {}
    T1(int i) :_i(i) {}
    T1(const string &s) :_s(s) {}
    T1(int i,const string &s) :_i(i),_s(s) {}
    ~T1()
    {
        vlogw($("T1") $(_i) $(_s));
    }
    int _i = -1;
    string _s;
};


void test_1()
{
    auto w1 = Topt<int>();
    auto w2 = Topt<int>(123456);
    auto w3 = Topt<T1>();
    auto w4 = Topt<T1>(123);
    auto w5 = Topt<T1>("s456");
    auto w6 = Topt<T1>(11,"s22");

    vlogd($(w1.use()) $(w1.value()));
    vlogd($(w2.use()) $(w2.value()));
    vlogd($(w3.use()) $(w3.value()._i) $(w3.value()._s));
    vlogd($(w4.use()) $(w4.value()._i) $(w4.value()._s));
    vlogd($(w5.use()) $(w5.value()._i) $(w5.value()._s));
    vlogd($(w6.use()) $(w6.value()._i) $(w6.value()._s));

    {
        int i1 = sizeof(Topt<int>());
        int i2 = sizeof(Topt<int>(100));
        int i3 = sizeof(int);
        vlogd($(i1) $(i2) $(i3));
    }
    {
        int i1 = sizeof(Topt<T1>());
        int i2 = sizeof(Topt<T1>(200));
        int i3 = sizeof(T1);
        vlogd($(i1) $(i2) $(i3));
    }
}

void test_2()
{
    {
        auto w1 = Topt<int>(123);
        vlogd($(w1.use()) $(w1.value()));

        w1.reset();
        vlogd($(w1.use()) $(w1.value()));

        w1.set(444);
        vlogd($(w1.use()) $(w1.value()));
    }
    {
        auto w5 = Topt<T1>("s456");
        vlogd($(w5.use()) $(w5.value()._i) $(w5.value()._s));

        w5.reset();
        vlogd($(w5.use()) $(w5.value()._i) $(w5.value()._s));

        w5.set("s789");
        vlogd($(w5.use()) $(w5.value()._i) $(w5.value()._s));
    }
}

Topt<T1> Test1(int a)
{   
    if(a == 100)
    {
        return Topt<T1>(5050,"calc");
    }
    else if(a == 1)
    {
        return Topt<T1>(50,"num");
    }
    else 
    {
        return Topt<T1>();
    }
} 


void test_3()
{
    auto fn1 = [](int a,int b) ->Topt<int> {
        if(a > b)
        {
            return Topt<int>(a);
        }
        else 
        {
            return Topt<int>();
        }
    };

    {
        auto t = fn1(10,5);
        if(t.use())
        {
            vlogi($("suc") $(t.value()));
        }
        else 
        {
            vloge($("err"));
        }
    }
    {
        auto t = fn1(10,20);
        if(t.use())
        {
            vlogi($("suc") $(t.value()));
        }
        else 
        {
            vloge($("err"));
        }
    }
    {
        auto t = Test1(100);
        if(t.use())
        {
            vlogi($("suc") $(t.value()._i) $(t.value()._s));
        }
        else 
        {
            vloge($("err"));
        }
    }
    {
        auto t = Test1(1);
        if(t.use())
        {
            vlogi($("suc") $(t.value()._i) $(t.value()._s));
        }
        else 
        {
            vloge($("err"));
        }
    }
    {
        auto t = Test1(50);
        if(t.use())
        {
            vlogi($("suc") $(t.value()._i) $(t.value()._s));
        }
        else 
        {
            vloge($("err"));
        }
    }


}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   

    return 0;
}