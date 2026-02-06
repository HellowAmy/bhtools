#include <iostream>

#include "Bdiv.h"
#include "Ftest.h"

void test_1()
{
    auto a1 = bh::Bdiv("11##22##33##44")("##", 0, 0);
    auto a2 = bh::Bdiv("11##22##33##44")("##", 1, 1);
    auto a3 = bh::Bdiv("11##22##33##44")("##", 2, 2);
    auto a4 = bh::Bdiv("11##22##33##44")("##", 3, 3);
    auto a5 = bh::Bdiv("11##22##33##44")("##", 4, 4);

    auto b1 = bh::Bdiv("##11##22##33##44##")("##", 0, 0);
    auto b2 = bh::Bdiv("##11##22##33##44##")("##", 1, 1);
    auto b3 = bh::Bdiv("##11##22##33##44##")("##", 2, 2);
    auto b4 = bh::Bdiv("##11##22##33##44##")("##", 3, 3);
    auto b5 = bh::Bdiv("##11##22##33##44##")("##", 4, 4);
    auto b6 = bh::Bdiv("##11##22##33##44##")("##", 5, 5);
    auto b7 = bh::Bdiv("##11##22##33##44##")("##", 6, 6);

    auto c1 = bh::Bdiv("11##22##33##44")("##", -1, -1);
    auto c2 = bh::Bdiv("11##22##33##44")("##", -2, -2);
    auto c3 = bh::Bdiv("11##22##33##44")("##", -3, -3);
    auto c4 = bh::Bdiv("11##22##33##44")("##", -4, -4);
    auto c5 = bh::Bdiv("11##22##33##44")("##", -5, -5);

    auto d1 = bh::Bdiv("##11##22##33##44##")("##", -1, -1);
    auto d2 = bh::Bdiv("##11##22##33##44##")("##", -2, -2);
    auto d3 = bh::Bdiv("##11##22##33##44##")("##", -3, -3);
    auto d4 = bh::Bdiv("##11##22##33##44##")("##", -4, -4);
    auto d5 = bh::Bdiv("##11##22##33##44##")("##", -5, -5);
    auto d6 = bh::Bdiv("##11##22##33##44##")("##", -6, -6);
    auto d7 = bh::Bdiv("##11##22##33##44##")("##", -7, -7);

    auto e1 = bh::Bdiv("11##22##33##44")("##", 0, -1);
    auto e2 = bh::Bdiv("11##22##33##44")("##", 0, -2);
    auto e3 = bh::Bdiv("11##22##33##44")("##", 1, -3);
    auto e4 = bh::Bdiv("11##22##33##44")("##", 2, -3);

    auto f1 = bh::Bdiv("##11##22##33##44##")("##", 0, -1);
    auto f2 = bh::Bdiv("##11##22##33##44##")("##", 0, -2);
    auto f3 = bh::Bdiv("##11##22##33##44##")("##", 1, -3);
    auto f4 = bh::Bdiv("##11##22##33##44##")("##", 2, -3);
    auto f5 = bh::Bdiv("##11##22##33##44##")("##", 3, -3);

    vloga("切割测试");
    BHTEST_EQUAL(a1, "11");
    BHTEST_EQUAL(a2, "22");
    BHTEST_EQUAL(a3, "33");
    BHTEST_EQUAL(a4, "44");
    BHTEST_EQUAL(a5, "");

    vloga("边界测试");
    BHTEST_EQUAL(b1, "");
    BHTEST_EQUAL(b2, "11");
    BHTEST_EQUAL(b3, "22");
    BHTEST_EQUAL(b4, "33");
    BHTEST_EQUAL(b5, "44");
    BHTEST_EQUAL(b6, "");
    BHTEST_EQUAL(b7, "");

    vloga("反向测试");
    BHTEST_EQUAL(c1, "44");
    BHTEST_EQUAL(c2, "33");
    BHTEST_EQUAL(c3, "22");
    BHTEST_EQUAL(c4, "11");
    BHTEST_EQUAL(c5, "");

    vloga("边界反向测试");
    BHTEST_EQUAL(d1, "");
    BHTEST_EQUAL(d2, "44");
    BHTEST_EQUAL(d3, "33");
    BHTEST_EQUAL(d4, "22");
    BHTEST_EQUAL(d5, "11");
    BHTEST_EQUAL(d6, "");
    BHTEST_EQUAL(d7, "");

    vloga("双向测试");
    BHTEST_EQUAL(e1, "11##22##33##44");
    BHTEST_EQUAL(e2, "11##22##33");
    BHTEST_EQUAL(e3, "22");
    BHTEST_EQUAL(e4, "");

    vloga("边界双向测试");
    BHTEST_EQUAL(f1, "##11##22##33##44##");
    BHTEST_EQUAL(f2, "##11##22##33##44");
    BHTEST_EQUAL(f3, "11##22##33");
    BHTEST_EQUAL(f4, "22##33");
    BHTEST_EQUAL(f5, "33");
}

void test_2() {}

int main(int argc, char *argv[])
{
    test_1();
    // test_2();

    return 0;
}