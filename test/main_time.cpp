

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "Ftime.h"
#include "Tlog.h"

using namespace bhtools;


void test_1()
{
    auto fndata = [](Ftimel::data d){
        vlogd($(d.nan) $(d.mic) $(d.mil) $(d.sec));
    };


    {
        vlogd("<<<< 1");
        Ftimel t;
        fndata( t.to_data(t.time_interval()));
        int count = 0;
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        fndata( t.to_data(t.time_interval()));
    }
    {
        vlogd("<<<< 2");
        Ftimel t;
        int count = 0;
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        vlogd(t.to_string());
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        vlogd(t.to_string(t.time_interval()));
    }
    {
        vlogd("<<<< 3");
        Ftimel t;
        int count = 0;
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        auto t1 = t.time_interval();

        for(int i=0;i<10000;i++)
        {
            count++;
        }
        auto t2 = t.time_interval();

        vlogd(t.to_string(t1));
        vlogd(t.to_string(t2));
    }
    {
        vlogd("<<<< 4");
        Ftimel t;
        int count = 0;
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        auto t1 = t.time_interval();
        t.update();

        for(int i=0;i<10000;i++)
        {
            count++;
        }
        auto t2 = t.time_interval();

        vlogd(t.to_string(t1));
        vlogd(t.to_string(t2));
    }
    {
        vlogd("<<<< 5");
        Ftimel t;
        t.push_point("begin",true,true);
        int count = 0;
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t1");

        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t2");

        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t3");

        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t4");

        vlogd(Tlog_con(t.check_vec(),1));
    }
    {
        vlogd("<<<< 6");
        Ftimel t;
        t.push_point("begin",true,true);
        int count = 0;
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t1");

        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t2");
        vlogd(Tlog_con(t.check_vec(),1));

        t.push_point("begin",true,true);
        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t3");

        for(int i=0;i<10000;i++)
        {
            count++;
        }
        t.push_point("t4");

        vlogd(Tlog_con(t.check_vec(),1));
    }

}

void test_2()
{
    {
        vlogd("<<<< 1");
        Ftimel t;
        sleep(1);
        vlogd($(t.to_string()));
    }

    {
        vlogd("<<<< 2");
        Ftimel t;
        sleep(2);
        vlogd($(t.to_string()));
    }

    {
        vlogd("<<<< 3");
        Ftimel t;
        usleep(1000);
        vlogd($(t.to_string()));
    }

    {
        vlogd("<<<< 4");
        Ftimel t;
        usleep(300);
        vlogd($(t.to_string()));
    }

    {
        vlogd("<<<< 5");
        Ftimel t;
        usleep(100);
        vlogd($(t.to_string()));

        usleep(100);
        vlogd($(t.to_string()));

        usleep(100);
        vlogd($(t.to_string()));
    }

    {
        vlogd("<<<< 6");
        Ftimel t;
        usleep(100);
        t.push_point();

        usleep(100);
        t.push_point();

        usleep(100);
        t.push_point();

        vlogd($C(t.check_vec()));
    }

    {
        vlogd("<<<< 7");
        Ftimel t;
        usleep(100);
        auto t1 = t.time_interval();

        usleep(100);
        auto t2 = t.time_interval();

        usleep(100);
        auto t3 = t.time_interval();

        vlogd($(t.to_string(t1))  $(t.to_string(t2)) $(t.to_string(t3)));
    }

    {
        vlogd("<<<< 8");
        Ftimel t;
        usleep(10000);
        auto t1 = t.time_interval();

        usleep(10000);
        auto t2 = t.time_interval();

        usleep(10000);
        auto t3 = t.time_interval();

        vlogd($(t.to_string(t1))  $(t.to_string(t2)) $(t.to_string(t3)));
    }

    {
        vlogd("<<<< 9");
        Ftimel t;
        usleep(10000);
        t.push_point();

        usleep(10000);
        t.push_point();

        usleep(10000);
        t.push_point();

        vlogd($C(t.check_vec()));
    }
} 

void test_3()
{
    {
        Ftimes t;
        auto d = t.to_data(t.time_now());
        vlogd($(d.yea) $(d.mon) $(d.day) $(d.hou) $(d.min) $(d.sec) $(d.mil) $(d.mic) $(d.nan));
    }
    {
        Ftimes t;
        auto s1 = t.to_string();
        auto s2 = t.to_ctime();
        vlogd($(s1) $(s2));
    }
}

void test_4()
{
    {
        vlogd($(Ftimes::to_string()));
    }
    {
        Ftimes t;
        auto tt = t.time_now();
        auto t1 = t.to_data(tt);
        auto s1 = t.format_time(t1);
        auto s2 = t.to_string(tt,8);
        vlogd($(s1) $(s2));
    }
    {
        Ftimes t;
        auto tt = t.time_now();
        auto t1 = t.to_data(tt);
        auto s13 = t.format_time(t1);
        auto s11 = t.format_time(t1,"%2Y-%2M-%2D.%2H:%2T:%2S.%2L.%2C.%3N");
        auto s2 = t.to_string(tt,8);
        vlogd($(s13) $(s11));
    }
}

void test_5()
{
    int sum = 10000000;
    {
        Ftimel t;
        for(int i=0;i<sum;i++)
        {
            auto t1 = Ftimes::time_now();
            auto t2 = Ftimes::to_data(t1);
            t2.hou += 8;
            auto s1 = Ftimes::format_time(t2);
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
    {
        Ftimel t;
        for(int i=0;i<sum;i++)
        {
            auto t1 = Ftimes::to_ctime();
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
    {
        Ftimel t;
        for(int i=0;i<sum;i++)
        {
            std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm *m = std::localtime(&t);
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
    {
        Ftimel t;
        for(int i=0;i<sum;i++)
        {
            std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm *m = std::localtime(&t);
            char buffer[80];
            std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", m);
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
    {
        Ftimel t;
        for(int i=0;i<sum;i++)
        {
            auto t1 = Ftimes::time_now();
            Ftimes::to_string();
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
}

int main(int argc, char *argv[])
{


    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    test_5();
    // test_6();

    return 0;
}