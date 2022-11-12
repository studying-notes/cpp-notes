---
date: 2022-11-09T13:09:46+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "线性表的链式表示"  # 文章标题
url:  "posts/cpp/algorithm/structures/linear_list/linked_list"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

顺序表可以随时存取表中的任意一个元素，它的存储位置可以用一个简单直观的公式表示，但插入和删除操作需要移动大量元素。链式存储线性表时，不需要使用地址连续的存储单元，即不要求逻辑上相邻的元素在物理位置上也相邻，它通过“链”建立起数据元素之间的逻辑关系，因此插入和删除操作不需要移动元素，而只需修改指针，但也会失去顺序表可随机存取的优点。

## 单链表的定义

线性表的链式存储又称单链表，它是指通过一组任意的存储单元来存储线性表中的数据元素。为了建立数据元素之间的线性关系，对每个链表结点，除存放元素自身的信息外，还需要存放一个指向其后继的指针。

```c++
typedef int ElemType;

typedef struct LNode {
  ElemType data;      //数据域
  struct LNode *next; //指针域
} LNode;              //单链表结点类型

/*
 * 结构体名和类型名是可以相同的，因为两者的命名空间是不同的：
 * 结构体声明变量时必须加 struct 关键字，即 struct LNode *L;
 * 而类型声明变量时不需要加 struct 关键字，即 LNode *L;
 */
```

利用单链表可以解决顺序表需要大量连续存储单元的缺点，但单链表附加指针域，也存在浪费存储空间的缺点。由于单链表的元素离散地分布在存储空间中，所以单链表是非随机存取的存储结构，即不能直接找到表中某个特定的结点。查找某个特定的结点时，需要从表头开始遍历，依次查找。

通常用头指针来标识一个单链表，如单链表 L，头指针为 NULL 时表示一个空表。此外，为了操作上的方便，在单链表第一个结点之前附加一个结点，称为头结点。头结点的数据域可以不设任何信息，也可以记录表长等信息。头结点的指针域指向线性表的第一个元素结点，如图 2.4 所示。

![图2.4带头结点的单链表](../../../assets/images/algorithm/structures/linear_list/linked_list/图2.4带头结点的单链表.png)

头结点和头指针的区分：不管带不带头结点，头指针都始终指向链表的第一个结点，而头结点是带头结点的链表中的第一个结点，结点内通常不存储信息。引入头结点后，可以带来两个优点：

1. 由于第一个数据结点的位置被存放在头结点的指针域中，因此在链表的第一个位置上的操作和在表的其他位置上的操作一致，无须进行特殊处理。

2. 无论链表是否为空，其头指针都指向头结点的非空指针（空表中头结点的指针域为空），因此空表和非空表的处理也就得到了统一。

## 单链表上基本操作的实现

```c++
//初始化单链表
void InitList(LNode *&L) {
  L = new LNode; //创建头结点
  L->next = nullptr;
}

//在单链表L中插入值为e的结点
void InsertElem(LNode *L, ElemType e) {
  auto *p = new LNode; //创建新结点
  p->data = e;
  p->next = L->next; //插入到表头
  L->next = p;
}

//在单链表L中查找值为e的结点
LNode *LocateElem(LNode *L, ElemType e) {
  LNode *p = L->next; //p指向第一个结点
  while (p != nullptr && p->data != e)
    p = p->next;
  return p;
}


//在单链表L中删除值为e的结点
void DeleteElem(LNode *L, ElemType e) {
  LNode *p = L->next, *q; //p指向第一个结点
  while (p != nullptr && p->data != e) {
    q = p;
    p = p->next;
  }
  if (p != nullptr) {
    q->next = p->next;
    delete p;
  }
}

//输出单链表L中的所有结点
void PrintList(LNode *L) {
  LNode *p = L->next; //p指向第一个结点
  while (p != nullptr) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}
```

## 从数组创建单链表

不带头节点时，还是先创建带头节点的单链表，然后将返回头结点的 next 部分即可。

其他操作可以先创建一个头节点指向这个不带头节点的单链表，然后再进行操作。

### 带头节点头插法

