#include <iostream>
#include <memory>
#include "Bdesign.h"
#include "Tlog.h"
#include "Btest.h"
#include "Btype.h"

// 简单职责链节点
struct filter_work : bh::Bwork_base<bh::int32>
{
    bool process(bh::int32 val) override
    {
        if(val == 777) {
            return true;
        }
        return false;
    }
};

struct filter_work2 : bh::Bwork_base<bh::int32>
{
    bool process(bh::int32 val) override
    {
        if(val == 888) {
            return true;
        }
        return false;
    }
};

// 复杂数据交互结构
struct calc_data
{
    bh::int32 a, b, res;
    bh::dstr action;
};

// 乘法节点
struct mul_work
{
    bool process(calc_data &d)
    {
        if(d.action == "*") {
            d.res = d.a * d.b;
            return true;
        }
        return false;
    }
};

void test_1()
{
    vloga("Bdesign 基础职责链逻辑测试");
    bh::Bwork_chain<filter_work, filter_work2> chain;

    vloga("测试目标值拦截");
    BHTEST_TRUE(chain.start(777));

    BHTEST_TRUE(chain.start(888));

    vloga("测试非目标值穿透");
    BHTEST_TRUE(chain.start(999));
}

void test_2()
{
    vloga("Bdesign 结构体数据计算链测试");
    bh::Bwork_chain<mul_work> chain;

    calc_data d{5, 6, 0, "*"};
    vloga("执行计算链...");
    bool ok = chain.start(d);

    vlogd("计算结果展示: " << $(d.res));
    BHTEST_TRUE(ok);
    BHTEST_EQUAL(d.res, 30);
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    return 0;
}
