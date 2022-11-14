---
date: 2022-11-14T09:39:17+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "共享栈"  # 文章标题
url:  "posts/cpp/algorithm/structures/stack/shared_stack"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 共享栈的定义

利用栈底位置相对不变的特性，可让两个顺序栈共享一个一维数组空间，将两个栈的栈底分别设置在共享空间的两端，两个栈顶向共享空间的中间延伸。

两个栈的栈顶指针都指向栈顶元素，top0 = -1 时 0 号栈为空，top1 = MaxSize 时 1 号栈为空；仅当两个栈顶指针相邻（top1-top0 = 1）时，判断为栈满。当 0 号栈进栈时 top0 先加 1 再赋值，1 号栈进栈时 top1 先减 1 再赋值；出栈时则刚好相反。

共享栈是为了更有效地利用存储空间，两个栈的空间相互调节，只有在整个存储空间被占满时才发生上溢。其存取数据的时间复杂度均为 O(1)，所以对存取效率没有什么影响。

## 共享栈的实现

```c
#define MaxSize 100//定义最大长度

typedef struct {
  int data[MaxSize];//存放顺序表的数组
  int top0, top1;   //栈顶指针
} SharedStack;      //共享栈类型

//初始化共享栈
void InitStack(SharedStack *S) {
  S->top0 = -1;
  S->top1 = MaxSize;
}

//判断共享栈是否为空
bool StackEmpty(SharedStack S, int i) {
  // i 表示栈号，i=0表示第一个栈，i=1表示第二个栈
  // 调用函数之前已经保证栈号i的合法性，即i=0或i=1，不再做检查
  return i == 0 ? S.top0 == -1 : S.top1 == MaxSize;
}

//判断共享栈是否已满
bool StackFull(SharedStack S) {
  return S.top0 + 1 == S.top1;
}

//进栈
bool Push(SharedStack *S, int e, int i) {
  if (S->top1 - S->top0 == 1)
    return false;

  if (i == 0) {
    S->data[++S->top0] = e;
  } else {
    S->data[--S->top1] = e;
  }

  return true;
}

bool Pop(SharedStack *S, int &e, int i) {
  if (i == 0) {
    if (S->top0 == -1)
      return false;
    e = S->data[S->top0--];
  } else {
    if (S->top1 == MaxSize)
      return false;
    e = S->data[S->top1++];
  }
  return true;
}
```

```c++

```
