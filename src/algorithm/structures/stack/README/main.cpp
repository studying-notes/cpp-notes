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

bool IsCentralSymmetric(LNode *L, const int n) {
  const int m = n / 2;
  ElemType stack[m], top = -1;
  LNode *p = L;// 不带头节点的情况

  for (int i = 0; i < m; ++i) {
    stack[++top] = p->data;
    p = p->next;
  }

  if (n % 2 == 1)
    p = p->next;

  for (int i = 0; i < m; ++i) {
    //    printf("%d %d\n", stack[top], p->data);
    if (stack[top--] != p->data)
      return false;
    p = p->next;
  }

  return true;
}

int main() {
  ElemType a[] = {1, 3, 5, 5, 3, 1};
  ElemType b[] = {2, 4, 2};

  auto *A = CreateListTail(a, len(a));
  auto *B = CreateListTail(b, len(b));

  std::cout << std::boolalpha << IsCentralSymmetric(A->next, len(a)) << std::endl;
  std::cout << std::boolalpha << IsCentralSymmetric(B->next, len(b)) << std::endl;

  return 0;
}
