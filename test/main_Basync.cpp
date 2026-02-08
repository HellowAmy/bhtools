#include <iostream>
#include <vector>
#include <string>

#include "Basync.h"
#include "Btype.h"
#include "Btest.h"
#include "Tlog.h"
#include "Btime.h"

// 模拟业务数据结构
struct test_step_arg
{
    bh::int32 val = 0;
    bh::int32 step = 0;
    bh::dstr info;
    bool is_done = false;
};

void test_1()
{
    vloga("Basync 链式顺序执行与错误中断逻辑测试 (参考 main_async::test_1)");
    bh::Basync<test_step_arg> asy;

    asy.next([](test_step_arg *arg) {
           vloga("执行步骤 1: 累加操作");
           arg->val += 10;
           arg->step = 1;
           return true;
       })
        .next([](test_step_arg *arg) {
            vloga("执行步骤 2: 条件中断检查");
            if(arg->val > 50) {
                arg->step = 2;
                return true;
            }
            arg->info = "数值不足 50，中断流程";
            return false;
        })
        .next([](test_step_arg *arg) {
            vloga("执行步骤 3: 终态标记");
            arg->step = 3;
            arg->is_done = true;
            return true;
        })
        .succee([](test_step_arg *arg) {
            vloga("任务链执行成功回调触发");
        })
        .error([](test_step_arg *arg) {
            vloga("任务链中断/错误回调触发");
        });

    {
        vloga("用例 A: 模拟中断流程 (val=10)");
        test_step_arg d1;
        d1.val = 10;
        asy.run(&d1, false); // 同步运行
        vlogd($(d1.val) $(d1.step) $(d1.info));
        BHTEST_EQUAL(d1.step, 1);
        BHTEST_EQUAL(d1.info, "数值不足 50，中断流程");
    }

    {
        vloga("用例 B: 模拟完整流程 (val=50)");
        test_step_arg d2;
        d2.val = 50;
        asy.run(&d2, false);
        vlogd($(d2.val) $(d2.step) $(d2.is_done));
        BHTEST_EQUAL(d2.step, 3);
        BHTEST_TRUE(d2.is_done);
    }
}

void test_2()
{
    vloga("Basync 无参数(void)异步线程执行测试 (参考 main_async::test_2)");
    bh::Basync<void> asy;
    bh::int32 count = 0;

    asy.next([&](void *) {
           vloga("异步步骤 1 正在执行");
           count += 1;
           bh::Btimel::sleep(200);
           return true;
       })
        .next([&](void *) {
            vloga("异步步骤 2 正在执行");
            count += 1;
            bh::Btimel::sleep(200);
            return true;
        });

    vloga("启动异步运行...");
    asy.run();

    vloga("主线程进行等待...");
    bh::Btimel::sleep(1000);

    vloga("异步执行结果校验");
    vlogd($(count));
    BHTEST_EQUAL(count, 2);
}

void test_3()
{
    vloga("Basync 任务重用与拷贝构造安全性测试 (参考 main_async::test_3)");
    bh::Basync<test_step_arg> asy_base;

    asy_base
        .next([](test_step_arg *arg) {
            arg->val += 100;
            return true;
        })
        .succee([](test_step_arg *arg) {
            arg->is_done = true;
        });

    vloga("通过拷贝构造生成多个独立的任务执行器");
    std::vector<std::pair<test_step_arg, bh::Basync<test_step_arg>>> tasks;
    for(bh::int32 i = 0; i < 5; i++) {
        test_step_arg data;
        data.val = i;
        tasks.push_back({data, asy_base});
    }

    vloga("并发启动所有拷贝的任务执行器");
    for(auto &item : tasks) {
        item.second.run(&item.first);
    }

    vloga("等待所有异步线程 join 结束...");
    // Basync 析构或再次 run 时会 join，这里通过 sleep 确保逻辑完成
    bh::Btimel::sleep(1000);

    vloga("数据一致性核对");
    bool all_ok = true;
    for(bh::int32 i = 0; i < 5; i++) {
        bh::int32 expected = i + 100;
        vlogd("Task " << i << " Result: " << tasks[i].first.val);
        if(tasks[i].first.val != expected || !tasks[i].first.is_done) {
            all_ok = false;
        }
    }
    BHTEST_TRUE(all_ok);
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();

    return 0;
}
