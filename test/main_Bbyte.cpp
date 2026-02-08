#include <iostream>
#include <string.h>
#include <vector>

#include "Bbyte.h"
#include "Btype.h"
#include "Tlog.h"
#include "Btest.h"

void test_1()
{
    vloga("Bendian 字节序转换逻辑测试 (参考 main_byte::test_1)");
    bh::int32 a1 = 3855;
    bh::int32 a2 = bh::Bendian::swap_endian(a1);
    bh::int32 a3 = bh::Bendian::to_host(a1);
    bh::int32 a4 = bh::Bendian::to_net(a1);
    bh::int32 a5 = bh::Bendian::to_net(a2);
    
    vlogd($(a1) $(a2) $(a3) $(a4) $(a5));
    
    vloga("执行字节序还原校验");
    BHTEST_EQUAL(bh::Bendian::swap_endian(a2), a1);
}

void test_2()
{
    vloga("Bbyte 进制与可视化字符串转换测试 (参考 main_byte::test_2)");
    bh::int32 a1 = 14;
    auto s1 = bh::Bbyte::b2_s2(a1);
    auto s2 = bh::Bbyte::b2_s2_true(a1);
    auto s3 = bh::Bbyte::b2_s8(a1);
    auto s4 = bh::Bbyte::b2_s16(a1);
    auto s5 = bh::Bbyte::b2_s10(a1);
    vlogd($(a1) $(s1) $(s2) $(s3) $(s4) $(s5));

    vloga("字符串逆向解析为二进制校验");
    bh::int32 d1 = bh::Bbyte::s2_b2<bh::int32>(s1);
    bh::int32 d2 = bh::Bbyte::s8_b2<bh::int32>(s3);
    bh::int32 d3 = bh::Bbyte::s10_b2<bh::int32>(s5);
    bh::int32 d4 = bh::Bbyte::s16_b2<bh::int32>(s4);
    vlogd($(d1) $(d2) $(d3) $(d4));
    
    BHTEST_EQUAL(d1, a1);
    BHTEST_EQUAL(d2, a1);
    BHTEST_EQUAL(d3, a1);
    BHTEST_EQUAL(d4, a1);

    vloga("Hex/Oct 符号与数值转换辅助接口测试");
    auto vec1 = bh::Bbyte::char_hex('a');
    auto vec2 = bh::Bbyte::char_oct('a');
    auto h1 = bh::Bbyte::num_hex(9);
    auto h2 = bh::Bbyte::num_hex(15);
    auto h3 = bh::Bbyte::hex_num('f');
    auto h4 = bh::Bbyte::hex_num('4');
    auto h5 = bh::Bbyte::oct_num('1');
    auto h6 = bh::Bbyte::oct_num('7');
    vlogd($C(vec1) $C(vec2) $(h1) $(h2) $(h3) $(h4) $(h5) $(h6));
    
    BHTEST_EQUAL(h1, '9');
    BHTEST_EQUAL(h2, 'f');
    BHTEST_EQUAL(h3, (bh::uint64)15);
}

void test_3()
{
    vloga("Bbyte 字符属性判断与转换接口测试 (参考 main_byte::test_3)");
    BHTEST_TRUE(bh::Bbyte::is_hex_digit('7'));
    BHTEST_TRUE(!bh::Bbyte::is_hex_digit('a'));
    BHTEST_TRUE(bh::Bbyte::is_hex_little('a'));
    BHTEST_TRUE(bh::Bbyte::is_hex_big('A'));
    BHTEST_TRUE(bh::Bbyte::is_hex_range('f'));
    BHTEST_TRUE(!bh::Bbyte::is_hex_range('p'));
    BHTEST_TRUE(bh::Bbyte::is_oct_range('7'));
    BHTEST_TRUE(!bh::Bbyte::is_oct_range('8'));

    vloga("单字符及字符串大小写转换测试");
    auto s1 = bh::Bbyte::to_upper('1');
    auto s2 = bh::Bbyte::to_upper('a');
    auto s3 = bh::Bbyte::to_lower('A');
    auto s4 = bh::Bbyte::to_lower("bhTOOLS");
    auto s5 = bh::Bbyte::to_upper("bhtools");
    vlogd($(s1) $(s2) $(s3) $(s4) $(s5));
    BHTEST_EQUAL(s2, 'A');
    BHTEST_EQUAL(s3, 'a');

    vloga("类型内存比特长度与幂运算校验");
    bh::int32 b1;
    bh::int16 b2;
    bh::uint64 b3;
    BHTEST_EQUAL(bh::Bbyte::size_byte(b1), (bh::uint64)32);
    BHTEST_EQUAL(bh::Bbyte::size_byte(b2), (bh::uint64)16);
    BHTEST_EQUAL(bh::Bbyte::size_byte(b3), (bh::uint64)64);

    BHTEST_EQUAL(bh::Bbyte::calc_exp(2, 3), (bh::uint64)8);
    BHTEST_EQUAL(bh::Bbyte::calc_exp(3, 3), (bh::uint64)27);

    vloga("浮点数位模式转换为整数测试 (Bit Cast)");
    bh::ft32 f1 = 5.5f;
    bh::ft64 f2 = 3.1415926;
    auto d1 = bh::Bbyte::to_integer(f1);
    auto d2 = bh::Bbyte::to_integer(f2);
    vlogd($(f1) $(f2) $(d1) $(d2));
    BHTEST_TRUE((d1 != 0));
}

void test_4()
{
    vloga("Bbyte 特殊数值二进制可视化展示测试 (参考 main_byte::test_4)");
    vloga("负数补码二进制展示");
    bh::int32 a1 = -14;
    auto s1 = bh::Bbyte::b2_s2(a1);
    auto s2 = bh::Bbyte::b2_s2_true(a1);
    vlogd($(a1) $(s1) $(s2));

    vloga("浮点数 IEEE 754 位模式展示");
    bh::ft64 b1 = 3.1415926;
    auto f1 = bh::Bbyte::b2_s2(bh::Bbyte::to_integer(b1));
    auto f2 = bh::Bbyte::b2_s2_true(bh::Bbyte::to_integer(b1));
    vlogd($(b1) $(f1) $(f2));
}

int main(bh::int32 argc, char *argv[])
{
    test_1(); 
    test_2(); 
    test_3(); 
    test_4(); 

    return 0;
}
