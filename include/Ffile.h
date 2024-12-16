
#ifndef FFILE_H
#define FFILE_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include "Tlog.h"

// 跨平台处理函数
#ifdef __linux__
    #include <sys/stat.h>
    #include <dirent.h>
    #include <cstdio>

    namespace bhtools_platform {

        // 分隔符
        inline static std::string file_splitter() { return "/"; }

        // 合并路径
        inline static std::string path_merge(const std::string &prefix,const std::string &file) 
        {
            if(prefix.size() > 0)
            {
                std::string sp = prefix.substr(prefix.size() - file_splitter().size());
                if(sp == file_splitter()) { return prefix + file; }
                else { return prefix + file_splitter() + file; }
            }
            return prefix + file; 
        }
        
        // 判断文件夹存在
        inline static bool is_exist_dir(const std::string &path)
        {
            DIR *dir = opendir(path.c_str());
            if(dir)
            {
                closedir(dir);
                return true;
            }
            return false;
        }

        // 判断为文件
        inline static bool is_file_type(const std::string &path)
        {
            struct stat st;
            stat(path.c_str(),&st);
            if(st.st_mode & S_IFREG) { return true; }
            return false;
        }

        // 判断为目录
        inline static bool is_dir_type(const std::string &path)
        {
            struct stat st;
            stat(path.c_str(),&st);
            if(st.st_mode & S_IFDIR) { return true; }
            return false;
        }

        // 删除文件
        inline static bool remove_file(const std::string &file)
        { return remove(file.c_str()) == 0; }
        
        // 移动文件
        inline static bool move_file(const std::string &src,const std::string &dst)
        { return rename(src.c_str(), dst.c_str()) == 0; }
        
        // 创建单层目录
        inline static bool create_dir(const std::string &dir,int mode)
        { return (!dir.empty() && !is_exist_dir(dir) && (mkdir(dir.c_str(), mode) != 0)) == false; }

        // 创建多层目录
        inline static bool make_dir(const std::string &dir,int mode)
        {
            size_t pos = 0;
            std::string level;
            while((pos = dir.find(file_splitter(), pos)) != std::string::npos) 
            {
                level = dir.substr(0, pos);
                if(create_dir(level,mode) == false)
                { return false; }
                pos++;
            }
            if(pos != dir.size())
            { level = dir.substr(0, dir.size()); }

            if(create_dir(level,mode) == false) { return false; }
            return true;
        }

        // 获取文件与目录列表
        inline static bool get_dir_info(const std::string &path,
                                        std::vector<std::string> &files,
                                        std::vector<std::string> &dirs,
                                        bool recursion)
        {
            DIR *dir = opendir(path.c_str());
            if(dir)
            {
                struct dirent *entry;
                std::vector<std::string> level;
                while((entry = readdir(dir)) != nullptr) 
                {
                    if(std::string(entry->d_name) != "." && std::string(entry->d_name) != "..")
                    {
                        std::string path_name = bhtools_platform::path_merge(path,std::string(entry->d_name));
                        if(is_dir_type(path_name))
                        { level.push_back(path_name); }
                        else { files.push_back(path_name); }
                    }
                }
                for(auto &a : level)
                {
                    dirs.push_back(a); 
                    if(recursion) 
                    { get_dir_info(a,files,dirs,recursion); }
                }
                closedir(dir);
                return true;
            }
            return false;
        }

    } // bhtools_platform
#elif
    namespace bhtools_platform {

        // //
        // static bool is_file_type(const std::string &file)
        // { return false; }

    } // bhtools_platform
#endif



namespace bhtools {


// 
struct Ffile
{
    // 判断存在-文件
    inline static bool is_exist_file(const std::string &path)
    { std::ifstream ifs(path); return ifs.good(); } 

    // 判断存在-文件夹
    inline static bool is_exist_dir(const std::string &path)
    { return bhtools_platform::is_exist_dir(path); }

    // 判断为文件
    inline static bool is_file_type(const std::string &path)
    { return bhtools_platform::is_file_type(path); } 

    // 判断为目录
    inline static bool is_dir_type(const std::string &path)
    { return bhtools_platform::is_dir_type(path); } 

    // 删除文件
    inline static bool remove_file(const std::string &file)
    { return bhtools_platform::remove_file(file); }

    // 移动文件
    inline static bool move_file(const std::string &src,const std::string &dst)
    { return bhtools_platform::move_file(src,dst); } 

    // 复制文件
    inline static bool copy_file(const std::string &src,const std::string &dst)
    {
        std::ifstream ifs(src,std::ios::binary);
        std::ofstream ofs(dst,std::ios::binary);
        if(ifs.is_open() && ofs.is_open())
        {
            ofs << ifs.rdbuf();
            ifs.close();
            ofs.close();
            return true;
        }
        return false;
    }

    // 创建单层目录
    inline static bool create_dir(const std::string &dir,int mode = 0755)
    { return bhtools_platform::create_dir(dir,mode); }

    // 创建多层目录
    inline static bool make_dir(const std::string &dir,int mode = 0755)
    { return bhtools_platform::make_dir(dir,mode); }

    // 
    inline static bool remove_dir(const std::string &dir)
    {   

    }

    inline static std::string get_suffix(const std::string &file)
    {

    }

    inline static std::string get_name(const std::string &file)
    {

    }

    inline static std::string get_basename(const std::string &file)
    {

    }

    // 
    inline static std::vector<std::string> get_files(const std::string &path,bool recursion = true)
    { 
        std::vector<std::string> files;
        std::vector<std::string> dirs;
        if(bhtools_platform::get_dir_info(path,files,dirs,recursion))
        { return files; }
        return {};
    }

    // 
    inline static std::vector<std::string> get_dirs(const std::string &path,bool recursion = true)
    { 
        std::vector<std::string> files;
        std::vector<std::string> dirs;
        if(bhtools_platform::get_dir_info(path,files,dirs,recursion))
        { return dirs; }
        return {};
    }

    
};



} // bhtools


#endif // FFILE_H
