

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>

#include "Tbase.h"
#include "Tlog.h"

using namespace bhtools;


void test_1()
{
    int ic = 100;
    const char *cs = "hellow";
    std::string ss = "world";
    {
        auto s1 = Tto_string(ic);
        auto s2 = Tto_string(cs);
        auto s3 = Tto_string(ss);

        vlogd($(s1) $(s2) $(s3));
    }
}

void test_2()
{
    {
        auto s1 = Tfrom_string<int>("123");
        auto s2 = Tfrom_string<size_t>("2003998899");
        auto s3 = Tfrom_string<double>("123.456");

        vlogd($(s1) $(s2) $(s3));
    }

    {
        int s1;
        long long s2;
        double s3;
        auto ok1 = Tfrom_string<int>("123",s1);
        auto ok2 = Tfrom_string<long long>("2003998899",s2);
        auto ok3 = Tfrom_string<double>("123.456",s3);

        vlogd($(ok1) $(ok2) $(ok3) $(s1) $(s2) $(s3));
    }
    {
        int s1;
        size_t s2;
        short s3;
        auto ok1 = Tfrom_string<int>("a12a3s1.2",s1);
        auto ok2 = Tfrom_string<size_t>("2003998899",s2);
        auto ok3 = Tfrom_string<short>("123.456",s3);

        vlogd($(ok1) $(ok2) $(ok3) $(s1) $(s2) $(s3));
    }
    {
        int s1;
        size_t s2;
        unsigned int s3;
        auto ok1 = Tfrom_string<int>("-123",s1);
        auto ok2 = Tfrom_string<size_t>("2003998899",s2);
        auto ok3 = Tfrom_string<unsigned int>("-123",s3);

        vlogd($(ok1) $(ok2) $(ok3) $(s1) $(s2) $(s3));
    }


}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();


    return 0;
}