```c++
//从数组a中创建单链表L
LNode *CreateListHead(ElemType a[], int n) {
  auto L = new LNode;//创建头结点
  L->next = nullptr; //头结点指针域置空
  for (int i = 0; i < n; i++) {
    auto *p = new LNode;//创建新结点
    p->data = a[i];     //新结点数据域赋值
    p->next = L->next;  //插入到表头
    L->next = p;        //头结点指针域指向新结点
  }
  return L;//返回头结点
}
```

### 带头节点尾插法

```c++
//从数组a中创建单链表L
LNode *CreateListTail(ElemType a[], int n) {
  auto L = new LNode;//创建头结点
  LNode *r = L;      // 指向尾节点
  for (int i = 0; i < n; i++) {
    auto *p = new LNode;//创建新结点
    p->data = a[i];     //新结点数据域赋值
    r->next = p;        //插入到表尾
    r = p;              //移动尾节点
  }
  r->next = nullptr;
  return L;//返回头结点
}
```

## 双链表

单链表结点中只有一个指向其后继的指针，使得单链表只能从头结点依次顺序地向后遍历。要访问某个结点的前驱结点（插入、删除操作时），只能从头开始遍历，访问后继结点的时间复杂度为 O(1)，访问前驱结点的时间复杂度为 O(n)。

为了克服单链表的上述缺点，引入了双链表，双链表结点中有两个指针 prior 和 next，分别指向其前驱结点和后继结点，如图 2.9 所示。

![](../../../assets/images/algorithm/structures/linear_list/linked_list/图2.9双链表示意图.png)
```c++
typedef struct DNode {
  ElemType data;      //数据域
  struct DNode *prior;//前驱指针域
  struct DNode *next; //后继指针域
} DNode;              //双链表结点类型
```

```c++
//从数组a中创建双链表L
DNode *CreateDListTail(ElemType a[], int n) {
  auto *L = new DNode;//创建头结点
  L->prior = nullptr;
  L->next = nullptr;
  DNode *r = L;       // 指向尾节点
  for (int i = 0; i < n; i++) {
    auto *p = new DNode;//创建新结点
    p->data = a[i];     //新结点数据域赋值
    r->next = p;        //插入到表尾
    p->prior = r;       //新结点的前驱指针指向尾节点
    r = p;              //移动尾节点
  }
  r->next = nullptr;
  return L;//返回头结点
}
```

```c++
//输出双链表L中的所有结点
void PrintDList(DNode *L) {
  DNode *p = L->next;//p指向第一个结点
  while (p != nullptr) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}
```

双链表在单链表的结点中增加了一个指向其前驱的 prior 指针，因此双链表中的按值查找和按位查找的操作与单链表的相同。但双链表在插入和删除操作的实现上，与单链表有着较大的不同。

```c++
// 双链表的插入操作
bool InsertDLinkList(DNode *&L, int i, ElemType e) {
  DNode *p = L, *s;
  int j = 0;
  while (p && j < i - 1) {
    p = p->next;
    j++;
  }
  if (!p || j > i - 1) {
    return false;
  }
  s = new DNode;
  s->data = e;
  s->next = p->next;
  if (p->next) {
    p->next->prior = s;
  }
  s->prior = p;
  p->next = s;
  return true;
}

// 双链表的删除操作
bool DeleteDLinkList(DNode *&L, int i, ElemType &e) {
  DNode *p = L, *q;
  int j = 0;
  while (p && j < i - 1) {
    p = p->next;
    j++;
  }
  if (!p || j > i - 1) {
    return false;
  }
  q = p->next;
  if (!q) {
    return false;
  }
  e = q->data;
  p->next = q->next;
  if (q->next) {
    q->next->prior = p;
  }
  delete q;
  return true;
}
```

## 循环链表

### 循环单链表

循环单链表和单链表的区别在于，表中最后一个结点的指针不是 NULL，而改为指向头结点，从而整个链表形成一个环，如图 2.12 所示。

在循环单链表中，表尾结点 *r 的 next 域指向 L，故表中没有指针域为 NULL 的结点，因此，循环单链表的判空条件不是头结点的指针是否为空，而是它是否等于头指针。

