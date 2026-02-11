
#include <iostream>
#include <future>
#include <vector>

#include "bhtools.h"

void test_1()
{
    // 多线程执行任务,当任务超出线程数时
    bhtools::Tpool<3> loop1;
    std::mutex _mux;
    bhtools::Ftimel t1;

    std::future<int> ret1 = loop1.push([&](){
        _mux.lock();
        vlogd("1");
        vlogd($S(std::this_thread::get_id()));
        t1.push_point("t1",true);
        _mux.unlock();
        int sum = 0;
        for(int i=0;i<100;i++)
        {
            sum += i;
        }
        bhtools::Ftimel::sleep(2000);
        return sum;
    });

    loop1.push([&](){
        _mux.lock();
        vlogd("2");
        vlogd($S(std::this_thread::get_id()));
        t1.push_point("t2",true);
        _mux.unlock();
        bhtools::Ftimel::sleep(2000);
    });

    loop1.push([&](){
        _mux.lock();
        vlogd("3");
        vlogd($S(std::this_thread::get_id()));
        t1.push_point("t3",true);
        _mux.unlock();
        bhtools::Ftimel::sleep(2000);
    });

    loop1.push([&](){
        _mux.lock();
        vlogd("4");
        vlogd($S(std::this_thread::get_id()));
        t1.push_point("t4",true);
        _mux.unlock();
        bhtools::Ftimel::sleep(2000);
    });

    bhtools::Ftimel::sleep(6 * 1000);
    
    vlogd($(ret1.get()));
    vlogd($C(t1.check_vec()));
}

void test_2()
{
    // 获取多线程下返回值
    bhtools::Tpool<> loop1;
    bhtools::Tpool<> loop2;
    std::vector<std::future<std::string>> vec;

    auto fn1 = [](std::string tip) -> std::string {
        std::string str = tip + ": ";
        for(int i=0;i<10;i++)
        {
            str += std::to_string(i);
        }
        bhtools::Ftimel::sleep(500);
        return str;
    };

    for(int i=0;i<20;i++)
    {
        std::future<std::string> rp = loop1.push(fn1,"tips" + std::to_string(i));
        vec.push_back(std::move(rp));
    }
    vlogd("wait1");

    loop2.push([&](){
        for(auto &a:vec)
        {
            std::string s = a.get();
            vlogd($(s));
        }
    });

    vlogd("wait2");
    bhtools::Ftimel::sleep(6 * 1000);
}

int main(int argc, char *argv[])
{
    // test_1();   
    test_2();   

    return 0;
}