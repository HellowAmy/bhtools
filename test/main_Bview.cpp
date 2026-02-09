#include <iostream>
#include <cstring>

#include "Bview.h"
#include "Btest.h"

void test_1()
{
    char cs1[] = "A1234567890";
    bh::cchp cs2 = "B1234567890";
    bh::dstr cs3 = "C1234567890";
    bh::cstr cs4 = "D1234567890";

    bh::Bview a1(cs1);
    bh::Bview a2(cs2);
    bh::Bview a3(cs3);
    bh::Bview a4(cs4);
    bh::Bview a5(a4);
    bh::Bview a6 = a5;

    vloga("\n测试视图");
    vloga("测试构造函数");
    vlogd($(a1.to_str()) $(a1.size()));
    vlogd($(a2.to_str()) $(a2.size()));
    vlogd($(a3.to_str()) $(a3.size()));
    vlogd($(a4.to_str()) $(a4.size()));
    vlogd($(a5.to_str()) $(a5.size()));
    vlogd($(a6.to_str()) $(a6.size()));

    vloga("测试 move 函数移动之后的内容");
    a1.move(5);
    BHTEST_EQUAL(a1.to_str(), "");

    a1.move(1);
    BHTEST_EQUAL(a1.to_str(), "");
    BHTEST_EQUAL(a1.size(), 11);

    vloga("测试 move_head 函数");
    a2.move_head(1);
    BHTEST_EQUAL(a2.to_str(), "1234567890");
    BHTEST_EQUAL(a2.size(), 10);

    a2.move_head(3);
    BHTEST_EQUAL(a2.to_str(), "4567890");
    BHTEST_EQUAL(a2.size(), 7);

    vloga("测试 move_tail 函数");
    a3.move_tail(-2);
    BHTEST_EQUAL(a3.to_str(), "C12345678");
    BHTEST_EQUAL(a3.size(), 9);

    a3.move_tail(-3);
    BHTEST_EQUAL(a3.to_str(), "C12345");
    BHTEST_EQUAL(a3.size(), 6);

    a3.move_tail(5);
    BHTEST_EQUAL(a3.to_str(), "C1234567890");
    BHTEST_EQUAL(a3.size(), 11);
}

void test_2()
{
    bh::cstr cs1 = "A1234567890B1234567890C1234567890D1234567890";
    bh::Bview a1(cs1);

    vloga("\n测试函数");
    vloga("测试 find rfind 函数");
    bh::Bview target("B123");
    BHTEST_EQUAL(a1.find(target, 0), 11);
    BHTEST_EQUAL(a1.find("E123", 0, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.find("", 0, 0), 0);
    BHTEST_EQUAL(a1.find("", 44, 0), 44);
    BHTEST_EQUAL(a1.find("A", 45, 1), bh::dstr::npos);

    BHTEST_EQUAL(a1.find("C123", 0, 4), 22);
    BHTEST_EQUAL(a1.find("Z123", 0, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.find("D123", 30, 4), 33);
    BHTEST_EQUAL(a1.find("D123", 34, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.find("A123", 1, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.find("B123", 11, 4), 11);

    BHTEST_EQUAL(a1.rfind(target, 44), 11);
    BHTEST_EQUAL(a1.rfind("D123", 44, 4), 33);
    BHTEST_EQUAL(a1.rfind("B123", 10, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.rfind("B123", 11, 4), 11);

    BHTEST_EQUAL(a1.rfind("A123", 44, 4), 0);
    BHTEST_EQUAL(a1.rfind("X123", 44, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.rfind("C123", 30, 4), 22);
    BHTEST_EQUAL(a1.rfind("C123", 21, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.rfind("D123", 32, 4), bh::dstr::npos);
    BHTEST_EQUAL(a1.rfind("D123", 33, 4), 33);
}

void test_3()
{
    bh::cstr cs1 = "A1234567890B1234567890C1234567890D1234567890";
    bh::Bview a1(cs1);
    bh::Bview a2(cs1, 1);
    bh::Bview a3(cs1, 11, 11);

    vloga("\n测试不同的构造方式");
    vlogd($(a1.to_str()) $(a1.size()));
    BHTEST_EQUAL(a2.to_str(), "1234567890B1234567890C1234567890D1234567890");
    BHTEST_EQUAL(a2.size(), 43);
    BHTEST_EQUAL(a3.to_str(), "B1234567890");
    BHTEST_EQUAL(a3.size(), 11);

    vloga("\n测试 move 函数移动之后的内容");
    a3.move(1);
    BHTEST_EQUAL(a3.to_str(), "1234567890C");
    a3.move(-1);
    BHTEST_EQUAL(a3.to_str(), "B1234567890");
    a3.move(11);
    BHTEST_EQUAL(a3.to_str(), "C1234567890");
    BHTEST_EQUAL(a3.size(), 11);
    a3.move(-11);
    BHTEST_EQUAL(a3.to_str(), "B1234567890");
    a3.move(5);
    BHTEST_EQUAL(a3.to_str(), "567890C1234");
    a3.move(-2);
    BHTEST_EQUAL(a3.to_str(), "34567890C12");

    vloga("\n测试 operator[] 函数");
    BHTEST_EQUAL(a1[0], 'A');
    BHTEST_EQUAL(a1[11], 'B');
    BHTEST_EQUAL(a1[43], '0');
    BHTEST_TRUE(a1[0] != '1');
    BHTEST_TRUE(a1[11] != 'A');
    BHTEST_TRUE(a1[43] != 'D');

    vloga("\n测试 operator== 函数");
    bh::Bview v1("hello");
    bh::Bview v2("hello");
    bh::Bview v3("world");
    bh::Bview v4("hell");
    bh::Bview v5(v1, 0, 4);
    BHTEST_TRUE(v1 == v2);
    BHTEST_TRUE(v4 == v5);
    BHTEST_TRUE(!(v1 == v3));
    BHTEST_TRUE(!(v1 == v4));
    BHTEST_TRUE(!(v1 == v5));
    BHTEST_TRUE(v5 == v4);
}

int main(int argc, char *argv[])
{
    // 
    test_1();
    test_2();
    test_3();

    return 0;
}
