

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <vector>
#include <map>
#include <list>

#include "Tlog.h"

using namespace bhtools;


void test_1()
{
    Tlog_cmd4 t1;
    t1.set_level(logel4(el4::e_deb));

    const char *s1 = "s11";
    std::string s2 = "s22";
    int si3 = 1024;

    t1<<Tlog_level<bhenum::level4>(bhenum::level4::e_deb);
    t1<<"debug  ";
    t1<<123;
    t1<<123.123;
    t1<<"123";
    t1<<s1;
    t1<<s2;
    t1<<si3;
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level4>(bhenum::level4::e_inf);
    t1<<"info  ";
    t1<<123<<456<<"|"<<99.99<<" po ";
    t1<<123.123;
    t1<<"123";
    t1<<s1;
    t1<<s2;
    t1<<si3;
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level4>(bhenum::level4::e_war);
    t1<<"war  ";
    t1<<123;
    t1<<123.123;
    t1<<"123";
    t1<<s1;
    t1<<s2;
    t1<<si3;
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level4>(bhenum::level4::e_err);
    t1<<"err  ";
    t1<<123;
    t1<<123.123;
    t1<<"123";
    t1<<s1;
    t1<<s2;
    t1<<si3;
    t1<<Tlog_end();
}

void test_2()
{
    Tlog_cmd8 t1;
    t1.set_level(Tlog_level<bhenum::level8>(bhenum::level8::e_warning));

    const char *s1 = "s11";
    std::string s2 = "s22";
    int si3 = 1024;

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_all);
    t1<<"e_all";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_trace);
    t1<<"e_trace";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_debug);
    t1<<"e_debug";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_info);
    t1<<"e_info";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_warning);
    t1<<"e_warning";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_error);
    t1<<"e_error";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_fatal);
    t1<<"e_fatal";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_all);
    t1<<"e_all";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_off);
    t1<<"e_off";
    t1<<Tlog_end();
}

void test_3()
{
    (*_sp_cmd4_)<<Tlog_level<bhenum::level4>(bhenum::level4::e_inf);
    (*_sp_cmd4_)<<"info  ";
    (*_sp_cmd4_)<<123<<456<<"|"<<99.99<<" po ";
    (*_sp_cmd4_)<<123.123;
    (*_sp_cmd4_)<<"123";
    (*_sp_cmd4_)<<Tlog_end();

    vlogd("123"<<123<<"pps");
    vlogi("123"<<123<<"pps");
    vlogw("123"<<123<<"pps");
    vloge("123"<<123<<"pps");

    vlogd8("11"<<"OOP"<<999);

    int s1 = 100;
    double s2 = 123.123;
    std::string s3 = "asdsa";

    vlogd($("123") $(s1) $(s2) $(s3));
}

void test_4()
{
    std::vector<int> c1;
    std::vector<std::string> c2;
    std::list<int> c3;
    std::map<double,int> c4;

    for(int i=0;i<50;i++)
    {
        c1.push_back(i);
        c2.push_back("po:"+std::to_string(i));
        c3.push_back(i);
    }

    vlogd(Tlog_con(c1,"",",",0));
    vlogd(Tlog_con(c1,"| ","-",5));

    vlogi(Tlog_con(c2));
    vlogw(Tlog_con(c3));

    vloge($C(c1));
}


void test_5()
{
    for(int i=0;i<10;i++)
    {
        (*_sp_file4_)<<Tlog_level<bhenum::level4>(bhenum::level4::e_deb);
        (*_sp_file4_)<<123<<456<<"|"<<99.99<<" po ";
        (*_sp_file4_)<<123.123;
        (*_sp_file4_)<<"123";
        (*_sp_file4_)<<Tlog_end();

    }

    for(int i=0;i<10;i++)
    {
        flogd($("123")$(i));
        flogi($("123")$(i));
        flogw($("123")$(i));
        floge($("123")$(i));
    }
}

void test_6()
{
    size_t len = (1<<15);
    _sp_file4_->_out.set_length(len);
    _sp_file4_->_out.set_limit(10);

    for(int i=0;i<100000;i++)
    {
        flogd($("123") $("asjnkhdbasd  qwe") $(i) $("--pp=") $(std::to_string(i)));
        flogi($("123") $("asjnkhdbasd  qwe") $(i) $("--pp=") $(std::to_string(i)));
        flogw($("123") $("asjnkhdbasd  qwe") $(i) $("--pp=") $(std::to_string(i)));
        floge($("123") $("asjnkhdbasd  qwe") $(i) $("--pp=") $(std::to_string(i)));
    }
}

int main(int argc, char *argv[])
{


    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    test_6();

    return 0;
}