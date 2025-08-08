
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "bhtools.h"


void test_1()
{
    // 线性时间
    bhtools::Ftimel t1;

    {
        std::string s1 = t1.to_string();
        bhtools::Ftimel::sleep(1000);

        std::string s2 = t1.to_string();
        vlogd($(s1) $(s2));
    }
    {
        std::string s1 = t1.to_string();
        t1.update();

        std::string s2 = t1.to_string();
        vlogd($(s1) $(s2));
    }
    {
        auto s1 = t1.time_interval();
        bhtools::Ftimel::sleep(1000);
        auto s2 = t1.time_interval();
        auto s3 = s2 - s1;
        vlogd($(t1.to_string(s3)));
    }
    {
        bhtools::Ftimel t2;
        bhtools::Ftimel::sleep(1000);
        vlogd($(t2.to_string()));
    }
    {
        bhtools::Ftimel t3;

        bhtools::Ftimel::sleep(100);
        t3.push_point("t1");

        bhtools::Ftimel::sleep(100);
        t3.push_point("t2");

        bhtools::Ftimel::sleep(100);
        t3.push_point("t3");

        bhtools::Ftimel::sleep(100);
        t3.push_point("t4");

        vlogd($C(t3.check_vec()));
    }

    {
        bhtools::Ftimel t3;

        bhtools::Ftimel::sleep(100);
        t3.push_point("t1",true);

        bhtools::Ftimel::sleep(100);
        t3.push_point("t2",true);

        bhtools::Ftimel::sleep(200);
        t3.push_point("t3",true);

        bhtools::Ftimel::sleep(300);
        t3.push_point("t4",true);

        vlogd($C(t3.check_vec()));
    }
}


void test_2()
{
    // 系统时间
    bhtools::Ftimes t1;

    {
        // 注意UTC时区问题
        auto s1 = t1.to_string(t1.to_data(t1.time_now()));
        auto s2 = t1.to_string();
    
        vlogd($(s1) $(s2));
    }
    {
        auto s1 = t1.to_string();
        bhtools::Ftimel::sleep(1000);
        auto s2 = t1.to_string();
    
        vlogd($(s1) $(s2));
    }
    {
        auto d = t1.to_data(t1.time_now());
        d.hou += 8;

        auto s1 = t1.format_time(d);
        auto s2 = t1.format_time(d,"%2Y-%2M-%2D.%2H:%2T:%2S");
        auto s3 = t1.format_time(t1.to_data());
        auto s4 = t1.to_ctime();

        vlogd($(s1) $(s2));
        vlogd($(s3) $(s4));
    }
}


int main(int argc, char *argv[])
{
    // test_1();
    test_2();


    return 0;
}