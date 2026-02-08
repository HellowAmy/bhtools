#include <iostream>

#include "Bany.h"
#include "Btype.h"
#include "Btest.h"
#include "Tlog.h"

struct Bany_data
{
    Bany_data() {}
    Bany_data(bh::int32 i, const bh::dstr &s) : _i(i), _s(s) {}
    ~Bany_data() { vloga("Bany_data 析构执行"); }

    bh::int32 _i = -1;
    bh::dstr _s;

    bool operator==(const Bany_data &other) const { return _i == other._i && _s == other._s; }
};

void test_1()
{
    bh::int32 a1 = 123;
    bh::int16 a2 = 456;
    bh::uint64 a3 = 789;
    bh::cchp a4 = "hello";
    bh::dstr a5 = "world";
    bool a6 = true;
    bh::ft32 a7 = 1.23f;
    bh::ft64 a8 = 4.56;

    {
        bh::Bany any;
        vloga("测试空对象状态");
        BHTEST_TRUE(any.use<void>());
        BHTEST_TRUE(!any.use<bh::int32>());
    }

    {
        bh::Bany any(a1);
        vloga("测试 int32 存储与读取");
        vlogd($(a1));
        BHTEST_TRUE(any.use<bh::int32>());
        BHTEST_EQUAL(any.value<bh::int32>(), a1);
    }

    {
        bh::Bany any(a2);
        vloga("测试 int16 存储与读取");
        vlogd($(a2));
        BHTEST_TRUE(any.use<bh::int16>());
        BHTEST_EQUAL(any.value<bh::int16>(), a2);
    }

    {
        bh::Bany any(a3);
        vloga("测试 int16 存储与读取");
        vlogd($(a3));
        BHTEST_TRUE(any.use<bh::uint64>());
        BHTEST_EQUAL(any.value<bh::uint64>(), a3);
    }

    {
        bh::Bany any(a4);
        vloga("测试 cchp 存储与读取");
        vlogd($(a4));
        BHTEST_TRUE(any.use<bh::cchp>());
        BHTEST_EQUAL(any.value<bh::cchp>(), a4);
    }

    {
        bh::Bany any(a5);
        vloga("测试 dstr 存储与读取");
        vlogd($(a5));
        BHTEST_TRUE(any.use<bh::dstr>());
        BHTEST_EQUAL(any.value<bh::dstr>(), a5);
    }

    {
        bh::Bany any(a6);
        vloga("测试 bool 存储与读取");
        vlogd($(a6));
        BHTEST_TRUE(any.use<bool>());
        BHTEST_EQUAL(any.value<bool>(), a6);
    }

    {
        bh::Bany any(a7);
        vloga("测试 bh::ft32 存储与读取");
        vlogd($(a7));
        BHTEST_TRUE(any.use<bh::ft32>());
        BHTEST_EQUAL(any.value<bh::ft32>(), a7);
    }

    {
        bh::Bany any(a8);
        vloga("测试 bh::ft64 存储与读取");
        vlogd($(a8));
        BHTEST_TRUE(any.use<bh::ft64>());
        BHTEST_EQUAL(any.value<bh::ft64>(), a8);
    }
}

void test_2()
{
    {
        Bany_data d1(999, "hello");
        bh::Bany any1(d1);
        vloga("测试自定义结构体存储");
        BHTEST_TRUE(any1.use<Bany_data>());
        BHTEST_EQUAL(any1.value<Bany_data>()._i, 999);

        vloga("测试对象拷贝构造");
        bh::Bany any2(any1);
        BHTEST_TRUE(any2.use<Bany_data>());
        BHTEST_EQUAL(any2.value<Bany_data>()._s, "hello");

        vloga("测试对象赋值操作");
        bh::Bany any3;
        any3 = any2;
        BHTEST_EQUAL(any3.value<Bany_data>()._i, 999);
    }
    vloga("结构体作用域生命周期结束");
}

void test_3()
{
    vloga("测试重新赋值为不同类型 int32");
    bh::Bany any(bh::int32(100));
    BHTEST_TRUE(any.use<bh::int32>());
    BHTEST_EQUAL((any.value<bh::int32>()), 100);

    vloga("测试重新赋值为不同类型 ft64");
    any = bh::ft64(3.1415);
    BHTEST_TRUE(any.use<bh::ft64>());
    BHTEST_EQUAL(any.value<bh::ft64>(), 3.1415);
}

void test_4()
{
    vloga("判断数据类型正确");

    bh::Bany any(bh::int64(100));

    if(any.use<bh::ft32>()) {
        vlogd($(any.value<bh::ft32>()));
    }

    if(any.use<bh::int64>()) {
        vlogd($(any.value<bh::int64>()));
    }

    if(any.use<bh::dstr>()) {
        vlogd($(any.value<bh::dstr>()));
    }
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}
