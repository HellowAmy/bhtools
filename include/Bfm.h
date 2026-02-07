#ifndef BFM_H
#define BFM_H

#include "Bstr.h"
#include "Bstrto.h"

namespace bh {

// 格式化字符串-从左到右替换参数
// 速度比 snprintf 函数慢三倍
class Bfm
{
public:
    Bfm(Bstrvi org) : _org(org)
    {
        // 优化初始化字符串缓冲区
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

        // 初始化列表解包
        bool next = true;
        bh::int32 dofor[]{0, ((next = (next && format(Bstrto::to_str(arg)))), 0)...};
        if(_offset < _org.size()) {
            _str << Bstrvi(_org, _offset, _org.size() - _offset);
        }
        return _str;
    }

    // 格式化字符串
    inline bool format(Bstrvi val)
    {
        uint64 pos = _offset;
        for(uint64 i = _offset; i < _org.size() - 1; i++) {
            if(_org[i] == strb() && _org[i + 1] == stre()) {
                if(pos != i) {
                    _str << Bstrvi(_org, pos, i - pos);
                }
                _str << val;
                _offset += 2;
                return true;
            }
            _offset++;
        }
        _str << Bstrvi(_org, pos, _org.size() - pos);
        _offset = _org.size();
        return false;
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
