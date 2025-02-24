
#include <iostream>

#include "Tlog.h"
#include "Tasync.h"

using namespace bhtools;

struct Tct1
{
    int a1;
    std::string a2;
};

void test_1()
{
    Tasync<std::string> task;
    task.start<int>([](){
        int ret = 100;
        vlogd($(ret));
        return ret;
    }).next<std::string,int>([](int arg){
        std::string ret;
        ret += "ss" + std::to_string(arg);
        vlogd($(ret));
        return ret;
    }).end<std::string>([](std::string arg){
        arg += "end";
        vlogd($(arg));
        return arg;
    });
    task.run(false);

    std::string ret = task.get_value();
    vlogd("=====" << $(ret));
}

void test_2()
{
    Tasync<std::string> task;
    task.start<int>([](){
        int ret = 100;
        vlogd($(ret));
        Ftimel::sleep(1000);
        return ret;
    }).next<std::string,int>([](int arg){
        std::string ret;
        ret += "ss" + std::to_string(arg);
        vlogd($(ret));
        Ftimel::sleep(1000);
        return ret;
    }).end<std::string>([](std::string arg){
        arg += "end";
        vlogd($(arg));
        Ftimel::sleep(1000);
        return arg;
    });
    task.run(false);

    std::string ret = task.get_value();
    vlogd("=====" << $(ret));
}

void test_3()
{
    Tasync<std::string> task;
    task.start<int>([](){
        Ftimel::sleep(500);
        int ret = 100;
        vlogd($(ret));
        Ftimel::sleep(500);
        return ret;
    }).next<std::string,int>([](int arg){
        std::string ret;
        ret += "ss" + std::to_string(arg);
        vlogd($(ret));
        Ftimel::sleep(1000);
        return ret;
    }).end<std::string>([](std::string arg){
        arg += "end";
        vlogd($(arg));
        Ftimel::sleep(1000);
        return arg;
    });
    task.run();

    vlogd("== end ==");
    Ftimel::sleep(5000);
    std::string ret = task.get_value();
    vlogd("=====" << $(ret));
}

void test_4()
{
    Tasync<std::string> task;
    task.set_error_func([](std::string err){
        vlogd(err);
    });
    task.start<int>([](){
        Ftimel::sleep(500);
        int ret = 100;
        vlogd($(ret));
        Ftimel::sleep(500);
        return ret;
    }).next<std::string,int>([&](int arg){
        std::string ret;
        ret += "ss" + std::to_string(arg);
        vlogd($(ret));
        if(ret != "100")
        {
            task.stop_run("err100");
        }
        Ftimel::sleep(1000);
        return ret;
    }).end<std::string>([](std::string arg){
        arg += "end";
        vlogd($(arg));
        Ftimel::sleep(1000);
        return arg;
    });
    task.run();

    vlogd("== end ==");
    Ftimel::sleep(5000);
    std::string ret = task.get_value();
    vlogd("=====" << $(ret));
}

void test_5()
{
    Tasync<std::string> task;
    task.set_error_func([](std::string err){
        vlogd(err);
    });
    task.start<int>([](){
        Ftimel::sleep(500);
        int ret = 100;
        vlogd($(ret));
        Ftimel::sleep(500);
        return ret;
    }).next<std::string,int>([&](int arg){
        std::string ret;
        ret += "ss" + std::to_string(arg);
        vlogd($(ret));
        Ftimel::sleep(1000);
        return ret;
    }).end<std::string>([](std::string arg){
        arg += "end";
        vlogd($(arg));
        Ftimel::sleep(1000);
        return arg;
    });
    task.run();

    for(int i=0;i<100;i++)
    {
        vlogd("main program loop : " << i);
        if(task.is_run() == false)
        {
            if(task.is_suc())
            {
                auto ret = task.get_value();
                vlogd("ret: " << $(ret));
            }
            else 
            {
                vlogd("failed calc");
            }   
            break;
        }
        Ftimel::sleep(500);
    }
    vlogd("== end ==");
}

void test_6()
{
    Tasync<> task;
    task.next<int,nullptr_t>([](nullptr_t){
        int i=100;
        Ftimel::sleep(1000);
        return i;
    });
    task.next<int,int>([](int arg){
        arg += 1000;
        Ftimel::sleep(1000);
        return arg;
    });
    task.next<Tct1,int>([](int arg){
        Tct1 ct;
        ct.a1 = arg;
        ct.a2 = "ss" + std::to_string(arg);
        Ftimel::sleep(1000);
        return ct;
    });
    task.next<nullptr_t,Tct1>([](Tct1 arg){
        arg.a1 += 444;
        arg.a2 += "444ss";
        vlogd($(arg.a1) $(arg.a1));
        Ftimel::sleep(1000);
        return nullptr_t();
    });

    task.run();
    vlogd("== run ==");
    
    for(int i=0;i<100;i++)
    {
        if(task.is_run() == false)
        {
            break;
        }
        vlogd("main program loop : " << i);
        Ftimel::sleep(500);
    }
    vlogd("== end ==");
}


void test_7()
{
    Tasync<> task;
    task.next<std::string,std::string>([](std::string arg){
        std::string path = "/root/path/";
        path = path + arg;
        vlogi("load picture: " << $(path));
        Ftimel::sleep(300);
        return path;
    }).next<std::vector<size_t>,std::string>([](std::string arg){
        vlogi("load finish and send to 1000 account: " << $(arg));
        std::vector<size_t> vec;
        vec.resize(1000);
        Ftimel::sleep(300);
        return vec;
    }).next<bool,std::vector<size_t>>([](const std::vector<size_t> &arg){
        int i=0;
        for(auto &a:arg)
        {
            i++;
        }
        vlogi("send update notify:" << $(i));
        Ftimel::sleep(300);
        return true;
    });

    task.set_next_arg("logo.png");
    task.run();

    vlogd("== run ==");

    std::vector<std::string> vec {
        "logo.png",
        "desktop.png",
        "work.png",
        "travel.png",
    };
    
    int count = 0;
    for(int i=0;i<100;i++)
    {
        if(task.is_run() == false)
        {
            vlogd("in is_run");
            count++;
            if(count >= vec.size())
            {
                break;
            }
            task.set_next_arg(vec[count]);
            task.run();
        }
        vlogd("main program loop : " << i);
        Ftimel::sleep(500);
    }
    vlogd("== end ==");
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   
    test_4();   
    test_5();   
    test_6();   
    test_7();   

    return 0;
}