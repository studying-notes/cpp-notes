---
date: 2022-11-04T09:25:50+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "数组相关问题"  # 文章标题
url:  "posts/cpp/algorithm/structures/linear_list/array_quiz"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 数组循环移位

> 有 n 个整数，使前面各数后移 m 个位置，最后 m 个数变成最前面 m 个数。例如，有 10 个数的数组，即 n = 10，它们的值分别是 `1,2,3,4,5,6,7,8,9,10`，如果取 m = 5，经过位置调整后，变为 `6,7,8,9,10,1,2,3,4,5`。

可将这个问题视为把数组 ab 转换成数组 ba，a 为数组前 m 个元素，b 为数组后 n-m 个元素，先将 a 和 b 分别逆序，然后将整个数组逆序，即可得到结果。

```c++
void reverse_array(int array[], int begin, int end) {
  while (begin < end) {
    swap(array, begin++, end--);
  }
}

void spin(int array[], int n, int m) {
  int l = n - m;
  reverse_array(array, 0, l - 1);
  reverse_array(array, l, n - 1);
  reverse_array(array, 0, n - 1);
}
```

上述算法中的三个 reverse_array 函数的执行次数分别为 l/2、n-l/2、n/2，所以整个算法的时间复杂度为 O(n)。

## 求两个等长数组的中位数

> 一个长度为 L（L ≥ 1）的升序序列 S，处在第 L/2 （向上取整）个位置的数称为 S 的中位数。例如，若序列 S=(11,13,15,17,19)，则 S 的中位数是 15，两个序列的中位数是含它们所有元素的升序序列的中位数。例如，若 S=(2,4,6,8,20)，则 5 和 S 的中位数是 11。现在有两个等长升序序列 A 和 B，找出两个序列 A 和 B 的中位数。

分别求两个升序序列 A、B 的中位数，设为 a 和 b，求序列 A、B 的中位数过程如下：

1. 若 a = b，则 a 或 b 即为所求中位数，算法结束。

2. 若 `a<b`，则舍弃序列 A 中较小的一半，同时舍弃序列 B 中较大的一半，**要求两次舍弃的长度相等**。

3. 若 `a>b`，则舍弃序列 A 中较大的一半，同时舍弃序列 B 中较小的一半，要求两次舍弃的长度相等。

在保留的两个升序序列中，重复过程 ①、②、③，直到两个序列中**均只含一个元素时为止**，**较小者即为所求的中位数**。

```c++
int find_median(int a[], int b[], int length) {
  int a_begin = 0, a_end = length - 1, a_median;
  int b_begin = 0, b_end = length - 1, b_median;

  while (a_begin != a_end || b_begin != b_end) {
    a_median = (a_begin + a_end) / 2;
    b_median = (b_begin + b_end) / 2;

    if (a[a_median] == b[b_median]) {
      return a[a_median];
    } else if (a[a_median] < b[b_median]) {
      b_end = b_median;
      // 偶数情况下保证两次舍弃的长度相等
      a_begin = a_median + (a_begin + a_end) % 2 != 0;
    } else if (a[a_median] > b[b_median]) {
      a_end = a_median;
      b_begin = b_median + (b_begin + b_end) % 2 != 0;
    }
  }

  return a[a_begin] < b[b_begin] ? a[a_begin] : b[b_begin];
}
```

算法的时间复杂度为 O(log2(n))，空间复杂度为 O(1)。

## 找出数组中出现次数超过了一半的数

> 一个数组中有一个数字出现的次数超过了数组长度的一半，则称为主元素，请找出这个数字。例如输入一个长度为 9 的数组 {1,2,3,2,2,2,5,4,2}。由于数字 2 在数组中出现了 5 次，超过数组长度的一半，因此输出 2。如果不存在则输出 -1。

### 哈希表计数法

遍历数值，用一个哈希表对数组中的每一个元素计数，当某个元素的计数超过一半则返回该值，遍历完成则表明不存在。

```c++
#include <map>
#include <stdio.h>

using namespace std;

#define len(array) (sizeof(array) / sizeof(array[0]))

int findTheMoreThanHalf(int array[], int length) {
  int half = length / 2;
  map<int, int> counter;
  for (int i = 0; i < length; i++) {
    int &value = array[i];
    counter[value]++;
    if (counter[value] > half) {
      return value;
    }
  }
  return -1;
}

int main() {
  int a[] = {1, 3, 1};
  printf("%d\n", findTheMoreThanHalf(a, len(a)));
  int b[] = {3, 1, 1};
  printf("%d\n", findTheMoreThanHalf(b, len(a)));
  return 0;
}
```

算法的时间复杂度为 O(n)，空间复杂度为 O(n)。

### 摩尔投票法

摩尔投票法是一种基于**抵消**的思想，遍历数组，用一个变量记录当前的候选主元素，用一个计数器记录当前候选主元素的计数，当遍历到的元素与候选主元素相同时计数器加一，否则减一，当计数器为 0 时，将当前元素设为候选主元素，继续遍历。

最后遍历完成后，再次遍历数组统计其出现次数，若超过一半，候选主元素即为所求，否则不存在。

```c++
int findTheMoreThanHalf(int array[], int length) {
  int count = 1, value = array[0];

  for (int i = 1; i < length; i++) {
    if (array[i] == value) {
      count++;
    } else if (count > 0) {
      count--;
    } else {
      value = array[i];
      count = 1;
    }
  }

  if (count > 0) {
    count = 0;
    for (int i = 0; i < length; i++) {
      if (array[i] == value) {
        count++;
      }
    }
  }

  return count > length / 2 ? value : -1;
}
```

算法的时间复杂度为 O(n)，空间复杂度为 O(1)。

## 找出数组中未出现的最小正整数

> 给定一个含 n（n ≥ 1）个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。例如，数组 {-5,3,2,3} 中未出现的最小正整数是 1 ；数组 {1,2,3} 中未出现的最小正整数是 4。

分配一个用于标记的数组 B[]，用来记录 A 中是否出现了 1 ~ n 中的正整数，B[0] 对应正整数 1，B[n-1] 对应正整数 n，初始化 B 中全部为 0. 由于 A 中含有 n 个整数，因此可能返回的值是 1 ~ n+1，当 A 中 n 个数恰好为 1 ~ n 时返回 n+1. 当数组 A 中出现了小于等于 0 或大于 n 的值时，会导致 1 ~ n 中出现空余位置，返回结果必然在 1 ~ n 中，因此对于 A 中出现了小于等于 0 或大于 n 的值，可以不采取任何操作。

遍历数组 A，对于 A[i]，如果 A[i] > 0 且 A[i] <= n，且 B[A[i]-1] == 0，将 B[A[i]-1] 置为 1，表示 A[i] 出现过。遍历完成后，遍历 B，找到第一个 B[i] == 0 的位置，返回 i+1 即可。

```c++
int findTheMinPositive(int array[], int length) {
  int *counter = new int[length];
  memset(counter, 0, length * sizeof(int));

  for (int i = 0; i < length; i++) {
    int value = array[i];
    if (value > 0 && value <= length && counter[value - 1] == 0) {
      counter[value - 1] = 1;
    }
  }

  for (int i = 0; i < length; i++) {
    if (counter[i] == 0) {
      return i + 1;
    }
  }

  return length + 1;
}
```

