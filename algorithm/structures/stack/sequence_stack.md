---
date: 2022-11-13T13:20:43+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "栈的顺序存储结构"  # 文章标题
url:  "posts/cpp/algorithm/structures/stack/sequence_stack"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 顺序栈的实现

采用顺序存储的栈称为顺序栈，它利用一组地址连续的存储单元存放自栈底到栈顶的数据元素，同时附设一个指针（top）指示当前栈顶元素的位置。

栈的顺序存储类型可描述为：

```c
#define MaxSize 20 // 顺序栈的最大长度

typedef int ElemType; // 数据元素类型

typedef struct {
  ElemType data[MaxSize]; // 用于存放栈中元素
  int top; // 栈顶指针
} SqStack; // 顺序栈类型
```

由于顺序栈的入栈操作受数组上界的约束，当对栈的最大使用空间估计不足时，有可能发生栈上溢，此时应及时向用户报告消息，以便及时处理，避免出错。

## 顺序栈的基本运算

```c++
// 初始化栈
void InitStack(SqStack &S) {
  S.top = -1; // 置栈顶指针为-1
}

// 判断栈是否为空
bool StackEmpty(SqStack S) {
  if (S.top == -1)
    return true; // 栈空
  else
    return false; // 栈不空
}

bool Push(SqStack &S, ElemType x) {
  if (S.top == MaxSize - 1)
    return false; // 栈上溢
  S.top++; // 栈顶指针加1
  S.data[S.top] = x; // 将新元素x赋值给栈顶空间
  return true;
}

bool Pop(SqStack &S, ElemType &x) {
  if (S.top == -1)
    return false; // 栈下溢
  x = S.data[S.top]; // 将栈顶元素赋值给x
  S.top--; // 栈顶指针减1
  return true;
}

bool GetTop(SqStack S, ElemType &x) {
  if (S.top == -1)
    return false; // 栈空
  x = S.data[S.top]; // 将栈顶元素赋值给x
  return true;
}
```

```c++

```
