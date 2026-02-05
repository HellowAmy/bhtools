#include <iostream>

#include "Bsin.h"
#include "Bstr.h"

#include "Ftest.h"

// 继承式单例
class TastA : public bh::Bsins<TastA>
{
    BHSIN_SIN(TastA, Bsins)
public:
    void print() { vlogd("hellow world A"); }
};

// 外挂式单例
class TastB
{
    BHSIN_SIN(TastB, bh::Bsins)
public:
    void print() { vlogd("hellow world B "); }
};

// 开放式-非单例-不限制构造函数
class TastC
{
public:
    std::string s = "ID";
    void print() { vlogd("hellow world C" $(s)); }
};

void test_1()
{
    vloga("单例访问");
    TastA::get()->print();
    bh::Bsins<TastB>::get()->print();
}

void test_2()
{
    vloga("开放式静态单例");
    bh::Bsins<TastC>::get()->print();
    bh::Bsins<TastC>::get()->s = "IDSIN S";
    bh::Bsins<TastC>::get()->print();

    vloga("新增动态单例");
    bh::Bsind<TastC>::get()->print();
    bh::Bsind<TastC>::get()->s = "IDSIN D";
    bh::Bsind<TastC>::get()->print();

    vloga("新增对象");
    TastC c;
    c.print();
    c.s = "ID C";
    c.print();
}

void test_3()
{
    vloga("自动销毁");
    bh::Bexit a([]() {
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