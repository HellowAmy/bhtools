

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

void test_3()
{
    {
        auto s1 = Tfrom_string_opt<int>("123");
        auto s2 = Tfrom_string_opt<size_t>("2003998899");
        auto s3 = Tfrom_string_opt<double>("123.456");

        vlogd($(s1.use()) $(s2.use()) $(s3.use()));
        vlogd($(s1.value()) $(s2.value()) $(s3.value()));
    }
    {
        auto s1 = Tfrom_string_opt<int>("2a");
        auto s2 = Tfrom_string_opt<size_t>("3dva2");
        auto s3 = Tfrom_string_opt<double>("909.aw02");

        vlogd($(s1.use()) $(s2.use()) $(s3.use()));
        vlogd($(s1.value()) $(s2.value()) $(s3.value()));
    }
}

void test_4()
{
    {
        Topt<int> s1 = Tfrom_string_opt<int>("123");
        Topt<int> s2 = Tfrom_string_opt<int>("a123");
        if(s1.use())
        {
            vlogd($(s1.value()));
        }
        if(s2.use())
        {
            vlogd($(s2.value()));
        }
    }
    {
        auto s1 = Tfrom_string_opt<int>("123");
        auto s2 = Tfrom_string_opt<int>("a123");
        if(s1)
        {
            vlogd($(*s1));
        }
        if(s2)
        {
            vlogd($(*s2));
        }
    }
    

}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    // test_3();   
    test_4();   
    // test_5();
    // test_6();


    return 0;
}