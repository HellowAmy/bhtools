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

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}