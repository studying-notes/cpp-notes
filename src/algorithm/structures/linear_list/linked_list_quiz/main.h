
#ifndef LINKED_LIST_QUIZ__MAIN_H
#define LINKED_LIST_QUIZ__MAIN_H

#include <iostream>

typedef int ElemType;

typedef struct LNode {
  ElemType data;     //数据域
  struct LNode *next;//指针域
} LNode;             //单链表结点类型

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
  r->next = L;
  return L;//返回头结点
}

//输出单链表L中的所有结点
void PrintList(LNode *L) {
  LNode *p = L->next;//p指向第一个结点
  while (p != nullptr && p != L) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}

typedef struct DNode {
  ElemType data;      //数据域
  struct DNode *prior;//前驱指针域
  struct DNode *next; //后继指针域
} DNode;              //双链表结点类型

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
  r->next = L;
  L->prior = r;
  return L;//返回头结点
}

//输出双链表L中的所有结点
void PrintDList(DNode *L) {
  DNode *p = L->next;//p指向第一个结点
  while (p != nullptr && p != L) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}


#endif//LINKED_LIST_QUIZ__MAIN_H
