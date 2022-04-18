---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP11"
url:  "posts/cpp/docs/CPP/CPP_11/第3章_C++新特性_CPP11"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [将 C99 标准纳入 C++11](#将-c99-标准纳入-c11)
  - [确定编译环境的预定义宏](#确定编译环境的预定义宏)
  - [__func__ 预定义标识符](#func-预定义标识符)
  - [_Pragma 操作符](#_pragma-操作符)
  - [不定参数宏定义以及 `__VA_ARGS__`](#不定参数宏定义以及-__va_args__)
  - [宽窄字符串连接](#宽窄字符串连接)
- [宏__cplusplus](#宏__cplusplus)
- [局部和匿名类型作为模板实参](#局部和匿名类型作为模板实参)
- [POD 类型](#pod-类型)
- [union 非受限联合体](#union-非受限联合体)
- [变长模板](#变长模板)
  - [模板参数包与递归](#模板参数包与递归)
  - [引用类型](#引用类型)
  - [特殊展开](#特殊展开)
  - [获取变长参数包长度](#获取变长参数包长度)
  - [模板的模板](#模板的模板)
- [快速退出：quick_exit, at_quick_exit](#快速退出quick_exit-at_quick_exit)
- [通用属性](#通用属性)
- [基于范围的 for 循环](#基于范围的-for-循环)
- [委托构造函数](#委托构造函数)
  - [不使用委托构造函数](#不使用委托构造函数)
  - [使用委托构造函数](#使用委托构造函数)
- [继承构造函数](#继承构造函数)
  - [不使用继承构造函数](#不使用继承构造函数)
  - [使用继承构造函数](#使用继承构造函数)
- [非受限联合体](#非受限联合体)
- [自定义字面量](#自定义字面量)
  - [字面量操作符](#字面量操作符)
- [内存对齐](#内存对齐)
  - [什么是内存对齐](#什么是内存对齐)
  - [为什么要内存对齐](#为什么要内存对齐)
- [随机数功能](#随机数功能)
- [正则表达式](#正则表达式)
- [新增数据结构](#新增数据结构)
- [新增算法](#新增算法)

## 将 C99 标准纳入 C++11

### 确定编译环境的预定义宏

- `__STDC_HOSTED__`：编译器的目标系统环境中是否包含完整的 C 库
- `__STDC__`：编译器对于标准 C 库的实现是否和 C 标准一致（是否定义、如何定义由编译器决定）
- `__STDC_VERSION__`：编译器支持的 C 标准的版本（是否定义、如何定义由编译器决定）
- `__STDC_ISO_10646__`：yyyymmL 格式的整数常量，表示 C++ 编译环境符合某个版本的 ISO/IEC 10646 标准

### __func__ 预定义标识符

函数中可以使用 `__func__` 标识符函数名称，编译器会在函数定义开始时隐式地插入 `__func__` 标识符定义：

```c++
static const char* __func__ = "<函数名称>";
```

### _Pragma 操作符

在之前的 C/C++ 标准中已经规定了可以使用 #pragma 预处理指令向编译器传递信息，比如可以通过在头文件首行放置 `#pragma once` 来告诉编译器这个头文件只应该被 include 一次。

C++11 中，规定了一个新的操作符 _Pragma，它的作用与 `#pragma` 完全相同，`_Pragma("once")` 就相当于 `#pragma once`。但是，_Pragma 由于**是一个操作符而不是预处理指令**，它的使用更为灵活，可以在宏中展开。

### 不定参数宏定义以及 `__VA_ARGS__`

C99 规定宏定义中，在参数列表的最后，可以使用...省略参数定义，而 `__VA_ARGS__` 可以用来**替换被省略号代表的字符串**。

### 宽窄字符串连接

## 宏__cplusplus

一般会和 `extern "C"` 配合使用，来让一个头文件即可以同时被 include 到 C 和 C++ 中编译，使用 `extern "C"` 避免 C++ 对符号名称进行重整，确保 C++ 编译器编译出的目标文件中的符号名维持原样。

```c++
#ifdef __cplusplus
extern "C" {
#endif
// 一些代码
#ifdef __cplusplus 
}
#endif
```

## 局部和匿名类型作为模板实参

C++98 禁止局部或者匿名的类型作为模板参数，这个限制没什么道理，因此 C++11 放宽了该限制。

```c++
// C++98中，只有A或者a可以作为模板参数
struct A {int a;} a;
// 匿名类型
typedef struct {int a;} B;
// 匿名类型变量
struct {int a;} b;

void test() {
    // 局部类型
 	struct C {int a;} c;
}
```

## POD 类型

POD，也就是 Plain Ordinary Data，纯数据类型。

C++11 对 POD 的定义是：平凡的，且是标准布局的。定义上，比 C++98 更宽容了，C++98 只规定了 C 风格的 struct 是 POD，但从 POD 的定义上，只要类对象布局是标准的，这样的类应该都是 POD 类。

## union 非受限联合体

C++11 将 C++98 对 union 的一些限制移除了。

- 在 C++98，union 中只能包含基础类型和 POD 类型，并且不能包含静态方法，但在 C++11 中，union 中可以包含任意非引用类型。
- C++11 中，如果 union 任何一个成员拥有非平凡的构造函数，那么编译器就不会为 union 生成默认构造函数。

- C++11 中，允许在类定义使用 union 声明成员变量，用这种方式声明的 union 不需要有类型名称，被称为匿名的非受限联合体，此时联合体内的所有成员都会自动的成为类的“变长成员”，即实际上它们共享同一处内存，应该只使用它们中的某一个。

## 变长模板

过去，C++可以使用C风格的方法来实现可变参函数，但这种实现方式是类型不安全的。

现在，C++11为可变参函数提出了更合理（类型安全）的解决方案：变长模板。可以使用变长模板来声明变长模板函数或者变长模板类。

### 模板参数包与递归

使用 `template <typename... Elements>` 这种方式可以声明一个变长模板参数，使用 `Elements...` 这种方式可以将变长模板参数展开成实际的多个参数类型；

不定长的变长模板类可以通过模板类的递归来解包：

```c++
template <typename... Elements> class tuple;	// 变长模板声明
// 以下是两个模板偏特化定义，利用模板偏特化会被优先匹配的规则，让变长模板参数递归地被解包
// 对于类型，可以使用递归的继承
template <typename Head, typename... Tail> 
class tuple <Head, Tail...> : private tuple<Tail...> {
	Head head;
}
template <> class tuple {};

// 对于函数，可以使用递归的函数调用
// 下面实现一个更强大的Printf，不论%后面跟的是什么符号，这个Printf总是会打印正确的类型
void Printf(const char* s) {
    while (*s) {
        if (*s == '%' && ++s != '%') {
         	   throw runtime_error("invalide format");
        }
        cout *s++;
    }
}

template <typename T, typename... Args>
void Printf(char* s, T value, Args... args) {
	while(*s) {
    	if (*s == '%' && *s++ != '%') {
        	cout << value;
            return Printf(++s, args...);
        }
        cout << *s++;
    }
    // 若百分号的数量和参数数量对不上，就抛异常
    throw runtime_error("extra arguments provided");
}
```

### 引用类型

定义了模板参数包后，还可以在展开模板参数包时使用引用标记：Args&&...，这样的写法是合法的；

### 特殊展开

解包时，有些非常特殊的规则，需要特别说明一下：

```c++
template <typename... Args> class MyCls: private A<Args>... {};
// 上面的表达式在解包时会解包成多继承：
T<Parent1, Parent2>  t;	// t的类型是：class MyCls: private A<Parent1>, A<Parent2>

template <typename Args...> class MyCls: private A<Args...> {};
// 而这个表达式在解包时，会在泛型参数表达式中直接展开
T<Parent1, Parent2>  t;	// t的类型是：class MyCls: private A<Parent1, Parent2>

template <typename Args...> void test(Args... args) {
    // 下面这个会被展开成call(a(arg1), a(arg2), ...)
	call(a(args)...);
    // 而下面这个会被展开成call(a(arg1, arg2, ...))
    call(a(args...));
}
```

### 获取变长参数包长度

可以使用 `sizeof...` 获取模板参数包的长度；

### 模板的模板

变长参数的模板类型本身也可以是一个模板，这一点和以前的非变长模板参数一样。

## 快速退出：quick_exit, at_quick_exit

在过去，大体上有三种退出程序的方式：terminate(), abort(), exit()。

- terminate 是有未处理的异常时会被调用的方法，可以使用 set_terminate 方法更改默认行为，terminate 默认调用 abort ；
- abort 是进程不得不终止时，被调用的函数，它会向本进程发送一个 SIGABRT 信号，该信号默认会导致操作系统直接释放该进程的所有资源并终止进程；
- exit 是进程自发调用的退出函数，它代表着进程运行到了某个节点，该退出了，它会导致每一个自动变量的析构函数被调用（是的，仅自动变量，也就是栈变量会被调用析构函数，至于单例什么的需要自己处理），并调用 at_exit 注册的函数，然后才会回收进程；

C++11 新增了 quick_exit 标准方法，该方法语意上和 exit 一样，都是程序自发终止，但和 exit 不同的是，它不会进行本进程的清理工作，在多线程环境下也不会先等待线程结束，而是直接让操作系统终止进程并回收资源。

## 通用属性

有时 C/C++ 提供的语言能力无法完全满足开发者的需求，编译器厂商为了解决这些问题，提供了一系列的语言扩展来扩展 C/C++ 的语法。这其中最常见的就是“属性”，可以告诉编译器一个符号的额外信息，让编译器做一些语言规范之外的处理。

- GNU 使用`__attribute__((<属性列表>))`来声明属性；
- Windows 使用 `__declspec(<属性列表>)` 来声明属性

C++11 也规定了类似的属性，之所以在语言中添加属性，是为了避免再给 C++ 增加更多的关键字。C++11 的属性和之前各个平台的编译器实现的属性的目的是一致的，它们提供的能力都是一般用不到，可以忽略的能力，语言规范不会考虑使用关键字来实现这些能力，因此将它们定义到通用属性里。C++ 规定通用属性的写法是：`[[<属性列表>]]`，这样的通用属性可以用来修饰任何语言元素。不过目前 C++11 只定义了两个通用属性：`[[noreturn]]` 和 `[[carries_dependency]]`。

## 基于范围的 for 循环

自定义集合类型要想支持这样的 for 循环，需要实现 begin, end, ++, ==四个函数。

```c++
vector<int> vec;

for (auto iter = vec.begin(); iter != vec.end(); iter++) { // before c++11
    cout << *iter << endl;
}

for (int i : vec) { // c++11基于范围的for循环
    cout << "i" << endl;
}
```

## 委托构造函数

可以在构造函数的 initializer-list 中调用另一个构造函数来完成构造，这种将构造委托给另一个构造函数的行为  就叫委派构造函数。

一旦在 initializer-list 中进行了委派构造，就不能再用正常的 initializer-list 初始化成员变量了。因此，通常被委派的构造函数会负责初始化类的所有成员变量。

使用初始化列表还可以促使编译器检查类型收窄的情况。初始化列表是目前唯一一种检查类型收窄的方式（不过事实上现在的大多数编译器在没有使用初始化列表时也会检查类型收窄并给出警告，但使用初始化列表编译器会直接给出错误）。

委托构造函数允许在同一个类中一个构造函数调用另外一个构造函数，可以在变量初始化时简化操作，通过代码来感受下委托构造函数的妙处：

### 不使用委托构造函数

```c++
struct A {
    A(){}
    A(int a) { a_ = a; }

    A(int a, int b) { // 好麻烦
        a_ = a;
        b_ = b;
    }

    A(int a, int b, int c) { // 好麻烦
        a_ = a;
        b_ = b;
        c_ = c;
    }

    int a_;
    int b_;
    int c_;
};
```

### 使用委托构造函数

```c++
struct A {
    A(){}
    A(int a) { a_ = a; }

    A(int a, int b) : A(a) { b_ = b; }

    A(int a, int b, int c) : A(a, b) { c_ = c; }

    int a_;
    int b_;
    int c_;
};
```

## 继承构造函数

继承关系中，子类可以自动或得父类的成员和接口，但构造函数无法自动地被子类继承。因为通常子类也有自己的成员，我们要定义子类自己的构造函数，在子类构造函数中去调用父类构造函数以及初始化自己的成员。

但是，如果子类中没有任何成员，或者其成员都用 C++11 的新特性“快速初始化成员变量”进行了初始化乃至于没有必要再用构造函数初始化了，那这时候我们很可能希望直接将父类的构造函数继承到子类，毕竟这时候只需要初始化父类成员。

C++11 允许我们使用 `using <父类名>::<父类名>` 来将所有父类构造函数引入子类，被 using 引入的父类构造函数是隐式声明的（也就是说，只有用到的函数才会被生成，以节省生成的代码）。

继承构造函数可以让派生类直接使用基类的构造函数，如果有一个派生类，希望派生类采用和基类一样的构造方式，可以直接使用基类的构造函数，而不是再重新写一遍构造函数。

### 不使用继承构造函数

```c++
struct Base {
    Base() {}
    Base(int a) { a_ = a; }

    Base(int a, int b) : Base(a) { b_ = b; }

    Base(int a, int b, int c) : Base(a, b) { c_ = c; }

    int a_;
    int b_;
    int c_;
};

struct Derived : Base {
    Derived() {}
    Derived(int a) : Base(a) {} // 好麻烦
    Derived(int a, int b) : Base(a, b) {} // 好麻烦
    Derived(int a, int b, int c) : Base(a, b, c) {} // 好麻烦
};

int main() {
    Derived a(1, 2, 3);
    return 0;
}
```

### 使用继承构造函数

```c++
struct Base {
    Base() {}
    Base(int a) { a_ = a; }

    Base(int a, int b) : Base(a) { b_ = b; }

    Base(int a, int b, int c) : Base(a, b) { c_ = c; }

    int a_;
    int b_;
    int c_;
};

struct Derived : Base {
    using Base::Base;
};

int main() {
    Derived a(1, 2, 3);
    return 0;
}
```

只需要使用using Base::Base继承构造函数，就免去了很多重写代码的麻烦。

## 非受限联合体

C++11 之前 union 中数据成员的类型不允许有非 POD 类型，而这个限制在 c++11 被取消，允许数据成员类型有非 POD 类型，看代码：

```c++
struct A {
    int a;
    int *b;
};

union U {
    A a; // 非 POD 类型 c++11 之前不可以这样定义联合体
    int b;
};
```

POD 类型，可以理解为对象可以直接 memcpy 的类型。

## 自定义字面量

C++11 可以自定义字面量，例如：

```c++
std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 100ms
std::this_thread::sleep_for(std::chrono::seconds(100)); // 100s
```

其实没必要这么麻烦，也可以这么写：

```c++
std::this_thread::sleep_for(100ms); // c++14里可以这么使用
std::this_thread::sleep_for(100s);
```

这就是自定义字面量的使用，示例如下：

```c++
struct mytype {
    unsigned long long value;
};
constexpr mytype operator"" _mytype ( unsigned long long n ) {
    return mytype{n};
}
mytype mm = 123_mytype;
cout << mm.value << endl;
```

### 字面量操作符

- 接收字符串：<用户类型> operator "" _<后缀字符>(const char* col, size_t size)
- 接收整数：<用户类型> operator "" _<后缀字符>(unsigned long long val)

- 接收整数，但整数越界，此时会传入'\0'结尾的char*：<用户类型> operator "" _<后缀字符>(const char*)
- 接收浮点：<用户类型> operator "" _<后缀字符>(long double val)

- 接收字符：<用户类型> operator "" _<后缀字符>(char val)

## 内存对齐

C 和 C++ 都是具备直接操作底层硬件能力的语言，因此某些开发者会对数据结构的对齐方式特别关注。

C++11 规定了 alignof 和 alignas 关键字，前者可以查询某个类型的对齐方式（一般来说都是 32 位 -4 字节或者 64 位 -8 字节对齐），而后者可以规定某个自定义类的对齐方式。比如如果我们想要使用内联汇编的向量指令（可以同时处理 4 组处理器位数的数据）来优化处理速度，就可能想要将数据对齐到 `4 * 处理器位数`的位置处。

需要注意的是，之前很多编译器也规定了指定数据对齐方式的方式，比如 GNU 就规定可以使用如下方式规定对齐字节：`__attribute__((__aligned__(8)))`；

需要注意的是，虽然标准规定了指定对齐的方式，但每个平台具体支持对齐到多少是不确定的。如果使用 `alignas(2 ^ 64)`，那显然是不合法的。不幸的是，目前标准似乎没办法查询每个平台支持的最大对齐字节。不过一般来说我们也用不到太大的对齐字节。

### 什么是内存对齐

理论上计算机对于任何变量的访问都可以从任意位置开始，然而实际上系统会对这些变量的存放地址有限制，通常将变量首地址设为某个数 N 的倍数，这就是内存对齐。

### 为什么要内存对齐

1. 硬件平台限制，内存以字节为单位，不同硬件平台不一定支持任何内存地址的存取，一般可能以双字节、4 字节等为单位存取内存，为了保证处理器正确存取数据，需要进行内存对齐。
2. 提高 CPU 内存访问速度，一般处理器的内存存取粒度都是 N 的整数倍，假如访问 N 大小的数据，没有进行内存对齐，有可能就需要两次访问才可以读取出数据，而进行内存对齐可以一次性把数据全部读取出来，提高效率。

在 C++11 之前如果想创建内存对齐需要：

```c++
void align_cpp11_before(){
    static char data[sizeof(void *) + sizeof(A)];
    const uintptr_t kAlign = sizeof(void *) - 1;
    char *align_ptr =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(data + kAlign) & ~kAlign);
    A *attr = new (align_ptr) A;
}
```

## 随机数功能

C++11 关于随机数功能则较之前丰富了很多，典型的可以选择概率分布类型，先看如下代码：

```c++
#include <time.h>

#include <iostream>
#include <random>

using namespace std;

int main() {
    std::default_random_engine random(time(nullptr));

    std::uniform_int_distribution<int> int_dis(0, 100); // 整数均匀分布
    std::uniform_real_distribution<float> real_dis(0.0, 1.0); // 浮点数均匀分布

    for (int i = 0; i < 10; ++i) {
        cout << int_dis(random) << ' ';
    }
    cout << endl;

    for (int i = 0; i < 10; ++i) {
        cout << real_dis(random) << ' ';
    }
    cout << endl;

    return 0;
}
```

输出：

```
38 100 93 7 66 0 68 99 41 7
0.232202 0.617716 0.959241 0.970859 0.230406 0.430682 0.477359 0.971858 0.0171148 0.64863
```

代码中举例的是整数均匀分布和浮点数均匀分布，C++11 提供的概率分布类型还有好多，例如伯努利分布、正态分布等，具体可以见最后的参考资料。

## 正则表达式

C++11 引入了 regex 库更好的支持正则表达式，见代码：

```c++
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main() {
    std::string s = "I know, I'll use2 regular expressions.";
    // 忽略大小写
    std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::icase);
    if (std::regex_search(s, self_regex)) {
        std::cout << "Text contains the phrase 'regular expressions'\n";
    }

    std::regex word_regex("(\\w+)");  // 匹配字母数字等字符
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found " << std::distance(words_begin, words_end) << " words\n";

    const int N = 6;
    std::cout << "Words longer than " << N << " characters:\n";
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > N) {
            std::cout << " " << match_str << '\n';
        }
    }

    std::regex long_word_regex("(\\w{7,})");
    // 超过7个字符的单词用[]包围
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';
}
```

## 新增数据结构

- `std::forward_list`：单向链表，只可以前进，在特定场景下使用，相比于 `std::list` 节省了内存，提高了性能

```c++
std::forward_list<int> fl = {1, 2, 3, 4, 5};
for (const auto &elem : fl) {
    cout << elem;
}
```

- std::unordered_set：基于 hash 表实现的 set，内部不会排序，使用方法和 set 类似
- std::unordered_map：基于 hash 表实现的 map，内部不会排序，使用方法和 set 类似
- std::array：数组，在越界访问时抛出异常，建议使用 std::array 替代普通的数组
- std::tuple：元组类型，类似 pair，但比 pair 扩展性好

```c++
typedef std::tuple<int, double, int, double> Mytuple;
Mytuple t(0, 1, 2, 3);
std::cout << "0 " << std::get<0>(t);
std::cout << "1 " << std::get<1>(t);
std::cout << "2 " << std::get<2>(t);
std::cout << "3 " << std::get<3>(t);
```

## 新增算法

- all_of：检测表达式是否对范围 [first, last) 中所有元素都返回 true，如果都满足，则返回 true

```c++
std::vector<int> v(10, 2);
if (std::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; })) {
    std::cout << "All numbers are even\n";
}
```

- any_of：检测表达式是否对范围[first, last)中至少一个元素返回 true，如果满足，则返回 true，否则返回 false，用法和上面一样
- none_of：检测表达式是否对范围[first, last)中所有元素都不返回 true，如果都不满足，则返回 true，否则返回 false，用法和上面一样
- find_if_not：找到第一个不符合要求的元素迭代器，和 find_if 相反
- copy_if：复制满足条件的元素
- itoa：对容器内的元素按序递增

```c++
std::vector<int> l(10);
std::iota(l.begin(), l.end(), 19); // 19为初始值
for (auto n : l) std::cout << n << ' ';
// 19 20 21 22 23 24 25 26 27 28
```

- minmax_element：返回容器内最大元素和最小元素位置

```c++
int main() {
    std::vector<int> v = {3, 9, 1, 4, 2, 5, 9};

    auto result = std::minmax_element(v.begin(), v.end());
    std::cout << "min element at: " << *(result.first) << '\n';
    std::cout << "max element at: " << *(result.second) << '\n';
    return 0;
}
// min element at: 1
// max element at: 9
```

- is_sorted、is_sorted_until：返回容器内元素是否已经排好序。
