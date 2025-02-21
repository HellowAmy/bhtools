
#include <iostream>

#include "Tlog.h"
#include "Fargv.h"
#include "Ftest.h"

using namespace bhtools;

void test_1(int argc, char *argv[])
{
    Fargv parse;
    parse.init(argc,argv);
    vlogd($C(parse._vec));
}

void test_2()
{
    {
        Fargv parse;
        parse.init("./main_argv -d path --prefix=path -a -b -c open1 open2 --long open version help -s \"'hellow word'\"");
        vlogd($C(parse._vec));
    }
    {
        Fargv parse;
        parse.init("./main_argv -d path --prefix=path -a -b -c open1 open2 --long open version help -s '\"hellow word\"'");
        vlogd($C(parse._vec));
    }
}

void test_3()
{
    {
        Fargv parse;
        parse.init("./main_argv -d path/file2.png --prefix=path/file.png --log= -a -b -c open1 open2 --long open version help -s \"'hellow word'\" src dst");
        vlogd($C(parse._vec));

        {
            bool ok = parse.is_exist("-d");
            BHTEST_EQUAL(ok,true);
        }
        {
            bool ok = parse.is_exist("-a");
            BHTEST_EQUAL(ok,true);
        }
        {
            bool ok = parse.is_exist("--long");
            BHTEST_EQUAL(ok,true);
        }
        {
            bool ok = parse.is_exist("ooopen");
            BHTEST_EQUAL(ok,false);
        }
        {
            vlogw("");
            std::string str = parse.is_exist_arg("-d");
            BHTEST_EQUAL(str,"path/file2.png");
        }
        {
            std::string str = parse.is_exist_arg("-a");
            BHTEST_EQUAL(str,"");
        }
        {
            vlogw("");
            std::vector<std::string> vec = parse.is_exist_args("-c");
            vlogd($C(vec));
        }
        {
            std::vector<std::string> vec = parse.is_exist_args("--long");
            vlogd($C(vec));
        }
        {
            std::vector<std::string> vec = parse.is_exist_args("-s");
            vlogd($C(vec));
        }
        {
            vlogw("");
            std::string str = parse.is_exist_path("--prefix");
            BHTEST_EQUAL(str,"path/file.png");
        }
        {
            std::string str = parse.is_exist_path("--log");
            BHTEST_EQUAL(str,"");
        }
        {
            vlogw("");
            bool ok = parse.is_exist_sub("-s","-");
            BHTEST_EQUAL(ok,true);
        }
        {
            bool ok = parse.is_exist_sub("ss","-");
            BHTEST_EQUAL(ok,false);
        }
        

    }
}

int main(int argc, char *argv[])
{
    // test_1(argc,argv);   
    // test_2();   
    test_3();   

    return 0;
}
