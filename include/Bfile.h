#ifndef BFILE_H
#define BFILE_H

#include <fstream>
#include <functional>
#include <vector>

#ifdef __linux__
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <unistd.h>
#elif __WIN32__
#include <Windows.h>
#include <cstdio>
#include <sys/stat.h>
#include <string>
#endif

#include "Btype.h"
#include "Bdiv.h"

namespace bh {

// 跨平台处理函数
#ifdef __linux__
namespace platform {

    // 分隔符
    inline static dstr file_splitter() { return "/"; }

    // 换行符
    inline static dstr file_break() { return "\n"; }

    // 获取当前路径
    inline static dstr get_dir()
    {
        char buff[FILENAME_MAX] = {0};
        if(getcwd(buff, sizeof(buff)) != nullptr) {
            return dstr(buff);
        }
        return "";
    }

    // 切换到目标路径
    inline static bool set_dir(cstr path)
    {
        if(chdir(path.c_str()) == 0) {
            return true;
        }
        return false;
    }

    // 合并路径
    inline static dstr path_merge(cstr prefix, cstr file)
    {
        if(prefix.size() > 0) {
            dstr sp = prefix.substr(prefix.size() - file_splitter().size());
            if(sp == file_splitter()) {
                return prefix + file;
            }
            else {
                return prefix + file_splitter() + file;
            }
        }
        return prefix + file;
    }

    // 判断文件夹存在
    inline static bool is_exist_file(cstr path)
    {
        struct stat st;
        int32 ret = lstat(path.c_str(), &st);
        if(ret == 0 && (st.st_mode & S_IFREG)) {
            return true;
        }
        return false;
    }

    // 判断文件夹存在
    inline static bool is_exist_dir(cstr path)
    {
        DIR *dir = opendir(path.c_str());
        if(dir) {
            closedir(dir);
            return true;
        }
        return false;
    }

    // 判断为文件
    inline static bool is_file_type(cstr path)
    {
        struct stat st;
        lstat(path.c_str(), &st);
        if(st.st_mode & S_IFREG) {
            return true;
        }
        return false;
    }

    // 判断为目录
    inline static bool is_dir_type(cstr path)
    {
        struct stat st;
        lstat(path.c_str(), &st);
        if(st.st_mode & S_IFDIR) {
            return true;
        }
        return false;
    }

    // 删除文件
    inline static bool remove_file(cstr file) { return remove(file.c_str()) == 0; }

    // 移动文件
    inline static bool move_file(cstr src, cstr dst)
    {
        return rename(src.c_str(), dst.c_str()) == 0;
    }

    // 创建单层目录
    inline static bool create_dir(cstr dir, int32 mode)
    {
        return (!dir.empty() && !is_exist_dir(dir) && (mkdir(dir.c_str(), mode) != 0)) == false;
    }

    // 创建多层目录
    inline static bool make_dir(cstr dir, int32 mode)
    {
        uint64 pos = 0;
        dstr level;
        while((pos = dir.find(file_splitter(), pos)) != dstr::npos) {
            level = dir.substr(0, pos);
            if(create_dir(level, mode) == false) {
                return false;
            }
            pos++;
        }
        if(pos != dir.size()) {
            level = dir.substr(0, dir.size());
        }

        if(create_dir(level, mode) == false) {
            return false;
        }
        return true;
    }

    // 获取文件与目录列表
    inline static bool get_dir_info(cstr path, std::vector<dstr> &files,
                                    std::vector<dstr> &dirs, bool recursion)
    {
        DIR *dir = opendir(path.c_str());
        if(dir) {
            struct dirent *entry;
            std::vector<dstr> level;
            while((entry = readdir(dir)) != nullptr) {
                if(dstr(entry->d_name) != "." && dstr(entry->d_name) != "..") {
                    dstr path_name = platform::path_merge(path, dstr(entry->d_name));
                    if(is_dir_type(path_name)) {
                        level.push_back(path_name);
                    }
                    else {
                        files.push_back(path_name);
                    }
                }
            }
            for(auto &a : level) {
                dirs.push_back(a);
                if(recursion) {
                    get_dir_info(a, files, dirs, recursion);
                }
            }
            closedir(dir);
            return true;
        }
        return false;
    }

    // 删除文件
    inline static bool rm_file(cstr path) { return remove(path.c_str()) == 0; }

