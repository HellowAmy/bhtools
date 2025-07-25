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


# 生成单个任务
if(ALL OR main_log)
    add_executable(main_log test/main_log.cpp)
endif()

if(ALL OR main_time)
    add_executable(main_time test/main_time.cpp)
endif()

if(ALL OR main_sin)
    add_executable(main_sin test/main_sin.cpp)
endif()

if(ALL OR main_pool)
    add_executable(main_pool test/main_pool.cpp)
endif()

if(ALL OR main_base)
    add_executable(main_base test/main_base.cpp)
endif()

if(ALL OR main_fm)
    add_executable(main_fm test/main_fm.cpp)
endif()

if(ALL OR main_heap)
    add_executable(main_heap test/main_heap.cpp)
endif()

if(ALL OR main_timer)
    add_executable(main_timer test/main_timer.cpp)
endif()

if(ALL OR main_stm)
    add_executable(main_stm test/main_stm.cpp)
endif()

if(ALL OR main_test)
    add_executable(main_test test/main_test.cpp)
endif()

if(ALL OR main_byte)
    add_executable(main_byte test/main_byte.cpp)
endif()

if(ALL OR main_design)
    add_executable(main_design test/main_design.cpp)
endif()

if(ALL OR main_cont)
    add_executable(main_cont test/main_cont.cpp)
endif()

if(ALL OR main_link)
    add_executable(main_link test/main_link.cpp)
endif()

if(ALL OR main_publish)
    add_executable(main_publish test/main_publish.cpp)
endif()

if(ALL OR main_unpack)
    add_executable(main_unpack test/main_unpack.cpp)
    target_link_libraries(main_unpack ${LIBHV})
endif()

if(ALL OR main_opt)
    add_executable(main_opt test/main_opt.cpp)
endif()

if(ALL OR main_any)
    add_executable(main_any test/main_any.cpp)
endif()

if(ALL OR main_file)
    add_executable(main_file test/main_file.cpp)
endif()

if(ALL OR main_argv)
    add_executable(main_argv test/main_argv.cpp)
endif()

if(ALL OR main_async)
    add_executable(main_async test/main_async.cpp)
endif()

# 生成目标
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# 安装头文件到目录
set(CMAKE_INSTALL_PREFIX install/bhtools)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION .
)