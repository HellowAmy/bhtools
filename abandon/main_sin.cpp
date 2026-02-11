
#include <iostream>

#include "bhtools.h"

// 继承式单例
class TastA : public bhtools::Tsins<TastA>
{
    BHSIN_SIN(TastA,Tsins)
public:
    void print()
    {
        vlogd("hellow world A");
    }
};

// 外挂式单例
class TastB
{
    BHSIN_SIN(TastB,bhtools::Tsins)
public:
    void print()
    {
        vlogd("hellow world B");
    }
};

// 开放式,非单例,不限制构造函数
class TastC
{
public:
    std::string s = "ID";
    void print()
    {
        vlogd("hellow world C" $(s));
    }
};

void test_1()
{
    // 不可生成构造函数
    TastA::get()->print();

    bhtools::Tsins<TastB>::get()->print();

    // TastA a;
    // a.print();

    // TastB b;
    // b.print();
}

void test_2()
{
    // 生成开放式单例
    bhtools::Tsins<TastC>::get()->print();
    bhtools::Tsins<TastC>::get()->s = "IDSIN S";
    bhtools::Tsins<TastC>::get()->print();

    vlogd("==");

    // 可以生成普通对象
    TastC c;
    c.print();
    c.s = "ID C";
    c.print();

    vlogd("==");

    // 注意Tsins和Tsind版本会单独生成独立对象
    bhtools::Tsind<TastC>::get()->print();
    bhtools::Tsind<TastC>::get()->s = "IDSIN D";
    bhtools::Tsind<TastC>::get()->print();
}

void test_3()
{
    // 测试自动退出
    bhtools::Fexit a([](){
        vlogd("exit func");
    });
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   

    return 0;
}