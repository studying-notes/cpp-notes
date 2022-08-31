---
date: 2022-02-21T00:07:56+08:00
author: "Rustle Karl"

title: "CMake 详解"
url:  "posts/cpp/quickstart/compile/cmake"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [基础规则](#基础规则)
- [定义变量](#定义变量)
  - [日志输出级别](#日志输出级别)
- [内置变量](#内置变量)
- [命令](#命令)
- [编译](#编译)
  - [静态库与动态库](#静态库与动态库)
  - [自动获取源码列表](#自动获取源码列表)
  - [递归获取文件列表](#递归获取文件列表)
  - [指定库的输出名称](#指定库的输出名称)
  - [定义宏与条件编译](#定义宏与条件编译)

## 基础规则

`CMakeLists.txt` 文件由命令、注释和空格组成，其中**命令是不区分大小写的**。`#` 开头的行表示注释。命令由命令名称、小括号和参数组成，参数之间使用空格进行间隔。

## 定义变量

```ini
# 定义变量 SRC_LIST
set (SRC_LIST add.c sub.c mul.c div.c main.c)

# 打印日志
message (STATUS "源文件列表：${SRC_LIST}")

# 引用变量
add_executable (main ${SRC_LIST})
```

### 日志输出级别

| 级别 | 简述 |
| : ------------- | : ------------- |
| (none) | 重要信息 |
| STATUS | 附带消息 |
| WARNING | CMake 警告，继续处理 |
| AUTHOR_WARNING | CMake 警告（dev），继续处理 |
| SEND_ERROR | CMake 错误，继续处理，但会跳过生成 |
| FATAL_ERROR | CMake 错误，停止处理和生成 |

## 内置变量

- `CMAKE_SOURCE_DIR` 或 `PROJECT_SOURCE_DIR` 表示工程的根目录；
- `CMAKE_BINARY_DIR` 或 `PROJECT_BINARY_DIR` 表示编译目录。如果是内部构建，则编译目录与工程根目录相同，如果是外部构建，则表示外部构建创建的编译目录；
- `CMAKE_CURRENT_SOURCE_DIR` 表示当前处理的 `CMakeLists.txt` 所在文件夹的路径；
- `CMAKE_CURRENT_LIST_FILE` 当前 `CMakeLists.txt` 文件的完整路径；
- `CMAKE_C_COMPILER` 和 `CMAKE_CXX_COMPILER` 分别表示 C 和 C++ 编译器的路径；
- `PROJECT_NAME` 该变量可获取 `project` 命令配置的项目名；
- `EXECUTABLE_OUTPUT_PATH` 设置该变量可修改可执行程序的生成路径；
- `LIBRARY_OUTPUT_PATH` 设置该变量可修改库文件生成路径；
- `BUILD_SHARED_LIBS` 指定默认生成的库的类型。

可用 `message` 命令打印这些内置变量的值：

```ini
message (${CMAKE_SOURCE_DIR})
message (${PROJECT_SOURCE_DIR})
message (${CMAKE_BINARY_DIR})
message (${PROJECT_BINARY_DIR})
message (${CMAKE_CURRENT_SOURCE_DIR})
message (${CMAKE_CURRENT_LIST_FILE})
message (${CMAKE_C_COMPILER})
message (${CMAKE_CXX_COMPILER})
message (${PROJECT_NAME})
```

## 命令

- `add_executable` 使用给定的源文件，生成一个可执行程序；
- `add_library` 使用给定的源文件，生成一个库（静态库或共享库）；
- `add_subdirectory`  添加一个子目录，该子目录也必须包含一个 `CMakeLists.txt` 文件；
- `include_directories` 添加头文件路径；
- `add_definitions` 添加编译参数；
- `target_link_libraries` 链接指定的库；
- `find_library` 查找指定的库，并将库文件路径保存到一个变量；
- `set_target_properties` 设置目标的一些属性，从而改变构建方式；
- `link_directories` 添加库的搜索路径；
- `aux_source_directory` 查找指定路径下的所有源文件。

## 编译

首先执行 `cmake -G "MinGW Makefiles" ..` 命令自动生成 `Makefile` 文件，然后执行 `make` 命令进行编译，完成后 `build` 目录下即生成 `main.exe`。

当链接已经编译好的库时，推荐使用 `find_library` 来查找库，因为 `link_directories` 命令传入相对路径时，会直接将相对路径传给编译器，导致出现找不到问题。

`find_library` 命令原型如下，第一个参数为变量，第二个参数为库名称，最后面可以填入多个路径：

```ini
# 在指定的目录下查找名为 calc 的库，并将库文件的绝对路径保存到变量 STATIC_LIB 中
find_library(STATIC_LIB calc "${PROJECT_BINARY_DIR}/calc")
message (STATUS ${STATIC_LIB})

# 为 main 程序指定链接静态库 calc
target_link_libraries(main ${STATIC_LIB})
```

### 静态库与动态库

使用 `add_library` 命令默认生成静态库，如 `add_library (calc add.c sub.c mul.c div.c)`，亦可加上参数 `STATIC` 显式指定，如需生成动态库，则添加参数` SHARED`，如 `add_library (calc SHARED add.c sub.c mul.c div.c)`，此外，还可以通过设置变量 `BUILD_SHARED_LIBS` 来修改默认行为，当该变量为真时，默认会生成动态库，如

```ini
# 使用 option 命令定义选项
option(BUILD_SHARED_LIBS "build shared or static libraries" ON)
```

### 自动获取源码列表

当我们工程的源码非常多时，一个个去手写源码列表是非常麻烦的，以上述 `calc` 目录下的 `CMakeLists.txt` 文件为例，这时可以使用 `aux_source_directory` 命令

```ini
# 获取当前目录下的源文件路径列表，并保存到变量 SRC_LIST 中
aux_source_directory (. SRC_LIST)

# 打印
message (STATUS ${SRC_LIST})
```

该命令原型如下，第一个参数为搜索的路径，第二个参数为变量

```ini
aux_source_directory(<dir> <variable>)
```

这个命令只能识别源码文件，不能识别其他文件，比如 `.h` 文件就不能扫描出来，因此存在一定缺陷，想知道能识别哪些拓展名的源文件，可打印两个内置变量获取：

```ini
message (STATUS ${CMAKE_C_SOURCE_FILE_EXTENSIONS})
message (STATUS ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS})
```

### 递归获取文件列表

`aux_source_directory` 命令只能获取源码文件列表，且无法递归获取给定路径下的嵌套子文件夹下的各种源文件，这时可以使用 `file` 命令，结合 `GLOB_RECURSE` 参数，对指定的文件拓展名进行递归获取。

```ini
# 递归遍历当前目录下的所有 .c .cpp 后缀名的文件，并将结果列表保存到 SRC_LIST 变量中
FILE(GLOB_RECURSE SRC_LIST *.c *.cpp)
# 打印
message (STATUS ${SRC_LIST})
add_library (calc STATIC ${SRC_LIST})
```

原型如下

```ini
file(GLOB_RECURSE
     variable
     [RELATIVE path]
     [FOLLOW_SYMLINKS]
     [globbing expressions]...)
```

如不需递归，可将 `GLOB_RECURSE` 改为 `GLOB`：

### 指定库的输出名称

```ini
add_library (calc STATIC ${SRC_LIST})
# 将生成 libcalculate.a
set_target_properties(calc PROPERTIES OUTPUT_NAME "calculate")
```

### 定义宏与条件编译

可使用 `add_definitions` 命令，传入 `-D` 加上宏名称来定义宏，以下定义宏 `USER_PRO`：

```ini
# 定义宏 USER_PRO
add_definitions(-DUSER_PRO)

# 等价于 #define VER 1 、#define Foo 2
add_definitions(-DVER=1 -DFoo=2)
```

配合使用 `option` 命令，实现条件编译

```ini
option(USER_PRO "option for user" OFF)
if (USER_PRO)
add_definitions(-DUSER_PRO)
endif()
```

`option` 命令原型：

```ini
 option(<option_variable> "描述选项的帮助性文字" [initial value])
```

`add_definitions` 命令主要用来添加编译参数，`add_compile_options` 命令也具有相同的功能，示例如下：

```ini
add_compile_options(-std=c99 -Wall)
add_definitions(-std=c99 -Wall)
```
