# CMakeLists.txt

cmake_minimum_required(VERSION 3.14) # 最低版本
project(project C) # 工程名称

set(CMAKE_C_STANDARD 99) # C 版本
set(CMAKE_C_FLAGS_DEBUG "-g -Wall") # 设置编译器的类型
set(CMAKE_C_FLAGS -m32) # 编译 32 位
set(CMAKE_BUILD_TYPE DEBUG) # 设置编译类型 DEBUG/RELEASE

# ./ 不可少
include_directories(./include) # 头文件路径
link_directories(./lib) # 链接库路径

# 链接库
link_libraries(
        project
)

add_executable(project main.c)
add_subdirectory(utility) # 添加工程主目录下的存放源代码的子目录