#include <stdio.h>

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

int main() {
  SharedStack S;
  int e;
  InitStack(&S);
  return 0;
}
