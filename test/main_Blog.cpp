#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>

// #define BHLOG_CLOSE_LOG // 关闭日志
// #define BHLOG_CLOSE_COL // 关闭颜色

#include "Btime.h"
#include "Blog.h"
#include "Bsin.h"

void test_1()
{
    vloga("测试换行输出\n");
    bh::Blog_cmd _cmd;
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_skip;
    _cmd << bh::bhenum::level::e_all << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_all << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_all << "test_4" << bh::bhenum::end::e_skip;
    _cmd << bh::bhenum::level::e_all << "test_5" << bh::bhenum::end::e_flush;
    _cmd << bh::bhenum::level::e_all << "test_6" << bh::bhenum::end::e_blank;
    _cmd << bh::bhenum::level::e_all << "test_7" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_all << 1 << 100 << 3.14 << "hello" << bh::bhenum::end::e_line;
}

void test_2()
{
    vloga("测试输出等级\n");
    vloga("e_all");
    bh::Blog_cmd _cmd;
    _cmd.set_level(bh::bhenum::level::e_all);
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_deb << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_inf << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_war << "test_4" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_err << "test_5" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_fat << "test_6" << bh::bhenum::end::e_line;

    vloga("e_deb");
    _cmd.set_level(bh::bhenum::level::e_deb);
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_deb << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_inf << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_war << "test_4" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_err << "test_5" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_fat << "test_6" << bh::bhenum::end::e_line;

    vloga("e_err");
    _cmd.set_level(bh::bhenum::level::e_err);
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_deb << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_inf << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_war << "test_4" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_err << "test_5" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_fat << "test_6" << bh::bhenum::end::e_line;

    vloga("e_fat");
    _cmd.set_level(bh::bhenum::level::e_fat);
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_deb << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_inf << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_war << "test_4" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_err << "test_5" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_fat << "test_6" << bh::bhenum::end::e_line;
}

void test_3()
{
    vloga("文件长度测试\n");
    int sum = 200 * 10000;
    {
        bh::Blog_file _file("Test_A.log");
        _file->set_length((1ULL << 23));
        for(int i = 0; i < sum; i++) {
            _file << bh::bhenum::level::e_fat << "hello world: " << i << bh::bhenum::end::e_line;
        }
    }
    {
        // 设置最大文件数量
        bh::Blog_file _file("Test_B.log");
        _file->set_length((1ULL << 23));
        _file->set_limit(3);
        for(int i = 0; i < sum; i++) {
            _file << bh::bhenum::level::e_fat << "hello world: " << i << bh::bhenum::end::e_line;
        }
    }
    {
        // 设置文件指向
        bh::Blog_file _file("Test_C.log");
        _file->set_length((1ULL << 23));
        for(int i = 0; i < sum / 2; i++) {
            _file << bh::bhenum::level::e_fat << "hello world: " << i << bh::bhenum::end::e_line;
        }
        _file->reopen("Test_D.log");
        for(int i = sum / 2; i < sum; i++) {
            _file << bh::bhenum::level::e_fat << "hello world: " << i << bh::bhenum::end::e_line;
        }
    }
}

void test_4()
{
    vloga("异步性能测试\n");
    bh::Btimel t1;
    int sum = 200 * 10000;

    t1.update();
    bh::Blog_file _file("F_Test_A.log");
    _file->set_length((1ULL << 23));
    for(int i = 0; i < sum; i++) {
        _file << bh::bhenum::level::e_fat << "hello world: " << i << bh::bhenum::end::e_line;
    }
    auto p1 = t1.time_interval();

    t1.update();
    bh::Blog_asyn _asyn("A_Test_A.log");
    _asyn->set_length((1ULL << 23));
    for(int i = 0; i < sum; i++) {
        _asyn << bh::bhenum::level::e_fat << "hello world: " << i << bh::bhenum::end::e_line;
    }
    auto p2 = t1.time_interval();

    bh::Blog_cmd _cmd;
    _cmd << bh::bhenum::level::e_all << t1.to_str(p1) << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_all << t1.to_str(p2) << bh::bhenum::end::e_line;
}