    // 删除空目录
    inline static bool rm_dir(cstr path) { return rmdir(path.c_str()) == 0; }

    // 删除目录包括目录下所有内容
    inline static bool remove_dir(cstr dir)
    {
        std::vector<dstr> files;
        std::vector<dstr> dirs;
        if(platform::get_dir_info(dir, files, dirs, true)) {
            for(auto it = files.rbegin(); it != files.rend(); it++) {
                if(platform::rm_file(*it) == false) {
                    return false;
                }
            }
            for(auto it = dirs.rbegin(); it != dirs.rend(); it++) {
                if(platform::rm_dir(*it) == false) {
                    return false;
                }
            }
            if(platform::rm_dir(dir) == false) {
                return false;
            }

            return true;
        }
        return false;
    }

} // namespace platform
#elif __WIN32__

namespace platform {

    // 分隔符
    inline static dstr file_splitter() { return "\\"; }

    // 换行符
    inline static dstr file_break() { return "\n"; }

    // 合并路径
    inline static dstr path_merge(cstr prefix, cstr file)
    {
        if(prefix.size() > 0) {
            dstr sp = prefix.substr(prefix.size() - file_splitter().size());
            if(sp == file_splitter()) {
                return prefix + file;
            }
            else {
                return prefix + file_splitter() + file;
            }
        }
        return prefix + file;
    }

    // 判断文件夹存在
    inline static bool is_exist_file(cstr path)
    {
        struct stat info;
        int32 ret = stat(path.c_str(), &info);
        if(ret == 0 && S_ISREG(info.st_mode)) {
            return true;
        }
        return false;
    }

    // 判断文件夹存在
    inline static bool is_exist_dir(cstr path)
    {
        struct stat info;
        if(stat(path.c_str(), &info) == 0) {
            return true;
        }
        return false;
    }

    // 判断为文件
    inline static bool is_file_type(cstr path)
    {
        struct stat info;
        stat(path.c_str(), &info);
        if(S_ISREG(info.st_mode)) {
            return true;
        }
        return false;
    }

    // 判断为目录
    inline static bool is_dir_type(cstr path)
    {
        struct stat info;
        stat(path.c_str(), &info);
        if(S_ISDIR(info.st_mode)) {
            return true;
        }
        return false;
    }

    // 删除文件
    inline static bool remove_file(cstr file) { return remove(file.c_str()) == 0; }

    // 移动文件
    inline static bool move_file(cstr src, cstr dst)
    {
        return rename(src.c_str(), dst.c_str()) == 0;
    }

    // 创建单层目录
    inline static bool create_dir(cstr dir, int32 mode)
    {
        return (!dir.empty() && !is_exist_dir(dir) && (mkdir(dir.c_str()) != 0)) == false;
    }

    // 创建多层目录
    inline static bool make_dir(cstr dir, int32 mode)
    {
        uint64 pos = 0;
        dstr level;
        while((pos = dir.find(file_splitter(), pos)) != dstr::npos) {
            level = dir.substr(0, pos);
            if(create_dir(level, mode) == false) {
                return false;
            }
            pos++;
        }
        if(pos != dir.size()) {
            level = dir.substr(0, dir.size());
        }

        if(create_dir(level, mode) == false) {
            return false;
        }
        return true;
    }

    // 获取文件与目录列表
    inline static bool get_dir_info(cstr path, std::vector<dstr> &files,
                                    std::vector<dstr> &dirs, bool recursion)
    {
        if(path[path.size() - 1] != platform::file_splitter()[0]) {
            path += platform::file_splitter();
        }

        WIN32_FIND_DATA fdata;
        HANDLE hfile = FindFirstFileA(dstr(path + "*").c_str(), &fdata);
        if(hfile != INVALID_HANDLE_VALUE) {
            std::vector<dstr> level;
            do {
                if(dstr(fdata.cFileName) != "." && dstr(fdata.cFileName) != "..") {
                    dstr path_name =
                        platform::path_merge(path, dstr(fdata.cFileName));
                    if(is_dir_type(path_name)) {
                        level.push_back(path_name);
                    }
                    else {
                        files.push_back(path_name);
                    }
                }
            } while(FindNextFile(hfile, &fdata) != 0);

            for(auto &a : level) {
                dirs.push_back(a);
                if(recursion) {
                    get_dir_info(a + file_splitter(), files, dirs, recursion);
                }
            }
            FindClose(hfile);
            return true;
        }
        return false;
    }

