#include <iostream>

#include "Btime.h"

#include "Ftest.h"

void test_1()
{
    bh::Btimel t1;
    auto p1 = t1.time_interval();

    bh::Btimel::sleep(100);
    auto p2 = t1.time_interval();

    t1.update();
    auto p3 = t1.time_interval();

    vloga("时间间隔");
    vlogd($(t1.to_str(p1)));
    vlogd($(t1.to_str(p2)));
    vlogd($(t1.to_str(p3)));
}

void test_2()
{
    bh::Btimes t1;
    auto p1 = t1.time_now();
    auto d1 = t1.to_data(p1);
    auto s1 = t1.format_time(d1);
    auto s2 = t1.format_time(d1, "YY-MM-DD.HH:TT:SS.LLL.CCC");

    bh::Btimel::sleep(100);
    auto s3 = t1.to_str();
    auto s4 = t1.to_str(0);

    vloga("时间格式");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
}

void test_3()
{
    bh::Btimes t1;
    auto p1 = t1.time_now();
    auto d1 = t1.to_data(p1);
    auto p2 = t1.from_data(d1);

    bh::Btimes::data d2{0};
    d2.yea = 2022;
    d2.mon = 7;
    d2.day = 15;
    d2.hou = 11;
    d2.min = 45;
    d2.sec = 30;
    auto p3 = t1.from_data(d2);
    auto d3 = t1.to_data(p3);

    bh::Btimes::data d4{0};
    d4.yea = 1850;
    d4.mon = 7;
    d4.day = 15;
    d4.hou = 11;
    d4.min = 45;
    d4.sec = 30;
    d4.mil = 100;
    d4.mic = 200;
    d4.nan = 300;
    auto p4 = t1.from_data(d4);
    auto d5 = t1.to_data(p4);

    vloga("日期逆向运算");
    vlogd($(t1.format_time(d1)));
    BHTEST_EQUAL(p1.count(), p2.count());

    vloga("指定日期");
    vlogd($(t1.format_time(d2)));
    vlogd($(t1.format_time(d3)));
    vlogd($(p3.count()));

    vloga("公元前");
    vlogd($(t1.format_time(d4)));
    vlogd($(t1.format_time(d5)));
    vlogd($(p4.count()));
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    test_3();

    return 0;
}