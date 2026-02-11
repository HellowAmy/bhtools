
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

    asy.next([](tets_a1_arg *arg) {
        auto s1 = arg->account;
        auto s2 = arg->password;
        vlogd("登陆账号 "<<$(s1) $(s2));

        bhtools::Ftimel::sleep(500);
        if(s1 == "123990" && s2 == "abcd")
        {
            arg->suc.name = "小明";
            return true;
        }   
        tets_a1_err e;
        e.step = 1;
        e.info = "登陆失败";
        arg->err = e;
        return false;

    }).next([](tets_a1_arg *arg){
        auto s1 = arg->path;
        auto s2 = arg->suc.name;
        vlogd("下载图片 "<<$(s1) $(s2));
        bhtools::Ftimel::sleep(500);
        if(s1 == "/home/1" && s2 == "小明")
        {
            arg->suc.token = "xxx";
            return true;
        }
        tets_a1_err e;
        e.step = 2;
        e.info = "下载失败";
        arg->err = e;
        return false;
    }).next([](tets_a1_arg *arg) {
        auto s1 = arg->suc.token;
        auto s2 = arg->sum;
        vlogd("拉取好友 "<<$(s1));
        bhtools::Ftimel::sleep(500);
        if(s1 == "xxx" && s2 == 4)
        {
            arg->suc.frends = {"a1","a2","a3","a4"};
            return true;
        }
        tets_a1_err e;
        e.step = 3;
        e.info = "拉取失败";
        arg->err = e;
        return false;
    }).error([](tets_a1_arg *arg) {
        vlogd("失败 "<<$(arg->err.step) $(arg->err.info));
    }).succee([](tets_a1_arg *arg) {
        vlogd("成功 "<<$(arg->suc.name) $(arg->suc.token) $C(arg->suc.frends));
    });

    // 测试异步操作
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd";
        arg.path = "/home/1";
        arg.sum = 4;
        bool ok = asy.run(&arg);
        vlogd($(ok));
        bhtools::Ftimel::sleep(2000);
    }
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd";
        arg.path = "/home/1";
        arg.sum = 2;
        bool ok = asy.run(&arg);
        vlogd($(ok));
        bhtools::Ftimel::sleep(2000);
    }
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd";
        arg.path = "/home/1111";
        arg.sum = 2;
        bool ok = asy.run(&arg);
        vlogd($(ok));
        bhtools::Ftimel::sleep(2000);
    }
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd22";
        arg.path = "/home/1111";
        arg.sum = 2;
        bool ok = asy.run(&arg);
        vlogd($(ok));
        bhtools::Ftimel::sleep(2000);
    }
    {
        tets_a1_arg arg;
        arg.account = "123990";
        arg.password = "abcd22";
        arg.path = "/home/1111";
        arg.sum = 2;
        bool ok = asy.run(nullptr);
        vlogd($(ok));
        bhtools::Ftimel::sleep(2000);
    }


}


void test_2()
{
    // 无参数异步
    bhtools::Tasync<void> asy;

    asy.next([](void *) {
        vlogd($("step 1"));
        bhtools::Ftimel::sleep(500);
        return true;
    }).next([](void *) {
        vlogd($("step 2"));
        bhtools::Ftimel::sleep(500);
        return true;
    }).next([](void *) {
        vlogd($("step 3"));
        bhtools::Ftimel::sleep(500);
        return true;
    }).succee([](void *){
        vlogd($("succee"));
    }).error([](void *){
        vlogd($("error"));
    });

    bool ok1 = asy.run();
    vlogd($("run1"));

    bool ok2 = asy.run();
    vlogd($("run2"));

    bool ok3 = asy.run();
    vlogd($("run3"));

    vlogd($(ok1) $(ok2) $(ok3));

    bhtools::Ftimel::sleep(2 * 1000);

}


struct tets_a2
{
    int index = 0;
    int data = 0;
};

void test_3()
{
    // 多任务重用
    bhtools::Tasync<tets_a2> asy;

    asy.next([&](tets_a2 *arg) {
        arg->data += 1;
        vlogd("step 1" $(arg->index) $(arg->data));
        bhtools::Ftimel::sleep(500);
        return true;
    }).next([&](tets_a2 *arg) {
        arg->data += 2;
        vlogd("step 1" $(arg->index) $(arg->data));
        bhtools::Ftimel::sleep(500);
        return true;
    }).next([&](tets_a2 *arg) {
        arg->data += 3;
        vlogd("step 1" $(arg->index) $(arg->data));
        bhtools::Ftimel::sleep(500);
        return true;
    }).succee([&](tets_a2 *arg){
        vlogd("succee" $(arg->index) $(arg->data));
    }).error([](tets_a2 *arg){
        vlogd("error" $(arg->index) $(arg->data));
    });


    std::vector<std::pair<tets_a2,bhtools::Tasync<tets_a2>>> vec_tasks;
    for(int i=0;i<10;i++)
    { 
        tets_a2 a;
        a.index = i;
        a.data = i + 10;
        vec_tasks.push_back(std::make_pair(a,asy));
    }
    for(int i=0;i<vec_tasks.size();i++)
    {
        bool ok = vec_tasks[i].second.run(&vec_tasks[i].first);
        vlogd($(ok) $(i));
    }

    vlogd("run");
    bhtools::Ftimel::sleep(3*1000);


    for(int i=0;i<vec_tasks.size();i++)
    {
        auto a = vec_tasks[i].first;
        vlogd($(a.index) $(a.data));
    }
    vlogd("data");

}

int main(int argc, char *argv[])
{
    // test_1();   
    test_2();   
    test_3();   

    return 0;
}