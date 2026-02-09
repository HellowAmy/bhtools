#include <iostream>

#include "Btype.h"
#include "Btest.h"
#include "Blog.h"

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
    bool b3 = true;

    vloga("\n相等测试");
    vloga("数字");
    vlogd($(a1) $(a2) $(a3));
    BHTEST_EQUAL(a1, a1);
    BHTEST_EQUAL(a1, a2);
    BHTEST_EQUAL(a1, a3);
    BHTEST_EQUAL(a1, 10);
    BHTEST_EQUAL(a1, 20);
    BHTEST_EQUAL(a2, 10);
    BHTEST_EQUAL(a2, 20);

    vloga("字符串");
    vlogd($(s1) $(s2) $(s3));
    BHTEST_EQUAL(s1, s1);
    BHTEST_EQUAL(s1, s2);
    BHTEST_EQUAL(s1, s3);
    BHTEST_EQUAL(s1, "hello");
    BHTEST_EQUAL(s1, "world");
    BHTEST_EQUAL(s2, "hello");
    BHTEST_EQUAL(s2, "world");

    vloga("布尔值");
    vlogd($(b1) $(b2) $(b3));
    BHTEST_EQUAL(b1, b1);
    BHTEST_EQUAL(b1, b2);
    BHTEST_EQUAL(b1, b3);
    BHTEST_EQUAL(b1, true);
    BHTEST_EQUAL(b1, false);
    BHTEST_EQUAL(b2, true);
    BHTEST_EQUAL(b2, false);

    vloga("相等测试-原地计算");
    vloga("数字");
    vlogd($(a1) $(a2));
    BHTEST_EQUAL(a1, 5 + 5);
    BHTEST_EQUAL(a2, 10 + 10);
    BHTEST_EQUAL(a2, 10 + 10);

    vloga("布尔值");
    BHTEST_EQUAL(b1, b1 && b2);
    BHTEST_EQUAL(b1, b1 || b2);
    BHTEST_EQUAL(b2, b1 && b2);
    BHTEST_EQUAL(b2, b1 || b2);
}

void test_2()
{
    bh::int32 a1 = 10;
    bh::int32 a2 = 20;

    bh::dstr s1 = "hello";
    bh::dstr s2 = "world";

    bool b1 = true;
    bool b2 = false;

    vloga("\n判断测试");
    vloga("数字");
    BHTEST_TRUE(a1 == 10);
    BHTEST_TRUE(a1 == 20);
    BHTEST_TRUE(a2 == 10);
    BHTEST_TRUE(a2 == 20);

    vloga("字符串");
    BHTEST_TRUE(s1 == "hello");
    BHTEST_TRUE(s1 == "world");
    BHTEST_TRUE(s2 == "hello");
    BHTEST_TRUE(s2 == "world");

    vloga("布尔值");
    BHTEST_TRUE(b1);
    BHTEST_TRUE(b2);
    BHTEST_TRUE(b1 == b1);
    BHTEST_TRUE(b1 == b2);
}

void test_3()
{
    bh::int32 d1 = 200;
    bh::int32 *p1 = &d1;
    bh::int32 *p2 = nullptr;
    bh::cchp p3 = "test";
    bh::cchp p4 = p3;
    bh::cchp p5 = nullptr;

    vloga("\n空指针测试");
    vloga("空指针错误打印");
    BHTEST_NULL(p1);
    BHTEST_NULL(p2);
    BHTEST_NULL(p3);
    BHTEST_NULL(p4);
    BHTEST_NULL(p5);
}

int main(bh::int32 argc, char *argv[])
{
    //
    test_1();
    test_2();
    test_3();

    return 0;
}