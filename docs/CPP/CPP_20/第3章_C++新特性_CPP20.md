---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP20"
url:  "posts/cpp/docs/CPP/CPP_20/第3章_C++新特性_CPP20"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [char8_t](#char8_t)
- [concept](#concept)
  - [引入概念的目的](#引入概念的目的)
  - [约束的种类](#约束的种类)
  - [Requires 子句](#requires-子句)
  - [Requires 表达式](#requires-表达式)
  - [Concepts 的定义](#concepts-的定义)
  - [Concept 的使用方法](#concept-的使用方法)
  - [concept 的组合(与或非)](#concept-的组合与或非)
- [requires](#requires)
  - [用在定义中](#用在定义中)
  - [进行约束嵌套或组合](#进行约束嵌套或组合)
  - [简单约束](#简单约束)
  - [类型约束](#类型约束)
  - [复合约束](#复合约束)
  - [嵌套约束](#嵌套约束)
- [consteval](#consteval)
- [co_await](#co_await)
- [co_yield](#co_yield)
- [co_return](#co_return)
- [export](#export)

## char8_t

char8_t UTF-8 字符表示的类型，要求大到足以表示任何 UTF-8 编码单元（ 8 位）。它与 unsigned char 具有相同的大小、符号性和对齐（从而与 char 和 signed char 具有相同的大小和对齐），但它是独立的类型。

## concept

概念是指给一组要求（Requirements）所起的名字。概念是一种具名谓词。使用这些要求和概念可以给函数和类模板的参数加上约束（Constraints）。

### 引入概念的目的

* 约束成为模板界面的一部分
* 基于概念的重载成为可能
* 模板的出错信息更加友好
* 没有约束的 auto 和有约束的概念得到统一

### 约束的种类

* 合取（conjunction） 约束的合取: 使用 && 运算符
* 析取（disjunction） 约束的析取: 使用 || 运算符
* 原子约束（atomic constraint）

### Requires 子句

Requires 子句由关键字 requires 后加上常量表达式构成，用于指定约束。

### Requires 表达式

Requires 表达式是 bool 类型的右值表达式，用于表达约束。其形式为 

```
requires ( 形参列表(可选) ) { 要求序列 }
```

要求序列中的要求有以下四种形式：

* 简单要求（simple requirement）
  * 简单要求是任意表达式语句。
* 类型要求（type requirement）
  * 类型要求是关键字 typename 加一个类型名。
* 复合要求（compound requirement）
  * { 表达式 } noexcept(可选) 返回类型要求(可选) ;
  * 返回类型要求 - -> 类型约束
* 嵌套要求（nested requirement）
  * reuires 约束表达式 ;

### Concepts 的定义

```C++
template < template-parameter-list >
concept  concept-name = constraint-expression;
```

其中，constraint-expression 是一个可以被 eval 为 bool 的表达式或者编译期函数。在使用定义好的 concept 时，constraint-expression 会根据上面 template-parameter-list 传入的类型，执行编译期计算，判断使用该 concept 的模板定义是否满足。如果不满足，则编译期会给定一个具有明确语义的错误，即 这个 concept 没有匹配成功啦啦这种。注意到，上述匹配的行为都是在编译期完成的，因此 concept 其实是 zero-cost 的。举个例子来描述一下，最基本的 concept 的定义。

```C++
// 一个永远都能匹配成功的concept
template <typename T>
concept always_satisfied = true; 

// 一个约束T只能是整数类型的concept，整数类型包括 char, unsigned char, short, ushort, int, unsinged int, long等。
template <typename T>
concept integral = std::is_integral_v<T>;

// 一个约束T只能是整数类型，并且是有符号的concept
template <typename T>
concept signed_integral = integral<T> && std::is_signed_v<T>;
```

接下来，我们再简单示例一下如何使用一个 concept：

```C++
// 任意类型都能匹配成功的约束，因此mul只要支持乘法运算符的类型都可以匹配成功。
template <always_satisfied T>
T mul(T a, T b) {
    return a * b;
}

// 整型才能匹配add函数的T
template <integral T>
T add(T a, T b) {
    return a + b;
}

// 有符号整型才能匹配subtract函数的T
template <signed_integral T>
T subtract(T a, T b) {
    return a - b;
}

int main() {
    mul(1, 2); // 匹配成功, T => int
    mul(1.0f, 2.0f);  // 匹配成功，T => float

    add(1, -2);  // 匹配成功, T => int
    add(1.0f, 2.0f); // 匹配失败, T => float，而T必须是整型
    subtract(1U, 2U); // 匹配失败，T => unsigned int,而T必须是有符号整型
    subtract(1, 2); // 匹配成功, T => int
}
```

### Concept 的使用方法

与 auto 关键字的一些结合方式：

```C++
// 约束函数模板方法1
template <my_concept T>
void f(T v);

// 约束函数模板方法2
template <typename T>
requires my_concept<T>
void f(T v);

// 约束函数模板方法3
template <typename T>
void f(T v) requires my_concept<T>;

// 直接约束C++14的auto的函数参数
void f(my_concept auto v);

// 约束模板的auto参数
template <my_concept auto v>
void g();

// 约束auto变量
my_concept auto foo = ...;
```

Concept 当然也可以用在 lambda 函数上，使用方法跟上面一样：

```C++
// 约束lambda函数的方法1
auto f = []<my_concept T> (T v) {
  // ...
};
// 约束lambda函数的方法2
auto f = []<typename T> requires my_concept<T> (T v) {
  // ...
};
// 约束lambda函数的方法3
auto f = []<typename T> (T v) requires my_concept<T> {
  // ...
};
// auto函数参数约束
auto f = [](my_concept auto v) {
  // ...
};
// auto模板参数约束
auto g = []<my_concept auto v> () {
  // ...
};
```

### concept 的组合(与或非)

concept 的本质是一个模板的编译期的 bool 变量，因此它可以使用 C++ 的与或非三个操作符。例如，我们可以在定义 concept 的时候，使用其他 concept 或者表达式，进行逻辑操作。

```C++
template <typename T>
concept Integral = std::is_integral<T>::value;
template <typename T>
concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
template <typename T>
concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;
```

当然，我们也可以在使用 concept 的时候使用逻辑操作符。

```C++
template <typename T>
requires Integral<T> && std::is_signed_v<T>
T add(T a, T b);
```

## requires

### 用在定义中

requires 关键字不仅能用在 concept 的使用上，也可以用在定义中。 例如

```C++
// requires用在使用concept时
template <typename T>
  requires my_concept<T>
void f(T);

// requires用在concept的定义，它表达了类型T的参数f，必须符合大括号内的模式，也就是能被调用。
// 也就是它是一个函数或者一个重载了operator()的类型
template <typename T>
concept callable = requires (T f) { f(); }; 

template <typename T>
  requires requires (T x) { x + x; } // `requires` 同时使用在concept的定义和使用上
T add(T a, T b) {
  return a + b;
}
``

requires 的语法理解：requires 后接的东西本质上是一个表达式

```C++
// requires后面接的是一个正在被eval的concept，用在上面的concept的使用中。
requires evaled-concept

// 本质上，concept在evaluate时，是一个编译期返回结果为bool的表达式。这种其实等价于上面那种。
requires expression

// 例如 下面这种就是requires后直接接个bool表达式了
template <typename T>
requires std::is_integral_v<T>
T add(T a, T b) {
    return a + b;
}
```

### 进行约束嵌套或组合

为了提高 concept 定义的能力，requires 支持用大括号的语法，进行多个约束分开表达，这些约束之间的关系是与的关系。requires 的这种方式的语法形式是：

```C++
requires { requirement-seq }
requires ( parameter-list(optional) ) { requirement-seq }
```

这里每个 requirement-seq 是可以由多行约束组成，每一行之间以分号分隔。这些约束的形式有以下几种：

* 简单约束(Simple Requirements)
* 类型约束(Type Requirements)
* 复合约束(Compound Requirements)
* 嵌套约束(Nested Requirements)

### 简单约束

简单约束就是一个任意的表达式，编译器对这个约束的检查就是检查这个表达式是否是合法的。注意，不是说这个表达式在编译期运行返回 true 或者 false。而是这个表达式是否合法。 例如

```C++
template<typename T>
concept Addable =
requires (T a, T b) {
    a + b; // "the expression a+b is a valid expression that will compile"
};

// example constraint from the standard library (ranges TS)
template <class T, class U = T>
concept Swappable = requires(T&& t, U&& u) {
    swap(std::forward<T>(t), std::forward<U>(u));
    swap(std::forward<U>(u), std::forward<T>(t));
};
```

### 类型约束

类型的约束是类似模板里面的参数一样，在 typename 后接一个类型。这个约束表达的含义是该类型在该 concept 进行 evaluate 时，必须是存在的。如下面的例子：

```C++
struct foo {
    int foo;
};

struct bar {
    using value = int;
    value data;
};

struct baz {
    using value = int;
    value data;
};

// Using SFINAE, enable if `T` is a `baz`.
template <typename T, typename = std::enable_if_t<std::is_same_v<T, baz>>>
struct S {};

template <typename T>
using Ref = T&;

template <typename T>
concept C = requires {
    // Requirements on type `T`:
    typename T::value;  // A) has an inner member named `value`
    typename S<T>;     // B) must have a valid class template specialization for `S`
    typename Ref<T>;   // C) must be a valid alias template substitution
};

template <C T>
void g(T a);

g(foo{}); // ERROR: Fails requirement A.
g(bar{}); // ERROR: Fails requirement B.
g(baz{}); // PASS.
```

### 复合约束

复合约束用于约束表达式的返回值的类型。它的写法形式为：

```C++
// 这里 ->和type-constraint是可选的.
{expression} noexcept(optional) -> type-constraint;
```

这里的约束的行为主要有三点，并且约束进行 evaluate 的顺序按照以下顺序：

* 模板类型代换到表达式中是否使得表达式合法
* 如果用了noexcept,表达式必须不能可能抛出异常.
* 如果用了->后的类型约束, 则按照以下步骤进行evaluate
* 代换模板类型到 type-constraint中,
* 并且 decltype((expression))的类型必须满足type-constraint的约束.

上述步骤任何一个失败，则 evaluate 的结果是 false.

```C++
template <typename T>
concept C = requires(T x) {
  {*x} -> typename T::inner; // the type of the expression `*x` is convertible to `T::inner`
  {x + 1} -> std::same_as<int>; // the expression `x + 1` satisfies `std::same_as<decltype((x + 1))>`
  {x * 1} -> T; // the type of the expression `x * 1` is convertible to `T`
};
```

### 嵌套约束

requires 内部还可以嵌套 requires。这种方式被称为嵌套的约束，它的形式为：

```C++
requires constraint-expression ;
```

例如：

```C++
template <class T>
concept Semiregular = DefaultConstructible<T> &&
    CopyConstructible<T> && Destructible<T> && CopyAssignable<T> &&
requires(T a, size_t n) {  
    requires Same<T*, decltype(&a)>;  // nested: "Same<...> evaluates to true"
    { a.~T() } noexcept;  // compound: "a.~T()" is a valid expression that doesn't throw
    requires Same<T*, decltype(new T)>; // nested: "Same<...> evaluates to true"
    requires Same<T*, decltype(new T[n])>; // nested
    { delete new T };  // compound
    { delete new T[n] }; // compound
};
```

## consteval

consteval 关键字，用来修饰函数时常量值的表达式，而且是强制性的。如果函数本身不是常量值的表达式的话则会编译失败。

constexpr 修饰函数时其实只是告诉编译器该函数可以按常量值的表达式去优化，但是如果函数本身不是常量值的表达式的话依然能够编译通过。

```C++
constexpr int add100_constexpr(int n) {
  return n + 100;
}
 
consteval int add100_consteval(int n) {
  return n + 100;
}
 
void test() {
    constexpr int c_constexpr = add100_consteval(200);
    int x = 200;
    // int d_consteval = add100_consteval(x);   // 编译失败
    int d_constexpr = add100_constexpr(x);      //编译成功，constexpr并非强制限定为常量表达式
}
```

## co_await

co_await 可以挂起和恢复函数的执行。

## co_yield

co_yield 可以在不结束协程的情况下从协程返回一些值。因此，可以用它来编写无终止条件的生成器函数。

## co_return

co_return 允许从协程返回一些值，需要自行定制。


## export

C++20 不使用并保留该关键词。
