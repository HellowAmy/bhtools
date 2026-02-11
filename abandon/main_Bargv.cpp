#include <iostream>

#include "Bargv.h"
#include "Tlog.h"
#include "Btest.h"
#include "Btype.h"

void test_1()
{
    vloga("Bargv 模拟命令行字符串初始化测试");
    bh::Bargv parse;
    bh::dstr cmd = "./program -a --prefix=/usr/local -f config.conf -p p1 p2 --version 1.5";
    parse.init(cmd);

    vlogd("解析后的完整参数列表: " << $C(parse.get_args()));
    BHTEST_EQUAL(parse.get_args().size(), (bh::uint64)9);

    vloga("参数存在性 (is_exist) 校验");
    BHTEST_TRUE(parse.is_exist("-a"));
    BHTEST_TRUE(parse.is_exist("--prefix=/usr/local"));
    BHTEST_TRUE(!parse.is_exist("-invalid"));

    vloga("单参数值提取 (is_exist_arg) 校验");
    BHTEST_EQUAL(parse.is_exist_arg("-f"), "config.conf");
    BHTEST_EQUAL(parse.is_exist_arg("--version"), "1.5");

    vloga("多参数列表提取 (is_exist_args) 校验");
    auto vec = parse.is_exist_args("-p");
    BHTEST_EQUAL(vec.size(), (bh::uint64)2);
    if(vec.size() == 2) {
        BHTEST_EQUAL(vec[0], "p1");
        BHTEST_EQUAL(vec[1], "p2");
    }

    vloga("路径/赋值型参数解析 (is_exist_path) 校验");
    BHTEST_EQUAL(parse.is_exist_path("--prefix"), "/usr/local");
}

int main(bh::int32 argc, char *argv[])
{
    vloga("Bargv 程序启动环境参数展示");
    bh::Bargv real_parse;
    real_parse.init(argc, argv);
    vlogd("当前进程启动参数: " << $C(real_parse.get_args()));

    test_1();
    return 0;
}
