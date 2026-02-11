
#include <iostream>
#include <optional>

#include "bhtools.h"


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
    // 测试类型有效
    int a1 = 123;
    short a2 = 456;
    size_t a3 = 789;
    const char *a4 = "hellow";
    std::string a5 = "world";
    bool a6 = true;
    char a7 = 'k';
    float a8 = 123.456;
    double a9 = 666.666;

    {
        bhtools::Tany any;
        vlogw($("null"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a1);
        vlogw($(a1));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a2);
        vlogw($(a2));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a3);
        vlogw($(a3));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a4);
        vlogw($(a4));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a5);
        vlogw($(a5));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a6);
        vlogw($(a6));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a7);
        vlogw($(a7));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a8);
        vlogw($(a8));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(a9);
        vlogw($(a9));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }

}


void test_2()
{
    // 测试具体类型
    {
        bhtools::Tany any;
        vlogw($("void"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(1234);
        vlogw($("int"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(1234L);
        vlogw($("long"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<long>()));
        vlogd($(any.use<long long>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(1234LL);
        vlogw($("long long"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<long>()));
        vlogd($(any.use<long long>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(1234UL);
        vlogw($("size_t"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<long>()));
        vlogd($(any.use<long long>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(123.456);
        vlogw($("double"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(123.456f);
        vlogw($("float"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any("hellow");
        vlogw($("const char *"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(std::string("hellow"));
        vlogw($("string"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any(true);
        vlogw($("bool"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }
    {
        bhtools::Tany any('k');
        vlogw($("char"));
        vlogd($(any.use<void>()));
        vlogd($(any.use<int>()));
        vlogd($(any.use<short>()));
        vlogd($(any.use<size_t>()));
        vlogd($(any.use<const char *>()));
        vlogd($(any.use<std::string>()));
        vlogd($(any.use<bool>()));
        vlogd($(any.use<char>()));
        vlogd($(any.use<float>()));
        vlogd($(any.use<double>()));
    }

}

void test_3()
{
    // 获取值
    int a1 = 123;
    short a2 = 456;
    size_t a3 = 789;
    const char *a4 = "hellow";
    std::string a5 = "world";
    bool a6 = true;
    char a7 = 'k';
    float a8 = 123.456;
    double a9 = 666.666;

    {
        bhtools::Tany any(a1);
        vlogd($(any.use<int>()) $(any.value<int>()));
    }
    {
        bhtools::Tany any(a2);
        vlogd($(any.use<short>()) $(any.value<short>()));
    }
    {
        bhtools::Tany any(a3);
        vlogd($(any.use<size_t>()) $(any.value<size_t>()));
    }
    {
        bhtools::Tany any(a4);
        vlogd($(any.use<const char *>()) $(any.value<const char *>()));
    }
    {
        bhtools::Tany any(a5);
        vlogd($(any.use<std::string>()) $(any.value<std::string>()));
    }
    {
        bhtools::Tany any(a6);
        vlogd($(any.use<bool>()) $(any.value<bool>()));
    }
    {
        bhtools::Tany any(a7);
        vlogd($(any.use<char>()) $(any.value<char>()));
    }
    {
        bhtools::Tany any(a8);
        vlogd($(any.use<float>()) $(any.value<float>()));
    }
    {
        bhtools::Tany any(a9);
        vlogd($(any.use<double>()) $(any.value<double>()));
    }



    {
        bhtools::Tany any(12344);
        vlogd($(any.use<int>()) $(any.value<int>()));
    }
    {
        bhtools::Tany any(66.666);
        vlogd($(any.use<double>()) $(any.value<double>()));
    }
    {
        bhtools::Tany any("hellow1");
        vlogd($(any.use<const char *>()) $(any.value<const char *>()));
    }
    {
        bhtools::Tany any(std::string("hellow2"));
        vlogd($(any.use<std::string>()) $(any.value<std::string>()));
    }

}

void test_4()
{
    // 指针转移和释放
    {
        T1 a1(999,"T1v");
        bhtools::Tany any1(a1);
        vlogd($(any1.use<T1>()) $(any1.value<T1>()._i) $(any1.value<T1>()._s));

        bhtools::Tany any2(any1);
        vlogd($(any2.use<T1>()) $(any2.value<T1>()._i) $(any2.value<T1>()._s));

        bhtools::Tany any3 = a1;
        vlogd($(any3.use<T1>()) $(any3.value<T1>()._i) $(any3.value<T1>()._s));

        bhtools::Tany any4 = any1;
        vlogd($(any4.use<T1>()) $(any4.value<T1>()._i) $(any4.value<T1>()._s));

        bhtools::Tany any5(T1(9999,"T1vv"));
        vlogd($(any5.use<T1>()) $(any5.value<T1>()._i) $(any5.value<T1>()._s));
    }

    // 拷贝复制
    {
        bhtools::Tany any1 = 123;
        bhtools::Tany any2(456);

        vlogd($(any1.use<int>()) $(any1.value<int>()));
        vlogd($(any2.use<int>()) $(any2.value<int>()));

        bhtools::Tany any3 = any1;
        vlogd($(any3.use<int>()) $(any3.value<int>()));

        any3 = any2;
        vlogd($(any3.use<int>()) $(any3.value<int>()));
    }
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   
    test_4();   

    return 0;
}