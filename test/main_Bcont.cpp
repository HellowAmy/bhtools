#include <iostream>
#include <string>
#include "Bcont.h"
#include "Bpool.h"
#include "Tlog.h"
#include "Btest.h"
#include "Btype.h"
#include "Btime.h"

void test_1()
{
    vloga("Bcont 高并发安全性测试 (Queue/Stack/Vector/Map)");
    bh::Bpool<> pool;
    bh::Bqueue<bh::int32> q;
    bh::Bstack<bh::int32> st;
    bh::Bvector<bh::int32> v;
    bh::Bmap<bh::int32, bh::dstr> m;

    bh::int32 sum = 5000;
    vloga("并发写入任务启动中...");

    auto push_task = [&]() {
        for(bh::int32 i = 0; i < sum; i++) {
            q.push(i);
            st.push(i);
            v.push_back(i);
            m.insert({i, "bh_data"});
        }
    };

    // 启动两个并发写入线程
    pool.push(push_task);
    pool.push(push_task);

    vloga("主线程等待写入完成...");
    bh::Btimel::sleep(1500);

    vloga("容器最终规模校验");
    vlogd($(q.size()) $(st.size()) $(v.size()) $(m.size()));

    // 校验：Queue, Stack, Vector 应该由于并发写入各翻一倍
    BHTEST_EQUAL(q.size(), (bh::uint64)sum * 2);
    BHTEST_EQUAL(st.size(), (bh::uint64)sum * 2);
    BHTEST_EQUAL(v.size(), (bh::uint64)sum * 2);
    // Map 键冲突，规模应等于单次循环量
    BHTEST_EQUAL(m.size(), (bh::uint64)sum);
}

void test_2()
{
    vloga("Bcont 弹出逻辑与顺序校验");
    bh::Bqueue<bh::int32> q;
    q.push(100);
    q.push(200);
    vlogd("Queue 弹出测试");
    vlogd($(q.pop_front()));
    vlogd($(q.pop_front()));

    bh::Bstack<bh::int32> st;
    st.push(100);
    st.push(200);
    vlogd("Stack 弹出测试");
    vlogd($(st.pop_top()));
    vlogd($(st.pop_top()));
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    return 0;
}
