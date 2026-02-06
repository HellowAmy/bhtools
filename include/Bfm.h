#ifndef BFM_H
#define BFM_H

#include "Bstr.h"
#include "Bstrto.h"

namespace bh {

// 快速格式化字符串
class Bfm
{
public:
    Bfm(Bstrvi org) : _org(org)
    {
        // 初始化字符串缓冲区
        if(org.size() < _BH_INT_256_) {
            _str.reserve(_BH_INT_256_);
        }
        else if(org.size() < _BH_INT_2048_) {
            _str.reserve(_BH_INT_2048_);
        }
        else {
            _str.reserve(org.size() * 2);
        }
    }

    // 传入替换参数-不限类型
    template <typename... Targ>
    inline Bstr operator()(Targ &&...arg)
    {
        if(_org.size() == 0) {
            return "";
        }
        cfms(std::forward<Targ>(arg)...);

        if(_offset < _org.size()) {
            _str << Bstrvi(_org, _offset, _org.size() - _offset);
        }
        return _str;
    }

    // 终止函数
    inline void cfms() {}

    // 退出时回收尾部字符
    template <typename T, typename... Targ>
    inline void cfms(T &&val, Targ &&...arg)
    {
        format(Bstrto::to_str(std::forward<T>(val)));
        cfms(arg...);
    }

    // 格式化字符串
    inline void format(Bstrvi val)
    {
        uint64 pos = _offset;
        for(uint64 i = _offset; i < _org.size() - 1; i++) {
            if(_org[i] == strb() && _org[i + 1] == stre()) {
                if(pos != i) {
                    _str << Bstrvi(_org, pos, i - pos);
                }
                _str << val;
                _offset += 2;
                return;
            }
            _offset++;
        }
        _str << Bstrvi(_org, pos, _org.size() - pos);
    }

protected:
    inline static char strb() { return '{'; };
    inline static char stre() { return '}'; };

protected:
    uint64 _offset = 0;
    Bstrvi _org;
    Bstr _str;
};

} // namespace bh

#endif // BFM_H
