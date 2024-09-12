
#ifndef FSTM_H
#define FSTM_H

// #include <iostream>
#include <string>
#include <algorithm>

#include "Tbase.h"
#include "Tlog.h"

namespace bhtools {


// 
struct Fstm
{
    Fstm(const std::string &str) : _str(str) {}

    // 
    template<class ...Tarr>  
    inline std::string section(){ return _str; }

    //
    template<class ...Tarr>
    inline std::string section(const std::string &sf,int ib,int ie,const Tarr &...arg)
    {
        if(_str == "") { return ""; }

        if(ib >= 0 && ie >= 0) 
        { 
            // 全整数切割-对比差值
            size_t ipb = find_part(_str,sf,ib);
            size_t ipe = find_part(_str,sf,ie,true);
            if(ipe > ipb) { _str = _str.substr(ipb,ipe - ipb); }
            else { _str = ""; }
        }
        else if(ib < 0 && ie < 0) 
        {
            // 负数切割-转成整数后反向查找-矫正反向下标后切割
            ib = revise_reverse_index(ib);
            ie = revise_reverse_index(ie);
            size_t ipb = find_part(_str,sf,ib,false,true);
            size_t ipe = find_part(_str,sf,ie,true,true);
            if(_str.size() >= ipe && ipe > ipb) { _str = _str.substr(_str.size() - ipe,ipe - ipb); }
            else { _str = ""; }
        }
        else if(ib < 0) 
        { 
            // 前负数切割-从矫正的前下标开始-获取前后下标的差值
            ib = revise_reverse_index(ib);
            size_t ipb = find_part(_str,sf,ib,true,true);
            size_t ipe = find_part(_str,sf,ie,true);
            if((_str.size() >= ipb) && (ipe > (_str.size() - ipb))) 
            { _str = _str.substr(_str.size() - ipb, ipe - (_str.size() - ipb)); }
            else { _str = ""; }
        }
        else if(ie < 0) 
        { 
            // 后负数切割-从前下标开始-对比矫正的后下标差值进行切割
            ie = revise_reverse_index(ie);
            size_t ipb = find_part(_str,sf,ib,false);
            size_t ipe = find_part(_str,sf,ie,false,true);
            if(_str.size() > ipe) { _str = _str.substr(ipb,_str.size() - ipe); }
            else { _str = ""; }
        }

        return section(arg...);
    }

    // 
    template<class ...Tarr>
    inline std::string operator()(const Tarr &...arg)
    {   return section(arg...); }

    //
    inline static int revise_reverse_index(int index)
    {
        index *= -1;
        index -= 1;
        return index;
    }

    //
    inline static size_t find_part(std::string str,const std::string &sub,size_t part,bool back = false,bool reverse = false)
    {
        if(str == "" || str.size() <= sub.size()) { return 0; }
        if(reverse) { std::reverse(str.begin(),str.end()); }
        if(back) { part += 1; }

        bool over = false;
        size_t index = 0;
        for(size_t i=0;i<part;i++)
        {
            if(over) { return 0; }
            auto btup = Ffinds::find_sub(str,sub,index);
            if(std::get<0>(btup))
            {
                index = std::get<1>(btup);
                index += sub.size();
            }
            else { index = str.size(); over = true; }
        }
        if(back && over == false && index != 0) { index -= sub.size(); }
        return index;
    }

    // 
    inline static std::string section_forward(std::string str,const std::string &sub,int ib,int ie,bool reverse = false)
    {
        if(str == "" || ib > ie) { return ""; }
        if(reverse) { std::reverse(str.begin(),str.end()); } 

        size_t secb = 0;
        size_t sece = 0;
        for(int i=0;i<ib;i++)
        {
            auto btup = Ffinds::find_sub(str,sub,secb);
            if(std::get<0>(btup))
            {
                secb = std::get<1>(btup);
                secb += sub.size();
            }
            else { return ""; }
        }
        sece = secb;

        bool over = false;
        for(int i=ib;i<=ie;i++)
        {
            if(sece == str.size()) { sece = 0; break; }

            auto btup = Ffinds::find_sub(str,sub,sece);
            if(std::get<0>(btup))
            {
                sece = std::get<1>(btup);
                sece += sub.size();
            }
            else { sece = str.size(); over = true; }
        }
        if(sece != 0 && over == false) { sece -= sub.size(); }
        if(sece > secb) 
        { 
            str = str.substr(secb,sece - secb); 
            if(reverse) { std::reverse(str.begin(),str.end()); } 
            return str; 
        }
        return "";
    }

    std::string _str;   // 存储需切割字符-处理结束时返回的结果
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
