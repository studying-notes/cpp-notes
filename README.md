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

## 基础语法

## C 语言编程基础

- [编译器与调试器](docs/编译器与调试器.md)
- [C语言程序结构](docs/C语言程序结构.md)
- [数据类型、运算符和表达式](docs/数据类型、运算符和表达式.md)
- [预处理命令](docs/预处理命令.md)
- [程序控制结构](docs/程序控制结构.md)
  - [数据的输入与输出](docs/程序控制结构.md#数据的输入与输出)
- [数组与指针](docs/数组与指针.md)
- [函数](docs/函数.md)
- [字符及字符串处理](docs/字符及字符串处理.md)
- [结构体与共用体](docs/结构体与共用体.md)
- [内存管理](docs/内存管理.md)

## C++ 语言编程基础

- [C++语言编程基础](docs/C++语言编程基础.md)
- [C++的特性](docs/C++的特性.md)
  - [运算符重载](docs/C++的特性.md#运算符重载)
  - [继承](docs/C++的特性.md#继承)
  - [虚拟函数和多态性](docs/C++的特性.md#虚拟函数和多态性)
  - [流输入与输出](docs/C++的特性.md#流输入与输出)
  - [模板](docs/C++的特性.md#模板)
  - [异常处理](docs/C++的特性.md#异常处理)
- [C++函数](docs/C++函数.md)
- [C++概述](docs/C++概述.md)
- [C++命名空间](docs/C++命名空间.md)
- [C++结构体](docs/C++结构体.md)

## 库

## 标准库

- [解析命令行参数](libraries/standard/getopt.md)

### Linux 系统编程

- [文件操作](docs/文件操作.md)
  - [打开、新建和关闭操作](docs/文件操作.md#打开文件、新建文件和关闭文件操作)
  - [文件状态和属性操作](docs/文件操作.md#文件状态和属性操作)
  - [目录操作](docs/文件操作.md#目录操作)
  - [删除目录或文件操作](docs/文件操作.md#删除目录或文件操作)
  - [错误处理](docs/文件操作.md#错误处理)
- [文件IO操作](docs/文件IO操作.md)
  - [读取文件](docs/文件IO操作.md#读取文件)
  - [写入文件](docs/文件IO操作.md#写入文件)
  - [随机读写文件](docs/文件IO操作.md#随机读写文件)
  - [缓冲文件操作](docs/文件IO操作.md#缓冲文件操作)
  - [打开与关闭文件流](docs/文件IO操作.md#打开与关闭文件流)
  - [读取与写入文件流](docs/文件IO操作.md#读取与写入文件流)
  - [文件流的格式化输入与输出](docs/文件IO操作.md#文件流的格式化输入与输出)
  - [文件流的定位操作](docs/文件IO操作.md#文件流的定位操作)
  - [文件流操作的其他函数](docs/文件IO操作.md#文件流操作的其他函数)
  - [文件流操作的错误处理](docs/文件IO操作.md#文件流操作的错误处理)
- [进程控制](docs/进程控制.md)
  - [进程的基本操作](docs/进程控制.md#进程的基本操作)
    - [fork系统调用](docs/进程控制.md#fork系统调用)
    - [exec系统调用](docs/进程控制.md#exec系统调用)
    - [exit系统调用](docs/进程控制.md#exit系统调用)
    - [wait系统调用](docs/进程控制.md#wait系统调用)
    - [sleep函数调用](docs/进程控制.md#sleep函数调用)
  - [进程的特殊操作](docs/进程控制.md#进程的特殊操作)
    - [获得进程ID](docs/进程控制.md#获得进程ID)
    - [setuid和setgid系统调用](docs/进程控制.md#setuid和setgid系统调用)
    - [setpgrp和setpgid系统调用](docs/进程控制.md#setpgrp和setpgid系统调用)
    - [chdir系统调用](docs/进程控制.md#chdir系统调用)
    - [chroot系统调用](docs/进程控制.md#chroot系统调用)
    - [nice系统调用](docs/进程控制.md#nice系统调用)
- [进程间通信](docs/进程间通信.md)
  - [进程间使用管道通信](docs/进程间通信.md#进程间使用管道通信)
    - [pipe系统调用](docs/进程间通信.md#pipe系统调用)
    - [dup系统调用](docs/进程间通信.md#dup系统调用)
- [线程控制](docs/线程控制.md)
  - [POSIX线程库](docs/线程控制.md#POSIX线程库)
    - [创建线程](docs/线程控制.md#创建线程)
    - [结束线程](docs/线程控制.md#结束线程)
  - [同步](docs/线程控制.md#同步)
    - [用信号量进行同步](docs/线程控制.md#用信号量进行同步)
    - [用互斥量进行同步](docs/线程控制.md#用互斥量进行同步)
    - [取消线程](docs/线程控制.md#取消线程)
    - [多线程的实现](docs/线程控制.md#多线程的实现)

## 第三方库

- [Crypto++ 的编译与基本用法](libraries/tripartite/crypto/cryptopp.md)
- [HTTP 客户端 curl 库用法](libraries/tripartite/curl.md)

## 暂未分类

- [Clion与WSL设置](docs/Clion与WSL设置.md)
- [CmakeList 的编写和参数详解](docs/CmakeList的编写和参数详解.md) 
- [静态链接与动态链接](docs/静态链接与动态链接.md)
- [数学表达式](docs/数学表达式.md)
