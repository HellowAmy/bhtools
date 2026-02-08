#include <iostream>
#include <atomic>

#include "Btimer.h"
#include "Btype.h"
#include "Btest.h"
#include "Btime.h"

void test_1()
{
    vloga("Btimer 基础触发与次数限制测试 (参考 main_timer::test_1)");
    bh::Btimer<> timer;

    std::atomic<bh::int32> count1{0};
    std::atomic<bh::int32> count2{0};
    std::atomic<bh::int32> count3{0};

    vloga("推入任务1：2000ms触发，无限循环(active=0)");
    bh::uint64 id1 = timer.push(
        2000,
        [&](bh::uint64 id) {
            count1++;
            vlogd("任务1触发一次");
        },
        0);

    vloga("推入任务2：1000ms触发，默认执行1次");
    bh::uint64 id2 = timer.push(1000, [&](bh::uint64 id) {
        count2++;
        vlogd("任务2触发一次");
    });

    vloga("推入任务3：500ms触发，执行5次");
    bh::uint64 id3 = timer.push(
        500,
        [&](bh::uint64 id) {
            count3++;
            vlogd("任务3触发一次");
        },
        5);

    vloga("主线程计时等待 6s 以覆盖所有任务周期");
    bh::Btimel::sleep(6000);

    vloga("结果数据校验");
    vlogd($(count1.load()) $(count2.load()) $(count3.load()));

    BHTEST_TRUE((count1.load() >= 2)); // 6s内至少触发2-3次
    BHTEST_EQUAL(count2.load(), 1);
    BHTEST_EQUAL(count3.load(), 5);
}

void test_2()
{
    vloga("Btimer 自定义时间单位与检查间隔测试 (参考 main_timer::test_2)");

    // 毫秒级检查间隔(5ms)
    bh::Btimer<std::chrono::milliseconds, 5> t_ms;
    // 秒级检查间隔
    bh::Btimer<std::chrono::seconds, 1> t_sec;

    std::atomic<bh::int32> count_ms{0};
    std::atomic<bh::int32> count_sec{0};

    vloga("推入毫秒任务(200ms触发5次)与秒级任务(2s触发2次)");
    t_ms.push(
        200,
        [&](bh::uint64 id) {
            count_ms++;
        },
        5);
    t_sec.push(
        2,
        [&](bh::uint64 id) {
            count_sec++;
        },
        2);

    vloga("等待执行完成...");
    bh::Btimel::sleep(6000);

    vlogd($(count_ms.load()) $(count_sec.load()));
    BHTEST_EQUAL(count_ms.load(), 5);
    BHTEST_EQUAL(count_sec.load(), 2);
}

void test_3()
{
    vloga("Btimer 任务移除与定时器关闭测试 (参考 main_timer::test_3)");
    bh::Btimer<> timer;
    std::atomic<bh::int32> count{0};

    vloga("推入 200ms 触发的无限循环任务");
    bh::uint64 id = timer.push(
        200,
        [&](bh::uint64 id) {
            count++;
        },
        0);

    bh::Btimel::sleep(1000);

    vloga("尝试移除运行中的任务");
    bool ok = timer.remove(id);
    BHTEST_TRUE(ok);

    bh::int32 last_count = count.load();
    vlogd("移除时触发总数: " $(last_count));

    bh::Btimel::sleep(1000);
    vloga("再次等待 1s 后校验计数器是否停止增加");
    BHTEST_EQUAL(count.load(), last_count);

    vloga("测试关闭整个定时器运行");
    timer.close_timer();
    BHTEST_TRUE(!timer.is_run());
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();

    return 0;
}
