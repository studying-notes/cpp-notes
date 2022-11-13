#include <iostream>
#include <map>
#include <unordered_set>

#define len(array) (sizeof(array) / sizeof(array[0]))

using namespace std;

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
  r->next = nullptr;
  return L;//返回头结点
}

//输出单链表L中的所有结点
void PrintList(LNode *L) {
  LNode *p = L->next;//p指向第一个结点
  while (p != nullptr) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}

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

int main() {
  ElemType a[] = {1, 3, 5};
  ElemType b[] = {2, 4, 6};

  auto *A = CreateListTail(a, len(a));
  auto *B = CreateListTail(b, len(b));

  auto *C = Merge(A, B);

  PrintList(C);

  //  LNode *p = A, *q = B;
  //  while (p->next != nullptr)
  //    p = p->next;
  //  while (q->next != nullptr)
  //    q = q->next;
  //
  //  p->next = A->next;
  //  q->next = A->next;

  return 0;
}