算法的时间复杂度为 O(n)，空间复杂度为 O(n)。

## 求解最小三元组距离

### 定义三元组距离为差的绝对值之和

> 定义三元组（a，b，c）（a、b、c 均为正数）的距离 D = |a-b|+|b-c|+lc-a|。给定 3 个非空整数集合 S1、S2 和 S3，按升序分别存储在 3 个数组中。计算并输出所有可能的三元组（a，b，c）（a ∈ S1，b ∈ S2，c ∈ S3）中的最小距离。例如 S1 = {-1，0，9}，S2 = {-25，-10，10，11}，S3 = {2，9，17，30，41}，则最小距离为 2，相应的三元组为（9，10，9）。

用 min 记录当前最小三元组距离，初值为首元素三元组距离，用 i1、i2、i3 分别记录三个数组的下标，初始值为 0，当其都小于其数组的长度时（即直到遍历完其中一个数组为止），执行下面的循环：计算 s1[i1]、s2[i2]、s3[i3] 三个数的三元组距离，如果距离比 min 小，则将 min 修改为此距离，然后将最小数所在数组的下标 i 加 1。最后输出 min。

```c++
#include <iostream>

#define len(array) (sizeof(array) / sizeof(array[0]))

int abs(int a) {
  return a < 0 ? -a : a;
}

int distance(int a, int b, int c) {
  return abs(a - b) + abs(b - c) + abs(c - a);
}

int find_minimal_distance(int s1[], int l1, int s2[], int l2, int s3[], int l3) {
  int i1 = 0, i2 = 0, i3 = 0, dist;
  int min = distance(s1[0], s2[0], s3[0]);

  while (i1 < l1 && i2 < l2 && i3 < l3) {
    dist = distance(s1[i1], s2[i2], s2[i3]);
    if (dist < min) {
      min = dist;
    }

    if (s1[i1] < s2[i2] && s1[i1] < s3[i3]) {
      i1++;
    } else if (s2[i2] < s1[i1] && s2[i2] < s3[i3]) {
      i2++;
    } else {
      i3++;
    }
  }

  return min;
}

int main() {
  int s1[] = {-1, 0, 9};
  int s2[] = {-25, -10, 10, 11};
  int s3[] = {2, 9, 17, 30, 41};
  std::cout << find_minimal_distance(s1, len(s1), s2, len(s2), s3, len(s3)) << std::endl;
  return 0;
}
```

算法的时间复杂度为 O(n)，空间复杂度为 O(1)。

### 定义三元组距离为最大差的绝对值

> 已知三个升序整数数组 a[l]，b[m] 和 c[n]，请在三个数组中各找一个元素，使得组成的三元组距离最小。三元组距离的定义是：假设 a[i]、b[j] 和 c[k] 是一个三元组，那么距离为：Distance=max(|a[i]-b[j]|，|a[i]-c[k]|，|b[j]-c[k]|)，请设计一个求最小三元组距离的最优算法。

用 min 记录当前最小三元组距离，初值为首元素三元组距离，用 i1、i2、i3 分别记录三个数组的下标，初始值为 0，当其都小于其数组的长度时（即直到遍历完其中一个数组为止），执行下面的循环：计算 s1[i1]、s2[i2]、s3[i3] 三个数的三元组距离，如果距离比 min 小，则将 min 修改为此距离，然后将最小数所在数组的下标 i 加 1。最后输出 min。

过程和上面是一样的，区别只有距离的计算方法。

```c++
int max(int a, int b, int c) {
  int d = a > b ? a : b;
  return d > c ? d : c;
}

int distance(int a, int b, int c) {
  return max(abs(a - b), abs(b - c), abs(c - a));
}
```

算法的时间复杂度为 O(n)，空间复杂度为 O(n)。

## 找出数组中唯一的重复元素

数字 1～1000 放在含有 1001 个元素的数组中，其中只有唯一的一个元素值重复，其他数字均只出现一次。设计一个算法，将重复元素找出来，要求每个数组元素只能访问一次。

### 哈希表法

访问一个元素然后将它的值作为索引访问下一个元素，同时标记已访问元素，一旦再次访问同一元素即是重复元素。

```c++
#include <map>

bool findTheUniqueRepeated(int array[], int length, int &candidate) {
  candidate = 0;
  std::map<int, bool> visited;

  for (int i = 0; i < length; i++) {
    if (visited[array[i]]) {
      candidate = array[i];
      return true;
    }
    visited[array[i]] = true;
  }

  return candidate != 0;
}
```

### 累加求和法

将 1001 个数求和然后减去 1~1000 的和就是多出来的那个数。

### 累计差值求和

这种方法是对累加求和法的改进。就是一边加一边减，而不是全部加起来减，因为如果累加的数值巨大时，全部求和就很有可能溢出了。

```c++
bool findTheUniqueRepeated(int array[], int length, int &candidate) {
  candidate = 0;

  for (int i = 0; i < length; i++) {
    candidate += array[i] - i;
  }

  return candidate != 0;
}
```

### 异或法

异或运算的性质：当相同元素异或时，其运算结果为 0，当相异元素异或时，其运算结果为非 0，任何数与数字 0 进行异或运算，其运算结果为该数。

| 异或运算  | 相与运算  |
| --------- | --------- |
| 1 ^ 1 = 0 | 1 & 1 = 1 |
| 1 ^ 0 = 1 | 1 & 0 = 0 |
| 0 ^ 0 = 0 | 0 & 0 = 0 |

```c++
bool findTheUniqueRepeated(int array[], int length, int &candidate) {
  candidate = 0;

  for (int i = 0; i < length; i++) {
    candidate ^= array[i] ^ i;
  }

  return candidate != 0;
}
```

1~1000 都出现了 2 次，所以相互抵消。

## 找出数组中丢失的数

给定一个由 n-1 个整数组成的未排序的数组序列，其元素都是 1～n 中的不同的整数。写出一个寻找数组序列中缺失整数的线性时间算法。

类似上面的方法。

```c++
int findTheMissing(int array[], int length) {
  int candidate = length + 1;

  for (int i = 0; i < length; i++) {
    candidate += i + 1 - array[i];
  }

  return candidate;
}
```

## 找出数组中出现奇数次的元素

给定一个含有 n 个元素的整型数组 array，其中只有一个元素出现奇数次，找出这个元素。

因为对于任意一个数 k，有 k^k = 0，k^0 = k，所以将 array 中所有元素进行异或，那么个数为偶数的元素异或后都变成了 0，只留下了个数为奇数的那个元素。

```c++
#include <iostream>

int findOddNumberedElement(int array[], int length) {
  int value = 0;
  for (int i = 0; i < length; i++)
    value ^= array[i];
  return value;
}

int main() {
  int array[] = {1, 2, 3, 4, 5, 6,
                 1, 2, 3, 4, 5};
  int length = sizeof(array) / sizeof(array[0]);
  std::cout << findOddNumberedElement(array, length) << std::endl;
  return 0;
}
```

## 找出数组中出现奇数次的两个元素

由 n 个元素组成的数组，n-2 个数出现了偶数次，两个数出现了奇数次（这两个数不相等），如何用 O(1) 的空间复杂度，找出这两个数。

