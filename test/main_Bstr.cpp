#include <iostream>

#include "Bstr.h"

#include "Ftest.h"

void test_1()
{
    bh::Bstr s1("1234567890");
    bh::Bstr s2("1234567890");
    bh::Bstr s3(s2);
    bh::Bstrvi svi(s1);

    s2 += s1;
    s2 += svi;
    s2 += " abc1";
    s2 += bh::dstr(" abc2");
    s2 += bh::cstr(" abc3");
    s2 += bh::Bstr(" abc4");
    s2 += bh::Bstrbc(" abc5");

    vloga("追加结果");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));

    s2 = s1;
    vlogd($(s2));

    s2 = "abc1";
    vlogd($(s2));

    s2 = bh::cstr("abc2");
    vlogd($(s2));

    s2 = bh::dstr("abc3");
    vlogd($(s2));

    bh::cchp ss1 = "abc4";
    s2 = ss1;
    vlogd($(s2));

    bh::dchr ss2[] = "abc5";
    s2 = ss2;
    vlogd($(s2));

    s2 = svi;
    vlogd($(s2));
}

void test_2()
{
    bh::Bstr s1("12345678901234567890");

    vloga("循环查找");
    bh::Bstr::range r1;
    while(true) {
        r1 = s1.find_range("456", r1.epos);
        if(!r1) {
            break;
        }
        vlogd($(r1.bpos) $(r1.epos));
    }
}

void test_3()
{
    bh::dchr cs1[] = "hello world";
    bh::cchp cs2 = "hello world";
    bh::dstr cs3 = "hello world";
    bh::cstr cs4 = "hello world";
    bh::Bstr ss1("hello world");
    bh::Bstrvi vs1(ss1);

    bool ok1 = ss1 == cs1;
    bool ok2 = ss1 == cs2;
    bool ok3 = ss1 == cs3;
    bool ok4 = ss1 == cs4;
    bool ok5 = ss1 == vs1;

    vloga("字符串");
    vlogd($(cs1));
    vlogd($(cs2));
    vlogd($(cs3));
    vlogd($(cs4));
    vlogd($(ss1));
    vlogd($(vs1));

    vloga("相等");
    BHTEST_EQUAL(ok1, true);
    BHTEST_EQUAL(ok2, true);
    BHTEST_EQUAL(ok3, true);
    BHTEST_EQUAL(ok4, true);
    BHTEST_EQUAL(ok5, true);
}

void test_4()
{
    bh::dchr cs1[] = "hello world1";
    bh::cchp cs2 = "hello world2";
    bh::dstr cs3 = "hello world3";
    bh::cstr cs4 = "hello world4";
    bh::Bstr ss1("hello world5");
    bh::Bstrvi vs1(ss1, 0, 5);

    bool ok1 = ss1 == cs1;
    bool ok2 = ss1 == cs2;
    bool ok3 = ss1 == cs3;
    bool ok4 = ss1 == cs4;
    bool ok5 = ss1 == vs1;

    vloga("字符串");
    vlogd($(cs1));
    vlogd($(cs2));
    vlogd($(cs3));
    vlogd($(cs4));
    vlogd($(ss1));
    vlogd($(vs1));

    vloga("不相等");
    BHTEST_EQUAL(ok1, false);
    BHTEST_EQUAL(ok2, false);
    BHTEST_EQUAL(ok3, false);
    BHTEST_EQUAL(ok4, false);
    BHTEST_EQUAL(ok5, false);
}

void test_5()
{
    bh::Bstr s1("1234567890");
    bh::Bstrvi svi(s1, 3, 3);

    auto r1 = s1.is_contain("456");
    auto r2 = s1.find_index("456");
    auto r3 = s1.compare_view(svi);

    vloga("基本功能");
    vlogd($(r1));
    vlogd($(r2));
    vlogd($(r3));
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();

    return 0;
}