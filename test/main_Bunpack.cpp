#include <iostream>
#include <random>
#include <vector>
#include <mutex>

#include "Btype.h"
#include "Bunpack.h"
#include "Btest.h"
#include "Bpool.h"
#include "Btime.h"

#include "Tlog.h"

void test_1()
{
    vloga("单次组包与拆包测试");
    {
        vloga("测试分隔符模式");
        bh::Bunpack_del t;
        bh::dstr s1 = t.pack("123");
        bh::dstr s2 = t.pack("456");
    
        vlogd($(s1.size()) $(s2.size()));
        vlogd($(s1) $(s2));

        bh::dstr ss = s1 + s2;
        auto vec = t.unpack(ss, true);
        vlogd($C(vec) $(ss.size()));

        vloga("数据校验");
        BHTEST_EQUAL(vec.size(), 2);
        if(vec.size() == 2) {
            BHTEST_EQUAL(vec[0], "123");
            BHTEST_EQUAL(vec[1], "456");
        }
    }

    {
        vloga("测试长度头模式");
        bh::Bunpack_len t;
        bh::dstr s1 = t.pack("123");
        bh::dstr s2 = t.pack("456");
    
        vlogd($(s1.size()) $(s2.size()));
        vlogd($(s1) $(s2));

        bh::dstr ss = s1 + s2;
        auto vec = t.unpack(ss, true);
        vlogd($C(vec) $(ss.size()));

        vloga("数据校验");
        BHTEST_EQUAL(vec.size(), 2);
        if(vec.size() == 2) {
            BHTEST_EQUAL(vec[0], "123");
            BHTEST_EQUAL(vec[1], "456");
        }
    }
}

void test_2()
{
    vloga("连续组包与拆包测试");
    bh::int32 num = 50;
    {
        bh::Bunpack_del t1;
        bh::Bunpack_len t2;
        bh::dstr ss;
        bh::dstr all1;
        bh::dstr all2;

        for(bh::int32 i=0; i<num; i++)
        {
            bh::dstr data = std::to_string(i);
            all1 += t1.pack(data);
            all2 += t2.pack(data);
        }

        auto vec1 = t1.unpack(all1, true);
        auto vec2 = t2.unpack(all2, true);
        vlogd($C(vec1) $C(vec2));

        vloga("连续拆包总量校验");
        BHTEST_EQUAL(vec1.size(), (bh::uint64)num);
        BHTEST_EQUAL(vec2.size(), (bh::uint64)num);

        vloga("内容一致性校验");
        bool content_ok = true;
        for(bh::int32 i=0; i<num; i++) {
            if(vec1[i] != std::to_string(i) || vec2[i] != std::to_string(i)) {
                content_ok = false;
                break;
            }
        }
        BHTEST_TRUE(content_ok);
    }

    vloga("更换切割符号测试");
    {
        struct Tunfd_delimit2
        {
            const bh::dstr _delimit = "#@@#";
        };
        using Bunpack_del2 = bh::Bunpack<bh::Bunf_delimit<Tunfd_delimit2>>;

        Bunpack_del2 t1;
        bh::dstr all1;

        for(bh::int32 i=0; i<num; i++)
        {
            all1 += t1.pack(std::to_string(i));
        }

        auto vec1 = t1.unpack(all1, true);
        vlogd($C(vec1));
        BHTEST_EQUAL(vec1.size(), (bh::uint64)num);
        if(!vec1.empty()) BHTEST_EQUAL(vec1[0], "0");
    }

    vloga("更换长度头类型测试");
    {
        using Bunpack_len2 = bh::Bunpack<bh::Bunf_length<bh::uint16>>;

        Bunpack_len2 t1;
        bh::dstr all1;

        for(bh::int32 i=0; i<num; i++)
        {
            all1 += t1.pack(std::to_string(i));
        }

        auto vec1 = t1.unpack(all1, true);
        vlogd($C(vec1));
        BHTEST_EQUAL(vec1.size(), (bh::uint64)num);
        if(!vec1.empty()) BHTEST_EQUAL(vec1[num-1], std::to_string(num-1));
    }
}


void test_3()
{
    vloga("多线程拆包压力测试");
    bh::Bpool<> loop;
    bool run1 = true;
    bool run2 = true;

    std::vector<bh::dstr> vec1;
    std::vector<bh::dstr> vec2;

    bh::Bunpack_del unp;
    std::mutex mut;
    bh::dstr pipe;

    vloga("启动发送线程：模拟高频随机数据推入");
    loop.push([&](){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<bh::uint64> dist(1000*10000, 10*10000);
        while (run1)
        {
            std::lock_guard<std::mutex> lock(mut);
            auto s = std::to_string(dist(gen));
            vec1.push_back(s);
            pipe += unp.pack(s);
            bh::Btimel::sleep(200);
        }
    });

    vloga("启动接收线程：模拟随机长度读取拆包");
    loop.push([&](){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<bh::uint64> dist(10, 100);
        
        while (run2)
        {
            bh::dstr s;
            {
                std::lock_guard<std::mutex> lock(mut);
                auto len = dist(gen);
                if(pipe.size() > len)
                {
                    s = bh::dstr(pipe.begin(), pipe.begin() + len);
                    pipe = bh::dstr(pipe.begin() + len, pipe.end());
                }
            }

            if(!s.empty()){
                auto vec = unp.unpack(s, true);
                if(vec.size() > 0)
                {
                    std::lock_guard<std::mutex> lock(mut);
                    for(auto &a : vec)
                    {
                        vec2.push_back(a);
                    }
                    vlogd($C(vec));
                }
            }
            bh::Btimel::sleep(100);
        }
        vloga("处理管道中剩余数据");
        vlogd($(pipe.size()));
        auto vec = unp.unpack(pipe, true);
        if(vec.size() > 0)
        {
            std::lock_guard<std::mutex> lock(mut);
            for(auto &a : vec)
            {
                vec2.push_back(a);
            }
            vlogd($C(vec));
        }
    });

    vloga("主线程计时等待中...");
    bh::int32 i = 0;
    while(true)
    {
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
        bh::Btimel::sleep(1000);
    }
    bh::Btimel::sleep(1000);
    
    vloga("最终数据核对");
    vlogd("发送包总数:" $(vec1.size()) " 接收包总数:" $(vec2.size()));

    vloga("多线程一致性结果判断");
    bool ok1 = true;
    if(vec1.size() == vec2.size())
    {
        for(bh::uint64 i = 0; i < vec1.size(); i++)
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
    BHTEST_TRUE(ok1);
}

int main(bh::int32 argc, char *argv[])
{
    test_1();   
    test_2();   
    test_3();   

    return 0;
}
