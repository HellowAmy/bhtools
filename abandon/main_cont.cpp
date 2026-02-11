
#include <iostream>

#include "bhtools.h"


void test_1()
{
    // 多线程添加与移除-非线程安全会导致直接崩溃
    // 注意线程安全容器的迭代器并不安全
    bhtools::Tpool<> pool;
    
    bhtools::Tqueue<int> cc1;
    bhtools::Tstack<int> cc2;
    bhtools::Tvector<int> cc3;
    bhtools::Tmap<int,std::string> cc4;
    
    int sum = 100*10000;
    int sumc = 0;
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    int sum4 = 0;

    pool.push([&](){
        for(int i=0;i<sum;i++)
        {
            cc1.push(i);
            cc2.push(i);
            cc3.push_back(i);
            cc4.emplace(i,"ss"+std::to_string(i));
        }
    });

    pool.push([&](){
        for(int i=0;i<sum;i++)
        {
            while(cc1.size() > 0)
            {
                sum1++;
                cc1.pop();
            }
            while(cc2.size() > 0)
            {
                sum2++;
                cc2.pop();
            }
            while(cc3.size() > 0)
            {
                sum3++;
                cc3.pop_back();
            }
            while(cc4.size() > 0)
            {
                sum4++;
                cc4.erase(cc4.begin());
            }
        }
    });

    while(true)
    {
        bhtools::Ftimel::sleep(1000);
        if(cc1.size() == 0 && cc2.size() == 0 && cc3.size() == 0 && cc4.size() == 0)
        {
            break;
        }
    }
    vlogd($(cc1.size()));
    vlogd($(cc2.size()));
    vlogd($(cc3.size()));
    vlogd($(cc4.size()));

    vlogd($(sumc) $(sum1) $(sum2) $(sum3) $(sum4));
}

void test_2()
{
    // 测试数据插入
    bhtools::Tqueue<int> cc1;
    bhtools::Tstack<int> cc2;

    cc1.push(10);
    cc1.push(20);
    cc1.push(30);

    cc2.push(10);
    cc2.push(20);
    cc2.push(30);

    vlogd($(cc1.size()) $(cc2.size()));
    
    vlogd($(cc1.pop_front()) $(cc1.pop_front()) $(cc1.pop_front()));
    vlogd($(cc2.pop_top()) $(cc2.pop_top()) $(cc2.pop_top()));
    
    vlogd($(cc1.size()) $(cc2.size()));
}

void test_3()
{
    // 测试safa接口的线程安全,不推荐使用该接口
    {
        bhtools::Tpool<> pool;
    
        bhtools::Tqueue<int> cc1;
        bhtools::Tstack<int> cc2;
        bhtools::Tvector<int> cc3;
        bhtools::Tmap<int,std::string> cc4;
    
        int sum = 1000*10000;
     
        
        pool.push([&](){
            for(int i=0;i<sum/2;i++)
            {
                cc1.push(i);
                cc2.push(i);
                cc3.push_back(i);
                cc4.emplace(i,"ss"+std::to_string(i));
            }
        });
    
        pool.push([&](){
            for(int i=0;i<sum/2;i++)
            {
                cc1.push(i);
                cc2.push(i);
                cc3.push_back(i);
                cc4.emplace(sum/2 + i,"ss"+std::to_string(sum/2 + i));
            }
        });
    
        while(true)
        {
            bhtools::Ftimel::sleep(1000);
            if(cc1.size() == sum && cc2.size() == sum && cc3.size() == sum && cc4.size() == sum)
            {
                break;
            }
            vlogd($(cc1.size()) $(cc2.size()) $(cc3.size()) $(cc4.size()));
        }
        vlogd($(cc1.size()));
    }
    {
        bhtools::Tpool<> pool;
    
        bhtools::Tqueue<int> cc1;
        bhtools::Tstack<int> cc2;
        bhtools::Tvector<int> cc3;
        bhtools::Tmap<int,std::string> cc4;
    
        int sum = 1000*10000;
     
        
        pool.push([&](){
            for(int i=0;i<sum/2;i++)
            {
                cc1.safa([=](std::queue<int> &org){
                    org.push(i);
                });
                cc2.safa([=](std::stack<int> &org){
                    org.push(i);
                });
                cc3.safa([=](std::vector<int> &org){
                    org.push_back(i);
                });
                cc4.safa([=](std::map<int,std::string> &org){
                    org.emplace(i,"ss"+std::to_string(i));
                });
            }
        });
    
        pool.push([&](){
            for(int i=0;i<sum/2;i++)
            {
                cc1.safa([=](std::queue<int> &org){
                    org.push(i);
                });
                cc2.safa([=](std::stack<int> &org){
                    org.push(i);
                });
                cc3.safa([=](std::vector<int> &org){
                    org.push_back(i);
                });
                cc4.safa([=](std::map<int,std::string> &org){
                    org.emplace(sum/2 + i,"ss"+std::to_string(sum/2 + i));
                });
            }
        });
    
        while(true)
        {
            bhtools::Ftimel::sleep(1000);
            if(cc1.size() == sum && cc2.size() == sum && cc3.size() == sum && cc4.size() == sum)
            {
                break;
            }
            vlogd($(cc1.size()) $(cc2.size()) $(cc3.size()) $(cc4.size()));
        }
        vlogd($(cc1.size()));
    }
}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    test_3();   

    return 0;
}