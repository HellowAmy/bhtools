 
#include <iostream>
#include <string.h>

#include "bhtools.h"

void test_1()
{
    // 交换字节序
    int a1 = 3855;
    int a2 = bhtools::Tendian::swap_endian(a1);
    int a3 = bhtools::Tendian::to_host(a1);
    int a4 = bhtools::Tendian::to_net(a1);
    int a5 = bhtools::Tendian::to_net(a2);
    vlogd($(a1) $(a2) $(a3) $(a4) $(a5));
}

void test_2()
{
    // 二进制与可视化字符相互转化
    int a1 = 14;
    auto s1 = bhtools::Tbyte::b2_s2(a1);
    auto s2 = bhtools::Tbyte::b2_s2_true(a1);
    auto s3 = bhtools::Tbyte::b2_s8(a1);
    auto s4 = bhtools::Tbyte::b2_s16(a1);
    auto s5 = bhtools::Tbyte::b2_s10(a1);
    vlogd($(a1) $(s1) $(s2) $(s3) $(s4) $(s5));

    int d1 = bhtools::Tbyte::s2_b2<int>(s1);
    int d2 = bhtools::Tbyte::s8_b2<int>(s3);
    int d3 = bhtools::Tbyte::s10_b2<int>(s5);
    int d4 = bhtools::Tbyte::s16_b2<int>(s4);
    vlogd($(d1) $(d2) $(d3) $(d4) );

    auto vec1 = bhtools::Tbyte::char_hex('a');
    auto vec2 = bhtools::Tbyte::char_oct('a');
    auto h1 = bhtools::Tbyte::num_hex(9);
    auto h2 = bhtools::Tbyte::num_hex(15);
    auto h3 = bhtools::Tbyte::hex_num('f');
    auto h4 = bhtools::Tbyte::hex_num('4');
    auto h5 = bhtools::Tbyte::oct_num('1');
    auto h6 = bhtools::Tbyte::oct_num('7');
    vlogd($C(vec1) $C(vec2) $(h1) $(h2) $(h3) $(h4) $(h5) $(h6));
}

void test_3()
{
    // 判断字符类型
    auto a1 = bhtools::Tbyte::is_hex_digit('7');
    auto a2 = bhtools::Tbyte::is_hex_digit('a');
    auto a3 = bhtools::Tbyte::is_hex_little('7');
    auto a4 = bhtools::Tbyte::is_hex_little('a');
    auto a5 = bhtools::Tbyte::is_hex_little('A');
    auto a6 = bhtools::Tbyte::is_hex_big('a');
    auto a7 = bhtools::Tbyte::is_hex_big('A');
    auto a8 = bhtools::Tbyte::is_hex_range('f');
    auto a9 = bhtools::Tbyte::is_hex_range('p');
    auto a10 = bhtools::Tbyte::is_oct_range('7');
    auto a11 = bhtools::Tbyte::is_oct_range('8');

    vlogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6));
    vlogd($(a7) $(a8) $(a9) $(a10) $(a11));

    auto s1 = bhtools::Tbyte::to_upper('1');
    auto s2 = bhtools::Tbyte::to_upper('a');
    auto s3 = bhtools::Tbyte::to_lower('A');
    auto s4 = bhtools::Tbyte::to_lower("123asHU");
    auto s5 = bhtools::Tbyte::to_upper("123asHU");
    vlogd($(s1) $(s2) $(s3) $(s4) $(s5));

    int aa1;
    short aa2;
    size_t aa3;
    auto h1 = bhtools::Tbyte::size_byte(aa1);
    auto h2 = bhtools::Tbyte::size_byte(aa2);
    auto h3 = bhtools::Tbyte::size_byte(aa3);
    vlogd($(h1) $(h2) $(h3));

    auto c1 = bhtools::Tbyte::calc_exp(1,2);
    auto c2 = bhtools::Tbyte::calc_exp(1,2);
    auto c3 = bhtools::Tbyte::calc_exp(2,2);
    auto c4 = bhtools::Tbyte::calc_exp(2,3);
    auto c5 = bhtools::Tbyte::calc_exp(3,3);
    vlogd($(c1) $(c2) $(c3) $(c4) $(c5));
}


int main(int argc, char *argv[])
{
    test_1(); 
    test_2(); 
    test_3(); 

    return 0;
}