假设这两个数分别为 a、b，将数组中所有元素异或之后结果为 x，因为 a != b，所以 x = a^b，且 x != 0，判断 x 的二进制数的位为 1 的位数，只需要知道某一个位为 1 的位数 k，如 00101100，k 可以取 2 或者 3，或者 5，然后将 x 与数组中第 k 位为 1 的数进行异或，异或结果就是 a 或 b 中的一个，其他元素因为是偶数次全部抵消了，最后实际只有 a 或 b 参与了运算，然后把这个结果与 x 异或，就可以求出另外一个数。

因为 x 中第 k 位为 1 表示 a 或 b 中有一个数的第 k 位也为 1，假设为 a，将 x 与数组中第 k 位为 1 的数进行异或时，也即将 x 与 a 以及其他第 k 位为 1 的**出现过偶数次**的数进行异或，化简即为 x 与 a 异或，最终结果即为 b。

```c++
void find_odd_elements(int array[], int length, int &x, int &y) {
  x = 0;
  for (int i = 0; i < length; i++) {
    x ^= array[i];
  }
  y = x;
  int bit = x & ~(x - 1);
  for (int i = 0; i < length; i++) {
    if ((array[i] & bit) == bit) {
      y ^= array[i];
    }
  }
  x ^= y;
}
```

## 找出数组中出现奇数次的三个元素中的一个

> 一个数组里，除了三个数是唯一出现的，其余的数都出现偶数次，找出这三个数中的**任意一个**。

与上面的异或方法原理是相同的。**把三个数其中的两个数看成一个整体**。

```c++
int find_odd_element(int array[], int length) {
  int v = 0;

  for (int i = 0; i < length; i++) {
    v ^= array[i];
  }

  int bit = v & ~(v - 1);
  int u = v;

  for (int i = 0; i < length; i++) {
    if ((array[i] & bit) != 0) {
      u ^= array[i];
    }
  }

  return v ^ u;
}

int main() {
  int array[] = {1, 1, 2, 2, 3, 4, 5, 6, 6};
  std::cout << find_odd_element(array, len(array)) << std::endl;
}
```

## 分别使用递归与非递归实现二分查找算法

二分查找法也称为折半查找法，它的思想是每次都与序列的中间元素进行比较。

二分查找的一个前提条件是数组是有序的，假设数组 array 为递增序列，findData 为要查找的数，n 为数组长度，首先将 n 个元素分成个数大致相同的两半，取 `array[n/2]` 与将要查找的值 findData 进行比较，如果 findData 等于 `array[n/2]`，则找到 findData，算法终止；如果 `findData<array[n/2]`，则只要在数组 array 的左半部分继续搜索 findData ；如果 `findData>array[n/2]`，则只需要在数组 array 的右半部分继续搜索即可。

递归实现：

```c++
#include <stdio.h>

int binary_search(int a[], int n, int findData) {
  if (n == 0)
    return -1;

  int mid = n / 2;

  if (a[mid] == findData)
    return mid;
  else if (a[mid] > findData)
    return binary_search(a, mid, findData);
  else
    return binary_search(a + mid + 1, n - mid - 1, findData);
}

int main() {
  int a[] = {1, 2, 3, 4, 5};
  printf("%d\n", binary_search(a, 5, 3));
  return 0;
}
```

```c++
#include <stdio.h>

int binary_search(int a[], int findData, int begin, int end) {
  if (begin >= end)
    return -1;

  int middle = (begin + end) / 2;

  if (a[middle] == findData) {
    return middle;
  } else if (a[middle] > findData) {
    return binary_search(a, findData, begin, middle);
  } else {
    return binary_search(a, findData, middle + 1, end);
  }
}

int main() {
  int a[] = {1, 2, 3, 4, 5};
  printf("%d\n", binary_search(a, 4, 0, 4));
  return 0;
}
```

循环实现：

```c++
#include <stdio.h>

int binary_search(int a[], int n, int findData) {
  int begin = 0, end = n - 1;

  while (begin <= end) {
    int middle = (begin + end) / 2;

    if (a[middle] == findData) {
      return middle;
    } else if (a[middle] > findData) {
      end = middle - 1;
    } else {
      begin = middle + 1;
    }
  }

  return -1;
}

int main() {
  int a[] = {1, 2, 3, 4, 5};
  printf("%d\n", binary_search(a, 5, 3));
  return 0;
}
```

## 在排序数组中找出给定数字出现的次数

如何在排序数组中找出给定数字出现的次数？例如，数组 [1, 2, 2, 2, 3] 中 2 的出现次数是 3 次。

```c++
#include <stdio.h>

int binary_search(int a[], int n, int findData) {
  int begin = 0, end = n - 1;

  while (begin <= end) {
    int middle = (begin + end) / 2;

    if (a[middle] == findData) {
      int num = 1;
      for (int i = middle + 1; a[i] == findData; i++)
        num++;
      for (int i = middle - 1; a[i] == findData; i--)
        num++;
      return num;
    } else if (a[middle] > findData) {
      end = middle - 1;
    } else {
      begin = middle + 1;
    }
  }

  return 0;
}

int main() {
  int a[] = {1, 3, 3, 3, 5};
  printf("%d\n", binary_search(a, 5, 3));
  return 0;
}
```

## 计算两个有序整型数组的交集

例如，两个含有 n 个元素的有序（非降序）整型数组 a 和 b（数组 a 和 b 中都没有重复元素），求出其共同元素。

```
a=0, 1, 2, 3, 4
b=1, 3, 5, 7, 9
```

那么，它们的交集为 {1, 3}。

方法一：采用二路归并来遍历两个数组。

设两个数组分别为 array1[n1] 和 array2[n2]，分别以 i、j 开始遍历两个数组。在遍历过程中，如果当前遍历位置的 array1[i] 与 array[j] 相等，则此数为两个数组的交集，记录下来，并继续向后遍历 array1 和 array2。如果 array1[i] 大于 array2[j]，则继续向后遍历 array2。如果 array1[i] 小于 array2[j]，则需要继续向后遍历 array1，直到有一个数组结束遍历即停止。

```c++
#include <stdio.h>

int intersection(const int a[], int m, const int b[], int n, int *c) {
  int count = 0;

  while (m >= 0 && n >= 0) {
    if (a[m] == b[n])
      c[count++] = a[m];
    if (a[m] >= b[n])
      m--;
    if (a[m] <= b[n])
      n--;
  }

  return count;
}

int main() {
  int a[] = {1, 2, 3, 4, 5};
  int b[] = {3, 4, 5, 6, 7};
  int c[] = {0, 0, 0, 0, 0};

  int count = intersection(a, 4, b, 4, c);

  printf("count = %d\n", count);
  for (int i = 0; i < count; i++) {
    printf("c[%d] = %d\n", i, c[i]);
  }

  return 0;
}
```

方法二：顺序遍历两个数组，将数组元素存放到哈希表中，同时对统计的数组元素进行计数。如果某个元素的计数器的值为 2，则该元素为两者的交集元素。

方法三：遍历两个数组中任意一个数组，将遍历得到的元素存放到哈希表，然后遍历另外一个数组，同时对建立的哈希表进行查询，如果存在，则为交集元素。

## 找出数组中重复次数最多的数

