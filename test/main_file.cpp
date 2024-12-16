
#include <iostream>

#include "Tlog.h"
#include "Ftest.h"
#include "Ffile.h"

using namespace bhtools;

void test_1()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/main.cpp";
        bool ret = Ffile::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/main2.cpp";
        bool ret = Ffile::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/ppqq.txt";
        bool ret = Ffile::is_file_type(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/ppqq.txt";
        bool ret = Ffile::is_dir_type(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/ppqq2.txt";
        bool ret = Ffile::remove_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/ppqq.txt";
        std::string f2 = "/home/red/open/github/bhtools/test/ppqq3.txt";
        bool ret = Ffile::copy_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/ppqq3.txt";
        std::string f2 = "/home/red/open/github/bhtools/ppqq4.txt";
        bool ret = Ffile::copy_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/ppqq3.txt";
        std::string f2 = "/home/red/open/github/bhtools/test/ppqq5.txt";
        bool ret = Ffile::copy_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/ppqq5.txt";
        std::string f2 = "/home/red/open/github/bhtools/test/ppqq6.txt";
        bool ret = Ffile::move_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/1国产会议系统软件V3.139(TS-0300GCR-V1.0.3)-itc.zip";
        std::string f2 = "/home/red/open/github/bhtools/test/1itc.zip";
        if(Ffile::is_exist_file(f1))
        {
            bool ret = Ffile::copy_file(f1,f2);
            BHTEST_EQUAL(ret,true);
        }
    }

}

void test_2()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/test";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test2";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/CMakeLists.txt";
        bool ret = Ffile::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/CMakeLists.txt";
        bool ret = Ffile::is_file_type(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test/";
        bool ret = Ffile::is_dir_type(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test2/";
        bool ret = Ffile::is_dir_type(f1);
        BHTEST_EQUAL(ret,false);
    }
}

void test_3()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/test2/";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::make_dir(f1);
            BHTEST_EQUAL(ret,true);
        }
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test3/t1/t2/t3/";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::make_dir(f1);
            BHTEST_EQUAL(ret,true);
        }
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test3/t1/t2/t4/";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::make_dir(f1);
            BHTEST_EQUAL(ret,true);
        }
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test3/t2/t2/t3";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::make_dir(f1);
            BHTEST_EQUAL(ret,true);
        }
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test3/t2/t2/t4";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::make_dir(f1);
            BHTEST_EQUAL(ret,true);
        }
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test6/t5";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::create_dir(f1);
            BHTEST_EQUAL(ret,false);
        }
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test4";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::create_dir(f1);
            BHTEST_EQUAL(ret,true);
        }
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test5";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
        if(ret == false)
        {
            bool ret = Ffile::create_dir(f1);
            BHTEST_EQUAL(ret,true);
        }
    }
}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    test_3();   

    return 0;
}