![](../../../assets/images/algorithm/structures/linear_list/linked_list/图2.12循环单链表.png)

```c++
//从数组a中创建单链表L
LNode *CreateListTail(ElemType a[], int n) {
  auto L = new LNode;//创建头结点
  LNode *r = L;      // 指向尾节点
  for (int i = 0; i < n; i++) {
    auto *p = new LNode;//创建新结点
    p->data = a[i];     //新结点数据域赋值
    r->next = p;        //插入到表尾
    r = p;              //移动尾节点
  }
  r->next = L;       //尾结点指针指向头结点
  return L;//返回头结点
}

//输出单链表L中的所有结点
void PrintList(LNode *L) {
  LNode *p = L->next;//p指向第一个结点
  while (p != nullptr&&p!=L) { //循环条件为p不为空且不为头结点
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}
```

### 循环双链表

在循环双链表中，头结点的 prior 指针还要指向表尾结点。

```c++
//从数组a中创建双链表L
DNode *CreateDListTail(ElemType a[], int n) {
  auto *L = new DNode;//创建头结点
  L->prior = nullptr;
  L->next = nullptr;
  DNode *r = L;// 指向尾节点
  for (int i = 0; i < n; i++) {
    auto *p = new DNode;//创建新结点
    p->data = a[i];     //新结点数据域赋值
    r->next = p;        //插入到表尾
    p->prior = r;       //新结点的前驱指针指向尾节点
    r = p;              //移动尾节点
  }
  r->next = L;      //尾结点指针指向头结点
  L->prior = r;   //头结点的前驱指针指向尾节点
  return L;//返回头结点
}

//输出双链表L中的所有结点
void PrintDList(DNode *L) {
  DNode *p = L->next;//p指向第一个结点
  while (p != nullptr && p != L) { //循环条件为p不为空且不为头结点
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}
```

## 静态链表

静态链表借助数组来描述线性表的链式存储结构，结点也有数据域 data 和指针域 next，与前面所讲的链表中的指针不同的是，这里的指针是结点的相对地址（数组下标），又称游标。和顺序表一样，静态链表也要预先分配一块连续的内存空间。

静态链表和单链表的对应关系如图 2.14 所示。

![](../../../assets/images/algorithm/structures/linear_list/linked_list/图2.14静态链表存储示意图.png)

```c++
#define MAXSIZE 1000

typedef struct {
  ElemType data;
  int next;
} SLinkList[MAXSIZE];
```

静态链表以 next==-1 作为其结束的标志。静态链表的插入、删除操作与动态链表的相同，只需要修改指针，而不需要移动元素。

## 王道练习题

> 设计一个递归算法，删除不带头结点的单链表 L 中所有值为 x 的结点。

```c++
void ListDeleteElem(LNode *&L, ElemType x) {
  if (L != nullptr) {
    // 从后往前删，防止遗落
    ListDeleteElem(L->next, x);
    if (L->data == x) {
      LNode *p = L;// 释放空间
      L = L->next; // 引用可以修改 L，让其指向为下一个节点
      delete p;
    }
  }
}
```

尽可能不用 C++ 的特性。

> 在带头结点的单链表 L 中，删除所有值为的结点，并释放其空间，假设值为 x 的结点不唯一，试编写算法以实现上述操作。

跟上面的题目几乎是一样的。这里再实现一种非递归的算法。

```c++
void ListDeleteElem(LNode *L, ElemType x) {
  LNode *p = L, *q;// q 储存将被释放的节点
  while (p->next != nullptr) {
    if (p->next->data == x) {
      q = p->next;
      p->next = q->next;// 指向下一节点
      delete q;               // 释放节点
    } else {
      p = p->next;
    }
  }
}
```

> 设 L 为带头结点的单链表，编写算法实现从尾到头反向输出每个结点的值。

```c++
// 不带头结点的单链表逆序输出
void printListReversed(LNode *L) {
  if (L != nullptr) {
    printListReversed(L->next);
    printf("%d ", L->data);
  }
}

void PrintListReversed(LNode *L) {
  printListReversed(L->next); // 不输出头结点
}
```

> 试编写在带头结点的单链表 L 中删除一个最小值结点的高效算法（假设最小值结点是唯一的）。

