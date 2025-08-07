
#include <iostream>

#include "Tlog.h"
#include "Ftest.h"
#include "Ffile.h"
#include "Ftime.h"
#include "Tpool.h"

using namespace bhtools;

void test_1()
{
    {
        std::string f1 = "../main.cpp";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../test";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
    }

    {
        std::string f1 = "../main2.cpp";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "../test2";
        bool ret = Ffsys::is_exist_file(f1);
        BHTEST_EQUAL(ret,false);
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
        std::string f1 = "../test";
        bool ret = Ffsys::is_file_type(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "../main.cpp";
        bool ret = Ffsys::is_dir_type(f1);
        BHTEST_EQUAL(ret,false);
    }

}

void test_2()
{
    {
        std::string f1 = "../build/test_file/level1/level1_0";
        std::string ret = Ffsys::platform_path(f1);
        vlogd($(ret));
    }
    {
        std::string f1 = "../build";
        bool ret = Ffsys::is_exist_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../build/test_file";
        bool ret = Ffsys::is_exist_dir(f1);
        BHTEST_EQUAL(ret,false);
    }
    {
        std::string f1 = "../build/test_file2";
        bool ret = Ffsys::create_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../build/test_file/level1/level1_0";
        bool ret = Ffsys::create_dir(f1);
        BHTEST_EQUAL(ret,false);
    }

    {
        std::string f1 = "../build/test_file/level1/level1_1";
        std::string f2 = "../build/test_file/level1/level1_2";
        std::string f3 = "../build/test_file/level1/level1_3";
        bool ret1 = Ffsys::make_dir(Ffsys::platform_path(f1));
        bool ret2 = Ffsys::make_dir(Ffsys::platform_path(f2));
        bool ret3 = Ffsys::make_dir(Ffsys::platform_path(f3));
        BHTEST_EQUAL(ret1,true);
        BHTEST_EQUAL(ret2,true);
        BHTEST_EQUAL(ret3,true);
    }
    {
        std::string f1 = "../CMakeLists.txt";
        std::string f2 = "../CMakeLists2.txt";
        bool ret = Ffsys::copy_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../CMakeLists2.txt";
        std::string f2 = "../build/test_file/CMakeLists.txt";
        bool ret = Ffsys::move_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../build/test_file/CMakeLists.txt";
        std::string f2 = "../build/test_file/CMakeLists2.txt";
        std::string f3 = "../build/test_file/CMakeLists3.txt";
        std::string f4 = "../build/test_file/CMakeLists4.txt";
        std::string f5 = "../build/test_file/CMakeLists5.txt";
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
        std::string f1 = "../build/test_file/CMakeLists3.txt";
        std::string f2 = "../build/test_file/CMakeLists33.txt";
        bool ret = Ffsys::move_file(f1,f2);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../build/test_file/CMakeLists4.txt";
        bool ret = Ffsys::remove_file(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../build/test_file/level1/level1_2/1";
        std::string f2 = "../build/test_file/level1/level1_2/2";
        std::string f3 = "../build/test_file/level1/level1_3/CMakeLists1.txt";
        std::string f4 = "../build/test_file/level1/level1_3/CMakeLists2.txt";
        std::string f5 = "../build/test_file/level1/level1_3/CMakeLists3.txt";
        std::string f6 = "../build/test_file/CMakeLists.txt";
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
        auto vec = Ffsys::get_files(Ffsys::platform_path("../build/test_file/"));
        vlogd($C(vec));
    }
    {
        auto vec = Ffsys::get_dirs(Ffsys::platform_path("../build/test_file/"));
        vlogd($C(vec));
    }
    {
        auto vec = Ffsys::get_files(Ffsys::platform_path("../build/test_file"),false);
        vlogd($C(vec));
    }
    {
        auto vec = Ffsys::get_dirs(Ffsys::platform_path("../build/test_file"),false);
        vlogd($C(vec));
    }
    {
        auto tup = Ffsys::get_files_and_dirs(Ffsys::platform_path("../build/test_file"),true);
        vlogd($C(std::get<0>(tup)) $C(std::get<1>(tup)));
    }
    {
        auto tup = Ffsys::get_files_and_dirs(Ffsys::platform_path("../build/test_file"),false);
        vlogd($C(std::get<0>(tup)) $C(std::get<1>(tup)));
    }
}

void test_4()
{
    {
        std::string f1 = "../build/test_file";
        bool ret = Ffsys::remove_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../build/test_file2";
        bool ret = Ffsys::remove_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
    {
        std::string f1 = "../build/delete";
        bool ret = Ffsys::remove_dir(f1);
        BHTEST_EQUAL(ret,true);
    }
}

void test_5()
{
    {
        std::string f1 = "../build/test_file/CMakeLists4.txt";
        std::string ret = Ffsys::get_suffix(f1);
        BHTEST_EQUAL(ret,"txt");
    }
    {
        std::string f1 = "../build/test_file/CMakeLists4.txt";
        std::string ret = Ffsys::get_name(Ffsys::platform_path(f1));
        BHTEST_EQUAL(ret,"CMakeLists4.txt");
    }
    {
        std::string f1 = "../build/test_file/CMakeLists4.txt";
        std::string ret = Ffsys::get_basename(Ffsys::platform_path(f1));
        BHTEST_EQUAL(ret,"CMakeLists4");
    }
}

void test_6()
{
    {
        vlogw("");
        std::fstream fs("../CMakeLists.txt");
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
        std::fstream fs("../CMakeLists.txt");
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
        std::fstream fs("../build/CMakeLists11.txt",std::ios::out);
        if(fs.is_open())
        {
            std::string s1 = "123456789";
            std::string s2 = "你们是谁";
            std::string s3 = "qweasdzxc";

            Ffio f(fs);
            auto sr1 = f.write_line(s1);
            auto sr2 = f.write_line(s2);
            auto sr3 = f.write_line(s3);
            vlogd($(sr1) $(s1));
            vlogd($(sr2) $(s2));
            vlogd($(sr3) $(s3));

            fs.close();
        }
    }
    {
        vlogw("");
        std::fstream fs("../build/CMakeLists11.txt");
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
        std::fstream fs("../build/CMakeLists22.txt",std::ios::out);
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
        std::fstream fs("../CMakeLists.txt",std::ios::in);
        std::fstream ofs("../build/CMakeLists33.txt",std::ios::out);
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
        std::fstream fs("../CMakeLists.txt",std::ios::in|std::ios::binary);
        std::fstream ofs("../build/CMakeLists44.txt",std::ios::out|std::ios::binary);
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
        std::fstream fs("../CMakeLists.txt");
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

void test_7()
{
    {
        vlogw("");
        std::fstream fs("../CMakeLists.txt");
        if(fs.is_open())
        {
            Ffio f(fs);
            {
                auto vec = f.read_line_all();
                vlogd($C(vec));             
            }
            {
                f.reset_pos();
                auto vec = f.read_line_all([](const std::string &buf){
                    return buf.size() != 0;
                });
                vlogd($C(vec));
            }
            fs.close();
        }
    }
}

void test_8()
{
    {
        Ftimel t;
        std::fstream fs("/home/red/open/download/wps-office_11.1.0.11723.XA_amd64.deb",std::ios::in|std::ios::binary);
        if(fs.is_open())
        {
            Ffio f(fs);
            auto bin = f.read_all();
            vlogd($(bin.size()));             
            fs.close();
        }
        vlogw($(t.to_string()));
    }
    {

        Ftimel t;
        Tpool<> pool;
        pool.push([](){
            Ftimel t;
            std::fstream fs("/home/red/open/download/wps-office_11.1.0.11723.XA_amd64.deb",std::ios::in|std::ios::binary);
            if(fs.is_open())
            {
                Ffio f(fs);
                auto bin = f.read_all(4096);
                vlogd($(bin.size()));             
                fs.close();
            }
            vlogw("read" $(t.to_string()));
        });

        vlogw($(t.to_string()));
    }

    vlogw("sleep_for start");
    Ftimel::sleep(3000);
    vlogw("sleep_for end");
}

void test_9()
{
    std::string ss = Fjoin()("123","223","41","q","asd");
    std::string s1 = Fjoin()("/home/red/open/github/bhtools/","223","41","q","asd");
    // std::string ss = Ffsys::join("123","223","41","q","asd");
    vlogd($(ss));
    vlogd($(s1));
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
    // test_8();   
    test_9();   

    return 0;
}