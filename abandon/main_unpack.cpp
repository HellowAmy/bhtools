
#include <iostream>
#include <random>

#include "bhtools.h"

void test_1()
{
    // 单次组包与拆包
    {
        bhtools::Tunpack_del t;
        std::string s1 = t.pack("123");
        std::string s2 = t.pack("456");
    
        vlogd($(s1.size()) $(s2.size()));
        vlogd($(s1) $(s2));

        std::string ss = s1 + s2;
        auto vec = t.unpack(ss);
        vlogd($C(vec) $(ss.size()));
    }

    {
        bhtools::Tunpack_len t;
        std::string s1 = t.pack("123");
        std::string s2 = t.pack("456");
    
        vlogd($(s1.size()) $(s2.size()));
        vlogd($(s1) $(s2));

        std::string ss = s1 + s2;
        auto vec = t.unpack(ss);
        vlogd($C(vec) $(ss.size()));
    }
}

void test_2()
{
    // 连续组包与拆包
    int num = 50;
    {
        bhtools::Tunpack_del t1;
        bhtools::Tunpack_len t2;
        std::string ss;
        std::string all1;
        std::string all2;

        for(int i=0;i<num;i++)
        {
            ss += std::to_string(i);
            all1 += t1.pack(ss);
            all2 += t2.pack(ss);
        }

        auto vec1 = t1.unpack(all1);
        auto vec2 = t2.unpack(all2);
        vlogd($C(vec1) $C(vec2));
    }

    // 更换切割符号
    {
        struct Tunfd_delimit2
        {
            const std::string _delimit = "#@@#";
        };
        using Tunpack_del2 = bhtools::Tunpack<bhtools::Tunf_delimit<Tunfd_delimit2>>;

        Tunpack_del2 t1;
        std::string ss;
        std::string all1;

        std::string s1 = t1.pack("12345");

        for(int i=0;i<num;i++)
        {
            ss += std::to_string(i);
            all1 += t1.pack(ss);
        }

        auto vec1 = t1.unpack(all1);
        vlogd($C(vec1) $(s1.size()) $(s1));
    }

    {
 
        using Tunpack_len2 = bhtools::Tunpack<bhtools::Tunf_length<unsigned short>>;

        Tunpack_len2 t1;
        std::string ss;
        std::string all1;

        std::string s1 = t1.pack("12345");

        for(int i=0;i<num;i++)
        {
            ss += std::to_string(i);
            all1 += t1.pack(ss);
        }

        auto vec1 = t1.unpack(all1);
        vlogd($C(vec1) $(s1.size()) $(s1));
    }
}


void test_3()
{
    // 多线程拆包
    bhtools::Tpool<> loop;
    bool run1 = true;
    bool run2 = true;

    std::vector<std::string> vec1;
    std::vector<std::string> vec2;

    bhtools::Tunpack_del unp;
    std::mutex mut;
    std::string pipe;

    // 发送线程
    loop.push([&](){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dist(1000*10000, 10*10000);
        while (run1)
        {
            mut.lock();
            auto s = std::to_string(dist(gen));
            vec1.push_back(s);
            pipe += unp.pack(s);
            mut.unlock();
            bhtools::Ftimel::sleep(200);
        }
    });

    // 接送线程
    loop.push([&](){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dist(10, 100);
        
        while (run2)
        {
            mut.lock();
            auto len = dist(gen);
            std::string s;
            if(pipe.size() > len)
            {
                s = std::string(pipe.begin(),pipe.begin()+len);
                pipe = std::string(pipe.begin()+len,pipe.end());
            }
            mut.unlock();

            auto vec = unp.unpack(s);
            if(vec.size() > 0)
            {
                for(auto &a:vec)
                {
                    vec2.push_back(a);
                }
                vlogd($C(vec));
            }
            bhtools::Ftimel::sleep(100);
        }
        vlogd($(pipe) $(pipe.size()));
        auto vec = unp.unpack(pipe);
        if(vec.size() > 0)
        {
            for(auto &a:vec)
            {
                vec2.push_back(a);
            }
            vlogd($C(vec));
        }
    });

    // 主线程等待
    while(true)
    {
        static int i=0;
        i++;
        if(i > 5)
        {
            run1 = false;
        }
        if(i > 10)
        {
            run2  = false;
            break;
        }
        bhtools::Ftimel::sleep(1000);
    }
    bhtools::Ftimel::sleep(1000);
    vlogd($C(vec1) $C(vec2));

    // 结果判断
    bool ok1 = true;
    if(vec1.size() == vec2.size())
    {
        for(int i=0;i<vec1.size();i++)
        {
            if(vec1[i] != vec2[i]) 
            {
                ok1 = false;
                break;
            }
        }
    }
    else 
    {
        ok1 = false;
    }
    vlogd($(ok1));
}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    // test_3();   

    return 0;
}