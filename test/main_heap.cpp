
#include <iostream>
#include <queue>
#include <list>

#include "bhtools.h"


void test_1()
{
    // 测试大小堆常用接口
    bhtools::Theap_max<int> h1;

    for(int i=0;i<200;i+=2)
    {
        h1.insert_node(i);
    }

    vlogd($(h1.size()) $(h1.check_root()) $(h1.is_empty()) );

    vlogd($(h1.is_exist(186)) $(h1.is_exist(155)) $(h1.value_tail()));

    h1.insert_node(155);

    vlogd($(h1.is_exist(186)) $(h1.is_exist(155)) $(h1.value_tail()));

    vlogd($(h1.size()) $(h1.check_root()));

    for(int i=0;i<5;i++)
    {
        int val = h1.pop_root();
        vlogd($(val));
    }

    vlogd($(h1.size()) $(h1.check_root()));

    bool ok1 = h1.remove_node(166);
    bool ok2 = h1.remove_node(140);
    vlogd($(ok1) $(ok2) $(h1.size()));

    h1.clear();

    vlogd($(h1.size()) $(h1.is_empty()));
}

void test_2()
{
    // 测试大小堆顺序
    bhtools::Theap_max<int> h1;
    bhtools::Theap_min<int> h2;

    for(int i=0;i<=200;i+=2)
    {
        h1.insert_node(i);
        h2.insert_node(i);
    }

    vlogi("==");
    while(h1.is_empty() == false)
    {
        int val = h1.pop_root();
        vlogd($(val));
    }
    
    vlogi("==");
    while(h2.is_empty() == false)
    {
        int val = h2.pop_root();
        vlogd($(val));
    }
}

void test_3()
{
    // 测试多次清空问题
    bhtools::Theap_max<int> h1;

    for(int i=0;i<=200;i+=2)
    {
        h1.insert_node(i);
    }
    vlogd($(h1.size()));
    
    while(h1.is_empty() == false)
    {
        int val = h1.pop_root();
    }
    vlogd($(h1.size()));
    
    for(int i=0;i<=200;i+=2)
    {
        h1.insert_node(i);
    }
    vlogd($(h1.size()));
    
    h1.clear();
    vlogd($(h1.size()));

    for(int i=0;i<=200;i+=2)
    {
        h1.insert_node(i);
    }
    vlogd($(h1.size()));

}

void test_4()
{
    // 性能测试
    bhtools::Theap_max<int> h1;
    bhtools::Ftimel t1;
    int sum = 1000 * 10000;

    for(int i=0;i<sum;i++)
    {
        h1.insert_node(i);
    }
    t1.push_point("t1",true);

    while(h1.is_empty() == false)
    {
        int val = h1.pop_root();
    }
    t1.push_point("t2",true);

    for(int i=0;i<sum;i++)
    {
        h1.insert_node(i);
    }
    t1.push_point("t3",true);
    
    h1.clear();
    t1.push_point("t4",true);

    vlogd($C(t1.check_vec()));

    /*
        [Deb]<<<< [t1.check_vec(): 
        | size: 4
        | t1 [nan: 1784518487|mic: 1784518|mil: 1784|sec: 1] 
        | t2 [nan: 2712563434|mic: 2712563|mil: 2712|sec: 2] 
        | t3 [nan: 1423664075|mic: 1423664|mil: 1423|sec: 1] 
        | t4 [nan: 337638702|mic: 337638|mil: 337|sec: 0] 
        ]  >>>>[/home/red/open/github/bhtools/test/main_heap.cpp:134][2025-08-07.20:45:19.936]
    */
}

void test_5()
{
    // 遍历容器
    bhtools::Theap_max<int> h1;
    for(int i=0;i<10;i++)
    {
        h1.insert_node(i);
    }
    vlogd($C(h1));

    // 拷贝
    bhtools::Theap_max<int> h2;
    for(int i=0;i<10;i++)
    {
        h2.insert_node(i);
    }
    {
        bhtools::Theap_max<int> h21(h2);
        bhtools::Theap_max<int> h22 = h2;
        bhtools::Theap_max<int> h23;
        for(int i=0;i<5;i++)
        {
            h23.insert_node(i + 100);
        }

        h21.insert_node(11);
        h21.insert_node(22);
        h22.insert_node(33);
        h22.insert_node(44);

        vlogd($(h21.size()) $(h22.size()) $(h23.size()));
        vlogd($C(h21));
        vlogd($C(h22));
        vlogd($C(h23));

        h2 = h23;
    }
    vlogd($C(h2));
}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();  
    // test_3();  
    // test_4();  
    test_5();  

    return 0;
}