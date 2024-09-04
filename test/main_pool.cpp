

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>

#include "Tpool.h"
#include "Tlog.h"
#include "Ftime.h"

using namespace bhtools;


void test_1()
{
    int count = 100000;
    auto fn_task1 = [](int num){
        int sum = 0;
        for(int i=0;i<100000;i++)
        {
            sum += i;
        }
    };

    auto fn_task2 = [](int num){
        int sum = 100;
        sum += num;
        return sum;
    };

    {
        Ftimel t;
        std::vector<std::future<void>> vec1;
        std::vector<std::future<int>> vec2;
        for(int i=0;i<count;i++)
        {
            vec1.push_back(_sp_pool_->push(fn_task1,i));
            vec2.push_back(_sp_pool_->push(fn_task2,i));
        }

        for(int i=0;i<vec2.size();i++)
        {
            auto val = vec2[i].get();
        }
        vlogd($(t.to_string()));
    }
    {
        Ftimel t;
        std::vector<std::future<void>> vec1;
        std::vector<std::future<int>> vec2;
        Tpool<2> ths;
        for(int i=0;i<count;i++)
        {
            vec1.push_back(ths.push(fn_task1,i));
            vec2.push_back(ths.push(fn_task2,i));
        }

        for(int i=0;i<vec2.size();i++)
        {
            auto val = vec2[i].get();
        }
        vlogd($(t.to_string()));
    }
    {
        Ftimel t;
        std::vector<std::future<void>> vec1;
        std::vector<std::future<int>> vec2;
        Tpool<4> ths;
        for(int i=0;i<count;i++)
        {
            vec1.push_back(ths.push(fn_task1,i));
            vec2.push_back(ths.push(fn_task2,i));
        }

        for(int i=0;i<vec2.size();i++)
        {
            auto val = vec2[i].get();
        }
        vlogd($(t.to_string()));
    }
    {
        Ftimel t;
        std::vector<std::future<void>> vec1;
        std::vector<std::future<int>> vec2;
        Tpool<8> ths;
        for(int i=0;i<count;i++)
        {
            vec1.push_back(ths.push(fn_task1,i));
            vec2.push_back(ths.push(fn_task2,i));
        }

        for(int i=0;i<vec2.size();i++)
        {
            auto val = vec2[i].get();
        }
        vlogd($(t.to_string()));
    }
    {
        Ftimel t;
        std::vector<std::future<void>> vec1;
        std::vector<std::future<int>> vec2;
        Tpool<16> ths;
        for(int i=0;i<count;i++)
        {
            vec1.push_back(ths.push(fn_task1,i));
            vec2.push_back(ths.push(fn_task2,i));
        }

        for(int i=0;i<vec2.size();i++)
        {
            auto val = vec2[i].get();
        }
        vlogd($(t.to_string()));
    }
}

int main(int argc, char *argv[])
{
    test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();

    return 0;
}