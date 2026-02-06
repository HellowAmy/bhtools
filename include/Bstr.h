#ifndef BSTR_H
#define BSTR_H

#include "Bstrvi.h"

namespace bh {

// 增强型字符串类 继承自标准字符串并扩展功能
class Bstr : public dstr
{
public:
    struct range
    {
        uint64 bpos = 0;
        uint64 epos = 0;
        operator bool() const { return bpos != dstr::npos && epos != dstr::npos; }
    };

public:
    using dstr::dstr;

    Bstr(cstr d) { this->assign(d); }

    Bstr(Bstrvi d) { this->assign(d.data(), d.size()); }

    // 重载等于操作符 支持视图比较
    bool operator==(Bstrvi d) const { return compare_view(d); }

    bool operator==(cstr d) const { return compare_view(d); }

    bool operator==(cchp d) const { return compare_view(d); }

    // 重载流式操作符 方便字符串拼接
    inline Bstr &operator<<(Bstrvi d)
    {
        this->append(d.data(), d.size());
        return *this;
    }

    inline Bstr &operator<<(char d)
    {
        this->push_back(d);
        return *this;
    }

    // 转换回标准字符串格式
    inline dstr to_str() const { return *this; }

    // 与视图进行内容比对
    inline bool compare_view(Bstrvi d) const
    {
        if(d.size() != size()) {
            return false;
        }
        return std::equal(c_str(), c_str() + size(), d.data());
    }

    // 判断是否包含指定子视图内容
    inline bool is_contain(Bstrvi sub)
    {
        uint64 index = find(sub.data(), 0, sub.size());
        return index != dstr::npos;
    }

    // 查找子视图所在的范围区间
    inline range find_range(Bstrvi sub, uint64 pos = 0)
    {
        range ret;
        uint64 index = find(sub.data(), pos, sub.size());
        ret.bpos = index;
        ret.epos = index + sub.size();
        return ret;
    }
};

using BCstr = const Bstr &;

} // namespace bh

#endif // BSTR_H