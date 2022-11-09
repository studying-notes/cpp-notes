---
date: 2022-11-02T13:31:19+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "线性表的顺序表示"  # 文章标题
url:  "posts/cpp/algorithm/structures/linear_list/contiguous_list"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 顺序表的定义

线性表的顺序存储又称顺序表。它是用一组地址连续的存储单元依次存储线性表中的数据元素，从而使得逻辑上相邻的两个元素在物理位置上也相邻。第 1 个元素存储在线性表的起始位置，第 i 个元素的存储位置后面紧接着存储的是第 i+1 个元素，称 i 为元素 ai 在线性表中的位序。

位序是从 1 开始的，而不是从 0 开始的，等于下标加 1。

因此，顺序表的特点是表中元素的逻辑顺序与物理顺序一致。

### 静态分配数组

```c++
#define MaxSize 50 // 顺序表的最大长度

typedef int ElemType; // 元素类型

typedef struct {
  ElemType data[MaxSize]; // 顺序表的数据域
  int length; // 顺序表的长度
} SqList; // 顺序表的类型定义
```

### 动态分配数组

```c++
#define InitSize 50 // 顺序表的初始长度

typedef int ElemType; // 元素类型

typedef struct {
  ElemType *data; // 顺序表的数据域
  int MaxSize; // 顺序表的最大长度
  int length; // 顺序表的长度
} SqList; // 顺序表的类型定义

int main() {
  SqList L;

  // C 初始化语句
  L.data = (ElemType *) malloc(sizeof(ElemType) * InitSize);

    // C++ 初始化语句
  L.data = new ElemType[InitSize];

  return 0;
}
```

## 顺序表上基本操作的实现

### 插入操作

```c++
bool ListInsert(SqList &L, int i, ElemType e) {
  if (i < 1 || i > L.length + 1) { // 判断插入位置是否合法
    return false;
  }

  if (L.length >= MaxSize) { // 判断顺序表是否已满
    return false;
  }

  for (int j = L.length; j >= i; j--) { // 将第i个元素及其后面的元素后移
    L.data[j] = L.data[j - 1];
  }

  L.data[i - 1] = e; // 将e插入到第i个位置
  L.length++;       // 顺序表长度加1

  return true;
}
```

这里是静态分配数组的插入操作。

如果是动态分配数组，当顺序表满时，需要重新分配一个更大的数组，将原数组中的元素复制到新数组中，再释放原数组。

比如，原顺序表长度 n，需要再插入 m 个元素，在申请时需申请 n+m 个连续的存储空间，然后将线性表原来的 n 个元素复制到新申请的 n+m 个连续的存储空间的前 n 个单元。

### 删除操作

```c++
bool ListDelete(SqList &L, int i, ElemType &e) {
  if (i < 1 || i > L.length) {// 判断i是否合法
    return false;
  }

  e = L.data[i - 1];// 将被删除的元素赋值给e

  for (int j = i; j < L.length; ++j) {// 将第i个元素后面的元素前移
    L.data[j - 1] = L.data[j];
  }

  L.length--;// 顺序表长度减1

  return true;
}
```

### 查找操作

```c++
int LocateElem(SqList L, ElemType e) {
  for (int i = 0; i < L.length; i++) {
    if (L.data[i] == e) {
      return i + 1; // 返回元素e在顺序表中的位置
    }
  }
  return 0; // 顺序表中不存在元素e
}
```

```c++

```
