#include <iostream>
#include <vector>
#include <tuple>

#include "Bfile.h"
#include "Btype.h"
#include "Btest.h"
#include "Tlog.h"

void test_1()
{
    vloga("Bfsys 跨平台文件系统基础接口测试 (参考 main_file::test_1)");

    bh::dstr current_dir = bh::Bfsys::get_dir();
    vloga("当前工作目录获取展示");
    vlogd($(current_dir));

    vloga("路径平台适配性测试 (platform_path)");
    bh::dstr p1 = bh::Bfsys::platform_path("/home/red/test");
    bh::dstr p2 = bh::Bfsys::platform_path("C:\\windows\\test");
    vlogd($(p1) $(p2));

    vloga("文件与目录存在性及类型判断校验");
    bh::dstr self_file = current_dir + bh::platform::file_splitter() + "CMakeLists.txt";
    bool e1 = bh::Bfsys::is_exist_file(self_file);
    bool e2 = bh::Bfsys::is_exist_dir(current_dir);
    bool t1 = bh::Bfsys::is_file_type(self_file);
    bool t2 = bh::Bfsys::is_dir_type(current_dir);
    
    vlogd($(self_file) $(e1) $(e2) $(t1) $(t2));
    BHTEST_TRUE(e1);
    BHTEST_TRUE(e2);
    BHTEST_TRUE(t1);
    BHTEST_TRUE(t2);
}

void test_2()
{
    vloga("Bfsys 物理文件/目录操作压力与清理测试 (参考 main_file::test_2/3)");
    bh::dstr base = bh::Bfsys::get_dir() + bh::platform::file_splitter() + "build";
    bh::dstr test_dir = base + bh::platform::file_splitter() + "bh_file_test_dir";
    bh::dstr test_file = test_dir + bh::platform::file_splitter() + "bh_test.txt";

    vloga("执行 make_dir 创建多级测试目录");
    BHTEST_TRUE(bh::Bfsys::make_dir(test_dir));
    BHTEST_TRUE(bh::Bfsys::is_exist_dir(test_dir));

    vloga("利用 Bfio 执行文件创建与写入内容");
    {
        bh::Bfio io(test_file, std::ios::out);
        BHTEST_TRUE(io.is_open());
        bh::dstr content = "bh_file_system_integrity_test_data";
        BHTEST_EQUAL(io.write(content), content.size());
        io.close();
    }

    vloga("执行 copy_file 复制测试");
    bh::dstr copy_path = test_dir + bh::platform::file_splitter() + "bh_test_copy.txt";
    BHTEST_TRUE(bh::Bfsys::copy_file(test_file, copy_path));
    BHTEST_TRUE(bh::Bfsys::is_exist_file(copy_path));
    
    vloga("执行 move_file 移动测试");
    bh::dstr move_path = test_dir + bh::platform::file_splitter() + "bh_test_moved.txt";
    BHTEST_TRUE(bh::Bfsys::move_file(copy_path, move_path));
    BHTEST_TRUE(!bh::Bfsys::is_exist_file(copy_path));
    BHTEST_TRUE(bh::Bfsys::is_exist_file(move_path));

    vloga("执行 remove_dir 递归清理测试目录");
    BHTEST_TRUE(bh::Bfsys::remove_dir(test_dir));
    BHTEST_TRUE(!bh::Bfsys::is_exist_dir(test_dir));
}

void test_3()
{
    vloga("Bfsys 路径字符串解析逻辑测试 (参考 main_file::test_1 结尾)");
    bh::dstr mock_path = "/home/project/include/Bfile.h";
    
    bh::dstr suffix = bh::Bfsys::get_suffix(mock_path);
    bh::dstr name = bh::Bfsys::get_name(mock_path);
    bh::dstr basename = bh::Bfsys::get_basename(mock_path);
    
    vlogd($(suffix) $(name) $(basename));
    BHTEST_EQUAL(suffix, "h");
    BHTEST_EQUAL(name, "Bfile.h");
    BHTEST_EQUAL(basename, "Bfile");

    vloga("执行 get_files 目录遍历测试");
    auto files = bh::Bfsys::get_files("include", false);
    vlogd("include 目录下文件数: " $(files.size()));
    BHTEST_TRUE((files.size() > 0));
}

void test_4()
{
    vloga("Bjoin 与 Bfsys 环境变量及路径切换测试 (参考 main_file::test_5)");
    
    vloga("测试变长参数路径拼接 Bjoin");
    bh::dstr joined = bh::Bjoin()("usr", "local", "bin", "bh_exec");
    vlogd("拼接结果展示: " $(joined));
    BHTEST_TRUE((joined.find("bin") != bh::dstr::npos));

    vloga("测试获取系统环境变量 (USER / PATH)");
    bh::dstr env_user = bh::Bfsys::get_env("USER");
    vlogd("USER: " $(env_user));
    if(!env_user.empty()) {
        BHTEST_TRUE((env_user.size() > 0));
    }

    vloga("测试工作路径切换 (set_dir)");
    bh::dstr old_path = bh::Bfsys::get_dir();
    bool changed = bh::Bfsys::set_dir("include");
    BHTEST_TRUE(changed);
    vlogd("切换后路径: " $(bh::Bfsys::get_dir()));
    
    bh::Bfsys::set_dir(old_path); // 恢复路径
    BHTEST_EQUAL(bh::Bfsys::get_dir(), old_path);
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}