```c++
void ListDeleteMin(LNode *L) {
  LNode *p = L, *min, *min_prior = L;// min_prior 记录最小节点的前驱
  while (p->next != nullptr) {
    if (p->next->data < min_prior->next->data) {
      min_prior = p;
    }
    p = p->next;
  }
  min = min_prior->next;
  min_prior->next = min->next;
  delete min;
}
```

> 试编写算法将带头结点的单链表就地逆置，所谓“就地”是指辅助空间复杂度为 O(1)。

```c++
void ListReversed(LNode *L) {
  if (L->next == nullptr) {
    return;// 空链表
  }
  
  LNode *p = L->next, *q;// 是 L->next 而不是 L
  while (p->next != nullptr) {
    q = L->next;            // 保存头结点的下一个节点
    L->next = p->next;      // 头插法插入下一个节点
    p->next = p->next->next;// p 指向下一个节点
    L->next->next = q;      // 头结点的下一个节点指向原来的头结点的下一个节点
  }
}
```

或者保存 p 的 next 指针，然后将 p 的 next 指针指向前一个节点。

```c++
void Reverse(LNode *L) {
  if (L->next == nullptr) {
    return;// 空链表
  }

  LNode *p = L->next, *q;// 是 L->next 而不是 L

  while (p->next != nullptr) {
    q = p->next;
    p->next = q->next;
    q->next = L->next;
    L->next = q;
  }
}
```

两点十分关键：

1. 必须临时保存一个节点的 next 指针，否则会丢失。
2. 初始 p 指向第一个节点，而不是头结点，否则陷入死循环。

> 有一个带头结点的单链表 L，设计一个算法使其元素递增有序。

插入排序法：

```c++
void ListInsertSort(LNode *L) {
  LNode *p = L->next, *q, *r;
  L->next = nullptr; // 原链表置空
  while (p != nullptr) {
    q = L;
    while (q->next != nullptr && q->next->data < p->data) {
      q = q->next;
    }
    r = p->next; // 保存下一个节点
    p->next = q->next; // 插入
    q->next = p;
    p = r; // p 指向下一个节点
  }
}
```

> 设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，删除表中所有介于给定的两个值（作为函数参数给出）之间（不包括边界）的元素的元素（若存在）。

```c++
void ListDeleteElems(LNode *L, ElemType x, ElemType y) {
  LNode *p = L, *q;
  while (p->next != nullptr) {
    if (p->next->data > x && p->next->data < y) {
      q = p->next;
      p->next = q->next;
      delete q;
    } else {
      p = p->next;
    }
  }
}
```

> 给定两个单链表，编写算法找出两个链表的公共结点。


```c++
LNode *ListFindCommonNode(LNode *L1, LNode *L2) {
  LNode *p1 = L1, *p2 = L2, *q1 = L1, *q2 = L2;

  while (p1 != nullptr && p2 != nullptr) {
    if (p1 == p2) {// 长度相同的情况
      return p1;
    }
    p1 = p1->next, p2 = p2->next;// 往后移动
  }

  // 长度不同的情况，将长的链表提前移动，对齐

  while (p1 != nullptr) {// L1 更长
    p1 = p1->next;
    q1 = q1->next;
  }

  while (p2 != nullptr) {// L2 更长
    p2 = p2->next;
    q2 = q2->next;
  }

  while (q1 != q2) {
    q1 = q1->next;
    q2 = q2->next;
  }

  return q1;
}

int main() {
  LNode *L0 = new LNode{5, nullptr};
  L0->next = new LNode{6, nullptr};
  L0->next->next = new LNode{7, nullptr};

  LNode *L1 = new LNode{0, nullptr};
  L1->next = new LNode{1, nullptr};
  L1->next->next = new LNode{2, nullptr};
  L1->next->next->next = L0;

  LNode *L2 = new LNode{0, nullptr};
  L2->next = new LNode{3, nullptr};
  L2->next->next = new LNode{4, nullptr};
  L2->next->next->next = L0;

  LNode *p = ListFindCommonNode(L1, L2);
  LNode *hp = new LNode{0, p};
  PrintList(hp);

  return 0;
}
```

