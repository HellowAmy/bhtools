
#ifndef TBASE_H
#define TBASE_H

#include <string>
#include <type_traits>
#include <sstream>

namespace bhtools {


// 各类型转字符串函数
template<typename T>
inline static std::string Tto_string(const T &val) 
{ return std::to_string(val); }

inline static std::string Tto_string(const char *val) 
{ return val; }

inline static std::string Tto_string(const std::string &val) 
{ return val; }

template<typename T>
inline static std::string Tto_string(T* val) 
{ std::stringstream ss; ss<<val; return ss.str(); }

inline static std::string Tto_string(void *val) 
{ std::stringstream ss; ss<<val; return ss.str(); }

//
//
//
//

// 字符串转各类型
template<typename T>
bool Tfrom_string(const std::string &str,T &ret)
{
    bool suc = true;
    try {
        if(std::is_same<T,double>::value) { ret = std::stod(str); }
        else if(std::is_same<T,float>::value) { ret = std::stof(str); }
        if(std::is_same<T,int>::value || std::is_same<T,unsigned int>::value)
        { ret = std::stoi(str); }
        else if(std::is_same<T,long>::value || std::is_same<T,unsigned long>::value)
        { ret = std::stol(str); }
        else if(std::is_same<T,long long>::value || std::is_same<T,unsigned long long>::value)
        { ret = std::stoll(str); }
        else { suc = false; }
    } catch(...) { suc = false; }
    return suc;
}

template<typename T>
T Tfrom_string(const std::string &str)
{ T ret; std::istringstream ss(str); ss>>ret; return ret; }




} // bhtools


#endif // TBASE_H
