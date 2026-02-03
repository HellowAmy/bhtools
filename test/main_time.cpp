
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

    // {
    //     // 注意UTC时区问题
    //     auto s1 = t1.to_string(t1.to_data(t1.time_now()));
    //     auto s2 = t1.to_string();
    
    //     vlogd($(s1) $(s2));
    // }
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

void test_3()
{
    int sum = 5000*10000;
    bhtools::Ftimel tt;
    
    {
        bhtools::Ftimes ft;
        for(int i=0;i<100*10000;i++)
        {
            ft.to_ctime();
        }
        tt.push_point("to_ctime ",true);
    }
    {
        bhtools::Ftimes ftrr;
        auto p = ftrr.time_now();
        bhtools::Ftimes ft;
        for(int i=0;i<sum;i++)
        {
            ft.to_data(p);
        }

        tt.push_point("to_data ",true);
        vlogd($C(tt.check_vec()));
        // vlogd(ft.to_string(ft.to_data(p)));
    }


    /*
        [Deb]<<<< [tt.check_vec(): 
        | size: 1
        | to_data  [nan: 1681911597|mic: 1681911|mil: 1681|sec: 1] 
        ]  >>>>[/home/red/open/github/bhtools/test/main_time.cpp:139][2026-02-02.19:32:26.295]
    */
}

void test_4()
{
    bhtools::Ftimes t1;
    {
        bhtools::Ftimel tff;
        int sum = 1000*10000;

        auto d = t1.to_data(t1.time_now());
        d.hou += 8;

        // t1.format_time2(d);

        tff.push_point("t1",true);

        for(int i=0;i<sum;i++)
        {
            t1.format_time(d);
        }
        tff.push_point("t3",true);

        vlogd($C(tff.check_vec()));
        vlogd(t1.to_string());
    }

}

int main(int argc, char *argv[])
{
    // test_1();
    // test_2();
    // test_3();
    test_4();


    return 0;
}