---
date: 2022-10-29T13:54:53+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "数组定义"  # 文章标题
url:  "posts/cpp/algorithm/structures/array"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 简介

高级语言中常用数组来表示顺序表。

## 获取数组长度

宏定义函数：

```c
#define len(array) (sizeof(array) / sizeof(array[0]))
```

下面的方法是错误的：

```c
int len(int array[]) {
  return sizeof(array) / sizeof(array[0]);
}
```

因为数组名是指向数组首元素的指针，所以 `sizeof(array)` 的值是指针的大小，而不是数组的大小。

## 打印一维数组元素

```c++
#include <stdio.h>

void print_array(const int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[length - 1]);
}
```

## 打印二维数组

### 一次循环法

```c++
#include <stdio.h>

int main() {
  const int m = 4, n = 5;

  int array[m][n] = {1, 2, 3, 4, 5,
                     6, 7, 8, 9, 10,
                     11, 12, 13, 14, 15,
                     16, 17, 18, 19, 20};

  for (int i = 0; i < m * n; ++i) {
    printf("%d ", array[i / n][i % n]);

    if ((i + 1) % n == 0)
      printf("\n");
  }

  return 0;
}
```

## 交换数组元素

### 临时变量法

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}
```

### 加减运算法

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] = array[j] + array[i];
    array[i] = array[j] - array[i];
    array[j] = array[j] - array[i];
  }
}
```

### 位运算法

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] = array[j] ^ array[i];
    array[i] = array[j] ^ array[i];
    array[j] = array[j] ^ array[i];
  }
}
```
