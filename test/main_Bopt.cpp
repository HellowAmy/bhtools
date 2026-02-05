#include <iostream>

#include <mutex>

#include "Bstr.h"
#include "Bopt.h"
#include "Btype.h"

#include "Ftest.h"

void test_1()
{
    auto a1 = bh::Bopt<bh::int32>();
    auto a2 = bh::Bopt<bh::int32>(100);
    auto a3 = bh::Bopt<bh::int64>(0);
    auto a4 = bh::Bopt<bh::int64>(100);
    auto a5 = bh::Bopt<bh::ft32>();
    auto a6 = bh::Bopt<bh::ft32>(3.1415);
    auto a7 = bh::Bopt<bh::dstr>();
    auto a8 = bh::Bopt<bh::dstr>("hello1");
    auto a9 = bh::Bopt<bh::Bstr>("hello2");

    vloga("测试有效");
    BHTEST_TRUE(a1.use());
    BHTEST_TRUE(a2.use());
    BHTEST_TRUE(a3.use());
    BHTEST_TRUE(a4.use());
    BHTEST_TRUE(a5.use());
    BHTEST_TRUE(a6.use());
    BHTEST_TRUE(a7.use());
    BHTEST_TRUE(a8.use());
    BHTEST_TRUE(a9.use());

    vloga("打印有效值");
    if(a1) {
        vlogd($(*a1));
    }
    if(a2) {
        vlogd($(*a2));
    }
    if(a3) {
        vlogd($(*a3));
    }
    if(a4) {
        vlogd($(*a4));
    }
    if(a5) {
        vlogd($(*a5));
    }
    if(a6) {
        vlogd($(*a6));
    }
    if(a7) {
        vlogd($(*a7));
    }
    if(a8) {
        vlogd($(*a8));
    }
    if(a9) {
        vlogd($(*a9));
    }
}

struct test_data
{
    bh::int32 num;
    bh::Bstr str;
};

bh::Bopt<test_data> get_word(bh::int32 num)
{
    if(num > 10) {
        test_data d;
        d.num = num + 20;
        d.str = "hello";
        return bh::Bopt<test_data>(d);
    }
    else {
        return bh::Bopt<test_data>();
    }
}

void test_2()
{
    bh::Bopt<test_data> a1 = get_word(5);
    bh::Bopt<test_data> a2 = get_word(15);
    bh::BCopt<test_data> a3 = get_word(25);
    auto a4 = get_word(1);

    vloga("有效值");
    BHTEST_TRUE(a1.use());
    BHTEST_TRUE(a2.use());
    BHTEST_TRUE(a3.use());
    BHTEST_TRUE(a4.use());

    vloga("打印");
    vlogd($(a1->num) $(a1->str));
    vlogd($(a2->num) $(a2->str));
    vlogd($(a3->num) $(a3->str));
    vlogd($(a4->num) $(a4->str));
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}