例如，数组 {1,1,2,2,4,4,4,4,5,5,6,6,6}，元素 1 出现的次数为两次，元素 2 出现的次数为两次，元素 4 出现的次数为 4 次，元素 5 出现的次数为两次，元素 6 出现的次数为 3 次，问题就是要找出出现重复次数最多的数，所以输出应该为元素 4。可以采取如下两种方法来计算数组中重复次数最多的数。

使用 map 映射表，通过引入 map 表（map 是一个用来存储键值对的容器）来记录每个元素出现的次数，然后判断每个数出现的次数，进而找出重复次数最多的元素。

```c++
#include <iostream>
#include <map>

bool findTheMostRepeated(int array[], int length, int &value) {
  if (length == 0)
    return false;

  std::map<int, int> counter;
  for (int i = 0; i < length; i++) {
    if (++counter[array[i]] >= counter[value])
      value = array[i];
  }

  return true;
}

int main() {
  int array[] = {1, 1, 2, 2, 4, 4, 4, 4, 5, 5, 6, 6, 6};
  int length = sizeof(array) / sizeof(array[0]);
  int value = 0;
  findTheMostRepeated(array, length, value);
  std::cout << value << std::endl;
  return 0;
}
```

## 判定数组是否存在重复元素

取值为 [1, N-1] 含 N 个元素的整数数组，至少存在一个重复数，即可能存在多个重复数，O(N) 时间内找出其中任意一个重复数。例如，array[] = {1,2,2,4,5,4}，则 2 和 4 均是重复元素。

### 位图法

定义长度为 N 的位图，每个 bit 表示对应数字是否出现过，可以看成是一个数组。一旦遇到一个已经出现过的元素，则直接输出。此时的时间复杂度是 O(N)，空间复杂度为 O(N)。

```c++
int is_repeated(int array[], int length) {
  int size = (length - 1) / 8 + 1;
  printf("size = %d\n", size);

  int bit_map[size];// 必须初始化赋值
  for (int i = 0; i < size; i++) {
    bit_map[i] = 0;
  }

  for (int i = 0; i < length; i++) {
    int v = array[i] - 1;
    int x = v / 8;// 桶
    int y = v % 8;// 偏移
    int z = bit_map[x];
    printf("x = %d, y = %d\n", x, y);
    if ((z & (1 << y)) != 0) {
      return 1;
    }
    bit_map[x] = z | (1 << y);
  }

  return 0;
}
```

### 数组排序法

首先对数组进行计数排序，然后顺次扫描整个数组，直到遇到一个已出现的元素，直接将之输出。此时的时间复杂度为 O(N)，空间复杂度为 O(N)。或者选择其他排序算法，然后比较相邻的元素是否相同。此时的时间复杂度为 O(nlogn)，空间复杂度为 O(1)。

### 有环单链表法

单链表可以采用数组实现，此时每个元素值作为 next 指针指向下一个元素。本题可以转化为“已知一个单链表中存在环，找出环的入口点”这种想法。

具体思路如下：将 `array[i]` 看作第 i 个元素的索引，即 `array[i] → array[array[i]] → array[array[array[i]]] → array[array[array[array[i]]]] →……` 最终形成一个单链表，由于数组 a 中存在重复元素，则一定存在一个环，且环的入口元素为重复元素。
 
该题的关键在于，数组 array 的大小是 n，而元素的范围是 [1, n-1]，所以 `array[0]` 不会指向自己，进而不会陷入错误的自循环。如果元素的范围中包含 0，则该题不可直接采用该方法。程序示例代码如下：

```c++
#include <iostream>

int findTheUniqueRepeated(int array[], int length) {
  if (length == 0)
    return false;

  int i = 0, j = 0;

  do {
    i = array[i];
    j = array[array[j]];
  } while (i != j);

  i = 0;

  do {
    i = array[i];
    j = array[j];
  } while (i != j);

  return i;
}

int main() {
  int array[] = {1, 2, 3, 4, 5, 6,
                 7, 8, 9, 10, 2, 11};
  int length = sizeof(array) / sizeof(array[0]);
  std::cout << findTheUniqueRepeated(array, length) << std::endl;
  return 0;
}
```

## 找出数列中符合条件的数对

一个整数数组，元素取值可能是 1～n（n 是一个较大的正整数）中的任意一个数，相同数值不会重复出现。设计一个算法，找出数列中符合条件的数对的个数，满足数对中两数的和等于 n+1。

### 蛮力法

枚举出数组中所有可能的数对，看其和是否为 n+1，如果是，则输出。但这种方法一般效率不高。

```c++
void find_fixed_sum(int array[], int length, int sum) {
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (array[i] + array[j] == sum) {
        printf("%d %d\n", array[i], array[j]);
      }
    }
  }
}
```

### 数组排序法

先对数组进行排序，然后用两个指示器（front 和 back）分别指向第一个元素和最后一个元素，然后从两端同时向中间遍历，直到两个指针交叉。

```c++
void find_fixed_sum(int array[], int length, int sum) {
  int begin = 0, end = length - 1, val;
  while (begin < end) {
    val = array[begin] + array[end];
    if (val > sum)
      end--;
    else if (val < sum)
      begin++;
    else {
      printf("%d %d\n", array[begin++], array[end--]);
    }
  }
}
```

### 哈希表法

遍历数组，对于每个元素，计算其与 n+1 的差值，然后在哈希表中查找这个差值，如果找到了，则输出这个数对，否则将这个元素插入到哈希表中。

```c++
#include <map>

void find_fixed_sum(int array[], int length, int sum) {
  int val;
  std::map<int, int> kv;
  for (int i = 0; i < length; i++) {
    val = array[i];
    if (kv[val] == 0) {
      kv[sum-val] = 1;
    } else {
      printf("%d + %d = %d\n", val, sum - val, sum);
    }
  }
}
```

## 重新排列数组，使得数组左边为奇数，右边为偶数

给定一个存放整数的数组，如何重新排列数组，使得数组左边为奇数，右边为偶数？且算法空间复杂度为 O(1)，时间复杂度为 O(N)。

借鉴快速排序的分割算法，设置两个指示器（front 和 back），分别指向数组的第一个元素和最后一个元素，然后从两端同时向中间遍历，直到两个指针交叉。如果 front 指向的元素是偶数，而 back 指向的元素是奇数，则交换这两个元素，然后继续遍历。如果 front 指向的元素是奇数，则向后移动一位，如果 back 指向的元素是偶数，则向前移动一位。

```c++
void reorganize(int array[], int length) {
  int front = 0, back = length - 1;
  while (front < back) {
    while (front < back && array[front] % 2 == 1) {
      front++;
    }
    while (front < back && array[back] % 2 == 0) {
      back--;
    }
    swap(array, front, back);
  }
}
```

## 把一个整型数组中重复的数字去掉

首先通过快速排序，时间复杂度为 O(nlogn)；然后对排好序的数组经过一次遍历，将其重复元素通过交换，最终达到删除重复元素的目的。

```c++
int deduplication(int array[], int length) {
  int i = 0, j = 1;
  while (j < length) {
    if (array[i] != array[j]) {
      i++;
      if (i != j) {
        array[i] = array[j];
      }
      j++;
    } else {
      j++;
    }
  }
  // 长度
  return i + 1;
}
```

## 找出一个数组中第二大的数

