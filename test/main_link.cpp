
#include <iostream>

#include "Tlog.h"
#include "Tlink.h"

using namespace bhtools;

void test_1()
{
    vlogw("== test_1 ==");

    auto fn_show = [](Tmlink<int> &m,Tvlink<int,Tmlink> v) {
        vlogw("show: " $(m.data()) $(v.data()));

    };



    Tmlink<int> m1(12);
    m1._fn_data_change = [&](int val,bool self){
        vlogd("modul _fn_data_change: " $(m1.data()) $(val) $(self));

        if(self == false)
        {
            m1.set_nonotify_data(50);
        }
    };

    Tvlink<int,Tmlink> v1(m1);
    v1._fn_data_change = [&](int val,bool self){
        vlogd("view _fn_data_change: " $(v1.data()) $(val) $(self));

        if(self == false)
        {
            v1.set_nonotify_data(150);
        }
        
        if(self)
        {
            // v1.set_data(350);    // 相互通知-死循环
            // v1.set_nonotify_data(450);   // 不通知-正常工作
        }
    };



    fn_show(m1,v1);


    m1.set_data(300);
    fn_show(m1,v1);


    v1.set_data(200);
    fn_show(m1,v1);
    






}

void test_2()
{

}

void test_3()
{

}

int main(int argc, char *argv[])
{
    test_1();   
    // test_2();   
    // test_3();   

    return 0;
}