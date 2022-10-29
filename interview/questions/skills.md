---
date: 2022-10-29T10:20:13+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "编程技巧"  # 文章标题
url:  "posts/cpp/interview/questions/skills"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 当 while() 的循环条件是赋值语句时会出现什么情况

```c++
#include <iostream>

int main() {
  while (int i = 0) {
    std::cout << i << std::endl;
    i--;
  }

  while (int i = 1) {
    std::cout << i << std::endl;
    i--;
  }

  return 0;
}
```

以上代码不执行任何动作，相当于执行了 while(0) 操作，循环结束，while 循环体不执行。而在 while 的循环条件里面定义一个变量并赋值为非 0 时，相当于执行了 while(1)，程序进入无限循环。

## 不使用 if/?:/switch 及其他判断语句如何找出两个 int 型变量中的最大值和最小值

```c++
int max=((a+b)+abs(a-b))/2
int min=((a+b)-abs(a-b))/2
```

## C 语言获取文件名的宏定义是什么

某些标识符是预定义的，扩展后将生成特定的信息，它们同预处理器表达式运算符 #define 一样，不能取消定义或重新定义。

| 函数 | 描述 |
| -------- | -------- |
| `__FILE__` | 包含当前程序文件名的字符串，包含了详细路径 |
| `__LINE__` | 包含当前源文件行数的十进制常量 |
| `__DATE__` | 包含编译日期的字符串字面值 |
| `__STDC__` | 如果编译器遵循 ANSIC 标准，它就是一个非零值 |
| `__TIME__` | 包含编译时间的字符串字面值 |
| `__FUNC__` | 当前所在函数名，在编译器的较高版本中支持 |

其中，标识符 `__LINE__` 和 `__FILE__` 通常用来调试程序，标识符 `__DATE__` 和 `__TIME__` 通常用来在编译后的程序中加入一个时间标志，以区分程序的不同版本。当要求程序严格遵循 ANSIC 标准时，标识符 `__STDC__` 就会被赋值为 1。

## 表达式 a>b>c 是什么意思

```c++
#include <iostream>

int main() {
  int a = 5, b = 4, c = 3;
  std::cout << std::boolalpha << (a > b > c) << std::endl;
  return 0;
}
```

对于这种连续运算，根据优先级，首先进行 a>b 的比较判断。本例中，由于 a 的值为 5，b 的值为 4，表达式 a>b 为真，所以返回值为 1，接着比较该返回值与 c 的大小。因为 c 的值为 3，1>c 表达式为假，所以返回值为 0。所以，程序的输出结果为 0。

```c++
#include <iostream>

int main() {
  int b, c;
  int a = (b = (c = 020) && (1 == 2));
  std::cout << a << b << c << std::endl;
  return 0;
}
```

在赋值语句中，c = 020，因为以 0 开头的数字一般表示的都是八进制的数值，所以转换成十进制的数为 16。根据优先级关系，b 的值为 (c = 020) && (1 == 2) 的结果，由于 c = 020 是一个赋值语句，所以该赋值语句的返回值为真，即为 1，而 1 == 2 为假，返回值为 0，所以 b 的值为 0，a = (b = 0)，因此 a 的值为 0。

## 如何打印自身代码

用常规的 printf 语句输出是得不到与自身代码一模一样的结果的，因为这涉及一个自身嵌套的问题。

```c++
#include <cstdio>

int func(int a, int b) {
  return a + b;
}

int main() {
  FILE *fp = fopen(__FILE__, "r");
  if (fp == nullptr) {
    return 1;
  }

  char c;
  while ((c = fgetc(fp)) != EOF) {
    putchar(c);
  }

  fclose(fp);
  return 0;
}
```

通过 fopen 函数打开自身文件，然后通过 fgetc 函数逐个字符读取文件内容，最后通过 putchar 函数输出到屏幕上。

## 如何实现一个最简单的病毒

可以把最简单的病毒理解为一个无限运行的恶意程序，无限运行可以通过无限循环实现，而恶意可以通过申请内存空间来实现，所以可以用如下代码来实现一个最简单的病毒。

```c++
#include <cstdio>

int main() {
  while (1) {
    int *p = new int[100000000];
    printf("p = %p\n", p);
  }

  return 0;
}
```

