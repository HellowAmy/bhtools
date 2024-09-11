
#ifndef FSTM_H
#define FSTM_H

// #include <iostream>
#include <string>

namespace bhtools {


// 
struct Fstm
{
    Fstm(const std::string &str) : _str(str) {}


    template<class ...Tarr> std::string section(){ return _str; }
    template<class ...Tarr>
    std::string section(const std::string &sf,int ib,int ie,const Tarr &...arg)
    {
        if((ib < 0) && (ie < 0)) _str = section_forward(_str,flg,begin,end);
        else _str = section_back(_str,flg,begin,end);
        return section(arg...);
    }

    std::string section_forward(const std::string &sf,int ib,int ie)
    {
        return "";
    }

    std::string section_back(const std::string &sf,int ib,int ie)
    {
        return "";
    }

    std::string _str;
};

/*

struct stm
{
    std::string v_str;
    stm(const std::string &str) : v_str(str){}

    template<class ...Tarr> std::string split_t(){ return v_str; }
    template<class ...Tarr>
    std::string split_t(const std::string &flg,int begin,int end,const Tarr &...arg)
    {
        if((begin < 0) && (end < 0)) v_str = split_back(v_str,flg,begin,end);
        else v_str = split_go(v_str,flg,begin,end);
        return split_t(arg...);
    }

    template<class ...Tarr>
    std::string operator()(const Tarr &...arg) { return split_t(arg...); }

    //反向切割:反向参数传递
    std::string split_back(const std::string &str,const std::string &flg, int end,int begin)
    {
        begin *= -1; begin -= 1; end *= -1;
        int len = end - begin;
        if((begin < 0) || (len <= 0)) return "";

        size_t pos_begin = str.size();
        for(int i=0;i<begin;i++)
        {
            if((pos_begin = str.rfind(flg,pos_begin)) == str.npos) return "";
            pos_begin -= 1;
        }

        size_t pos_end = pos_begin;
        for(int i=0;i<len;i++)
        {
            if((pos_end = str.rfind(flg,pos_end)) == str.npos) return "";
            pos_end -= 1;
        }

        if(pos_begin != str.size()) pos_begin += 1;
        pos_end += flg.size() +1;

        if(pos_begin <= pos_end) return "";
        return std::string (str.begin()+pos_end,str.begin()+pos_begin);
    }

    //正向切割:正向参数传递
    std::string split_go(const std::string &str,const std::string &flg, int begin,int end)
    {
        int len = (end - begin) + 1;
        if((begin < 0) || (len <= 0)) return "";

        size_t pos_begin = 0;
        for(int i=0;i<begin;i++)
        {
            if((pos_begin = str.find(flg,pos_begin)) == str.npos) return "";
            pos_begin += flg.size();
        }

        size_t pos_end = pos_begin;
        for(int i=0;i<len;i++)
        {
            if((pos_end = str.find(flg,pos_end)) == str.npos) return "";
            pos_end += flg.size();
        }

        pos_end -= flg.size();
        if(pos_begin >= pos_end) return "";
        return std::string(str.begin()+pos_begin,str.begin()+pos_end);
    }
};


*/

} // bhtools

#endif // FSTM_H
