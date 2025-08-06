
#include <iostream>
#include <map>

#include "bhtools.h"

auto fprint = [](std::map<int,int> mp,std::string tips = ""){
    vlogd($(tips));
    for(auto &a:mp)
    {
        std::cout<<"|"<<a.first<<": ";
        for(int i=0;i<a.second;i++)
        {
            std::cout<<"#";
        }
        std::cout<<std::endl;
    }
};

void test_1()
{
    bhtools::Trand_int rd1(-10,10);
    bhtools::Trand_double rd2(-0.2,0.2);
    bhtools::Trand_bool rd3;

    std::map<int,int> mp1;
    std::map<int,int> mp2;
    std::map<int,int> mp3;

    int num = 100;
    for(int i=0;i<num;i++)
    {
        mp1[rd1.value()]++;
    }

    for(int i=0;i<num;i++)
    {
        int index = rd2.value() * 100;
        mp2[index]++;
    }

    for(int i=0;i<num;i++)
    {
        mp3[rd3.value()]++;
    }

    fprint(mp1);
    fprint(mp2);
    fprint(mp3);
}

void test_2()
{
    bhtools::Trand_ndis rd1(50.0,5.0);
    bhtools::Trand_ddis rd2{10,10,40,40,90,90};
    bhtools::Trand_pdis rd3(10);
    bhtools::Trand_gdis rd4(10.0,1.5);

    std::map<int,int> mp1;
    std::map<int,int> mp2;
    std::map<int,int> mp3;
    std::map<int,int> mp4;

    int num = 200;

    for(int i=0;i<num;i++)
    {
        mp1[rd1.value()]++;
    }

    for(int i=0;i<num;i++)
    {
        mp2[rd2.value()]++;
    }

    for(int i=0;i<num;i++)
    {
        mp3[rd3.value()]++;
    }

    for(int i=0;i<num;i++)
    {
        mp4[rd4.value()]++;
    }

    fprint(mp1,"mp1");
    fprint(mp2,"mp2");
    fprint(mp3,"mp3");
    fprint(mp4,"mp4");
}


int main(int argc, char *argv[])
{
    test_1();   
    test_2();   

    return 0;
}