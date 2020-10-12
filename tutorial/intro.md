---
date: 2020-10-09T12:48:02+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C++ 概述"  # 文章标题
description: "介绍了最简单的 C++ 程序"
url:  "posts/cpp/tutorial/intro"  # 设置网页链接，默认使用文件名
tags: [ "cpp", "intro" ]  # 自定义标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 文章在章节中的排序优先级，正序排序
chapter: false  # 将页面设置为章节

index: true  # 文章是否可以被索引
draft: true  # 草稿
toc: true  # 是否自动生成目录
---

> 输入圆的半径，求圆的周长和面积。

## 结构化方法编程

```c++
#include <iostream>

using namespace std;

int main() {
    double r, girth, area;
    const double PI = 3.14159;

    cout << "Please input radius:\n";
    cin >> r;

    girth = 2 * PI * r;
    area = PI * r * r;

    cout << "radius=" << r << endl;
    cout << "girth=" << girth << endl;
    cout << "area=" << area << endl;
    return 0;
}

// Please input radius:
// 3
// radius=3
// girth=18.8495
// area=28.2743
```

第 1 行称为预编译指令，说明该程序要使用的外部文件。C ++语言标准头文件 iostream 包含了程序常用的输入 cin 和输出 cout 的定义。

第 2 行是使用名空间的声明。using 和 namespace 都是关键字，std 是系统提供的标准命名空间。

C++ 语言以函数为程序运行的基本单位。

## 面向对象方法编程

当我们用对象思维考虑问题时，可以对问题进一步抽象。所有称为“圆”的这种类型的几何图形，最基本的要素是半径。它决定了圆的大小，也是区分具体圆 A、圆 B、圆 C 等的基本数据。一旦定义了具体的有半径值的圆，就有它特定的周长和面积了。

“圆”是一种类型。在面向对象方法中，称为“类类型”或“类”。“圆”类型的基本数据是“半径”。类的数据称为“属性”或“数据成员”。

数据成员有了具体的值之后，就可以计算周长和面积了。这种“计算”由程序代码实现，并且“封装”在类中，称为类的“方法”或“成员函数”。

```c++
#include <iostream>

using namespace std;

class Circle {
    double radius;
public:
    void Set_Radius(double r) {
        radius = r;
    }

    double Get_Radius() const {
        return radius;
    }

    double Get_Girth() const {
        return 2 * 3.14 * radius;
    }

    double Get_Area() const {
        return 3.14 * radius * radius;
    }
};

int main() {
    Circle A{}, B{};

    A.Set_Radius(3);
    cout << "A.Radius=" << A.Get_Radius() << endl;
    cout << "A.Girth=" << A.Get_Girth() << endl;
    cout << "A.Area=" << A.Get_Area() << endl;

    B.Set_Radius(3);
    cout << "B.Radius=" << B.Get_Radius() << endl;
    cout << "B.Girth=" << B.Get_Girth() << endl;
    cout << "B.Area=" << B.Get_Area() << endl;

    return 0;
}
```

该例程首先说明一个类 Circle。类中数据成员 radius 用于定义半径。成员函数 Set_Radius 用于设置半径的值，Get_Radius 获取半径，Get_Girth 计算并返回圆周长，Get_Area 计算并返回圆面积。

主函数中说明了圆类 Circle 的两个圆：A 和 B。A 和 B 称为 Circle 类的实例或对象。main 函数中由对象调用成员函数输出两个圆的半径、周长和面积。

这个程序看起来要烦琐一些。但是，以 Circle 类为基础，可以很方便地派生新的类。新的类对原有类的特性不需要重定义，可以自己定义新的数据，例如，指定圆心坐标，填充圆的颜色；派生出球体、圆柱体等新的几何体。每个新类都可以拥有自己的成员函数，实现自己特有的功能，这是结构化程序设计方法所做不到的。面向对象技术提供了软件重用、解决大问题和复杂问题的有效途径。

## C++ 语言的字符集与词汇

由字符可以组成“词”，由词组成“表达式”、“句子”，由各种句子又可以构成“函数”、“程序”。

### 字符集

C++ 语言的字符集是 ASCII 码的子集：

- 26 个小写字母 abcdefghijklmnopqrstuvwxyz
- 26 个大写字母 ABCDEFGHIJKLMNOPQRSTUVWⅩYZ
- 10 个数字 0123456789
- 空格 !"＃%&'()*+-/:;<=>?[\]^_{|}～.

### 词汇

单词是语言中有意义的最小语法单位。根据构成规则，一个单词由一个或多个字符组成。

### 常数

常数是指按照特定类型语法规则解释的数据值。C++语言常数有数值、字符和字符串。数据的书写形式表示了它的类型和值。

基本类型的常数在程序运行时直接参与运算，不需占用内存单元存储。

## C++ 语言的数据类型

```c++

```


```c++

```


```c++

```


```c++

```


```c++

```


