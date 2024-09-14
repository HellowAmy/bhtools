

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "Tdesign.h"
#include "Tlog.h"
// #include "Ftime.h"

using namespace bhtools;


// 模式1-使用父类继承-可减少每个处理类需要编写的代码量
class TestBase
{
public:
    template<typename ...Targ>
    bool next(Targ ...arg) { return process(arg...); }
    bool process() { return true; };
    virtual bool process(std::string name,int score) = 0;
};

class TestA : public TestBase
{
public:
    bool process(std::string name,int score) override
    {
        if(score >= 90)
        {
            std::cout<<name<<"同学的得分是"<<score<<"--属于A级"<<std::endl;
            return false;
        }
        return true;
    }
};

class TestB : public TestBase
{
public:
    bool process(std::string name,int score) override
    {
        if(score >= 75)
        {
            std::cout<<name<<"同学的得分是"<<score<<"--属于B级"<<std::endl;
            return false;
        }
        return true;
    }
};

class TestC : public TestBase
{
public:
    bool process(std::string name,int score)
    {
        if(score >= 60)
        {
            std::cout<<name<<"同学的得分是"<<score<<"--属于C级"<<std::endl;
            return false;
        }
        return true;
    }
};

class TestD : public TestBase
{
public:
    bool process(std::string name,int score)
    {
        if(score < 60)
        {
            std::cout<<name<<"同学的得分是"<<score<<"--属于D级"<<std::endl;
            return false;
        }
        return true;
    }
};


void test_1()
{
    {
        vlogi("== 1 ==");
        Twork_chain<TestD,TestC,TestB,TestA> work;
        {
            bool ok = work.start("黄衣",98);
            vlogd($(ok));
        }
        {
            bool ok = work.start("周某",76);
            vlogd($(ok));
        }
        {
            bool ok = work.start("雷雷子",62);
            vlogd($(ok));
        }
        {
            bool ok = work.start("渣渣辉",53);
            vlogd($(ok));
        }
    }
    {
        vlogi("== 2 ==");
        Twork_chain<TestA,TestB,TestC,TestD> work;
        {
            bool ok = work.start("黄衣",98);
            vlogd($(ok));
        }
        {
            bool ok = work.start("周某",76);
            vlogd($(ok));
        }
        {
            bool ok = work.start("雷雷子",62);
            vlogd($(ok));
        }
        {
            bool ok = work.start("渣渣辉",53);
            vlogd($(ok));
        }
    }
}

// 模式2-处理类单独处理模板职责链需要的鸭子函数
struct TestStringData
{
    int height;    
    int width;
    std::string info;     
};

class TestStringA
{
public:
    template<typename ...Targ>
    bool next(Targ ...arg) { return process(arg...); }

    template<typename ...Targ>
    bool process(TestStringData data)
    {
        if(data.info == "长方形")
        {
            int ret = data.height * data.width;
            std::cout<<"图形是"<<data.info<<"图形面积是: "<<ret<<std::endl;
            return false;
        }
        return true;
    }
    bool process() { return true; }
};

class TestStringB
{
public:
    template<typename ...Targ>
    bool next(Targ ...arg) { return process(arg...); }

    template<typename ...Targ>
    bool process(TestStringData data)
    {
        if(data.info == "三角形")
        {
            int ret = data.height * data.width / 2;
            std::cout<<"图形是"<<data.info<<"图形面积是: "<<ret<<std::endl;
            return false;
        }
        return true;
    }
    bool process() { return true; }
};

void test_2()
{
    vlogi("== test_2 ==");
    Twork_chain<TestStringB,TestStringA> work;
    {
        TestStringData a;
        a.info = "长方形";
        a.height = 10;
        a.width = 5;
        bool ok = work.start(a);
        vlogd($(ok));
    }
    {
        TestStringData a;
        a.info = "三角形";
        a.height = 10;
        a.width = 5;
        bool ok = work.start(a);
        vlogd($(ok));
    }
    {
        TestStringData a;
        a.info = "圆形";
        a.height = 10;
        a.width = 5;
        bool ok = work.start(a);
        vlogd($(ok));
    }
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();

    return 0;
}