#include <iostream>
#include <future>
#include <vector>
#include <mutex>
#include <string>
#include <atomic>

#include "Bpool.h"
#include "Btime.h"
#include "Btest.h"
#include "Btype.h"
#include "Tlog.h"

void test_1()
{
    vloga("Bpool 基础并发与 Future 返回值测试 (参考 main_pool::test_1)");

    // 创建一个容量为 3 的线程池
    bh::Bpool<3> loop1;
    std::mutex _mux;
    bh::Btimel t1;

    vloga("任务 1：计算 0-99 的累加和并返回 Future");
    std::future<bh::int32> ret1 = loop1.push([&]() {
        bh::int32 sum = 0;
        for(bh::int32 i = 0; i < 100; i++) {
            sum += i;
        }
        bh::Btimel::sleep(1000);
        return sum;
    });

    vloga("任务 2-4：执行耗时任务占用线程资源");
    for(bh::int32 i = 2; i <= 4; i++) {
        loop1.push([&_mux, i]() {
            std::lock_guard<std::mutex> lock(_mux);
            vlogd("任务 " + std::to_string(i) + " 正在执行");
            bh::Btimel::sleep(500);
        });
    }

    vloga("主线程阻塞等待任务 1 的结果并校验");
    bh::int32 final_sum = ret1.get();
    vlogd($(final_sum));

    BHTEST_EQUAL(final_sum, 4950);

    vloga("执行时间记录");
    vlogd($(t1.to_str()));
}

void test_2()
{
    vloga("Bpool 批量任务处理与内容完整性校验 (参考 main_pool::test_2)");

    bh::Bpool<> loop1;
    std::vector<std::future<bh::dstr>> vec;

    auto fn1 = [](bh::dstr tip) -> bh::dstr {
        bh::dstr str = tip + ": ";
        for(bh::int32 i = 0; i < 10; i++) {
            str += std::to_string(i);
        }
        bh::Btimel::sleep(50);
        return str;
    };

    bh::int32 total_tasks = 20;
    vloga("批量推送 20 个字符串处理任务");
    for(bh::int32 i = 0; i < total_tasks; i++) {
        std::future<bh::dstr> rp = loop1.push(fn1, "task_id_" + std::to_string(i));
        vec.push_back(std::move(rp));
    }

    vloga("验证所有 Future 的返回内容");
    bh::int32 success_count = 0;
    for(bh::int32 i = 0; i < total_tasks; i++) {
        bh::dstr result = vec[i].get();
        bh::dstr expected = "task_id_" + std::to_string(i) + ": 0123456789";
        if(result == expected) {
            success_count++;
        }
        else {
            vlogd("内容不一致! 实际: " + result);
        }
    }

    vlogd("成功校验任务数: " $(success_count));
    BHTEST_EQUAL(success_count, total_tasks);
}

void test_3()
{
    vloga("Bpool 并发推送压力与线程安全补齐测试");

    bh::Bpool<4> pool;
    std::atomic<bh::int32> total_executed{0};
    bh::int32 producer_count = 10;
    bh::int32 tasks_per_producer = 100;

    vloga("启动 10 个生产者线程，并发向同一个 Bpool 推送总计 1000 个任务");
    std::vector<std::thread> producers;
    for(bh::int32 i = 0; i < producer_count; i++) {
        producers.emplace_back([&]() {
            for(bh::int32 j = 0; j < tasks_per_producer; j++) {
                pool.push([&]() {
                    total_executed++;
                });
            }
        });
    }

    for(auto &t : producers)
        t.join();

    vloga("等待所有任务在池内消费完成");
    bh::int32 timeout = 0;
    while(total_executed < (producer_count * tasks_per_producer) && timeout++ < 50) {
        bh::Btimel::sleep(100);
    }

    vloga("最终执行总量校验");
    vlogd("预期总数: " $(producer_count * tasks_per_producer));
    vlogd("实际执行: " $(total_executed.load()));

    BHTEST_EQUAL(total_executed.load(), producer_count * tasks_per_producer);
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();

    return 0;
}
