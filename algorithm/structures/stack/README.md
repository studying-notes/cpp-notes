---
date: 2022-11-13T13:01:19+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "栈"  # 文章标题
url:  "posts/cpp/algorithm/structures/stack/README"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 栈的定义

栈（Stack）是只允许在一端进行插入或删除操作的线性表。

首先栈是一种线性表，但限定这种线性表只能在某一端进行插入和删除操作。

栈顶（Top）。线性表允许进行插入删除的那一端。

栈底（Bottom）。固定的，不允许进行插入和删除的另一端。

空栈。不含任何元素的空表。

栈的操作特性可以明显地概括为后进先出（Last In First Out，LIFO）。

n 个不同元素进栈，出栈元素不同排列的个数为(1/(n+1))*C(n, 2n)。上述公式称为卡特兰（Catalan）数，可采用数学归纳法证明。

## 栈的基本操作

```c++
// 初始化栈
void InitStack(Stack &S);

// 判断栈是否为空
bool StackEmpty(Stack S);

// 进栈
void Push(Stack &S, ElemType x);

// 出栈
bool Pop(Stack &S, ElemType &x);

// 读栈顶元素
bool GetTop(Stack S, ElemType &x);

// 销毁栈
void DestroyStack(Stack &S);
```

## 栈的存储结构

栈是一种操作受限的线性表，类似于线性表，它也有对应的两种存储方式。

### 栈的顺序存储结构

[栈的顺序存储结构](sequence_stack.md)

### 栈的链式存储结构

[栈的链式存储结构](linked_stack.md)

## 王道习题

> 设不带头节点的单链表的表头指针为 L，结点结构由 data 和 next 两个域构成，其中 data 域为字符型。试设计算法判断该链表的全部 n 个字符是否中心对称。例如 xyx、xyyx 都是中心对称。

用栈保存链表的前半部分，然后依次与后半部分比较。

```c++
bool IsCentralSymmetric(LNode *L, const int n) {
  const int m = n / 2;
  ElemType stack[m], top = -1;
  LNode *p = L;// 不带头节点的情况

  for (int i = 0; i < m; ++i) {
    stack[++top] = p->data;
    p = p->next;
  }

  if (n % 2 == 1) // 奇数个结点，跳过中间结点
    p = p->next;

  for (int i = 0; i < m; ++i) {
    //    printf("%d %d\n", stack[top], p->data);
    if (stack[top--] != p->data)
      return false;
    p = p->next;
  }

  return true;
}
```

```c++

```

```c++

```