首先定义一个变量 m 存储数组的最大数，初始值为数组首元素；另一个变量 n 用来存储数组元素的第二大数，初始值为数组第二个元素，然后遍历数组元素。如果数组元素的值比最大数变量的值大，则将第二大变量的值更新为最大数变量的值，最大数变量的值更新为该元素的值；如果数组元素的值比最大数的值小，则判断该数组元素的值是否比第二大数的值大，如果大，则更新第二大数的值为该数组元素的值。

```c++
int find_2nd_largest(int array[], int length) {
  if (length < 2) {
    exit(-1);
  }

  int m = array[0], n = array[1];
  if (m < n) {
    m = array[1], n = array[0];
  }

  for (int i = 2; i < length; i++) {
    int v = array[i];
    if (v > m) {
      n = m, m = v;
    } else if (v > n && v < m) {
      n = v;
    }
  }

  return n;
}
```

## 寻找数组中的最小值和最大值

### 变量标记法

维持两个变量 min 和 max，min 标记最小值，max 标记最大值，每次取出一个元素，先与已找到的最小值比较，再与已找到的最大值比较。此种方法只需要遍历一次数组。比较次数为 2N 次。

维持两个变量 min 和 max，min 标记最小值，max 标记最大值，每次比较相邻两个数，较大者与 max 比较，较小者与 min 比较，找出最大值和最小值。比较次数为 1.5N 次。

```c++
void find_max_and_min(int array[], int length, int &max, int &min) {
  if (length < 2) {
    exit(-1);
  }

  // 找出两个数
  max = array[0], min = array[1];
  if (max < min) {
    max = array[1], min = array[0];
  }

  int i, left, right;
  for (i = 3; i < length; i += 2) {
    left = array[i - 1], right = array[i];
    if (left < right) {
      left = array[i], right = array[i - 1];
    }
    if (left > max) {
      max = left;
    }
    if (right < min) {
      min = right;
    }
  }
}
```

## 找出有序旋转数组的最小元素

把一个有序数组最开始的若干个元素搬到数组的末尾，称为**数组的旋转**。

输入一个排好序的数组的一个旋转，输出旋转数组的最小元素。

例如数组 {3, 4, 5, 1, 2} 为数组 {1, 2, 3, 4, 5} 的一个旋转，该数组的最小值为 1。

通过数组的特性可以发现，数组元素首先是递增的，然后突然下降到最小值，然后再递增。虽然如此，但是还有下面三种特殊情况需要注意：

1. 数组本身是没有发生过旋转的，是一个有序的数组，例如序列 {1, 2, 3, 4, 5, 6}。
2. 数组中元素值全部相等，例如序列 {1, 1, 1, 1, 1, 1}。
3. 数组中元素值大部分都相等，例如序列 {1, 0, 1, 1, 1, 1}。

### 直接遍历法

```c++
#include <cstdio>

#define len(array) (sizeof(array) / sizeof(array[0]))

int findTheMinimum(int array[], int length) {
  for (int i = 1; i < length; i++) {
    if (array[i] < array[i - 1]) {
      return array[i];
    }
  }
  return array[0];
}

int main() {
  //  int array[] = {6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
  int array[] = {1, 0, 1, 1, 1, 1};
  int candidate = findTheMinimum(array, 0, len(array) - 1);
  printf("%d\n", candidate);
  return 0;
}
```

### 二分查找法

```c
#include <cstdio>

#define len(array) (sizeof(array) / sizeof(array[0]))

int findTheMinimum(int array[], int begin, int end) {
  if (begin == end)
    return array[begin];

  int mid = (begin + end) / 2;

	// 正好取到边缘
  if (mid > 0 && array[mid] < array[mid - 1]) {
    return array[mid];
  } else if (mid + 1 < end && array[mid + 1] < array[mid]) {
    return array[mid + 1];
  }

  // 有序数组
  if (array[mid] < array[end]) {
    return findTheMinimum(array, begin, mid);
  } else if (array[mid] > array[begin]) {
    return findTheMinimum(array, mid + 1, end);
  }

  int left = findTheMinimum(array, begin, mid);
  int right = findTheMinimum(array, mid + 1, end);
  return left < right ? left : right;
}

int main() {
  //  int array[] = {6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
  int array[] = {1, 0, 1, 1, 1, 1};
  int candidate = findTheMinimum(array, 0, len(array) - 1);
  printf("%d\n", candidate);
  return 0;
}
```

## 计算出序列的前 n 项数据

正整数序列 Q 中的每个元素都至少能被正整数 a 和 b 中的一个整除。现给定 a 和 b，如何计算出 Q 中的前 n 项？

例如，当 a = 3，b = 5，n = 6 时，序列为 3，5，6，9，10，12。

可以与归并排序联系起来，给定两个数组 A、B，数组 A 存放：3*1，3*2，3*3，…数组 B 存放：5*1，5*2，5*3，…有两个指针 i、j，分别指向 A、B 的第一个元素，取 `Min(A[i],B[j])`，并将较小值的指针前移，然后继续比较。当然，编程实现的时候，完全没有必要申请两个数组，用两个变量就可以了。

```c++
void get_foremost_n(int a, int b, int n, int array[]) {
  int a_sum = a, b_sum = b;
  for (int i = 0; i < n; i++) {
    if (a_sum < b_sum) {
      array[i] = a_sum;
      a_sum += a;
    } else if (a_sum > b_sum) {
      array[i] = b_sum;
      b_sum += b;
    } else {
      array[i] = a_sum;
      a_sum += a;
      b_sum += b;
    }
  }
}
```

## 判断一个整数 x 是否可以表示成 n 个连续正整数的和

假设 x 可以表示成 `n(n≥2)` 个连续正整数的和，那么数学表达式如下：`x = m+(m+1)+(m+2)+ … +(m+n-1)`，其中 m 为分解成的连续整数中最小的那一个，由 m 是大于等于 1 的正整数可知，`x =(2m+n-1)*n/2`，变换之后 `m =(2*x/n-n+1)/2`，由 m 的范围可以知道 `(2*x/n-n+1)/2 ≥ 1`，以上就是 x 和 n 的关系。给定一个 n，看是否 x 能分解成 n 个连续整数的和，可以判断是否存在 m，也就转换成 `(2*x/n-n+1)` 是否是偶数的问题。

```c++
int main() {
  int x = 45;
  int n = 3;
  int dm = 2 * x / n - n + 1;
  if (dm % 2 == 0) {
    int m = dm / 2;
    for (int i = 0; i < n; i++) {
      printf("%d\n", m + i);
    }
  }
  return 0;
}
```

## 找出数组中第 k 小的数

给定一个长度为 n 的整数数组，如何快速地求出该数组中第 k （k<=n）小的数。假如数组为 {4, 0, 1, 0, 2, 3}，那么第 3 小的元素是 1。

### 部分排序法

由于只需要找出第 k 小的数，因此，没必要对数组中所有的元素进行排序，可以采用部分排序的方法。

下面是冒泡排序的方法：

