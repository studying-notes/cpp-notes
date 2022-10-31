---
date: 2022-10-30T14:27:10+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "排序算法"  # 文章标题
url:  "posts/cpp/algorithm/sort"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

算法的详细解释可以参考 [Go 学习笔记](https://github.com/studying-notes/go-notes)的算法部分。

## 获取数组长度

```c
#define len(array) (sizeof(array) / sizeof(array[0]))
```

```c
int main() {
  int array[] = {38, 65, 97, 76, 13, 27, 49};
  int length = sizeof(array) / sizeof(array[0]);
}
```

## 打印数组元素

```c++
#include <stdio.h>

void print_array(const int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[length - 1]);
}
```

## 交换数组元素

### 临时变量法

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}
```

### 加减运算法

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] = array[j] + array[i];
    array[i] = array[j] - array[i];
    array[j] = array[j] - array[i];
  }
}
```

### 位运算法

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] = array[j] ^ array[i];
    array[i] = array[j] ^ array[i];
    array[j] = array[j] ^ array[i];
  }
}
```

## 选择排序

```c++
void selection_sort(int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    int k = i;// 最小值索引
    for (int j = i + 1; j < length; j++) {
      if (array[j] < array[k]) {
        k = j;
      }
    }
    swap(array, i, k);
  }
}
```

## 插入排序

```c++
void insertion_sort(int array[], int length) {
  for (int i = 0; i < length-1; i++) {
    for (int j = i+1; j > 0; j--) {
      if (array[j] >= array[j - 1])
        break;
      swap(array, j, j-1);
    }
  }
}
```

## 冒泡排序

从前往后冒泡，每次冒泡都会将最大的元素冒泡到最后。

```c++
void bubble_sort(int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    for (int j = 1; j < length - i; j++) {
      if (array[j - 1] > array[j]) {
        swap(array, j, j - 1);
      }
    }
  }
}
```

从后往前冒泡，每次冒泡都会将最小的元素冒泡到最前。

```c++
void bubble_sort(int array[], int length) {
  for (int i = 0; i < length-1; i++) {
    for (int j = length - 1; j > i; j--) {
      if (array[j] < array[j - 1])
        swap(array, j, j - 1);
    }
  }
}
```

## 归并排序

```c++
void merge(int array[], int begin, int mid, int end) {
  int left_length = mid - begin + 1;
  int right_length = end - mid;

  int left[left_length], right[right_length];

  for (int i = 0; i < left_length; i++) {
    left[i] = array[begin + i];
  }

  for (int j = 0; j < right_length; j++) {
    right[j] = array[mid + j + 1];
  }

  int i = 0, j = 0;

  while (i < left_length && j < right_length) {
    if (left[i] < right[j]) {
      array[begin + +j] = left[i];
      i++;
    } else {
      array[begin + +j] = right[j];
      j++;
    }
  }

  while (i < left_length) {
    array[begin + i + j] = left[i];
    i++;
  }

  while (j < right_length) {
    array[begin + i + j] = right[j];
    j++;
  }
}

void merge_sort(int array[], int begin, int end) {
  // begin 表示开始索引 end 表示结束索引，可以取到
  if (begin < end) {
    int mid = (begin + end) / 2;
    merge_sort(array, begin, mid);
    merge_sort(array, mid + 1, end);
    merge(array, begin, mid, end);
  }
}
```

## 快速排序

```c++
int partition(int array[], int begin, int end) {
  // begin, end 都可以取到
  int pivot = array[begin];
  while (begin < end) {
    while (begin < end && array[begin] < pivot)
      begin++;
    while (begin < end && array[end] > pivot)
      end--;
    swap(array, begin, end);
  }
  array[begin]=pivot;
  return begin;
}

void quick_sort(int array[], int begin, int end) {
  // begin, end 都可以取到
  if (begin < end) {
    int mid = partition(array, begin, end);
    quick_sort(array, begin, mid);
    quick_sort(array, mid + 1, end);
  }
}
```

## 希尔排序

```c++
void hill_sort(int array[], int length) {
  for (int step = length / 2; step > 0; step /= 2) {
    for (int i = 1; i < length; i += step) {
      for (int j = i; j > step - 1; j -= step) {
        if (array[j] >= array[j - step])
          break;
        swap(array, j, j - step);
      }
    }
  }
}
```

```c++

```
