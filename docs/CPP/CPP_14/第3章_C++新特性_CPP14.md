---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP14"
url:  "posts/cpp/docs/CPP/CPP_14/第3章_C++新特性_CPP14"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [函数返回值类型推导](#函数返回值类型推导)
- [lambda 参数 auto](#lambda-参数-auto)
- [变量模板](#变量模板)
- [别名模板](#别名模板)
- [constexpr 的限制](#constexpr-的限制)
- [[[deprecated]]标记](#deprecated标记)
- [二进制字面量与整形字面量分隔符](#二进制字面量与整形字面量分隔符)
- [std::make_unique](#stdmake_unique)
- [std::shared_timed_mutex与std::shared_lock](#stdshared_timed_mutex与stdshared_lock)
- [std::integer_sequence](#stdinteger_sequence)
- [std::exchange](#stdexchange)
- [std::quoted](#stdquoted)

## 函数返回值类型推导

C++14 对函数返回类型推导规则做了优化，先看一段代码：

```CPP
#include <iostream>

using namespace std;

auto func(int i) {
  return i;
}

int main() {
  cout << func(4) << endl;
  return 0;
}
```

使用 C++11 编译：

```
error: 'func' function uses 'auto' type specifier without trailing return type
 auto func(int i) {
                ^
```

上面的代码使用 C++11 是不能通过编译的，通过编译器输出的信息也可以看见这个特性需要到 C++14 才被支持。

返回值类型推导也可以用在模板中：

```CPP
#include <iostream>

using namespace std;

template<typename T> auto func(T t) { return t; }

int main() {
    cout << func(4) << endl;
    cout << func(3.4) << endl;
    return 0;
}
```

注意：函数内如果有多个 return 语句，它们必须返回相同的类型，否则编译失败。

```CPP
auto func(bool flag) {
    if (flag) return 1;
    else return 2.3; // error
}
// inconsistent deduction for auto return type: ‘int’ and then ‘double’
```

如果 return 语句返回初始化列表，返回值类型推导也会失败。

```CPP
auto func() {
    return {1, 2, 3}; // error returning initializer list
}
```

如果函数是虚函数，不能使用返回值类型推导。

```CPP
struct A {
	// error: virtual function cannot have deduced return type
	virtual auto func() { return 1; } 
}
```

返回类型推导可以用在前向声明中，但是在使用它们之前，翻译单元中必须能够得到函数定义。

```CPP
auto f();               // declared, not yet defined
auto f() { return 42; } // defined, return type is int

int main() {
	cout << f() << endl;
}
```

返回类型推导可以用在递归函数中，但是递归调用必须以至少一个返回语句作为先导，以便编译器推导出返回类型。

```CPP
auto sum(int i) {
    if (i == 1)
        return i;              // return int
    else
        return sum(i - 1) + i; // ok
}
```

## lambda 参数 auto

在 C++11 中，lambda 表达式参数需要使用具体的类型声明：

```CPP
auto f = [] (int a) { return a; }
```

在 C++14 中，对此进行优化，lambda 表达式参数可以直接是 auto：

```CPP
auto f = [] (auto a) { return a; };
cout << f(1) << endl;
cout << f(2.3f) << endl;
```

## 变量模板

C++14 支持变量模板：

```CPP
template<class T>
constexpr T pi = T(3.1415926535897932385L);

int main() {
    cout << pi<int> << endl; // 3
    cout << pi<double> << endl; // 3.14159
    return 0;
}
```

## 别名模板

C++14 也支持别名模板：

```CPP
template<typename T, typename U>
struct A {
    T t;
    U u;
};

template<typename T>
using B = A<T, int>;

int main() {
    B<double> b;
    b.t = 10;
    b.u = 20;
    cout << b.t << endl;
    cout << b.u << endl;
    return 0;
}
```

## constexpr 的限制

C++ 中一直存在着常量表达式的概念，在 C++98 中我们可以这样定义一个常量

```cpp
const int SIZE = 100005;
```

常量将无法修改，并且这也是编译器的一个优化机会，编译器往往会在编译时就处理好常量表达式的值，并在程序中硬编码结果，也就是不会在程序运行时再去计算表达式的值。

```cpp
const int MOD = 1e9 + 7;

// source code
ans = ans % MOD;

// after compilation
ans = ans % 1000000007; // yes, 1e9 + 7 has been calculated
ans = ans % (1e9 + 7); // no
```

另外，常量可以用来初始化数组

```cpp
int len = 10;
int a[len]; // compile error

const int len = 10;
int a[len]; // ok
```

C++14 相较于 C++11 对 constexpr 减少了一些限制：

C++11 中 constexpr 函数可以使用递归，在 C++14 中可以使用局部变量和循环

```CPP
constexpr int factorial(int n) { // C++14 和 C++11均可
    return n <= 1 ? 1 : (n * factorial(n - 1));
}
```

在 C++14 中可以这样做：

```CPP
constexpr int factorial(int n) { // C++11中不可，C++14中可以
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        ret += i;
    }
    return ret;
}
```

C++11 中 constexpr 函数必须必须把所有东西都放在一个单独的 return 语句中，而 constexpr 则无此限制：

```CPP
constexpr int func(bool flag) { // C++14 和 C++11均可
    return 0;
}
```

在C++14 中可以这样：

```CPP
constexpr int func(bool flag) { // C++11中不可，C++14中可以
    if (flag) return 1;
    else return 0;
}
```

C++11 允许将函数作为常量表达式，但是 C++11 要求函数必须恰由一条 `return` 语句组成，而 C++14 解除了这一限制，但你仍需要保证函数中没有：

- `goto` 语句

- 未进行初始化的变量定义

```cpp
int a; // no
int a = 10; // yes
```

- 非字面类型的变量定义（算术类型如 `int` 属于字面类型，而自定义类型如 `string` 属于非字面类型

## [[deprecated]]标记

C++14 中增加了 deprecated 标记，修饰类、变、函数等，当程序中使用到了被其修饰的代码时，编译时被产生警告，用户提示开发者该标记修饰的内容将来可能会被丢弃，尽量不要使用。

```CPP
struct [[deprecated]] A { };

int main() {
    A a;
    return 0;
}
```

当编译时，会出现如下警告：

```CPP
warning: ‘A’ is deprecated [-Wdeprecated-declarations]
     A a;
       ^
 ```

## 二进制字面量与整形字面量分隔符

C++14 引入了二进制字面量，也引入了分隔符：

```CPP
int a = 0b0001'0011'1010;
double b = 3.14'1234'1234'1234;
```

## std::make_unique

C++11 中有 std::make_shared，却没有 std::make_unique，在 C++14 已经改善。

```CPP
struct A {};
std::unique_ptr<A> ptr = std::make_unique<A>();
```

## std::shared_timed_mutex与std::shared_lock

C++14 通过 std::shared_timed_mutex 和 std::shared_lock 来实现读写锁，保证多个线程可以同时读，但是写线程必须独立运行，写操作不可以同时和读操作一起进行。

实现方式如下：

```CPP
struct ThreadSafe {
    mutable std::shared_timed_mutex mutex_;
    int value_;

    ThreadSafe() {
        value_ = 0;
    }

    int get() const {
        std::shared_lock<std::shared_timed_mutex> loc(mutex_);
        return value_;
    }

    void increase() {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        value_ += 1;
    }
};
```

## std::integer_sequence

```CPP
#include <iostream>
#include <utility>

template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq) {
  std::cout << "The sequence of size " << int_seq.size() << ": ";
  ((std::cout << ints << ' '), ...);
  std::cout << '\n';
}

int main() {
  print_sequence(std::integer_sequence<int, 9, 2, 5, 1, 9, 1, 6>{});
  return 0;
}
```

输出：

```
7 9 2 5 1 9 1 6
```

std::integer_sequence 和 std::tuple 的配合使用：

```CPP
template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(std::index_sequence<Is...>, F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <typename S, typename F, typename T>
auto map_filter_tuple(F&& f, T& t) {
    return map_filter_tuple(S{}, std::forward<F>(f), t);
}
```

## std::exchange

```CPP
#include <iostream>
#include <utility>
#include <vector>

int main() {
  std::vector<int> v;
  std::exchange(v, {1, 2, 3, 4});
  std::cout << v.size() << std::endl;
  for (int a : v) {
    std::cout << a << " ";
  }
  return 0;
}
```

看样子貌似和 std::swap 作用相同，那它俩有什么区别呢？

可以看下 exchange 的实现：

```CPP
template<class T, class U = T>
constexpr T exchange(T& obj, U&& new_value) {
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}
```

可以看见 new_value 的值给了 obj，而没有对 new_value 赋值！

## std::quoted

C++14 引入 std::quoted 用于给字符串添加双引号，直接看代码：

```CPP
int main() {
    string str = "hello world";
    cout << str << endl;
    cout << std::quoted(str) << endl;
    return 0;
}
```

编译&输出：

```
"hello world"
```
