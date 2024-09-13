

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>
#include <string.h>

#include "Tlog.h"
#include "Tbyte.h"
#include "Ftest.h"

using namespace bhtools;


void test_1()
{   
    int i = 3855;
    int b = Tendian::swap_endian(i);
    int c = Tendian::to_host(i);
    int d = Tendian::to_net(i);

    vlogd($(i) $(b) $(c) $(d));
}

void test_2()
{
    {
        int i = 255;
        auto s1 = Tbyte::b2_s2(i);
        vlogd($(s1));
    }
    {
        int i = 15;
        auto s1 = Tbyte::b2_s2(i);
        vlogd($(s1));
    }
    {
        int i = -1;
        auto s1 = Tbyte::b2_s2(i);
        vlogd($(s1));
    }
    {
        int i = 0;
        auto s1 = Tbyte::b2_s2(i);
        vlogd($(s1));
    }
    {
        int i = 1023;
        auto s1 = Tbyte::b2_s2_true(i);
        vlogd($(s1));
    }
    {
        int i = 1023;
        auto s1 = Tbyte::b2_s2(i);
        vlogd($(s1));
    }
}

void test_3()
{
    {
        auto s1 = Tbyte::calc_exp(2,0);
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::calc_exp(2,1);
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::calc_exp(2,2);
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::calc_exp(2,3);
        vlogd($(s1));
    }

    {
        int i = 1023;
        auto s1 = Tbyte::b2_s10(i);
        vlogd($(s1));
    }
    {
        char buf[4];
        memset(&buf,0x00,sizeof(buf));
        buf[3] = 0xff;
        int i = *(int*)buf;

        auto s1 = Tbyte::b2_s10(i);
        auto s2 = Tbyte::b2_s2_true(i);
        vlogd($(s1) $(s2));

    }
    {
        int i = 1023;
        auto s1 = Tbyte::b2_s8(i);
        vlogd($(s1));
    }
    {
        int i = 15;
        auto s1 = Tbyte::b2_s8(i);
        vlogd($(s1));
    }
    {
        int i = 255;
        auto s1 = Tbyte::b2_s16(i);
        vlogd($(s1));
    }
    {
        int i = 61695;
        auto s1 = Tbyte::b2_s16(i);
        vlogd($(s1));
    }
    {
        char buf[4];
        memset(&buf,0x00,sizeof(buf));
        buf[3] = 0xff;
        int i = *(int*)buf;
        auto s1 = Tbyte::b2_s16(i);
        vlogd($(s1) $(i));

        i = 255;
        auto s2 = Tbyte::b2_s16(i);
        vlogd($(s2) $(i));

    }
}

