 
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "bhtools.h"


// 通用处理模板-带返回值
// 用于定义参数-计算分数等级
struct test_base
{
    template<typename ...Targ>
    std::pair<bool,std::string> accept(Targ ...arg) { return process(arg...); }
    std::pair<bool,std::string> process() { return {}; };
    virtual std::pair<bool,std::string> process(std::string name,int score) = 0;
};

struct test_a1 : public test_base
{
    std::pair<bool,std::string> process(std::string name,int score) override
    {
        vlogd("test_a1");
        std::string ret;
        if(score > 90) 
        {
            ret = name+"同学大于90分,分数为"+std::to_string(score);
            return {true,ret};
        }
        return {false,""};
    }
};

struct test_a2 : public test_base
{
    std::pair<bool,std::string> process(std::string name,int score) override
    {
        vlogd("test_a2");
        std::string ret;
        if(score > 70) 
        {
            ret = name+"同学大于70分,分数为"+std::to_string(score);
            return {true,ret};
        }
        return {false,""};
    }
};

struct test_a3 : public test_base
{
    std::pair<bool,std::string> process(std::string name,int score) override
    {
        vlogd("test_a3");
        std::string ret;
        if(score > 60) 
        {
            ret = name+"同学大于60分,分数为"+std::to_string(score);
            return {true,ret};
        }
        return {false,""};
    }
};


// 通用处理模板-无返回值
// 用于定义参数-计算形状周长-传入结构体
struct perimeter_calc_data
{
    int ret;
    std::string type;
    std::vector<int> vec;
};

struct test_base_bool
{
    template<typename ...Targ>
    bool accept(Targ ...arg) { return process(arg...); }
    bool process() { return {}; };
    virtual bool process(perimeter_calc_data *) = 0;
};

struct test_b1 : public test_base_bool
{
    bool process(perimeter_calc_data *d) override
    {
        vlogd("test_b1");
        if(d->type == "长方形")
        {
            int t1 = d->vec[0];
            int t2 = d->vec[1];
            d->ret = 2*(t1+t2);
            return true;
        }
        return false;
    }
};

struct test_b2 : public test_base_bool
{
    bool process(perimeter_calc_data *d) override
    {
        vlogd("test_b2");
        if(d->type == "圆形")
        {
            int t1 = d->vec[0];
            d->ret = 2*3.14*t1;
            return true;
        }
        return false;
    }
};

struct test_b3 : public test_base_bool
{
    bool process(perimeter_calc_data *d) override
    {
        vlogd("test_b3");
        if(d->type == "三角形")
        {
            int t1 = d->vec[0];
            int t2 = d->vec[1];
            int t3 = d->vec[2];
            d->ret = t1+t2+t3;
            return true;
        }
        return false;
    }
};

struct test_b4 : public test_base_bool
{
    bool process(perimeter_calc_data *d) override
    {
        vlogd("test_b4");
        if(d->type == "多边形")
        {
            for(int i=0;i<d->vec.size();i++)
            {
                d->ret += d->vec[i];
            }
            return true;
        }
        return false;
    }
};


void test_1()
{
    // 带返回值
    {
        bhtools::Twork_chain<test_a1,test_a2,test_a3> work;
        std::pair<bool,std::string> p1 = work.start<std::string>("小明",79);
        vlogd($(p1));
    }
    {
        bhtools::Twork_chain<test_a1,test_a2,test_a3> work;
        std::pair<bool,std::string> p1 = work.start<std::string>("小王",99);
        vlogd($(p1));
    }
    {
        bhtools::Twork_chain<test_a1,test_a2,test_a3> work;
        std::pair<bool,std::string> p1 = work.start<std::string>("小熊",61);
        vlogd($(p1));
    }
    {
        bhtools::Twork_chain<test_a1,test_a2,test_a3> work;
        std::pair<bool,std::string> p1 = work.start<std::string>("小花",55);
        vlogd($(p1));
    }
}

void test_2()
{
    // 无返回值-通过参数返回
    bhtools::Twork_chain<test_b1,test_b2,test_b3> work;

    {
        auto d = std::make_shared<perimeter_calc_data>();
        d->type = "圆形";
        d->vec = {5};
        bool p1 = work.start(d.get());
        vlogd($(p1) $(d->type) $(d->ret));
    }
    {
        auto d = std::make_shared<perimeter_calc_data>();
        d->type = "三角形";
        d->vec = {5,10,15};
        bool p1 = work.start(d.get());
        vlogd($(p1) $(d->type) $(d->ret));
    }
    {
        auto d = std::make_shared<perimeter_calc_data>();
        d->type = "长方形";
        d->vec = {5,20};
        bool p1 = work.start(d.get());
        vlogd($(p1) $(d->type) $(d->ret));
    }
    {
        auto d = std::make_shared<perimeter_calc_data>();
        d->type = "锥形";
        d->vec = {5,2,6};
        bool p1 = work.start(d.get());
        vlogd($(p1) $(d->type) $(d->ret));
    }
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    return 0;
}