> 给定一个带表头结点的单链表，设 head 为头指针，结点结构为 (data, next)，data 为整型元素，next 为指针，试写出算法：按**递增**次序输出单链表中各结点的数据元素，并释放结点所占的存储空间。

```c++
void PrintListIncrement(LNode *L) {
  LNode *p, *q, *o;
  while (L->next != nullptr) {
    p = L, q = L;
    while (p->next != nullptr) {
      if (p->next->data < q->next->data) {
        q = p;
      }
      p = p->next;
    }
    if (q->next != nullptr) {
      printf("%d ", q->next->data);
      o = q->next;
      q->next = o->next;
      delete o;
    }
  }
}
```

> 将一个带头结点的单链表 A 分解为两个带头结点的单链表 A 和 B，使得 A 表中含有原表中**序号**为奇数的元素，而 B 表中含有原表中序号为偶数的元素，且保持其相对顺序不变。

```c++
void Partition(LNode *A, LNode *B) {
  LNode *p = A, *q = B;
  int even = 0;
  while (p->next != nullptr) {
    if (even) {               //偶数
      q->next = p->next;      // 将该节点添加到 B 尾
      p->next = p->next->next;// A 断开该节点
      q = q->next;            // B 往后移动
      q->next = nullptr;      // 断开与 A 的链接
    } else {                  // 这里是关键，上面 p->next 已经改变
      p = p->next;
    }
    even = !even;
  }
}

int main() {
  ElemType a[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};

  auto *A = CreateListTail(a, 9);
  auto *B = new LNode{0, nullptr};

  PrintList(A);
  Partition(A, B);
  PrintList(A);
  PrintList(B);

  return 0;
}
```

> 设 C = {a1, b1, a, b2, …, an, bn} 为线性表，采用带头结点的 hc 单链表存放，设计一个就地算法，将其拆分为两个线性表，使得 A = {a1, a2, …, an}，B = {bn, …, b2, b1}，与上面的题目类似，但 B 是逆序。

```c++
void Partition(LNode *A, LNode *B) {
  LNode *p = A, *q;
  int even = 0;
  while (p->next != nullptr) {
    if (even) {         //偶数
      q = p->next;      // 保存p的下一个结点
      p->next = q->next;//A断开q结点
      // 头插法
      q->next = B->next;//将q结点指向B链表部分
      B->next = q;      //修改B的头结点指向q
    } else {            // 这里是关键，上面 p->next 已经改变
      p = p->next;
    }
    even = !even;
  }
}
```

> 在一个递增有序的线性表中，有数值相同的元素存在。若存储方式为单链表，设计算法去掉数值相同的元素，使表中不再有重复的元素，例如 (7,10,10,21,30,42,42,42,51,70) 将变为 (7,10,21,30,42,51,70)。

```c++
void Deduplicate(LNode *L) {
  if (L->next == nullptr) {
    return;
  }

  LNode *p = L->next, *q;
  while (p->next != nullptr) {
    if (p->next->data == p->data) {
      q = p->next;
      p->next = q->next;
      delete q;
    } else {
      p = p->next;
    }
  }
}
```

> 假设有两个按元素值递增次序排列的线性表，均以单链表形式存储。请编写算法将这两个单链表归并为一个按元素值递减次序排列的单链表，并要求利用原来两个单链表的结点存放归并后的单链表。

```c++
void Merge(LNode *A, LNode *B, LNode *C) {
  LNode *p = A->next, *q = B->next, *o;

  while (p != nullptr && q != nullptr) {
    if (p->data < q->data) {
      o = p, p = p->next;
    } else {
      o = q, q = q->next;
    }
    o->next = C->next;
    C->next = o;
  }

  while (p != nullptr) {
    o = p, p = p->next;
    o->next = C->next;
    C->next = o;
  }

  while (q != nullptr) {
    o = q, q = q->next;
    o->next = C->next;
    C->next = o;
  }
}

int main() {
  ElemType a[] = {1, 3, 5, 7};
  ElemType b[] = {2, 4, 6, 8,9,10};

  auto *A = CreateListTail(a, 4);
  auto *B = CreateListTail(b, 6);
  auto *C = new LNode{0, nullptr};

  Merge(A, B, C);
  PrintList(C);

  return 0;
}
```

