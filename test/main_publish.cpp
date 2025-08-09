
#include <iostream>
#include <unordered_set>

#include "bhtools.h"


// 发布消息数据
struct test_msg1
{
    int a1;
};

struct test_msg2
{
    int a1;
    size_t a2;
};

struct test_msg3
{
    int a1;
    size_t a2;
    std::string a3;
};


// 监控消息的处理类
struct test_a1 : bhtools::Tpubmsg<test_msg1>
{
    test_a1(bhtools::Tpublish *pub) : 
        bhtools::Tpubmsg<test_msg1>(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        vlogd($("test_a1") $(d.a1));
    }
};

struct test_a2 : bhtools::Tpubmsg<test_msg1>,
                    bhtools::Tpubmsg<test_msg2>
{
    test_a2(bhtools::Tpublish *pub) : 
        bhtools::Tpubmsg<test_msg1>(pub), 
        bhtools::Tpubmsg<test_msg2>(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        vlogd($("test_a2") $(d.a1));
    }

    void notify_msg(const test_msg2 &d) override
    {
        vlogd($(d.a1) $(d.a2));
    }
};

struct test_a3 : bhtools::Tpubmsg<test_msg1>,
                     bhtools::Tpubmsg<test_msg2>,
                     bhtools::Tpubmsg<test_msg3>
{
    test_a3(bhtools::Tpublish *pub) : 
        bhtools::Tpubmsg<test_msg1>(pub), 
        bhtools::Tpubmsg<test_msg2>(pub),
        bhtools::Tpubmsg<test_msg3>(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        vlogd($("test_a3") $(d.a1));
    }

    void notify_msg(const test_msg2 &d) override
    {
        vlogd($(d.a1) $(d.a2));
    }

    void notify_msg(const test_msg3 &d) override
    {
        vlogd($(d.a1) $(d.a2) $(d.a3));
    }
};

struct test_a4 : test_a3
{
    test_a4(bhtools::Tpublish *pub) : test_a3(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        vlogd($("test_a4") $(d.a1));
    }

    void notify_msg(const test_msg2 &d) override
    {
        vlogd($(d.a1) $(d.a2));
    }

    void notify_msg(const test_msg3 &d) override
    {
        vlogd($(d.a1) $(d.a2) $(d.a3));
    }
};

struct test_a5 : bhtools::Tpubmsg<test_msg1>,
                    bhtools::Tpubmsg<test_msg3>
{
    test_a5(bhtools::Tpublish *pub) : 
        bhtools::Tpubmsg<test_msg1>(pub),
        bhtools::Tpubmsg<test_msg3>(pub) {}

    void notify_msg(const test_msg1 &d) override
    {
        vlogd($("test_a5") $(d.a1));
    }

    void notify_msg(const test_msg3 &d) override
    {
        vlogd($(d.a1) $(d.a2) $(d.a3));
    }
};


void test_1()
{
    // 消息绑定
    bhtools::Tpublish pub;
    std::set<int> ss;
    ss.erase(5);
    test_a1 a1(&pub);
    test_a2 a2(&pub);
    test_a3 a3(&pub);
    test_a4 a4(&pub);
    test_a5 a5(&pub);

    // 发送消息
    {
        test_msg1 msg1;
        msg1.a1 = -19;
        pub.notify(msg1);
    }
    {
        test_msg2 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        pub.notify(msg1);
    }
    {
        test_msg3 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        msg1.a3 = "hellow";
        pub.notify(msg1);
    }

    // 检查和删除a5
    bool ok1 = pub.find<test_msg1>(&a5);
    bool ok2 = pub.find<test_msg2>(&a5);
    bool ok3 = pub.find<test_msg3>(&a5);
    vlogw($(ok1) $(ok2) $(ok3));
    
    pub.remove<test_msg1>(&a5);
    pub.remove<test_msg3>(&a5);
    vlogw($("remove a5"));
    vlogw($(ok1) $(ok2) $(ok3));

    {
        test_msg1 msg1;
        msg1.a1 = -19;
        pub.notify(msg1);
    }
    {
        test_msg2 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        pub.notify(msg1);
    }
    {
        test_msg3 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        msg1.a3 = "hellow";
        pub.notify(msg1);
    }

    // 删除所有a2
    vlogw($("remove all a2"));
    pub.remove(&a2);

    {
        test_msg1 msg1;
        msg1.a1 = -19;
        pub.notify(msg1);
    }
    {
        test_msg2 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        pub.notify(msg1);
    }
    {
        test_msg3 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        msg1.a3 = "hellow";
        pub.notify(msg1);
    }

    // 清空msg3并准备释放空间
    vlogw($("remove all msg3"));
    pub.remove<test_msg3>(&a3);
    pub.remove<test_msg3>(&a4);

    vlogw($(pub._sub.size()));
    pub.release_overdue();
    vlogw($(pub._sub.size()));

    {
        test_msg1 msg1;
        msg1.a1 = -19;
        pub.notify(msg1);
    }
    {
        test_msg2 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        pub.notify(msg1);
    }
    {
        test_msg3 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        msg1.a3 = "hellow";
        pub.notify(msg1);
    }

    // 重新注册
    vlogw($("重新注册"));
    a5.bhtools::Tpubmsg<test_msg1>::install_pub(&pub);
    a5.bhtools::Tpubmsg<test_msg3>::install_pub(&pub);
    {
        test_msg1 msg1;
        msg1.a1 = -19;
        pub.notify(msg1);
    }
    {
        test_msg2 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        pub.notify(msg1);
    }
    {
        test_msg3 msg1;
        msg1.a1 = -19;
        msg1.a2 = 1234;
        msg1.a3 = "hellow";
        pub.notify(msg1);
    }
}

int main(int argc, char *argv[])
{
    test_1();   
 
    return 0;
}