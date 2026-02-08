#include <iostream>

#include "Btype.h"
#include "Btest.h"

#include "Tlog.h"

void test_1()
{
    bh::int32 a1 = 10;
    bh::int32 a2 = 20;
    bh::int32 a3 = 10;

    bh::dstr s1 = "hello";
    bh::dstr s2 = "world";
    bh::dstr s3 = "hello";

    bool b1 = true;
    bool b2 = false;

    vloga("相等性基础测试");
    vlogd($(a1) $(a2) $(a3));
    BHTEST_EQUAL(a1, a3);
    BHTEST_EQUAL(a1, a2);

    vloga("字符串相等性测试");
    vlogd($(s1) $(s2) $(s3));
    BHTEST_EQUAL(s1, s3);
    BHTEST_EQUAL(s1, s2);

    vloga("布尔值相等性测试");
    vlogd($(b1) $(b2));
    BHTEST_EQUAL(b1, true);
    BHTEST_EQUAL(b2, false);
}

void test_2()
{
    bool b1 = true;
    bool b2 = false;
    bh::int32 n1 = 100;

    vloga("真值逻辑测试");
    vlogd($(b1) $(b2) $(n1));
    BHTEST_TRUE(b1);
    BHTEST_TRUE((n1 == 100));
    BHTEST_TRUE(b2);
    BHTEST_TRUE((n1 > 200));
}

void test_3()
{
    bh::int32 d1 = 200;
    bh::int32 *p1 = nullptr;
    bh::int32 *p2 = &d1;
    bh::cchp p3 = "test";

    vloga("空指针边界测试");
    vlogd($(p1) $(p2) $(p3) $(d1));
    BHTEST_NULL(p1);
    BHTEST_NULL(p2);
    BHTEST_NULL(p3);
    BHTEST_NULL(d1);
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();

    return 0;
}