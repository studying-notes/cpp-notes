#include <iostream>

#define MaxSize 200

typedef int ElemType;

typedef struct {
  ElemType data[MaxSize];
  int top;
} SqStack;

void InitStack(SqStack &S) {
  S.top = -1;
}

bool StackEmpty(SqStack S) {
  if (S.top == -1)
    return true;
  else
    return false;
}

bool Push(SqStack &S, ElemType x) {
  if (S.top == MaxSize - 1)
    return false;
  S.top++;
  S.data[S.top] = x;
  return true;
}

bool Pop(SqStack &S, ElemType &x) {
  if (S.top == -1)
    return false;
  x = S.data[S.top];
  S.top--;
  return true;
}

bool GetTop(SqStack S, ElemType &x) {
  if (S.top == -1)
    return false;
  x = S.data[S.top];
  return true;
}

void PrintStack(SqStack S) {
  int i;
  for (i = S.top; i >= 0; i--)
    std::cout << S.data[i] << " ";
  std::cout << std::endl;
}

int main() {
  SqStack S;

  InitStack(S);

  Push(S, 1);
  Push(S, 2);
  Push(S, 3);
  Push(S, 4);
  Push(S, 5);
  Push(S, 6);
  Push(S, 7);
  Push(S, 8);
  Push(S, 9);

  PrintStack(S);
}
