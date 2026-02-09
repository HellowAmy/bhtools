#include <iostream>

#include "Btype.h"
#include "Btest.h"

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
    bh::dstr &c3 = c1;

    char d1[100] = "hello";
    bh::dchp d2 = d1;
    bh::cchp d3 = "world";

    vloga("\n长度测试");
    vloga("整数长度");
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

void test_2()
{
    vloga("\n常量测试");
    vloga("数据长度");
    BHTEST_EQUAL(bh::_BH_INT_16_, 16);
    BHTEST_EQUAL(bh::_BH_INT_32_, 32);
    BHTEST_EQUAL(bh::_BH_INT_64_, 64);
    BHTEST_EQUAL(bh::_BH_INT_128_, 128);
    BHTEST_EQUAL(bh::_BH_INT_256_, 256);
    BHTEST_EQUAL(bh::_BH_INT_512_, 512);
    BHTEST_EQUAL(bh::_BH_INT_1024_, 1024);
    BHTEST_EQUAL(bh::_BH_INT_2048_, 2048);
    BHTEST_EQUAL(bh::_BH_INT_4096_, 4096);

    vloga("数值打印");
    BHTEST_EQUAL(bh::_BH_ONE_LOW_, 1);
    BHTEST_EQUAL(bh::_BH_ONE_HIGH_INT08_, 128);
    BHTEST_EQUAL(bh::_BH_ONE_HIGH_INT16_, 32768);
    BHTEST_EQUAL(bh::_BH_ONE_HIGH_INT32_, 2147483648);
    BHTEST_EQUAL(bh::_BH_ONE_HIGH_INT64_, 9223372036854775808ULL);

    BHTEST_EQUAL(bh::_BH_ONE_HEX_1_, 1);
    BHTEST_EQUAL(bh::_BH_ONE_HEX_2_, 2);
    BHTEST_EQUAL(bh::_BH_ONE_HEX_4_, 4);
    BHTEST_EQUAL(bh::_BH_ONE_HEX_8_, 8);
}

int main(int argc, char *argv[])
{
    //
    test_1();
    test_2();

    return 0;
}