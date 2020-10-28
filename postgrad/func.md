---
date: 2020-10-28T21:22:34+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "计算机考研之 C/C++ 函数"  # 文章标题
url:  "posts/cpp/postgrad/func"  # 设置网页链接，默认使用文件名
tags: [ "cpp", "c" ]  # 自定义标签
series: [ "计算机考研笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 排序优先级
chapter: false  # 设置为章节

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

## 改变传入参数

C++ 有引用参数：

```c++
void func(int &x) {
    ++x;
}

int main() {
    int x = 1;
    func(x);
    cout << x << endl;
}
```

C 可以用指针参数：

```c++
void func(int *x) {
    ++*x;
}

int main() {
    int x = 1;
    func(&x);
    printf("%d", x);
}
```

## 一维数组参数

```c++
void func(int x[], int n) {
    
}
```

对于一维数组的定义，只需写出中括号即可，不需要限定数组长度，n 指参与函数加工的元素个数。

## 二维数组参数

```c++
void func(int x[][size], int n) {

}
```

对于二维数组，必须声明第二维的长度。

将数组作为参数传入函数，函数就是对传入数组本身进行操作，即如果函数体内涉及改变数组数据的操作，则传入的数组中的数据就会依照函数的操作来改变。

对于数组而言，没有引用型和非引用型之分，可以理解为数组参数都是引用型。

```c++

```

```c++

```

```c++

```

```c++

```

