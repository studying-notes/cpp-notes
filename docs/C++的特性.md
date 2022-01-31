---
date: 2022-01-31T19:19:07+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C++的特性"  # 文章标题
# description: "文章描述"
url:  "posts/cpp/docs/C++的特性"  # 设置网页永久链接
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

## 运算符重载

在 C++ 语言的定乂中，很多运算符只能对简单的数据结构进行操作。例如，加法运算符只能用于两个数值类型的操作，要使两个字符串相加，可使用下列源代码重载加法运算符。

```c++
#include <iostream>
#include <cstring>
#include <cstdio>

class String {//创建字符串类 String
public:
    String(const char *str = NULL);//构造函数
    char *m_data;//放置字符串数据的成员
    char *addstr;//字符串相加时使用的临时空间
    String &operator+(const String &rhs);//重载加法运算符
};

String::String(const char *str) {
    if (str == NULL) {//如果输入为空字符串，则添加“\0”表示空串
        m_data = new char[1];//动态为字符串分配内存空间
        m_data[0] = '\0';//初始化字符串
    } else {//如果输入非空串，复制该字符串
        m_data = new char[strlen(str) + 1];
        strcpy(m_data, str);
    }
}

String &String::operator+(const String &rhs) {
    //为临时空间划分内存，长度为两个字符串之和
    addstr = new char[strlen(m_data) + strlen(rhs.m_data) + 1];

    strcpy(addstr, m_data);//将第一个字符串复制到临时空间中
    strcat(addstr, rhs.m_data);//将第二个字符串追加到临时空间中

    delete[]m_data;//释放为 m data成员所划分的内存空间

    m_data = new char[strlen(addstr) + 1];//以临时空间的长度为 m_data 成员划分内存空间

    strcpy(m_data, addstr);//将临时空间内的数据复制给 m_data 成员

    delete[]addstr;//释放临时空间
    return *this;//返回this指针
}

int main() {
    String s1("I Love ");
    String s2("C++!");
    s1 + s2;
    puts(s1.m_data);
    return 0;
}
```

## 继承

面向对象编程的一个重要特性是继承。继承是指利用一个类生成另一个类的对象，前者称为父类，后者称为子类。子类不但获得了父类的所有成员，还可以加上它自己的一些成员。例如，矩形和三角形都有属性底和高，那么可以利用它们之间的共同特点定义出父类 Cstd，再让矩形类 Crect 和三角形类 Celt 继承父类 Cstd。

```c++
#include <iostream>

using namespace std;

class Cstd {
public:
    void set_values(int a, int b) {
        width = a;
        height = b;
    }

protected:
    int width;
    int height;
};

class Crect : public Cstd {
public:
    int area() { return (width * height); }
};

class Cdelt : public Cstd {
public:
    int area() {
        return width * height / 2;
    }
};

int main() {
    Crect rect;
    Cdelt delt;
    rect.set_values(4, 5);
    delt.set_values(4, 5);

    cout << rect.area() << endl;
    cout << delt.area() << endl;

    return 0;
}
```

在程序中，类 Crect 和类 Celt 的每一个对象都包含类 Cstd 的成员 width、height 和 set values。标识符 protected 与 private 类似，它们的唯一区别是父类的 protected 成员可以被子类的其他成员所使用，然而 private 成员就不可以。

## 虚拟函数和多态性

虚拟函数是一种特殊的成员，该成员在父类中定义但不实现该函数的细节，而将细节留在子类中进行实现。虚拟函数必须加上关键字 virtual，以便可以使用指针对指向相应的对象进行操作。**多态性是通过虚拟函数实现的，即通过同一父类的虚拟函数，子类实现不同的细节**。代码如下：

```c++
class Cstd {
public:
    virtual int area() {
        return 0;
    }
    
    void set_values(int a, int b) {
        width = a;
        height = b;
    }

protected:
    int width;
    int height;
};
```

## 流输入与输出

C++ 输入与输岀操作是通过控制数据流实现的，流是数据的字节序列。在输入操作中数据从输入设备流向内存；输岀操作中，数据从内存流向输岀设备。C++ 提供了流输入输出函数库，函数库的名称是 iostream。该函数库将流输入输出定义为操作符 >> 和 <，前者的作用是输入，后者的作用是输出。另外，它在标准名字空间 std 中定义了 cin、cout 和 endl 函数，由此可见操作符 >> 和 < 是通过在这 3 个函数中的重载而实现的。cin 函数的作用是输入薮据流，cout 函数的作用是输岀数据流，end 函数的作用是立即将缓存中的数据全部输出。

## 模板

模板是 C++ 中更高级的特性。利用模板不仅可以指定全部相关的函数重载，即模板函数，还可以指定全部相关的类，即模板类。模板可以生成通用的函数，这些函数不仅能够接受任意数据类型的实际参数，而且可返回任意类型的值。使用模板后，不需要对所有可能的数据类型进行函数重载，简化了成员函数设计的难度，如下例所示。

```c++
#include <iostream>

using namespace std;

//定义模板 T，计算任何数据类型两个数之和
template<typename T>
T Add2Value(T a, T b) {
    T result;
    result = a + b;
    return result;
}

int main() {
    int i = 11, j = 55, k;
    float l = 2.323, m = 3.23, n;

    k = Add2Value(i, j);
    n = Add2Value(l, m);

    cout << k << endl;
    cout << n << endl;

    return 0;
}
```

template 是一个声明模板的关键字，typename 是用来表示之后的参数是一个类型的参数。早期的 C++ 版本中所使用的是 class，后来为了不与类产生混淆，所以增加关键字 typename。

## 异常处理

在程序运行中，很多时候无法确定一段代码是否能够正常工作。程序岀错的原因可能是因为程序访问了并不存在的资源，或者由于一些变量超岀了预期的范围等。这些情况统称为异常，C++ 新引入的 3 种操作符 try、throw 和 catch 能够帮助处理这些出错情况，如下例所示。

```c++

```

在该例中，如果变量 b 的值为 0，则抛出一个异常，因为除以 0 是会造成非常严重的错误。当 throw 被执行的时候，try 语句块立即被停止执行，在 try 语句块中生成的所有对象会被销毁。此后，控制权被传递给相应的 catch 语句块。最后程序紧跟着 catch 语句块继续向下执行。

```c++
#include <iostream>

using namespace std;

int main() {
    float a, b;
    cin >> a >> b;

    try {
        //如果b为0，throw语句将b的值抛出，终止try代码段执行
        if (b == 0) throw b;
        cout << a / b << endl;
    } catch (float n) {//如果 throw语句执行，接受 throw语句抛出的值
        cout << "error b=" << n << endl;
    }

    return 0;
}
```
