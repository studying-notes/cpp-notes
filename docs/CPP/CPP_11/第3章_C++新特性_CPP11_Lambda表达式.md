---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP11_Lambda表达式"
url:  "posts/cpp/docs/CPP/CPP_11/第3章_C++新特性_CPP11_Lambda表达式"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [std::function](#stdfunction)
  - [参考实例](#参考实例)
- [std::bind](#stdbind)
  - [具体示例](#具体示例)
- [Lambda 表达式](#lambda-表达式)
- [Lambda 表达式的基本语法](#lambda-表达式的基本语法)
- [将 Lambda 传递到函数指针](#将-lambda-传递到函数指针)
- [Lambda 表达式中的变量捕获](#lambda-表达式中的变量捕获)
- [Lambda 表达式、函数对象和函子](#lambda-表达式函数对象和函子)

C++11 新增了 `std::function`、`std::bind`、`lambda` 表达式等封装使函数调用更加方便。

## std::function

讲 `std::function` 前首先需要了解下什么是可调用对象

满足以下条件之一就可称为可调用对象：

- 是一个函数指针
- 是一个具有`operator()`成员函数的类对象(传说中的仿函数)，lambda 表达式
- 是一个可被转换为函数指针的类对象
- 是一个类成员(函数)指针
- bind 表达式或其它函数对象

而 `std::function` 就是上面这种可调用对象的封装器，可以把 `std::function` 看做一个函数对象，用于表示函数这个抽象概念。`std::function` 的实例可以存储、复制和调用任何可调用对象，存储的可调用对象称为 `std::function` 的目标，若 `std::function` 不含目标，则称它为空，调用空的 `std::function` 的目标会抛出 `std::bad_function_call` 异常。

### 参考实例

```c++
std::function<void(int)> f;// 这里表示function的对象f的参数是int，返回值是void
```

```c++
#include <functional>
#include <iostream>

struct Foo {
  Foo(int num) : num_(num) {}
  void print_add(int i) const { std::cout << num_ + i << '\n'; }
  int num_;
};

void print_num(int i) { std::cout << i << '\n'; }

struct PrintNum {
  void operator()(int i) const { std::cout << i << '\n'; }
};

int main() {
  // 存储自由函数
  std::function<void(int)> f_display = print_num;
  f_display(-9);

  // 存储 lambda
  std::function<void()> f_display_42 = []() { print_num(42); };
  f_display_42();

  // 存储到 std::bind 调用的结果
  std::function<void()> f_display_31337 = std::bind(print_num, 31337);
  f_display_31337();

  // 存储到成员函数的调用
  std::function<void(const Foo &, int)> f_add_display = &Foo::print_add;
  const Foo foo(314159);
  f_add_display(foo, 1);
  f_add_display(314159, 1);

  // 存储到数据成员访问器的调用
  std::function<int(Foo const &)> f_num = &Foo::num_;
  std::cout << "num_: " << f_num(foo) << '\n';

  // 存储到成员函数及对象的调用
  using std::placeholders::_1;
  std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
  f_add_display2(2);

  // 存储到成员函数和对象指针的调用
  std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
  f_add_display3(3);

  // 存储到函数对象的调用
  std::function<void(int)> f_display_obj = PrintNum();
  f_display_obj(18);
}
```

从上面可以看到 `std::function` 的使用方法，当给 `std::function` 填入合适的参数表和返回值后，它就变成了可以容纳所有这一类调用方式的函数封装器。`std::function` 还可以用作回调函数，或者在 C++ 里如果需要使用回调那就一定要使用 `std::function`，特别方便。

## std::bind

使用 `std::bind` 可以将可调用对象和参数一起绑定，绑定后的结果使用 `std::function` 进行保存，并延迟调用到任何需要的时候。

`std::bind` 通常有两大作用：

- 将可调用对象与参数一起绑定为另一个`std::function`供调用
- 将n元可调用对象转成m(m < n)元可调用对象，绑定一部分参数，这里需要使用`std::placeholders`

### 具体示例

```c++
#include <functional>
#include <iostream>
#include <memory>

void f(int n1, int n2, int n3, const int &n4, int n5) {
  std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << std::endl;
}

int g(int n1) { return n1; }

struct Foo {
  void print_sum(int n1, int n2) { std::cout << n1 + n2 << std::endl; }
  int data = 10;
};

int main() {
  using namespace std::placeholders;// 针对 _1, _2, _3...

  // 演示参数重排序和按引用传递
  int n = 7;
  // （ _1 与 _2 来自 std::placeholders ，并表示将来会传递给 f1 的参数）
  auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
  n = 10;
  f1(1, 2, 1001);// 1 为 _1 所绑定， 2 为 _2 所绑定，不使用 1001
  // 进行到 f(2, 42, 1, n, 7) 的调用

  // 嵌套 bind 子表达式共享占位符
  auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
  f2(10, 11, 12);// 进行到 f(12, g(12), 12, 4, 5); 的调用

  // 绑定指向成员函数指针
  Foo foo;
  auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
  f3(5);

  // 绑定指向数据成员指针
  auto f4 = std::bind(&Foo::data, _1);
  std::cout << f4(foo) << std::endl;

  // 智能指针亦能用于调用被引用对象的成员
  std::cout << f4(std::make_shared<Foo>(foo)) << std::endl;
}
```

## Lambda 表达式

Lambda 表达式定义了一个匿名函数，不仅具有函数指针的灵活性，还可以通过捕获局部变量提高可扩展性。

Lambda 表达式把函数看作对象。Lambda 表达式可以像对象一样使用，比如可以将它们赋给变量和作为参数传递，还可以像函数一样对其求值。

当一个函数需要将另一个函数用作参数时，可以使用 Lambda。

```c++
auto func = [capture] (params) opt -> ret { func_body; };
```

其中 `func` 是可以当作 `lambda` 表达式的名字，作为一个函数使用，`capture` 是捕获列表，`params` 是参数表，`opt` 是函数选项 (mutable 之类 )，ret 是返回值类型，func_body 是函数体。

一个完整的 lambda 表达式：

```c++
auto func1 = [](int a) -> int { return a + 1; };
auto func2 = [](int a) { return a + 2; };
cout << func1(1) << " " << func2(2) << endl;
```

如上代码，很多时候lambda表达式返回值是很明显的，c++11 允许省略表达式的返回值定义。

`lambda`表达式允许捕获一定范围内的变量：

- `[]`不捕获任何变量
- `[&]`引用捕获，捕获外部作用域所有变量，在函数体内当作引用使用

- `[=]`值捕获，捕获外部作用域所有变量，在函数内内有个副本使用
- `[=, &a]`值捕获外部作用域所有变量，按引用捕获a变量

- `[a]`只值捕获a变量，不捕获其它变量
- `[this]`捕获当前类中的this指针

lambda表达式示例代码：

```c++
int a = 0;
auto f1 = [=](){ return a; }; // 值捕获a
cout << f1() << endl;

auto f2 = [=]() { return a++; }; // 修改按值捕获的外部变量，error
auto f3 = [=]() mutable { return a++; };
```

代码中的f2是编译不过的，因为修改了按值捕获的外部变量，其实lambda表达式就相当于是一个仿函数，仿函数是一个有`operator()`成员函数的类对象，这个`operator()`默认是`const`的，所以不能修改成员变量，而加了`mutable`，就是去掉`const`属性。

还可以使用 lambda 表达式自定义 stl 的规则，例如自定义 sort 排序规则：

```c++
struct A {
    int a;
    int b;
};

int main() {
    vector<A> vec;
    std::sort(vec.begin(), vec.end(), [](const A &left, const A &right) { return left.a < right.a; });
}
```

**清单 1**

```c++
#include <cstdlib>
#include <iostream>

static int compareInt(const void *p1, const void *p2) {
  int i = *((int *) p1);
  int j = *((int *) p2);
  return (i < j);
}

int main() {
  int list[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  qsort((void *) list, 10, sizeof(int), compareInt);

  for (int i : list) {
    std::cout << i << " ";
  }

  std::cout << std::endl;

  return 0;
}
```

清单 1 中的代码有以下几点不足：

- 比较函数需要单独声明。这增加了将错误的比较函数传递给 qsort() 操作的风险。
- 比较函数接受 void * 参数，因此缺失了某种程度的类型检查。
- 比较函数看不到任何局部作用的变量。因此，如果存在其他影响排序的因素，必须在更大范围内声明。

清单 2 显示重新编写后的清单 1 中的示例，将 C++ std::sort() 算法与 lambda 表达式结合使用。由于 std::sort() 是一个模板，因此会保留所有类型信息。注意如何在通常出现函数名的位置编写 lambda 表达式。

**清单 2**

```c++
#include <algorithm>
#include <iostream>

int main() {
  int list[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  std::sort(list, &list[10], [](int x, int y) { return x < y; });

  for (int i = 0; i < 10; i++) {
    std::cout << i << " ";
  }

  std::cout << std::endl;

  return 0;
}
```

## Lambda 表达式的基本语法

Lambda 表达式本质上与函数声明非常类似。我们可以提取清单 2 中的 lambda 表达式，详加说明。提取的 lambda 表达式如清单 3 所示：

```c++
[](int x, int y){ return x < y ; }
```

**清单 3**

如果我们将 lambda 表达式比作函数，可以看到它与函数名对应的是一对空的方括号，即*捕获表达式*。这些括号表示后面跟着一个 lambda 表达式。这些方括号不必为空；稍后将讨论其内容。

如果 lambda 主体只含一个返回类型，则暗示返回的表达式类型为 lambda 返回类型。如果要显式指定返回类型，需使用新的 C++11 语法表示函数声明中的后置返回类型。对于返回类型 T 的普通函数，您可以这样编写：

```c++
auto foo(...) -> T { ... }
```

对于 lambda，您需要要这样编写：

```c++
[] (...) -> T { ... }
```

lambda 表达式的其余部分与常规 C 或 C++ 函数主体类似。

## 将 Lambda 传递到函数指针

C++11 标准库中有一个名为 function 的模板，它可以接受指定类型的函数或者具有匹配的返回类型和参数列表的 lambda。这将产生一个指向函数类型的指针，例如，清单 4 可用作函数参数类型，接受 int 参数，返回 void。您可以向其传递任何类似匹配函数或 lambda 的内容。

```c++
std::function<void(int)>
```

**清单 4**

清单 5 显示的函数扫描一个数组，对每个元素应用一个给定函数。

```c++
#include <functional>

void scan(int *list, int length, const std::function<void(int)>& process) {
  for (int i = 0; i < length; i++) {
    process(list[i]);
  }
}
```

**清单 5**

清单 6 显示如何通过传递一个函数或 lambda 表达式作为参数来调用 scan() 函数。

**清单 6**

```c++
  int list[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  scan(list, 10, [](int i) -> void {
    std::cout << i << " ";
  });
```

## Lambda 表达式中的变量捕获

到目前为止，我们对 lambda 表达式的处理基本与标准函数调用类似：传入参数，返回结果。然而，在函数主体中声明的 lambda 表达式还是可以捕获在声明 lambda 处可见的函数的任何局部变量。

假设我们需要使用函数 scan()，但希望 process 函数只对大于某个阈值的值起作用。我们不能修改 scan()，不能让 scan() 向 process 函数传递多个参数。但如果我们将一个 lambda 表达式传递给 scan() 函数，则可以从其环境捕获一个局部变量。

在清单 7 中，我们将希望捕获的变量放在方括号中，即放在捕获表达式中。这实际上向 lambda 表达式中额外传递了一个参数，但无需更改 scan 函数的定义。就像传递参数给函数一样，我们实际上是在函数的调用点捕获值 threshold 的副本，这称为*通过值捕获*。

**清单 7**

```c++
#include <algorithm>
#include <functional>
#include <iostream>

void scan(int *list, int length, const std::function<void(int)> &process) {
  for (int i = 0; i < length; i++) {
    process(list[i]);
  }
}

int main() {
  int threshold = 5;

  int list[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  scan(list, 10, [threshold](int v) { if (v>threshold) { std::cout <<v<<" "; } });

  return 0;
}
```

有一个简写形式 [=]，表示“通过值捕获每个变量”。在清单 8 中，我们将函数调用重新编写为使用这种更短的表达式。

**清单 8**

```c++
  scan(list, 10, [=](int v) { if (v>threshold) { std::cout <<v<<" "; } });
```

**注**：通过值捕获变量意味着生成局部副本。如果有多个局部变量，全部捕获可能会导致 lambda 产生显著开销。

但有些情况下，我们希望修改捕获的变量。例如，假设我们要计算最大值并将其存储在变量 max 中。在这种情况下，我们不想使用该变量值的副本，而是希望使用该变量的引用，这样，我们就可以在模板中修改该变量。这称为*通过引用捕获变量*。清单 9 显示了这样一个示例。

**清单 9**

```c++
#include <algorithm>
#include <functional>
#include <iostream>

void scan(int *list, int length, const std::function<void(int)> &process) {
  for (int i = 0; i < length; i++) {
    process(list[i]);
  }
}

int main() {
  int max = 0;
  int threshold = 5;

  int list[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  std::sort(list, &list[10], [](int x, int y) { return (x < y); });

  scan(list, 10, [threshold, &max](int v) {
    if (v > max) {
      max = v;
    }
    if (v > threshold) {
      std::cout << v << " ";
    }
  });

  std::cout << "max=" << max << std::endl;

  return 0;
}
```

同样，也有一个简写形式 [&]，用于应通过引用捕获每个变量的情况。

```cpp
  scan(list, 10, [&](int v) {
    if (v > max) {
      max = v;
    }
    if (v > threshold) {
      std::cout << v << " ";
    }
  });
```

## Lambda 表达式、函数对象和函子

虽然 lambda 表达式是 C++11 的新特性，但用这种方式访问现有语言特性的确很方便。lambda 表达式是*函数对象* 的速记表示法。函数对象是一个具有成员 operator()()（函数调用运算符）的类类型对象，因此可以像函数一样调用。函数对象类型被称作*函子*。清单 10 显示了一个函子的示例。

**清单 10**

```c++
class compare_ints {
public:
  compare_ints(int j, int k) : l(j), r(k) {}
  bool operator()() const { return l < r; }

private:
  int l, r;
};
```

您可以创建一个 compare_ints 对象，用两个整型值初始化，如果第一个值小于第二个值，使用函数调用运算符返回 true：

```c++
  int j = 1, k = 2;
  
  compare_ints comp(j, k);
  bool less_than = comp();
```

也可以动态创建一个临时对象，然后直接使用：

```c++
bool less_than = compare_ints(j, k)();
```

使用 lambda 表达式不必创建和命名函子类即可达到这种效果。编译器为您创建一个匿名函子，如清单 11 所示。

**清单 11**

```c++
auto comp = [](int j, int k) { return j < k; };  
bool less_than =  comp(l,r);
```

在清单 11 中，comp 是匿名函子类型的对象。

您也可以动态执行此操作：

```c++
bool less_than = [l,r]() { return l < r; }();
```
