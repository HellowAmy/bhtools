
#ifndef FTIME_H
#define FTIME_H

#include <chrono>
#include <vector>
#include <string>


namespace bhtools {


// 用于记录线性流逝的时间点
struct Ftimel
{
    typedef std::chrono::nanoseconds nanoseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    typedef std::chrono::steady_clock steady_clock;
    typedef typename std::chrono::time_point<std::chrono::steady_clock,std::chrono::nanoseconds> time_point;

    // 自定义格式
    struct data
    {
        size_t nan;
        size_t mic;
        size_t mil;
        size_t sec;
    };

    // 启动时开始计时
    Ftimel() { update(); }

    // 获取从开始时的时间间隔
    inline nanoseconds time_interval()
    { return steady_clock::now() - _begin; }

    // 转自定义格式
    inline data to_data(const nanoseconds &loss)
    {
        data ret;
        ret.nan = loss.count();
        ret.mic = std::chrono::duration_cast<microseconds>(loss).count();
        ret.mil = std::chrono::duration_cast<milliseconds>(loss).count();
        ret.sec = std::chrono::duration_cast<seconds>(loss).count();
        return ret;
    }

    // 转字符显示
    inline std::string to_string(const nanoseconds &loss)
    {
        //顺序 [纳秒|微秒|毫秒|秒]
        data d = to_data(loss);
        std::string str =
                "[nan: " + std::to_string(d.nan) +
                "|mic: " + std::to_string(d.mic) +
                "|mil: " + std::to_string(d.mil) +
                "|sec: " + std::to_string(d.sec) +
                "]";
        return str;
    }

    // 获取当前时间显示
    inline std::string to_string()
    { return to_string(time_interval()); }

    // 刷新开始时间
    inline void update() { _begin = steady_clock::now(); }

    // 加入时间点-用于多点记录时一起打印-可选择清空容器-可选择重置时间
    inline void push_point(const std::string &tips = "",bool reset = false,bool now = false) 
    { 
        if(reset) { _vec.clear(); }
        if(now) { update(); }
        _vec.push_back(tips +" "+ to_string());
    }

    // 获取加入时间点-可选择清空容器
    inline std::vector<std::string> check_vec() 
    { return _vec; }

    time_point _begin;              //用于计算上一个时间点
    std::vector<std::string> _vec;  //多点打印记录
};

//
//
//
//

//
struct Ftimes
{

    Ftimes() {}
    ~Ftimes() {}
};


} // bhtools




/*

class ctimel
{
public:
    ctimel() { _pass = steady_clock::now(); _begin = _pass; }
    ~ctimel() { nanoseconds loss = steady_clock::now() - _pass; show_point(loss); }

    inline nanoseconds to_point()
    {
        nanoseconds loss = steady_clock::now() - _begin;
        return loss;
    }

    inline std::string to_string(const nanoseconds &loss)
    {
        //顺序 [纳秒|微秒|毫秒|秒]
        std::string str =
                "[nan: " + std::to_string(loss.count()) +
                "|mic: " + std::to_string(duration_cast<microseconds>(loss).count()) +
                "|mil: " + std::to_string(duration_cast<milliseconds>(loss).count()) +
                "|sec: " + std::to_string(duration_cast<seconds>(loss).count()) +
                "]";
        return str;
    }

    inline void show_vec()
    {
        for(auto a:_vec)
        { std::cout<<to_string(a)<<std::endl; }
    }

    inline void show_point(const nanoseconds &loss) { std::cout<<to_string(loss)<<std::endl; }
    inline void show() { show_point(to_point()); }
    inline void update() { _begin = steady_clock::now(); }
    inline void add_point() { _vec.push_back(to_point()); }
    inline void add_point_re() { _vec.push_back(to_point()); update(); }

protected:
    time_point<steady_clock,nanoseconds> _begin;    //用于计算上一个时间点
    time_point<steady_clock,nanoseconds> _pass;     //计算生存时间，析构时打印
    std::vector<nanoseconds> _vec;                  //多点打印记录
};


*/



#endif // FTIME_H
