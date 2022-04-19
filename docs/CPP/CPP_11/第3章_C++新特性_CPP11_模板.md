---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP11_模板"
url:  "posts/cpp/docs/CPP/CPP_11/第3章_C++新特性_CPP11_模板"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [模板的右尖括号](#模板的右尖括号)
- [模板的别名](#模板的别名)
- [函数模板的默认模板参数](#函数模板的默认模板参数)

C++11 关于模板有一些细节的改进：

- 模板的右尖括号
- 模板的别名
- 函数模板的默认模板参数

## 模板的右尖括号

C++11之前是不允许两个右尖括号出现的，会被认为是右移操作符，所以需要中间加个空格进行分割，避免发生编译错误。

```c++
#include <vector>

int main() {
    std::vector<std::vector<int>> a; // error
    std::vector<std::vector<int> > b; // ok
}
```

## 模板的别名

C++11 引入了 using，可以轻松的定义别名，而不是使用繁琐的 typedef。

使用 using 明显简洁并且易读，大家可能之前也见过使用 typedef 定义函数指针之类的操作。

```c++
#include <functional>
#include <iostream>

typedef void (*func1)(int, int);
using func2 = void (*)(int, int);

void func(const std::function<void(int, int)> &f) {
  f(1, 2);
}

int main() {
  func([](int x, int y) { std::cout << x + y; });
}
```

上面的代码使用 using 比 typedef 容易看的懂一些。

但用 std::function()、std::bind()、std::placeholder()、lambda 表达式更好。

## 函数模板的默认模板参数

C++11 之前只有类模板支持默认模板参数，函数模板是不支持默认模板参数的，C++11 后都支持。

```c++
template <typename T, typename U=int>
class A {
    T value;  
};

template <typename T=int, typename U> // error
class A {
    T value;  
};
```

**类模板**的默认模板参数**必须从右往左定义**，而函数模板则没有这个限制。

```c++
#include <iostream>

using std::cout;
using std::endl;

template<typename R, typename U = int>
R func1(U val) {
  return val;
}

template<typename R = int, typename U>
R func2(U val) {
  return val;
}

int main() {
  cout << func1<int, double>(99.9) << endl;   // 99
  cout << func1<double, double>(99.9) << endl;// 99.9
  cout << func1<double>(99.9) << endl;        // 99.9
  cout << func1<int>(99.9) << endl;           // 99
  cout << func2<int, double>(99.9) << endl;   // 99
  cout << func1<double, double>(99.9) << endl;// 99.9
  cout << func2<double>(99.9) << endl;        // 99.9
  cout << func2<int>(99.9) << endl;           // 99
  return 0;
}
```
