
#include <iostream>
#include <unordered_set>
#include "Tlog.h"

#include "Tpublish.h"
#include "Ffm.h"

using namespace bhtools;


struct TdataA
{
    std::string type = "电台";
    std::string ctx = "爱情公寓曾小贤栏目";
};

struct TdataB
{
    std::string type = "舞蹈";
    std::string ctx = "迪丽热巴跳舞";
    int time = 48;
};

struct TdataC
{
    std::string type = "游戏更新";
    std::string ctx = "战锤2更新了dlc是时候大出血了";
    int price = 588;
};

struct TdataD
{
    std::string type = "热点事件";
    std::string ctx = "你碰倒了我的自行车，赔我三万八";
    int value = 38000;
};


struct UserA : Tpubmsg<TdataA>
{
    UserA(const std::string &name)
    {
        this->Tpubmsg<TdataA>::_notify = [=](const TdataA &data){
            auto s = Fffm("{}司机订阅了 {} ，当前正在模播放 {} ")(name,data.type,data.ctx);
            vlogd($(s));
        };
    }
};

void test_1()
{
    // 单发布与单类型多用户订阅
    Tpublish<TdataA,Tpubmsg> puba;

    UserA a1("A");
    UserA a2("B");
    UserA a3("C");
    UserA a4("D");

    puba.insert(a1);
    puba.insert(a2);
    puba.insert(a3);
    puba.insert(a4);
    puba.notify(TdataA());

    puba.remove(a2);
    puba.remove(a3);
    puba.notify(TdataA());

    UserA a5("E");
    UserA a6("F");
    puba.insert(a5);
    puba.insert(a6);
    puba.notify(TdataA());
}



struct UserB : Tpubmsg<TdataB>, Tpubmsg<TdataC>
{
    UserB(int time)
    {
        this->Tpubmsg<TdataB>::_notify = [=](const TdataB &data){
            auto s = Fffm("{}小时的骨灰玩家订阅了 {} 区的 {}栏目 当前观看时间累计 {} 小时")(time,data.type,data.ctx,data.time);
            vlogd($(s));
        };
        this->Tpubmsg<TdataC>::_notify = [=](const TdataC &data){
            auto s = Fffm("{}小时的骨灰玩家关注了 {} 内容为 {} 价格 {}")(time,data.type,data.ctx,data.price);
            vlogd($(s));
        };
    }
};


struct UserC : Tpubmsg<TdataA>, Tpubmsg<TdataB>, Tpubmsg<TdataC>, Tpubmsg<TdataD>
{
    UserC(std::string name)
    {
        this->Tpubmsg<TdataA>::_notify = [=](const TdataA &data){
            auto s = Fffm("媒体人 {} 关注 {} 的 {} 节目")(name,data.type,data.ctx);
            vlogd($(s));
        };
        this->Tpubmsg<TdataB>::_notify = [=](const TdataB &data){
            auto s = Fffm("媒体人 {} 关注 {} 分区的 {}")(name,data.type,data.ctx,data.time);
            vlogd($(s));
        };
        this->Tpubmsg<TdataC>::_notify = [=](const TdataC &data){
            auto s = Fffm("媒体人 {} 关注 {} 消息内容为 {} 价格为 {}")(name,data.type,data.ctx,data.price);
            vlogd($(s));
        };
        this->Tpubmsg<TdataD>::_notify = [=](const TdataD &data){
            auto s = Fffm("媒体人 {} 关注 {} 新闻，事件为 {} 其中令人震惊的价格 {}")(name,data.type,data.ctx,data.value);
            vlogd($(s));
        };
    }
};


void test_2()
{
    // 订阅 : 司机(1) 玩家(23) 媒体(1234)
    // 发布 : 电台 舞蹈 游戏更新 热点事件
    Tpublish<TdataA,Tpubmsg> puba;
    Tpublish<TdataB,Tpubmsg> pubb;
    Tpublish<TdataC,Tpubmsg> pubc;
    Tpublish<TdataD,Tpubmsg> pubd;

    UserA a1("A");
    puba.insert(a1);

    UserB b1(12);
    pubb.insert(b1);
    pubc.insert(b1);

    UserC c1("张三");
    puba.insert(c1);
    pubb.insert(c1);
    pubc.insert(c1);
    pubd.insert(c1);


    puba.notify(TdataA());
    vlogw("");

    pubb.notify(TdataB());
    vlogw("");

    pubc.notify(TdataC());
    vlogw("");

    pubd.notify(TdataD());
    vlogw("");

}

