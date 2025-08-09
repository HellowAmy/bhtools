
#include <iostream>

#include "bhtools.h"

//
struct tets_a1_err
{
    int step = 0;
    std::string info;
};

struct tets_a1_suc
{
    std::string name;
    std::string token;
    std::vector<std::string> frends;
};

struct tets_a1_arg
{
    tets_a1_suc suc;
    tets_a1_err err;
    std::string account;
    std::string password;
    std::string path;
    size_t sum;
};

void test_1()
{
    // 测试异步执行顺序
    bhtools::Tasync<tets_a1_arg> asy;

    asy.next([](tets_a1_arg &arg) {
        auto s1 = arg.account;
        auto s2 = arg.password;
        vlogd("登陆账号 "<<$(s1) $(s2));

        bhtools::Ftimel::sleep(500);
        if(s1 == "123990" && s2 == "abcd")
        {
            arg.suc.name = "小明";
            return true;
        }   
        tets_a1_err e;
        e.step = 1;
        e.info = "登陆失败";
        arg.err = e;
        return false;

    }).next([](tets_a1_arg &arg){
        auto s1 = arg.path;
        auto s2 = arg.suc.name;
        vlogd("下载图片 "<<$(s1) $(s2));
        bhtools::Ftimel::sleep(500);
        if(s1 == "/home/1" && s2 == "小明")
        {
            arg.suc.token = "xxx";
            return true;
        }
        tets_a1_err e;
        e.step = 2;
        e.info = "下载失败";
        arg.err = e;
        return false;
    }).next([](tets_a1_arg &arg) {
        auto s1 = arg.suc.token;
        auto s2 = arg.sum;
        vlogd("拉取好友 "<<$(s1));
        bhtools::Ftimel::sleep(500);
        if(s1 == "xxx" && s2 == 4)
        {
            arg.suc.frends = {"a1","a2","a3","a4"};
            return true;
        }
        tets_a1_err e;
        e.step = 3;
        e.info = "拉取失败";
        arg.err = e;
        return false;
    }).error([](tets_a1_arg arg) {
        vlogd("失败 "<<$(arg.err.step) $(arg.err.info));
    }).succee([](tets_a1_arg arg) {
        vlogd("成功 "<<$(arg.suc.name) $(arg.suc.token) $C(arg.suc.frends));
    });

    // 测试异步操作
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd";
        arg.path = "/home/1";
        arg.sum = 4;
        asy.run(arg);
        bhtools::Ftimel::sleep(2000);
    }
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd";
        arg.path = "/home/1";
        arg.sum = 2;
        asy.run(arg);
        bhtools::Ftimel::sleep(2000);
    }
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd";
        arg.path = "/home/1111";
        arg.sum = 2;
        asy.run(arg);
        bhtools::Ftimel::sleep(2000);
    }
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd22";
        arg.path = "/home/1111";
        arg.sum = 2;
        asy.run(arg);
        bhtools::Ftimel::sleep(2000);
    }


}

int main(int argc, char *argv[])
{
    test_1();   

    return 0;
}