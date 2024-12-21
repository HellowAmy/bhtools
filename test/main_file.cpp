
#include <iostream>

#include "Tlog.h"
#include "Ftest.h"
#include "Ffile.h"

using namespace bhtools;

void test_1()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/main.cpp";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/main2.cpp";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test2";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/main.cpp";
        bool ret = Ffsys::is_file_type(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/test";
        bool ret = Ffsys::is_dir_type(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "../main.cpp";
        bool ret = Ffsys::is_file_type(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../test";
        bool ret = Ffsys::is_dir_type(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "../main.cpp";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../test";
        bool ret = Ffsys::is_exist_dir(f1);
        BHTEST_EQUAL(ret,true);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/test";
        bool ret = Ffsys::is_file_type(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/main.cpp";
        bool ret = Ffsys::is_dir_type(f1);
        BHTEST_EQUAL(ret,false);
    }

}

void test_2()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/build";
        bool ret = Ffsys::is_exist_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file";
        bool ret = Ffsys::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file2";
        bool ret = Ffsys::create_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/level1/level1_0";
        bool ret = Ffsys::create_dir(f1);
        BHTEST_EQUAL(ret,false);
    }

    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/level1/level1_1";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/level1/level1_2";
        std::string f3 = "/home/red/open/github/bhtools/build/test_file/level1/level1_3";
        bool ret1 = Ffsys::make_dir(f1);
        bool ret2 = Ffsys::make_dir(f2);
        bool ret3 = Ffsys::make_dir(f3);
        BHTEST_EQUAL(ret1,true);
        BHTEST_EQUAL(ret2,true);
        BHTEST_EQUAL(ret3,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/CMakeLists.txt";
        std::string f2 = "/home/red/open/github/bhtools/CMakeLists2.txt";
        bool ret = Ffsys::copy_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/CMakeLists2.txt";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/CMakeLists.txt";
        bool ret = Ffsys::move_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists.txt";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/CMakeLists2.txt";
        std::string f3 = "/home/red/open/github/bhtools/build/test_file/CMakeLists3.txt";
        std::string f4 = "/home/red/open/github/bhtools/build/test_file/CMakeLists4.txt";
        std::string f5 = "/home/red/open/github/bhtools/build/test_file/CMakeLists5.txt";
        bool ret1 = Ffsys::copy_file(f1,f2);
        bool ret2 = Ffsys::copy_file(f1,f3);
        bool ret3 = Ffsys::copy_file(f1,f4);
        bool ret4 = Ffsys::copy_file(f1,f5);
        BHTEST_EQUAL(ret1,true);
        BHTEST_EQUAL(ret2,true);
        BHTEST_EQUAL(ret3,true);
        BHTEST_EQUAL(ret4,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists3.txt";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/CMakeLists33.txt";
        bool ret = Ffsys::move_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists4.txt";
        bool ret = Ffsys::remove_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/level1/level1_2/1";
        std::string f2 = "/home/red/open/github/bhtools/build/test_file/level1/level1_2/2";
        std::string f3 = "/home/red/open/github/bhtools/build/test_file/level1/level1_3/CMakeLists1.txt";
        std::string f4 = "/home/red/open/github/bhtools/build/test_file/level1/level1_3/CMakeLists2.txt";
        std::string f5 = "/home/red/open/github/bhtools/build/test_file/level1/level1_3/CMakeLists3.txt";
        std::string f6 = "/home/red/open/github/bhtools/build/test_file/CMakeLists.txt";
        bool ret1 = Ffsys::make_dir(f1);
        bool ret2 = Ffsys::make_dir(f2);
        bool ret3 = Ffsys::copy_file(f6,f3);
        bool ret4 = Ffsys::copy_file(f6,f4);
        bool ret5 = Ffsys::copy_file(f6,f5);
        BHTEST_EQUAL(ret1,true);
        BHTEST_EQUAL(ret2,true);
        BHTEST_EQUAL(ret3,true);
        BHTEST_EQUAL(ret4,true);
        BHTEST_EQUAL(ret5,true);
    }
}

void test_3()
{
    {
        auto vec = Ffsys::get_files("/home/red/open/github/bhtools/build/test_file");
        vlogd($C(vec));
    }
    {
        auto vec = Ffsys::get_dirs("/home/red/open/github/bhtools/build/test_file");
        vlogd($C(vec));
    }
    {
        auto vec = Ffsys::get_files("/home/red/open/github/bhtools/build/test_file",false);
        vlogd($C(vec));
    }
    {
        auto vec = Ffsys::get_dirs("/home/red/open/github/bhtools/build/test_file",false);
        vlogd($C(vec));
    }
    {
        auto tup = Ffsys::get_files_and_dirs("/home/red/open/github/bhtools/build/test_file",true);
        vlogd($C(std::get<0>(tup)) $C(std::get<1>(tup)));
    }
    {
        auto tup = Ffsys::get_files_and_dirs("/home/red/open/github/bhtools/build/test_file",false);
        vlogd($C(std::get<0>(tup)) $C(std::get<1>(tup)));
    }
}

void test_4()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file";
        bool ret = Ffsys::remove_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file2";
        bool ret = Ffsys::remove_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/delete";
        bool ret = Ffsys::remove_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
}

void test_5()
{
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists4.txt";
        std::string ret = Ffsys::get_suffix(f1);
        BHTEST_EQUAL(ret,"txt");
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists4.txt";
        std::string ret = Ffsys::get_name(f1);
        BHTEST_EQUAL(ret,"CMakeLists4.txt");
    }
    {
        std::string f1 = "/home/red/open/github/bhtools/build/test_file/CMakeLists4.txt";
        std::string ret = Ffsys::get_basename(f1);
        BHTEST_EQUAL(ret,"CMakeLists4");
    }
}

