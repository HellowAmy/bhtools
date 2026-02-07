#include <iostream>
#include <tuple>
#include <cstdint>
#include <charconv>

#include "Bstrto.h"
#include "Btime.h"

#include "Ftest.h"

void test_1()
{
    bh::int08 a1 = 1;
    bh::int16 a2 = 2;
    bh::int32 a3 = 3;
    bh::int64 a4 = 4;

    bh::uint08 a5 = 5;
    bh::uint16 a6 = 6;
    bh::uint32 a7 = 7;
    bh::uint64 a8 = 8;

    bh::ft32 b1 = 3.14;
    bh::ft64 b2 = 3.1415;

    bh::dstr c1 = "hello1";
    bh::cstr c2 = "hello2";
    bh::dstr &c3 = c1;

    char c4[] = "hello3";
    bh::dchp c5 = "hello4";
    bh::cchp c6 = "hello5";

    bh::Bstr s1 = bh::Bstrto::to_str(a1);
    bh::Bstr s2 = bh::Bstrto::to_str(a2);
    bh::Bstr s3 = bh::Bstrto::to_str(a3);
    bh::Bstr s4 = bh::Bstrto::to_str(a4);
    bh::Bstr s5 = bh::Bstrto::to_str(a5);
    bh::Bstr s6 = bh::Bstrto::to_str(a6);
    bh::Bstr s7 = bh::Bstrto::to_str(a7);
    bh::Bstr s8 = bh::Bstrto::to_str(a8);
    bh::Bstr s9 = bh::Bstrto::to_str(b1);
    bh::Bstr s10 = bh::Bstrto::to_str(b2);
    bh::Bstr s11 = bh::Bstrto::to_str(c1);
    bh::Bstr s12 = bh::Bstrto::to_str(c2);
    bh::Bstr s13 = bh::Bstrto::to_str(c3);
    bh::Bstr s14 = bh::Bstrto::to_str(c4);
    bh::Bstr s15 = bh::Bstrto::to_str(c5);
    bh::Bstr s16 = bh::Bstrto::to_str(c6);

    vloga("整数");
    vlogd($(a1));
    vlogd($(a2));
    vlogd($(a3));
    vlogd($(a4));
    vlogd($(a5));
    vlogd($(a6));
    vlogd($(a7));
    vlogd($(a8));

    vloga("浮点");
    vlogd($(b1));
    vlogd($(b2));

    vloga("字符");
    vlogd($(c1));
    vlogd($(c2));
    vlogd($(c3));
    vlogd($(c4));
    vlogd($(c5));
    vlogd($(c6));

    vloga("转换之后");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
    vlogd($(s5));
    vlogd($(s6));
    vlogd($(s7));
    vlogd($(s8));
    vlogd($(s9));
    vlogd($(s10));
    vlogd($(s11));
    vlogd($(s12));
    vlogd($(s13));
    vlogd($(s14));
    vlogd($(s15));
    vlogd($(s16));
}

void test_2()
{
    std::pair<bh::int32, bh::dstr> d1 = std::make_pair(1, "hello1");
    std::tuple<bh::int32, bh::int32, bh::dstr> d2 = std::make_tuple(1, 2, "hello2");
    bh::cchp d3 = "hello3";
    bh::ft64 d4 = 3.1415926123123123;

    bh::Bstr s1 = bh::Bstrto::to_str(d1);
    bh::Bstr s2 = bh::Bstrto::to_str(d2);
    bh::Bstr s3 = bh::Bstrto::to_str(d3);
    bh::Bstr s4 = bh::Bstrto::to_str((void *)d3);
    bh::Bstr s5 = bh::Bstrto::to_str(d4);
    bh::Bstr s6 = bh::Bstrto::to_str(bh::Bstrto::float_dec(d4, 10));

    vloga("特殊类型转换");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
    vlogd($(s5));
    vlogd($(s6));
}

void test_3()
{
    char cs1[] = "100";
    bh::cchp cs2 = "101";
    bh::dstr cs3 = "102";
    bh::cstr cs4 = "10399";
    bh::Bstr cs5("xxxx");
    bh::Bstr cs6("00100");
    bh::Bstr cs7("3.1415");
    bh::Bstr cs8("3.1415926123123123");
    bh::Bstr cs9("xxxxxxxxx.xxxxx");

    auto a1 = bh::Bstrto::from_str<bh::int32>(cs1);
    auto a2 = bh::Bstrto::from_str<bh::int32>(cs2);
    auto a3 = bh::Bstrto::from_str<bh::int32>(cs3);
    auto a4 = bh::Bstrto::from_str<bh::int32>(cs4);
    auto a5 = bh::Bstrto::from_str<bh::int32>(cs5);
    auto a6 = bh::Bstrto::from_str<bh::int32>(cs6);
    auto a7 = bh::Bstrto::from_str<bh::ft32>(cs7);
    auto a8 = bh::Bstrto::from_str<bh::ft64>(cs8);
    auto a9 = bh::Bstrto::from_str<bh::ft64>(cs9);

    vloga("转数字");
    vlogd($(a1));
    vlogd($(a2));
    vlogd($(a3));
    vlogd($(a4));
    vlogd($(a5));
    vlogd($(a6));
    vlogd($(a7));
    vlogd($(a8));
    vlogd($(a9));

    auto b1 = bh::Bstrto::from_str_opt<bh::int32>(cs1);
    auto b2 = bh::Bstrto::from_str_opt<bh::int32>(cs2);
    auto b3 = bh::Bstrto::from_str_opt<bh::int32>(cs3);
    auto b4 = bh::Bstrto::from_str_opt<bh::int32>(cs4);
    auto b5 = bh::Bstrto::from_str_opt<bh::int32>(cs5);
    auto b6 = bh::Bstrto::from_str_opt<bh::int32>(cs6);
    auto b7 = bh::Bstrto::from_str_opt<bh::ft32>(cs7);
    auto b8 = bh::Bstrto::from_str_opt<bh::ft64>(cs8);
    auto b9 = bh::Bstrto::from_str_opt<bh::ft64>(cs9);

    vloga("转数字可判断");
    BHTEST_TRUE(b1.use());
    BHTEST_TRUE(b2.use());
    BHTEST_TRUE(b3.use());
    BHTEST_TRUE(b4.use());
    BHTEST_TRUE(b5.use());
    BHTEST_TRUE(b6.use());
    BHTEST_TRUE(b7.use());
    BHTEST_TRUE(b8.use());
    BHTEST_TRUE(b9.use());

    vlogd($(*b1));
    vlogd($(*b2));
    vlogd($(*b3));
    vlogd($(*b4));
    vlogd($(*b5));
    vlogd($(*b6));
    vlogd($(*b7));
    vlogd($(*b8));
    vlogd($(*b9));
}

