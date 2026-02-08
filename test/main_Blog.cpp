#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>

#include "Blog.h"
#include "Bfm.h"
#include "Btime.h"
#include "Btype.h"
#include "Btest.h"

void test_1()
{
    vloga("Blog 各等级颜色打印效果测试 (参考 main_log::test_1)");
    vloga("vloga - 展示 [All] 等级");
    vlogd("vlogd - 展示 [Deb] 等级");
    vlogi("vlogi - 展示 [Inf] 等级");
    vlogw("vlogw - 展示 [War] 等级");
    vloge("vloge - 展示 [Err] 等级");
    vlogf("vlogf - 展示 [Fat] 等级");

    vloga("基础类型变量流式追加打印测试");
    bool a1 = true;
    bh::int32 a2 = 10;
    bh::uint64 a3 = 64;
    bh::ft64 a4 = 6.66;
    bh::dstr a5 = "bh_dstr_content";
    bh::cchp a6 = "bh_cchp_content";
    vlogd(a1 << " | " << a2 << " | " << a3 << " | " << a4 << " | " << a5 << " | " << a6);

    vloga("带变量名格式化打印测试 ($ 宏)");
    vlogi($(a1) $(a2) $(a3) $(a4) $(a5) $(a6));

    vloga("标准容器可视化展示测试 ($C 宏)");
    std::vector<bh::int32> vec;
    std::list<bh::int32> ls;
    std::map<bh::int32, bh::dstr> mp;
    std::unordered_map<bh::int32, bh::dstr> mp2;
    for(bh::int32 i = 0; i < 5; i++) {
        bh::dstr val = bh::Bfm("val_{}")(i);
        vec.push_back(i);
        ls.push_back(i);
        mp.emplace(i, val);
        mp2.emplace(i, val);
    }
    vlogd($C(vec));
    vlogd($C(ls));
    vlogd($C(mp));
    vlogd($C(mp2));

    vloga("日志运行等级动态切换测试");
    auto log_conf = bh::Bsin_log_conf::get();
    
    vloga("切换等级至 War (仅警告及以上可见)");
    log_conf->set_level(log_conf->_cmd, bh::bhenum::level::e_war);
    vlogd("这条调试信息不应该被看到");
    vlogw("这条警告信息应该被看到");

    vloga("切换等级至 Fat (仅致命错误可见)");
    log_conf->set_level(log_conf->_cmd, bh::bhenum::level::e_fat);
    vlogw("这条警告信息不应该被看到");
    vlogf("这条致命信息应该被看到");

    vloga("恢复等级至 All");
    log_conf->set_level(log_conf->_cmd, bh::bhenum::level::e_all);
}

void test_2()
{
    vloga("Blog 多端输出与异步文件日志测试 (参考 main_log::test_2)");
    auto log_conf = bh::Bsin_log_conf::get();

    vloga("测试 nlogd (静默输出，不产生任何内容)");
    nlogd("silent message");

    vloga("测试 flog* 系列文件日志 (输出至 Bflog.log)");
    flogd("flogd write to file");
    floge("floge write to file");

    vloga("测试 alog* 系列异步文件日志 (输出至 Baflog.log)");
    alogd("alogd async write");
    alogi("alogi async write");
    
    vloga("测试异步日志文件重开与刷新逻辑");
    log_conf->exit_flush_afile();
    log_conf->reopen(log_conf->_afile, "Baflog_v2.log", true);
    alogd("alogd_v2 content after reopen");
    
    vloga("执行异步刷新以确保程序退出前数据落盘");
    log_conf->exit_flush_afile();
}

void test_3()
{
    vloga("Blog 文件滚动(Rotation)策略与数量限制测试 (参考 main_log::test_3)");
    auto log_conf = bh::Bsin_log_conf::get();
    
    vloga("配置滚动策略：单文件长度 64K，最大保留 3 个备份文件");
    log_conf->reopen(log_conf->_file, "Broll.log", false);
    log_conf->set_length(log_conf->_file, (1 << 16)); 
    log_conf->set_limit(log_conf->_file, 3);
    
    bh::int32 num = 1500;
    vloga("开始压力写入以触发文件自动切分...");
    for(bh::int32 i = 0; i < num; i++) {
        flogd("rolling_log_index_" << bh::Bfm("{}")(i));
    }
    vloga("文件切分操作模拟完成");
}

void test_4()
{
    vloga("Blog 不同输出端性能极限压力测试 (参考 main_log::test_4)");
    bh::Btimel watch;
    bh::int32 stress_num = 5;
    
    bh::int32 val_i = 12345;
    bh::dstr val_s = "performance_benchmark_content";

    vloga("1. 开始同步命令行输出压力测试 (5万次)...");
    watch.update();
    for(bh::int32 i = 0; i < stress_num; i++) {
        vlogd($(val_i) $(val_s) $(i));
    }
    vloga("命令行输出总耗时: " << watch.to_str());

    vloga("2. 开始文件输出压力测试 (5万次)...");
    watch.update();
    for(bh::int32 i = 0; i < stress_num; i++) {
        flogd($(val_i) $(val_s) $(i));
    }
    vloga("同步文件输出总耗时: " << watch.to_str());

    vloga("3. 开始异步文件输出压力测试 (5万次)...");
    watch.update();
    for(bh::int32 i = 0; i < stress_num; i++) {
        alogd($(val_i) $(val_s) $(i));
    }
    vloga("异步文件输出总耗时: " << watch.to_str());
    bh::Bsin_log_conf::get()->exit_flush_afile();
}

int main(bh::int32 argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}