```c++
#include <iostream>

#define len(array) (sizeof(array) / sizeof(array[0]))

void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] += array[i];
    array[i] = array[j] - array[i];
    array[j] -= array[i];
  }
}

int find_kth_smallest(int array[], int length, int k) {
  for (int i = 0; i < k; i++) {
    for (int j = length - 1; j > i; j--) {
      if (array[j] < array[j - 1]) {
        swap(array, j, j - 1);
      }
    }
  }
  return array[k - 1];
}

int main() {
  int array[] = {5, 2, 3, 1, 4, 6};
  std::cout << find_kth_smallest(array, len(array), 3) << std::endl;
}
```

这种方法的时间复杂度为 O(n*k)。

### 类快速排序法

借鉴快速排序的划分算法，将数组 `array[low…high]` 中**下标为 i 的元素作为划分依据**，然后**把数组划分为三部分**：

1. `array[low…i-1]` 所有的元素的值都小于或等于 `array[i]`
2. `array[i]`
3. `array[i+1…high]` 所有的元素的值都大于 `array[i]`

当 i+1 正好为 k 时，算法结束，否则如果 i+1 大于 k，则继续从左半部分寻找，小于 k，则则继续从右半部分寻找。

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] += array[i];
    array[i] = array[j] - array[i];
    array[j] -= array[i];
  }
}

int partition(int array[], int begin, int end) {
  int val = array[begin];
  while (begin < end) {
    // array[begin] < val 不能是 <=，会造成第一个元素重复
    while (begin < end && array[begin] < val)
      begin++;
    while (begin < end && array[end] > val)
      end--;
    swap(array, begin, end);
  }
  array[begin] = val;
  return begin;
}

int find_kth_smallest(int array[], int length, int k) {
  int begin = 0, end = length - 1, m;

  while (begin < end) {
    m = partition(array, begin, end);
    if (m == k - 1)
      break;
    else if (m < k - 1) {
      begin = m + 1;
    } else {
      end = m - 1;
    }
  }

  return array[k - 1];
}
```

这种方法的时间复杂度为 O(k*log2n)。

## 在不排序的情况下求数组中的中位数

把问题转化为求一列数中第 i 小的数的问题，求中位数就是求一列数的第（length/2+1）小的数的问题。

## 在 O(n) 时间复杂度内查找数组中前三名

用 3 个变量分别记录前三名的分数，然后遍历数组，如果当前元素大于前三名中的任意一个，则更新前三名的分数。

```c++
int find_top3(int array[], int length, int &a, int &b, int &c) {
  if (length < 3) {
    return 0;
  }
  a = array[0], b = array[1], c = array[2];
  for (int i = 0; i < length; i++) {
    int &v = array[i];
    if (v != a && v != b && v != c) {
      if (v > a) {
        c = b, b = a, a = v;
      } else if (v > b) {
        c = b, b = v;
      } else if (v > c) {
        c = v;
      }
    }
  }
  return 1;
}
```

## 求数组中两个重复元素的最小距离

> 给定一个数组，数组中含有重复元素，给定两个数字 x 和 y，求这两个数字在数组中出现的位置的最小距离。

## 双重循环

遍历一次数组，找到与 x 相等的元素，然后再遍历一次数组，找到与 y 相等的元素，记录最小距离。

```c++
int find_xy_distance(int array[], int length, int x, int y) {
  int min_dist = length, dist;

  for (int i = 0; i < length; i++) {
    if (array[i] == x) {
      for (int j = 0; j < length; j++) {
        if (array[j] == y) {
          dist = abs(i - j);
          if (dist < min_dist) {
            min_dist = dist;
          }
        }
      }
    }
  }

  return min_dist;
}
```

时间复杂度为 O(n^2)。

### 位置记录法

用两个变量记录 x 和 y 的位置，遍历数组，如果当前元素等于 x，则更新 x 的位置，如果当前元素等于 y，则更新 y 的位置，记录最小距离。

```c++
int find_xy_distance(int array[], int length, int x, int y) {
  int min_dist = length;     // 记录最短距离，不可能超过数组长度
  int dist;                  // 临时计算距离
  int m = length, n = length;// 记录上一次 x，y 所在下标，初始化为数组长度，因为不可能取到

  for (int i = 0; i < length; i++) {
    // 更新最新下标
    if (array[i] == x)
      m = i;
    else if (array[i] == y)
      n = i;

    // 有更新才计算距离，避免 m，n 初始值的影响
    if (m == i || n == i) {
      dist = abs(m - n);
      if (dist < min_dist)
        min_dist = dist;
    }
  }

  return min_dist;
}

int main() {
  int array[] = {5, 2, 3, 1, 4, 1};
  std::cout << find_xy_distance(array, len(array), 1, 2) << std::endl;
}
```

## 求数组中绝对值最小的数

> 有一个升序排列的数组，数组中可能有正数、负数或 0，求数组中元素的绝对值最小的数。例如，数组 {-10, -5, -2,  7,  15,  50}，该数组中绝对值最小的数是 -2。

用二分法查找，如果中间元素的绝对值小于左右两边元素的绝对值，则返回中间元素，否则，如果中间元素的绝对值大于左边元素的绝对值，则绝对值最小的数在左边，否则在右边。

```c++
int find_min_abs(int array[], int length) {
  int begin = 0, end = length - 1, mid;

  while (begin < end) {
    // 都是正数
    if (array[begin] >= 0) {
      return array[begin];
    }

    // 都是负数
    if (array[end] <= 0) {
      return array[end];
    }

    // 一正一负
    if (end - begin == 1) {
      return array[begin] + array[end] > 0 ? array[begin] : array[end];
    }

    // 必然 begin < mid < end
    mid = (begin + end) / 2;

    // 0 是绝对值最小的数
    if (array[mid] == 0) {
      return 0;
    }

    // 处理边界情况
    if (array[mid - 1] < 0 && array[mid] > 0) {
      return array[mid - 1] + array[mid] > 0 ? array[mid - 1] : array[mid];
    }

    if (array[mid] < 0 && array[mid + 1] > 0) {
      return array[mid] + array[mid + 1] > 0 ? array[mid] : array[mid + 1];
    }

    if (array[mid] > 0)
      end = mid - 1;
    if (array[mid] < 0)
      begin = mid + 1;
  }

  return array[begin];
}

