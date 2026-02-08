#ifndef BHEAP_H
#define BHEAP_H

#include <vector>
#include <cmath>
#include <queue>
#include <limits>
#include <utility>

#include "Btype.h"

namespace bh {

// 最大堆对比函数-总是大的在树根-需存在操作符
template <typename T>
struct Bheap_comp_max
{
    inline static bool comp(const T &a, const T &b)
    {
        if(a > b) {
            return true;
        }
        return false;
    }
};

// 最小堆对比函数-总是小的在树根-需存在操作符
template <typename T>
struct Bheap_comp_min
{
    inline static bool comp(const T &a, const T &b)
    {
        if(a < b) {
            return true;
        }
        return false;
    }
};

// 大小堆树节点
template <typename T>
struct Bheap_node
{
    Bheap_node() {}
    Bheap_node(T val) : _value(val) {}

    Bheap_node *_parent = nullptr; // 父节点
    Bheap_node *_right = nullptr;  // 右节点
    Bheap_node *_left = nullptr;   // 左节点
    T _value;                      // 存储值
};

// 大小堆二叉树
template <typename Tval, template <typename> class Tcomp>
class Bheap
{
public:
    // 迭代器-支持前后移动-非常慢-为了保持树结构不可改变迭代器指向数据
    struct iterator
    {
        const Bheap *_heap;
        uint64 _idx;
        iterator(const Bheap *h, uint64 i) : _heap(h), _idx(i) {}
        const Tval &operator*() const { return _heap->find_index(_idx)->_value; }
        const Tval *operator->() const { return &(_heap->find_index(_idx)->_value); }
        iterator &operator++()
        {
            _idx++;
            return *this;
        }
        iterator &operator--()
        {
            _idx--;
            return *this;
        }
        bool operator==(const iterator &other) const { return _idx == other._idx; }
        bool operator!=(const iterator &other) const { return _idx != other._idx; }
    };

    inline iterator begin() { return iterator(this, 0); }

    inline iterator begin() const { return iterator(this, 0); }

    inline iterator end() { return iterator(this, _size); }

    inline iterator end() const { return iterator(this, _size); }

public:
    // 初始化树根
    Bheap()
    {
        _root = new Bheap_node<Tval>;
        _tail = new Bheap_node<Tval>;
        _tail->_parent = _root;
    }

    // 拷贝构造-拷贝需要重排速度很慢
    Bheap(const Bheap &other) : Bheap()
    {
        std::queue<Bheap_node<Tval> *> que_node;
        que_node.push(other._root);
        while(que_node.empty() == false) {
            uint64 size = que_node.size();
            for(uint64 i = 0; i < size; i++) {
                Bheap_node<Tval> *node = que_node.front();
                que_node.pop();
                insert_node(node->_value);

                Bheap_node<Tval> *nl = node->_left;
                if(nl) {
                    que_node.push(nl);
                }

                Bheap_node<Tval> *nr = node->_right;
                if(nr) {
                    que_node.push(nr);
                }
            }
        }
    }

    // 赋值拷贝
    Bheap &operator=(Bheap other)
    {
        std::swap(_size, other._size);
        std::swap(_root, other._root);
        std::swap(_tail, other._tail);
        return *this;
    }

    // 析构时清空分配内存
    ~Bheap()
    {
        clear();
        delete _root;
        delete _tail;
        _root = nullptr;
        _tail = nullptr;
    }

    // 插入新节点
    inline void insert_node(Tval val)
    {
        if(_size == 0) {
            _root->_value = val;
            _size++;
        }
        else {
            Bheap_node<Tval> *node = new Bheap_node<Tval>(val);
            push_node_tail(node);
            move_up(node);
            if(is_left_node()) {
                update_tail();
            }
        }
    }

    // 检查根节点
    inline Tval check_root()
    {
        if(_size == 0) {
            return Tval();
        }
        return _root->_value;
    }

    // 弹出树根值
    inline Tval pop_root()
    {
        if(_size == 0) {
            return Tval();
        }
        if(_size == 1) {
            _size--;
            return _root->_value;
        }

        // 交换树根和尾节点-上扬
        Tval val = _root->_value;
        Bheap_node<Tval> *tail = nullptr;
        if(is_left_node()) {
            tail = tail_node();
        }
        else {
            tail = _tail->_parent->_left;
        }
        swap_value(_root, tail);

        // 释放尾节点-减去数量
        Bheap_node<Tval> *ptail = tail->_parent;
        if(ptail->_left == tail) {
            ptail->_left = nullptr;
        }
        else {
            ptail->_right = nullptr;
        }
        delete tail;
        _size--;

        move_down(_root);
        if(is_left_node() == false) {
            update_tail();
        }
        return val;
    }

