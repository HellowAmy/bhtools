

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <queue>
#include "Tlog.h"
#include "Theap.h"

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
    auto fn_show = [](int count){
        {
            Theap<int,Theap_comp<int>> heap;
            for(int i=1;i<=count;i++)
            {
                heap.insert_node(i);
            }

            vlogd(heap._root->_value);
            vlogd(heap._tail->_parent->_value);
            vlogd(heap._size);
            vlogd(heap.value_tail());

            show_node(heap._root);
            heap.clear_heap();
            show_node(heap._root);
            vlogd(heap._size);

            vlogi($("===="));
        }
    };


    auto fn_push = [](Theap<int,Theap_comp<int>> &heap,int count){
        for(int i=1;i<=count;i++)
        {
            heap.insert_node(i);
        }
    };


    {
        Theap<int,Theap_comp<int>> heap;
        fn_push(heap,10);

        show_node(heap._root);
        
        for(int i=0;i<20;i++)
        {
            {
                vlogi("============= " $(heap.size_node()));
                auto val = heap.pop_root(); 
                vlogi($(val) $(heap.size_node()));
                show_node(heap._root);
            }
        }

        // {
        //     auto val = heap.pop_root(); 
        //     vlogi($(val));
        //     show_node(heap._root);
        // }






    }



    // for(int i=1;i<=10;i++)
    // {
    //     fn_show(i);
    // }


    // {
    //     Theap<int,Theap_comp<int>> heap;
    //     for(int i=1;i<=10;i++)
    //     {
    //         heap.insert_node(i);
    //     }

    //     vlogd(heap._root->_value);
    //     vlogd(heap._tail->_parent->_value);
    //     vlogd(heap._size);


    //     show_node(heap._root);
    //     vlogi($("===="));


    //     vlogd($(heap.update_tail(10)->_value));
    //     vlogd($(heap.update_tail(9)->_value));
    //     vlogd($(heap.update_tail(8)->_value));

    //     vlogd(heap._root->_value);
    //     vlogd(heap._tail->_parent->_value);
    //     vlogd(heap._size);


    // }





    // for(int i=1;i<=77;i++)
    // {
    //     std::cout<<i<<",";
    // }
    // std::cout<<std::endl;




    // for()
    // fn_show(11);
    // fn_show(11);
    // fn_show(11);
    // fn_show(11);


    // {
    //     Theap<int,Theap_comp<int>> heap;
    //     for(int i=1;i<=7;i++)
    //     {
    //         heap.insert_node(i);
    //     }

    //     vlogd(heap._root->_value);
    //     vlogd(heap._tail->_parent->_value);
    //     vlogd(heap._size);
    //     show_node(heap._root);
    //     vlogi($("===="));
    // }
    // {
    //     Theap<int,Theap_comp<int>> heap;
    //     for(int i=1;i<=6;i++)
    //     {
    //         heap.insert_node(i);
    //     }

    //     vlogd(heap._root->_value);
    //     vlogd(heap._tail->_parent->_value);
    //     vlogd(heap._size);
    //     show_node(heap._root);
    //     vlogi($("===="));
    // }


    // show_node(heap._root);
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