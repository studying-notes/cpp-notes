---
date: 2020-10-29T19:01:00+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C/C++ 数据结构与算法之线性表"  # 文章标题
url:  "posts/algorithm/c/doc/linear_list"  # 设置网页永久链接
tags: [ "algorithm", "c/c++" ]  # 标签
series: [ "C/C++ 数据结构与算法"]  # 系列
categories: [ "数据结构与算法"]  # 分类

# 章节
weight: 20 # 排序优先级
chapter: false  # 设置为章节

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

## 线性表的结构体定义

### 顺序表的结构体定义

```c++
#define maxSize 100

typedef struct {
    int data[maxSize];  // 顺序表元素数组
    int length;  // 顺序表的长度
} SqList;
```

### 顺序表的数组定义

一般用数组，而不是繁琐的结构体定义。

```c++
int SqList[maxSize];
int n;
```

### 单链表结点定义

```c++
typedef struct LNode {
    int data;
    struct LNode *next;
} LNode;
```

### 双链表结点定义

```c++
typedef struct DLNode {
    int data;
    struct DLNode *prior;
    struct DLNode *next;
} DLNode;
```

结点是内存中一片由用户分配的存储空间，只有一个地址来表示它的存在，没有显式的名称，因此我们会在分配链表结点空间的时候，同时定义一个指针，来存储这片空间的地址（这个过程通俗地讲叫指针指向结点），并且常用这个指针的名称来作为结点的名称。

但指针变量自身所需的存储空间是系统分配的，不需要用户调用函数 free()，只有用户分配的存储空间才需要用户自己来释放。

## 顺序表的操作

### 插入示例

已知一个顺序表 L，其中的元素递增有序排列，设计一个算法，插入一个元素 x（ x 为 int 型）后保持该顺序表仍然递增有序排列。

```c++
#define maxSize 100

typedef struct {
    int data[maxSize];  // 顺序表元素数组
    int length;  // 顺序表的长度
} SqList;

int findElem(SqList L, int x) {
    int i;
    for (i = 0; i < L.length; ++i) {
        if (x < L.data[i]) {
            return i;
        }
    }
    return i;
}

void insertElem(SqList &L, int x) {
    int p, i;
    p = findElem(L, x);
    for (i = L.length - 1; i > p; --i) {
        L.data[i + 1] = L.data[i];
    }
    L.data[p] = x;
    ++(L.length);
}
```

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

```c++

```

```c++

```

```c++

```

```c++

```