void test_5()
{
    vloga("颜色打印\n");
    vloga("hello");
    vlogd("hello");
    vlogi("hello");
    vlogw("hello");
    vloge("hello");
    vlogf("hello");

    vloga("直接打印");
    vlogd('a');
    vlogd(123);
    vlogd(123.456);
    vlogd("hello");

    char a1 = 'a';
    int a2 = 123;
    size_t a3 = 123456;
    float a4 = 123.456;
    double a5 = 123.456789;
    char a6[] = "hello";
    const char *a7 = "world";
    std::string a8 = "hello world";

    vloga("变量打印");
    vlogd($(a1));
    vlogd($(a2));
    vlogd($(a3));
    vlogd($(a4));
    vlogd($(a5));
    vlogd($(a6) $(a7) $(a8));
}

void test_6()
{
    bh::Bsin_conf::get()->_file->reopen("TestF1.log");
    vloga("文件打印");
    floga("hello");
    flogd("hello");
    flogi("hello");
    flogw("hello");
    floge("hello");
    flogf("hello");

    bh::Bsin_conf::get()->_asyn->reopen("TestA1.log");
    vloga("异步文件");
    aloga("hello");
    alogd("hello");
    alogi("hello");
    alogw("hello");
    aloge("hello");
    alogf("hello");

    vloga("空打印");
    nloga("hello");
    nlogd("hello");
    nlogi("hello");
    nlogw("hello");
    nloge("hello");
    nlogf("hello");
}

void test_7()
{
    bh::Btimel t1;
    int sum = 100 * 10000;

    vloga("调试打印");
    t1.update();
    for(int i = 0; i < sum; i++) {
        vlogd(i);
    }
    auto p1 = t1.time_interval();

    vloga("文件打印");
    t1.update();
    for(int i = 0; i < sum; i++) {
        flogd(i);
    }
    auto p2 = t1.time_interval();

    vloga("异步打印");
    t1.update();
    for(int i = 0; i < sum; i++) {
        alogd(i);
    }
    auto p3 = t1.time_interval();

    vloga("性能测试结果");
    vlogd(t1.to_str(p1));
    vlogd(t1.to_str(p2));
    vlogd(t1.to_str(p3));

    /*
        [Deb]<<<< [nan: 19376556478|mic: 19376556|mil: 19376|sec: 19]
        [Deb]<<<< [nan: 833558612|mic: 833558|mil: 833|sec: 0]
        [Deb]<<<< [nan: 556108026|mic: 556108|mil: 556|sec: 0]
    */
}

void test_8()
{
    bh::Btimel t1;
    int sum = 1000 * 10000;

    bool a1 = true;
    int a2 = 10;
    size_t a3 = 64;
    double a4 = 6.66;
    std::string a5 = "ss hellow";
    const char *a6 = "cs hellow";

    vloga("空打印测试格式速度");
    t1.update();
    for(int i = 0; i < sum; i++) {
        nlogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6) $(i));
    }
    auto p1 = t1.time_interval();

    vloga("文件打印");
    t1.update();
    for(int i = 0; i < sum; i++) {
        flogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6) $(i));
    }
    auto p2 = t1.time_interval();

    vloga("异步打印");
    t1.update();
    for(int i = 0; i < sum; i++) {
        alogd($(a1) $(a2) $(a3) $(a4) $(a5) $(a6) $(i));
    }
    auto p3 = t1.time_interval();

    vloga("默认打印");
    t1.update();
    char buf[512];
    for(int i = 0; i < sum; i++) {
        std::memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%d %d %d %f %s %s %d %s %d", a1, a2, a3, a4, a5.c_str(), a6, i,
                 __FILE__, __LINE__);
    }
    auto p4 = t1.time_interval();

    vloga("性能测试结果");
    vlogd(t1.to_str(p1));
    vlogd(t1.to_str(p2));
    vlogd(t1.to_str(p3));
    vlogd(t1.to_str(p4));
    vlogd($(buf));

    /*
        [Deb]<<<< [nan: 8424222038|mic: 8424222|mil: 8424|sec: 8]
        [Deb]<<<< [nan: 15198119656|mic: 15198119|mil: 15198|sec: 15]
        [Deb]<<<< [nan: 10206193338|mic: 10206193|mil: 10206|sec: 10]
        [Deb]<<<< [nan: 2455783810|mic: 2455783|mil: 2455|sec: 2]
    */
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    // test_3();
    // test_4();
    test_5();
    test_6();
    // test_7();
    // test_8();

    return 0;
}
