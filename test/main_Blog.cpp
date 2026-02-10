#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>

#include "Btime.h"
#include "Blog.h"
#include "Bsin.h"

void test_1()
{
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
    bh::Blog_cmd _cmd;
    _cmd.set_level(bh::bhenum::level::e_all);
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_deb << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_inf << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_war << "test_4" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_err << "test_5" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_fat << "test_6" << bh::bhenum::end::e_line;

    _cmd.set_level(bh::bhenum::level::e_deb);
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_deb << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_inf << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_war << "test_4" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_err << "test_5" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_fat << "test_6" << bh::bhenum::end::e_line;

    _cmd.set_level(bh::bhenum::level::e_err);
    _cmd << bh::bhenum::level::e_all << "test_1" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_deb << "test_2" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_inf << "test_3" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_war << "test_4" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_err << "test_5" << bh::bhenum::end::e_line;
    _cmd << bh::bhenum::level::e_fat << "test_6" << bh::bhenum::end::e_line;

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
    int sum = 200 * 10000;
    {
        // 设置最大长度
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
    bh::Btimel t1;
    int sum = 1000 * 10000;

    for(int i = 0; i < sum; i++) {
        auto s1 = bh::Blog_time::print();
    }

    bh::Blog_cmd _cmd;
    _cmd << bh::bhenum::level::e_all << t1.to_str() << bh::bhenum::end::e_line;
}

int main(bh::int32 argc, char *argv[])
{
    // test_1();
    // test_2();
    // test_3();
    // test_4();
    test_5();

    return 0;
}
