#include <iostream>

#define MaxSize 50// 顺序表的最大长度

typedef int ElemType;// 元素类型

typedef struct {
  ElemType data[MaxSize];// 顺序表的数据域
  int length;            // 顺序表的长度
} SqList;                // 顺序表的类型定义

bool ListInsert(SqList &L, int i, ElemType e) {
  if (i < 1 || i > L.length + 1) { // 判断插入位置是否合法
    return false;
  }

  if (L.length >= MaxSize) { // 判断顺序表是否已满
    return false;
  }

  for (int j = L.length; j >= i; j--) { // 将第i个元素及其后面的元素后移
    L.data[j] = L.data[j - 1];
  }

  L.data[i - 1] = e; // 将e插入到第i个位置
  L.length++;       // 顺序表长度加1

  return true;
}

int main() {
  SqList L;

  return 0;
}
