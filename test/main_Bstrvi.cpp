#include <iostream>
#include <cstring>

#include "Bstrvi.h"

#include "Tlog.h"
#include "Ftest.h"

void test_1()
{
    bh::dchr cs1[] = "hello world 1";
    bh::cchp cs2 = "hello world 2";
    bh::dstr cs3 = "hello world 3";
    bh::cstr cs4 = "hello world 4";

    bh::Bstrbc s1(cs1);
    bh::Bstrbc s2(cs2);
    bh::Bstrbc s3(cs3);
    bh::Bstrbc s4(cs4);

    bh::Bstrvi a1(cs1);
    bh::Bstrvi a2(cs2);
    bh::Bstrvi a3(cs3);
    bh::Bstrvi a4(cs4);
    bh::Bstrvi a5(s1);
    bh::Bstrvi a6(a2);

    vloga("全部长度");
    vlogd($(a1));
    vlogd($(a2));
    vlogd($(a3));
    vlogd($(a4));
    vlogd($(a5));
    vlogd($(a6));
}

void test_2()
{

    bh::dchr cs1[] = "hello world 1";
    bh::cchp cs2 = "hello world 2";
    bh::dstr cs3 = "hello world 3";
    bh::cstr cs4 = "hello world 4";
    bh::Bstrbc cs5("hello world 5");

    bh::Bstrvi a1(bh::Bstrvi(cs1, sizeof(cs1)));
    bh::Bstrvi a2(bh::Bstrvi(cs2, strlen(cs2)));
    bh::Bstrvi a3(cs3);
    bh::Bstrvi a4(cs4);
    bh::Bstrvi a5(cs5);
    bh::Bstrvi a6(a5);
    bh::Bstrvi a7 = a6;

    bh::Bstrvi b1(bh::Bstrvi(cs1, sizeof(cs1)), 0, 5);
    bh::Bstrvi b2(bh::Bstrvi(cs2, strlen(cs2)), 0, 8);
    bh::Bstrvi b3(bh::Bstrvi(cs3), 1, 8);
    bh::Bstrvi b4(bh::Bstrvi(cs4), 2, 8);

    vloga("全部长度");
    vlogd($(a1));
    vlogd($(a2));
    vlogd($(a3));
    vlogd($(a4));
    vlogd($(a5));
    vlogd($(a6));
    vlogd($(a7));

    vloga("截取数据");
    vlogd($(b1));
    vlogd($(b2));
    vlogd($(b3));
    vlogd($(b4));
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}