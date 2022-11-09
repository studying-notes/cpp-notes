#include <iostream>

typedef int ElemType;

typedef struct LNode {
  ElemType data;     //数据域
  struct LNode *next;//指针域
} LNode;             //单链表结点类型

typedef struct DNode {
  ElemType data;      //数据域
  struct DNode *prior;//前驱指针域
  struct DNode *next; //后继指针域
} DNode;              //双链表结点类型

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
