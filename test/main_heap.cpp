

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL

#include "Theap.h"

#include <iostream>
#include <queue>

#include "Tlog.h"
#include "Ftime.h"

#include "heap.h"

using namespace bhtools;


int show_node(Theap_node<int> *root,bool show = true)
{
    if(root == nullptr)
    {
        return 0;
    }
    vlogd("=====");
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
            if(show)
            {
                vlogw($(count) $(clevel) $(node->_value));
            } 

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

    return count;
}




void test_1()
{
    auto fn_push1 = [](Theap<int,Theap_comp_max> &heap,int count){
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
    };
    auto fn_push2 = [](Theap<int,Theap_comp_min> &heap,int count){
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
    };


    {
        Theap<int,Theap_comp_max> heap;
        fn_push1(heap,40);

        show_node(heap._root);
        vlogd($(heap.size_node()));
        vlogd($(heap.is_empty()));
        vlogd($(heap.check_root()));
        vlogd($(heap.value_tail()));
        vlogd($(heap._tail->_parent->_value));
    }
    {
        Theap<int,Theap_comp_max> heap;

        show_node(heap._root);
        vlogd($(heap.size_node()));
        vlogd($(heap.is_empty()));
        vlogd($(heap.check_root()));
        vlogd($(heap.value_tail()));
        vlogd($(heap._tail->_parent->_value));
    }
    {
        Theap<int,Theap_comp_max> heap;
        fn_push1(heap,1);

        show_node(heap._root);
        vlogd($(heap.size_node()));
        vlogd($(heap.is_empty()));
        vlogd($(heap.check_root()));
        vlogd($(heap.value_tail()));
        vlogd($(heap._tail->_parent->_value));
    }
    {
        Theap<int,Theap_comp_max> heap;
        fn_push1(heap,2);

        show_node(heap._root);
        vlogd($(heap.size_node()));
        vlogd($(heap.is_empty()));
        vlogd($(heap.check_root()));
        vlogd($(heap.value_tail()));
        vlogd($(heap._tail->_parent->_value));
    }
    {
        Theap<int,Theap_comp_max> heap;
        fn_push1(heap,3);

        show_node(heap._root);
        vlogd($(heap.size_node()));
        vlogd($(heap.is_empty()));
        vlogd($(heap.check_root()));
        vlogd($(heap.value_tail()));
        vlogd($(heap._tail->_parent->_value));
    }
    {
        Theap<int,Theap_comp_max> heap;
        fn_push1(heap,4);

        show_node(heap._root);
        vlogd($(heap.size_node()));
        vlogd($(heap.is_empty()));
        vlogd($(heap.check_root()));
        vlogd($(heap.value_tail()));
        vlogd($(heap._tail->_parent->_value));
    }
}

void test_2()
{
    auto fn_push1 = [](Theap<int,Theap_comp_max> &heap,int count){
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
    };
    auto fn_push2 = [](Theap<int,Theap_comp_min> &heap,int count){
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
    };


    {
        Theap<int,Theap_comp_max> heap;
        fn_push1(heap,40);

        vlogw($(heap.size_node()));
        while (heap.is_empty() == false)
        {
            auto val = heap.pop_root();
            vlogd($(val));
        }
    }  
    {
        Theap<int,Theap_comp_max> heap;
        for(int i=40;i>0;i--)
        {
            heap.insert_node(i);
        }

        vlogw($(heap.size_node()));
        while (heap.is_empty() == false)
        {
            auto val = heap.pop_root();
            vlogd($(val));
        }
    }  
    {
        Theap<int,Theap_comp_min> heap;
        fn_push2(heap,40);

        vlogw($(heap.size_node()));
        while (heap.is_empty() == false)
        {
            auto val = heap.pop_root();
            vlogd($(val));
        }
    }  

}

void test_3()
{
    int count = 10000000;

    {
        Theap<int,Theap_comp_min> heap;
        {
            Ftimel t;
            for(int i=1;i<=count;i++)
            {
                heap.insert_node(i);
            }
            vlogd($(t.to_string()) $(heap.size_node()) );
        }
        int sum = show_node(heap._root);
        vlogd($(sum));
        {
            Ftimel t;
            while(heap.is_empty() == false)
            {
                heap.pop_root();
            }
            vlogd($(t.to_string()) $(heap.size_node()) );
        }

    }

    {
        Theap<int,Theap_comp_max> heap;
        {
            Ftimel t;
            for(int i=1;i<=count;i++)
            {
                heap.insert_node(i);
            }
            vlogd($(t.to_string()) $(heap.size_node()) );
        }
        {
            Ftimel t;
            while(heap.is_empty() == false)
            {
                heap.pop_root();
            }
            vlogd($(t.to_string()) $(heap.size_node()) );
        }

    }

}

