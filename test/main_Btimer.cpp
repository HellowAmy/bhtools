#include <iostream>
#include <atomic>

#include "Btimer.h"
#include "Btype.h"
#include "Btest.h"
#include "Btime.h"

void test_1()
{
    bh::Btimel ts1;
    bh::Btimer<> t1;

    bh::uint32 a1 = 0;
    bh::uint32 a2 = 0;
    bh::uint32 a3 = 0;

    vloga("定时触发\n");
    bh::uint32 id1 = t1.push(
        300,
        [&](bh::uint32 id) {
            a1++;
            vlogd("id1 " $(ts1.to_str()));
        },
        0);

    bh::uint32 id2 = t1.push(200, [&](bh::uint32 id) {
        a2++;
        vlogd("id2 " $(ts1.to_str()));
    });

    bh::uint32 id3 = t1.push(
        100,
        [&](bh::uint32 id) {
            a3++;
            vlogd("id3 " $(ts1.to_str()));
        },
        5);

    bh::Btimel::sleep(1 * 1000);
    t1.close();

    vloga("关闭 " $(ts1.to_str()));
    vloga("次数验证");
    BHTEST_EQUAL(a1, 3);
    BHTEST_EQUAL(a2, 1);
    BHTEST_EQUAL(a3, 5);
}

void test_2()
{
    bh::Btimer<2, 100> t1;
    bh::Btimer<2, 20> t2;

    bh::Btimel ts1;
    bh::uint32 a1 = 0;
    bh::uint32 a2 = 0;

    bh::uint32 id1 = t1.push(
        500,
        [&](bh::uint32 id) {
            a1++;
            vloga("id1 " $(ts1.to_str()));
        },
        0);

    bh::uint32 id2 = t2.push(
        100,
        [&](bh::uint32 id) {
            a2++;
            vlogd("id2 " $(ts1.to_str()));
        },
        0);

    bh::Btimel::sleep(1 * 1100 + 50);
    t1.close();

    vloga("关闭 " $(ts1.to_str()));
    vloga("不同速度循环间隔\n");
    BHTEST_EQUAL(a1, 2000);
    BHTEST_EQUAL(a2, 10);
}

void test_3()
{
    bh::Btimer<8> t1;
    bh::Btimer<8> t2;

    bh::Btimel ts1;

    std::atomic<int> at1(0);
    bh::uint32 a1 = 0;
    bh::uint32 a2 = 0;

    bh::uint32 id1 = t1.push(
        100,
        [&](bh::uint32 id) {
            a1++;
            at1++;
            vloga("id1 " $(ts1.to_str()));
        },
        0);
    bh::uint32 id2 = t1.push(
        100,
        [&](bh::uint32 id) {
            a1++;
            at1++;
            vloga("id2 " $(ts1.to_str()));
        },
        0);
    bh::uint32 id3 = t1.push(
        100,
        [&](bh::uint32 id) {
            a1++;
            at1++;
            vloga("id3 " $(ts1.to_str()));
        },
        0);

    bh::uint32 id4 = t2.push(
        100,
        [&](bh::uint32 id) {
            a2++;
            vlogd("id4 " $(ts1.to_str()));
        },
        0);

    bh::Btimel::sleep(1 * 1100 + 50);
    t1.close();

    vloga("关闭 " $(ts1.to_str()));
    vloga("多线程处理\n");
    BHTEST_EQUAL(at1.load(), 30);
    BHTEST_EQUAL(a1, 30);
    BHTEST_EQUAL(a2, 10);
}

void test_4()
{
    bh::Btimel ts1;
    bh::Btimer<> t1;

    bh::uint32 a1 = 0;
    bh::uint32 a2 = 0;
    bh::uint32 a3 = 0;

    vloga("移除测试\n");
    bh::uint32 id1 = t1.push(
        100,
        [&](bh::uint32 id) {
            a1++;
            vlogd("id1 " $(ts1.to_str()));
        },
        0);

    bh::uint32 id2 = t1.push(
        150,
        [&](bh::uint32 id) {
            a2++;
            vlogd("id2 " $(ts1.to_str()));
        },
        0);

    bh::uint32 id3 = t1.push(
        200,
        [&](bh::uint32 id) {
            a3++;
            vlogd("id3 " $(ts1.to_str()));
        },
        5);

    bh::Btimel::sleep(500 + 20);
    t1.remove(id1);
    t1.remove(id3);
    vloga("移除 " $(id1) $(id3) $(t1.is_run()));

    bh::Btimel::sleep(500 + 20);
    t1.close();
    vloga("关闭 " $(ts1.to_str()) $(t1.is_run()));

    vloga("次数验证");
    BHTEST_EQUAL(a1, 4);
    BHTEST_EQUAL(a2, 6);
    BHTEST_EQUAL(a3, 2);
}

void test_5()
{
    using namespace std::chrono;
    bh::Btimel ts1;
    bh::Btimer<> t1;
    milliseconds ms1(0);

    vloga("下一个任务间隔\n");
    bh::uint32 id1 = t1.push(
        milliseconds(100),
        [&](bh::uint32 id) {
            static int count = 0;
            count++;
            auto a1 = duration_cast<milliseconds>(ts1.time_interval()).count() - count * 100;

            ms1 += milliseconds(a1);
            vlogd("id1 " $(ts1.to_str()) $(a1));
        },
        0);
    bh::Btimel::sleep(1 * 1000);
    t1.close();

    vloga("误差计算\n");
    vlogd($(ms1.count()));
}

void test_6()
{
    vloga("长定时任务\n");

    vloga("10分钟检查一次");
    using namespace std::chrono;
    bh::Btimel ts1;
    bh::Btimer<8, 10, minutes> t1;
    milliseconds ms1(0);

    vloga("1小时触发一次");
    bh::uint32 id1 = t1.push(
        hours(1),
        [&](bh::uint32 id) {
            static int count = 0;
            count++;
            auto a1 = duration_cast<milliseconds>(ts1.time_interval()).count() - count * 100;
            ms1 += milliseconds(a1);
            vlogd("id1 " $(ts1.to_str()) $(a1));
        },
        0);
    bh::Btimel::sleep(10 * 1000);
    t1.close();

    vloga("误差计算\n");
    vlogd($(ms1.count()));
}

int main(bh::int32 argc, char *argv[])
{
    // test_1();
    // test_2();
    // test_3();
    // test_4();
    test_5();
    // test_6();

    return 0;
}