    // 清空堆树并释放内存-广度优先-树根不释放内存
    inline void clear()
    {
        if(_size == 0) {
            return;
        }

        std::queue<Bheap_node<Tval> *> que_clear;
        que_clear.push(_root);

        while(que_clear.empty() == false) {
            uint64 size = que_clear.size();
            for(uint64 i = 0; i < size; i++) {
                Bheap_node<Tval> *node = que_clear.front();
                que_clear.pop();

                Bheap_node<Tval> *nl = node->_left;
                if(nl) {
                    que_clear.push(nl);
                }

                Bheap_node<Tval> *nr = node->_right;
                if(nr) {
                    que_clear.push(nr);
                }

                if(node != _root) {
                    delete node;
                    node = nullptr;
                }
                else {
                    _root->_left = nullptr;
                    _root->_right = nullptr;
                    _tail->_parent = _root;
                }
            }
        }
        _size = 0;
    }

    // 返回最后一个插入的值
    inline Tval value_tail()
    {
        Bheap_node<Tval> *tail = tail_node();
        if(tail) {
            return tail->_value;
        }
        return _root->_value;
    }

    // 从堆数中移除传入值-移除成功返回true-未找到返回false
    inline bool remove_node(Tval val)
    {
        Bheap_node<Tval> *node = find_node(val);
        if(node == nullptr) {
            return false;
        }

        if(node == _root) {
            pop_root();
        }
        else {
            // 交换查询节点和根节点-将交换节点移动到根节点的前一层等待交换-弹出根节点
            // 弹出交换节点过程中尾节点开始下沉会将在前一层等待原本的根节点重新归位到根节点位置
            swap_value(_root, node);
            while(true) {
                if(node->_parent == _root) {
                    break;
                }
                if(Tcomp<Tval>::comp(node->_value, node->_parent->_value)) {
                    swap_value(node, node->_parent);
                    node = node->_parent;
                }
                else {
                    break;
                }
            }
            pop_root();
        }
        return true;
    }

    // 返回节点数
    inline uint64 size() const { return _size; }

    // 判断堆树是否为空
    inline bool is_empty() const { return _size == 0; }

    // 判断值是否存在堆数中
    inline bool is_exist(Tval val) { return find_node(val) != nullptr; }

protected:
    // internal
    // 找到节点指向的指针-未找到返回NULL
    inline Bheap_node<Tval> *find_node(Tval val)
    {
        if(_size == 0) {
            return nullptr;
        }

        std::queue<Bheap_node<Tval> *> que_node;
        que_node.push(_root);

        while(que_node.empty() == false) {
            uint64 size = que_node.size();
            for(uint64 i = 0; i < size; i++) {
                Bheap_node<Tval> *node = que_node.front();
                que_node.pop();
                if(node->_value == val) {
                    return node;
                }

                Bheap_node<Tval> *nl = node->_left;
                if(nl) {
                    que_node.push(nl);
                }

                Bheap_node<Tval> *nr = node->_right;
                if(nr) {
                    que_node.push(nr);
                }
            }
        }
        return nullptr;
    }

    // 查找下标位置-每次都需要从头开始
    inline Bheap_node<Tval> *find_index(uint64 index) const
    {
        if(_size == 0) {
            return nullptr;
        }
        if(index == 0) {
            return _root;
        }
        if(index >= _size) {
            return nullptr;
        }

        std::queue<Bheap_node<Tval> *> que_node;
        que_node.push(_root);
        uint64 count = 0;
        while(que_node.empty() == false && count <= index) {
            uint64 size = que_node.size();
            for(uint64 i = 0; i < size; i++) {
                Bheap_node<Tval> *node = que_node.front();
                que_node.pop();
                if(count == index) {
                    return node;
                }
                count++;

                Bheap_node<Tval> *nl = node->_left;
                if(nl) {
                    que_node.push(nl);
                }

                Bheap_node<Tval> *nr = node->_right;
                if(nr) {
                    que_node.push(nr);
                }
            }
        }
        return nullptr;
    }

