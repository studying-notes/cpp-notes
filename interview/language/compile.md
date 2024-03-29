---
date: 2022-10-28 13:54:16+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "编译"  # 文章标题
url:  "posts/cpp/interview/language/compile"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 编译和链接的区别是什么

在多道程序环境中，要想将源代码变成一个可执行的程序，通常分为 3 个步骤：编译、链接、载入。

1. 编译：将预处理生成的文件，经过词法分析、语法分析、语义分析以及优化后编译成若干个目标模块。可以理解为将高级语言翻译为计算机可以理解的二进制代码，即机器语言。

2. 链接：由链接程序将编译后形成的一组目标模块以及它们所需要的库函数链接在一起，形成一个完整的载入模型。**链接主要解决模块间的相互引用问题**，分为**地址和空间分配**，**符号解析**和**重定位**几个步骤。在编译阶段生成目标文件时，会暂时搁置那些外部引用，而这些外部引用就是在链接时进行确定的，链接器在链接时，会根据符号名称去相应模块中寻找对应符号。待符号确定之后，链接器会重写之前那些未确定的符号的地址，这个过程就是重定位。链接一般分为静态链接、载入时动态链接以及运行时动态链接 3 种。

3. 载入：由载入程序将载入模块载入内存。

编译和链接是为了将用户程序从硬盘上调入内存并将其转换成可执行程序服务的。用编译器时的 compile 就是在进行编译，link 就是链接，运行程序可以看到。

以 C/C++ 语言为例，把源文件编译成中间代码文件，在 Windows 下面为 .obj 文件，在 UNIX、Linux 下面就是.o 文件，即 Object File，该动作被称为编译。然后再把大量的 Object File 合成执行文件，这个动作称为链接。

编译时，编译器需要的是语法正确，函数与变量的声明正确。而一般来说，每个源文件都应该对应于一个中间目标文件（.o 文件或是.obj 文件）。链接时，主要是链接函数和全局变量，所以可以使用这些中间目标文件（.o 文件或是.obj 文件）来链接应用程序。链接就是那些目标文件之间相互链接自己所需要的函数和全局变量，而函数可能来源于其他目标文件或库文件。

## 编译型语言与解释型语言的区别是什么

编译型语言：编译是指在应用源程序执行前，就将程序源代码“翻译”成目标代码（机器语言），因此其目标程序可以脱离其语言环境独立执行，使用比较方便、效率较高。

解释型语言：在解释型语言的实现中，翻译器并不产生目标机器代码，而是产生易于执行的中间代码。这种中间代码与机器代码是不同的，中间代码的解释是由软件支持的，不能直接使用硬件，软件解释器通常会导致执行效率较低。用解释型语言编写的程序是由另一个可以理解中间代码的解释程序执行的。与编译程序不同的是，解释程序的任务是逐一将源程序的语句解释成可执行的机器指令，不需要将源程序翻译成目标代码后再执行。

## 如何判断一段程序是由 C 编译程序，还是由 C++ 编译程序编译的

如果编译器在编译 cpp 文件，那么 `_cplusplus` 就会被定义，如果是一个 C 文件在被编译，那么 `__STDC__` 就会被定义。`__STDC__` 是预定义宏，当它被定义后，编译器将按照 ANSIC 标准编译 C 语言程序。

```c++
#include <iostream>

int main() {
#ifdef __cplusplus
  std::cout << "C++" << std::endl;
#else
  std::cout << "C" << std::endl;
#endif

  return 0;
}
```

编写 C 与 C++ 兼容的代码所需的宏如下：

```c++
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
// 代码
#ifdef __cplusplus
}
#endif

int main() {
  std::cout << "Hello World!" << std::endl;
  return 0;
}
```

## C++ 程序中调用被 C 编译器编译后的函数，为什么要加 extern“C”

C++ 语言是一种面向对象编程语言，支持函数重载，而 C 语言是面向过程的编程语言，不支持函数重载，所以函数被 C++ 编译后在库中的名字与 C 语言的不同。

如果声明一个 C 语言函数 `float f(int a,char b)`，C++ 的编译器就会将这个名字变成像 `_f_int_char` 之类的东西，以支持函数重载。然而，C 语言编译器的库一般不进行该转换，所以它的内部名为 `_f`，这样链接器将无法解释 C++ 对函数 f() 的调用。

C++提供了C 语言 Alternate linkage specification（替代连接说明）符号 extern“C”来解决名字匹配问题，它会告诉编译器使用 C 的规则，而不是 C++ 的规则。

## 两段代码共存于一个文件，编译时有选择地编译其中的一部分，如何实现

可以通过以下两种方法实现：

1. 在源码中使用条件编译语句，然后在程序文件中定义宏的形式来选择需要的编译代码。

2. 在源码中使用条件编译语句，然后在编译命令的命令中加入宏定义命令来实现选择编译。

```c++

```
