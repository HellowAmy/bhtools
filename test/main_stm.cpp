

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>

#include "Ftest.h"
#include "Fstm.h"
#include "Tlog.h"
// #include "Tpool.h"
// #include "Ftime.h"

using namespace bhtools;


void test_1()
{
    vlogi($("== 1 =="));
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,0,0);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,1,1);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,2,2);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,3,3);
        BHTEST_EQUAL(s1,"");
    }

    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,0,0);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,1,1);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,2,2);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,3,3);
        BHTEST_EQUAL(s1,"");
    }

    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,0,0);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,1,1);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,2,2);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,3,3);
        BHTEST_EQUAL(s1,"");
    }

    {
        std::string s = "123####456####789";
        std::string sf = "####";
        auto s1 = Fstm::section_forward(s,sf,0,0);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123####456####789";
        std::string sf = "####";
        auto s1 = Fstm::section_forward(s,sf,1,1);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123####456####789";
        std::string sf = "####";
        auto s1 = Fstm::section_forward(s,sf,2,2);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123####456####789";
        std::string sf = "####";
        auto s1 = Fstm::section_forward(s,sf,3,3);
        BHTEST_EQUAL(s1,"");
    }
}

void test_2()
{
    vlogi($("== 2 =="));
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,0,1);
        BHTEST_EQUAL(s1,"123#456");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,0,2);
        BHTEST_EQUAL(s1,"123#456#789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,1,2);
        BHTEST_EQUAL(s1,"456#789");
    }

    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,0,1);
        BHTEST_EQUAL(s1,"123###456");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,0,2);
        BHTEST_EQUAL(s1,"123###456###789");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,1,2);
        BHTEST_EQUAL(s1,"456###789");
    }

    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,0,3);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,0,4);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,1,3);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "123###456###789";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,1,4);
        BHTEST_EQUAL(s1,"");
    }
    
}

void test_3()
{
    vlogi($("== 3 =="));
    {
        std::string s = "#123#456#789#";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,0,0);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "#123#456#789#";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,1,1);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "#123#456#789#";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,2,2);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "#123#456#789#";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,3,3);
        BHTEST_EQUAL(s1,"789");
    }

    {
        std::string s = "#123#456#789#";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,4,4);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "#123#456#789#";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,5,5);
        BHTEST_EQUAL(s1,"");
    }

    {
        std::string s = "###123###456###789###";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,0,0);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "###123###456###789###";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,1,1);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "###123###456###789###";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,3,3);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "###123###456###789###";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,4,4);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "###123###456###789###";
        std::string sf = "###";
        auto s1 = Fstm::section_forward(s,sf,5,5);
        BHTEST_EQUAL(s1,"");
    }
}

void test_4()
{
    vlogi($("== 4 =="));
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,0,0,true);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,1,1,true);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,2,2,true);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm::section_forward(s,sf,3,3,true);
        BHTEST_EQUAL(s1,"");
    }

    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,0,0,true);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,1,1,true);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,2,2,true);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,3,3,true);
        BHTEST_EQUAL(s1,"");
    }

    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,0,2,true);
        BHTEST_EQUAL(s1,"123##456##789");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,0,1,true);
        BHTEST_EQUAL(s1,"456##789");
    }
    {
        std::string s = "123##456##789";
        std::string sf = "##";
        auto s1 = Fstm::section_forward(s,sf,1,2,true);
        BHTEST_EQUAL(s1,"123##456");
    }

}


void test_5()
{
    vlogi($("== 5 =="));
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,0,0);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,1,1);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,2,2);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,3,3);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,0,1);
        BHTEST_EQUAL(s1,"123#456");
    }

    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,0,1);
        BHTEST_EQUAL(s1,"123#456");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,1,2);
        BHTEST_EQUAL(s1,"456#789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,0,2);
        BHTEST_EQUAL(s1,"123#456#789");
    }

    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,0,-1);
        BHTEST_EQUAL(s1,"123#456#789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,0,-2);
        BHTEST_EQUAL(s1,"123#456");
    }

    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-1,-1);
        BHTEST_EQUAL(s1,"789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-2,-2);
        BHTEST_EQUAL(s1,"456");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-3,-3);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-4,-4);
        BHTEST_EQUAL(s1,"");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-1,-2);
        BHTEST_EQUAL(s1,"456#789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-1,-3);
        BHTEST_EQUAL(s1,"123#456#789");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-3,0);
        BHTEST_EQUAL(s1,"123");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-3,1);
        BHTEST_EQUAL(s1,"123#456");
    }
    {
        std::string s = "123#456#789";
        std::string sf = "#";
        auto s1 = Fstm(s)(sf,-2,1);
        BHTEST_EQUAL(s1,"456");
    }


/*
123#456#789 [0 - 2][-3 - -3]
0:0 = 123
1:1 = 456
2:2 = 789
3:3 =  
0:1 = 123#456
1:2 = 456#789
0:2 = 123#456#789

0:-1 = 123#456#789
-1:-1 = 789
-2:-2 = 456
-3:-3 = 123
-1:-2 = 456#789
-1:-3 = 123#456#789
-4:-4 = 

-1:0 = 789123
-3:0 = 123#456#789123
-3:1 = 123#456#789123#456
-3:2 = 123#456#789123#456#789
*/

}


void test_6()
{
    vlogi($("== 6 =="));
    std::string s = "1#23#456#7890";
    std::string sf = "#";

    {
        auto s1 = Fstm::find_part(s,sf,0);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,1);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,2);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,3);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,4);
        vlogd($(s1));

    }
    {
        auto s1 = Fstm::find_part(s,sf,0,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,1,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,2,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,3,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,4,true);
        vlogd($(s1));
    }


    {
        auto s1 = Fstm::find_part(s,sf,0,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,1,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,2,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,3,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,4,true,true);
        vlogd($(s1));
    }
}


void test_7()
{
    vlogi($("== 7 =="));
    std::string s = "1#23#456#7890"; // 13 [0-4] =   9,4  ---- 13 [5-8] = 5,3
    std::string sf = "#";

    {
        auto s1 = Fstm::find_part(s,sf,0,false,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,1,false,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,2,false,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,3,false,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,4,false,true);
        vlogd($(s1));
    }

    {
        auto s1 = Fstm::find_part(s,sf,0,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,1,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,2,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,3,true,true);
        vlogd($(s1));
    }
    {
        auto s1 = Fstm::find_part(s,sf,4,true,true);
        vlogd($(s1));
    }

}


int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    test_5();
    // test_6();
    // test_7();

    return 0;
}