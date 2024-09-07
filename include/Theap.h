
#ifndef THEAP_H
#define THEAP_H

#include <iostream>
#include <vector>
#include <cmath>

#include <assert.h>
#include "Tlog.h"


namespace bhtools {


//
template<typename T>
struct Theap_node
{
    Theap_node() { }
    Theap_node(T val) : _value(val) { }

    Theap_node *_parent = nullptr;  //
    Theap_node *_right = nullptr;   //
    Theap_node *_left = nullptr;    //
    T _value;                       //
};


// 
template<typename T>
struct Theap_comp
{
    inline static bool comp(T a, T b)
    {
        if(a > b) { return true; } 
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

    // 插入新节点
    void insert_node(Tval val)
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

    // 
    Tval pop_root()
    {
        if(_size <= 1) 
        { 

            return _root->_value; 
        }

        Theap_node<Tval> *tail = tail_node();
        return Tval();
        // else if(_size > 1)
        // {

        // }
    }

    // 
    size_t size()
    {
        return _size;
    }

    //
    bool dalete_node(Tval val)
    {
        return false;
    }


    //
    bool find_node(Tval val)
    {
        return false;
    }

    // 加入到尾节点位置
    void push_node_tail(Theap_node<Tval> *node)
    {
        Theap_node<Tval> *ptail = _tail->_parent;
        node->_parent = ptail;

        if(is_left_node()) { node->_parent->_left = node; }
        else { node->_parent->_right = node; }
        _size++;
    }

    // 判断尾部节点方向
    bool is_left_node()
    {
        if(_size % 2 == 1) { return true; }
        return false;
    }

    // 判断传入节点是父节点的左右方向
    bool is_left_node(Theap_node<Tval> *node,Theap_node<Tval> *parent)
    {
        if(parent->_left == node) { return true; }
        return false;
    }

    //
    void move_node(Theap_node<Tval> *node)
    {

    }

    // 节点上升-从尾部插入
    void move_up(Theap_node<Tval> *node)
    {
        Theap_node<Tval> *next = node;
        while(true)
        {
            if(next->_parent == nullptr) { break; }

            if(Tcomp::comp(next->_value,next->_parent->_value))
            { swap_node(next,next->_parent); next = next->_parent; }
            else { break; }
        }
    }

    // 
    void move_down(Theap_node<Tval> *node)
    {

    }

    // 交换节点
    void swap_node(Theap_node<Tval> *node,Theap_node<Tval> *parent)
    {
        Tval tm = node->_value;
        node->_value = parent->_value;
        parent->_value = tm;
    }

    // 根据传入位置返回指向下一个位置的父节点
    Theap_node<Tval>* find_tail_parent(size_t size)
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
    void update_tail()
    {
        Theap_node<Tval> *tail = find_tail_parent(_size);
        if(tail) { _tail->_parent = tail; } 
    }

    // 返回最后一个值的节点指针
    Theap_node<Tval>* tail_node()
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

    // 返回最后一个插入的值
    Tval value_tail()
    {
        Theap_node<Tval> *tail = tail_node();
        if(tail) { return tail->_value; }
        return _root->_value; 
    }

    size_t _size = 0;                       //
    Tcomp _comp;                            // 
    Theap_node<Tval> *_root = nullptr;      //
    Theap_node<Tval> *_tail = nullptr;      //
};


} // bhtools


#endif // THEAP_H
