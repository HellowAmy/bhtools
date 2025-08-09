
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
    {   
        bhtools::Ffio io("/home/red/open/github/bhtools/main.cpp");
        if(io)
        {
            std::string ss = io.read_all();
            vlogd($(ss));
            
            io.reset_pos();
            auto vec = io.read_line_all();
            vlogd($C(vec));
    
            io.reset_pos();
            std::string s1 = io.read_line();
            s1 += io.read_line();
            s1 += io.read_line();
            vlogd($(s1));
    
            size_t len = io.file_len_max();
            vlogd($(len));

            io.close();
        }
    }

    // 修改文件
    {
        bhtools::Ffsys::copy_file(
            "/home/red/open/github/bhtools/main.cpp",
            "/home/red/open/github/bhtools/main2.cpp"
        );

        bhtools::Ffio io("/home/red/open/github/bhtools/main2.cpp");
        if(io)
        {
            std::string s1 = io.read_all();
            vlogd($(s1));
    
            io.reset_pos();
            io.skip_pos(20);
            size_t t1 = io.write_line("123456789");
    
            io.skip_pos(50);
            size_t t2 = io.write("s123456789s");
            vlogd($(t1) $(t2));
    
            std::string s2 = io.read_all();
            vlogd($(s2));
            io.close();
        }

        bhtools::Ffio io2("/home/red/open/github/bhtools/main2.cpp");
        if(io2)
        {
            std::string s3 = io2.read_all();
            vlogd($(s3));
            io2.close();
        }

        bhtools::Ffsys::remove_file(
            "/home/red/open/github/bhtools/main2.cpp"
        );
    }
}

void test_5()
{
    // 路径拼接
    std::string ss = bhtools::Fjoin()("123","abc","qwe","asd");
    vlogd($(ss));


    // 获取环境变量
    std::string s1 = bhtools::Ffsys::get_env("USER");
    std::string s2 = bhtools::Ffsys::get_env("HTTP_PROXY");
    std::string s3 = bhtools::Ffsys::get_env("DBUS_SESSION_BUS_ADDRESS");
    std::string s4 = bhtools::Ffsys::get_env("Pos11s");

    vlogd($(s1) $(s2) $(s3) $(s4));
}

int main(int argc, char *argv[])
{
    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    test_5();   

    return 0;
}