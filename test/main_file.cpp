
#include <iostream>

#include "bhtools.h"


void test_1()
{
    // 测试接口
    {
        auto s1 = bhtools::Ffsys::platform_path("/home/red/open/github/bhtools");
        auto s2 = bhtools::Ffsys::platform_path("C:\\home\\red\\open\\github\\bhtools");
        vlogd($("platform_path") $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::is_exist_file("/home/red/open/github/bhtools/main.cpp");
        auto s2 = bhtools::Ffsys::is_exist_file("/home/red/open/github/bhtools/main2.cpp");
        vlogd($("is_exist_file")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::is_exist_dir("/home/red/open/github/bhtools");
        auto s2 = bhtools::Ffsys::is_exist_dir("/home/red/open/github/bhtools2");
        vlogd($("is_exist_dir")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::is_file_type("/home/red/open/github/bhtools/main.cpp");
        auto s2 = bhtools::Ffsys::is_file_type("/home/red/open/github/bhtools");
        vlogd($("is_file_type")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::is_dir_type("/home/red/open/github/bhtools/main.cpp");
        auto s2 = bhtools::Ffsys::is_dir_type("/home/red/open/github/bhtools");
        vlogd($("is_dir_type")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::copy_file(
            "/home/red/open/github/bhtools/main.cpp",
            "/home/red/open/github/bhtools/build/main2.cpp"
        );
        vlogd($("copy_file")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::move_file(
            "/home/red/open/github/bhtools/build/main2.cpp",
            "/home/red/open/github/bhtools/main2.cpp"
        );
        vlogd($("move_file")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::remove_file(
            "/home/red/open/github/bhtools/main2.cpp"
        );
        vlogd($("remove_file")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::create_dir(
            "/home/red/open/github/bhtools/build/p1"
        );
        auto s2 = bhtools::Ffsys::create_dir(
            "/home/red/open/github/bhtools/build/p1/pp1"
        );
        vlogd($("create_dir")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::make_dir(
            "/home/red/open/github/bhtools/build/f1/ff1"
        );
        vlogd($("make_dir")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::remove_dir(
            "/home/red/open/github/bhtools/build/p1"
        );
        auto s2 = bhtools::Ffsys::remove_dir(
            "/home/red/open/github/bhtools/build/f1"
        );
        vlogd($("remove_dir")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::get_suffix(
            "/home/red/open/github/bhtools/build/main.cpp"
        );
        vlogd($("get_suffix")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::get_name(
            "/home/red/open/github/bhtools/build/main.cpp"
        );
        vlogd($("get_name")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::get_basename(
            "/home/red/open/github/bhtools/build/main.cpp"
        );
        vlogd($("get_basename")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::get_files(
            "/home/red/open/github/bhtools/include"
        );
        vlogd($("get_files")  $C(s1));
    }
    {
        auto s1 = bhtools::Ffsys::get_dirs(
            "/home/red/open/github/bhtools/build"
        );
        vlogd($("get_files")  $C(s1));
    }
    {
        auto s1 = bhtools::Ffsys::get_files_and_dirs(
            "/home/red/open/github/bhtools/build"
        );
        vlogd($("get_files")  $C(std::get<0>(s1)) $C(std::get<1>(s1)));
    }
}

void test_2()
{
    // 创建测试
    {
        auto s1 = bhtools::Ffsys::copy_file(
            "/home/red/open/github/bhtools/main.cpp",
            "/home/red/open/github/bhtools/build/main2.cpp"
        );
        auto s2 = bhtools::Ffsys::copy_file(
            "/home/red/open/github/bhtools/main.cpp",
            "/home/red/open/github/bhtools/build/main3.cpp"
        );
        vlogd($("copy_file")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::move_file(
            "/home/red/open/github/bhtools/build/main2.cpp",
            "/home/red/open/github/bhtools/main2.cpp"
        );
        vlogd($("move_file")  $(s1));
    }
    {
        auto s1 = bhtools::Ffsys::create_dir(
            "/home/red/open/github/bhtools/build/p1"
        );
        auto s2 = bhtools::Ffsys::create_dir(
            "/home/red/open/github/bhtools/build/p1/pp1"
        );
        vlogd($("create_dir")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::make_dir(
            "/home/red/open/github/bhtools/build/f1/ff1"
        );
        vlogd($("make_dir")  $(s1));
    }
}

void test_3()
{
    // 删除测试
    {
        auto s1 = bhtools::Ffsys::remove_file(
            "/home/red/open/github/bhtools/main2.cpp"
        );
        auto s2 = bhtools::Ffsys::remove_file(
            "/home/red/open/github/bhtools/build/main3.cpp"
        );
        vlogd($("remove_file")  $(s1) $(s2));
    }
    {
        auto s1 = bhtools::Ffsys::remove_dir(
            "/home/red/open/github/bhtools/build/p1"
        );
        auto s2 = bhtools::Ffsys::remove_dir(
            "/home/red/open/github/bhtools/build/f1"
        );
        vlogd($("remove_dir")  $(s1) $(s2));
    }
}

void test_4()
{
    // 文件读写
}

void test_4()
{
    // 路径拼接
}

int main(int argc, char *argv[])
{
    test_1();   
    // test_2();   
    // test_3();   

    return 0;
}