    // 加入到尾节点位置
    inline void push_node_tail(Bheap_node<Tval> *node)
    {
        Bheap_node<Tval> *ptail = _tail->_parent;
        node->_parent = ptail;

        if(is_left_node()) {
            node->_parent->_left = node;
        }
        else {
            node->_parent->_right = node;
        }
        _size++;
    }

    // 判断尾部节点方向
    inline bool is_left_node()
    {
        if(_size % 2 == 1) {
            return true;
        }
        return false;
    }

    // 判断传入节点是父节点的左右方向
    inline bool is_left_node(Bheap_node<Tval> *node, Bheap_node<Tval> *parent)
    {
        if(parent->_left == node) {
            return true;
        }
        return false;
    }

    // 节点上升-从尾部插入
    inline void move_up(Bheap_node<Tval> *node)
    {
        Bheap_node<Tval> *next = node;
        while(true) {
            if(next->_parent == nullptr) {
                break;
            }

            if(Tcomp<Tval>::comp(next->_value, next->_parent->_value)) {
                swap_value(next, next->_parent);
                next = next->_parent;
            }
            else {
                break;
            }
        }
    }

    // 向下移动-正常是从树根开始
    inline void move_down(Bheap_node<Tval> *node)
    {
        Bheap_node<Tval> *next = node;
        while(next) {
            // 父节点总是和最小的子节点交换-先对比右节点
            Bheap_node<Tval> *snode = nullptr;
            if(next->_right) {
                if(Tcomp<Tval>::comp(next->_right->_value, next->_value)) {
                    snode = next->_right;
                }
            }

            // 对比左节点时如果右节点已经被选中-左节点和右节点对比而不是父节点
            if(next->_left) {
                if(snode) {
                    if(Tcomp<Tval>::comp(next->_left->_value, next->_right->_value)) {
                        snode = next->_left;
                    }
                }
                else {
                    if(Tcomp<Tval>::comp(next->_left->_value, next->_value)) {
                        snode = next->_left;
                    }
                }
            }

            if(snode) {
                swap_value(next, snode);
                next = snode;
            }
            else {
                break;
            }
        }
    }

    // 交换节点
    inline void swap_value(Bheap_node<Tval> *node, Bheap_node<Tval> *parent)
    {
        Tval tm = node->_value;
        node->_value = parent->_value;
        parent->_value = tm;
    }

    // 根据传入位置返回指向下一个位置的父节点
    inline Bheap_node<Tval> *find_tail_parent(uint64 size)
    {
        if(size == 0) {
            return nullptr;
        }
        if(size < 3) {
            return _root;
        }

        // 将数值从左忘右推进的bit和对比符号比较-如果为1则代表应该走右节点-可以从数值的二进制中找规律
        Bheap_node<Tval> *node = _root;
        bool find = false;
        uint64 path = size + 1;
        for(uint64 i = 0; i < (sizeof(path) * 8) - 1; i++) {
            if(find && (path & _BH_ONE_HIGH_INT64_)) {
                node = node->_right;
            }
            else if(find) {
                node = node->_left;
            }
            else if((find == false) && (path & _BH_ONE_HIGH_INT64_)) {
                find = true;
            }
            path <<= 1;
        }
        return node;
    }

    // 更新尾节点位置
    inline void update_tail()
    {
        Bheap_node<Tval> *tail = find_tail_parent(_size);
        if(tail) {
            _tail->_parent = tail;
        }
    }

    // 返回最后一个值的节点指针
    inline Bheap_node<Tval> *tail_node()
    {
        Bheap_node<Tval> *ptail = find_tail_parent(_size - 1);
        Bheap_node<Tval> *tnode = nullptr;
        if(ptail) {
            if(ptail->_right != nullptr) {
                tnode = ptail->_right;
            }
            else {
                tnode = ptail->_left;
            }
        }
        return tnode;
    }

protected:
    uint64 _size = 0;                  // 堆树大小
    Bheap_node<Tval> *_root = nullptr; // 根节点-总是存在
    Bheap_node<Tval> *_tail = nullptr; // 尾节点-总是指向下一个加入的位置
};

//
//
//
//

// 定义快捷使用类型
template <typename T>
using Bheap_max = Bheap<T, Bheap_comp_max>;

template <typename T>
using Bheap_min = Bheap<T, Bheap_comp_min>;

} // namespace bh

#endif // BHEAP_H