    // 删除文件
    inline static bool rm_file(cstr path) { return remove(path.c_str()) == 0; }

    // 删除空目录
    inline static bool rm_dir(cstr path) { return rmdir(path.c_str()) == 0; }

    // 删除目录包括目录下所有内容
    inline static bool remove_dir(cstr dir)
    {
        std::vector<dstr> files;
        std::vector<dstr> dirs;
        if(platform::get_dir_info(dir, files, dirs, true)) {
            for(auto it = files.rbegin(); it != files.rend(); it++) {
                if(platform::rm_file(*it) == false) {
                    return false;
                }
            }
            for(auto it = dirs.rbegin(); it != dirs.rend(); it++) {
                if(platform::rm_dir(*it) == false) {
                    return false;
                }
            }
            if(platform::rm_dir(dir) == false) {
                return false;
            }

            return true;
        }
        return false;
    }

} // namespace platform
#endif

// 文件处理类-提供跨平台处理文件与目录的功能
class Bfsys
{
public:
    // 获取环境变量
    inline static dstr get_env(cstr name)
    {
        dchp val = std::getenv(name.c_str());
        if(val) {
            return val;
        }
        return "";
    }

    // 获取当前路径
    inline static dstr get_dir() { return platform::get_dir(); }

    // 切换到目标路径
    inline static bool set_dir(cstr path) { return platform::set_dir(path); }

    // 替换为当前平台路径
    inline static dstr platform_path(cstr path)
    {
        dstr sp = platform::file_splitter();
        if(sp == splitter_linux()) {
            return replace_str(path, splitter_win32(), sp);
        }
      
        return replace_str(path, splitter_linux(), sp);
    }

    // 判断存在-文件
    inline static bool is_exist_file(cstr path)
    {
        return platform::is_exist_file(path);
    }

    // 判断存在-文件夹
    inline static bool is_exist_dir(cstr path)
    {
        return platform::is_exist_dir(path);
    }

    // 判断为文件
    inline static bool is_file_type(cstr path)
    {
        return platform::is_file_type(path);
    }

    // 判断为目录
    inline static bool is_dir_type(cstr path) { return platform::is_dir_type(path); }

    // 删除文件
    inline static bool remove_file(cstr file) { return platform::remove_file(file); }

    // 移动文件
    inline static bool move_file(cstr src, cstr dst)
    {
        return platform::move_file(src, dst);
    }

    // 复制文件
    inline static bool copy_file(cstr src, cstr dst)
    {
        std::ifstream ifs(src, std::ios::binary);
        std::ofstream ofs(dst, std::ios::binary);
        if(ifs.is_open() && ofs.is_open()) {
            ofs << ifs.rdbuf();
            ifs.close();
            ofs.close();
            return true;
        }
        return false;
    }

    // 创建单层目录
    inline static bool create_dir(cstr dir, int32 mode = 0755)
    {
        return platform::create_dir(dir, mode);
    }

    // 创建多层目录
    inline static bool make_dir(cstr dir, int32 mode = 0755)
    {
        return platform::make_dir(dir, mode);
    }

    // 删除目录包括目录下所有内容-目录不存在则认为删除成功
    inline static bool remove_dir(cstr dir)
    {
        if(is_exist_dir(dir)) {
            return platform::remove_dir(dir);
        }
        else {
            return true;
        }
    }

    // 返回后缀
    inline static dstr get_suffix(cstr file)
    {
        return Bdiv(file)(".", -1, -1);
    }

    // 返回全名称
    inline static dstr get_name(cstr file)
    {
        return Bdiv(file)(platform::file_splitter(), -1, -1);
    }

    // 返回无后缀名
    inline static dstr get_basename(cstr file)
    {
        return Bdiv(file)(platform::file_splitter(), -1, -1, ".", 0, 0);
    }

    // 获取文件
    inline static std::vector<dstr> get_files(cstr path, bool recursion = true)
    {
        std::vector<dstr> files;
        std::vector<dstr> dirs;
        if(platform::get_dir_info(path, files, dirs, recursion)) {
            return files;
        }
        return {};
    }

