

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "Ffm.h"
#include "Tlog.h"

using namespace bhtools;

void test_1()
{
    {
        std::string s = "<<--++((##";
        {
            auto tup = Ffinds::find_sub(s,"<<");
            auto s1 = std::get<0>(tup);
            auto s2 = std::get<1>(tup);
            vlogd($(s1) $(s2));
        }
        {
            auto tup = Ffinds::find_sub(s,"++");
            auto s1 = std::get<0>(tup);
            auto s2 = std::get<1>(tup);
            vlogd($(s1) $(s2));
        }
        {
            auto tup = Ffinds::find_sub(s,"##");
            auto s1 = std::get<0>(tup);
            auto s2 = std::get<1>(tup);
            vlogd($(s1) $(s2));
        }
        {
            auto tup = Ffinds::find_sub(s,"}}");
            auto s1 = std::get<0>(tup);
            auto s2 = std::get<1>(tup);
            vlogd($(s1) $(s2));
        }
    }
    {
        std::string s = "{{{{1111}}}}--{{{{2222}}}}--{{{{3333}}}}";
        {
            auto tup = Ffinds::find_range(s,"{{{{","}}}}");
            auto s1 = std::get<0>(tup);
            auto s2 = std::get<1>(tup);
            auto s3 = std::get<2>(tup);
            auto s4 = std::get<3>(tup);
            vlogi($(s1) $(s2) $(s3) $(s4));
        }
        {
            size_t offset = 0;
            for(int i=0;i<s.size();i++)
            {
                auto tup = Ffinds::find_range(s,"{{{{","}}}}",offset);
                auto s1 = std::get<0>(tup);
                auto s2 = std::get<1>(tup);
                auto s3 = std::get<2>(tup);
                auto s4 = std::get<3>(tup);
                offset = s3;
                i += s3;
                vlogd($(s1) $(s2) $(s3) $(s4) $(i) $(offset) );
            }
        }
    }
    {
        std::string s = "{1}{2}{3}";
        {
            auto tup = Ffinds::find_range(s,"{","}");
            auto s1 = std::get<0>(tup);
            auto s2 = std::get<1>(tup);
            auto s3 = std::get<2>(tup);
            auto s4 = std::get<3>(tup);
            vlogi($(s1) $(s2) $(s3) $(s4));
        }
        {
            size_t offset = 0;
            for(int i=0;i<s.size();i++)
            {
                auto tup = Ffinds::find_range(s,"{","}",offset);
                auto s1 = std::get<0>(tup);
                auto s2 = std::get<1>(tup);
                auto s3 = std::get<2>(tup);
                auto s4 = std::get<3>(tup);
                offset = s3+1;
                i = offset;
                vlogd($(s1) $(s2) $(s3) $(s4) $(i) $(offset) );
            }
        }
    }
    {
        std::string s = "#{11}#{1}{2}{3}#{33}#";
        {
            auto tup = Ffinds::find_range(s,"{","}");
            auto s1 = std::get<0>(tup);
            auto s2 = std::get<1>(tup);
            auto s3 = std::get<2>(tup);
            auto s4 = std::get<3>(tup);
            vlogi($(s1) $(s2) $(s3) $(s4));
        }
        {
            size_t offset = 0;
            for(int i=0;i<s.size();i++)
            {
                auto tup = Ffinds::find_range(s,"{","}",offset);
                auto s1 = std::get<0>(tup);
                auto s2 = std::get<1>(tup);
                auto s3 = std::get<2>(tup);
                auto s4 = std::get<3>(tup);
                offset = s3+1;
                i = offset;
                vlogd($(s1) $(s2) $(s3) $(s4) $(i) $(offset) );
            }
        }
    }
    {
        std::string s = "#{11}#{1}{2}{3}#{33}#";
        auto s1 = Ffinds::section_range(s,0,6);
        auto s2 = Ffinds::section_range(s,1,5);
        auto s3 = Ffinds::section_range(s,16,20);
        auto s4 = Ffinds::section_range(s,0,100);
        auto s5 = Ffinds::section_range(s,20,21);
        auto s6 = Ffinds::section_range(s,15,23);
        auto s7 = Ffinds::section_range(s,0,1);
        auto s8 = Ffinds::section_range(s,0,21);
        auto s9 = Ffinds::section_range(s,0,s.size());

        vlogi($(s1) $(s2) $(s3) $(s4) $(s5) $(s6) $(s7) $(s8) $(s9));
    }
}


int main(int argc, char *argv[])
{


    test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();

    return 0;
}