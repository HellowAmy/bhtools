#ifndef BARGV_H
#define BARGV_H

#include <iostream>
#include <vector>

#include "Btype.h"
#include "Bdiv.h"

// #include "Bstm.h"

namespace bh {

// 解析命令行传入参数
class Bargv
{
public:
    Bargv() {}
    ~Bargv() {}

    // 初始化参数列表-常规参数
    void init(int32 argc, char **argv)
    {
        for(int32 i = 0; i < argc; i++) {
            _vec.push_back(argv[i]);
        }
    }

    // 初始化参数列表-分析字符串
    void init(cstr args)
    {
        bool split = true;
        char csplit = ' ';
        dstr val;
        for(const char a : args) {
            if(split && a == ' ') {
                if(val.size() != 0) {
                    _vec.push_back(val);
                    val.clear();
                }
            }
            else if(a == '\'' || a == '"') {
                if(csplit == ' ') {
                    csplit = a;
                    split = !split;
                }
                else if(a == csplit) {
                    csplit == ' ';
                    split = !split;
                }
                else {
                    val.push_back(a);
                }
            }
            else {
                val.push_back(a);
            }
        }
        if(val.size() != 0) {
            _vec.push_back(val);
            val.clear();
        }
    }

    // 判断参数存在
    bool is_exist(cstr arg)
    {
        for(auto &a : _vec) {
            if(a == arg) {
                return true;
            }
        }
        return false;
    }

    // 存在参数时返回对应值
    dstr is_exist_arg(cstr arg, cstr end = "-")
    {
        bool find = false;
        for(int32 i = 0; i < _vec.size(); i++) {
            if(find) {
                if(is_exist_sub(_vec[i], end) == false) {
                    return _vec[i];
                }
                break;
            }

            if(find == false && _vec[i] == arg) {
                find = true;
            }
        }
        return "";
    }

    // 存在参数时返回对应参数列表
    std::vector<dstr> is_exist_args(cstr arg, cstr end = "-")
    {
        bool find = false;
        std::vector<dstr> vec_args;
        for(int32 i = 0; i < _vec.size(); i++) {
            if(find) {
                if(is_exist_sub(_vec[i], end)) {
                    return vec_args;
                }
                else {
                    vec_args.push_back(_vec[i]);
                }
            }

            if(find == false && _vec[i] == arg) {
                find = true;
            }
        }
        return vec_args;
    }

    // 存在参数时返回参数赋值的路径
    dstr is_exist_path(cstr arg, cstr end = "=")
    {
        for(int32 i = 0; i < _vec.size(); i++) {
            if(is_exist_sub(_vec[i], arg)) {
                return bh::Bdiv(_vec[i])(end, 1, 1).to_str();
            }
        }
        return "";
    }

    // 获取所有参数
    const std::vector<dstr> &get_args() { return _vec; }

protected:
    // 判断字符串是否存在子串
    inline static bool is_exist_sub(cstr str, cstr sub)
    {
        auto index = str.find(sub);
        return index != dstr::npos;
    }

protected:
    std::vector<dstr> _vec; // 存储所有传入的参数
};

} // namespace bh

#endif // BARGV_H
