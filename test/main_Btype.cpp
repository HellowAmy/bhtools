#include <iostream>

#include "Btype.h"
#include "Ftest.h"

void test_1()
{
    bh::int08 a1 = 1;
    bh::int16 a2 = 2;
    bh::int32 a3 = 3;
    bh::int64 a4 = 4;

    bh::uint08 ua1 = 5;
    bh::uint16 ua2 = 6;
    bh::uint32 ua3 = 7;
    bh::uint64 ua4 = 8;

    bh::ft32 b1 = 167772170123.0;
    bh::ft64 b2 = 167772170123.0;

    bh::dstr c1 = "hello";
    bh::cstr c2 = "world";
    bh::rstr c3 = c1;

    bh::dchr d1[100] = "hello";
    bh::dchp d2 = d1;
    bh::cchp d3 = "world";

    vloga("长度测试");
    BHTEST_EQUAL(sizeof(a1), 1)
    BHTEST_EQUAL(sizeof(a2), 2)
    BHTEST_EQUAL(sizeof(a3), 4)
    BHTEST_EQUAL(sizeof(a4), 8)

    BHTEST_EQUAL(sizeof(ua1), 1)
    BHTEST_EQUAL(sizeof(ua2), 2)
    BHTEST_EQUAL(sizeof(ua3), 4)
    BHTEST_EQUAL(sizeof(ua4), 8)

    vloga("指针长度");
    BHTEST_EQUAL(sizeof(d1), 100)
    BHTEST_EQUAL(sizeof(d2), 8)
    BHTEST_EQUAL(sizeof(d3), 8)

    vloga("数据显示");
    vlogd($(a1) $(a2) $(a3) $(a4));
    vlogd($(ua1) $(ua2) $(ua3) $(ua4));
    vlogd($(b1) $(b2));
    vlogd($(c1) $(c2) $(c3));
    vlogd($(d1) $(d2) $(d3));
}

void test_2() {}

int main(int argc, char *argv[])
{
    test_1();
    // test_2();

    return 0;
}