#include <iostream>
#include <cstring>

#include "Bstrvi.h"

#include "Ftest.h"

void test_1()
{
    char cs1[] = "hello world 1";
    bh::cchp cs2 = "hello world 2";
    bh::dstr cs3 = "hello world 3";
    bh::cstr cs4 = "hello world 4";

    bh::Bstrvi a1(cs1);
    bh::Bstrvi a2(cs2);
    bh::Bstrvi a3(cs3);
    bh::Bstrvi a4(cs4);
    bh::Bstrvi a5(a4);
    bh::Bstrvi a6 = a5;

    vloga("全部长度");
    vlogd($(a1));
    vlogd($(a2));
    vlogd($(a3));
    vlogd($(a4));
    vlogd($(a5));
    vlogd($(a6));

    bh::Bstrvi b1(cs1);
    bh::Bstrvi b2(cs1, 0, 4);
    bh::Bstrvi b3(cs1, 0, 5);
    bh::Bstrvi b4(cs1, 2);
    bh::Bstrvi b5(cs1, 6);
    bh::Bstrvi b6(cs1, 6, 5);
    bh::Bstrvi b7(cs1, 6, 4);

    vloga("部分长度");
    BHTEST_EQUAL(b1, "hello world 1");
    BHTEST_EQUAL(b2, "hell");
    BHTEST_EQUAL(b3, "hello");
    BHTEST_EQUAL(b4, "llo world 1");
    BHTEST_EQUAL(b5, "world 1");
    BHTEST_EQUAL(b6, "world");
    BHTEST_EQUAL(b7, "worl");

    bh::Bstrvi c1(a1);
    bh::Bstrvi c2(a1, 0, 5);
    bh::Bstrvi c3(a1, 0, 5);
    bh::Bstrvi c4(a1);

    c2.move(2);
    c3.move_head(2);
    c4.move_tail(-3);

    vloga("移动数据");
    BHTEST_EQUAL(c1, "hello world 1");
    BHTEST_EQUAL(c2, "llo w");
    BHTEST_EQUAL(c3, "llo");
    BHTEST_EQUAL(c4, "hello worl");

    bh::Bstrvi d1(a1);
    bh::Bstrvi d2(a1);
    bh::Bstrvi d3(a1, 0, 5);
    bh::Bstrvi d4(a1, 6, 5);

    bool ok1 = (d1 == a1);
    bool ok2 = (d1 == d2);
    bool ok3 = (d1 == d4);
    bool ok4 = (d3 == "hello");
    bool ok5 = (d3 == "world");
    bool ok6 = (d4 == bh::dstr("hello"));
    bool ok7 = (d4 == bh::dstr("world"));
    bool ok8 = (d1 == cs1);
    bool ok9 = (d1 == cs2);
    bool ok10 = (d1 == cs3);
    bool ok11 = (d1 == cs4);

    vloga("相等测试");
    BHTEST_EQUAL(ok1, true);
    BHTEST_EQUAL(ok2, true);
    BHTEST_EQUAL(ok3, false);
    BHTEST_EQUAL(ok4, true);
    BHTEST_EQUAL(ok5, false);
    BHTEST_EQUAL(ok6, false);
    BHTEST_EQUAL(ok7, true);
    BHTEST_EQUAL(ok8, true);
    BHTEST_EQUAL(ok9, false);
    BHTEST_EQUAL(ok10, false);
    BHTEST_EQUAL(ok11, false);
}

void test_2()
{
    bh::Bstrvi b1("hello world 1 hello world 1");

    auto p1 = b1.find("world", 0, 5);
    auto p2 = b1.find("ll", 0, 2);
    auto p3 = b1.find("d 1", 0, 3);
    auto p4 = b1.find("he", 0, 2);
    auto p5 = b1.find("1", 0, 1);
    auto p6 = b1.find("2", 0, 1);
    auto p7 = b1.find("hella", 0, 5);
    auto p8 = b1.find("world", p1 + 1, 5);
    auto p9 = b1.find("ll", p2 + 1, 2);
    auto p10 = b1.find("ll", p2 + 100, 2);

    auto r1 = b1.rfind("world", b1.size(), 5);
    auto r2 = b1.rfind("ll", b1.size(), 2);
    auto r3 = b1.rfind("d 1", b1.size(), 3);
    auto r4 = b1.rfind("he", b1.size(), 2);
    auto r5 = b1.rfind("1", b1.size(), 1);
    auto r6 = b1.rfind("2", b1.size(), 1);
    auto r7 = b1.rfind("hella", b1.size(), 5);
    auto r8 = b1.rfind("world", r1 - 1, 5);
    auto r9 = b1.rfind("ll", r2 - 1, 2);
    auto r10 = b1.rfind("ll", r2 - 100, 2);

    bh::dstr s1;
    s1.rfind("world", 0, 5);

    vloga("查找字符串位置");
    vlogd($(b1) $(b1.size()));
    vlogd($(p1));
    vlogd($(p2));
    vlogd($(p3));
    vlogd($(p4));
    vlogd($(p5));
    vlogd($(p6));
    vlogd($(p7));
    vlogd($(p8));
    vlogd($(p9));
    vlogd($(p10));

    vloga("反向查找");
    vlogd($(b1) $(b1.size()));
    vlogd($(r1));
    vlogd($(r2));
    vlogd($(r3));
    vlogd($(r4));
    vlogd($(r5));
    vlogd($(r6));
    vlogd($(r7));
    vlogd($(r8));
    vlogd($(r9));
    vlogd($(r10));
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}