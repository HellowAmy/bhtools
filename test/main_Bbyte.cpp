#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

#include "Bbyte.h"
#include "Btype.h"
#include "Btest.h"

void test_1()
{
    vloga("字节转换\n");
    bh::int32 a1 = 1;
    bh::int32 a2 = 15;
    bh::int32 a3 = 65535;

    auto s1 = bh::Bbyte::b2_s2(a1);
    auto s2 = bh::Bbyte::b2_s2(a2);
    auto s3 = bh::Bbyte::b2_s2(a3);

    auto sa1 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a1));
    auto sa2 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a2));
    auto sa3 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a3));

    vloga("转换前");
    BHTEST_EQUAL(s1, "00000000000000000000000000000001");
    BHTEST_EQUAL(s2, "00000000000000000000000000001111");
    BHTEST_EQUAL(s3, "00000000000000001111111111111111");

    vloga("转换后");
    BHTEST_EQUAL(sa1, "00000001000000000000000000000000");
    BHTEST_EQUAL(sa2, "00001111000000000000000000000000");
    BHTEST_EQUAL(sa3, "11111111111111110000000000000000");
}

void test_2()
{
    bh::int08 a1 = 1;
    bh::int16 a2 = 3;
    bh::int32 a3 = 7;
    bh::int64 a4 = 15;

    bh::int08 a5 = -32;
    bh::int16 a6 = -64;
    bh::int32 a7 = -128;
    bh::int64 a8 = -256;

    bh::uint08 a9 = 1;
    bh::uint16 a10 = 3;
    bh::uint32 a11 = 7;
    bh::uint64 a12 = 15;

    auto sa1 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a1));
    auto sa2 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a2));
    auto sa3 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a3));
    auto sa4 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a4));

    auto sa5 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a5));
    auto sa6 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a6));
    auto sa7 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a7));
    auto sa8 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a8));

    auto sa9 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a9));
    auto sa10 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a10));
    auto sa11 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a11));
    auto sa12 = bh::Bbyte::b2_s2(bh::Bendian::swap_endian(a12));

    vloga("小端内存排布\n");
    BHTEST_EQUAL(sa1, "00000001");
    BHTEST_EQUAL(sa2, "0000001100000000");
    BHTEST_EQUAL(sa3, "00000111000000000000000000000000");
    BHTEST_EQUAL(sa4, "0000111100000000000000000000000000000000000000000000000000000000");
    BHTEST_EQUAL(sa5, "11100000");
    BHTEST_EQUAL(sa6, "1100000011111111");
    BHTEST_EQUAL(sa7, "10000000111111111111111111111111");
    BHTEST_EQUAL(sa8, "0000000011111111111111111111111111111111111111111111111111111111");
    BHTEST_EQUAL(sa9, "00000001");
    BHTEST_EQUAL(sa10, "0000001100000000");
    BHTEST_EQUAL(sa11, "00000111000000000000000000000000");
    BHTEST_EQUAL(sa12, "0000111100000000000000000000000000000000000000000000000000000000");
}

void test_3()
{
    vloga("内存字节\n");
    bh::int08 a1 = 1;
    bh::int16 a2 = 3;
    bh::int32 a3 = 7;
    bh::int64 a4 = 15;

    auto sa1 = bh::Bbyte::b2_s2(a1);
    auto sa2 = bh::Bbyte::b2_s2(a2);
    auto sa3 = bh::Bbyte::b2_s2(a3);
    auto sa4 = bh::Bbyte::b2_s2(a4);

    vloga("逻辑内存字节-总是一样");
    BHTEST_EQUAL(sa1, "00000001");
    BHTEST_EQUAL(sa2, "0000000000000011");
    BHTEST_EQUAL(sa3, "00000000000000000000000000000111");
    BHTEST_EQUAL(sa4, "0000000000000000000000000000000000000000000000000000000000001111");

    auto ss1 = bh::Bbyte::b2_s2_true(a1);
    auto ss2 = bh::Bbyte::b2_s2_true(a2);
    auto ss3 = bh::Bbyte::b2_s2_true(a3);
    auto ss4 = bh::Bbyte::b2_s2_true(a4);

    vloga("真实内存字节-根据大端和小端有区别");
    BHTEST_EQUAL(ss1, "00000001");
    BHTEST_EQUAL(ss2, "0000001100000000");
    BHTEST_EQUAL(ss3, "00000111000000000000000000000000");
    BHTEST_EQUAL(ss4, "0000111100000000000000000000000000000000000000000000000000000000");
}

void test_4()
{
    bh::int32 a1 = 0b00001111111111110000111111111111;

    auto s1 = bh::Bbyte::b2_s2(a1);
    auto s2 = bh::Bbyte::b2_s2_true(a1);
    auto s3 = bh::Bbyte::b2_s8(a1);
    auto s4 = bh::Bbyte::b2_s16(a1);
    auto s5 = bh::Bbyte::b2_s10(a1);

    vloga("数字转各进制\n");
    BHTEST_EQUAL(s1, "00001111111111110000111111111111");
    BHTEST_EQUAL(s2, "11111111000011111111111100001111");
    BHTEST_EQUAL(s3, "01777607777");
    BHTEST_EQUAL(s4, "0fff0fff");
    BHTEST_EQUAL(s5, "268374015");
    BHTEST_EQUAL(a1, 268374015);

    vloga("各进制转数字");
    bh::int32 d1 = bh::Bbyte::s2_b2<bh::int32>(s1);
    bh::int32 d2 = bh::Bbyte::s8_b2<bh::int32>(s3);
    bh::int32 d3 = bh::Bbyte::s16_b2<bh::int32>(s4);
    bh::int32 d4 = bh::Bbyte::s10_b2<bh::int32>(s5);

    BHTEST_EQUAL(d1, a1);
    BHTEST_EQUAL(d2, a1);
    BHTEST_EQUAL(d3, a1);
    BHTEST_EQUAL(d4, a1);
}