int main() {
  int array[] = {-4, -3, -1, 2, 4, 8};
  std::cout << find_min_abs(array, len(array)) << std::endl;
}
```

## 求数组连续最大和

> 一个有 n 个元素的数组，这 n 个元素既可以是正数也可以是负数，数组中连续的一个或多个元素可以组成一个连续的子数组，一个数组可能有多个这种连续的子数组，求子数组和的最大值。

用一个变量 `max_sum` 记录最大和，用一个变量 `sum` 记录当前和，遍历数组，如果当前和 `sum` 大于 0，则 `sum += array[i]`，否则 `sum = array[i]`，每次更新 `max_sum`。

```c++
int max_contiguous_sum(int array[], int length) {
  // 初始化为首元素
  int sum = array[0], max_sum = array[0];
  for (int i = 1; i < length; i++) {
    // 前值和为负数则重新开始
    sum = sum > 0 ? sum + array[i] : array[i];
    if (sum > max_sum)
      max_sum = sum;
  }
  return max_sum;
}
```

> 可能全是负数。

### 确定最大子数组的位置

```c++
int max_contiguous_sum(int array[], int length, int &begin, int &end) {
  // 初始化为首元素
  int sum = array[0], max_sum = array[0], p;

  for (int i = 1; i < length; i++) {
    // 前值和为负数则重新开始
    if (sum < 0) {
      sum = 0, p = i;
    }
    sum += array[i];
    if (sum > max_sum) {
      max_sum = sum;
      begin = p, end = i;
    }
  }

  return max_sum;
}
```

## 求集合的所有子集

> 有一个集合，求其全部子集（包含集合自身）。比如，给定一个集合 s，它包含两个元素 `<1, 2>`，则其全部的子集为 `<1, 12, 2>`。子集个数 Sn 与原集合元素个数 n 之间的关系满足如下等式：Sn=2^n-1。

### 位图法

1. 构造一个和集合一样大小的数组 A，分别与集合中的某个元素对应，数组 A 中的元素只有两种状态：“1” 和 “0”，分别代表每次子集输出中集合中对应元素是否要输出，这样数组 A 可以看作是原集合的一个标记位图。

2. 数组 A 模拟整数“加 1”的操作，每执行“加 1”操作之后，就将原集合中所有与数组 A 中值为“1”的相对应的元素输出。

设原集合为 `<a, b, c, d>`，数组 A 的某次“加1”后的状态为 `[1, 0, 1, 1]`，则本次输出的子集为 `<a, c, d>`。使用非递归的思想，如果有一个数组，大小为 n，那么就使用 n 位的二进制，如果对应的位为 1，那么就输出这个位，如果对应的位为 0，那么就不输出这个位。

```c++
void find_subsets(int array[], int length) {
  int size = length + 1;
  int *map = (int *) malloc(size * sizeof(int));
  memset(map, 0, size * sizeof(int));

  while (map[length] != 1) {
    for (int i = 0; i < size; i++) {
      if (map[i] == 0) {
        map[i] = 1;
        break;
      }
      map[i] = 0;
    }

    for (int i = 0; i < length; i++) {
      if (map[i] == 1) {
        printf("%d ", array[i]);
      }
    }
    printf("\n");
  }
}

int main() {
  int array[] = {1, 2, 3};
  find_subsets(array, len(array));
}
```

时间复杂度为 O(n*2^n)，空间复杂度 O(n)。

## 在有规律的二维数组中进行高效的数据查找

> 在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请实现一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

关键在于想到从二维数组的右上角遍历到左下角。右对角线的位置就是二分的位置，其左边都更小，下边都更大。



```c++
#define row 3
#define column 4

bool find_k(int array[row][column], int k) {
  int i = 0, j = column - 1, value;
  while (i < row && j >= 0) {
    value = array[i][j];
    if (value == k) {
      printf("array[%d][%d]=%d\n", i, j, k);
      return true;
    } else if (value < k) {
      i++;
    } else if (value > k) {
      j--;
    }
  }
  return false;
}

int main() {
  int array[row][column] = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
  };

  std::cout << std::boolalpha << find_k(array, 10);
}
```

## 寻找覆盖点最多的路径

> **坐标轴**上（即有序递增数组）从左到右依次的点为 `a[0]、a[1]、a[2]…a[n-1]`，求满足 `a[j]-a[i]<=L`、`a[j+1]-a[i]>L`，这两个条件的 `j` 与 `i` 中间的所有点个数中的最大值，即 `j-i+1` 最大。

```c++
int find_max_covered(int array[], int length, int threshold, int &begin, int &end) {
  int i = 0, j = 1, m, n, max = 0;

  while (j + 1 < length) {
    m = array[j] - array[i], n = array[j + 1] - array[i];
    if (m <= threshold && n > threshold) {
      if (j - i > max) {
        begin = i, end = j;
        max = end - begin + 1;
      }
      i++, j++;
    } else if (n <= threshold) {
      j++;
    } else if (m > threshold) {
      i++;
    }
  }

  return max;
}

int main() {
  int array[] = {1, 2, 4, 5, 6, 7, 8, 9};
  int begin = 0, end = 0;
  std::cout << find_max_covered(array, len(array), 6, begin, end) << std::endl;
  std::cout << "begin: " << begin << " end: " << end << std::endl;
  for (int i = begin; i <= end; ++i) {
    std::cout << array[i] << " ";
  }
}
```

## 判断请求能否在给定的存储条件下完成

> 给定一台有 m 个存储空间的机器，有 n 个请求需要在这台机器上运行，第 i 个请求计算时需要占 `R[i]` 空间，计算结果需要占 `O[i]` 个空间 `O[i] < R[i]`。请设计一个算法，判断这 n 个请求能否全部完成？若能，给出这 n 个请求的安排顺序。

首先对请求按照 `R[i]-O[i]` 由大到小进行排序，然后按照由大到小的顺序进行处理，如果按照这个顺序能处理完，则这 n 个请求能被处理完，否则处理不完。

```c++
void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] += array[i];
    array[i] = array[j] - array[i];
    array[j] -= array[i];
  }
}

void sort(int R[], int O[], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n - i; j++) {
      if (R[j] - O[j] > R[j - 1] - O[j - 1]) {
        swap(R, j, j - 1);
        swap(O, j, j - 1);
      }
    }
  }
}

bool schedule(int R[], int O[], int n, int m) {
  sort(R, O, n);
  for (int i = 0; i < n; i++) {
    if (R[i] > m) { // 判断是否有请求占用的空间大于机器的空间
      return false;
    }
    m -= O[i]; // 减去计算结果所占用的空间
  }
  return true;
}

int main() {
  int n = 8;
  int R[8] = {10, 15, 23, 20, 6, 9, 7, 16};// 计算时占用的空间
  int O[8] = {2, 7, 8, 4, 5, 8, 6, 8};     // 计算结果占用的空间

  sort(R, O, n);
  for (int i = 0; i < n; i++) {
    printf("%d %d,%d,%d\n", i, R[i], O[i], R[i] - O[i]);
  }

  std::cout << std::boolalpha << schedule(R, O, len(R), 1024);
}
```


## 根据规则构造新的数组

> 给定一个数组 `a[N]`，希望构造一个新的数组 `b[N]`，其中，`b[i]=a[0]*a[1]*…*a[N-1]/a[i]`。不允许使用除法， O(1) 空间复杂度和 O(n) 时间复杂度，除遍历计数器与 `a[n]`、`b[n]` 外，不可以使用新的变量（包括栈临时变量、堆空间和全局静态变量等）。

关键在于可以把 b[0] 当成临时储存空间，先把 b[0] 置为 1，然后从左到右遍历一遍，把 b[i] 置为 b[i - 1] * a[i - 1]，然后从右到左遍历一遍，把 b[i] 置为 b[i] * b[0]，b[0] 置为 b[N] * a[N - 1] * … * a[i]。

```c++
void construct(int a[], int b[], int n) {
  for (int i = 1; i < n; i++) {
    b[i] = b[i - 1] * a[i - 1];
  }

  for (int i = n - 1; i > 0; i--) {
    b[i] *= b[0];
    b[0] *= a[i];
  }
}

