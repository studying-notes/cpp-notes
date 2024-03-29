---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP11_新增关键字"
url:  "posts/cpp/docs/CPP/CPP_11/第3章_C++新特性_CPP11_新增关键字"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [auto](#auto)
  - [推导规则](#推导规则)
  - [何时用](#何时用)
- [decltype](#decltype)
  - [基本用法](#基本用法)
  - [与 const 结合](#与-const-结合)
  - [与引用结合](#与引用结合)
  - [与指针结合](#与指针结合)
- [与 auto 结合](#与-auto-结合)
  - [decltype 和 auto 差异](#decltype-和-auto-差异)
  - [推导规则](#推导规则-1)
- [class](#class)
  - [class & struct](#class--struct)
  - [strcut 和 class 的区别](#strcut-和-class-的区别)
  - [final & override](#final--override)
- [enum class](#enum-class)
  - [不带作用域的枚举代码](#不带作用域的枚举代码)
  - [有作用域的枚举代码](#有作用域的枚举代码)
  - [底层枚举类型](#底层枚举类型)
- [explicit](#explicit)
  - [不用 explicit](#不用-explicit)
  - [使用 explicit](#使用-explicit)
- [default](#default)
  - [情景分析](#情景分析)
  - [内联](#内联)
- [delete](#delete)
- [export](#export)
- [extern](#extern)
- [inline](#inline)
- [mutable](#mutable)
- [sizeof](#sizeof)
  - [C++11 前](#c11-前)
  - [C++11 后](#c11-后)
- [struct](#struct)
- [using](#using)
  - [去除作用域的限制](#去除作用域的限制)
  - [解除函数隐藏](#解除函数隐藏)
  - [代替 typedef，给类型命名](#代替-typedef给类型命名)
- [thread_local](#thread_local)
  - [案例](#案例)
- [static_assert](#static_assert)
- [nullptr](#nullptr)
- [noexcept](#noexcept)
  - [noexcept 指定符](#noexcept-指定符)
  - [noexcept 运算符](#noexcept-运算符)
- [const](#const)
  - [用于定义常量](#用于定义常量)
  - [指针常量](#指针常量)
  - [传参避免拷贝](#传参避免拷贝)
  - [修饰类成员变量](#修饰类成员变量)
  - [修饰类成员函数](#修饰类成员函数)
  - [修饰类对象](#修饰类对象)
- [char16_t 和 char32_t](#char16_t-和-char32_t)
  - [产生原因](#产生原因)
- [alignof 和 alignas](#alignof-和-alignas)
- [chrono 时间库](#chrono-时间库)
  - [duration](#duration)
  - [time_point](#time_point)
  - [clocks 时钟](#clocks-时钟)
    - [steady_clock 相对于系统开机启动的时间](#steady_clock-相对于系统开机启动的时间)
    - [system_clock 当前的系统时钟](#system_clock-当前的系统时钟)
    - [high_resolution_clock 系统可用的最高精度的时钟](#high_resolution_clock-系统可用的最高精度的时钟)

## auto

C++11 标准和 C++98/03 标准的 auto 是不同的。

C++98/03 标准中，auto 表示自动储存类型 ； C++11 标准中，auto 表示由编译器静态判断其应有的类型。

**C++98 auto**

```C++
int a =10 ;  //拥有自动生命期
auto int b = 20 ;//拥有自动生命期
static int c = 30 ;//延长了生命期
```

**C++11 auto**

auto 可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型。

```C++
int a = 10;
auto b = a;//自动推断类型，b为 int类型
auto c = 1.9;//自动推断类型，c为double类型
auto d = 1.2e12L;//自动推断类型，d 是 long double
```

### 推导规则

```c++
int i = 10;
auto a = i, &b = i, *c = &i; // a 是 int，b 是 i 的引用，c 是 i 的指针，auto 就相当于 int
auto d = 0, f = 1.0; // error，0 和1.0 类型不同，对于编译器有二义性，没法推导
auto e; // error，使用 auto 必须马上初始化，否则无法推导类型

void func(auto value) {} // error，auto 不能用作函数参数

class A {
    auto a = 1; // error，在类中 auto 不能用作非静态成员变量
    static auto b = 1; // error，这里与 auto 无关，正常 static int b = 1 也不可以
    static const auto int c = 1; // ok
};

void func2() {
    int a[10] = {0};
    auto b = a; // ok
    auto c[10] = a; // error，auto 不能定义数组，可以定义指针
    vector<int> d;
    vector<auto> f = d; // error，auto 无法推导出模板参数
}
```

```c++
int i = 0;
auto *a = &i; // a是int*
auto &b = i; // b是int&
auto c = b; // c是int，忽略了引用

const auto d = i; // d是const int
auto e = d; // e是int

const auto& f = e; // f是const int&
auto &g = f; // g是const int&
```

这里的 cv 是指 const 和 volatile：

- 在不声明为引用或指针时，auto 会忽略等号右边的引用类型和 cv 限定
- 在声明为引用或者指针时，auto 会保留等号右边的引用和 cv 属性

### 何时用

这里没有绝对答案，在不影响代码代码可读性的前提下尽可能使用 auto 是蛮好的，复杂类型就使用 auto，int、double 这种就没有必要使用 auto 了，看下面这段代码：

```c++
auto func = [&] {
    cout << "xxx";
}; // 不关心 lambda 表达式究竟是什么类型

auto asyncfunc = std::async(std::launch::async, func);
// 记不住它返回的究竟是什么，也不关心返回值
```

## decltype

decltype 类型说明符，相对于 auto 用于推导变量类型，而 decltype 则用于推导表达式类型，它的作用是选择并返回操作数的数据类型，在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。

### 基本用法

```c++
int func() { return 0; }
decltype(func()) i; // i为int类型

int x = 0;
decltype(x) y; // y是int类型
decltype(x + y) z; // z是int类型
```

```c++
cont int &i = 1;
int a = 2;
decltype(i) b = 2; // b是const int&
```

注意：decltype 不会像 auto 一样忽略引用和 cv 属性，decltype 会保留表达式的引用和 cv 属性。

```C++
int getSize();

int main(void)
{
    int tempA = 2;
    
    /*1.dclTempA为int*/
    decltype(tempA) dclTempA;
    /*2.dclTempB为int，对于getSize根本没有定义，但是程序依旧正常，因为decltype只做分析，并不调用getSize，*/
    decltype(getSize()) dclTempB;

    return 0;
}
```

### 与 const 结合

```C++
double tempA = 3.0;
    const double ctempA = 5.0;
    const double ctempB = 6.0；
    const double *const cptrTempA = &ctempA;
    
    /*1.dclTempA推断为const double（保留顶层const，此处与auto不同）*/
    decltype(ctempA) dclTempA = 4.1;
    /*2.dclTempA为const double，不能对其赋值，编译不过*/
    dclTempA = 5;
    /*3.dclTempB推断为const double * const*/
    decltype(cptrTempA) dclTempB = &ctempA;
    /*4.输出为4（32位计算机）和5*/
    cout<<sizeof(dclTempB)<<"    "<<*dclTempB<<endl;
    /*5.保留顶层const，不能修改指针指向的对象，编译不过*/
    dclTempB = &ctempB;
    /*6.保留底层const，不能修改指针指向的对象的值，编译不过*/
    *dclTempB = 7.0;
```

### 与引用结合

```C++
int tempA = 0, &refTempA = tempA;

    /*1.dclTempA为引用，绑定到tempA*/
    decltype(refTempA) dclTempA = tempA;
    /*2.dclTempB为引用，必须绑定到变量，编译不过*/
    decltype(refTempA) dclTempB = 0;
    /*3.dclTempC为引用，必须初始化，编译不过*/
    decltype(refTempA) dclTempC;
    /*4.双层括号表示引用，dclTempD为引用，绑定到tempA*/
    decltype((tempA)) dclTempD = tempA;
    
    const int ctempA = 1, &crefTempA = ctempA;
    
    /*5.dclTempE为常量引用，可以绑定到普通变量tempA*/
    decltype(crefTempA) dclTempE = tempA;
    /*6.dclTempF为常量引用，可以绑定到常量ctempA*/
    decltype(crefTempA) dclTempF = ctempA;
    /*7.dclTempG为常量引用，绑定到一个临时变量*/
    decltype(crefTempA) dclTempG = 0;
    /*8.dclTempH为常量引用，必须初始化，编译不过*/
    decltype(crefTempA) dclTempH;
    /*9.双层括号表示引用,dclTempI为常量引用，可以绑定到普通变量tempA*/
    decltype((ctempA))  dclTempI = ctempA;
```

### 与指针结合

```C++
int tempA = 2;
int *ptrTempA = &tempA;
/*1.常规使用dclTempA为一个int *的指针*/
decltype(ptrTempA) dclTempA;
/*2.需要特别注意，表达式内容为解引用操作，dclTempB为一个引用，引用必须初始化，故编译不过*/
decltype(*ptrTempA) dclTempB;
```

## 与 auto 结合

auto 和 decltype 一般配合使用在推导函数返回值的类型问题上。

下面这段代码

```c++
template<typename T, typename U>
return_value add(T t, U u) { // t和v类型不确定，无法推导出return_value类型
    return t + u;
}
```

上面代码由于 t 和 u 类型不确定，那如何推导出返回值类型呢，可能会想到这种

```c++
template<typename T, typename U>
decltype(t + u) add(T t, U u) { // t和u尚未定义
    return t + u;
}
```

这段代码在 C++11 上是编译不过的，因为在 decltype(t +u) 推导时，t 和 u 尚未定义，就会编译出错，所以有了下面的叫做返回类型后置的配合使用方法：

```c++
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}
```

返回值后置类型语法就是为了解决函数返回值类型依赖于参数但却难以确定返回值类型的问题。

### decltype 和 auto 差异

decltype 和 auto 都可以用来推断类型，但是二者有几处明显的差异：

1. auto 忽略顶层 const，decltype 保留顶层 const ；
2. 对引用操作，auto 推断出原有类型，decltype 推断出引用；
3. 对解引用操作，auto 推断出原有类型，decltype 推断出引用；
4. auto 推断时会实际执行，decltype 不会执行，只做分析。

### 推导规则

对于decltype(exp)有

- exp 是表达式，decltype(exp) 和 exp 类型相同
- exp 是函数调用，decltype(exp) 和函数返回值类型相同
- 其它情况，若 exp 是左值，decltype(exp) 是 exp 类型的左值引用

```c++
int a = 0, b = 0;
decltype(a + b) c = 0; // c是int，因为(a+b)返回一个右值
decltype(a += b) d = c;// d是int&，因为(a+=b)返回一个左值

d = 20;
cout << "c " << c << endl; // 输出c 20
```

## class

C++11 中对类 (class) 新增的特性：

* default/delete 控制默认函数
* override /final 强制重写 / 禁止重写虚函数
* 委托构造函数 Delegating constructors
* 继承的构造函数 Inheriting constructors
* 类内部成员的初始化 Non-static data member initializers
* 移动构造和移动赋值

### class & struct

在 C++ 中我们可以看到 struct 和 class 的区别并不是很大，两者之间有很大的相似性。那么为什么还要保留 struct, 这是因为 C++ 是向下兼容的，因此 C++ 中保留了很多 C 的东西。

```c++
#include <iostream>

using std::cout;
using std::endl;

struct Base1 {
  virtual void func() {
    cout << "base1" << endl;
  }
};

class Base2 {
  virtual void func() {
    cout << "base2" << endl;
  }
};
```

### strcut 和 class 的区别

1. 默认的继承访问权。class 默认的是 private, strcut 默认的是 public。
2. 默认访问权限：struct 作为数据结构的实现体，它默认的数据访问控制是 public 的，而 class 作为对象的实现体，它默认的成员变量访问控制是 private 的。
3. “class”这个关键字还用于定义模板参数，就像“typename”。但关建字“struct”不用于定义模板参数
4. class和struct在使用大括号{ }初始化上的区别
  1. class 和 struct 如果定义了构造函数的话，都不能用大括号进行初始化
  2. 如果没有定义构造函数，struct 可以用大括号初始化。
  3. 如果没有定义构造函数，且所有成员变量全是 public 的话，class 可以用大括号初始化

### final & override

C++11 关于继承新增了两个关键字，final 用于修饰一个类，表示禁止该类进一步派生和虚函数的进一步重载，override 用于修饰派生类中的成员函数，标明该函数重写了基类函数，如果一个函数声明了 override 但父类却没有这个虚函数，编译报错，使用 override 关键字可以避免开发者在重写基类函数时无意产生的错误。

示例代码1：

```c++
struct Base {
    virtual void func() {
        cout << "base" << endl;
    }
};

struct Derived : public Base{
    void func() override { // 确保func被重写
        cout << "derived" << endl;
    }

    void fu() override { // error，基类没有fu()，不可以被重写
    }
};
```

示例代码2：

```c++
struct Base final {
    virtual void func() {
        cout << "base" << endl;
    }
};

struct Derived : public Base{ // 编译失败，final修饰的类不可以被继承
    void func() override {
        cout << "derived" << endl;
    }
};
```

## enum class

C++11 新增有作用域的枚举类型。

### 不带作用域的枚举代码

```c++
enum AColor {
    kRed,
    kGreen,
    kBlue
};

enum BColor {
    kWhite,
    kBlack,
    kYellow
};

int main() {
    if (kRed == kWhite) {
        cout << "red == white" << endl;
    }
    return 0;
}
```

如上代码，**不带作用域的枚举类型可以自动转换成整形**，且**不同的枚举可以相互比较**，代码中的红色居然可以和白色比较，这都是潜在的难以调试的 bug，而这种完全可以通过有作用域的枚举来规避。

### 有作用域的枚举代码

```c++
enum class AColor {
    kRed,
    kGreen,
    kBlue
};

enum class BColor {
    kWhite,
    kBlack,
    kYellow
};

int main() {
    if (AColor::kRed == BColor::kWhite) { // 编译失败
        cout << "red == white" << endl;
    }
    return 0;
}
```

使用带有作用域的枚举类型后，对不同的枚举进行比较会导致编译失败，消除潜在 bug，同时带作用域的枚举类型可以选择底层类型，默认是 int，可以改成 char 等别的类型。

### 底层枚举类型

```c++
enum class AColor : char {
    kRed,
    kGreen,
    kBlue
};
```

## explicit

explicit 专用于修饰构造函数，表示只能显式构造，不可以被隐式转换。

### 不用 explicit

```c++
#include <iostream>

using std::cout;
using std::endl;

struct A {
  A(int value) {// 没有explicit关键字
    cout << "value" << endl;
  }
};

int main() {
  A a = 1;// 可以隐式转换
  return 0;
}
```

### 使用 explicit

```c++
#include <iostream>

using std::cout;
using std::endl;

struct A {
  explicit A(int value) {
    cout << "value" << endl;
  }
};

int main() {
  A a = 1;// error，不可以隐式转换
  A aa(2);// ok
  return 0;
}
```

## default

在 C+11 中，对于 defaulted 函数，编译器会为其自动生成默认的函数定义体，从而获得更高的代码执行效率，也可免除程序员手动定义该函数的工作量。

C++ 的类有**四类特殊成员函数**，它们分别是：**默认构造函数**、**析构函数**、**拷贝构造函数**以及**拷贝赋值运算符**。

这些类的特殊成员函数**负责创建、初始化、销毁，或者拷贝类的对象**。如果程序员没有显式地为一个类定义某个特殊成员函数，而又需要用到该特殊成员函数时，则编译器会隐式的为这个类生成一个默认的特殊成员函数。当存在用户自定义的特殊成员函数时，编译器将不会隐式的自动生成默认特殊成员函数，而需要程序员手动编写，加大了程序员的工作量。并且手动编写的特殊成员函数的代码执行效率比编译器自动生成的特殊成员函数低。

C++11 标准引入了一个新特性：defaulted 函数。程序员只需在函数声明后加上”= default ;”，就可将该函数声明为 defaulted 函数，编译器将为显式声明的 defaulted 函数**自动生成函数体**。

defaulted 函数特性仅适用于类的特殊成员函数，且**该特殊成员函数没有默认参数**。

defaulted 函数既可以在类体里(inline)定义，也可以在类体外(out-of-line)定义。

```c++
struct A {
  int a;
  A(int i) { a = i; }
};

int main() {
  A a;// 编译出错
  A a(2);// 编译成功
  return 0;
}
```

上面代码编译出错，因为没有匹配的构造函数，因为编译器没有生成默认构造函数，而通过 default，程序员只需在函数声明后加上“=default;”，就可将该函数声明为 defaulted 函数，编译器将为显式声明的 defaulted 函数自动生成函数体，如下：

```c++
struct A {
  A() = default;
  int a;
  A(int i) { a = i; }
};

int main() {
  A a;
  return 0;
}
```

### 情景分析

```C++
class Foo {
  Foo(int x);     // 自定义构造函数
  Foo() = default;// 编译器自动生成默认构造函数
};

struct A {
  int x;
  A(int x = 1) : x(x) {}//用户定义的默认构造函数
};

struct B : A {
  // B::B() 是隐式定义的，调用 A::A()
};

struct C {
  A a;
  // C::C() 是隐式定义的，调用 A::A()
};

struct D : A {
  D(int y) : A(y) {}
  // D::D() 未声明，因为存在另一个构造函数
};

struct E : A {
  E(int y) : A(y) {}
  E() = default;// 显式默认，调用A::A()
};

struct F {
  int &ref;   //引用成员
  const int c;// 常量成员
              // F::F() 被隐式定义为已删除
};

int test_default1() {
  A a;
  B b;
  C c;
  // D d; // 编译错误
  E e;
  // F f; // 编译错误

  return 0;
}
```

### 内联

```cpp
struct widget {
  widget() = default;

  inline widget &operator=(const widget &);
};

// 只要是可内联的，就可以在类的主体之外默认一个特殊的成员函数。
inline widget &widget::operator=(const widget &) = default;
```

## delete

C++ 中，如果开发人员没有定义特殊成员函数，那么编译器在需要特殊成员函数时候会隐式自动生成一个默认的特殊成员函数，例如拷贝构造函数或者拷贝赋值操作符，如下代码：

```c++
struct A {
    A() = default;
    int a;
    A(int i) { a = i; }
};

int main() {
    A a1;
    A a2 = a1;  // 正确，调用编译器隐式生成的默认拷贝构造函数
    A a3;
    a3 = a1;  // 正确，调用编译器隐式生成的默认拷贝赋值操作符
}
```

有时候想禁止对象的拷贝与赋值，可以使用 delete 修饰，如下：

```c++
struct A {
    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    int a;
    A(int i) { a = i; }
};

int main() {
    A a1;
    A a2 = a1;  // 错误，拷贝构造函数被禁用
    A a3;
    a3 = a1;  // 错误，拷贝赋值操作符被禁用
}
```

delele 函数在 C++11 中很常用，std::unique_ptr 就是通过 delete 修饰来禁止对象的拷贝的。

delete 关键字可用于任何函数，不仅仅局限于类成员函数

## export

C++11 中，不使用但保留该关键词。

## extern

C++ 中，如果多个源文件都使用了同一个模板，会对该模板进行多次实例化，但最后编译时，编译器会仅保留一份模板实例化产生的代码。在一些比较大的项目中，冗余的模板实例化会明显拖慢编译速度，可以使用“外部模板”技术告诉编译器不需要对模板进行实例化，在某一个源文件中仅进行一次显式实例化。

```c++
template void fun<int>(int); // 显示地实例化
```

```c++
extern template void fun<int>(int); // 外部模板的声明
```

## inline

C++11中引入了内联命名空间（inline namespace），它的特点就是不需要使用 using 语句就可以直接在外层命名空间使用该命名空间内部的内容，而且无需使用命名空间前缀。

```C++
namespace inline_test {
inline namespace inline_namespace1 {
class Inline1 {
public:
  int iv;
};
}// namespace inline_namespace1
namespace inline_namespace1 {
class Inline2 {
public:
  double dv;
};
}// namespace inline_namespace1
void test_inline_namespace() {
  Inline1 in1;
  in1.iv = 5;
  Inline2 in2;
  in2.dv = 2;
}
}// namespace inline_test
```

内联命名空间的声明方法就是在原来的声明语法前面增加 inline 关键字。除此之外上面代码还有以下特点：

两处声明的命名空间同名，它们同属一个命名空间。这是 C++ 命名空间从来就有的特性。

第一次声明命名空间时使用了 inline 关键字，这叫显式内联；第二次没有使用 inline 关键字，但是由于第一次已经声明了 inline，这里声明的还是内联命名空间。这种情况成为隐式内联。

内联命名空间声明之后，就可以在外层命名空间不适用前缀而直接使用它们了。

```C++
namespace inline_test {
inline namespace inline_namespace1 {
class Inline1 {
public:
  int iv;
};
}// namespace inline_namespace1
namespace inline_namespace1 {
class Inline2 {
public:
  double dv;
};
}// namespace inline_namespace1
void test_inline_namespace() {
  Inline1 in1;
  in1.iv = 5;
  Inline2 in2;
  in2.dv = 2;
}
}// namespace inline_test
void test_inline_namespace2() {
  inline_test::Inline1 in1;
  in1.iv = 5;
  inline_test::Inline2 in2;
  in2.dv = 2;
}
```

上述代码中 test_inline_namespace 处在 linline_namespace1 的外层，所以可以直接使用 Inline1 和 Inline2。test_inline_namespace2 处在更外层，这时也只是需要使用外层命名空间 inline_test 前缀即可。

看起来 inline_namespace 就像不存在一样。

## mutable

C++11 中的 mutable 是用来修改 const 函数中的不可修改类成员的缺陷

```C++
#include <string>

class Log {

public:
  void print(const std::string &str) const {
    printf("%s", str.c_str());
    printNums++;//统计输出次数
  }

private:
  mutable int printNums;//这里必须声明为 mutable
}
```

## sizeof

C++11 中 sizeof 可以用的类的数据成员上，看代码：

### C++11 前

```c++
struct A {
    int data[10];
    int a;
};

int main() {
    A a;
    cout << "size " << sizeof(a.data) << endl;
    return 0;
}
```

### C++11 后

```c++
struct A {
    int data[10];
    int a;
};

int main() {
    cout << "size " << sizeof(A::data) << endl;
    return 0;
}
```

想知道类中数据成员的大小在 C++11 中是不是方便了许多，而不需要定义一个对象，在计算对象的成员大小。

在标准 C++，sizeof 可以作用在对象以及类别上。但是不能够做以下的事：

```C++
struct someType { otherType member; } ;
sizeof(SomeType::member); //直接由 someType 型别取得非静态成员的大小，C++03 不行
```

这会传回 OtherType 的大小。C++03 并不允许这样做，所以会引发编译错误。C++11 将会允许这种使用。

```C++
#include <iostream>

using namespace std;

struct Empty {};

struct Base {
  int a;
};

struct Derived : Base {
  int b;
};

struct Bit {
  unsigned bit : 1;
};

int main() {
  Empty e;
  Derived d;
  Base &b = d;
  Bit bit;
  cout << sizeof(e) << endl;
  cout << sizeof(Empty) << endl;
  cout << sizeof(&e) << endl;
  cout << sizeof(Derived) << endl;
  cout << sizeof(d) << endl;
  //  cout << sizeof(void) << endl;//错误
  return 0;
}
```

## struct

C++11 struct 可以给每个成员变量赋予默认的初始值。

```C++
struct Student{
    char* name = nullptr;
    unsigned int age  = 15;
    int number = 21509111;  
};
```

所有声明的新结构体对象就是默认上面的值。

## using

### 去除作用域的限制

using 在 C++11 之前主要用于名字空间、类型、函数与对象的引入，实际上是去除作用域的限制。

```C++
//引入名字空间
using namespace std;
//引入类型
using std::iostream;
//引入函数
using std::to_string;
//引入对象
using std::cout;
```

### 解除函数隐藏

“隐藏”是指派生类的函数屏蔽了与其同名的基类函数，规则如下：

- 如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无 virtual 关键字，基类的函数将被隐藏（注意别与重载混淆）
- 如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有 virtual 关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）

使用了 using 关键字，就可以避免 1 的情况，是的父类同名函数在子类中**得以重载**，不被隐藏

```C++
class Base {
public:
  void func() { cout << "in Base::func()" << endl; }
  void func(int n) { cout << "in Base::func(int)" << endl; }
};

class Sub : public Base {
public:
  using Base::func;//引入父类所有同名函数func，解除函数隐藏
  void func() { cout << "in Sub::func()" << endl; }
};

int main() {
  Sub s;
  s.func();
  s.func(1);// Success!
}
```

### 代替 typedef，给类型命名

```C++
using uint8 = unsigned char;                 //等价于typedef unsigned char uint8;
using FunctionPtr = void (*)();              //等价于typedef void (FunctionPtr)();
template using MapString = std::map<T, char>;//定义模板别名，注意typedef无法定义模板别名，因为typedef只能作用于具体类型而非模板
```

## thread_local

thread_local 是 C++11 增加的存储类指定符。

C++ 中有 4 种存储周期：

* automatic
* static
* dynamic
* thread

有且只有 thread_local 关键字修饰的变量具有线程周期 (thread duration)，这些变量 ( 或者说对象）在线程开始的时候被生成 (allocated)，在线程结束的时候被销毁 (deallocated)。并且每 一个线程都拥有一个独立的变量实例 (Each thread has its own instance of the object)。

每一个线程都拥有并只拥有一个该变量的独立实例，一般用于需要保证线程安全的函数中。

thread_local 可以和 static 与 extern 关键字联合使用，这将影响变量的链接属性 (to adjust linkage)。

那么，哪些变量可以被声明为thread_local？可以是以下3类：

* 命名空间下的全局变量
* 类的 static 成员变量
* 本地变量

```c++
#include <iostream>
#include <thread>

class A {
    public:
    A() {}
    ~A() {}

    void test(const std::string &name) {
        thread_local int count = 0;
        ++count;
        std::cout << name << ": " << count << std::endl;
    }
};

void func(const std::string &name) {
    A a1;
    a1.test(name);
    a1.test(name);
    A a2;
    a2.test(name);
    a2.test(name);
}

int main() {
    std::thread(func, "thread1").join();
    std::thread(func, "thread2").join();
    return 0;
}
```

输出：

```c++
thread1: 1
thread1: 2
thread1: 3
thread1: 4
thread2: 1
thread2: 2
thread2: 3
thread2: 4
```

验证上述说法，对于一个线程私有变量，一个线程拥有且只拥有一个该实例，类似于 static。

### 案例

```C++
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
 
thread_local unsigned int rage = 1;
std::mutex cout_mutex;
 
void increase_rage(const std::string& thread_name) {
  ++rage; // 在锁外修改 OK ；这是线程局域变量
  std::lock_guard<std::mutex> lock(cout_mutex);
  std::cout << "Rage counter for " << thread_name << ": " << rage << '\n';
}
 
void test() {
  thread_local int i = 0;
  printf("id=%d, n=%d\n", std::this_thread::get_id(), i);
  i++;
}
 
void test2() {
  test();
  test();
}
 
int main() {
  std::thread a(increase_rage, "a"), b(increase_rage, "b");
 
  {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Rage counter for main: " << rage << '\n';
  }
 
  a.join();
  b.join();
 
  std::thread t1(test);
  std::thread t2(test);
  t1.join();
  t2.join();
 
  std::thread t3(test2);
  t3.join();
 
  system("pause");
  return 0;
}
```

## static_assert

C++11 引入 static_assert 来补充编译时断言。

之前 Boost 库也实现了类似的功能，它是利用编译器在编译时会检查除以 0 这个特性，如果条件为假就构建一个除以 0 的语句迫使编译器报错来实现的，虽然可以达成编译时检查的目的，但报错信息比较不明确。

使用 C++11 的 static_assert，在断言失败时，可以得到明确的错误提示。

```c++
static_assert(true/false, message);
```

C++11 引入 static_assert 声明，用于在编译期间检查，如果第一个参数值为 false，则打印 message，编译失败。

```C++
#include <memory>
#include <type_traits>

struct MyClass {
  char m_value;
};

struct MyEmptyClass {
  void func();
};

void MyEmptyClass::func() {}

// 确保MyEmptyClass是一个空类（没有任何非静态成员变量，也没有虚函数）
static_assert(std::is_empty<MyEmptyClass>::value, "empty class needed");

//确保MyClass是一个非空类
static_assert(!std::is_empty<MyClass>::value, "non-empty class needed");

template<typename T, typename U, typename V>
class MyTemplate {
  // 确保模板参数T是一个非空类
  static_assert(
      !std::is_empty<T>::value,
      "T should be n non-empty class");

  // 确保模板参数U是一个空类
  static_assert(
      std::is_empty<U>::value,
      "U should be an empty class");

  // 确保模板参数V是从std::allocator<T>直接或间接派生而来，
  // 或者V就是std::allocator<T>
  static_assert(
      std::is_base_of<std::allocator<T>, V>::value,
      "V should inherit from std::allocator<T>");
};

// 仅当模板实例化时，MyTemplate里面的那三个static_assert才会真正被演算，
// 藉此检查模板参数是否符合期望
template class MyTemplate<MyClass, MyEmptyClass, std::allocator<MyClass>>;

int main(int argc, char *argv[]) {
  return 0;
}
```

## nullptr

nullptr 是 C++11 用来表示空指针新引入的常量值，在 C++11 中如果表示空指针语义时建议使用 nullptr 而不要使用 NULL，因为 NULL 本质上是个 int 型的 0，其实不是个指针。举例：

```c++
void func(void *ptr) {
    cout << "func ptr" << endl;
}

void func(int i) {
    cout << "func i" << endl;
}

int main() {
    func(NULL); // 编译失败，会产生二义性
    func(nullptr); // 输出func ptr
    return 0;
}
```

nullptr 关键字用于标识空指针，是 `std::nullptr_t` 类型的(constexpr)变量.它可以转换成任何指针类型和 bool 布尔类型（主要是为了兼容普通指针可以作为条件判断语句的写法），但是不能被转换为整数。

```C++
char *p1 = nullptr;     // 正确
int  *p2 = nullptr;     // 正确
bool b = nullptr;       // 正确. if(b)判断为false
int a = nullptr;        // error
```

## noexcept

noexcept 有两类作用：noexcept 指定符和 noexcept 运算符

### noexcept 指定符

```C++
void f() noexcept;  // 函数 f() 不抛出
void (*fp)() noexcept(false); // fp 指向可能抛出的函数
void g(void pfa() noexcept);  // g 接收指向不抛出的函数的指针
// typedef int (*pf)() noexcept; // 错误
```

### noexcept 运算符

```C++
#include <iostream>
#include <utility>
#include <vector>
 
// noexcept 运算符 
void may_throw() {};
void no_throw() noexcept {};
auto lmay_throw = [] {};
auto lno_throw = []() noexcept {};
 
class T {
};
class T1 {
public:
  ~T1() {}
};
class T2 {
public:
  ~T2() {}
  int v;
};
class T3 {
public:
  ~T3() {}
  std::vector<int> v;
};
class T4 {
public:
  std::vector<int> v;
};
 
int main()
{
  T t;
  T1 t1;
  T2 t2;
  T3 t3;
  T4 t4;
 
  std::vector<int> vc;
 
  std::cout << std::boolalpha
    << "Is may_throw() noexcept? " << noexcept(may_throw()) << '\n'
    << "Is no_throw() noexcept? " << noexcept(no_throw()) << '\n'
    << "Is lmay_throw() noexcept? " << noexcept(lmay_throw()) << '\n'
    << "Is lno_throw() noexcept? " << noexcept(lno_throw()) << '\n'
    << "Is ~T1() noexcept? " << noexcept(std::declval<T1>().~T1()) << '\n'
    << '\n'
    << '\n'
 
    << "Is T(rvalue T) noexcept? " << noexcept(T(std::declval<T>())) << '\n'
    << "Is T(lvalue T) noexcept? " << noexcept(T(t)) << '\n'
    << '\n'
 
    << "Is T1(rvalue T1) noexcept? " << noexcept(T1(std::declval<T1>())) << '\n'
    << "Is T1(lvalue T1) noexcept? " << noexcept(T1(t1)) << '\n'
    << '\n'
 
    << "Is T2(rvalue T2) noexcept? " << noexcept(T2(std::declval<T2>())) << '\n'
    << "Is T2(lvalue T2) noexcept? " << noexcept(T2(t2)) << '\n'
    << '\n'
 
    << "Is T3(rvalue T3) noexcept? " << noexcept(T3(std::declval<T3>())) << '\n'
    << "Is T3(lvalue T3) noexcept? " << noexcept(T3(t3)) << '\n'
    << '\n'
 
    << "Is T4(rvalue T4) noexcept? " << noexcept(T4(std::declval<T4>())) << '\n'
    << "Is T4(lvalue T4) noexcept? " << noexcept(T4(t4)) << '\n'
    << '\n'
 
    << "Is std::vector<int>(rvalue std::vector<int>) noexcept? " << noexcept(std::vector<int>(std::declval<std::vector<int>>())) << '\n'
    << "Is std::vector<int>(lvalue std::vector<int>) noexcept? " << noexcept(std::vector<int>(vc)) << '\n';
 
  system("pause");
  return 0;
}
```

## const

因为要讲后面的 constexpr，所以这里简单介绍下 const。

const 字面意思为只读，可用于定义变量，表示变量是只读的，不可以更改，如果更改，编译期间就会报错。

主要用法如下：

### 用于定义常量

```c++
const int value = 5;
```

### 指针常量

这里有个小技巧，从右向左读，即可知道 const 究竟修饰的是指针还是指针所指向的内容。

```c++
char *const ptr; // 指针本身是常量
const char* ptr; // 指针指向的变量为常量
```

### 传参避免拷贝

一般会传递类对象时会传递一个 const 的引用或者指针，这样可以避免对象的拷贝，也可以防止对象被修改。

```c++
class A{};
void func(const A& a);
```

### 修饰类成员变量

表示是成员常量，不能被修改，可以在初始化列表中被赋值。

```c++
class A {
    const int value = 5;
};
class B {
    const int value;
    B(int v) : value(v){}
};
```

### 修饰类成员函数

表示在该函数内不可以修改该类的成员变量。

```c++
class A{
    void func() const;
};
```

### 修饰类对象

类对象只能调用该对象的 const 成员函数。

```c++
class A {
    void func() const;
};

const A a;

a.func();
```



## char16_t 和 char32_t

### 产生原因

随着编程人员日益的熟悉 Unicode，类型 wchar_t 显然已经满足不了需求，在计算机系统上进行的编码字符和字符串编码时，仅仅使用 Unicode 码点显然是不够的。

因此 C++11 新增了类型 char16_t，char32_t。

- char16_t: 无符号类型，长 16 位
- char32_t: 无符号类型，长 32 位

C++11 使用前缀 u 表示 char16_t 字符常量和字符串常量如：u'L'; u"lilili";
C++11 使用前缀 U 表示 char32_t 字符常量和字符串常量如：U'L' ; U"lilili" ;

类型 char16_t 与 /u00F6 形式的通用字符名匹配，

类型 char32_t 与 /U0000222B 形式的通用字符名匹配。

前缀 u 和 U 分别指出字符字面值的类型为 char16_t 和 char32_t。

如果在 VS 中使用 char16_t 或者 char32_t 的话，不要加前缀 u 或者 U 只能加前缀 L.

## alignof 和 alignas

C++11 新引入内存对齐操作符 alignof，对齐描述符 alignas，基本对齐值 alignof(std::max_align_t)

alignas 可以接受常量表达式和类型作为参数，可以修饰变量、类的数据成员等，不能修饰位域和用 register 申明的变量。一般往大对齐。

```C++
struct s3
{
    char s;
    double d;
    int i;
};
 
struct s11
{
    alignas(16) char s;
    int i;
};
 
struct s12
{
    alignas(16) char s;
    int i;
};

// alignof
cout << "-------------------alignof---------------------" << endl;

cout << "alignof(std::max_align_t)	" << alignof(std::max_align_t) << endl;

// 基本对齐值
cout << endl;
cout << "-------basic type" << endl;
cout << "alignof(char)		" << alignof(char) << endl;
cout << "alignof(int)		" << alignof(int) << endl;
cout << "alignof(double)	" << alignof(double) << endl;
 
cout << endl;
cout << "-------struct" << endl;
cout << "alignof(s1)		" << alignof(s1) << endl;
cout << "alignof(s2)		" << alignof(s2) << endl;
cout << "alignof(s3)		" << alignof(s3) << endl;
 
cout << endl;
 
// alignas
cout << "-------------------alignas---------------------" << endl;
cout << "alignof(s1)		" << alignof(s1) << endl;
cout << "alignof(s11)		" << alignof(s11) << endl;
cout << "alignof(s12)		" << alignof(s12) << endl;
 
cout << "sizeof(s1)    	" << sizeof(s1) << endl;
cout << "sizeof(s11)	" << sizeof(s11) << endl;
cout << "sizeof(s12)	" << sizeof(s12) << endl;
```

结果如下：

```
-------------------alignof---------------------
alignof(std::max_align_t)	8

-------basic type
alignof(char)	1
alignof(int)	4
alignof(double)	8

-------struct
alignof(s1)	4
alignof(s2)	8
alignof(s3)	8

-------------------alignas---------------------
alignof(s1)	4
alignof(s11)	16
alignof(s12)	16
sizeof(s1)	4
sizeof(s11)	16
sizeof(s12)	16
```

## chrono 时间库

### duration

`std::chrono::duration` 表示一段时间，常见的单位有 s、ms 等，示例代码：

```c++
// 拿休眠一段时间举例，这里表示休眠100ms
std::this_thread::sleep_for(std::chrono::milliseconds(100));
```

`sleep_for` 里面其实就是 `std::chrono::duration`，表示一段时间，实际是这样：

```c++
typedef duration<int64_t, milli> milliseconds;
typedef duration<int64_t> seconds;
```

`duration` 具体模板如下：

```c++
template <class Rep, class Period = ratio<1> > class duration;
```

Rep 表示一种数值类型，用来表示 Period 的数量，比如 int、float、double，Period 是 ratio 类型，用来表示【用秒表示的时间单位】比如 second，常用的 `duration<Rep, Period>`已经定义好了，在 `std::chrono::duration` 下：

- ratio<3600, 1>：hours
- ratio<60, 1>：minutes

- ratio<1, 1>：seconds
- ratio<1, 1000>：microseconds

- ratio<1, 1000000>：microseconds
- ratio<1, 1000000000>：nanosecons

ratio 的具体模板如下：

```c++
template <intmax_t N, intmax_t D = 1> class ratio;
```

N 代表分子，D 代表分母，所以 ratio 表示一个分数，可以自定义 Period，比如 `ratio<2, 1>` 表示单位时间是 2 秒。

### time_point

表示一个具体时间点，如2020年5月10日10点10分10秒，拿获取当前时间举例：

```c++
std::chrono::time_point<std::chrono::high_resolution_clock> Now() {
    return std::chrono::high_resolution_clock::now();
}
// std::chrono::high_resolution_clock为高精度时钟，下面会提到
```

### clocks 时钟

#### steady_clock 相对于系统开机启动的时间

稳定的时间间隔，表示相对时间，相对于系统开机启动的时间，无论系统时间如何被更改，后一次调用 now() 肯定比前一次调用 now() 的数值大，可用于计时。

#### system_clock 当前的系统时钟

表示当前的系统时钟，可以用于获取当前时间：

```c++
#include <chrono>
#include <iostream>

int main() {
  using std::chrono::system_clock;
  system_clock::time_point today = system_clock::now();

  std::time_t tt = system_clock::to_time_t(today);
  std::cout << "today is: " << ctime(&tt);

  return 0;
}
```

#### high_resolution_clock 系统可用的最高精度的时钟

high_resolution_clock 表示系统可用的最高精度的时钟，实际上就是 system_clock 或者 steady_clock 其中一种的定义，官方没有说明具体是哪个，不同系统可能不一样，看 gcc chrono 源码中 high_resolution_clock 是 steady_clock 的 typedef。
