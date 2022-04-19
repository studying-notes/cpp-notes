---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP11_列表初始化"
url:  "posts/cpp/docs/CPP/CPP_11/第3章_C++新特性_CPP11_列表初始化"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [列表初始化](#列表初始化)
- [列表初始化的一些规则](#列表初始化的一些规则)
  - [聚合类型](#聚合类型)
- [std::initializer_list](#stdinitializer_list)
- [列表初始化的好处](#列表初始化的好处)
  - [什么是类型窄化](#什么是类型窄化)

## 列表初始化

在 C++11 中可以直接在变量名后面加上初始化列表来进行对象的初始化。

```c++
struct A {
public:
  A(int) {}

private:
  A(const A &) {}
};

int main() {
  A a(123);
  A b = 123;// error
  A c = {123};
  A d{123};// c++11

  int e = {123};
  int f{123};// c++11

  return 0;
}
```

列表初始化也可以用在函数的返回值上：

```c++
#include <vector>

std::vector<int> func() {
  return {};
}
```

## 列表初始化的一些规则

聚合类型可以进行直接列表初始化。

### 聚合类型

1. 类型是一个普通数组，如 `int[5]`，`char[]`，`double[]` 等
2. 类型是一个类，且满足以下条件：

- 没有用户声明的构造函数
- 没有用户提供的构造函数(允许显示预置或弃置的构造函数)
- 没有私有或保护的非静态数据成员
- 没有基类
- 没有虚函数
- 没有{}和=直接初始化的非静态数据成员
- 没有默认成员初始化器

```c++
struct A {
  int a;
  int b;
  int c;
  A(int, int) {}
};

int main() {
  A a{1, 2, 3};// error，A有自定义的构造函数，不能列表初始化
}
```

上述代码类 A 不是聚合类型，无法进行列表初始化，必须以自定义的构造函数来构造对象。

```c++
struct A {
    int a;
    int b;
    virtual void func() {} // 含有虚函数，不是聚合类
};

struct Base {};
struct B : public Base { // 有基类，不是聚合类
    int a;
    int b;
};

struct C {
    int a;
    int b = 10; // 有等号初始化，不是聚合类
};

struct D {
    int a;
    int b;
    private:
    int c; // 含有私有的非静态数据成员，不是聚合类
};

struct E {
    int a;
    int b;
    E() : a(0), b(0) {} // 含有默认成员初始化器，不是聚合类
};
```

上面列举了一些不是聚合类的例子，对于一个聚合类型，使用列表初始化相当于对其中的每个元素分别赋值；对于非聚合类型，需要先自定义一个对应的构造函数，此时列表初始化将调用相应的构造函数。

## std::initializer_list

平时开发使用 STL 过程中可能发现它的初始化列表可以是任意长度，大家有没有想过它是怎么实现的呢，答案是 std::initializer_list，看下面这段示例代码：

```c++
struct CustomVec {
    std::vector<int> data;
    CustomVec(std::initializer_list<int> list) {
        for (auto iter = list.begin(); iter != list.end(); ++iter) {
            data.push_back(*iter);
        }
    }
};
```

这个 std::initializer_list 其实也可以作为函数参数。

`std::initializer_list<T>`，它可以接收任意长度的初始化列表，但是里面必须是相同类型 T，或者都可以转换为 T。

## 列表初始化的好处

列表初始化的好处如下：

1. 方便，且基本上可以替代括号初始化
2. 可以使用初始化列表接受任意长度
3. 可以防止类型窄化，避免精度丢失的隐式类型转换

### 什么是类型窄化

列表初始化通过禁止下列转换，对隐式转化加以限制：

- 从浮点类型到整数类型的转换
- 从 long double 到 double 或 float 的转换，以及从 double 到 float 的转换，除非源是常量表达式且不发生溢出
- 从整数类型到浮点类型的转换，除非源是其值能完全存储于目标类型的常量表达式
- 从整数或无作用域枚举类型到不能表示原类型所有值的整数类型的转换，除非源是其值能完全存储于目标类型的常量表达式

示例：

```c++
int main() {
    int a = 1.2; // ok
    int b = {1.2}; // error

    float c = 1e70; // ok
    float d = {1e70}; // error

    float e = (unsigned long long)-1; // ok
    float f = {(unsigned long long)-1}; // error
    float g = (unsigned long long)1; // ok
    float h = {(unsigned long long)1}; // ok

    const int i = 1000;
    const int j = 2;
    char k = i; // ok
    char l = {i}; // error

    char m = j; // ok
    char m = {j}; // ok，因为是const类型，这里如果去掉const属性，也会报错
}
```

打印如下：

```c++
test.cc:24:17: error: narrowing conversion of ‘1.2e+0’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
    int b = {1.2};
                ^
test.cc:27:20: error: narrowing conversion of ‘1.0000000000000001e+70’ from ‘double’ to ‘float’ inside { } [-Wnarrowing]
     float d = {1e70};

test.cc:30:38: error: narrowing conversion of ‘18446744073709551615’ from ‘long long unsigned int’ to ‘float’ inside { } [-Wnarrowing]
    float f = {(unsigned long long)-1};
                                     ^
test.cc:36:14: warning: overflow in implicit constant conversion [-Woverflow]
    char k = i;
             ^
test.cc:37:16: error: narrowing conversion of ‘1000’ from ‘int’ to ‘char’ inside { } [-Wnarrowing]
    char l = {i};
```
