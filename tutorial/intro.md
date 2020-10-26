---
date: 2020-10-09T12:48:02+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C++ 概述"  # 文章标题
description: "介绍了最简单的 C++ 程序"
url:  "posts/cpp/tutorial/intro"  # 设置网页链接，默认使用文件名
tags: [ "cpp", "intro" ]  # 自定义标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 文章在章节中的排序优先级，正序排序
chapter: false  # 将页面设置为章节

index: true  # 文章是否可以被索引
draft: true  # 草稿
toc: true  # 是否自动生成目录
---

> 输入圆的半径，求圆的周长和面积。

## 结构化方法编程

```c++
#include <iostream>

using namespace std;

int main() {
    double r, girth, area;
    const double PI = 3.14159;

    cout << "Please input radius:\n";
    cin >> r;

    girth = 2 * PI * r;
    area = PI * r * r;

    cout << "radius=" << r << endl;
    cout << "girth=" << girth << endl;
    cout << "area=" << area << endl;
    return 0;
}

// Please input radius:
// 3
// radius=3
// girth=18.8495
// area=28.2743
```

第 1 行称为预编译指令，说明该程序要使用的外部文件。C ++语言标准头文件 iostream 包含了程序常用的输入 cin 和输出 cout 的定义。

第 2 行是使用名空间的声明。using 和 namespace 都是关键字，std 是系统提供的标准命名空间。

C++ 语言以函数为程序运行的基本单位。

## 面向对象方法编程

当我们用对象思维考虑问题时，可以对问题进一步抽象。所有称为“圆”的这种类型的几何图形，最基本的要素是半径。它决定了圆的大小，也是区分具体圆 A、圆 B、圆 C 等的基本数据。一旦定义了具体的有半径值的圆，就有它特定的周长和面积了。

“圆”是一种类型。在面向对象方法中，称为“类类型”或“类”。“圆”类型的基本数据是“半径”。类的数据称为“属性”或“数据成员”。

数据成员有了具体的值之后，就可以计算周长和面积了。这种“计算”由程序代码实现，并且“封装”在类中，称为类的“方法”或“成员函数”。

```c++
#include <iostream>

using namespace std;

class Circle {
    double radius;
public:
    void Set_Radius(double r) {
        radius = r;
    }

    double Get_Radius() const {
        return radius;
    }

    double Get_Girth() const {
        return 2 * 3.14 * radius;
    }

    double Get_Area() const {
        return 3.14 * radius * radius;
    }
};

int main() {
    Circle A{}, B{};

    A.Set_Radius(3);
    cout << "A.Radius=" << A.Get_Radius() << endl;
    cout << "A.Girth=" << A.Get_Girth() << endl;
    cout << "A.Area=" << A.Get_Area() << endl;

    B.Set_Radius(3);
    cout << "B.Radius=" << B.Get_Radius() << endl;
    cout << "B.Girth=" << B.Get_Girth() << endl;
    cout << "B.Area=" << B.Get_Area() << endl;

    return 0;
}
```

该例程首先说明一个类 Circle。类中数据成员 radius 用于定义半径。成员函数 Set_Radius 用于设置半径的值，Get_Radius 获取半径，Get_Girth 计算并返回圆周长，Get_Area 计算并返回圆面积。

主函数中说明了圆类 Circle 的两个圆：A 和 B。A 和 B 称为 Circle 类的实例或对象。main 函数中由对象调用成员函数输出两个圆的半径、周长和面积。

这个程序看起来要烦琐一些。但是，以 Circle 类为基础，可以很方便地派生新的类。新的类对原有类的特性不需要重定义，可以自己定义新的数据，例如，指定圆心坐标，填充圆的颜色；派生出球体、圆柱体等新的几何体。每个新类都可以拥有自己的成员函数，实现自己特有的功能，这是结构化程序设计方法所做不到的。面向对象技术提供了软件重用、解决大问题和复杂问题的有效途径。

## C++ 语言的字符集与词汇

由字符可以组成“词”，由词组成“表达式”、“句子”，由各种句子又可以构成“函数”、“程序”。

### 字符集

C++ 语言的字符集是 ASCII 码的子集：

