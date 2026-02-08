#include <iostream>
#include <queue>
#include <list>

#include "Bheap.h"
#include "Btime.h"
#include "Btest.h"
#include "Btype.h"

#include "Tlog.h"

void test_1()
{
    vloga("Bheap 常用接口功能测试");
    bh::Bheap_max<bh::int32> h1;

    for(bh::int32 i = 0; i < 20; i += 2) {
        h1.insert_node(i);
    }

    vlogd($(h1.size()) $(h1.check_root()) $(h1.is_empty()));
    BHTEST_EQUAL(h1.size(), 10);
    BHTEST_EQUAL(h1.check_root(), 18);
    BHTEST_TRUE(!h1.is_empty());

    vlogd($(h1.is_exist(18)) $(h1.is_exist(15)) $(h1.value_tail()));
    BHTEST_TRUE(h1.is_exist(18));
    BHTEST_TRUE(!h1.is_exist(15));

    bh::int32 root_val = h1.pop_root();
    vlogd($(root_val) $(h1.check_root()));
    BHTEST_EQUAL(root_val, 18);
    BHTEST_EQUAL(h1.check_root(), 16);

    bool ok1 = h1.remove_node(10);
    bool ok2 = h1.remove_node(99);
    vlogd($(ok1) $(ok2) $(h1.size()));
    BHTEST_TRUE(ok1);
    BHTEST_TRUE(!ok2);
    BHTEST_EQUAL(h1.size(), 8);

    h1.clear();
    BHTEST_TRUE(h1.is_empty());
    BHTEST_EQUAL(h1.size(), 0);
}

void test_2()
{
    vloga("Bheap 最大堆与最小堆顺序逻辑测试");
    bh::Bheap_max<bh::int32> h_max;
    bh::Bheap_min<bh::int32> h_min;

    bh::int32 data[] = {50, 10, 90, 30, 70};
    for(auto v : data) {
        h_max.insert_node(v);
        h_min.insert_node(v);
    }

    vloga("最大堆弹出");
    while(!h_max.is_empty()) {
        vlogd($(h_max.pop_root()));
    }

    vloga("最小堆弹出");
    while(!h_min.is_empty()) {
        vlogd($(h_min.pop_root()));
    }
}

void test_3()
{
    vloga("Bheap 拷贝构造与赋值操作符测试");
    bh::Bheap_max<bh::int32> h1;
    for(bh::int32 i = 0; i < 5; i++) {
        h1.insert_node(i);
    }

    bh::Bheap_max<bh::int32> h2(h1);
    BHTEST_EQUAL(h2.size(), 5);
    BHTEST_EQUAL(h2.check_root(), 4);

    bh::Bheap_max<bh::int32> h3;
    h3 = h1;
    BHTEST_EQUAL(h3.size(), 5);
    BHTEST_EQUAL(h3.check_root(), 4);

    h1.insert_node(100);
    BHTEST_EQUAL(h1.check_root(), 100);
    BHTEST_EQUAL(h2.check_root(), 4);
}

void test_4()
{
    vloga("Bheap 大规模数据压力测试");
    bh::Bheap_max<bh::int32> h1;
    bh::Btimel t1;
    bh::int32 sum = 1000 * 10000;

    for(bh::int32 i = 0; i < sum; i++) {
        h1.insert_node(i);
    }
    vlogd("插入操作完成 " $(h1.size()));
    BHTEST_EQUAL(h1.size(), sum);
    auto p1 = t1.time_interval();

    t1.update();
    vloga("开始大规模弹出数据");
    while(!h1.is_empty()) {

        h1.pop_root();
    }
    vlogd("弹出操作完成 " $(h1.size()));
    BHTEST_TRUE(h1.is_empty());
    auto p2 = t1.time_interval();

    t1.update();
    for(bh::int32 i = 0; i < sum; i++) {
        h1.insert_node(i);
    }
    vlogd("插入操作完成 " $(h1.size()));
    auto p3 = t1.time_interval();

    t1.update();
    h1.clear();
    auto p4 = t1.time_interval();
    vlogd("清空操作完成 " $(h1.size()));
    vlogd($(t1.to_str()));

    vlogd($(t1.to_str(p1)));
    vlogd($(t1.to_str(p2)));
    vlogd($(t1.to_str(p3)));
    vlogd($(t1.to_str(p4)));

    // [Deb]<<<< [t1.to_str(p1): [nan: 1911582568|mic: 1911582|mil: 1911|sec: 1]]
    // [Deb]<<<< [t1.to_str(p2): [nan: 2814359457|mic: 2814359|mil: 2814|sec: 2]]
    // [Deb]<<<< [t1.to_str(p3): [nan: 1629178176|mic: 1629178|mil: 1629|sec: 1]]
}

void test_5()
{
    vloga("Bheap 最大堆遍历与弹出测试");
    bh::Bheap_max<bh::int32> h1;
    for(bh::int32 i = 0; i < 10; i++) {
        h1.insert_node(i);
    }
    vlogd($(h1.size()));
    for(auto &a : h1) {
        vlogd($(a));
    }
    while(!h1.is_empty()) {
        vlogd($(h1.pop_root()));
    }

    vloga("Bheap 最小堆遍历与弹出测试");
    bh::Bheap_min<bh::int32> h2;
    for(bh::int32 i = 0; i < 10; i++) {
        h2.insert_node(i);
    }
    vlogd($(h2.size()));

    for(auto &a : h2) {
        vlogd($(a));
    }
    while(!h2.is_empty()) {
        vlogd($(h2.pop_root()));
    }
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();

    return 0;
}
