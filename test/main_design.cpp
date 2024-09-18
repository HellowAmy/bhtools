

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
#include "Ffm.h"
// #include "Ftime.h"

using namespace bhtools;


namespace Test1 {

// 模式1-使用父类继承-可减少每个处理类需要编写的代码量
class TestBase
{
public:
    template<typename ...Targ>
    std::pair<bool,std::string> accept(Targ ...arg) { return process(arg...); }
    std::pair<bool,std::string> process() { return {}; };
    virtual std::pair<bool,std::string> process(std::string name,int score) = 0;
};

class TestA : public TestBase
{
public:
    std::pair<bool,std::string> process(std::string name,int score) override
    {
        if(score >= 90)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于A级")(name,score);
            return std::make_pair(true,ret);
        }
        return std::make_pair(false,"");
    }
};

class TestB : public TestBase
{
public:
    std::pair<bool,std::string> process(std::string name,int score) override
    {
        if(score >= 75)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于B级")(name,score);
            return std::make_pair(true,ret);
        }
        return std::make_pair(false,"");
    }
};

class TestC : public TestBase
{
public:
    std::pair<bool,std::string> process(std::string name,int score)
    {
        if(score >= 60)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于C级")(name,score);
            return std::make_pair(true,ret);
        }
        return std::make_pair(false,"");
    }
};

class TestD : public TestBase
{
public:
    std::pair<bool,std::string> process(std::string name,int score)
    {
        if(score < 60)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于D级")(name,score);
            return std::make_pair(true,ret);
        }
        return std::make_pair(false,"");
    }
};


} // Test1



void test_1()
{
    using namespace Test1;
    {
        vlogi("== 1 ==");
        Twork_chain<TestD,TestC,TestB,TestA> work;
        {
            auto ret = work.start<std::string>("黄一衣",98);
            vlogd($(ret.first) $(ret.second));
        }
        {
            auto ret = work.start<std::string>("周某星",76);
            // vlogd($(ok));
            vlogd($(ret.first) $(ret.second));
        }
        {
            auto ret = work.start<std::string>("雷雷子",62);
            vlogd($(ret.first) $(ret.second));
        }
        {
            auto ret = work.start<std::string>("渣渣辉",53);
            vlogd($(ret.first) $(ret.second));
        }
    }
}


namespace Test2 {


class TestBase
{
public:
    template<typename ...Targ>
    bool accept(Targ ...arg) { return process(arg...); }
    bool process() { return false; };
    virtual bool process(std::string name,int score) = 0;
};

class TestA : public TestBase
{
public:
    bool process(std::string name,int score) override
    {
        if(score >= 90)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于A级")(name,score);
            vlogd($(ret));
            return true;
        }
        return false;
    }
};

class TestB : public TestBase
{
public:
    bool process(std::string name,int score) override
    {
        if(score >= 75)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于B级")(name,score);
            vlogd($(ret));
            return true;
        }
        return false;
    }
};

class TestC : public TestBase
{
public:
    bool process(std::string name,int score)
    {
        if(score >= 60)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于C级")(name,score);
            vlogd($(ret));
            return true;
        }
        return false;
    }
};

class TestD : public TestBase
{
public:
    bool process(std::string name,int score)
    {
        if(score > 0 && score < 60)
        {
            std::string ret = Fffm("{}同学的得分是{}--属于D级")(name,score);
            vlogd($(ret));
            return true;
        }
        return false;
    }
};

} // Test2



void test_2()
{
    using namespace Test2;
    {
        vlogi("== 1 ==");
        Twork_chain<TestD,TestC,TestB,TestA> work;
        {
            bool ok = work.start("黄一衣",98);
            vlogd($(ok));
        }
        {
            bool ok = work.start("周某星",76);
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
        {
            bool ok = work.start("猪猪侠",-13);
            vlogd($(ok));
        }
    }
    {
        Twork_chain<TestA,TestB,TestC,TestD> work;
        {
            bool ok = work.start("黄一衣",98);
            vlogd($(ok));
        }
        {
            bool ok = work.start("周某星",76);
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
        {
            bool ok = work.start("猪猪侠",-13);
            vlogd($(ok));
        }
    }
}
namespace Test3 {

struct TestStringData
{
    int height;    
    int width;
    std::string info;     
};

// 模式2-处理类单独处理模板职责链需要的鸭子函数
class TestStringA
{
public:
    template<typename ...Targ>
    std::pair<bool,int> accept(Targ ...arg) { return process(arg...); }

    template<typename ...Targ>
    std::pair<bool,int> process(TestStringData data)
    {
        if(data.info == "长方形")
        {
            int ret = data.height * data.width;
            return std::make_pair(true,ret);
        }
        return std::make_pair(false,0);
    }
    std::pair<bool,int> process() { return {}; }
};

class TestStringB
{
public:
    template<typename ...Targ>
    std::pair<bool,int> accept(Targ ...arg) { return process(arg...); }

    template<typename ...Targ>
    std::pair<bool,int> process(TestStringData data)
    {
        if(data.info == "三角形")
        {
            int ret = data.height * data.width / 2;
            return std::make_pair(true,ret);
        }
        return std::make_pair(false,0);
    }
    std::pair<bool,int> process() { return {}; }
};


} // Test3


void test_3()
{
    vlogi("== test_3 ==");
    using namespace Test3;
    Twork_chain<TestStringB,TestStringA> work;
    {
        TestStringData a;
        a.info = "长方形";
        a.height = 10;
        a.width = 5;
        auto ret = work.start<int>(a);
        vlogd($(ret.first) $(ret.second));
    }
    {
        TestStringData a;
        a.info = "三角形";
        a.height = 10;
        a.width = 5;
        auto ret = work.start<int>(a);
        vlogd($(ret.first) $(ret.second));
    }
    {
        TestStringData a;
        a.info = "圆形";
        a.height = 10;
        a.width = 5;
        auto ret = work.start<int>(a);
        vlogd($(ret.first) $(ret.second));
    }
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   
    // test_4();   
    // test_5();
    // test_6();

    return 0;
}