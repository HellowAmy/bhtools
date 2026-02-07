#include <iostream>

#include "Bfm.h"
#include "Btime.h"

#include "Ftest.h"

void test_1()
{
    auto s1 = bh::Bfm("{}{}{}")(1, 2, 3);
    auto s2 = bh::Bfm("{}{}{}")(100, 200, 300);
    auto s3 = bh::Bfm("{}{}{}")(123, 456, 789);
    auto s4 = bh::Bfm("#{}#{}#{}#")(123, 456, 789);
    auto s5 = bh::Bfm("{}#{}#{}")(123, 456, 789);
    auto s6 = bh::Bfm("##{}##{}##{}##")(123, 456, 789);
    auto s7 = bh::Bfm("####{}####{}####{}####")(123, 456, 789);
    auto s8 = bh::Bfm("####{{}}####{{}}####{{}}####")(123, 456, 789);
    auto s9 = bh::Bfm("####{{#}}####{{#}}####{{#}}####")(123, 456, 789);

    auto a1 = bh::Bfm("{}{}{}")(1, 2, 3, 10, 10, 10);
    auto a2 = bh::Bfm("{}{}{}")(100, 200, 300, 10, 10, 10);
    auto a3 = bh::Bfm("{}{}{}")(123, 456, 789, 10, 10, 10);
    auto a4 = bh::Bfm("#{}#{}#{}#")(123, 456, 789, 10, 10, 10);
    auto a5 = bh::Bfm("{}#{}#{}")(123, 456, 789, 10, 10, 10);
    auto a6 = bh::Bfm("##{}##{}##{}##")(123, 456, 789, 10, 10, 10);
    auto a7 = bh::Bfm("####{}####{}####{}####")(123, 456, 789, 10, 10, 10);
    auto a8 = bh::Bfm("####{{}}####{{}}####{{}}####")(123, 456, 789, 10, 10, 10);
    auto a9 = bh::Bfm("####{{#}}####{{#}}####{{#}}####")(123, 456, 789, 10, 10, 10);

    auto b1 = bh::Bfm("{}{}{}{}")(100, 3.14, true, "hello");
    auto b2 = bh::Bfm("#{}#{}#{}#{}#")(100, 3.14, true, "hello");

    vloga("边界检查");
    BHTEST_EQUAL(s1, "123");
    BHTEST_EQUAL(s2, "100200300");
    BHTEST_EQUAL(s3, "123456789");
    BHTEST_EQUAL(s4, "#123#456#789#");
    BHTEST_EQUAL(s5, "123#456#789");
    BHTEST_EQUAL(s6, "##123##456##789##");
    BHTEST_EQUAL(s7, "####123####456####789####");
    BHTEST_EQUAL(s8, "####{123}####{456}####{789}####");
    BHTEST_EQUAL(s9, "####{{#}}####{{#}}####{{#}}####");

    vloga("多余参数");
    BHTEST_EQUAL(a1, "123");
    BHTEST_EQUAL(a2, "100200300");
    BHTEST_EQUAL(a3, "123456789");
    BHTEST_EQUAL(a4, "#123#456#789#");
    BHTEST_EQUAL(a5, "123#456#789");
    BHTEST_EQUAL(a6, "##123##456##789##");
    BHTEST_EQUAL(a7, "####123####456####789####");
    BHTEST_EQUAL(a8, "####{123}####{456}####{789}####");
    BHTEST_EQUAL(a9, "####{{#}}####{{#}}####{{#}}####");

    vloga("多类型转换");
    BHTEST_EQUAL(b1, "1003.140000truehello");
    BHTEST_EQUAL(b2, "#100#3.140000#true#hello#");
}

void test_2()
{
    bh::int32 sum = 1000 * 10000;
    bh::Btimel t1;

    char buf1[100] = {0};
    for(bh::int32 i = 0; i < sum; i++) {
        memset(buf1, 0, sizeof(buf1));
        snprintf(buf1, sizeof(buf1), "###%d---%d###%d---%d###%f---%f###%s---%s###", true, false,
                 100, 200, 3.1415, 9.99, "hello", "world");
    }
    auto p1 = t1.time_interval();
    t1.update();

    bh::Bstr buf2;
    for(bh::int32 i = 0; i < sum; i++) {
        buf2 = bh::Bfm("###{}---{}###{}---{}###{}---{}###{}---{}###")(true, false, 100, 200, 3.1415,
                                                                      9.99, "hello", "world");
    }
    auto p2 = t1.time_interval();
    t1.update();

    // bh::Bstr buf3;
    // for(bh::int32 i = 0; i < sum; i++) {
    //     buf3 = bh::Bfm("#{}-{}#{}-{}#{}-{}#{}-{}#")(true, false, 100, 200, 3.1415, 9.99, "hello",
    //                                                 "world");
    // }
    // auto p3 = t1.time_interval();
    // t1.update();

    // bh::Bstr buf4;
    // for(bh::int32 i = 0; i < sum; i++) {
    //     buf4 = bh::Bfm("###{}---{}###{}---{}###{}---{}###{}---{}###")(
    //         true, false, 100, 200, 3.1415, 9.99, "hello", "world", 123, 123, 123, 123, 123, 123,
    //         123, 123);
    // }
    // auto p4 = t1.time_interval();
    // t1.update();

    // bh::Bstr buf5;
    // for(bh::int32 i = 0; i < sum; i++) {
    //     buf5 =
    //         bh::Bfm("###{}---{}###{}---{}###{}---{}###{}---{}###")(true, false, 100,
    //         200, 3.1415);
    // }
    // auto p5 = t1.time_interval();
    // t1.update();

    vloga("性能测试");
    vlogd($(t1.to_str(p1)));
    vlogd($(t1.to_str(p2)));
    // vlogd($(t1.to_str(p3)));
    // vlogd($(t1.to_str(p4)));
    // vlogd($(t1.to_str(p5)));
    vlogd($(buf1));
    vlogd($(buf2));
    // vlogd($(buf3));
    // vlogd($(buf4));
    // vlogd($(buf5));

    // [Deb]<<<< [t1.to_str(p1): [nan: 3194180180|mic: 3194180|mil: 3194|sec: 3]]
    // [Deb]<<<< [t1.to_str(p2): [nan: 9831876176|mic: 9831876|mil: 9831|sec: 9]]

    // [Deb]<<<< [t1.to_str(p1): [nan: 3061736285|mic: 3061736|mil: 3061|sec: 3]]  
    // [Deb]<<<< [t1.to_str(p2): [nan: 8270601629|mic: 8270601|mil: 8270|sec: 8]]  

}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}