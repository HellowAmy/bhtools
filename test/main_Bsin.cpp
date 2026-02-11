#include <iostream>

#include "Bsin.h"
#include "Btype.h"
#include "Btest.h"

// 继承式单例-继承单例会自己调用析构-否则需要手动调用
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
    vloga("单例访问\n");
    TastA::get()->print();
    bh::Bsins<TastB>::get()->print();
}

void test_2()
{
    vloga("开放式静态单例\n");
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
    vloga("自动销毁\n");
    bh::Bexit a([]() {
        vlogd("exit func");
    });
}

class TastDA : public bh::Bsins<TastDA>
{
public:
    friend bh::Bsins<TastDA>;
    void print() { vlogd("hellow world A"); }

protected:
    TastDA() { vlogd("TastDA构造函数"); }
    ~TastDA() { vlogd("TastDA析构"); }
};

class TastDB : public bh::Bsind<TastDB>
{
public:
    friend bh::Bsind<TastDB>;
    void print() { vlogd("hellow world B"); }

protected:
    TastDB() { vlogd("TastDB构造函数"); }
    ~TastDB() { vlogd("TastDB析构"); }
};

class TastDC
{
public:
    void print() { vlogd("hellow world C"); }
    TastDC() { vlogd("TastDC构造函数"); }
    ~TastDC() { vlogd("TastDC析构"); }
};

class TastDD
{
public:
    void print() { vlogd("hellow world D"); }
    TastDD() { vlogd("TastDD构造函数"); }
    ~TastDD() { vlogd("TastDD析构"); }
};

void test_4()
{
    vloga("析构测试\n");
    TastDA::get()->print();
    TastDA::get()->print();
    TastDB::get()->print();
    TastDB::get()->print();

    bh::Bsind<TastDC>::get()->print();
    bh::Bsind<TastDC>::get()->print();

    bh::Bsins<TastDD>::get()->print();
    bh::Bsins<TastDD>::get()->print();
}

int main(int argc, char *argv[])
{
    //
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}