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

int main() {
  ElemType a[] = {1, 3, 4, 2};
  auto *A = CreateListTail(a, 4);
  //  PrintList(A);
  Resort(A);
  PrintList(A);
  return 0;
}
