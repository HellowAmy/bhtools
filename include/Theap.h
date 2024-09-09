
#ifndef THEAP_H
#define THEAP_H

// #include <iostream>
#include <vector>
#include <cmath>
#include <queue>

// #include <assert.h>
// #include "Tlog.h"


namespace bhtools {


// 大小堆树节点
template<typename T>
struct Theap_node
{
    Theap_node() { }
    Theap_node(T val) : _value(val) { }

    Theap_node *_parent = nullptr;  // 父节点
    Theap_node *_right = nullptr;   // 右节点
    Theap_node *_left = nullptr;    // 左节点
    T _value;                       // 存储的值
};


// 最大堆对比函数-总是大的在上
template<typename T>
struct Theap_comp_max
{
    inline static bool comp(T a, T b)
    {
        if(a > b) { return true; } 
        return false;
    }
};


// 最小堆对比函数-总是小的在上
template<typename T>
struct Theap_comp_min
{
    inline static bool comp(T a, T b)
    {
        if(a < b) { return true; } 
        return false;
    }
};


// 大小堆二叉树
template<typename Tval,typename Tcomp>
struct Theap
{
    // 初始化树根
    Theap() 
    {
        _root = new Theap_node<Tval>;
        _tail = new Theap_node<Tval>;
        _tail->_parent = _root;
    }

    // 析构时清空分配内存
    ~Theap()
    {
        clear_heap();
        delete _root;
        delete _tail;
        _root = nullptr;
        _tail = nullptr;
    }

    // 插入新节点
    inline void insert_node(Tval val)
    {
        if(_size == 0) { _root->_value = val; _size++; }
        else 
        {
            Theap_node<Tval> *node = new Theap_node<Tval>(val);
            push_node_tail(node);
            move_up(node);
            update_tail();
        }
    }   

    // 检查根节点
    inline Tval check_root()
    {
        if(_size == 0) { return Tval(); }
        return _root->_value;
    }

    // 弹出树根值
    inline Tval pop_root()
    {
        if(_size == 0) { return Tval(); }
        if(_size == 1) 
        { 
            _size--;
            return _root->_value; 
        }

        // 交换树根和尾节点-上扬
        Tval val = _root->_value;
        Theap_node<Tval> *tail = tail_node();
        swap_value(_root,tail);

        // 释放尾节点-减去数量
        Theap_node<Tval> *ptail = tail->_parent;
        if(ptail->_left == tail) { ptail->_left = nullptr; }
        else { ptail->_right = nullptr; }
        delete tail;
        _size--;

        move_down(_root);
        update_tail();
        return val;
    }

    // 清空堆树并释放内存-广度优先-树根不释放内存
    inline void clear_heap()
    {
        if(_size < 1) { return; }

        std::queue<Theap_node<Tval>*> que_clear;
        que_clear.push(_root);

        while (que_clear.empty() == false)
        {
            std::queue<Theap_node<Tval>*> que_level;

            size_t size = que_clear.size();
            for(size_t i=0;i<size;i++)
            {
                Theap_node<Tval> *node = que_clear.front();
                que_clear.pop();

                Theap_node<Tval> *nl = node->_left;
                if(nl) { que_clear.push(nl); }

                Theap_node<Tval> *nr = node->_right;
                if(nr) { que_clear.push(nr); }

                if(node != _root)
                {
                    delete node;
                    node = nullptr;
                }
                else 
                {
                    _root->_left = nullptr;
                    _root->_right = nullptr;
                }
            }
        }
        _size = 0;
    }

    // 返回最后一个插入的值
    inline Tval value_tail()
    {
        Theap_node<Tval> *tail = tail_node();
        if(tail) { return tail->_value; }
        return _root->_value; 
    }

    // 返回节点数
    inline size_t size_node() const { return _size; }

    // 判断堆树是否为空
    inline bool is_empty() const { return _size == 0; }



    // 加入到尾节点位置
    inline void push_node_tail(Theap_node<Tval> *node)
    {
        Theap_node<Tval> *ptail = _tail->_parent;
        node->_parent = ptail;

        if(is_left_node()) { node->_parent->_left = node; }
        else { node->_parent->_right = node; }
        _size++;
    }

