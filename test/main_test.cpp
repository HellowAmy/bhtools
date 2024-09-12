

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>

// #include "Fstm.h"
// #include "Tlog.h"
#include "Ftest.h"
// #include "Tpool.h"
// #include "Ftime.h"

using namespace bhtools;


void test_1()
{
    {
        int a = 5;
        int b = 4;
        BHTEST_EQUAL(a,b);
    }
    {
        int a = 4;
        int b = 4;
        BHTEST_EQUAL(a,b);
    }
    {
        double a = 5;
        int b = 4;
        BHTEST_EQUAL(a,b);
    }
    {
        double a = 4;
        int b = 4;
        BHTEST_EQUAL(a,b);
    }
    {
        std::string a = "hell";
        std::string b = "llwo";
        BHTEST_EQUAL(a,b);
    }
    {
        std::string a = "oo";
        std::string b = "oo";
        BHTEST_EQUAL(a,b);
    }
}

void test_2()
{
    {
        bool tr = false;
        BHTEST_TRUE(tr);
    } 
    {
        bool tr = true;
        BHTEST_TRUE(tr);
    } 
    {
        BHTEST_TRUE((3 == 3));
        BHTEST_TRUE((3 == 2));
    } 

}

int main(int argc, char *argv[])
{
    // test_1();   
    test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();

    return 0;
}