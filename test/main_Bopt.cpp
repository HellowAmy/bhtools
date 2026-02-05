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
    auto a9 = bh::Bopt<bh::cstr>("hello2");
    auto a10 = bh::Bopt<bh::Bstr>("hello3");

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
    BHTEST_TRUE(a10.use());

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
    // if(a9)
    // {
    //     vlogd($(*a9));
    // }
    if(a10) {
        vlogd($(*a10));
    }
}

void test_2() {}

int main(int argc, char *argv[])
{
    test_1();
    // test_2();

    return 0;
}