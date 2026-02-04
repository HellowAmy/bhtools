#include <iostream>
#include <cstring>

#include "Bstrbc.h"

#include "Ftest.h"

void test_1()
{
    bh::dchr cs1[] = "hello world";
    bh::cchp cs2 = "hello world";
    bh::dstr cs3 = "hello world";
    bh::cstr cs4 = "hello world";

    bh::Bstrbc s1(cs1, sizeof(cs1));
    bh::Bstrbc s2(cs2, strlen(cs2));
    bh::Bstrbc s3(cs3);
    bh::Bstrbc s4(cs4);
    bh::Bstrbc s5 = s4;

    vloga("打印测试");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
    vlogd($(s5));
}

void test_2() {}

int main(int argc, char *argv[])
{
    test_1();
    // test_2();

    return 0;
};