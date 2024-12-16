
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
        std::string f1 = "/home/red/open/github/bhtools/test";
        bool ret = Ffile::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/main2.cpp";
        bool ret = Ffile::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test2";
        bool ret = Ffile::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/main.cpp";
        bool ret = Ffile::is_file_type(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test";
        bool ret = Ffile::is_dir_type(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "../main.cpp";
        bool ret = Ffile::is_file_type(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../test";
        bool ret = Ffile::is_dir_type(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "../main.cpp";
        bool ret = Ffile::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../test";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/test";
        bool ret = Ffile::is_file_type(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/main.cpp";
        bool ret = Ffile::is_dir_type(f1);
        BHTEST_EQUAL(ret,false);
    }

}

void test_2()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/build";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file";
        bool ret = Ffile::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file2";
        bool ret = Ffile::create_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/level1/level1_0";
        bool ret = Ffile::create_dir(f1);
        BHTEST_EQUAL(ret,false);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/level1/level1_1";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/level1/level1_2";
        std::string f3 = "/home/red/open/github/bhtools/build/test_file/level1/level1_3";
        bool ret1 = Ffile::make_dir(f1);
        bool ret2 = Ffile::make_dir(f2);
        bool ret3 = Ffile::make_dir(f3);
        BHTEST_EQUAL(ret1,true);
        BHTEST_EQUAL(ret2,true);
        BHTEST_EQUAL(ret3,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/CMakeLists.txt";
        std::string f2 = "/home/red/open/github/bhtools/CMakeLists2.txt";
        bool ret = Ffile::copy_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/CMakeLists2.txt";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/CMakeLists.txt";
        bool ret = Ffile::move_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists.txt";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/CMakeLists2.txt";
        std::string f3 = "/home/red/open/github/bhtools/build/test_file/CMakeLists3.txt";
        std::string f4 = "/home/red/open/github/bhtools/build/test_file/CMakeLists4.txt";
        std::string f5 = "/home/red/open/github/bhtools/build/test_file/CMakeLists5.txt";
        bool ret1 = Ffile::copy_file(f1,f2);
        bool ret2 = Ffile::copy_file(f1,f3);
        bool ret3 = Ffile::copy_file(f1,f4);
        bool ret4 = Ffile::copy_file(f1,f5);
        BHTEST_EQUAL(ret1,true);
        BHTEST_EQUAL(ret2,true);
        BHTEST_EQUAL(ret3,true);
        BHTEST_EQUAL(ret4,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists3.txt";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/CMakeLists33.txt";
        bool ret = Ffile::move_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists4.txt";
        bool ret = Ffile::remove_file(f1);
        BHTEST_EQUAL(ret,true);
    }
}

void test_3()
{
    {
        auto vec = Ffile::get_files("/home/red/open/github/bhtools/build/test_file");
        vlogd($C(vec));
    }
    {
        auto vec = Ffile::get_dirs("/home/red/open/github/bhtools/build/test_file");
        vlogd($C(vec));
    }
    {
        auto vec = Ffile::get_files("/home/red/open/github/bhtools/build/test_file",false);
        vlogd($C(vec));
    }
    {
        auto vec = Ffile::get_dirs("/home/red/open/github/bhtools/build/test_file",false);
        vlogd($C(vec));
    }
}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    test_3();   

    return 0;
}