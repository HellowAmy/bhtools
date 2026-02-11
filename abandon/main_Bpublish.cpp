#include <iostream>
#include <unordered_set>

#include "Bpublish.h"
#include "Btype.h"
#include "Tlog.h"
#include "Btest.h"

// 发布消息数据
struct test_msg1
{
    bh::int32 a1;
};

struct test_msg2
{
    bh::int32 a1;
    bh::uint64 a2;
};

struct test_msg3
{
    bh::int32 a1;
    bh::uint64 a2;
    bh::dstr a3;
};

// 监控消息的处理类 - 增加计数器用于结果验证
struct test_a1 : bh::Bpubmsg<test_msg1>
{
    bh::int32 c1 = 0;
    test_a1(bh::Bpublish *pub) : bh::Bpubmsg<test_msg1>(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        c1++;
        vlogd($("test_a1") $(d.a1));
    }
};

struct test_a2 : bh::Bpubmsg<test_msg1>, bh::Bpubmsg<test_msg2>
{
    bh::int32 c1 = 0;
    bh::int32 c2 = 0;
    test_a2(bh::Bpublish *pub) : bh::Bpubmsg<test_msg1>(pub), bh::Bpubmsg<test_msg2>(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        c1++;
        vlogd($("test_a2") $(d.a1));
    }

    void notify_msg(const test_msg2 &d) override
    {
        c2++;
        vlogd($(d.a1) $(d.a2));
    }
};

struct test_a3 : bh::Bpubmsg<test_msg1>, bh::Bpubmsg<test_msg2>, bh::Bpubmsg<test_msg3>
{
    bh::int32 c1 = 0;
    bh::int32 c2 = 0;
    bh::int32 c3 = 0;
    test_a3(bh::Bpublish *pub)
        : bh::Bpubmsg<test_msg1>(pub), bh::Bpubmsg<test_msg2>(pub), bh::Bpubmsg<test_msg3>(pub)
    {
    }

    void notify_msg(const test_msg1 &d) override
    {
        c1++;
        vlogd($("test_a3") $(d.a1));
    }

    void notify_msg(const test_msg2 &d) override
    {
        c2++;
        vlogd($(d.a1) $(d.a2));
    }

    void notify_msg(const test_msg3 &d) override
    {
        c3++;
        vlogd($(d.a1) $(d.a2) $(d.a3));
    }
};

struct test_a4 : test_a3
{
    test_a4(bh::Bpublish *pub) : test_a3(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        this->c1++;
        vlogd($("test_a4") $(d.a1));
    }

    void notify_msg(const test_msg2 &d) override
    {
        this->c2++;
        vlogd($(d.a1) $(d.a2));
    }

    void notify_msg(const test_msg3 &d) override
    {
        this->c3++;
        vlogd($(d.a1) $(d.a2) $(d.a3));
    }
};

struct test_a5 : bh::Bpubmsg<test_msg1>, bh::Bpubmsg<test_msg3>
{
    bh::int32 c1 = 0;
    bh::int32 c3 = 0;
    test_a5(bh::Bpublish *pub) : bh::Bpubmsg<test_msg1>(pub), bh::Bpubmsg<test_msg3>(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        c1++;
        vlogd($("test_a5") $(d.a1));
    }

    void notify_msg(const test_msg3 &d) override
    {
        c3++;
        vlogd($(d.a1) $(d.a2) $(d.a3));
    }
};

void test_1()
{
    vloga("消息绑定与自动校验测试");
    bh::Bpublish pub;

    test_a1 a1(&pub);
    test_a2 a2(&pub);
    test_a3 a3(&pub);
    test_a4 a4(&pub);
    test_a5 a5(&pub);

    vloga("第一轮消息发布 - 全员接收");
    {
        test_msg1 m1;
        m1.a1 = 10;
        pub.notify(m1);
        test_msg2 m2;
        m2.a1 = 20;
        m2.a2 = 200;
        pub.notify(m2);
        test_msg3 m3;
        m3.a1 = 30;
        m3.a2 = 300;
        m3.a3 = "hello";
        pub.notify(m3);
    }

    vloga("校验第一轮触发次数");
    BHTEST_EQUAL(a1.c1, 1);
    BHTEST_EQUAL(a2.c1, 1);
    BHTEST_EQUAL(a2.c2, 1);
    BHTEST_EQUAL(a3.c3, 1);
    BHTEST_EQUAL(a5.c1, 1);
    BHTEST_EQUAL(a5.c3, 1);

    vloga("检查和删除 a5 的部分订阅");
    BHTEST_TRUE(pub.find<test_msg1>(&a5));
    BHTEST_TRUE(pub.find<test_msg3>(&a5));

    pub.remove<test_msg1>(&a5);
    pub.remove<test_msg3>(&a5);

    BHTEST_TRUE(!pub.find<test_msg1>(&a5));
    BHTEST_TRUE(!pub.find<test_msg3>(&a5));

    vloga("第二轮消息发布 - 确认 a5 不再接收");
    {
        test_msg1 m1;
        m1.a1 = 11;
        pub.notify(m1);
        test_msg3 m3;
        m3.a1 = 33;
        m3.a2 = 333;
        m3.a3 = "world";
        pub.notify(m3);
    }
    BHTEST_EQUAL(a5.c1, 1); // 次数应维持在 1
    BHTEST_EQUAL(a5.c3, 1);
    BHTEST_EQUAL(a1.c1, 2); // 其他人应递增

    vloga("删除 a2 的所有订阅");
    pub.remove(&a2);
    BHTEST_TRUE(!pub.find<test_msg1>(&a2));
    BHTEST_TRUE(!pub.find<test_msg2>(&a2));

    vloga("清空 msg3 订阅并测试过期释放");
    pub.remove<test_msg3>(&a3);
    pub.remove<test_msg3>(&a4);

    bh::uint64 size_before = pub._sub.size();
    pub.release_overdue();
    bh::uint64 size_after = pub._sub.size();
    vlogd("清理前订阅类型数: " << $(size_before) << " 清理后: " << $(size_after));
    BHTEST_TRUE((size_after < size_before));

    vloga("重新注册 a5 测试");
    a5.bh::Bpubmsg<test_msg1>::install_pub(&pub);
    BHTEST_TRUE(pub.find<test_msg1>(&a5));

    {
        test_msg1 m1;
        m1.a1 = 100;
        pub.notify(m1);
    }
    BHTEST_EQUAL(a5.c1, 2); // 重新注册后应收到消息
    vloga("所有校验完成");
}

int main(bh::int32 argc, char *argv[])
{
    test_1();

    return 0;
}