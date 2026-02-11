
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "Ffm.h"
#include "Ftest.h"

void test_1()
{
    // 多参数格式化
    {
        std::string s = "{0}{1}{2}";
        int a = 100;
        double b = 3.145;
        std::string c = "hellow";
        auto s1 = bhtools::Fsfm(s)(a,b,c);
        auto s2 = bhtools::Fsfm("{0}{1}{2}")(100,3.145,"hellow");
        vlogd($(s1) $(s1));
    }
    {
        auto s1 = bhtools::Fsfm("#{0}#{1}#{2}#")(123);
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fsfm("#{0}#{1}#{2}#")(123,456,789);
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fsfm("{0}##{1}##{2}")(123,456,789);
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fsfm("{0}{1}{2}#")(123,456,789);
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fsfm("####")(123,456,789);
        vlogd($(s1));
    }

    // 无序格式化
    {
        auto s1 = bhtools::Fsfm("={2}={1}={0}")(100,3.145,"hellow");
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fsfm("={1}={1}={1}")(100,3.145,"hellow");
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fsfm("={2}={0}={1}")(100,3.145,"hellow");
        vlogd($(s1));
    }
}


void test_2()
{
    // 快速格式化
    {
        auto s1 = bhtools::Fffm("{}{}{}")(100,3.145,"hellow");
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fffm("{}={}={}")(100,3.145,"hellow");
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fffm("#{}={}={}#")(100,3.145,"hellow");
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fffm("###{}={}={}###")(100,3.145,"hellow");
        vlogd($(s1));
    }
    {
        auto s1 = bhtools::Fffm("######")(100,3.145,"hellow");
        vlogd($(s1));
    }
}

void test_3()
{
    // 性能测试
    int sum = 1000 * 10000;
    bhtools::Ftimel t1;

    for(int i=0;i<sum;i++)
    {
        // auto s1 = bhtools::Fsfm("#{0}={1}={2}#")(100,3.145,"hellow");
    }
    t1.push_point("t1",true);
    
    for(int i=0;i<sum;i++)
    {
        auto str = bhtools::Fffm("#{}-{}#{}-{}#{}-{}#{}-{}#")(true, false, 100, 200, 3.1415, 9.99, "hello",
                                                   "world");

        // auto str = bhtools::Fffm("###{}---{}###{}---{}###{}---{}###{}---{}###")(true, false, 100, 200, 3.1415, 9.99, "hello",
                                                //    "world");
    }
    t1.push_point("t2",true);
    
    char buffer[100] = {0};
    for(int i=0;i<sum;i++)
    {
        memset(buffer,0,sizeof(buffer));
                snprintf(buffer, sizeof(buffer), "#%d-%d#%d-%d#%f-%f#%s-%s#", true, false, 100, 200, 3.1415,
                 9.99, "hello", "world");
    }
    t1.push_point("t3",true);

    vlogd($C(t1.check_vec()));

    /*
        [Deb]<<<< [t1.check_vec(): 
        | size: 3
        | t1 [nan: 14526386315|mic: 14526386|mil: 14526|sec: 14] 
        | t2 [nan: 3705913936|mic: 3705913|mil: 3705|sec: 3] 
        | t3 [nan: 1351624577|mic: 1351624|mil: 1351|sec: 1] 
        ]  >>>>[/home/red/open/github/bhtools/test/main_fm.cpp:112][2025-08-07.24:28:05.813]

        [Deb]<<<< [t1.check_vec(): 
        | size: 3
        | t1 [nan: 5173605|mic: 5173|mil: 5|sec: 0] 
        | t2 [nan: 6500595366|mic: 6500595|mil: 6500|sec: 6] 
        | t3 [nan: 2538978984|mic: 2538978|mil: 2538|sec: 2] 
        ]  >>>>[/home/red/open/github/bhtools/test/main_fm.cpp:112][2026-02-02.16:51:39.554] 

        [Deb]<<<< [t1.check_vec(): 
        | size: 3
        | t1 [nan: 2576872|mic: 2576|mil: 2|sec: 0] 
        | t2 [nan: 7671707095|mic: 7671707|mil: 7671|sec: 7] 
        | t3 [nan: 3005069501|mic: 3005069|mil: 3005|sec: 3] 
        ]  >>>>[/home/red/open/github/bhtools/test/main_fm.cpp:114][2026-02-07.13:52:23.564]
    */
}

void test_4()
{
    // 浮点数格式化,只有Fsfm支持
    auto s1 = bhtools::Fsfm("#{0}={1}={2}#")(100,3.1415267777,"hellow");
    auto s2 = bhtools::Fsfm("#{0}={1:2}={2}#")(100,3.1415267777,"hellow");
    auto s3 = bhtools::Fsfm("#{0}={1:10}={2}#")(100,3.1415267777,"hellow");
    vlogd($(s1) $(s2) $(s3));
}


int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    test_3();   
    // test_4();   

    return 0;
}