# == 函数 ==
# 递归目录并直接包含头文件函数
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


# 递归获取头文件子目录路径到变量
function(fn_get_include_sub_ls result root_dir)
    set(abs_dir ${CMAKE_SOURCE_DIR}/${root_dir})
    if (IS_DIRECTORY ${abs_dir})
        file(GLOB children RELATIVE ${abs_dir} ${abs_dir}/*)
        set(dirlist "")
        foreach(child ${children})
            if(IS_DIRECTORY ${abs_dir}/${child})
                list(APPEND dirlist ${root_dir}/${child})
                fn_get_include_sub_ls(subdirlist ${root_dir}/${child})
                list(APPEND dirlist ${subdirlist})
            endif()
        endforeach()
        set(${result} ${dirlist} PARENT_SCOPE)
    endif()
endfunction()

# 递归获取目录下的库文件
function(fn_get_lib_ls result root_dir)
    file(GLOB_RECURSE reslib "${root_dir}/*.so*")
    set(${result} ${reslib} PARENT_SCOPE)
endfunction()
# == 函数 ==



# ===== 编译入口 =====
# 项目名
cmake_minimum_required(VERSION 3.22.1)
project(bhtools)


# C++ 11 版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# 调试模式
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")


# 查找多线程
find_package(Threads REQUIRED)



# 加载头文件
include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(${CMAKE_THREAD_LIBS_INIT})

if(ALL OR main_log)
    add_executable(main_log test/main_log.cpp)
endif()

if(ALL OR main_time)
    add_executable(main_time test/main_time.cpp)
endif()


# 生成目标
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
