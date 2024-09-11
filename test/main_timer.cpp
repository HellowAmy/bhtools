

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <sstream>

#include "Tlog.h"
#include "Ttimer.h"
#include "Ftime.h"

#include "unistd.h"



using namespace bhtools;


void test_1()
{
    Ttimer<> ti;
    size_t tid1 = ti.push(1000,[&](size_t id){
        vlogd($("mil: 1000"));
    });

    size_t tid2 = ti.push(2000,[&](size_t id){
        vlogd($("mil: 2000"));
    });

    size_t tid3 = ti.push(3000,[&](size_t id){
        vlogd($("mil: 3000"));
    });

    size_t tid4 = ti.push(4000,[&](size_t id){
        vlogd($("mil: 4000"));
    });

    size_t tid5 = ti.push(100,[&](size_t id){
        vlogd($("mil: 100"));
    });

    ti.push(200,[&](size_t id){
        static int i = 0;
        i++;
        vlogd($("mil: 200") $(i));
        if(i > 20)
        {
            ti.remove(id);
        }



    },0);

    sleep(1);
    ti.remove(tid3);

    sleep(100);
}

void test_2()
{
    {
        vlogi("=====");
        Ttimer<> ti;
        size_t tid1 = ti.push(200,[&](size_t id){
            vlogd($("mil: 200"));
            vlogd($S(std::this_thread::get_id()));

        },0);

        sleep(5);
    }
    {
        vlogi("=====");
        Ttimer<std::chrono::milliseconds,20,4> ti;
        size_t tid1 = ti.push(300,[&](size_t id){
            vlogd($("mil: 300"));
            vlogd($S(std::this_thread::get_id()));
        },0);

        sleep(5);
    }
    {
        vlogi("=====");
        Ttimer<std::chrono::milliseconds,20,1> ti;
        size_t tid1 = ti.push(400,[&](size_t id){
            vlogd($("mil: 400"));
            vlogd($S(std::this_thread::get_id()));
        },0);

        sleep(5);
    }

    sleep(50);
    vlogi("===== end =====");

}

void test_3()
{
    
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,20,2> ti;
        size_t tid1 = ti.push(200,[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,50,2> ti;
        size_t tid1 = ti.push(200,[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,100,2> ti;
        size_t tid1 = ti.push(200,[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,200,2> ti;
        size_t tid1 = ti.push(200,[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,500,2> ti;
        size_t tid1 = ti.push(200,[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
}

void test_4()
{
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::seconds,1,2> ti;
        size_t tid1 = ti.push(3,[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(10);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::nanoseconds,100,2> ti;
        size_t tid1 = ti.push(500,[&](size_t id){
            vlogd($(t.to_string()) $(ti._heap.size_node()) );
            t.update();
        },0);
        sleep(10);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,200,2> ti;
        size_t tid1 = ti.push(300,[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(10);
    }

}

void test_5()
{
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,50,2> ti;
        size_t tid1 = ti.push(std::chrono::seconds(1),[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::milliseconds,50,2> ti;
        size_t tid1 = ti.push(std::chrono::milliseconds(100),[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::nanoseconds,500,2> ti;
        size_t tid1 = ti.push(std::chrono::microseconds(1000),[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }
    {
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::microseconds,100,2> ti;
        size_t tid1 = ti.push(std::chrono::milliseconds(1),[&](size_t id){
            vlogd($(t.to_string()));
            t.update();
        },0);
        sleep(5);
    }

}

void test_6()
{
    {
        int count = 0;
        vlogi("=====");
        Ftimel t;
        Ttimer<std::chrono::microseconds,100,2> ti;
        size_t tid1 = ti.push(std::chrono::milliseconds(1),[&](size_t id){
            auto s1 = t.time_interval();
            auto data = t.to_data(s1);
            if(data.mic > 1100 || data.mic < 900)
            {
                vlogw($("====="));
                count++;
            }
            else 
            {
                vlogd($(t.to_string(s1)));    
            }
            t.update();

        },0);
        sleep(30);
        vlogd($(count));     // 5253
    }
}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    test_6();

    return 0;
}