#ifndef BUNPACK_H
#define BUNPACK_H

#include <functional>
#include <mutex>
#include <vector>

#include "Btype.h"
#include "Bbyte.h"

namespace bh {

// 拆包参数-分隔符
struct Bunfd_delimit
{
    const dstr _delimit = "\n";
};

// 拆包函数-分隔符
template <typename T = Bunfd_delimit>
struct Bunf_delimit
{
    // 传入数据返回包体
    static dstr pack(cstr ctx)
    {
        T arg;
        return ctx + arg._delimit;
    }

    // 拆包函数
    std::vector<dstr> unpack(cstr ctx, bool ths)
    {
        uint64 sidel = _arg._delimit.size();
        std::vector<dstr> vec;

        if(sidel == 0) {
            return vec;
        }
        if(ths) {
            _mux.lock();
        }

        dstr all = _save + ctx;
        uint64 go = _save.size();

        // 循环拆包
        while(go < all.size()) {
            // 检查到分隔符
            if(all[go] == _arg._delimit[0]) {
                if((go + sidel) > all.size()) {
                    break;
                }

                // 检测分割符
                bool into = true;
                for(uint64 i = 0; i < sidel; i++) {
                    if(all[go + i] != _arg._delimit[i]) {
                        into = false;
                        go += i;
                        break;
                    }
                }

                // 匹配成功
                if(into) {
                    dstr data = dstr(all.begin(), all.begin() + go);
                    vec.push_back(data);

                    all = dstr(all.begin() + go + sidel, all.end());
                    go = 0;
                }
            }
            go++;
        }
        _save = all;

        if(ths) {
            _mux.unlock();
        }
        return vec;
    }

    T _arg;           // 拆包函数参数
    std::mutex _mux;  // 线程锁
    dstr _save;       // 保存上次数据
};

// 拆包函数-包长度
template <typename T = uint64>
struct Bunf_length
{
    // 传入数据返回包体
    static dstr pack(cstr ctx)
    {
        T arg;
        arg = ctx.size();
        arg = Bendian::to_net(arg);
        return dstr((char *)&arg, sizeof(arg)) + ctx;
    }

    // 拆包函数
    std::vector<dstr> unpack(cstr ctx, bool ths)
    {
        if(ths) {
            _mux.lock();
        }

        std::vector<dstr> vec;
        dstr all = _save + ctx;
        uint64 len_head = sizeof(_arg);

        while(true) {
            // 包头字节不足退出
            if(all.size() < len_head) {
                break;
            }

            // 数据长度不足退出
            uint64 len_data = all.size() - len_head;
            dstr head = dstr(all.begin(), all.begin() + len_head);
            _arg = *(decltype(_arg) *)head.c_str();
            _arg = Bendian::to_host(_arg);

            if(len_data < _arg) {
                break;
            }

            // 数据达到或超出包范围-回调包体数据
            dstr data = dstr(all.begin() + len_head, all.begin() + len_head + _arg);
            vec.push_back(data);

            all = dstr(all.begin() + len_head + _arg, all.end());
        }
        _save = all;

        if(ths) {
            _mux.unlock();
        }
        return vec;
    }

    T _arg;           // 拆包函数参数
    std::mutex _mux;  // 线程锁
    dstr _save;       // 保存上次数据
};

// 数据拆包组合
template <typename Tfn>
struct Bunpack
{
    // 拆包函数
    std::vector<dstr> unpack(cstr ctx, bool ths = true) { return _fn.unpack(ctx, ths); }

    // 组包函数
    inline static dstr pack(cstr ctx) { return Tfn::pack(ctx); }

    Tfn _fn; // 拆包类型
};

// 定义快捷使用类型
using Bunpack_len = Bunpack<Bunf_length<>>;
using Bunpack_del = Bunpack<Bunf_delimit<>>;

} // namespace bh

#endif // BUNPACK_H