void test_3()
{
    // 多发布与多订阅
    Tpublish<TdataA,Tpubmsg> puba;
    Tpublish<TdataB,Tpubmsg> pubb;
    Tpublish<TdataC,Tpubmsg> pubc;
    Tpublish<TdataD,Tpubmsg> pubd;

    UserA a1("A");
    UserA a2("B");
    UserA a3("C");
    UserA a4("D");
    puba.insert(a1);
    puba.insert(a2);
    puba.insert(a3);
    puba.insert(a4);

    UserB b1(12);
    UserB b2(123);
    UserB b3(999);
    UserB b4(55);
    pubb.insert(b1);
    pubb.insert(b2);
    pubb.insert(b3);
    pubb.insert(b4);

    pubc.insert(b1);
    pubc.insert(b2);
    pubc.insert(b3);
    pubc.insert(b4);


    UserC c1("张三");
    UserC c2("李四");
    UserC c3("王五");
    UserC c4("麻六");
    puba.insert(c1);
    puba.insert(c2);
    puba.insert(c3);
    puba.insert(c4);

    pubb.insert(c1);
    pubb.insert(c2);
    pubb.insert(c3);
    pubb.insert(c4);

    pubc.insert(c1);
    pubc.insert(c2);
    pubc.insert(c3);
    pubc.insert(c4);

    pubd.insert(c1);
    pubd.insert(c2);
    pubd.insert(c3);
    pubd.insert(c4);

    puba.notify(TdataA());
    vlogw("");

    pubb.notify(TdataB());
    vlogw("");

    pubc.notify(TdataC());
    vlogw("");

    pubd.notify(TdataD());
    vlogw("");

}


void test_4()
{
    // 改变消息
    Tpublish<TdataA,Tpubmsg> puba;

    UserA a1("A");
    puba.insert(a1);

    puba.notify(TdataA());
    vlogw("");
    
    TdataA a;
    a.type = "中央电台";
    a.ctx = "紧急插播最新地震消息";
    puba.notify(a);
    vlogw("");
}



struct BTpublishA : Tpublish<TdataA,Tpubmsg> {};
struct BTpublishB : Tpublish<TdataB,Tpubmsg> {};
struct BTpublishC : Tpublish<TdataC,Tpubmsg> {};
struct BTpublishD : Tpublish<TdataD,Tpubmsg> {};

struct BUserA : UserA
{
    BUserA(std::string name, BTpublishA &pa) : UserA(name)
    {
        pa.insert(*this);
    }
};

struct BUserB : UserB
{
    BUserB(int time, BTpublishB &pb,BTpublishC &pc) : UserB(time)
    {
        pb.insert(*this);
        pc.insert(*this);
    }
};

struct BUserC : UserC
{
    BUserC(std::string name, BTpublishA &pa, BTpublishB &pb, BTpublishC &pc, BTpublishD &pd) : UserC(name)
    {
        pa.insert(*this);
        pb.insert(*this);
        pc.insert(*this);
        pd.insert(*this);
    }
};

void test_5()
{
    // 生成时绑定-套壳类
    BTpublishA puba;
    BTpublishB pubb;
    BTpublishC pubc;
    BTpublishD pubd;

    BUserA a1("A",puba);
    BUserA a2("B",puba);
    BUserA a3("C",puba);
    BUserA a4("D",puba);

    BUserB b1(101,pubb,pubc);
    BUserB b2(123,pubb,pubc);
    BUserB b3(999,pubb,pubc);
    BUserB b4(551,pubb,pubc);

    BUserC c1("张三",puba,pubb,pubc,pubd);
    BUserC c2("李四",puba,pubb,pubc,pubd);
    BUserC c3("王五",puba,pubb,pubc,pubd);
    BUserC c4("麻六",puba,pubb,pubc,pubd);

    puba.notify(TdataA());
    vlogw("");

    pubb.notify(TdataB());
    vlogw("");

    pubc.notify(TdataC());
    vlogw("");

    pubd.notify(TdataD());
    vlogw("");

}


struct UserD : Tpubmsg<TdataA>, Tpubmsg<TdataD>
{
    UserD(std::string name, BTpublishA &pa, BTpublishD &pd)
    {
        this->Tpubmsg<TdataA>::_notify = [=](const TdataA &data){
            auto s = Fffm("{} 的最新动向 {} {}")(name,data.type,data.ctx);
            vlogd($(s));
        };

        this->Tpubmsg<TdataD>::_notify = [=](const TdataD &data){
            auto s = Fffm("{} 的最新动向 {} {} {}")(name,data.type,data.ctx,data.value);
            vlogd($(s));
        };

        pa.insert(*this);
        pd.insert(*this);
    }
};

void test_6()
{
    // 生成时绑定-新类
    BTpublishA puba;
    BTpublishD pubd;

    UserD a1("四川观察",puba,pubd);
    UserD a2("湖南卫视",puba,pubd);
    UserD a3("爱丽岛网",puba,pubd);

    puba.notify(TdataA());
    vlogw("");

    pubd.notify(TdataD());
    vlogw("");
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   
    test_4();   
    test_5();   
    test_6();   

    return 0;
}