- 26 个小写字母 abcdefghijklmnopqrstuvwxyz
- 26 个大写字母 ABCDEFGHIJKLMNOPQRSTUVWⅩYZ
- 10 个数字 0123456789
- 空格 !"＃%&'()*+-/:;<=>?[\]^_{|}～.

### 词汇

单词是语言中有意义的最小语法单位。根据构成规则，一个单词由一个或多个字符组成。

### 常数

常数是指按照特定类型语法规则解释的数据值。C++语言常数有数值、字符和字符串。数据的书写形式表示了它的类型和值。

基本类型的常数在程序运行时直接参与运算，不需占用内存单元存储。

## C++ 语言的数据类型

[![BeU8f0.png](https://s1.ax1x.com/2020/10/25/BeU8f0.png)](https://imgchr.com/i/BeU8f0)

基本类型是系统用于表示可以直接处理的数据值。结构类型是由一些其他类型按一定规则组合而成的。

指针是一种特殊的简单数据类型，用于表示对象的地址值。

空类型不是值意义可以直接解释的数据类型，它用于表示函数无返回值，或指针所指对象无结构。此时需要通过强类型转换才能解释数据。

### 存储长度

内存以字节为基本存储单位，1字节是8位二进制位。

[![BeB2o4.png](https://s1.ax1x.com/2020/10/25/BeB2o4.png)](https://imgchr.com/i/BeB2o4)

## 数据对象与访问

程序中必须使用一些内存单元存放数据。程序的代码可以读出或改写这些存储单元的内容，对内存的读、写操作称为访问。

程序可以用标识符命名指定存储单元。若定义的内存对象**既能读又能写**，则称为变量；一旦把数据存入内存单元，程序中就**不能修改的对象**称为常量。

### 访问变量

程序运行时占有内存的实体，包括数据（常量、变量）、代码（函数）都可以称为对象。数据是程序处理的对象，程序是编译器的处理对象。“对象”是一个广义的概念。对对象的访问包括对内存相关单元内容的读和写操作。

内存单元由操作系统按字节编号，称为地址。当程序出现常量或变量说明语句时，编译器按类型分配存储空间，把地址写入标识符表。标识符就是获得分配的内存单元的名字。

例如，对已经说明的变量：

```c++
int a；
```

[![BeD5NQ.png](https://s1.ax1x.com/2020/10/25/BeD5NQ.png)](https://imgchr.com/i/BeD5NQ)

内存状态示意如图所示。标识符 a 是变量名，按照类型 int 分配 4 字节存储空间，第 1 字节的地址 0x8FC6FFF4 称为变量 a 的地址。地址值是系统分配的，不能由高级程序设计语言决定，但 C++可以通过代码获取对象被分配的地址值。

在内存建立一个对象后，可以用名方式和地址方式访问。

对于数据单元，名访问就是操作对象的内容。名访问又称直接访问。访问形式分为“读”和“写”两种。例如，有赋值表达式：

变量 = 表达式

其中，运算符“=”称为赋值号。其功能是首先计算“表达式”的值，然后写入“变量”代表的存储单元，用新的值代替旧的值。

如果对象名出现在“表达式”中，表示读出对象的值。而对赋值号左边的对象进行写操作，把表达式的运算结果写入对象中。

按地址找到所需的内存空间。对象的地址用于指示对象的存储位置，称为对象的“指针”。指针所指的物理存储空间称为“指针所指对象”。通过地址访问对象又称为“指针访问”。

```c++
#include <iostream>

using namespace std;

int main() {
    int a = 451;
    cout << a << endl;
    cout << (&a) << endl;
    cout << *(&a) << endl;
    return 0;
}
```

void 指针变量能够存放任意对象的地址。因为没有关联类型，编译器无法解释所指对象，因此，在程序中必须对其作强制类型转换，才可以按指定类型使用数据。

```c++
#include <iostream>

using namespace std;

int main() {
    int a = 65;
    int *ip;
    void *vp = &a;
    cout << *(int *) vp << endl;
    cout << *(char *) vp << endl;
    ip = (int *) vp;
    cout << (*ip) << endl;
    return 0;
}
```

### 引用

C++ 允许为对象定义别名，称为“引用”。

```c++
#include <iostream>

using namespace std;

int main() {
    int a;
    int *pa;
    int &ra = a; // ra 是 a 的别名，只能在定义时初始化
    pa = &a; // pa 指向 a，这里“&”是取址符
    return 0;
}
```

### 常量和约束访问

C++ 语言中，关键字 const 可以约束对象的访问性质，使对象值一旦初始化就不允许修改。被约束为只读的对象称为常对象。

用 const 约束指针对所指对象访问时，这个指针称为指向常量的指针。

const 写在关联类型之前或者紧跟关联类型之后，表示约束所指对象访问。

指向常量的指针变量可以获取变量或常量的地址，但限制用指针间址访问对象方式为“只读”。

C++ 语言为了保证标识常量的只读性，常量的地址只能赋给指向常量的指针。

指针常量的意义是指针变量的值只能在定义的时候初始化，定义后不能修改，即不能改变指针变量的指向。但不影响所指对象的访问特性。

## 数据输入和输出

C++ 的输入、输出操作由 I/O 流库提供。cin 和 cout 是流库预定义的两个标准对象，分别连接键盘和屏幕，它们在头文件 iostream 中说明。

### 键盘输入

键盘输入的作用是读取用户输入的字符串，按相应变量的类型转换成二进制代码写入内存。

```c++
#include <iostream>

using namespace std;

int main() {
    double x, y, *p = &y;
    cin >> x >> *p;
    return 0;
}
```

其中，cin 是预定义输入流对象；>> 在流操作中称为提取运算符。

输入的各数据用空格或换行符分隔。cin 不接受空格或换行符的键盘输入。

### 屏幕输出

屏幕输出的作用是从内存读取数据项，并对表达式求值，转换成相应的字符串显示到屏幕上。

```c++
#include <iostream>

using namespace std;

int main() {
    double x, y, *p = &y;
    cin >> x >> *p;

    cout << x << *p << endl;
    return 0;
}
```

其中，cout 是预定义输出流对象；<< 在流操作中称为插入运算符；表达式 1 ～表达式 n 是输出项。

cout 的插入操作首先对各输出项的表达式求值，然后转换成字符串形式输出。

提取符“>>”和插入符“<< ”是 I/O 流重载的运算符，重载运算符可以改变语义，但不能改变优先级。当输出项表达式中的运算符优先级高于插入符时，cout 能够正确地先计算值后输出；反之，就会出编译错误。

赋值符和条件运算的优先级都低于插入运算符。

```c++
#include <iostream>

using namespace std;

int main() {
    int a, b = 2;
    cout << (a = b) <<endl;
    cout << (a > b ? a : b);
    return 0;
}
```

输出项可以包含各种控制格式的符号或函数。例如，制表符'\t'，换行符'\n'等特殊控制字符可以直接嵌入字符串输出项中。I/O 流还提供了一批数据输出格式控制符，它们作为独立输出项目使用。

### 常用输出格式控制符

[![Be6Wxs.png](https://s1.ax1x.com/2020/10/25/Be6Wxs.png)](https://imgchr.com/i/Be6Wxs)

```c++
#include <iostream>

using namespace std;

int main() {
    cout << "Time is scarce,\nvery precious.\n\n";
    cout << "Time is scarce," << '\n' << "very precious." << '\n';
}
```

```c++
#include <iostream>

using namespace std;

int main() {
    int a, b, s;
    cout.setf(ios::showbase);
    a = 01137;
    b = 023362;
    s = a + b;
    cout << "8\n";
    cout << oct << a << "+" << b << "=" << s << endl;
    a = 239;
    b = 5618;
    s = a + b;
    cout << "10\n";
    cout << dec << a << "+" << b << "=" << s << endl;
    a = 0x1a3e;
    b = 0x4bf;
    s = a + b;
    cout << "16\n";
    cout << hex << a << "+" << b << "=" << s << endl;
}
```


```c++

```

```c++

```


```c++

```

```c++

```


```c++

```

```c++

```


```c++

```

```c++

```


```c++

```


