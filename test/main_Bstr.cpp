#include <iostream>

#include "Bstr.h"
#include "Bstrvi.h"

#include "Ftest.h"

void test_1()
{
    char cs1[] = "hello world 1";
    bh::cchp cs2 = "hello world 2";
    bh::dstr cs3 = "hello world 3";
    bh::cstr cs4 = "hello world 4";

    bh::Bstr s1(cs1);
    bh::Bstr s2(cs2);
    bh::Bstr s3(cs3);
    bh::Bstr s4(cs4);
    bh::Bstr s5(s4);
    bh::Bstr s6 = s5;
    bh::Bstr s7 = "hello world 5";
    bh::Bstr s8("hello world 6");

    vloga("赋值字符串");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
    vlogd($(s5));
    vlogd($(s6));
    vlogd($(s7));
    vlogd($(s8));

    bh::Bstrvi v1(cs1);
    bh::Bstrvi v2(cs1);
    bh::Bstrvi v3(cs1, 0, 5);
    bh::Bstrvi v4(cs1, 0, 5);

    bh::Bstr sv1(v1);
    bh::Bstr sv2 = v3;

    bool ok1 = (sv1 == cs1);
    bool ok2 = (sv1 == cs2);
    bool ok3 = (sv1 == cs3);
    bool ok4 = (sv1 == cs4);
    bool ok5 = (sv1 == sv2);
    bool ok6 = (sv1 == v1);
    bool ok7 = (sv2 == v3);

    vloga("赋值视图");
    vlogd($(v1));
    vlogd($(v2));
    vlogd($(v3));
    vlogd($(v4));
    vlogd($(sv1));
    vlogd($(sv2));

    vloga("相等比较");
    BHTEST_EQUAL(ok1, true);
    BHTEST_EQUAL(ok2, false);
    BHTEST_EQUAL(ok3, false);
    BHTEST_EQUAL(ok4, false);
    BHTEST_EQUAL(ok5, false);
    BHTEST_EQUAL(ok6, true);
    BHTEST_EQUAL(ok7, true);
}

void test_2()
{
    char cs1[] = "hello world 1";
    bh::cchp cs2 = "hello world 2";
    bh::dstr cs3 = "hello world 3";
    bh::cstr cs4 = "hello world 4";

    bh::Bstr s1(cs1);
    bh::Bstr s2;

    s1 += " ";
    s1 += cs2;
    s1 += " ";
    s1 += cs3;
    s1 += " ";
    s1 += cs4;

    s2.append("[ ").append(cs2).append(" ]");

    vloga("字符追加");
    vlogd($(cs1));
    vlogd($(cs2));
    vlogd($(cs3));
    vlogd($(cs4));
    vlogd($(s1));
    vlogd($(s2));

    bh::Bstr s3;
    s3 << "[ " << "hello" << " ] ";
    s3 << s2;
    s3 << ' ';
    s3 << '0';
    s3 << 'x';

    vloga("推入字符");
    vlogd($(s3));
}

void test_3()
{
    bh::Bstr s1 = "12345678901234567890";
    bh::Bstr s2 = "hello world";
    bh::Bstrvi sv1(s2, 0, 5);
    bh::Bstrvi sv2(s2);

    bool ok1 = s1.is_contain("hello");
    bool ok2 = s2.is_contain("hello");
    bool ok3 = s2.compare_view(sv1);
    bool ok4 = s2.compare_view(sv2);

    vloga("查找功能");
    BHTEST_EQUAL(ok1, false);
    BHTEST_EQUAL(ok2, true);

    vloga("视图对比");
    BHTEST_EQUAL(ok3, false);
    BHTEST_EQUAL(ok4, true);

    vloga("查找位置");
    bh::Bstr::range rg;
    while(true) {
        rg = s1.find_range("456", rg.epos);
        if(!rg) {
            break;
        }
        vlogd($(rg.bpos) $(rg.epos));
    }
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    test_3();

    return 0;
}