实际上，不能跟预期的那样，很快就报错了，看不到内存占用增加。

```
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
```

## 如何只使用一条语句实现 x 是否为 2 的若干次幂的判断

```c++
#include <iostream>

int main() {
  int x = 8;
  std::cout << std::boolalpha << ((x & (x - 1)) == 0) << std::endl;
  return 0;
}
```

## 如何定义一对相互引用的结构

用常规的定义相互引用的结构一般容易出现类似于死锁一样的问题。例如，A 引用 B 的成员，B 也引用 A 的成员，由于 C 语言需要先声明后使用，所以常规的方法会引起编译器错误。

```c++
struct b;

struct a {
  int afield;
  struct b *bpointer;
};

struct b {
  int bfield;
  struct a *apointer;
};
```

结构体的自引用（self reference）就是在结构体内部，包含指向自身类型结构体的指针。结构体的相互引用（mutual reference）即在多个结构体中，都包含指向其他结构体的指针。

## 已知随机数函数 rand7()，如何构造 rand10() 函数

要保证 rand10() 产生的随机数是整数 1～10 的均匀分布，可以构造一个 1～10 * n 的均匀分布的随机整数区间（n 为任意正整数）。假设 x 是这个 1～10 * n 区间上的一个随机数，那么 x%10+1 就是均匀分布在 1～10 区间上的整数。

根据题意，rand7() 函数返回 1～7 的随机数，那么 rand7()-1 则得到一个离散整数集合，该集合为 {0，1，2，3，4，5，6}，该集合中每个整数的出现概率都为 1/7。那么，(rand7()-1) * 7 得到另一个离散整数集合 A，该集合元素为 7 的整数倍，即 {0，7，14，21，28，35，42}，其中每个整数的出现概率也都为 1/7。而由于 rand7() 得到的集合 B = {1，2，3，4，5，6，7}，其中每个整数出现的概率也为 1/7。显然，集合 A 与集合 B 中任何两个元素组合可以与 1～49 之间的一个整数一一对应，即 1～49 之间的任何一个数，可以唯一确定 A 和 B 中两个元素的一种组合方式，反过来也成立。由于 A 和 B 中元素可以看成是独立事件，根据独立事件的概率公式 P(AB) = P(A)P(B)，得到每个组合的概率是 1/7 * 1/7 = 1/49。因此，(rand7()-1) * 7+rand7() 生成的整数均匀分布在 1～49 之间，每个数的概率都是 1/49。

所以，(rand7()-1) * 7+rand7() 可以构造出均匀分布在 1～49 的随机数。为了将 49 种组合映射为 1～10 之间的 10 种随机数，需要进行截断，即将 41～49 这样的随机数剔除掉，得到的数 1～40 仍然是均匀分布在 1～40 的，这是因为每个数都可以看成一个独立事件。

## printf("%p\n",(void*)x) 与 printf("%p\n",&x) 有什么区别

printf("%p\n",(void *)x) 语句把 x 强制转换为指针类型的变量输出，也就是说，把 x 的值当作一个地址输出。printf("%p\n",&x) 语句将打印变量x的地址。

```c++
#include <cstdio>

int main() {
  int x = 0x100;

  printf("%p\n", (void *) x);
  printf("%p\n", &x);
}
```

输出：

```c++
0000000000000100
000000936cfffbac
```

## main() 主函数执行完毕后，是否会再执行一段代码

可以。例如，可以用 atexit 注册一个函数，它会在 main 之后执行 int fn(void)。需要注意的是，使用 atexit() 函数需要添加头文件 stdlib.h，否则会报编译错误。

```c++
#include <cstdio>
#include <cstdlib>

void fn() {
  printf("next\n");
}

int main() {
  atexit(fn);
  printf("first\n");
  return 0;
}
```

需要注意的是，在 C 语言中，用户代码也可以调用 main() 函数，程序示例如下：

```c++
#include <cstdio>

int main();

void run() {
  printf("run\n");
  main();
}

int main() {
  printf("main\n");
  run();
}
```

上例中，程序运行一段时间会中断，递归却没有终止。

```c++

```