> 设 A 和 B 是两个单链表（带头结点），其中元素递增有序。设计一个算法从 A 和 B 中的公共元素产生单链表 C，要求不破坏 A、B 的结点。

```c++
void Common(LNode *A, LNode *B, LNode *C) {
  LNode *p = A->next, *q = B->next, *o = C;

  while (p != nullptr && q != nullptr) {
    if (p->data < q->data) {
      p = p->next;
    } else if (p->data > q->data) {
      q = q->next;
    } else {
      o->next = new LNode{p->data, nullptr};
      o = o->next, p = p->next, q = q->next;
    }
  }
}

int main() {
  ElemType a[] = {1, 3, 5, 7};
  ElemType b[] = {5, 7, 8, 9};

  auto *A = CreateListTail(a, 4);
  auto *B = CreateListTail(b, 4);
  auto *C = new LNode{0, nullptr};

  Common(A, B, C);
  PrintList(C);

  return 0;
}
```

> 已知两个链表 A 和 B 分别表示两个集合，其元素递增排列。编制函数，求 A 与 B 的交集，并存放于 A 链表中。

```c++
void Intersection(LNode *A, LNode *B) {
  LNode *p = A->next, *q = B->next, *o = A;
  while (p != nullptr && q != nullptr) {
    if (p->data < q->data) {
      p = p->next;
    } else if (p->data > q->data) {
      q = q->next;
    } else {
      o->next = p;
      p = p->next, q = q->next;
      o->next->next = nullptr;
      o=o->next;
    }
  }
}
```

> 两个整数序列 A = a1, a2, a3, …, am 和 B = b1, b2, b3, …, bn 已经存入两个单链表中，设计一个算法，判断序列 B 是否是序列 A 的连续子序列。

KMP

> 设计一个算法用于判断带头结点的循环双链表是否对称。

```c++
bool IsSymmetrical(DNode *L) {
  DNode *p = L->next, *q = L->prior;
  while (p != nullptr && q != nullptr && p != q && p->data == q->data) {
    p = p->next, q = q->prior;
  }
  return p == q;
}
```

> 有两个循环单链表，链表头指针分别为 h1 和 h2，编写一个函数将链表 h2 链接到链表 h1 之后，要求链接后的链表仍保持循环链表形式。

```c++
void Merge(LNode *h1, LNode *h2) {
  LNode *p1 = h1->next;
  while (p1->next != h1) {
    p1 = p1->next;
  }

  LNode *p2 = h2->next;
  while (p2->next != h2) {
    p2 = p2->next;
  }

  p1->next = h2->next;
  p2->next = h1;
}
```

> 设有一个带头结点的循环单链表，其结点值均为正整数。设计一个算法，反复找出单链表中结点值最小的结点并输出，然后将该结点从中删除，直到单链表空为止，再删除表头结点。

```c++
void PrintListIncrement(LNode *L) {
  LNode *p, *q, *o;
  while (L->next != L) {
    p = L, q = L;
    while (p->next != L) {
      if (p->next->data < q->next->data) {
        q = p;
      }
      p = p->next;
    }
    if (q->next != L) {
      printf("%d ", q->next->data);
      o = q->next;
      q->next = o->next;
      delete o;
    }
  }
  delete L;
}
```

> 设头指针为 L 的带有表头结点的非循环**双向链表**，其每个结点中除有 pred（前驱指针）、 data（数据）和 next（后继指针）域外，还有一个访问频度域 freq。在链表被启用前，其值均初始化为零。每当在链表中进行一次 Locate(L,x) 运算时，令元素值为 x 的结点中 freq 域的值增 1，并使此链表中结点保持按访问频度非增（递减）的顺序排列，同时最近访问的结点排在频度相同的结点前面，以便使频繁访问的结点总是靠近表头。试编写符合上述要求的 Locate(L, x) 运算的算法，该运算为函数过程，返回找到结点的地址，类型为指针型。