    // 获取目录
    inline static std::vector<dstr> get_dirs(cstr path, bool recursion = true)
    {
        std::vector<dstr> files;
        std::vector<dstr> dirs;
        if(platform::get_dir_info(path, files, dirs, recursion)) {
            return dirs;
        }
        return {};
    }

    // 获取文件和目录
    inline static std::tuple<std::vector<dstr>, std::vector<dstr>> get_files_and_dirs(
        cstr path, bool recursion = true)
    {
        std::vector<dstr> files;
        std::vector<dstr> dirs;
        if(platform::get_dir_info(path, files, dirs, recursion)) {
            return std::make_tuple(files, dirs);
        }
        return {};
    }

    // internal
    // 平台分割符
    inline static dstr splitter_linux() { return "/"; }
    inline static dstr splitter_win32() { return "\\"; }

    // 替换字符串
    inline static dstr replace_str(cstr str, cstr from,
                                          cstr to)
    {
        dstr ret = str;
        uint64 pos = 0;
        while((pos = ret.find(from, pos)) != dstr::npos) {
            ret.replace(pos, from.length(), to);
            pos++;
        }
        return ret;
    }
};

// 文件读写扩展类
class Bfio : private std::fstream
{
public:
    using std::fstream::fstream;

    operator bool() { return is_open(); }

    // 判断文件打开
    bool is_open() { return std::fstream::is_open(); }

    // 读取所有字节
    dstr read_all(uint64 chunk_size = 0)
    {
        dstr buf;
        if(chunk_size == 0) {
            buf.resize(file_len_max());
            read((dchp)buf.c_str(), buf.size());
        }
        else {
            dstr cache;
            cache.resize(chunk_size);
            while(eof() == false) {
                read((dchp)cache.c_str(), cache.size());
                buf += cache;
            }
        }
        return buf;
    }

    // 读取一行文本
    dstr read_line()
    {
        dstr buf;
        std::getline(*this, buf);
        return buf;
    }

    // 读取所有行
    std::vector<dstr> read_line_all(
        std::function<bool(cstr)> filtrate = nullptr)
    {
        std::vector<dstr> vec;
        dstr buf;
        while(std::getline(*this, buf)) {
            if(filtrate) {
                if(filtrate(buf)) {
                    vec.push_back(buf);
                }
            }
            else {
                vec.push_back(buf);
            }
        }
        return vec;
    }

    // 写入缓冲字节
    uint64 write(cstr buf)
    {
        uint64 bnow = tellp();
        std::fstream::write(buf.c_str(), buf.size());

        uint64 enow = tellp();
        uint64 len = enow - bnow;
        if(buf.size() == len) {
            return len;
        }
        return 0;
    }

    // 写入一行字符-返回带换行符长度
    uint64 write_line(cstr buf)
    {
        uint64 bnow = tellp();
        dstr sbreak = platform::file_break();
        dstr str = buf + sbreak;
        std::fstream::write(str.c_str(), str.size());

        uint64 enow = tellp();
        uint64 len = enow - bnow;
        if((buf.size() + sbreak.size()) == len) {
            return len;
        }
        return 0;
    }

    // 获取文件最大长度
    uint64 file_len_max()
    {
        uint64 now = tellg();
        seekg(0, std::ios::end);

        uint64 end = tellg();
        seekg(now, std::ios::beg);
        return end;
    }

    // 清除状态重新开始
    void reset_pos()
    {
        clear();
        seekg(0, std::ios::beg);
        seekp(0, std::ios::beg);
    }

    // 从当前位置跳过指定长度
    void skip_pos(uint64 len)
    {
        uint64 pnow = tellp();
        uint64 gnow = tellg();
        seekp(pnow + len, std::ios::beg);
        seekg(gnow + len, std::ios::beg);
    }

    // 关闭文件
    void close() { std::fstream::close(); }
};

// 文件路径拼接
class Bjoin
{
public:
    // 退出函数
    dstr operator()(cstr str) { return _str + str; }

    // 拼接路径
    template <typename... Targ>
    dstr operator()(cstr str, Targ... arg)
    {
        _str += str + platform::file_splitter();
        return (*this)(arg...);
    }

protected:
    dstr _str; // 存储拼接内容
};

} // namespace bh

#endif // BFILE_H
