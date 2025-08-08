
#include <iostream>

#include "bhtools.h"


void test_1()
{
    // 快捷宏测试
    {
        int a = 10;
        int b = 20;
        BHTEST_EQUAL(a,b);
    }
    {
        int a = 10;
        int b = 10;
        BHTEST_EQUAL(a,b);
    }
    {
        std::string a = "hellow";
        std::string b = "hello";
        BHTEST_EQUAL(a,b);
    }
    {
        std::string a = "hellow";
        std::string b = "hellow";
        BHTEST_EQUAL(a,b);
    }
    {
        bool ok = false;
        BHTEST_TRUE(ok);
    } 
    {
        bool ok = true;
        BHTEST_TRUE(ok);
    } 
    {
        BHTEST_TRUE((10 == 20));
        BHTEST_TRUE((10 == 10));
    } 
    {
        const char *p1= nullptr;
        const char *p2= "hellow";

        BHTEST_NULL(p1);
        BHTEST_NULL(p2);
    }

}


int main(int argc, char *argv[])
{
    test_1();   

    return 0;
}