#include <iostream>

#include "Bdiv.h"
#include "Btime.h"

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

void test_2()
{
    auto a1 = bh::Bdiv("11##22##33##44")("##", 0, 1);
    auto a2 = bh::Bdiv("11##22##33##44")("##", 0, 2);
    auto a3 = bh::Bdiv("11##22##33##44")("##", 1, 2);
    auto a4 = bh::Bdiv("11##22##33##44")("##", 1, 3);

    auto b1 = bh::Bdiv("1#2#3#4")("#", 0, 0);
    auto b2 = bh::Bdiv("1#2#3#4")("#", 1, 1);
    auto b3 = bh::Bdiv("1#2#3#4")("#", 3, 3);
    auto b4 = bh::Bdiv("1#2#3#4")("#", -1, -1);
    auto b5 = bh::Bdiv("1#2#3#4")("#", -2, -2);
    auto b6 = bh::Bdiv("1#2#3#4")("#", -4, -4);

    auto c1 = bh::Bdiv("###111###222###333###444")("###", 1, 1);
    auto c2 = bh::Bdiv("###111###222###333###444")("###", 4, 4);
    auto c3 = bh::Bdiv("###111###222###333###444")("###", -1, -1);
    auto c4 = bh::Bdiv("###111###222###333###444")("###", -4, -4);

    vloga("多段分割");
    BHTEST_EQUAL(a1, "11##22");
    BHTEST_EQUAL(a2, "11##22##33");
    BHTEST_EQUAL(a3, "22##33");
    BHTEST_EQUAL(a4, "22##33##44");

    vloga("单字符分割");
    BHTEST_EQUAL(b1, "1");
    BHTEST_EQUAL(b2, "2");
    BHTEST_EQUAL(b3, "4");
    BHTEST_EQUAL(b4, "4");
    BHTEST_EQUAL(b5, "3");
    BHTEST_EQUAL(b6, "1");

    vloga("多字符分割");
    BHTEST_EQUAL(c1, "111");
    BHTEST_EQUAL(c2, "444");
    BHTEST_EQUAL(c3, "444");
    BHTEST_EQUAL(c4, "111");
}

void test_3()
{
    auto a1 = bh::Bdiv("[main_Bdiv.cpp:102][2026-02-06.21:25:19.664]")(".", 1, 1, ":", 0, 0);
    auto a2 = bh::Bdiv("[main_Bdiv.cpp:102][2026-02-06.21:25:19.664]")("[", 2, 2, "-", 0, 0);
    auto a3 = bh::Bdiv("[main_Bdiv.cpp:102][2026-02-06.21:25:19.664]")("[", 2, 2, "-", 1, 1);
    auto a4 =
        bh::Bdiv("[main_Bdiv.cpp:102][2026-02-06.21:25:19.664]")("cpp", 0, 0, "main_Bdiv", 1, 1);
    auto a5 =
        bh::Bdiv("[main_Bdiv.cpp:102][2026-02-06.21:25:19.664]")("main_Bdiv", 1, 1, "cpp", 0, 0);

    vloga("精准分割");
    BHTEST_EQUAL(a1, "cpp");
    BHTEST_EQUAL(a2, "2026");
    BHTEST_EQUAL(a3, "02");
    BHTEST_EQUAL(a4, ".");
    BHTEST_EQUAL(a5, ".");
}

void test_4()
{
    bh::int32 sum = 1000 * 10000;
    bh::Btimel t1;
    bh::Bstr s1;
    for(bh::int32 i = 0; i < sum; i++) {
        s1 = bh::Bdiv("##100##<<abc-hellow world-1992/4/3 15:12:54>>")("##", 2, 2, " ", 1, 1, "-",
                                                                       1, 1);
    }

    vloga("速度测试");
    vlogd($(sum) $(s1) $(t1.to_str()));

    /*
        [All]<<<< 速度测试 >>>>
        [sum: 10000000] [nan: 2265625724|mic: 2265625|mil: 2265|sec: 2]
    */
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}