// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "Tlog.h"
#include "Ffm.h"
#include "Ftime.h"

void test_1()
{
    // 颜色打印
    vlogd("vlogd");
    vlogi("vlogi");
    vlogw("vlogw");
    vloge("vloge");

    // 打印变量
    bool a1 = true;
    int a2 = 10;
    size_t a3 = 64;
    double a4 = 6.66;
    std::string a5 = "ss hellow";
    const char *a6 = "cs hellow";
    vlogd(a1 << a2 << a3 << a4 << a5 << a6);

    //带变量名称打印
    vlogi($(a1) $(a2) $(a3) $(a4) $(a5) $(a6));

    // 容器打印
    std::vector<int> vec;
    std::map<int,std::string> mp;
    for(int i=0;i<10;i++)
    {
        std::string val = bhtools::Fffm("index{}")(i);
        vec.push_back(i);
        mp.emplace(i,val);
    }
    vlogd($C(vec));
    vlogd($C(mp));
}

void test_2()
{
    // 设置日志
    auto log = bhtools::Tsin_log_conf::get();
 
    // 无效打印
    nlogd("nlogd");
    nlogi("nlogi");
    nlogw("nlogw");
    nloge("nloge");

    // 文件打印
    flogd("flogd");
    flogi("flogi");
    flogw("flogw");
    floge("floge");

    // 异步文件打印
    alogd("alogd");
    alogi("alogi");
    alogw("alogw");
    aloge("aloge");
    
    // 异步文件打印换文件,退出时刷入文件
    log->exit_flush_afile();
    log->reopen(log->_afile,"Talogv2.log",true);
    alogd("alogdv2");
    alogi("alogiv2");
    alogw("alogwv2");
    aloge("alogev2");
    
    // 刷新异步日志到文件,否则程序退出时会丢失日志
    log->exit_flush_afile();

    // 文件等级打印
    log->set_level(log->_file,bhtools::bhenum::level::e_war);
    log->set_level(log->_afile,bhtools::bhenum::level::e_war);
    log->set_level(log->_cmd,bhtools::bhenum::level::e_war);

    flogd("flogd level");
    flogi("flogi level");
    flogw("flogw level");
    floge("floge level");
 
    vlogd("vlogd level");
    vlogi("vlogi level");
    vlogw("vlogw level");
    vloge("vloge level");

    alogd("alogdv2 level");
    alogi("alogiv2 level");
    alogw("alogwv2 level");
    aloge("alogev2 level");

    log->exit_flush_afile();
}

void test_3()
{
    // 设置文件最大长度,无限制
    auto log = bhtools::Tsin_log_conf::get();
    log->set_length(log->_file,(1 << 16));

    log->reopen(log->_file,"Tlogv2.log",true);
    log->set_limit(log->_file,0);
    
    int num = 10000;
    for(int i=0;i<num;i++)
    {
        flogd("flogdlevel v2 " << bhtools::Fffm("{}")(i));
    }

    // 5文件限制
    log->reopen(log->_file,"Tlogv3.log",true);
    log->set_limit(log->_file,5);

    for(int i=0;i<num;i++)
    {
        flogd("flogdlevel v3 " << bhtools::Fffm("{}")(i));
    }

    // 1文件限制
    log->reopen(log->_file,"Tlogv4.log",true);
    log->set_limit(log->_file,1);

    for(int i=0;i<num;i++)
    {
        flogd("flogdlevel v4 " << bhtools::Fffm("{}")(i));
    }

    // 异步
    log->reopen(log->_afile,"Talogv3.log",true);
    log->set_length(log->_afile,(1 << 16));
    log->set_limit(log->_afile,1);

    for(int i=0;i<num;i++)
    {
        alogd("alogdlevel v3 " << bhtools::Fffm("{}")(i));
    }
    log->exit_flush_afile();

    log->reopen(log->_afile,"Talogv4.log",true);
    log->set_limit(log->_afile,5);
    for(int i=0;i<num;i++)
    {
        alogd("alogdlevel v4 " << bhtools::Fffm("{}")(i));
    }
    log->exit_flush_afile();
}

void test_4()
{
    // 性能测试
    using namespace bhtools;

    bhtools::Ftimel t1;
    int num = 50*10000;
    bool a1 = true;
    int a2 = 10;
    size_t a3 = 64;
    double a4 = 6.66;
    std::string a5 = "ss hellow";
    const char *a6 = "cs hellow";

    t1.push_point("begin",true);
    for(int i=0;i<num;i++)
    {
        vlogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6) $(i));
    }
    t1.push_point("time1",true);
    
    for(int i=0;i<num;i++)
    {
        nlogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6) $(i));
    }
    t1.push_point("time2",true);

    for(int i=0;i<num;i++)
    {
        flogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6) $(i));
    }
    t1.push_point("time3",true);

    for(int i=0;i<num;i++)
    {
        alogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6) $(i));
    }
    t1.push_point("time4",true);

    vlogd($C(t1.check_vec()));

    /*
        [Deb]<<<< [t1.check_vec(): 
        | size: 5
        | begin [nan: 1611|mic: 1|mil: 0|sec: 0] 
        | time1 [nan: 21748766152|mic: 21748766|mil: 21748|sec: 21] 
        | time2 [nan: 760231027|mic: 760231|mil: 760|sec: 0] 
        | time3 [nan: 1526813941|mic: 1526813|mil: 1526|sec: 1] 
        | time4 [nan: 1210863417|mic: 1210863|mil: 1210|sec: 1] 
        ]  >>>>[/home/red/open/github/bhtools/test/main_log.cpp:198][2025-08-05.15:02:01.403]
    */
}

int main(int argc, char *argv[])
{
    // test_1();
    // test_2();
    // test_3();
    test_4();

    return 0;
}