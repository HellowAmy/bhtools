

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL

#include "Theap.h"

#include <iostream>
#include <queue>

#include "Tlog.h"
#include "Ftime.h"

#include "heap.h"

using namespace bhtools;


void show_node(Theap_node<int> *root)
{
    if(root == nullptr)
    {
        return;
    }
    std::queue<Theap_node<int> *> que;
    que.push(root);
    int count = 0;
    int clevel = 0;
    while (que.empty() == false)
    {
        // node
        std::queue<Theap_node<int> *> que_level;
        int size = que.size();
        for(int i=0;i<size;i++)
        {
            Theap_node<int> *node = que.front();
            que.pop();
            vlogw($(count) $(clevel) $(node->_value));

            Theap_node<int> *nl = node->_left;
            if(nl)
            {
                que.push(nl);
            }

            Theap_node<int> *nr = node->_right;
            if(nr)
            {
                que.push(nr);
            }
            count++;
        }
        clevel++;
    }
}


void test_1()
{
    auto fn_push1 = [](Theap<int,Theap_comp_max<int>> &heap,int count){
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
    };
    auto fn_push2 = [](Theap<int,Theap_comp_min<int>> &heap,int count){
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
    };


    {
        Theap<int,Theap_comp_max<int>> heap;
        fn_push1(heap,40);
        fn_push1(heap,40);

        while(heap.is_empty() == false)
        {
            auto val = heap.pop_root();
            vlogd($(val));
        }
        
        // show_node(heap._root);
        // vlogd($(heap.size_node()));
        // vlogd($(heap.is_empty()));
        // vlogd($(heap.check_root()));
    }

    {
        Theap<int,Theap_comp_min<int>> heap;
        fn_push2(heap,30);
        fn_push2(heap,30);

        while(heap.is_empty() == false)
        {
            auto val = heap.pop_root();
            vlogd($(val));
        }
        
        // show_node(heap._root);
        // vlogd($(heap.size_node()));
        // vlogd($(heap.is_empty()));
        // vlogd($(heap.check_root()));
    }
}

void test_2()
{
    int count = 10000000;

    {
        Ftimel t;
        Theap<int,Theap_comp_min<int>> heap;
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
        vlogd($(t.to_string()));
    }

    {
        Theap<int,Theap_comp_min<int>> heap;
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }

        Ftimel t;
        while(heap.is_empty() == false)
        {
            heap.pop_root();
        }
        vlogd($(t.to_string()));
    }
}

struct heap_val_int
{
    heap_node node;
    int val;
};

#ifndef container_of
#define container_of(ptr, type, member) \
((type*)((char*)(ptr) - offsetof(type, member)))
#endif

void test_3()
{

    int count = 10000000;
    // {
    //     heap hp;    
    //     heap_init(&hp,[](const struct heap_node* lhs, const struct heap_node* rhs)->int {
    //         heap_val_int *lv = container_of(lhs,heap_val_int,val);
    //         heap_val_int *rv = container_of(rhs,heap_val_int,val);
    //         return lv->val > rv->val;
    //     });

    //     Ftimel t;
    //     for(int i=1;i<=count;i++)
    //     {
    //         heap_val_int *ct = new heap_val_int;
    //         ct->val = i;
    //         heap_insert(&hp,&ct->node);
    //     }
    //     vlogd($(t.to_string()));
    // }
    {
        heap hp;    
        heap_init(&hp,[](const struct heap_node* lhs, const struct heap_node* rhs)->int {
            heap_val_int *lv = container_of(lhs,heap_val_int,val);
            heap_val_int *rv = container_of(rhs,heap_val_int,val);
            return lv->val > rv->val;
        });

        for(int i=1;i<=count;i++)
        {
            heap_val_int *ct = new heap_val_int;
            ct->val = i;
            heap_insert(&hp,&ct->node);
        }
        vlogd($(hp.nelts));

        Ftimel t;
        {
            while(hp.nelts > 0)
            {
                heap_dequeue(&hp);
            }
        }
        vlogd($(t.to_string()));

        vlogd($(hp.nelts));
    }

}

int main(int argc, char *argv[])
{
    // test_1();   
    test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();


    return 0;
}