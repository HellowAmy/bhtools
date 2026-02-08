#include <iostream>
#include <map>
#include "Brand.h"
#include "Tlog.h"
#include "Btest.h"
#include "Btype.h"

void test_1()
{
    vloga("Brand 均匀分布随机数测试");
    bh::Brand_int rd1(-10, 10);
    bh::Brand_bool rd2;

    std::map<bh::int32, bh::int32> mp1;
    bh::int32 num = 100;
    for(bh::int32 i = 0; i < num; i++) {
        bh::int32 val = rd1.value();
        // 范围校验
        BHTEST_TRUE((val >= -10 && val <= 10));
        mp1[val]++;
    }

    vloga("均匀分布(Int)结果频次观察");
    for(auto &a : mp1) {
        vlogd("[" << a.first << "]: " << a.second);
    }

    vloga("布尔分布测试 (100次采样)");
    bh::int32 true_count = 0;
    for(bh::int32 i = 0; i < num; i++) {
        if(rd2.value())
            true_count++;
    }
    vlogd("True 出现次数: " << $(true_count));
    // 概率断言：100次中全为真或全为假的概率极低
    BHTEST_TRUE((true_count > 0 && true_count < num));
}

void test_2()
{
    vloga("Brand 高级分布测试 (正态/离散)");
    bh::Brand_ndis rd_n(50.0, 5.0); // 均值50，标准差5
    bh::Brand_ddis rd_d{10, 90};    // 10%概率0, 90%概率1

    bh::int32 n_val = rd_n.value();
    vlogd("正态分布随机采样值: " << $(n_val));
    BHTEST_TRUE((n_val > 0));

    bh::int32 d_sum = 0;
    for(bh::int32 i = 0; i < 100; i++) {
        d_sum += rd_d.value();
    }
    vlogd("离散分布(90%权重为1) 100次累加结果: " << $(d_sum));
    // 概率断言：90%概率为1，100次累加应显著大于50
    BHTEST_TRUE((d_sum > 50));
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    return 0;
}
