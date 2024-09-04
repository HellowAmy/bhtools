
#ifndef FFM_H
#define FFM_H

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

#include "Tbase.h"

namespace bhtools {


// 
struct Ffinds
{
    // 
    inline static std::tuple<bool,size_t> find_sub(const std::string &str,const std::string &sub,size_t offset = 0)
    {
        auto it = std::find(str.begin() + offset,str.end(),sub);
        if(it != str.end())
        {
            size_t index = it - str.begin();
            return std::make_tuple(true,index);
        }
        return std::make_tuple(false,0);
    }

    // 
    inline static std::tuple<bool,size_t,size_t> find_sub(const std::string &str,const std::string &fb,const std::string &fe,size_t offset = 0)
    {
        auto rb = find_sub(str,fb,offset); 
        auto re = find_sub(str,fe,offset); 
        if(std::get<0>(rb) && std::get<0>(re))
        { return std::make_tuple(true,std::get<1>(rb),std::get<1>(re)); }

        return std::make_tuple(false,0,0);
    }

    // 
    inline static std::string section_range(const std::string &str,size_t ib,size_t ie)
    {
        std::string ret;
        size_t len = ie - ib;
        if(ie > ib)
        {
            ret.resize(len);
            for(size_t i=0;i<len;i++)
            {
                ret[i] = str[ib+i];
            }
        }
        return ret;
    }
};


// 
struct Ffm_base
{
    // 
    inline static std::string& strb() { static std::string s = "{"; return s; };
    inline static std::string& stre() { static std::string s = "}"; return s; };

    // 
    inline static std::tuple<bool,size_t,size_t> to_num(const std::string &str,const std::tuple<bool,size_t,size_t> &tup)
    {
        if(std::get<0>(tup))
        {
            size_t ib = std::get<1>(tup);
            size_t ie = std::get<2>(tup);
            std::string snum = Ffinds::section_range(str,ib + strb().size(),ie);
            size_t num = 0;
            if(Tfrom_string<size_t>(snum,num))
            {
                return std::make_tuple(true,num,ie + stre().size());
            }
        }   
        return std::make_tuple(false,0,0);
    }   

    // 
    inline static std::string copy_str(const std::string &str,size_t ib,size_t ie)
    {
        size_t len = ie - ib;
        if(ie > ib) { return std::string(str.begin() +ib,str.begin() +ib +len); }
        return "";
    }   
};


// 
struct Fsfm : public Ffm_base
{

    Fsfm(const std::string &str) : _str(str) { }

    // 
    template<class ...Tarr>
    std::string operator()(const Tarr &...arg)
    { return fms(arg...); }

    // 
    template<class T,class ...Tarr>
    std::string fms(T && val,const Tarr &...arg)
    {
        _vec.push_back(Tto_string(std::forward<T>(val)));
        return fms(arg...);
    }

    //
    template<class ...Tarr>
    std::string fms()
    {
        std::string ret;
        size_t val = 0;
        size_t offset = 0;
        while(true)
        {
            auto tsub = Ffinds::find_sub(_str,strb(),stre(),offset)
            auto tnum = Ffm_base::to_num(_str,tsub);
            if(std::get<0>(tnum))
            {
                ret += Ffinds::copy_str(_str,offset,std::get<1>(tsub));

                size_t index = std::get<1>(tnum);
                if(index < _vec.size()) { ret += _vec[index]; }
                else { ret += Ffinds::copy_str(_str,std::get<1>(tsub),std::get<2>(tsub) + stre().size()); }

                offset = std::get<2>(tnum);
            }
            else { break; }
        }
        return ret;
    }


    std::string _str;               //
    std::vector<std::string> _vec;  //
};

/*
    std::string _str;
    std::vector<std::string> _vec;

    sformat(const std::string &str) : _str(str){}

    //== 字符串转换函数 ==
    template <class T>
    inline std::string to_string(T && val)
    { return std::to_string(std::forward<T>(val)); }

    inline std::string to_string(const char *val)
    { return val; }

    inline std::string to_string(const std::string &val)
    { return val; }

    inline std::string to_string(double val)
    {
        std::ostringstream os;
        os<<std::setprecision(10)<<std::noshowpoint<<val;
        return os.str();
    }
    //== 字符串转换函数 ==



    //== 处理格式化字符 ==
    template<class ...Tarr>
    std::string sformat_t()
    {
        int val = -1;
        int end = 0;
        while(true)
        {
            std::tuple<bool,int,int> a = find_flg(_str,end);
            int flg_begin = std::get<1>(a);
            int flg_end = std::get<2>(a);

            if(std::get<0>(a))
            {
                if(to_num(val,_str,flg_begin,flg_end))
                {
                    try{
                        _str = replace_string(_str,_vec.at(val),flg_begin,flg_end);
                    }
                    catch(...) { }
                }
                end = flg_end;
            }
            else break;
        }
        return _str;
    }

    template<class T,class ...Tarr>
    std::string sformat_t(T && val,const Tarr &...arg)
    {
        _vec.push_back(to_string(std::forward<T>(val)));
        return sformat_t(arg...);
    }

    template<class ...Tarr>
    std::string operator()(const Tarr &...arg)
    { return sformat_t(arg...); }
    //== 处理格式化字符 ==



    //!
    //! 功能：发现长字符串中标记的下标范围
    //!
    //! std::tuple<bool,int,int> :
    //!     [1:bool]    : 是否查到"{}" 标记,
    //!     [2:int]     : "{" 前标记的下标
    //!     [3:int]     : "}" 后标记的下标
    //!
    //! str      : 传入带标记的字符串
    //! in_begin : 从str的下标开始遍历
    //!
    std::tuple<bool,int,int> find_flg(const std::string &str,int in_begin = 0)
    {
        bool ret = false;
        int begin = -1;
        int end = -1;
        for(int i=in_begin;i<str.size();i++)
        {
            if(str[i] == '{') begin = i;
            else if(str[i] == '}' && begin != -1)
            {
                end = i;
                ret = true;
                break;
            }
        }
        return std::make_tuple(ret,begin,end);
    }

    //!
    //! 功能：从长字符串中定位，并返回标记数字
    //!
    //! val     : 返回字符串 "{x}" ,x的值
    //! str     : 传入带标记的字符串
    //! begin   : 传入 "{x}" 的字符串，"{"的前下标
    //! end     : 传入 "{x}" 的字符串，"}"的后下标
    //!
    bool to_num(int &val,const std::string &str,int begin,int end)
    {
        bool ret = false;
        std::string s(str.begin()+begin+1,str.begin()+end);

        try {
            val = std::stoi(s);
            ret = true;
        }
        catch(...) {}
        return ret;
    }

    //!
    //! 功能：传入长字串和拼接字符串，返回新拼接的字符串，需要传入拼接覆盖范围
    //!
    string replace_string(const std::string &str,const std::string &flg,int begin,int end)
    {
        string str_front(str.begin(),str.begin()+begin);
        string str_after(str.begin()+end+1,str.end());
        return str_front + flg + str_after;
    }
    
    */


// 
struct Fffm
{
    Fffm() {}
    ~Fffm() {}
};


} // bhtools


#endif // FFM_H
