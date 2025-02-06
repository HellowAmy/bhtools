

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "Tlog.h"




void test_1()
{
    using namespace bhtools;
    Tlog_cmd4 t1;
    t1.set_level(*_sp_level4_<<el4::e_inf);

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
    using namespace bhtools;
    Tlog_cmd8 t1;
    t1.set_level(Tlog_level<bhenum::level8>(bhenum::level8::e_war));

    const char *s1 = "s11";
    std::string s2 = "s22";
    int si3 = 1024;

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_all);
    t1<<"e_all";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_tra);
    t1<<"e_trace";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_deb);
    t1<<"e_debug";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_inf);
    t1<<"e_info";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_war);
    t1<<"e_warning";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_err);
    t1<<"e_error";
    t1<<Tlog_end();

    t1<<Tlog_level<bhenum::level8>(bhenum::level8::e_fat);
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
    using namespace bhtools;
    (*_sp_cmd4_)<<Tlog_level<bhenum::level4>(bhenum::level4::e_inf);
    (*_sp_cmd4_)<<"info  ";
    (*_sp_cmd4_)<<123<<456<<"|"<<99.99<<" po ";
    (*_sp_cmd4_)<<123.123;
    (*_sp_cmd4_)<<"123";
    (*_sp_cmd4_)<<Tlog_end();


    // 快捷命令行打印-自行扩展 等级8
    #define vlogd8(...) BHLOG_PRINT((*_sp_cmd8_),"\033[32m[Deb-level8]","\033[0m"<<(*_sp_end_),BHLOG_FORMAT_VSC,_sp_level8_->set_level(bhenum::level8::e_deb),__VA_ARGS__)
    #define vloge8(...) BHLOG_PRINT((*_sp_cmd8_),"\033[31m[Err-level8]","\033[0m"<<(*_sp_end_),BHLOG_FORMAT_VSC,_sp_level8_->set_level(bhenum::level8::e_err),__VA_ARGS__)

    vlogd("123"<<123<<"pps");
    vlogi("123"<<123<<"pps");
    vlogw("123"<<123<<"pps");
    vloge("123"<<123<<"pps");

    vlogd8("11"<<"OOP"<<999);
    vloge8("11"<<"OOP"<<999);

    int s1 = 100;
    double s2 = 123.123;
    std::string s3 = "asdsa";

    vlogd($("123") $(s1) $(s2) $(s3));
}

void test_4()
{
    using namespace bhtools;
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

    vlogd(Tlog_con(c1,0,",",""));
    vlogd(Tlog_con(c1,5,"-","| "));

    vlogi(Tlog_con(c2));
    vlogw(Tlog_con(c3));

    vloge($C(c1));
}


