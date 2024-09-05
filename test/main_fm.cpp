

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "Ffm.h"
#include "Tlog.h"
#include "Ftime.h"

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

void test_2()
{
    {
        std::string s = "{0}{1}{2}";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fsfm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "#{0}#{1}#{2}#";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fsfm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "##{0}##{1}##{2}##";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fsfm(s)(a,b);
        vlogd($(s1));
    }
    {
        std::string s = "##{0}##{1}##";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fsfm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "##{0}##{1}##{0}##{1}##{2}";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fsfm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "##{2}##{1}##{0}##";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fsfm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        auto s1 = Fsfm("##{2}##{1}##{0}##")(100,3.145,"hellow");
        vlogd($(s1));
    }
}

void test_3()
{
    {
        std::string s = "{}{}{}";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fffm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "#{}#{}#{}#";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fffm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "##{}##{}##";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fffm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "######";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fffm(s)(a,b,c);
        vlogd($(s1));
    }
    {
        std::string s = "##{}##{}##{}##";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = Fffm(s)(c,b,a);
        vlogd($(s1));
    }
    {
        auto s1 = Fffm("##{}##{}##{}##")(100,3.145,"hellow");
        vlogd($(s1));
    }
}

template<class... T>
std::string formatf(const char *fmt, const T&...t)
{
    const auto len = snprintf(nullptr, 0, fmt, t...);
    std::string r;
    r.resize(static_cast<size_t>(len) + 1);
    snprintf(&r.front(), len + 1, fmt, t...);  // Bad boy
    r.resize(static_cast<size_t>(len));
 
    return r;
}

void test_4()
{
    int count = 10000000;
    // int count = 1;

    short a = 128;
    int b = 1024;
    float c = 123.123;
    double d = 456.456;
    const char * e = "hellow";
    std::string f = "world";

    {
        Ftimel t;
        char buf[64];
        for(int i=0;i<count;i++)
        {   
            memset(buf,0x00,sizeof(buf));
            sprintf(buf,"<<%d-%d-%d-%f-%f-%s-%s>>",i,a,b,c,d,e,f.c_str());
            std::string s(buf);
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
    {
        Ftimel t;
        for(int i=0;i<count;i++)
        {   
            std::string s = formatf("<<%d-%d-%d-%f-%f-%s-%s>>",i,a,b,c,d,e,f);
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
    {
        Ftimel t;
        for(int i=0;i<count;i++)
        {   
            std::string s = Fsfm("<<{0}-{1}-{2}-{3}-{4}-{5}-{6}>>")(i,a,b,c,d,e,f);
        }
        auto s1 = t.to_string();
        vlogd($(s1));
    }
    {
        Ftimel t;
        for(int i=0;i<count;i++)
        {   
            std::string s = Fffm("<<{}-{}-{}-{}-{}-{}-{}>>")(i,a,b,c,d,e,f);
        }
        auto s1 = t.to_string();
        vlogd($(s1));
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