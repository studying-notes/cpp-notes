---
date: 2022-11-10T09:09:35+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "链表相关问题"  # 文章标题
url:  "posts/cpp/algorithm/structures/linear_list/linked_list_quiz"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 从有序链表中移除重复项

见[习题](linked_list.md)。

## 从无序链表中移除重复项

用一个哈希表记录已经出现过的元素，遍历链表，如果当前元素已经出现过，则删除该元素。

```c++
void Deduplicate(LNode *L) {
  if (L->next == nullptr) {
    return;
  }

  LNode *p = L, *q;
  map<ElemType, bool> visited;
  while (p->next != nullptr) {
    if (visited[p->next->data]) {
      q = p->next;
      p->next = q->next;
      delete q;
    } else {
      visited[p->next->data] = true;
      p = p->next;
    }
  }
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

## 计算两个单链表所代表的数之和

> 给定两个带头节点的单链表，链表的每个结点代表一位数，位权从低到高，**个位数在链表开始位置**，计算两个数的和，储存到新的链表，返回新链表的头节点。例如：输入链表 (3->1->5) 和链表 (5->9->2)，输出：8->0->8，即 513+295 = 808。

对链表中的结点直接进行相加操作，把相加的和存储到新的链表中对应的结点中，同时还要记录结点相加后的进位。

```c++
LNode *Add(LNode *a, LNode *b) {
  auto c = new LNode{0, nullptr};
  LNode *p = a->next, *q = b->next, *o = c;
  ElemType carry = 0, sum, remainder;

  while (p != nullptr || q != nullptr) {
    sum = carry;
    if (p != nullptr)
      sum += p->data, p = p->next;
    if (q != nullptr)
      sum += q->data, q = q->next;
    carry = sum / 10, remainder = sum % 10;
    o->next = new LNode{remainder, nullptr};
    o = o->next;
  }

  return c;
}
```

时间复杂度为 $O(max(m, n))$，空间复杂度为 $O(n)$。

## 将单链表向右旋转 k 个位置

> 给定带头节点的单链表 1->2->3->4->5->6->7，k=3，那么旋转后的单链表变为 5->6->7->1->2->3->4，即将链表最后 k 个元素移动到前面。

快指针先走 k 步，然后快慢指针同时走，当快指针走到链表尾部时，慢指针所指向的结点就是倒数第 k 个结点。

特别注意，先走 k 步得到的是倒数第 k+1 个结点，即倒数第 k 个节点的前驱，先走 k-1 步得到的是倒数第 k 个结点。

```c++
void RevolveK(LNode *L, int k) {
  LNode *fast = L, *slow = L;

  // 快指针先走 k 步
  for (int i = 0; i < k; i++) {
    if (fast->next == nullptr)
      return;
    fast = fast->next;
  }

  // 得到倒数第 k 个节点的前驱
  while (fast->next != nullptr) {
    fast = fast->next, slow = slow->next;
  }

  fast->next = L->next;
  L->next = slow->next;
  slow->next = nullptr;
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

## 检测单链表是否有环

> 单链表有环指的是单链表中某个结点的 next 域指向的是链表中在它之前的某一个结点，这样在链表的尾部形成一个环形结构。

### 哈希表法

遍历链表，将每个结点的地址存储到哈希表中，如果遍历到的结点的地址已经在哈希表中，则说明链表有环。

```c++
bool HasCycle(LNode *L) {
  unordered_set<LNode *> visited;
  LNode *p = L->next;

  while (p != nullptr) {
    if (visited.find(p) != visited.end())
      return true;
    visited.insert(p);
    p = p->next;
  }

  return false;
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 快慢指针法

快指针每次走两步，慢指针每次走一步，如果快指针追上了慢指针，则说明链表有环。

```c++
bool HasCycle(LNode *L) {
  LNode *fast = L, *slow = L;

  while (fast->next != nullptr) {
    fast = fast->next, slow = slow->next;
    if (fast->next != nullptr)
      fast = fast->next;
    if (fast == slow) {
      return true;
    }
  }

  return false;
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

## 找出环的入口点

当链表有环的时候，如果知道环的入口点，那么在需要遍历链表或释放链表所占的空间的时候方法将会非常简单。

### 哈希表法

遍历链表，将每个结点的地址存储到哈希表中，如果遍历到的结点的地址已经在哈希表中，则说明链表有环，此时返回该结点的地址。

```c++
LNode *FindCycleEntry(LNode *L) {
  unordered_set<LNode *> visited;
  LNode *p = L->next;

  while (p != nullptr) {
    if (visited.find(p) != visited.end())
      return p;
    visited.insert(p);
    p = p->next;
  }

  return nullptr;
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 快慢指针法

**fast 比 slow 多走了一倍的路程**（fast 每次走 2 步，所以路程是 slow 的 2 倍），这一倍路程就是 **n 个环的长度**。那么 **n 个环的长度就就是起始点到相遇点的距离**，于是**相遇点向后离入口点 + (n-1) 个环的长度**就是**起始点到入口点的距离**。

```c++
LNode *FindCycleEntry(LNode *L) {
  LNode *fast = L, *slow = L;

  // 找到相遇点
  while (fast->next != nullptr) {
    fast = fast->next, slow = slow->next;
    if (fast->next != nullptr)
      fast = fast->next;
    if (fast == slow)
      break;
  }

  slow = L;// 两者必须同时走
  while (fast != slow) {
    fast = fast->next,
    slow = slow->next;
  }

  return slow;
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

## 链表相邻元素翻转

> 把带头节点的链表相邻元素翻转，例如给定链表为1->2->3->4->5->6->7，则翻转后的链表变为2->1->4->3->6->5->7。

交换数据域即可。

```c++
void Flip(LNode *L) {
  if (L->next == nullptr)
    return;

  LNode *p = L->next;
  while (p->next != nullptr) {
    L->data = p->data;// 当作临时储存
    p->data = p->next->data;
    p->next->data = L->data;
    p = p->next;
    if (p != nullptr) {
      p = p->next;
    }
  }
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

## 把链表以 k 个结点为一组进行翻转

> 把每 k 个相邻的结点看成一组进行翻转，**如果剩余结点不足 k 个，则剩余部分翻转**。假设给定链表 1->2->3->4->5->6->7 和一个数 k，如果 k 的值为 2，那么翻转后的链表为 2->1->4->3->6->5->7。如果 k 的值为 3，那么翻转后的链表为：3->2->1->6->5->4->7。

```c++
LNode *ReverseK(LNode *L, int k) {
  if (L->next == nullptr ||             // 空链表
      L->next->next == nullptr || k < 2)//仅有一个节点
    return nullptr;

  // 头插法逆序
  LNode *p = L->next, *q;// p 记录节点前驱，所以 p 不会为 nullptr
  for (int i = 1; i < k && p->next != nullptr; i++) {
    q = p->next;
    p->next = q->next;
    q->next = L->next;
    L->next = q;
  }

  // 返回第 k 个节点
  return p;
}

void FlipK(LNode *L, int k) {
  if (L->next == nullptr)
    return;

  LNode *p = L;
  while (p != nullptr) {
    p = ReverseK(p, k);
  }
}
```

如果剩余部分保持原样，那么最后一部分还必须重新翻转回去，或者翻转之前计算链表的长度是否足够。

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

## 合并两个有序链表

> 合并两个递增有序链表，使得合并后的链表仍然递增有序。

```c++
LNode *Merge(LNode *L1, LNode *L2) {
  auto *L3 = new LNode{0, nullptr};
  LNode *p1 = L1->next, *p2 = L2->next, *p3 = L3;

  while (p1 != nullptr && p2 != nullptr) {
    if (p1->data < p2->data) {
      p3->next = p1;
      p1 = p1->next;
    } else {
      p3->next = p2;
      p2 = p2->next;
    }
    p3 = p3->next;
  }

  if (p1 != nullptr)
    p3->next = p1;

  if (p2 != nullptr)
    p3->next = p2;

  return L3;
}
```

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。
