---
date: 2022-11-03T10:03:49+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "顺序表相关问题"  # 文章标题
url:  "posts/cpp/algorithm/structures/linear_list/contiguous_list_quiz"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

> 从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删元素的值。空出的位
置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行。

```c++
int ListDeleteMin(SqList &L) {
  if (L.length == 0) {
    exit(-1);// 顺序表为空
  }

  ElemType index = 0;// 最小值元素下标
  for (int i = 1; i < L.length; i++) {
    if (L.data[i] < L.data[index]) {
      index = i;// 找到更小值元素则更新下标
    }
  }

  int min = L.data[index];// 最小值元素

  L.data[index] = L.data[L.length - 1];// 空出的位置由最后一个元素填补

  L.length--;// 别忘了顺序表长度减一

  return min;
}
```

> 设计一个高效算法，将顺序表 L 的所有元素逆置，要求算法的空间复杂度为 O(1)。

```c++
void ListReverse(SqList &L) {
  int i = 0, j = L.length - 1;
  while (i < j) {
    // 对换元素
    L.data[i] = L.data[i] + L.data[j];
    L.data[j] = L.data[i] - L.data[j];
    L.data[i] = L.data[i] - L.data[j];
    i++, j--;
  }
}
```

> 对长度为 n 的顺序表 L，编写一个时间复杂度为 O(n)、空间复杂度为 O(1)的算法，该算法删除线性表中所有值为 x 的数据元素。

```c++
void ListDeleteElem(SqList &L, ElemType x) {
  int i = 0;
  for (int j = 0; j < L.length; j++) {
    if (L.data[j] != x) {
      if (i != j) {
        L.data[i] = L.data[j];
      }
      i++;
    }
  }
  L.length = i;
}
```

> 从**有序**顺序表中删除其值在给定值 s 与 t 之间（包含 s 和 t，要求 `s<t`）的所有元素，若 s 或 t 不合理或顺序表为空，则显示出错信息并退出运行。

```c++
bool ListDeleteElem(SqList &L, ElemType s, ElemType t) {
  if (s >= t || L.length == 0) {
    return false;
  }

  int i, j;

  for (i = 0; i < L.length && L.data[i] < s; i++) {}

  if (i == L.length)
    return false;

  for (j = i; i < L.length && L.data[j] <= t; j++) {}

  while (j < L.length) {
    L.data[i++] = L.data[j++];
  }

  L.length = i;

  return true;
}
```

> 从顺序表中删除其值在给定值 s 与 t 之间（包含 s 和 t，要求 `s<t`）的所有元素，若 s 或 t 不合理或顺序表为空，则显示出错信息并退出运行。

```c++
bool ListDeleteElem(SqList &L, ElemType s, ElemType t) {
  if (s >= t || L.length == 0) {
    return false;
  }

  int i = 0, j;

  for (j = 0; j < L.length; j++) {
    if (L.data[j] >= s && L.data[j] <= t) {
      if (i != j) {
        L.data[i] = L.data[j];
      }
      i++;
    }
  }
```

> 从**有序**顺序表中删除所有其值重复的元素，使表中所有元素的值均不同。

```c++
void ListDeleteElem(SqList &L) {
  int i = 0, j;

  for (j = 1; j < L.length; j++) {
    if (L.data[j] != L.data[i]) {
      L.data[++i] = L.data[j];
    }
  }

  L.length = ++i;
}
```

> 将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表。

```c++
void ListDeleteElem(SqList La, SqList Lb, SqList &Lc) {
  int i = 0, j = 0;

  while (i < La.length && j < Lb.length) {
    if (La.data[i] < Lb.data[j]) {
      Lc.data[i + j] = La.data[i];
      i++;
    } else {
      Lc.data[i + j] = Lb.data[j];
      j++;
    }
  }

  while (i < La.length) {
    Lc.data[i + j] = La.data[i];
    i++;
  }

  while (j < La.length) {
    Lc.data[i + j] = Lb.data[j];
    j++;
  }

  Lc.length = i + j;
}
```

> 线性表中的元素递增有序且按顺序存储于计算机内。要求设计一个算法，完成用最少时间在表中查找数值为 x 的元素，若找到，则将其与后继元素位置相交换，若找不到，则将其插入表中并使表中元素仍递增有序。

```c++
void SearchExchange(SqList &L, ElemType x) {
  int begin = 0, end = L.length - 1, mid;
  while (begin <= end) {
    mid = (begin + end) / 2;
    if (L.data[mid] == x) {
      break;
    } else if (L.data[mid] < x) {
      begin = mid + 1;
    } else if (L.data[mid] > x) {
      end = mid - 1;
    }
  }

  if (L.data[mid] == x && mid < L.length - 1) {
    int temp = L.data[mid];
    L.data[mid] = L.data[mid + 1];
    L.data[mid + 1] = temp;
  }

  // 找不到则 begin 一定大于 end，且 L.data[end] < x < L.data[begin]
  if (begin > end) {
    for (int i = L.length - 1; i > end; i--) {
      L.data[i + 1] = L.data[i];
    }
    L.data[end + 1] = x;
    L.length++;
  }
}
```

```c++

```