void test_4()
{
    bh::Bstr cs1(bh::Bstrto::to_str(INT32_MAX));
    bh::Bstr cs2(bh::Bstrto::to_str(UINT32_MAX));
    bh::Bstr cs3(bh::Bstrto::to_str(INT64_MAX));
    bh::Bstr cs4(bh::Bstrto::to_str(UINT64_MAX));

    auto b1 = bh::Bstrto::from_str_opt<bh::int32>(cs1);
    auto b2 = bh::Bstrto::from_str_opt<bh::uint32>(cs2);
    auto b3 = bh::Bstrto::from_str_opt<bh::int64>(cs3);
    auto b4 = bh::Bstrto::from_str_opt<bh::uint64>(cs4);

    vloga("范围判断");
    vlogd($(cs1));
    vlogd($(cs2));
    vlogd($(cs3));
    vlogd($(cs4));

    vloga("转数字");
    BHTEST_EQUAL(*b1, INT32_MAX)
    BHTEST_EQUAL(*b2, UINT32_MAX)
    BHTEST_EQUAL(*b3, INT64_MAX)
    BHTEST_EQUAL(*b4, UINT64_MAX)
}

void test_5()
{
    bh::Btimel t1;
    bh::int32 sum = 1000 * 10000;

    char buf[128];
    for(bh::int32 i = 0; i < sum; i++) {
        snprintf(buf, sizeof(buf), "%d%d%d%d%d%d%d%d%d", i, i, i, i, i, i, i, i, i);
    }
    auto p1 = t1.time_interval();
    t1.update();

    for(bh::int32 i = 0; i < sum; i++) {
        std::string s1 = std::to_string(i);
        std::string s2 = std::to_string(i);
        std::string s3 = std::to_string(i);
        std::string s4 = std::to_string(i);
        std::string s5 = std::to_string(i);
        std::string s6 = std::to_string(i);
        std::string s7 = std::to_string(i);
        std::string s8 = std::to_string(i);
        std::string s9 = std::to_string(i);
    }
    auto p2 = t1.time_interval();
    t1.update();

    for(bh::int32 i = 0; i < sum; i++) {
        bh::Bstr s1 = bh::Bstrto::to_str(i);
        bh::Bstr s2 = bh::Bstrto::to_str(i);
        bh::Bstr s3 = bh::Bstrto::to_str(i);
        bh::Bstr s4 = bh::Bstrto::to_str(i);
        bh::Bstr s5 = bh::Bstrto::to_str(i);
        bh::Bstr s6 = bh::Bstrto::to_str(i);
        bh::Bstr s7 = bh::Bstrto::to_str(i);
        bh::Bstr s8 = bh::Bstrto::to_str(i);
        bh::Bstr s9 = bh::Bstrto::to_str(i);
    }
    auto p3 = t1.time_interval();
    t1.update();

    for(bh::int32 i = 0; i < sum; i++) {
        bh::Bstr s1 = std::move(std::to_string(i));
        bh::Bstr s2 = std::move(std::to_string(i));
        bh::Bstr s3 = std::move(std::to_string(i));
        bh::Bstr s4 = std::move(std::to_string(i));
        bh::Bstr s5 = std::move(std::to_string(i));
        bh::Bstr s6 = std::move(std::to_string(i));
        bh::Bstr s7 = std::move(std::to_string(i));
        bh::Bstr s8 = std::move(std::to_string(i));
        bh::Bstr s9 = std::move(std::to_string(i));
    }
    auto p4 = t1.time_interval();
    t1.update();

    vloga("性能测试");
    vlogd($(t1.to_str(p1)));
    vlogd($(t1.to_str(p2)));
    vlogd($(t1.to_str(p3)));
    vlogd($(t1.to_str(p4)));
}

int main(int argc, char *argv[])
{
    // test_1();
    // test_2();
    // test_3();
    // test_4();
    test_5();

    return 0;
}