```c++
#include <iostream>

typedef int ElemType;

typedef struct DNode {
  ElemType data;      //数据域
  struct DNode *prior;//前驱指针域
  struct DNode *next; //后继指针域
  int freq;           //访问频度域
} DNode;              //双链表结点类型

//从数组a中创建双链表L
DNode *CreateDListTail(ElemType a[], int n) {
  auto *L = new DNode;//创建头结点
  L->prior = nullptr;
  L->next = nullptr;
  DNode *r = L;// 指向尾节点
  for (int i = 0; i < n; i++) {
    auto *p = new DNode;//创建新结点
    p->freq = 0;
    p->data = a[i];//新结点数据域赋值
    r->next = p;   //插入到表尾
    p->prior = r;  //新结点的前驱指针指向尾节点
    r = p;         //移动尾节点
  }
  r->next = L;
  L->prior = r;
  return L;//返回头结点
}

//输出双链表L中的所有结点
void PrintDList(DNode *L) {
  DNode *p = L->next;//p指向第一个结点
  while (p != L) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}

DNode *Locate(DNode *L, ElemType x) {
  DNode *p = L->next, *q;
  while (p != L) {
    if (p->data == x) {
      p->freq++;

      // 搜索
      q = p->prior;
      while (q != L && q->freq <= p->freq) {
        q = q->prior;
      }

      if (q != p->prior) {
        //断开
        p->prior->next = p->next;
        p->next->prior = p->prior;

        // 插入
        q->next->prior = p, p->next = q->next;
        q->next = p, p->prior = q;
      }

      return p;
    } else {
      p = p->next;
    }
  }

  return nullptr;
}

int main() {
  ElemType a[] = {1, 2, 3, 4};
  auto *A = CreateDListTail(a, 4);
  Locate(A, 3);
  Locate(A, 4);
  PrintDList(A);
  return 0;
}
```

> 已知一个带有表头结点的单链表，查找链表中倒数第 k 个位置上的结点（k 为正整数）。若查找成功，算法输出该结点的 data 域的值，并返回 1 ；否则，只返回 0。

设置两个指针 p 和 q ，初始时，p 和 q 都指向头结点。然后 q 向后移动 k-1 个位置，若此时 q 为空，则说明 k 值大于链表长度，返回 0 ；否则，p 和 q 同时向后移动，直到 q 为空，此时 p 指向的结点即为所求结点。

```c++
int FindTheKThLast(LNode *L, int k) {
  LNode *fast = L, *slow = L;

  //fast 先移动 k-1 个位置
  for (int i = 1; i < k; i++) {
    fast = fast->next;
    if (fast == nullptr) {
      return 0;
    }
  }

  // 同时移动
  while (fast->next != nullptr) {
    fast = fast->next;
    slow = slow->next;
  }

  printf("%d\n", slow->data);

  return 1;
}
```

时间复杂度为 O(n) ，空间复杂度为 O(1) 。

> 设线性表 L =(a1, a2, a2, …, an-2, an-1,an) 采用带头结点的单链表保存，请设计一个空间复杂度为 O(1) 且时间上尽可能高效的算法，重新排列 L 中的各结点，得到线性表 L' =(a1, an,a2, an-1, a3, an-2 …)。

```c++
void Reverse(LNode *L) {
  if (L->next == nullptr) {
    return;// 空链表
  }

  LNode *p = L->next, *q;// 是 L->next 而不是 L

  while (p->next != nullptr) {
    q = p->next;
    p->next = q->next;
    q->next = L->next;
    L->next = q;
  }
}

void Resort(LNode *L) {
  if (L->next == nullptr) {
    return;// 空链表
  }

  // 找到中间节点
  LNode *fast = L, *slow = L;
  while (fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next;
    if (fast->next != nullptr) {
      fast = fast->next;
    }
  }

  // 对后半链表逆序
  Reverse(slow);

  // 插入
  LNode *p = L->next, *q;
  while (slow->next != nullptr && slow != p) {
    // slow != p 十分关键，因为 slow 可能不是最后一个节点
    q = slow->next;
    slow->next = q->next;
    q->next = p->next;
    p->next = q;
    p = q->next;
  }
}
```

```c++

```
