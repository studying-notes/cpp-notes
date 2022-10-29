---
date: 2022-09-23T09:58:31+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "constexpr 常量表达式"  # 文章标题
url:  "posts/cpp/quickstart/feature/cpp11/constexpr"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [简介](#简介)
- [constexpr 和 const 的区别](#constexpr-和-const-的区别)
- [用法](#用法)
  - [修饰函数](#修饰函数)
  - [修饰类型](#修饰类型)
  - [修饰指针](#修饰指针)
  - [修饰引用](#修饰引用)
- [实例](#实例)
  - [switch/case 字符串](#switchcase-字符串)

## 简介

将变量声明为 constexpr 类型以便由编译器来验证变量是否是一个常量表达式，即在编译过程中就能得到计算结果的表达式。

## constexpr 和 const 的区别

是一种比 `const` 更强的约束，可以得到更好的效率和安全性。

两者都代表可读，`const` 只表示 `read only` 的语义，只保证了运行时不可以被修改，但它修饰的仍然有可能是个动态变量（编译期间是不确定的）。

而 `constexpr` 修饰的才是真正的常量，它会在编译期间就会被计算出来，整个运行过程中都不可以被改变，`constexpr` 可以用于修饰函数，这个函数的返回值会尽可能在编译期间被计算出来当作一个常量，但是如果编译期间此函数不能被计算出来，那它就会当作一个普通函数被处理。

如下代码：

```c++
#include <iostream>

constexpr int func(int i) {
  return i + 1;
}

int main() {
  int i = 4;
  // 普通函数
  std::cout << func(i) << std::endl;

  // 编译期间就会被计算出来
  std::cout << func(2) << std::endl;
}
```

## 用法

### 修饰函数

```C++
/*1.如果size在编译时能确定，那么返回值就可以是constexpr,编译通过*/
constexpr int getSizeA(int size) {
  return 4 * size;
}

/*2.编译通过，有告警：在constexpr中定义变量*/
constexpr int getSizeB(int size) {
  int index = 0;
  return 4;
}

/*3.编译通过，有告警：在constexpr中定义变量*/
constexpr int getSizeC(int size) {
  constexpr int index = 0;
  return 4;
}

/*4.编译通过，有告警：使用了if语句（使用switch也会告警）*/
constexpr int getSizeD(int size) {
  if (0) {}
  return 4;
}

///*5.定义变量并且没有初始化，编译不过*/
//constexpr int getSizeE(int size) {
//  int index;
//  return 4;
//}

///*6.rand()为运行期函数，不能在编译期确定，编译不过*/
//constexpr int getSizeF(int size) {
//  return 4 * rand();
//}
//
///*7.使用了for，编译不过*/
//constexpr int getSizeG(int size) {
//  for (; 0;) {}
//  return 4 * rand();
//}
```

### 修饰类型

```C++
#include <iostream>

/*1.如果size在编译时能确定，那么返回值就可以是constexpr,编译通过*/
constexpr int getSizeA(int size) {
  return 4 * size;
}

int main() {
  int tempA;
  std::cin >> tempA;

  const int ctempA = 4;
  const int ctempB = tempA;

  /*1.可以再编译器确定，编译通过*/
  constexpr int conexprA = 4;
  constexpr int conexprB = conexprA + 1;
  constexpr int conexprC = getSizeA(conexprA);
  constexpr int conexprD = ctempA;

  /*2.不能在编译期决定，编译不过*/
  //  constexpr int conexprE = tempA;
  //  constexpr int conexprF = ctempB;
}
```

### 修饰指针

```C++
int g_tempA = 4;
const int g_conTempA = 4;
constexpr int g_conexprTempA = 4;

int main() {
  int tempA = 4;
  const int conTempA = 4;
  constexpr int conexprTempA = 4;

  /*1.正常运行,编译通过*/
  const int *conptrA = &tempA;
  const int *conptrB = &conTempA;
  const int *conptrC = &conexprTempA;

  /*2.局部变量的地址要运行时才能确认，故不能在编译期决定，编译不过*/
  //  constexpr int *conexprPtrA = &tempA;
  //  constexpr int *conexprPtrB = &conTempA constexpr int *conexprPtrC = &conexprTempA;

  /*3.第一个通过，后面两个不过,因为constexpr int *所限定的是指针是常量，故不能将常量的地址赋给顶层const*/
  constexpr int *conexprPtrD = &g_tempA;
  //  constexpr int *conexprPtrE = &g_conTempA constexpr int *conexprPtrF = &g_conexprTempA;

  /*4.局部变量的地址要运行时才能确认，故不能在编译期决定，编译不过*/
  //  constexpr const int *conexprConPtrA = &tempA;
  //  constexpr const int *conexprConPtrB = &conTempA;
  //  constexpr const int *conexprConPtrC = &conexprTempA;

  /*5.正常运行，编译通过*/
  constexpr const int *conexprConPtrD = &g_tempA;
  constexpr const int *conexprConPtrE = &g_conTempA;
  constexpr const int *conexprConPtrF = &g_conexprTempA;

  return 0;
}
```
 
### 修饰引用

```C++
int g_tempA = 4;
const int g_conTempA = 4;
constexpr int g_conexprTempA = 4;

int main(void) {
  int tempA = 4;
  const int conTempA = 4;
  constexpr int conexprTempA = 4;

  /*1.正常运行，编译通过*/
  const int &conptrA = tempA;
  const int &conptrB = conTempA;
  const int &conptrC = conexprTempA;

  /*2.有两个问题：一是引用到局部变量，不能再编译器确定；二是conexprPtrB和conexprPtrC应该为constexpr const类型，编译不过*/
  //  constexpr int &conexprPtrA = tempA;
  //  constexpr int &conexprPtrB = conTempA
  //      constexpr int &conexprPtrC = conexprTempA;

  /*3.第一个编译通过，后两个不通过，原因是因为conexprPtrE和conexprPtrF应该为constexpr const类型*/
  constexpr int &conexprPtrD = g_tempA;
  //  constexpr int &conexprPtrE = g_conTempA;
  //  constexpr int &conexprPtrF = g_conexprTempA;

  /*4.正常运行，编译通过*/
  constexpr const int &conexprConPtrD = g_tempA;
  constexpr const int &conexprConPtrE = g_conTempA;
  constexpr const int &conexprConPtrF = g_conexprTempA;

  return 0;
}
```

## 实例

### switch/case 字符串

在 c++中，是不能用字符串来作为 case 的标签的。

c++ 11 引入了 constexpr 和自定义文字常量，将这两个新特性结合，可以实现类似的功能。

基本原理是将字符串进行哈希，转换为整数。

```c++
#include <iostream>

typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char const *str) {
  hash_t ret{basis};

  while (*str) {
    ret ^= *str;
    ret *= prime;
    str++;
  }

  return ret;
}

constexpr hash_t hash(char const *str, hash_t last = basis) {
  return *str ? hash(str + 1, (*str ^ last) * prime) : last;
}

constexpr unsigned long long operator"" _hash(char const *p, size_t) {
  return hash(p);
}

void switch_string(char const *str) {
  switch (hash_(str)) {
  case "first"_hash:
    std::cout << 1 << std::endl;
    break;
  case "second"_hash:
    std::cout << 2 << std::endl;
    break;
  case "third"_hash:
    std::cout << 3 << std::endl;
    break;
  default:
    std::cout << 0 << std::endl;
  }
}

int main() {
  switch_string("first");

  return 0;
}
```

```c++

```

```c++

```
