
#include <iostream>

#include "bhtools.h"


void test_1()
{
    // 多位置组合切割
    std::string ss = "##100##<<abc-hellow world-1992/4/3 15:12:54>>";
    {
        std::string s1 = bhtools::Fstm(ss)("100",0,0);
        std::string s2 = bhtools::Fstm(ss)("100",1,1);
        vlogd($("1") $(s1) $(s2));
    }
    {
        std::string s1 = bhtools::Fstm(ss)("##",1,1,"##",0,0);
        vlogd($("2") $(s1));
    }
    {
        std::string s1 = bhtools::Fstm(ss)(" ",1,1," ",0,0);
        vlogd($("3") $(s1));
    }
    {
        std::string s1 = bhtools::Fstm(ss)(" ",1,1,"-",1,1);
        vlogd($("3") $(s1));
    }

    /*
        [Deb]<<<< ["1": 1] [s1: ##] [s2: ##<<abc-hellow world-1992/4/3 15:12:54>>]  >>>>
        [Deb]<<<< ["2": 2] [s1: 100]  >>>>
        [Deb]<<<< ["3": 3] [s1: world-1992/4/3]  >>>>
        [Deb]<<<< ["3": 3] [s1: 1992/4/3]  >>>>
    */
}


void test_2()
{
    // 分段定位切割
    std::string ss = "##11##22##33##44##55";
    {
        std::string s1 = bhtools::Fstm(ss)("##",0,0);
        std::string s2 = bhtools::Fstm(ss)("##",1,1);
        std::string s3 = bhtools::Fstm(ss)("##",2,2);
        std::string s4 = bhtools::Fstm(ss)("##",3,3);
        std::string s5 = bhtools::Fstm(ss)("##",0,3);
        std::string s6 = bhtools::Fstm(ss)("##",-1,-1);
        std::string s7 = bhtools::Fstm(ss)("##",-1,-2);
        std::string s8 = bhtools::Fstm(ss)("##",-1,-3);
        std::string s9 = bhtools::Fstm(ss)("##",-3,-3);

        vlogd($(s1) $(s2) $(s3) $(s4) $(s5));
        vlogd($(s6) $(s7) $(s8) $(s9));
    }
    {
        std::string s1 = bhtools::Fstm(ss)("##",0,-1);
        std::string s2 = bhtools::Fstm(ss)("##",-1,0);
        vlogd($(s1) $(s2));
    }

    /*
        [Deb]<<<< [s1: ] [s2: 11] [s3: 22] [s4: 33] [s5: ##11##22##33]  >>>>
        [Deb]<<<< [s6: 55] [s7: 44##55] [s8: 33##44##55] [s9: 33]  >>>>
        [Deb]<<<< [s1: ##11##22##33##44##55] [s2: ]  >>>>
    */
}

void test_3()
{
    // 性能测试
    int sum = 1000 * 10000;
    
    std::string ss = "##100##<<abc-hellow world-1992/4/3 15:12:54>>";
    std::string s1 = bhtools::Fstm(ss)("##",2,2," ",1,1,"-",1,1);
    vlogd($(s1));
    
    bhtools::Ftimel t1;
    for(int i=0;i<sum;i++)
    {
        std::string s = bhtools::Fstm(ss)("##",2,2," ",1,1,"-",1,1);
    }
    vlogd($(t1.to_string()));

    /*
        [Deb]<<<< [s1: 1992/4/3]  >>>>
        [Deb]<<<< [t1.to_string(): [nan: 6942064817|mic: 6942064|mil: 6942|sec: 6]]  >>>>
    */
}


int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    test_3();   

    return 0;
}