void test_5()
{
    using namespace bhtools;
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
    using namespace bhtools;
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

void test_7()
{
    using namespace bhtools;
    size_t len = (1<<15);
    _sp_file4_->_out.set_length(len);
    _sp_file4_->_out.set_limit(10);

    for(int i=0;i<100;i++)
    {
        floge($(i) $("2445") $(std::to_string(i)));
        flogd($(i) $("dd2445") $(std::to_string(i)));
        vlogd($(i) $("dd2445") $(std::to_string(i)));
        vloge($(i) $("2445") $(std::to_string(i)));
        vlogw("war");
    }
}

void test_8()
{
    using namespace bhtools;
    {
        auto s1 = Tlog_time::get_time();
        for(int i=0;i<100;i++)
        {
            vlogd($(s1));
        }
    }
}

void test_9()
{
    using namespace bhtools;
    int count = 10000000;
    double ss1 = 55.5; 
    std::string ss2 = "hellow world"; 
    // {
    //     Ftimel t;
    //     for(int i=0;i<count;i++)
    //     {
    //         vlogd($(i) $(count) $(ss1) $(ss2));
    //     }
    //     vlogd($(t.to_string()));
    // }
    {
        Ftimel t;
        for(int i=0;i<count;i++)
        {
            aflogd($(i) $(count) $(ss1) $(ss2));
        }
        vlogd($(t.to_string()));
    }
    {
        Ftimel t;
        for(int i=0;i<count;i++)
        {
            flogd($(i) $(count) $(ss1) $(ss2));
        }
        vlogd($(t.to_string()));
    }
    // {
    //     Ftimel t;
    //     for(int i=0;i<count;i++)
    //     {
    //         nulogd($(i) $(count) $(ss1) $(ss2));
    //     }
    //     vlogd($(t.to_string()));
    // }
    std::string sr1;
    std::string sr2;
    std::string sr3;
    // {
    //     Ftimel t;
    //     for(int i=0;i<count;i++)
    //     {
    //         std::cout<<i<<count<<ss1<<ss2<<std::endl;

    //         // vlogd($(i) $(count) $(ss1) $(ss2));
    //     }
    //     sr3 = t.to_string();
    // }
    // {
    //     Ftimel t;
    //     for(int i=0;i<count;i++)
    //     {
    //         (*_sp_cmd4_)<<Tlog_level<bhenum::level4>(bhenum::level4::e_deb)<<$(i) $(count) $(ss1) $(ss2)<<Tlog_end();
    //     }
    //     sr1 = t.to_string();
    // }
    // {
    //     Ftimel t;
    //     for(int i=0;i<count;i++)
    //     {
    //         (*_sp_cmd4_)<<_sp_level4_->set_level(bhenum::level4::e_deb)<<$(i) $(count) $(ss1) $(ss2)<<*_sp_end_;
    //     }
    //     sr2 = t.to_string();
    // }
    vlogd($(sr1) $(sr2) $(sr3));
}


void test_10()
{
    using namespace bhtools;
    int count = 10000000;
    double ss1 = 55.5; 
    std::string ss2 = "hellow world"; 


    {
        Ftimel t;
        for(int i=0;i<count;i++)
        {
            aflogd("==1=="<<$(ss1) $(ss2) $(i));
        }
        auto v1 = t.to_string();
        vlogd(v1);
    }

    // {
    //     Ftimel t;
    //     for(int i=0;i<count;i++)
    //     {
    //         flogd("==2=="<<$(ss1) $(ss2) $(i));
    //     }
    //     auto v1 = t.to_string();
    //     vlogd(v1);
    // }

  

    // auto fn_th1 = [=](){
    //     {
    //         Ftimel t;
    //         for(int i=0;i<count;i++)
    //         {
    //             aflogd("==1=="<<$(ss1) $(ss2) $(i));
    //         }
    //         auto v1 = t.to_string();
    //         vlogd(v1);
    //     }
    // };

    // auto fn_th2 = [=](){
    //     {
    //         Ftimel t;
    //         for(int i=0;i<count;i++)
    //         {
    //             aflogd("==2=="<<$(ss1) $(ss2) $(i));
    //         }
    //         auto v1 = t.to_string();
    //         vlogd(v1);
    //     }
    // };

    // _sp_afile4_->_out._out.reopen("Tflog.log",false);

    // std::thread(fn_th1).detach();
    // std::thread(fn_th2).detach();


    sleep(100);

    
}

void test_11()
{
    using namespace bhtools;
    #define aflogd_th1(...) BHLOG_MAKE_L4D((*_sp_th1_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
    #define aflogi_th1(...) BHLOG_MAKE_L4I((*_sp_th1_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
    #define aflogw_th1(...) BHLOG_MAKE_L4W((*_sp_th1_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
    #define afloge_th1(...) BHLOG_MAKE_L4E((*_sp_th1_),(*_sp_end_),_sp_level4_,__VA_ARGS__)

    #define aflogd_th2(...) BHLOG_MAKE_L4D((*_sp_th2_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
    #define aflogi_th2(...) BHLOG_MAKE_L4I((*_sp_th2_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
    #define aflogw_th2(...) BHLOG_MAKE_L4W((*_sp_th2_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
    #define afloge_th2(...) BHLOG_MAKE_L4E((*_sp_th2_),(*_sp_end_),_sp_level4_,__VA_ARGS__)

    static Tlog_asyn_file4 *_sp_th1_ = new Tlog_asyn_file4;
    _sp_th1_->_out._out.reopen("Tflog_th1.log");

    static Tlog_asyn_file4 *_sp_th2_ = new Tlog_asyn_file4;
    _sp_th2_->_out._out.reopen("Tflog_th2.log");


    int count = 1000000;
    double ss1 = 55.5; 
    std::string ss2 = "hellow world"; 

    auto fn_th1 = [=](){
        {
            Ftimel t;
            for(int i=0;i<count;i++)
            {
                aflogd_th1("==1=="<<$(ss1) $(ss2) $(i));
            }
            auto v1 = t.to_string();
            vlogd(v1);

            // 需要手动刷新否则缓冲区数据丢失-需要等待异步写入完成
            sleep(2);
            _sp_th1_->flush();
        }
    };

    auto fn_th2 = [=](){
        {
            Ftimel t;
            for(int i=0;i<count;i++)
            {
                aflogd_th2("==2=="<<$(ss1) $(ss2) $(i));
            }
            auto v1 = t.to_string();
            vlogd(v1);

            
            // sleep(2);
            // _sp_th2_->flush();
        }
    };

    auto fn_th3 = [=](){
        {
            Ftimel t;
            for(int i=0;i<count;i++)
            {
                flogd("==3=="<<$(ss1) $(ss2) $(i) $(count));
            }
            auto v1 = t.to_string();
            vlogd(v1);
        }
        _sp_file4_->flush();
    };

    _sp_afile4_->_out._out.reopen("Tflog.log",false);

    std::thread (fn_th1).detach();
    std::thread (fn_th2).detach();
    std::thread (fn_th3).detach();
    sleep(15);


}

void test_12()
{

    std::string h = "hellow world";

    aflogd($(h));
    aflogi($(h));
    aflogw($(h));
    afloge($(h));

    aflogd("Debug");
    aflogi("Info");
    aflogw("Warn");
    afloge("Error");

    flogd($(h));
    flogi($(h));
    flogw($(h));
    floge($(h));

    vlogd($(h));
    vlogi($(h));
    vlogw($(h));
    vloge($(h));

    std::this_thread::sleep_for(std::chrono::seconds(2));

}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    test_3();   
    // test_4();   
    // test_5();
    // test_6();
    // test_7();
    // test_8();
    // test_9();
    // test_10();
    // test_11();
    test_12();




    return 0;
}