    // 判断尾部节点方向
    inline bool is_left_node()
    {
        if(_size % 2 == 1) { return true; }
        return false;
    }

    // 判断传入节点是父节点的左右方向
    inline bool is_left_node(Theap_node<Tval> *node,Theap_node<Tval> *parent)
    {
        if(parent->_left == node) { return true; }
        return false;
    }

    // 节点上升-从尾部插入
    inline void move_up(Theap_node<Tval> *node)
    {
        Theap_node<Tval> *next = node;
        while(true)
        {
            if(next->_parent == nullptr) { break; }

            if(Tcomp::comp(next->_value,next->_parent->_value))
            { swap_value(next,next->_parent); next = next->_parent; }
            else { break; }
        }
    }

    // 向下移动-正常是从树根开始
    inline void move_down(Theap_node<Tval> *node)
    {
        Theap_node<Tval> *next = node;
        while (next)
        {
            // 父节点总是和最小的子节点交换-先对比右节点
            Theap_node<Tval> *snode = nullptr;
            if(next->_right) 
            { 
                if(Tcomp::comp(next->_right->_value,next->_value)) 
                { snode = next->_right; }
            }

            // 对比左节点时如果右节点已经被选中-左节点和右节点对比而不是父节点
            if(next->_left)
            {
                if(snode)
                {
                    if(Tcomp::comp(next->_left->_value,next->_right->_value)) 
                    { snode = next->_left; }
                }
                else 
                {
                    if(Tcomp::comp(next->_left->_value,next->_value)) 
                    { snode = next->_left; }
                }
            }

            if(snode) { swap_value(next,snode); next = snode; }
            else { break; }
        }
    }

    // 交换节点
    inline void swap_value(Theap_node<Tval> *node,Theap_node<Tval> *parent)
    {
        Tval tm = node->_value;
        node->_value = parent->_value;
        parent->_value = tm;
    }

    // 根据传入位置返回指向下一个位置的父节点
    inline Theap_node<Tval>* find_tail_parent(size_t size)
    {
        if(size == 0) { return nullptr; }
        if(size < 3) { return _root; }

        // 计算尾节点所在树的层级
        Theap_node<Tval> *node = _root;
        size_t sum = size - 2;
        size_t level = 2;
        while(true)
        {
            size_t val = std::pow(2,level);
            if(sum <= val) { break; }
            sum -= val;
            level++;
        }

        // 计算去往尾节点的左右路径
        size_t pos = size + 1;
        while(true)
        {
            size_t prev_sum = std::pow(2,level) -1;
            size_t prev_level = std::pow(2,level -1);

            size_t old_pos = pos;
            pos -= prev_sum;

            if(pos > prev_level) 
            { 
                node = node->_right;
                pos = old_pos - std::pow(2,level);
            }
            else 
            { 
                node = node->_left; 
                pos = old_pos - std::pow(2,level -1);
            }

            level--;
            if(level == 1) { break; }
        }
        return node;
    }

    // 更新尾节点位置
    inline void update_tail()
    {
        Theap_node<Tval> *tail = find_tail_parent(_size);
        if(tail) { _tail->_parent = tail; } 
    }

    // 返回最后一个值的节点指针
    inline Theap_node<Tval>* tail_node()
    {
        Theap_node<Tval> *ptail = find_tail_parent(_size -1);
        Theap_node<Tval> *tnode = nullptr;
        if(ptail)
        {
            if(ptail->_right != nullptr) { tnode = ptail->_right; }
            else { tnode = ptail->_left; }
        }
        return tnode;
    }


    size_t _size = 0;                       // 堆树大小
    Tcomp _comp;                            // 对比函数
    Theap_node<Tval> *_root = nullptr;      // 根节点-总是存在
    Theap_node<Tval> *_tail = nullptr;      // 尾节点-总是指向下一个加入的位置
};


} // bhtools


#endif // THEAP_H
