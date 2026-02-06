#ifndef BDIV_H
#define BDIV_H

#include "Bstr.h"

namespace bh {

// 切割字符串
class Bdiv
{

public:
    Bdiv(Bstrvi str) : _str(str) {}

    // 切割参数进入
    template <typename... Tarr>
    inline Bstr operator()(const Tarr &...arg)
    {
        if(_str.size() == 0 || sizeof...(arg) == 0) {
            return "";
        }
        if(section(arg...)) {
            return _str;
        }
        return "";
    }

protected:
    // 退出函数
    template <typename... Tarr>
    inline bool section()
    {
        return true;
    }

    // 根据分隔符和获取部分标记切割字符串-可以对同一字符进行多次切割
    template <typename... Tarr>
    inline bool section(Bstrvi flag, int32 ib, int32 ie, const Tarr &...arg)
    {
        uint64 bpos = 0;
        uint64 epos = 0;

        if(ib >= 0 && ie >= 0) {
            // 正向
            // 开始下标
            if(ib > 0) {
                bpos = find(flag, ib, 0, true);
                if(bpos >= _str.size()) {
                    return false;
                }
            }
            // 结束下标
            epos = find(flag, ie - ib + 1, bpos, false);
            if(epos == dstr::npos || epos <= bpos) {
                return false;
            }
            _str = Bstrvi(_str, bpos, epos - bpos);
        }
        else if(ib < 0 && ie < 0) {
            // 反向
            // 反向时结束下标先移动
            epos = _str.size();
            if(ie < -1) {
                epos = rfind(flag, std::abs(ie) - 1, epos, false);
                if(epos > _str.size()) {
                    return false;
                }
            }
            // 开始下标
            bpos = rfind(flag, std::abs(ib - ie) + 1, epos - 1, true);
            if(bpos >= _str.size() || epos <= bpos) {
                return false;
            }
            _str = Bstrvi(_str, bpos, epos - bpos);
        }
        else {
            // 混合模式
            // 开始下标
            if(ib > 0) {
                bpos = find(flag, ib, 0, true);
                if(bpos >= _str.size()) {
                    return false;
                }
            }
            else if(ib < 0) {
                bpos = rfind(flag, std::abs(ib), _str.size(), true);
                if(bpos >= _str.size()) {
                    return false;
                }
            }

            // 结束下标
            if(ie >= 0) {
                epos = find(flag, ie + 1, 0, false);
                if(epos <= bpos) {
                    return false;
                }
            }
            else if(ie < -1) {
                epos = rfind(flag, std::abs(ie) - 1, _str.size(), false);
                if(epos <= bpos) {
                    return false;
                }
            }

            _str = Bstrvi(_str, bpos, epos - bpos);
        }

        return section(arg...);
    }

    // 查找字符串
    inline uint64 find(Bstrvi flag, int32 count, uint64 pos, bool offset) const
    {
        if(count <= 0) {
            return dstr::npos;
        }
        for(int32 i = 0; i < count; i++) {
            if(i > 0) {
                pos++;
            }
            pos = _str.find(flag, pos);
            if(pos == dstr::npos) {
                if(i == count - 1) {
                    return _str.size();
                }
                return dstr::npos;
            }
        }
        if(offset) {
            pos += flag.size();
        }
        return pos;
    }

    // 反向查找字符串
    inline uint64 rfind(Bstrvi flag, int32 count, uint64 pos, bool offset) const
    {
        if(count <= 0) {
            return dstr::npos;
        }
        for(int32 i = 0; i < count; i++) {
            if(i > 0) {
                pos--;
            }
            pos = _str.rfind(flag, pos);
            if(pos == dstr::npos) {
                if(i == count - 1) {
                    return 0;
                }
                return dstr::npos;
            }
        }
        if(offset) {
            pos += flag.size();
        }
        return pos;
    }

protected:
    Bstrvi _str;
};

} // namespace bh

#endif // BDIV_H