void test_4()
{
    struct heap_val_int
    {
        heap_node node;
        int val;
    };

    #ifndef container_of
    #define container_of(ptr, type, member) \
    ((type*)((char*)(ptr) - offsetof(type, member)))
    #endif

    int count = 10000000;

    {
        heap hp;    
        heap_init(&hp,[](const struct heap_node* lhs, const struct heap_node* rhs)->int {
            heap_val_int *lv = container_of(lhs,heap_val_int,val);
            heap_val_int *rv = container_of(rhs,heap_val_int,val);
            return lv->val < rv->val;
        });

        {
            Ftimel t;
            for(int i=1;i<=count;i++)
            {
                heap_val_int *ct = new heap_val_int;
                ct->val = i;
                ct->node.left = nullptr;
                ct->node.right = nullptr;
                ct->node.parent = nullptr;
                heap_insert(&hp,&ct->node);
            }
            vlogd($(t.to_string()));
        }
        {
            Ftimel t;
            {
                while(hp.nelts > 0)
                {
                    heap_dequeue(&hp);
                }
            }
            vlogd($(t.to_string()));
        }
    }


}


void test_5()
{
    {
        Theap<int,Theap_comp_max> heap;
        for(int i=1;i<=10000000;i++)
        {
            heap.insert_node(i);
        }

        // show_node(heap._root);
        vlogd($(heap.size_node()));
        vlogd($(heap.is_empty()));
        vlogd($(heap.check_root()));
        vlogd($(heap.value_tail()));
        vlogd($(heap._tail->_parent->_value));

        {
            auto n = heap.find_tail_parent(heap._size-14);
            vlogd($(n->_value));
        }
        {
            auto n = heap.find_tail_parent(heap._size-15);
            vlogd($(n->_value));
        }
        {
            auto n = heap.find_tail_parent(heap._size-16);
            vlogd($(n->_value));
        }

    }
    {
        static const size_t _max_one = (1UL << 63);
        vlogd($(_max_one));
    }
}

void test_6()
{
    Theap<int,Theap_comp_max> heap;
    for(int i=1;i<=20;i++)
    {
        heap.insert_node(i);
    }
    show_node(heap._root);

    heap.remove_node(1);
    heap.remove_node(2);
    heap.remove_node(3);
    heap.remove_node(4);
    heap.remove_node(5);
    // heap.remove_node(6);
    // heap.remove_node(7);
    // heap.remove_node(8);
    // heap.remove_node(9);
    // heap.remove_node(10);
    // heap.remove_node(11);
    // heap.remove_node(12);
    // heap.remove_node(13);
    // heap.remove_node(14);
    // heap.remove_node(15);
    heap.remove_node(16);
    heap.remove_node(17);
    heap.remove_node(18);
    heap.remove_node(19);
    heap.remove_node(20);

    show_node(heap._root);

    vlogd($(heap.size_node()));
    while(heap.is_empty() == false)
    {
        auto s1 = heap.pop_root();
        vlogd($(s1));
    }
}


struct TestA
{
    TestA() {};
    TestA(int max,int min,int val) : _max(max),_min(min),_val(val) {};
    int _max = 0;
    int _min = 0;
    int _val = 0;
    int sum_value() { return _max+_min+_val; }

    bool is_max(const TestA &ct)
    {
        return (_max+_min+_val) > (ct._max+ct._min+ct._val);
    }

    bool is_min(const TestA &ct)
    {
        return (_max+_min+_val) < (ct._max+ct._min+ct._val);
    }

    bool is_equal(const TestA &ct)
    {
        return _val == ct._val;
    }

    bool operator>(const TestA &ct)
    {
        return is_max(ct);
    }

    bool operator<(const TestA &ct)
    {
        return is_max(ct);
    }

    bool operator==(const TestA &ct)
    {
        return is_equal(ct);
    }
};


void test_7()
{
    Theap<TestA,Theap_comp_max> heap;

    for(int i=1;i<=20;i++)
    {
        TestA a {i,i+10,i+100};
        heap.insert_node(a);
    }   

    {
        int i = 4;
        heap.remove_node(TestA{i,i+10,i+100});
    }
    {
        TestA a;
        a._val = 108;
        heap.remove_node(a);
    }

    while(heap.is_empty() == false)
    {
        auto s1 = heap.pop_root();
        vlogd($(s1._max) $(s1._min) $(s1._val) $(s1.sum_value()) $(heap.size_node()));
    }

}

int main(int argc, char *argv[])
{
    test_1();   
    test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();
    // test_7();


    // for(int i=1;i<=40;i++)
    // {
    //     std::cout<<i<<",";
    // }
    // std::cout<<std::endl;

    return 0;
}