---
date: 2022-02-16T21:39:01+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C 学习笔记"  # 文章标题
description: "纸上得来终觉浅，学到过知识点分分钟忘得一干二净，今后无论学什么，都做好笔记吧。"
url:  "posts/c/README"  # 设置网页永久链接
tags: [ "C", "README" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

# C 学习笔记

> 纸上得来终觉浅，学到过知识点分分钟忘得一干二净，今后无论学什么，都做好笔记吧。

个人体会，写 C/C++ 工程，大部分时间花在了解决依赖、解决依赖编译问题上，一搞就是半天，最终还是解决不了，浪费生命。

## 目录结构

- `assets/images`: 笔记配图
- `assets/templates`: 笔记模板
- `docs`: 基础语法
- `libraries`: 库
  - `libraries/standard`: 标准库
  - `libraries/tripartite`: 第三方库
- `quickstart`: 基础用法
- `src`: 源码示例
  - `src/docs`: 基础语法源码示例
  - `src/libraries/standard`: 标准库源码示例
  - `src/libraries/tripartite`: 第三方库源码示例
  - `src/quickstart`: 基础用法源码示例

## 基础用法

- [用 clang-format 代码格式化](quickstart/clang_format.md)

### 依赖

- [vcpkg 管理 C 和 C++ 库](quickstart/compile/vcpkg.md)

### 编译

- [Makefile 详解](quickstart/compile/Makefile.md)
- [CMake 详解](quickstart/compile/cmake.md)
- [GCC 静态链接与动态链接](quickstart/compile/link.md)
- [C 语言编译预处理命令](quickstart/compile/preprocessing_command.md)

## 基础语法

### Linux C 编程

- [第3章_GCC编译器与调试器](docs/[Linux]C/第3章_GCC编译器与调试器.md)
- [第6章_数据类型、运算符和表达式](docs/[Linux]C/第6章_数据类型、运算符和表达式.md)
- [第7章_程序控制结构](docs/[Linux]C/第7章_程序控制结构.md)
- [第8章_数组与指针](docs/[Linux]C/第8章_数组与指针.md)
- [第9章_函数](docs/[Linux]C/第9章_函数.md)
- [第10章_字符及字符串处理](docs/[Linux]C/第10章_字符及字符串处理.md)
- [第11章_结构体与共用体](docs/[Linux]C/第11章_结构体与共用体.md)
- [第12章_C++语言编程基础](docs/[Linux]C/第12章_C++语言编程基础.md)
- [第13章_文件操作](docs/[Linux]C/第13章_文件操作.md)
- [第14章_文件IO操作](docs/[Linux]C/第14章_文件IO操作.md)
- [第15章_进程控制](docs/[Linux]C/第15章_进程控制.md)
- [第16章_进程间通信](docs/[Linux]C/第16章_进程间通信.md)
- [第17章_线程控制](docs/[Linux]C/第17章_线程控制.md)

### [C++ 笔记目录](docs/CPP/README.md)

#### 第1章_C++基础入门

- [第1章_C++基础入门_初识](docs/CPP/第1章_C++基础入门_初识.md)
- [第1章_C++基础入门_变量](docs/CPP/第1章_C++基础入门_变量.md)
- [第1章_C++基础入门_函数](docs/CPP/第1章_C++基础入门_函数.md)
- [第1章_C++基础入门_数据类型](docs/CPP/第1章_C++基础入门_数据类型.md)
- [第1章_C++基础入门_运算符](docs/CPP/第1章_C++基础入门_运算符.md)
- [第1章_C++基础入门_函数程序流程结构](docs/CPP/第1章_C++基础入门_函数程序流程结构.md)
- [第1章_C++基础入门_数组](docs/CPP/第1章_C++基础入门_数组.md)
- [第1章_C++基础入门_指针](docs/CPP/第1章_C++基础入门_指针.md)
- [第1章_C++基础入门_结构体](docs/CPP/第1章_C++基础入门_结构体.md)

#### 第2章_C++学习笔记

- [第2章_C++学习笔记_动态内存](docs/CPP/第2章_C++学习笔记_动态内存.md)
- [第2章_C++学习笔记_多线程](docs/CPP/第2章_C++学习笔记_多线程.md)
- [第2章_C++学习笔记_类与对象](docs/CPP/第2章_C++学习笔记_类与对象.md)
- [第2章_C++学习笔记_命名空间](docs/CPP/第2章_C++学习笔记_命名空间.md)
- [第2章_C++学习笔记_模板](docs/CPP/第2章_C++学习笔记_模板.md)
- [第2章_C++学习笔记_日期时间](docs/CPP/第2章_C++学习笔记_日期时间.md)
- [第2章_C++学习笔记_输入输出](docs/CPP/第2章_C++学习笔记_输入输出.md)
- [第2章_C++学习笔记_数据结构](docs/CPP/第2章_C++学习笔记_数据结构.md)
- [第2章_C++学习笔记_信号处理](docs/CPP/第2章_C++学习笔记_信号处理.md)
- [第2章_C++学习笔记_异常处理](docs/CPP/第2章_C++学习笔记_异常处理.md)
- [第2章_C++学习笔记_预处理器](docs/CPP/第2章_C++学习笔记_预处理器.md)

#### 第3章_C++新特性

- [第3章_C++新特性_CPP11](docs/CPP/CPP_11/第3章_C++新特性_CPP11.md)
- [第3章_C++新特性_CPP11_新增关键字](docs/CPP/CPP_11/第3章_C++新特性_CPP11_新增关键字.md)
- [第3章_C++新特性_CPP11_左值右值](docs/CPP/CPP_11/第3章_C++新特性_CPP11_左值右值.md)
- [第3章_C++新特性_CPP11_Lambda表达式](docs/CPP/CPP_11/第3章_C++新特性_CPP11_Lambda表达式.md)
- [第3章_C++新特性_CPP11_模板](docs/CPP/CPP_11/第3章_C++新特性_CPP11_模板.md)
- [第3章_C++新特性_CPP11_线程](docs/CPP/CPP_11/第3章_C++新特性_CPP11_线程.md)
- [第3章_C++新特性_CPP11_智能指针](docs/CPP/CPP_11/第3章_C++新特性_CPP11_智能指针.md)
- [第3章_C++新特性_CPP11_列表初始化](docs/CPP/CPP_11/第3章_C++新特性_CPP11_列表初始化.md)

## 库

### 标准库

- [解析命令行参数](libraries/standard/getopt.md)

### 第三方库

- [Crypto++ 的编译与基本用法](libraries/tripartite/crypto/cryptopp.md)
- [HTTP 客户端 curl 库用法](libraries/tripartite/curl.md)
- [日志库 spdlog 基本用法](libraries/tripartite/spdlog.md)
- [CPP JSON 库 nlohmann_json 用法](libraries/tripartite/nlohmann_json.md)
- [CPP HTTP 库 httplib 用法](libraries/tripartite/httplib.md)

## 暂未分类

- [用 CPP 进行数学计算](docs/others/math.md)
- [C 语言内存管理](docs/others/memory.md)
