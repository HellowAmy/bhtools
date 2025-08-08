
#include <iostream>

#include "bhtools.h"

void test_1()
{
    // 转为字符串
    bool a1 = true;
    bool a2 = false;
    int a3 = 10;
    double a4 = 20.5;
    const char *a5 = nullptr;
    const char *a6 = "cs hellow";
    std::string a7 = "ss hellow";
    std::pair<int,int> a8(11,22);
    std::pair<std::string,int> a9("pp",22);
    std::tuple<int,double,int,std::string> a10(1111,4.5,300,"hh1");

    auto s1 = bhtools::Tstr::to_string(a1);
    auto s2 = bhtools::Tstr::to_string(a2);
    auto s3 = bhtools::Tstr::to_string(a3);
    auto s4 = bhtools::Tstr::to_string(a4);
    auto s5 = bhtools::Tstr::to_string(a5);
    auto s6 = bhtools::Tstr::to_string(a6);
    auto s7 = bhtools::Tstr::to_string(a7);
    auto s8 = bhtools::Tstr::to_string(a8);
    auto s9 = bhtools::Tstr::to_string(a9);
    auto s10 = bhtools::Tstr::to_string(a10);

    vlogd($(s1) $(s2) $(s3) $(s4));
    vlogd($(s5) $(s6) $(s7));
    vlogd($(s8) $(s9) $(s10));

    vlogd($(bhtools::Tstr::to_string("=====")));

    // 来自字符串
    int b1 = bhtools::Tstr::from_string<int>("123");
    double b2 = bhtools::Tstr::from_string<double>("44.44");
    int b3 = bhtools::Tstr::from_string<int>("aad44.44");
    double b4 = bhtools::Tstr::from_string<double>("aoiksd");

    vlogd($(b1) $(b2) $(b3) $(b4));

    // 来自字符串,判断是否成功
    int c1;
    double c2;
    int c3;
    int c4;
    int c5;
    bool ok1 = bhtools::Tstr::from_string("456",c1);
    bool ok2 = bhtools::Tstr::from_string("77.77",c2);
    bool ok3 = bhtools::Tstr::from_string("331aa44",c3);
    bool ok4 = bhtools::Tstr::from_string("as44",c4);
    bool ok5 = bhtools::Tstr::from_string("asdsc",c5);

    vlogd($(ok1) $(c1));
    vlogd($(ok2) $(c2));
    vlogd($(ok3) $(c3));
    vlogd($(ok4) $(c4));
    vlogd($(ok5) $(c5));
}
 
void test_2()
{
    // 查找子串
    {
        std::string ss = "123456 hellow world";
        std::string s1 = "hellow";
        std::string s2 = "123";
        std::string s3 = "yes";
        auto t1 = bhtools::Tstr::find_sub(ss,s1);
        auto t2 = bhtools::Tstr::find_sub(ss,s2);
        auto t3 = bhtools::Tstr::find_sub(ss,s3);
        auto t4 = bhtools::Tstr::find_sub(ss,s1,10);
    
        vlogd($(t1) $(t2) $(t3) $(t4));
    }

    // 获取标记类字符串
    {
        std::string ss = "{123456} [hellow] world";
        std::string s1 = "hellow";
        std::string s2 = "123";
        std::string s3 = "yes";
        auto t1 = bhtools::Tstr::find_range(ss,"{","}");
        auto t2 = bhtools::Tstr::find_range(ss,"[","]");
        auto t3 = bhtools::Tstr::find_range(ss,"{","}",10);
        auto t4 = bhtools::Tstr::find_range(ss,"#","#");
    
        vlogd($(t1) $(t2) $(t3) $(t4));
    }

    // 在已知范围内切割字符
    {
        std::string ss = "123456 hellow world";
        std::string s1 = "hellow";
        std::string s2 = "123";
        std::string s3 = "yes";
        auto t1 = bhtools::Tstr::section_range(ss,0,0);
        auto t2 = bhtools::Tstr::section_range(ss,0,6);
        auto t3 = bhtools::Tstr::section_range(ss,7,13);
        auto t4 = bhtools::Tstr::section_range(ss,0,100);
        auto t5 = bhtools::Tstr::section_range(ss,0,1);
    
        vlogd($(t1) $(t2) $(t3) $(t4) $(t5));
    }

}

void test_3()
{
    char a1 = '0';
    char a2 = 'a';
    char a3 = 'A';
    char a4 = '|';

    vlogd($(a1) $(a2) $(a3) $(a4));
}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    test_3();

    return 0;
}
