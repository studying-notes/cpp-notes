---
date: 2020-10-26T08:28:51+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C++ 函数"  # 文章标题
# description: "文章描述"
url:  "posts/cpp/tutorial"  # 设置网页永久链接
tags: [ "cpp" ]  # 标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 排序优先级
chapter: false  # 设置为章节

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

## 函数原型

函数原型是函数的声明，作用是告诉编译器有关函数接口的信息：函数的名字、函数返回值的数据类型、函数的参数个数、参数类型和参数的顺序，编译器根据函数原型检查函数调用的正确性。

```c++
void count(int x, int y);
```

函数原型是一个声明语句，由函数首部加上分号组成。由于函数原型没有实现代码，因此不需要参数名。通常添加参数名是为了增加可读性，但编译器将忽略这些名称。

标准库函数的函数原型存放在指定的头文件中，用 include 预处理指令获取。

## 函数参数的传递

参数是调用函数与被调用函数之间交换数据的通道。函数定义首部的参数称为形式参数（简称形参），调用函数时使用的参数称为实际参数（实参）。

实际参数必须与形式参数在类型、个数、位置上相对应。函数被调用前，形参没有存储空间。函数被调用时，系统建立与实参对应的形参存储空间，函数通过形参与实参进行通信、完成操作。函数执行完毕，系统收回形参的临时存储空间。这个过程称为参数传递或参数的虚实结合。

C++ 语言有三种参数传递机制：值传递（值调用）、指针传递（地址调用）和引用传递（引用调用）。实际参数和形式参数按照不同传递机制进行通信。

## 传值参数

### 值传递机制

在值传递机制中，作为实际参数的表达式的值被复制到由对应的形式参名所标识的对象中，成为形参的初始值。完成参数值传递之后，函数体中的语句对形参的访问、修改都是在这个标识对象上操作的，与实际参数对象无关。

```c++
#include <iostream>

using namespace std;

void count(int x, int y) {
    x *= 2;
    y *= y;
    cout << "x=" << x << '\t';
    cout << "y=" << y << endl;
}

int main() {
    int x = 3, y = 4;
    count(x, y);
    cout << "x=" << x << '\t';
    cout << "y=" << y << endl;
}
```

如果函数具有返回值，则在函数执行 return 语句时，系统将创建一个匿名对象临时存放函数的返回结果。这个匿名对象在返回调用之后撤销。

```c++
#include <iostream>

using namespace std;

double volume(double radius, double height) {
    // 创建一个匿名对象临时存放函数的返回结果
    return 3.14 * radius * radius * height;
}

int main() {
    double vol, r, h;
    cout << "Input radius and height: \n";
    cin >> r >> h;
    vol = volume(r, h);
    cout << "Volume = " << vol << endl;
}
```

因为在传值方式中，实际参数对形式参数进行赋值操作，所以实际参数可以是各种能够对形式参数标识对象赋值的表达式。如果实参值的类型和形参对象类型不相同，将按形参的类型进行强制类型转换，然后赋给形参。

```c++
#include <iostream>

using namespace std;

double max(double x, double y, double z) {
    y = x > y ? x : y;
    return y > z ? y : z;
}

int main() {
    double x, y, z, s;
    cout << "Input x, y, z: \n";
    cin >> x >> y >> z;
    s = max(x, y, z) / (max(x + y, y, z) * max(x, y, y + z));
    cout << "s = " << s << endl;
}
```

### 实际参数求值的副作用

C++ 没有规定在函数调用时实际参数的求值顺序。实际参数求值顺序的不同规定，对一般参数没有什么影响，但若实际参数表达式之间有求值关联，则同一个程序在不同编译器可能产生不同的运行结果。

```c++
#include <iostream>

using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 4, y = 6;
    cout << add(++x, x + y) << endl;
}
```

### 默认参数

函数传值调用时，实际参数作为右值表达式向形式参数提供初始值。C++ 允许指定参数的默认值，当函数调用中省略默认参数时，默认值自动传递给被调用函数。

调用带参数默认值的函数时，如果显式指定实际参数值，则不使用函数参数的默认值。

```c++
#include <iostream>
#include <cmath>

using namespace std;

// 在函数原型中指定默认参数值
double dist(double, double, double = 0, double = 0);

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    double x1, y1, x2, y2;
    cout << "Enter point (x1, y1):";
    cin >> x1 >> y1;
    cout << "Enter point (x2, y2):";
    cin >> x2 >> y2;

    cout << dist(x1, y1, x2, y2) << endl;
    cout << dist(x1, y1) << endl;
    cout << dist(x1, y1, x2) << endl;
}
```

### 默认参数规定

- C++ 规定，函数的形式参数说明中设置一个或多个实际参数的默认值，默认参数必须是函数参数表中最右边（尾部）的参数。调用具有多个默认参数的函数时，如果省略的参数不是参数表中最右边的参数，则该参数右边的所有参数也应该省略。
- 默认参数应该在函数名第一次出现时指定，通常在函数原型中。若已在函数原型中指定默认参数，则函数定义时不能重复给出。
- 默认值可以是常量、全局变量或函数调用，但不能是局部量。
- 默认参数可以用于内联函数。

## 指针参数

函数定义中的形式参数被说明为指针类型时，称为指针参数。形参指针对应的实际参数是地址表达式。调用函数时，实际参数把对象的地址值赋给形式参数名标识的指针变量，被调用函数可以在函数体内通过形参指针来间接访问实参地址所指的对象。这种参数传递方式称为指针传递或地址调用。

```c++

```


```c++

```

```c++

```


```c++

```




