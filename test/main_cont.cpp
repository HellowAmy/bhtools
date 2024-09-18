

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>

#include "Tcont.h"
#include "Tpool.h"
#include "Tlog.h"
#include "Ftime.h"

using namespace bhtools;


void test_1()
{
    {
        vlogd($("== 1 =="));

        int count1 = 10000000;
        int count2 = 1000000;
        std::queue<int> que;
        Tpool<> pool;
        pool.push([&](){
            for(int i=0;i<count1;i++)
            {
                que.push(i);
            }
        });
        pool.push([&](){
            for(int i=0;i<count2;i++)
            {
                if(que.size() > 0)
                {
                    que.pop();
                }
            }
        }); 

        std::this_thread::sleep_for(std::chrono::seconds(1));
        vlogd($(que.size()));
    }


}

void test_2()
{
    {
        vlogi($("== 2 =="));

        int count1 = 100000000;
        int count2 = 10000000;
        Tqueue<int> que;
        Tpool<> pool;
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count1;i++)
            {
                que.push(i);
            }
            vlogd("push: "<<$(t.to_string()));
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count2;i++)
            {
                if(que.size() > 0)
                {
                    que.pop();
                }
                else 
                {
                    i--;
                }
            }
            vlogd("pop: "<<$(t.to_string()));
        }); 

        std::this_thread::sleep_for(std::chrono::seconds(10));
        vlogd($(que.size()));
    }

    {
        vlogi($("== mutex =="));

        int count1 = 100000000;
        int count2 = 10000000;
        Tqueue<int,std::mutex> que;
        Tpool<> pool;
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count1;i++)
            {
                que.push(i);
            }
            vlogd("push: "<<$(t.to_string()));
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count2;i++)
            {
                if(que.size() > 0)
                {
                    que.front();
                    que.pop();
                }
                else 
                {
                    i--;
                }
            }
            vlogd("pop: "<<$(t.to_string()));
        }); 

        std::this_thread::sleep_for(std::chrono::seconds(10));
        vlogd($(que.size()));
    }
}

void test_3()
{
    {
        vlogi($("== test_3 =="));

        int count1 = 100000000;
        int count2 = 10000000;
        Tstack<int> que;
        Tpool<> pool;
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count1;i++)
            {
                que.push(i);
            }
            vlogd("push: "<<$(t.to_string()));
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count2;i++)
            {
                if(que.size() > 0)
                {
                    que.top();
                    que.pop();
                }
                else 
                {
                    i--;
                }
            }
            vlogd("pop: "<<$(t.to_string()));
        }); 

        std::this_thread::sleep_for(std::chrono::seconds(10));
        vlogd($(que.size()));
    }
}

void test_4()
{
    {
        Tmap<int,std::string> mp;

        mp.insert(std::pair<int,std::string>(10,"s10"));
        mp.emplace(1,"s1");
        mp.emplace(2,"s2");
        mp.emplace(3,"s3");

        {
            auto it = mp.find(2);
            if(it != mp.end())
            {
                vlogd($(it->first) $(it->second));
                mp.erase(it);
            }
        }
        {
            auto it = mp.find(5);
            if(it != mp.end())
            {
                vlogd($(it->first) $(it->second));
                mp.erase(it);
            }
        }

        for(auto &a:mp)
        {
            vlogd($(a.first) $(a.second));
        }
        mp.clear();
        vlogd($(mp.size()));
        vlogi("==");
        vlogd($(mp[17]));
        mp[11] = "s11";
        mp[17] = "s17";

        vlogd($(mp[17]));
        vlogd($(mp.size()));
    }
    {
        vlogi($("== test_3 =="));

        int count1 = 10000000;
        int count2 = 1000000;
        Tpool<> pool;
        Tmap<int,std::string> mp;
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count1;i++)
            {
                mp.emplace(i,"s11");
            }
            vlogd("push: "<<$(t.to_string()));
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count2;i++)
            {
                auto it = mp.find(i);
                if(it != mp.end())
                {
                    mp.erase(it);
                }
                else 
                {
                    i--;
                }
            }
            vlogd("pop: "<<$(t.to_string()));
        }); 

        std::this_thread::sleep_for(std::chrono::seconds(15));
        vlogd($(mp.size()));
    }

    {
        vlogi($("== test_3 =="));

        int count1 = 10000000;
        int count2 = 1000000;
        Tmap<int,std::string,std::mutex> mp;
        Tpool<> pool;
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count1;i++)
            {
                mp.emplace(i,"s11");
            }
            vlogd("push: "<<$(t.to_string()));
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count2;i++)
            {
                auto it = mp.find(i);
                if(it != mp.end())
                {
                    mp.erase(it);
                }
                else 
                {
                    i--;
                }
            }
            vlogd("pop: "<<$(t.to_string()));
        }); 

        std::this_thread::sleep_for(std::chrono::seconds(15));
        vlogd($(mp.size()));
    }
}

void test_5()
{
    {
        Tvector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);
        for(auto &a:vec)
        {
            vlogd($(a));
        }
        vlogd($(vec.size()));

        vec.pop_back();
        vlogd($(vec.size()));

        vec.clear();
        vlogd($(vec.size()));

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);

        vlogd($(*vec.begin()));
        vlogd($(*(vec.end()-1)));

        vec.insert(vec.begin()+2,25);
        for(auto &a:vec)
        {
            vlogd($(a));
        }
        vec.erase(vec.begin());

        vlogi("==");
        for(auto &a:vec)
        {
            vlogd($(a));
        }

        vlogi("==");
        // vec[0]
        vlogd($(vec[0]));
        vec[0] = 12;
        vlogd($(vec[0]));

    }

    {
        vlogi($("== test_5 =="));

        int count1 = 10000000;
        int count2 = 1000000;
        // Tmap<int,std::string,std::mutex> mp;
        Tvector<int> vec;
        Tpool<> pool;
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count1;i++)
            {
                vec.push_back(i);
            }
            vlogd("push: "<<$(t.to_string()));
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pool.push([&](){
            Ftimel t;
            for(int i=0;i<count2;i++)
            {
                if(vec.size() > 0)
                {
                    vec.erase(vec.end() -1);
                    vec.pop_back();
                }
                else 
                {
                    i--;
                } 
            }
            vlogd("pop: "<<$(t.to_string()));
        }); 

        std::this_thread::sleep_for(std::chrono::seconds(5));
        vlogd($(vec.size()));
    }
    

}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    test_5();
    // test_6();

    return 0;
}