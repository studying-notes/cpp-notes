---
date: 2020-10-09T12:48:02+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: GCC 静态链接与动态链接"  # 文章标题
url:  "posts/cpp/quickstart/link"  # 设置网页链接，默认使用文件名
tags: [ "cpp", "c" ]  # 自定义标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 文章在章节中的排序优先级，正序排序
chapter: false  # 将页面设置为章节

index: true  # 文章是否可以被索引
draft: false  # 草稿
toc: true  # 是否自动生成目录
---

链接就是把目标文件与一些库文件生成可执行文件的一个过程。

## 静态链接

静态链接是由链接器在链接时将库的内容加入到可执行程序中的做法。链接器是一个独立程序，将一个或多个库或目标文件（先前由编译器或汇编器生成）链接到一块生成可执行程序。这里的库指的是静态链接库，Windows 下以 `.lib` 为后缀，Linux 下以 `.a` 为后缀。

### 优点

- 代码装载速度快，执行速度略比动态链接库快；
- 只需保证在开发者的计算机中有正确的 `.lib` 文件，在以二进制形式发布程序时不需考虑在用户的计算机上 `.lib` 文件是否存在及版本问题。

### 缺点

- 使用静态链接生成的可执行文件体积较大，包含相同的公共代码，造成浪费。

## 动态链接

动态链接（`Dynamic Linking`），把链接这个过程推迟到了运行时再进行，在可执行文件装载时或运行时，由操作系统的装载程序加载库。这里的库指的是动态链接库，Windows下以 `.dll` 为后缀，Linux 下以 `.so` 为后缀。值得一提的是，在 Windows 下的动态链接也可以用到 `.lib` 为后缀的文件，但这里的 `.lib` 文件叫做导入库，是由 `.dll` 文件生成的。

### 优点

- 生成的可执行文件较静态链接生成的可执行文件小；
- 适用于大规模的软件开发，使开发过程独立、耦合度小，便于不同开发者和开发组织之间进行开发和测试；
- 不同编程语言编写的程序只要按照函数调用约定就可以调用同一个DLL函数；
- DLL 文件与 EXE 文件独立，只要输出接口不变（即名称、参数、返回值类型和调用约定不变），更换 DLL 文件不会对 EXE 文件造成任何影响，因而极大地提高了可维护性和可扩展性。

### 缺点

- 使用动态链接库的应用程序不是自完备的，它依赖的 DLL 模块也要存在，如果使用载入时动态链接，程序启动时发现 DLL 不存在，系统将终止程序并给出错误信息；
- 速度比静态链接慢。

## Windows 下的链接实验

以 Windows 平台搭配 `MinGW` 来演示，首先创建编写如下三个文件：

`main.c`

```c
#include "test.h"

int main(void) {
    print_hello();
    system("pause");
    return 0;
}
```

`test.c`

```c
#include "test.h"

void print_hello(void) {
    printf("hello world\n");
}
```

`test.h`

```c
#ifndef __TEST_H
#define __TEST_H

#include <stdio.h>
#include <stdlib.h>

void print_hello(void);

#endif
```

文件如下：

```shell
> ls
main.c  test.c  test.h
```

### 静态链接

```shell
> gcc -c test.c main.c
> ls
main.c  main.o  test.c  test.h  test.o
```

编译、汇编指定的源文件，将每一个源文件编译成对应的目标文件。此时文件夹下多出了 `test.o` 和 `main.o` 文件。

接下来使用 `ar` 工具把 `test.o` 和 `main.o` 打包成一个静态库文件 `lib_test.lib`，输入命令：

```shell
> ar rv lib_test.lib test.o main.o
ar: creating lib_test.lib
a - test.o
a - main.o
```

```shell
> ls
lib_test.lib  main.c  main.o  test.c  test.h  test.o
```

然后把这个静态库链接成可执行文件 `lib_test.exe`，输入命令：

```shell
> gcc lib_test.lib -o lib_test.exe
> ls
lib_test.exe  lib_test.lib  main.c  main.o  test.c  test.h  test.o
```

此时文件夹下多出了可执行文件 `lib_test.exe`，双击运行与预期一致。说明静态链接的方式生成的可执行文件没问题。这个可执行文件的运行并不依赖于 `lib_test.lib` 文件，我们可以试着把这个文件删除之后再运行，仍然可以正常运行。

### 动态链接

我们把 `test.c` 编译成动态库文件 `dll_test.dll`，输入命令：

```shell
> gcc test.c -shared -o dll_test.dll
>ls
dll_test.dll  lib_test.lib  main.o  test.h  lib_test.exe  main.c  test.c  test.o
```

我们用该动态库文件 `dll_test.dll` 与 `main.c` 一起编译生成可执行文件 `dll_test.exe`，输入命令：

```c
> gcc dll_test.dll main.c -o dll_test.exe
>ls
dll_test.dll  lib_test.exe  main.c  test.c  test.o
dll_test.exe  lib_test.lib  main.o  test.h
```

这个可执行文件的运行依赖于 `dll_test.dll` 文件，把这个文件删除之后再运行就会出错。那是因为使用动态链接库的应用程序不是自完备的，它依赖的 DLL 模块也要存在。