void test_5()
{
    bh::int32 a1 = 1;
    bh::int32 a2 = 7;
    bh::int32 a3 = 8;
    bh::int32 a4 = 10;
    bh::int32 a5 = 15;
    bh::int32 a6 = 25;

    char c1 = bh::Bbyte::num_hex(a1);
    char c2 = bh::Bbyte::num_hex(a2);
    char c3 = bh::Bbyte::num_hex(a3);
    char c4 = bh::Bbyte::num_hex(a4);
    char c5 = bh::Bbyte::num_hex(a5);
    char c6 = bh::Bbyte::num_hex(a6);

    vloga("转16进制\n");
    BHTEST_EQUAL(c1, '1');
    BHTEST_EQUAL(c2, '7');
    BHTEST_EQUAL(c3, '8');
    BHTEST_EQUAL(c4, 'a');
    BHTEST_EQUAL(c5, 'f');
    BHTEST_EQUAL(c6, '0');

    bh::int32 b1 = bh::Bbyte::hex_num(c1);
    bh::int32 b2 = bh::Bbyte::hex_num(c2);
    bh::int32 b3 = bh::Bbyte::hex_num(c3);
    bh::int32 b4 = bh::Bbyte::hex_num(c4);
    bh::int32 b5 = bh::Bbyte::hex_num(c5);
    bh::int32 b6 = bh::Bbyte::hex_num(c6);

    vloga("反转16进制");
    BHTEST_EQUAL(a1, b1);
    BHTEST_EQUAL(a2, b2);
    BHTEST_EQUAL(a3, b3);
    BHTEST_EQUAL(a4, b4);
    BHTEST_EQUAL(a5, b5);
    BHTEST_TRUE(a6 != b6);
}

void test_6()
{
    bh::dstr s1 = "Hello World 1";
    bh::dstr s2 = "hello world 2";
    bh::dstr s3 = "HELLO WORLD 3";

    auto ss1 = bh::Bbyte::to_upper(s1);
    auto ss2 = bh::Bbyte::to_upper(s2);
    auto ss3 = bh::Bbyte::to_upper(s3);

    vloga("转大写字母\n");
    BHTEST_EQUAL(ss1, "HELLO WORLD 1");
    BHTEST_EQUAL(ss2, "HELLO WORLD 2");
    BHTEST_EQUAL(ss3, "HELLO WORLD 3");

    vloga("转小写字母");
    auto sa1 = bh::Bbyte::to_lower(s1);
    auto sa2 = bh::Bbyte::to_lower(s2);
    auto sa3 = bh::Bbyte::to_lower(s3);

    BHTEST_EQUAL(sa1, "hello world 1");
    BHTEST_EQUAL(sa2, "hello world 2");
    BHTEST_EQUAL(sa3, "hello world 3");
}

void test_7()
{
    bh::ft32 a1 = 123.456;
    bh::ft64 a2 = 123456.123456;

    auto d1 = bh::Bbyte::to_integer(a1);
    auto d2 = bh::Bbyte::to_integer(a2);

    auto s1 = bh::Bbyte::b2_s2(d1);
    auto s2 = bh::Bbyte::b2_s2(d2);

    vloga("浮点转二进制\n");
    BHTEST_EQUAL(d1, 1123477881);
    BHTEST_EQUAL(d2, 4683220253414326184);

    BHTEST_EQUAL(s1, "01000010111101101110100101111001");
    BHTEST_EQUAL(s2, "0100000011111110001001000000000111111001101011001111111110101000");

    vloga("反转回浮点");
    auto dd1 = bh::Bbyte::s2_b2<bh::int32>(s1);
    auto dd2 = bh::Bbyte::s2_b2<bh::int64>(s2);

    bh::ft32 aa1;
    bh::ft64 aa2;
    std::memcpy(&aa1, &d1, sizeof(aa1));
    std::memcpy(&aa2, &d2, sizeof(aa2));

    BHTEST_EQUAL(dd1, d1);
    BHTEST_EQUAL(dd2, d2);
    BHTEST_EQUAL(aa1, a1);
    BHTEST_EQUAL(aa2, a2);
}

void test_8()
{
    vloga("指数计算\n");

    bh::int32 d1 = bh::Bbyte::calc_exp(2, 2);
    bh::int32 d2 = bh::Bbyte::calc_exp(2, 3);
    bh::int32 d3 = bh::Bbyte::calc_exp(2, 4);

    BHTEST_EQUAL(d1, 4);
    BHTEST_EQUAL(d2, 8);
    BHTEST_EQUAL(d3, 16);
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();

    return 0;
}
