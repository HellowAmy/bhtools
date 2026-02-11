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

    vloga("间隔显示测试\n");
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
    auto s5 = t1.to_ctime();

    vloga("格式测试\n");
    vloga("时间格式");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
    vlogd($(s5));
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

    vloga("日期逆向测试\n");
    vloga("逆向计算");
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

void test_4()
{
    int sum = 1000 * 10000;
    bh::Btimel t1;
    bh::Btimefms ts1;

    std::chrono::nanoseconds one_day_ns = std::chrono::hours(24);

    bh::Btimes::data d1{0};
    d1.yea = 1850;
    d1.mon = 7;
    d1.day = 15;
    d1.hou = 11;
    d1.min = 45;
    d1.sec = 30;
    d1.mil = 100;
    d1.mic = 200;
    d1.nan = 300;
    auto p1 = ts1.from_data(d1);
    auto p2 = ts1.from_data(d1);
    auto p3 = ts1.from_data(d1);

    t1.update();
    bh::dstr ss1;
    for(int i = 0; i < sum; i++) {
        p1 += one_day_ns;
        ss1 = ts1.format_time(ts1.to_data(p1));
    }
    auto tt1 = t1.time_interval();

    t1.update();
    bh::dstr ss2;
    for(int i = 0; i < sum; i++) {
        p2 += one_day_ns;
        ss2 = ts1.get_datetime(p2).to_str();
    }
    auto tt2 = t1.time_interval();

    t1.update();
    bh::dstr ss3;
    for(int i = 0; i < sum; i++) {
        // p3 += one_day_ns;
        ss3 = ts1.get_datetime(p3).to_str();
    }
    auto tt3 = t1.time_interval();

    t1.update();
    bh::dstr ss4;
    ts1.set_format("HH:TT:SS.LLL");
    for(int i = 0; i < sum; i++) {
        ss4 = ts1.get_datetime(p3).to_str();
    }
    auto tt4 = t1.time_interval();

    vloga("性能测试\n");
    vlogd($(t1.to_str(tt1)));
    vlogd($(t1.to_str(tt2)));
    vlogd($(t1.to_str(tt3)));
    vlogd($(t1.to_str(tt4)));
    vlogd($(ss1));
    vlogd($(ss2));
    vlogd($(ss3));
    vlogd($(ss4));

    /*
        [All]<<<< 性能测试
        [Deb]<<<< [t1.to_str(tt1): [nan: 4560358410|mic: 4560358|mil: 4560|sec: 4]]
        [Deb]<<<< [t1.to_str(tt2): [nan: 1454485026|mic: 1454485|mil: 1454|sec: 1]]
        [Deb]<<<< [t1.to_str(tt3): [nan: 891818065|mic: 891818|mil: 891|sec: 0]]
        [Deb]<<<< [t1.to_str(tt4): [nan: 637329481|mic: 637329|mil: 637|sec: 0]]
        [Deb]<<<< [ss1: 1755-07-26.07:41:05.751.274.348]
        [Deb]<<<< [ss2: 1755-07-26.15:41:05.751.274.348]
        [Deb]<<<< [ss3: 1850-07-15.19:45:30.100.200.300]
        [Deb]<<<< [ss4: 19:45:30.100]
    */
}

void test_5()
{
    bh::Btimefms ts1;

    bh::dstr s1 = ts1.cur_datetime().to_str(); // YYYY-MM-DD.HH:TT:SS.LLL.CCC.NNN

    ts1.set_format("YYYY-MM-DD.HH:TT:SS.LLL.CCC.NNN");
    bh::dstr s2 = ts1.cur_datetime().to_str();

    ts1.set_format("YY-MM-DD.HH:TT:SS.LLL.CCC.NNN");
    bh::dstr s3 = ts1.cur_datetime().to_str();

    ts1.set_format("HH:TT:SS.LLL");
    bh::dstr s4 = ts1.cur_datetime().to_str();

    vloga("格式打印");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
}

int main(int argc, char *argv[])
{
    //
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();

    return 0;
}