void test_4()
{
    {
        auto s1 = Tbyte::num_hex(0);
        auto s2 = Tbyte::num_hex(1);
        auto s3 = Tbyte::num_hex(15);
        auto s4 = Tbyte::num_hex(16);
        BHTEST_EQUAL(s1,'0');
        BHTEST_EQUAL(s2,'1');
        BHTEST_EQUAL(s3,'f');
        BHTEST_EQUAL(s4,'0');
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::is_hex_digit('0');
        auto s2 = Tbyte::is_hex_digit('1');
        auto s3 = Tbyte::is_hex_digit('9');
        auto s4 = Tbyte::is_hex_digit('a');
        BHTEST_EQUAL(s1,true);
        BHTEST_EQUAL(s2,true);
        BHTEST_EQUAL(s3,true);
        BHTEST_EQUAL(s4,false);
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::is_hex_little('2');
        auto s2 = Tbyte::is_hex_little('a');
        auto s3 = Tbyte::is_hex_little('b');
        auto s4 = Tbyte::is_hex_little('A');
        BHTEST_EQUAL(s1,false);
        BHTEST_EQUAL(s2,true);
        BHTEST_EQUAL(s3,true);
        BHTEST_EQUAL(s4,false);
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::is_hex_big('2');
        auto s2 = Tbyte::is_hex_big('a');
        auto s3 = Tbyte::is_hex_big('b');
        auto s4 = Tbyte::is_hex_big('A');
        BHTEST_EQUAL(s1,false);
        BHTEST_EQUAL(s2,false);
        BHTEST_EQUAL(s3,false);
        BHTEST_EQUAL(s4,true);
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::is_hex_range('2');
        auto s2 = Tbyte::is_hex_range('a');
        auto s3 = Tbyte::is_hex_range('z');
        auto s4 = Tbyte::is_hex_range('A');
        BHTEST_EQUAL(s1,true);
        BHTEST_EQUAL(s2,true);
        BHTEST_EQUAL(s3,false);
        BHTEST_EQUAL(s4,true);
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::to_upper('a');
        auto s2 = Tbyte::to_upper('b');
        auto s3 = Tbyte::to_upper('A');
        auto s4 = Tbyte::to_upper('1');
        BHTEST_EQUAL(s1,'A');
        BHTEST_EQUAL(s2,'B');
        BHTEST_EQUAL(s3,'A');
        BHTEST_EQUAL(s4,'1');
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::to_lower('a');
        auto s2 = Tbyte::to_lower('b');
        auto s3 = Tbyte::to_lower('A');
        auto s4 = Tbyte::to_lower('1');
        BHTEST_EQUAL(s1,'a');
        BHTEST_EQUAL(s2,'b');
        BHTEST_EQUAL(s3,'a');
        BHTEST_EQUAL(s4,'1');
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::to_upper("abcABC123");
        auto s2 = Tbyte::to_upper("123");
        auto s3 = Tbyte::to_upper("QWER");
        auto s4 = Tbyte::to_upper("qwer");
        BHTEST_EQUAL(s1,"ABCABC123");
        BHTEST_EQUAL(s2,"123");
        BHTEST_EQUAL(s3,"QWER");
        BHTEST_EQUAL(s4,"QWER");
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
    {
        auto s1 = Tbyte::to_lower("abcABC123");
        auto s2 = Tbyte::to_lower("123");
        auto s3 = Tbyte::to_lower("QWER");
        auto s4 = Tbyte::to_lower("qwer");
        BHTEST_EQUAL(s1,"abcabc123");
        BHTEST_EQUAL(s2,"123");
        BHTEST_EQUAL(s3,"qwer");
        BHTEST_EQUAL(s4,"qwer");
        // vlogd($(s1) $(s2) $(s3) $(s4));
    }
}


void test_5()
{
    {
        std::string s = "11110000000000000000000000001111";
        auto s1 = Tbyte::s2_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "1100000011110000000000000000000000001111";
        auto s1 = Tbyte::s2_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "111100";
        auto s1 = Tbyte::s2_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "00001111";
        auto s1 = Tbyte::s2_b2<char>(s);
        vlogd($(s1));
    }
}

void test_6()
{
    {
        auto s1 = Tbyte::hex_num('0');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('1');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('a');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('b');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('f');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('z');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('A');
        vlogd($(s1));
    }    
    {
        auto s1 = Tbyte::hex_num('B');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('F');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::hex_num('Z');
        vlogd($(s1));
    }

    {
        auto s1 = Tbyte::char_hex('1');
        vlogd($C(s1));
    }
    {
        auto s1 = Tbyte::char_hex('2');
        vlogd($C(s1));
    }
    {
        auto s1 = Tbyte::char_hex('a');
        vlogd($C(s1));
    }
    {
        auto s1 = Tbyte::char_hex('f');
        vlogd($C(s1));
    }
    {
        auto s1 = Tbyte::char_hex('z');
        vlogd($C(s1));
    } 
}

void test_7()
{
    {
        auto s1 = Tbyte::oct_num('0');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::oct_num('1');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::oct_num('7');
        vlogd($(s1));
    }
    {
        auto s1 = Tbyte::oct_num('8');
        vlogd($(s1));
    }

    {
        auto s1 = Tbyte::char_oct('1');
        vlogd($C(s1));
    }
    {
        auto s1 = Tbyte::char_oct('2');
        vlogd($C(s1));
    }
    {
        auto s1 = Tbyte::char_oct('7');
        vlogd($C(s1));
    }
    {
        auto s1 = Tbyte::char_oct('8');
        vlogd($C(s1));
    }

}


void test_8()
{
    {
        std::string s = "777";
        auto s1 = Tbyte::s8_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "77";
        auto s1 = Tbyte::s8_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "37777777777";
        auto s1 = Tbyte::s8_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "77777777777";
        auto s1 = Tbyte::s8_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "00000077777777777";
        auto s1 = Tbyte::s8_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "00000077777777000";
        auto s1 = Tbyte::s8_b2<int>(s);
        vlogd($(s1));
    }

    {
        std::string s = "f";
        auto s1 = Tbyte::s16_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "ffff";
        auto s1 = Tbyte::s16_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "ff";
        auto s1 = Tbyte::s16_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "ffffffff";
        auto s1 = Tbyte::s16_b2<int>(s);
        vlogd($(s1));
    }

    {
        std::string s = "123";
        auto s1 = Tbyte::s10_b2<int>(s);
        vlogd($(s1));
    }
    {
        std::string s = "456";
        auto s1 = Tbyte::s10_b2<int>(s);
        vlogd($(s1));
    }

}


int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();
    // test_7();
    test_8();

    return 0;
}