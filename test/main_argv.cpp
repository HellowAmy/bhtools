
#include <iostream>

#include "bhtools.h"

void test_1(int argc, char *argv[])
{
    // 解析启动参数
    bhtools::Fargv parse;
    parse.init(argc,argv);

    vlogd($C(parse.get_args()));
}

void test_2()
{
    // 测试参数
    {
        bhtools::Fargv parse;
        parse.init("./main_argv -a -b -c");
        vlogd($C(parse.get_args()));
    }
    {
        bhtools::Fargv parse;
        parse.init("./main_argv -a --prefix=/home/abc/hellow -b open1 open2 --version 1.0");
        vlogd($C(parse.get_args()));
    }
}

void test_3()
{
    // 参数解析
    bhtools::Fargv parse;
    parse.init("./main_argv -a --prefix=/home/abc/hellow -f=/home/abc/world -p open1 open2 --version 1.0");
    vlogd($C(parse.get_args()));

    bool ok1 = parse.is_exist("-a");
    bool ok2 = parse.is_exist("-b");
    vlogd($(ok1) $(ok2));

    std::string s1 = parse.is_exist_arg("-a");
    std::string s2 = parse.is_exist_arg("-b");
    std::string s3 = parse.is_exist_arg("--version");
    vlogd($(s1) $(s2) $(s3));

    std::vector<std::string> vec1 = parse.is_exist_args("-p");
    std::vector<std::string> vec2 = parse.is_exist_args("-pp");
    vlogd($C(vec1) $C(vec2));

    std::string p1 = parse.is_exist_path("--prefix");
    std::string p2 = parse.is_exist_path("-f");
    vlogd($(p1) $(p2));
    
}

void test_4()
{
    // 文件读写

}

void test_4()
{
    // 文件读写
    
}

int main(int argc, char *argv[])
{
    test_1(argc,argv);   
    test_2();   
    test_3();   

    return 0;
}
