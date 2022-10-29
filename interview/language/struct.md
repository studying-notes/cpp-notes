---
date: 2022-10-26 14:29:30+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "结构体与类"  # 文章标题
url:  "posts/cpp/interview/language/struct"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## C 语言中 struct 与 union 的区别是什么

struct（结构体）与 union（联合体）是 C 语言中两种不同的数据结构，两者都是常见的复合结构，其区别主要表现在以下两个方面。

1. 结构体与联合体虽然都是由多个不同的数据类型成员组成的，但不同之处在于联合体中所有成员共用一块地址空间，即联合体只存放了一个被选中的成员，而结构体中所有成员占用空间是累加的，其所有成员都存在，不同成员会存放在不同的地址。在计算一个结构型变量的总长度时，其内存空间大小等于所有成员长度之和（需要考虑字节对齐），而在联合体中，所有成员不能同时占用内存空间，它们不能同时存在，所以一个联合型变量的长度等于其最长的成员的长度。

2. 对于联合体的不同成员赋值，将会对它的其他成员重写，原来成员的值就不存在了，而对结构体的不同成员赋值是互不影响的。

```c++
#include <iostream>

typedef union {
  double i; // 8 bytes
  int k[5]; // 20 bytes
  char c;  // 1 byte
} DATE; // 24 bytes

typedef struct data {
  int cat; // 4 bytes
  DATE cow; // 24 bytes
  double dog; // 8 bytes
} too; // 40 bytes

int main() {
  DATE max;

  std::cout << "Size of DATE: " << sizeof(max) << std::endl;
  std::cout << "Size of too: " << sizeof(too) << std::endl;

  return 0;
}
```

```
Size of DATE: 24
Size of too: 40
```

假设为 32 位机器，int 型占 4 个字节，double 型占 8 个字节，char 型占 1 个字节，而 DATE 是一个联合型变量，联合型变量共用空间，union 里面最大的变量类型是 `int[5]`，所以占用 20 个字节，它的大小是 20，而由于 union 中 double 占了 8 个字节，因此 union 是要 8 个字节对齐，所占内存空间为 8 的倍数。为了**实现 8 个字节对齐**，所占空间为 24。

而 data 是一个结构体变量，每个变量分开占用空间，依次为 `sizeof(int)+sizeof(DATE)+sizeof(double) = 4+24+8 = 36`，按照 8 字节对齐，占用空间为 40。

## C 和 C++ 中 struct 的区别是什么

C 语言中的 struct 与 C++ 语言中的 struct 的区别表现在以下 3 个方面。

1. C 语言的 struct 不能有函数成员，而 C++ 语言的 struct 可以有。

2. C 语言的 struct 中数据成员没有 private、public 和 protected 访问权限的设定，而 C++ 语言的 struct 的成员有访问权限设定。

3. C 语言的 struct 是没有继承关系的，而 C++ 语言的 struct 却有丰富的继承关系。

C 语言中的 struct 是用户自定义数据类型（User Defined Type），它是没有权限设置的，它只能是一些变量的集合体，虽然可以封装数据，却不可以隐藏数据，而且成员不可以是函数。为了和 C 语言兼容，C++ 语言中就引入了 struct 关键字。C++ 语言中的 struct 是抽象数据类型（ADT），它支持成员函数的定义，同时增加了访问权限，它的成员函数的默认访问权限为 public。

在用模板的时候，只能写 `template<class Type>` 或 `template<typename Type>`，不能写 `template<struct Type>`。

## C++ 中 struct 与 class 的区别是什么

如果没有多态和虚拟继承，在 C++ 语言中，struct 和 class 的存取效率完全相同，存取 class 的数据成员与非虚函数效率和 struct 完全相同，不管该数据成员是定义在基类，还是定义在派生类。

class 的数据成员在内存中的布局不一定是数据成员的声明顺序，C++ 只保证处于同一个 access section 的数据成员按照声明顺序排列。

具体而言，在 C++ 语言中，class 和 struct 做类型定义时只有以下 3 点区别。

1. 默认继承权限：class 继承默认是 private 继承，而 struct 继承默认是 public 继承。

2. 数据访问权限：struct 作为数据结构的实现体，它的默认数据访问控制是 public，而 class 作为对象的实现体，它的默认成员变量访问控制是 private。

3. class 还用于定义模板参数，就像 typename，但关键字 struct 不用于定义模板参数。

C++ 中之所以保留 struct 关键字，主要有两方面原因：第一，保证与 C 语言的向下兼容性， C++ 必须提供一个 struct ；第二，class 表示的是一个实体（实体有数据和操作），而 struct 表示的是数据，当仅仅需要创建一个数据结构，而没有附加的操作的时候，使用 struct 更好，因此， struct 可以被看作是一个轻量级的 class。

```c++

```
