
#include <iostream>
#include <sstream>

#include "bhtools.h"

void test_1()
{
    // 不同定时时间
    bhtools::Ttimer<> t1;
    bhtools::Ftimel tt1;
    bhtools::Ftimel tt2;
    bhtools::Ftimel tt3;

    vlogd($(tt1.to_string()));
    vlogi($(tt2.to_string()));
    vlogw($(tt3.to_string()));

    // 无限次
    size_t id1 = t1.push(2000,[&](size_t id){
        vlogd("id1: " << $(tt1.to_string()));
    },0);

    // 默认1次
    size_t id2 = t1.push(1000,[&](size_t id){
        vlogi("id2: " << $(tt2.to_string()));
    });

    // 5次
    size_t id3 = t1.push(500,[&](size_t id){
        vlogw("id3: " << $(tt3.to_string()));
    },5);


    bhtools::Ftimel::sleep(10 * 1000);

    vlogd($(id1) $(id2) $(id3));
}

void test_2()
{
    // 设置为微妙和秒为检查的定时器间隔
    bhtools::Ttimer<std::chrono::milliseconds,5> t1;
    bhtools::Ttimer<std::chrono::seconds,1> t2;
    bhtools::Ftimel tt1;
    bhtools::Ftimel tt2;

    vlogd($(tt1.to_string()));
    vlogi($(tt2.to_string()));

    // 无限次
    size_t id1 = t1.push(200,[&](size_t id){
        vlogd("id1: " << $(tt1.to_string()));
        tt1.update();
    },20);

    size_t id2 = t2.push(4,[&](size_t id){
        vlogi("id2: " << $(tt2.to_string()));
    },5);

    bhtools::Ftimel::sleep(10 * 1000);

    vlogd($(id1) $(id2));
}

void test_3()
{
    // 停止定时任务
    bhtools::Ttimer<> t1;
    bhtools::Ftimel tt1;

    vlogd($(tt1.to_string()));

    // 无限次
    size_t id1 = t1.push(200,[&](size_t id){
        vlogd("id1: " << $(tt1.to_string()));
    },0);

    bhtools::Ftimel::sleep(2 * 1000);

    bool ok = t1.remove(id1);
    vlogd($(ok));

    bhtools::Ftimel::sleep(2 * 1000);

    t1.close_timer();
    vlogd($(t1.is_run()));

    bhtools::Ftimel::sleep(1 * 1000);

    vlogd("end");
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   

    return 0;
}