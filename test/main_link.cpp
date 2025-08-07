
#include <iostream>

#include "bhtools.h"

void test_1()
{
    bhtools::Tmlink<int> m1(12);
    m1.set_change_cb([](int val,bool self){
        vlogi($("m") $(val) $(self));
    });

    bhtools::Tvlink<bhtools::Tmlink,int> v1(m1);
    v1.set_change_cb([](int val,bool self){
        vlogw($("v1") $(val) $(self));
    });

    bhtools::Tvlink<bhtools::Tmlink,int> v2(m1);
    v2.set_change_cb([](int val,bool self){
        vlogw($("v2") $(val) $(self));
    });

    
    m1.set_data(44);
    vlogd($(m1.data()) $(v1.data()) $(v2.data()));

    v1.set_data(66);
    vlogd($(m1.data()) $(v1.data()) $(v2.data()));

    v2.set_data(77);
    vlogd($(m1.data()) $(v1.data()) $(v2.data()));


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