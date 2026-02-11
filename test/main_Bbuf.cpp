#include <iostream>
#include <cstring>

#include "Btype.h"
#include "Btest.h"
#include "Bbuf.h"

void test_1()
{
    vloga("构造函数测试\n");

    vloga("默认构造");
    bh::Bbuf b1;
    bh::Bbuf b2(1);
    bh::Bbuf b3(10);
    bh::Bbuf b4("hello1");
    bh::Bbuf b5("hello2");
    bh::Bbuf b6("hello3");

    bh::Bview vs1(b6.data(), b6.size(), 0, 0);
    bh::Bbuf b7(vs1);

    vloga("数据大小");
    BHTEST_EQUAL(b1.size(), 0);
    BHTEST_EQUAL(b2.size(), 0);
    BHTEST_EQUAL(b3.size(), 0);
    BHTEST_EQUAL(b4.size(), 6);
    BHTEST_EQUAL(b5.size(), 6);
    BHTEST_EQUAL(b6.size(), 6);
    BHTEST_EQUAL(b7.size(), 6);

    vloga("数据容量");
    BHTEST_EQUAL(b1.capacity(), 64);
    BHTEST_EQUAL(b2.capacity(), 1);
    BHTEST_EQUAL(b3.capacity(), 10);
    BHTEST_EQUAL(b4.capacity(), 6);
    BHTEST_EQUAL(b5.capacity(), 6);
    BHTEST_EQUAL(b6.capacity(), 6);
    BHTEST_EQUAL(b7.capacity(), 6);
}

void test_2()
{
    vloga("构造扩展与拷贝测试\n");

    vloga("多重构造");
    bh::Bbuf b1("string_test");
    bh::Bbuf b2("pointer_test", 12);
    bh::Bview v1(b1.data(), b1.size(), 0, 0);
    bh::Bbuf b3(v1);
    bh::Bbuf b4(b1);
    bh::Bbuf b5;
    b5 = b2;

    vloga("数据大小验证");
    BHTEST_EQUAL(b1.size(), 11);
    BHTEST_EQUAL(b2.size(), 12);
    BHTEST_EQUAL(b3.size(), 11);
    BHTEST_EQUAL(b4.size(), 11);
    BHTEST_EQUAL(b5.size(), 12);

    vloga("内容一致性验证");
    BHTEST_EQUAL(b1[0], 's');
    BHTEST_EQUAL(b2[0], 'p');
    BHTEST_EQUAL(b3[0], 's');
    BHTEST_EQUAL(b4[0], 's');
    BHTEST_EQUAL(b5[0], 'p');

    vloga("空状态验证");
    bh::Bbuf b6;
    bh::Bbuf b7(1);
    BHTEST_TRUE(b6.empty());
    BHTEST_TRUE(b7.empty());
}

void test_3()
{
    vloga("追加重载与索引读写测试\n");

    vloga("四种追加方式");
    bh::Bbuf b1("A");
    b1 += bh::Bbuf("B");
    b1 += bh::Bview("C", 1, 0, 0);
    b1 += std::string("D");
    b1 += "E";
    b1.append("FG", 2);

    vloga("追加结果验证");
    BHTEST_EQUAL(b1.size(), 7);
    BHTEST_EQUAL(b1[0], 'A');
    BHTEST_EQUAL(b1[6], 'G');
    BHTEST_EQUAL(b1.to_str(), "ABCDEFG");

    vloga("索引操作验证");
    char c1 = b1[0];
    char c2 = b1[3];
    char c3 = b1[6];
    b1[0] = '1';
    b1[3] = '4';
    b1[6] = '7';

    BHTEST_EQUAL(c1, 'A');
    BHTEST_EQUAL(c2, 'D');
    BHTEST_EQUAL(c3, 'G');
    BHTEST_EQUAL(b1[0], '1');
    BHTEST_EQUAL(b1[3], '4');
    BHTEST_EQUAL(b1[6], '7');

    vloga("清理与调整验证");
    b1.resize(20);
    bh::uint64 s1 = b1.size();
    b1.clear();
    bh::uint64 s2 = b1.size();

    BHTEST_EQUAL(s1, 20);
    BHTEST_EQUAL(s2, 0);
}

void test_4()
{
    vloga("内存管理与转换交换测试\n");

    vloga("内存控制");
    bh::Bbuf b1(10);
    b1.reserve(100);
    bh::uint64 c1 = b1.capacity();

    vloga("数据转换");
    bh::Bbuf b2("convert");
    bh::dstr str2 = b2.to_str();
    bh::Bview viw2 = b2.to_view();
    bh::dchp ptr2 = b2.data();

    vloga("转换结果验证");
    BHTEST_EQUAL(c1, 100);
    BHTEST_EQUAL(str2.size(), 7);
    BHTEST_EQUAL(viw2.size(), 7);
    BHTEST_EQUAL(ptr2[0], 'c');

    vloga("原子交换验证");
    bh::Bbuf b3("left");
    bh::Bbuf b4("right_side");
    b3.swap(b4);

    BHTEST_EQUAL(b3.size(), 10);
    BHTEST_EQUAL(b4.size(), 4);
    BHTEST_EQUAL(b3[0], 'r');
    BHTEST_EQUAL(b4[0], 'l');
}

int main(bh::int32 argc, char *argv[])
{
    //
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}