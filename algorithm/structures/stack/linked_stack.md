---
date: 2022-11-13T13:30:43+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "栈的链式存储结构"  # 文章标题
url:  "posts/cpp/algorithm/structures/stack/linked_stack"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 链栈的实现

采用链式存储的栈称为链栈，链栈的优点是便于多个栈共享存储空间和提高其效率，且不存在栈满上溢的情况。

通常采用单链表实现，并规定所有操作都是在单链表的表头进行的。

## 链栈的基本操作

带头结点的单链表实现的链栈的基本操作如下：

```c++
typedef int ElemType;

typedef struct LNode {
  ElemType data;     //数据域
  struct LNode *next;//指针域
} LNode;             //单链表结点类型

bool StackEmpty(LNode *S) {
  return S->next == nullptr;
}

void Push(LNode *S, ElemType e) {
  S->next = new LNode{e, S->next};
}

bool Pop(LNode *S, ElemType &e) {
  if (S->next == nullptr)
    return false;
  LNode *p = S->next;
  e = p->data;
  S->next = S->next->next;
  delete p;
  return true;
}

bool GetTop(LNode *S, ElemType &e) {
  if (S->next == nullptr)
    return false;
  e = S->next->data;
  return true;
}
```

不带头结点的单链表实现的链栈的基本操作如下：

```c++
typedef int ElemType;

typedef struct LNode {
  ElemType data;     //数据域
  struct LNode *next;//指针域
} LNode;             //单链表结点类型

bool StackEmpty(LNode *S) {
  return S == nullptr;
}

void Push(LNode *&S, ElemType e) {
  S = new LNode{e, S};
}

bool Pop(LNode *&S, ElemType &e) {
  if (S == nullptr)
    return false;
  LNode *p = S;
  e = p->data;
  S = S->next;
  delete p;
  return true;
}

bool GetTop(LNode *S, ElemType &e) {
  if (S == nullptr)
    return false;
  e = S->data;
  return true;
}
```

关键在于指针引用。


