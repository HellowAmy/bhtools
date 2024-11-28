
#include <iostream>
#include <optional>

#include "Tlog.h"
#include "Tany.h"
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
    {
        Tany any;
        vlogd($(any._type.name()));
        vlogd($(any.use<void>()));
    }
    {
        Tany any(123);
        vlogd($(any.use<int>()));
        vlogd($(any._type.name()));

        if(any.use<int>())
        {
            auto s = any.value<int>();
            vlogd($(s));
        }
    }
    {
        Tany any(123.456);
        vlogd($(any._type.name()));
        vlogd($(any.value<double>()));
    }
    {
        Tany any("hellow");
        vlogd($(any._type.name()));
        vlogd($(any.value<std::string>()));
    }
    {
        Tany any(T1(123));
        vlogd($(any._type.name()));
        vlogd($(any.value<T1>()._i) $(any.value<T1>()._s));
    }
    {
        Tany any(T1(100,"hhq"));
        vlogd($(any._type.name()));
        vlogd($(any.value<T1>()._i) $(any.value<T1>()._s));
    }
    {
        Tany any1(123);
        Tany any2("swq");
        vlogd($(any1._type.name()) $(any2._type.name()) );
        vlogd( $(any1.value<int>()) $(any2.value<std::string>()) );

        Tany any3(any1);
        Tany any4(std::move(any2));

        vlogd($(any1._type.name()) $(any2._type.name()) $(any3._type.name()) $(any4._type.name()));
        vlogd( $(any1.value<int>()) $(any2.value<std::string>()) $(any3.value<int>()) $(any4.value<std::string>()));
    }
    {
        Tany any1(123);
        Tany any2("swq");
        Tany any3 = any1;
        Tany any4;

        vlogd($(any1._type.name()) $(any2._type.name()) $(any3._type.name()) $(any4._type.name()));
        
        any4 = any2;

        vlogd($(any1._type.name()) $(any2._type.name()) $(any3._type.name()) $(any4._type.name()));

        vlogd( $(any1.value<int>()) $(any2.value<std::string>()) $(any3.value<int>()) $(any4.value<std::string>()));
    }
}

void test_2()
{

}

void test_3()
{

}

int main(int argc, char *argv[])
{
    test_1();   
    // test_2();   
    // test_3();   

    return 0;
}