int main() {
  const int n = 4;
  int a[n] = {1, 2, 3, 4}, b[n] = {1};
  construct(a, b, n);
  for (int i = 0; i < n; i++) {
    printf("%d ", b[i]);
  }
}
```

## *求解迷宫问题

> 给定一个大小为 N×N 的迷宫，一只老鼠需要从迷宫的左上角（对应矩阵的 `[0][0]`）走到迷宫的右下角（对应矩阵的 `[N-1][M-1]`），老鼠只能向两方向移动：向右或向下。在迷宫中，0 表示没有路（是死胡同），1 表示有路。

尝试可能的路径，遇到岔路口时**保存其中一个方向**，然后尝试走另一个方向，当碰到死胡同的时候，**回溯到前一步**，然后从前一步出发继续寻找可达的路径。

```c++
int main() {
  const int N = 4, M = 4;
  int matrix[N][M] = {
      {1, 1, 1, 1},
      {1, 0, 0, 0},
      {1, 1, 1, 1},
      {1, 0, 0, 1},
  };

  int ways[N + M - 1][2] = {{0, 0}}, length = 1; // 正确路径
  int other_ways[N + M - 1][3], other_length = 0;// 分歧路径

  int i = 0, j = 0;

  // 限制条件相当重要
  while (i < M - 1 || j < N - 1) {
    if (i < M - 1 && matrix[i + 1][j] == 1) {
      other_ways[other_length][0] = i + 1;
      other_ways[other_length][1] = j;
      other_ways[other_length][2] = length;// 记录正确路径长度
      other_length++;
    }

    if (j < N - 1 && matrix[i][j + 1] == 1) {
      other_ways[other_length][0] = i;
      other_ways[other_length][1] = j + 1;
      other_ways[other_length][2] = length;
      other_length++;
    }

    // 回退一定是岔口，所以不用担心走重复路线
    int *next = other_ways[--other_length];
    i = next[0], j = next[1], length = next[2];
    ways[length][0] = i, ways[length][1] = j, length++;
  }

  for (i = 0; i < length; ++i) {
    printf("%d %d\n", ways[i][0], ways[i][1]);
  }
}
```

时间复杂度为 O(2^(N+M))，空间复杂度为 O(N+M)。

## 对任务进行调度

> 假设有一个中央调度机，有 n 个相同的任务需要调度到 m 台服务器上去执行，由于每台服务器的配置不一样，因此，服务器执行一个任务所花费的时间也不同。现在假设第 i 个服务器执行一个任务所花费的时间也不同。假设第 i 个服务器执行一个任务需要的时间为 `t[i]`。例如，有 2 个执行机 a 与 b，执行一个任务分别需要 7min 和 10min，有 6 个任务待调度。如果平分这 6 个任务，即 a 与 b 各 3 个任务，则最短需要 30min 执行完所有。如果 a 分 4 个任务，b 分 2 个任务，则最短 28min 执行完。请设计调度算法，使得所有任务完成所需要的时间最短。

每次比较两个服务器加上新任务后的总执行时间，将较短的服务器分配一个任务，直到所有任务分配完毕。

```c++
int main() {
  const int n = 6, m = 2;
  int t[m] = {7, 10};// 一个任务所花费的时间
  int c[m] = {0, 0}; // 全部任务所花费的时间

  for (int i = 0; i < n; i++) {
    int k = 0;
    for (int j = 1; j < m; j++) {
      if (t[j] + c[j] < t[k] + c[k]) {
        k = j;
      }
    }
    c[k] += t[k];
  }

  int k = 0;
  for (int i = 1; i < m; i++) {
    if (c[i] > c[k]) {
      k = i;
    }
  }

  printf("%d\n", c[k]);
}
```

时间复杂度为 O(n*m)，空间复杂度为 O(m)。

## 对磁盘分区

> 有 N 个磁盘，每个磁盘大小为 `D[i]（i=0…N-1）`，现在要在这 N 个磁盘上"顺序分配" M 个分区，每个分区大小为 `P[j]（j=0…M-1）`，顺序分配的意思是：分配一个分区 P[j] 时，如果当前磁盘剩余空间足够，则在当前磁盘分配；如果不够，则尝试下一个磁盘，直到找到一个磁盘 `D[i+k]` 可以容纳该分区，分配下一个分区 `P[j+1]` 时，则从当前磁盘 `D[i+k]` 的剩余空间开始分配，不在使用 `D[i+k]` 之前磁盘未分配的空间，如果这 M 个分区不能在这 N 个磁盘完全分配，则认为分配失败。

```c++
bool partition_disk(int D[], int P[], int i, int j) {
  int m = 0;

  for (int n = 0; n < j && m < i; n++) {
    if (D[m] < P[n])
      m++;
    D[m] -= P[n];
  }

  return m < i;
}

int main() {
  int D[] = {120, 120, 120};
  int P[] = {60, 60, 80, 20, 80};
  //  int P[] = {60, 80, 80, 20, 80};
  std::cout << partition_disk(D, P, len(D), len(P)) << std::endl;
}
```

时间复杂度为 Om)，空间复杂度为 O(1)。

## 求一个数组的全排列

> 给定长度为 n 的数组，则这 n 个数字共有 n! 种排列。

每次通过与首元素交换位置的方法固定一个数字，然后求剩下的数字的全排列，最后将首元素与固定的数字交换回来。

```c++
#include <cstdio>

#define len(array) (sizeof(array) / sizeof(array[0]))

void print_array(const int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[length - 1]);
}

void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] += array[i];
    array[i] = array[j] - array[i];
    array[j] -= array[i];
  }
}

void permutation(int array[], int length, int begin, int end) {
  if (begin == end) {
    print_array(array, length);
  } else {
    for (int i = begin; i <= end; i++) {
      swap(array, begin, i);
      permutation(array, length, begin + 1, end);
      swap(array, begin, i);
    }
  }
}

int main() {
  int array[] = {1, 2, 3,4};
  permutation(array, len(array), 0, len(array) - 1);
}
```

## 在二维数组中寻找最短路线

> 寻找一条从左上角（`array[0][0]`）到右下角（`array[m-1][n-1]`）的路线，使得沿途经过的数组中的整数的和最小。

用一个二维数组 `dist[m][n]` 来保存从左上角到当前位置的最小路径和，`dist[i][j] = min(dist[i-1][j], dist[i][j-1]) + array[i][j]`。

```c++
int min(int a, int b) {
  return a < b ? a : b;
}

int main() {
  const int m = 3, n = 3;
  int array[m][n] = {
      {1, 4, 3},
      {8, 7, 5},
      {2, 1, 5},
  };// 17

  // 记录距离
  int dist[m + 1][n + 1];
  memset(dist, 0, (m + 1) * (n + 1) * sizeof(int));

  // 处理边界情况，防止将边界认为是一条路线
  for (int i = 1; i < m; i++) {
    dist[i + 1][0] = dist[i][0] + array[i][0];
  }
  for (int i = 1; i < n; i++) {
    dist[0][i + 1] = dist[0][i] + array[0][i];
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      // 最短的路径一定是之前最短路径加上当前路径
      dist[i + 1][j + 1] = min(dist[i + 1][j], dist[i][j + 1]) + array[i][j];
    }
  }

  // 打印二维数组
  int x = m + 1, y = n + 1;
  for (int i = 0; i < x * y; ++i) {
    printf("%d ", dist[i / y][i % y]);
    if ((i + 1) % y == 0)
      printf("\n");
  }
}
```

时间复杂度为 O(mn)，空间复杂度为 O(mn)。