void test_6()
{
    {
        vlogw("");
        std::fstream fs("/home/red/open/github/bhtools/CMakeLists.txt");
        if(fs.is_open())
        {
            Ffio f(fs);
            for(int i=0;i<3;i++)
            {
                auto s = f.read_line();
                vlogd($(s));
            }
            fs.close();
        }
    }
    {
        vlogw("");
        std::fstream fs("/home/red/open/github/bhtools/CMakeLists.txt");
        if(fs.is_open())
        {
            Ffio f(fs);
            auto s = f.read_all();
            vlogd($(s));
            fs.close();
        }
    }
    {
        vlogw("");
        std::fstream fs("/home/red/open/github/bhtools/build/CMakeLists22.txt",std::ios::out);
        if(fs.is_open())
        {
            std::string ss = R"(
function(include_directories_sub root_dir)
    if (IS_DIRECTORY ${root_dir})               
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
        include_directories_sub(${root_dir}/${sub})
        endif()
    endforeach()
endfunction() 
)";

            Ffio f(fs);
            auto s = f.write(ss);
            vlogd($(ss.size()) $(s));

            fs.close();
        }
    }
    {
        vlogw("");
        std::fstream fs("/home/red/open/github/bhtools/CMakeLists.txt");
        std::fstream ofs("/home/red/open/github/bhtools/build/CMakeLists33.txt",std::ios::out);
        if(fs.is_open())
        {
            Ffio f(fs);
            Ffio f2(ofs);
            auto s = f.read_all();
            auto len = f2.write(s);

            vlogd($(s.size()) $(len));

            fs.close();
            ofs.close();
        }
    }
    {
        vlogw("");
        std::fstream fs("/home/red/open/github/bhtools/CMakeLists.txt",std::ios::in|std::ios::binary);
        std::fstream ofs("/home/red/open/github/bhtools/build/CMakeLists44.txt",std::ios::out);
        if(fs.is_open())
        {
            Ffio f(fs);
            Ffio f2(ofs);
            auto s = f.read_all();
            auto len = f2.write(s);

            vlogd($(s.size()) $(len));

            fs.close();
            ofs.close();
        }
    }
    {
        vlogw("");
        std::fstream fs("/home/red/open/github/bhtools/CMakeLists.txt");
        if(fs.is_open())
        {
            Ffio f(fs);
            vlogd($(fs.good()) $(fs.eof()) $(fs.tellg()));
            auto s = f.read_all();

            vlogd($(fs.good()) $(fs.eof()) $(fs.tellg()));

            auto buf1 = f.read_line();
            vlogd($(buf1));
            vlogd($(fs.good()) $(fs.eof()) $(fs.tellg()));

            f.reset_pos();
            vlogd($(fs.good()) $(fs.eof()) $(fs.tellg()));
            
            auto buf2 = f.read_line();
            vlogd($(buf2));
            vlogd($(fs.good()) $(fs.eof()) $(fs.tellg()));
            fs.close();
        }
    }

}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();   
    test_6();   

    return 0;
}