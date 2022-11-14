#include <iostream>

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

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
