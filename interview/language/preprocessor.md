---
date: 2022-10-26 10:05:54+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "预处理"  # 文章标题
url:  "posts/cpp/interview/language/preprocessor"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 简介

预处理也称为预编译，它为编译做预备工作，主要进行代码文本的替换工作，用于处理 # 开头的指令，其中预处理器产生编译器的输出。表 1-2 所示为常见的一些预处理指令及其功能。

| 指令 | 功能 |
| -------- | -------- |
| # | 空指令，无任何效果 |
| #include | 包含一个源代码文件，把源文件中的 #include 扩展为文件正文，即把包含的.h 文件找到并扩展到 #include 所在处 |
| #define | 定义宏 |
| #undef | 取消已定义的宏 |
| #if | 条件编译指令，如果给定条件为真，则编译下面代码 |
| #ifdef | 条件编译指令，如果宏已经定义，则编译下面代码 |
| #ifndef | 条件编译指令，如果宏没有定义，则编译下面代码 |
| #elif | 条件编译指令，如果前面的 #if 给定条件不为真，当前条件为真，则编译下面代码 |
| #endif | 结束一个 #if...#else 条件编译块 |
| #error | 停止编译并显示错误信息 |

经过预处理器处理的源程序与之前的源程序会有所不同，在预处理阶段进行的工作只是纯粹地替换与展开，没有任何计算功能，所以在学习 #define 命令时只有真正地理解这一点，才不会误解并误用此命令。

## ifndef/define/endif 的作用有哪些

C/C++ 头文件中的 ifndef/define/endif 主要用于防止头文件的重复包含和编译。

如果一个项目中存在两个 C 文件，而这两个 C 文件都 include（包含）了同一个头文件，当编译时，这两个 C 文件要一同编译成一个可运行文件，可能会产生大量的声明冲突。

## `#include<filename.h>` 和 `#include“filename.h”` 有什么区别

对于 `#include <filename.h>` ，编译器先从标准库路径开始搜索 filename.h，使得系统文件调用较快。而对于 `#include“filename.h”`，编译器先从用户的工作路径开始搜索 filename.h，然后去寻找系统路径，使得自定义文件较快。

## 头文件的作用有哪些

1. 通过头文件来调用库功能。出于对源代码保密的考虑，源代码不便（或不准）向用户公布，只要向用户提供头文件和二进制的库即可。用户只需要按照头文件中的接口声明来调用库功能，而不必关心接口是怎么实现的。编译器会从库中提取相应的代码。

2. 头文件能加强类型安全检查。当某个接口被实现或被使用时，其方式与头文件中的声明不一致，编译器就会指出错误。

## `#define` 有哪些缺陷

由于宏定义在预处理阶段进行，主要做的是字符替换工作，所以它存在着一些固有的缺陷：

1. 它无法进行类型检查。宏定义是在预处理阶段进行字符的替换，因此无法检查类型。

2. 由于优先级的不同，在使用宏定义时，可能会存在副作用。例如，执行加法操作的宏定义运算 `#define ADD(a,b) a+b`，在使用的过程中，对于表达式的运算就可能存在潜在的问题，例如，当使用如下代码使用这个宏的时候就会有问题：`ADD(2,2) * 5` 进行宏替换后实际执行的语句为：`2+2 * 5`。所以正确的定义应该为 `#define ADD(a,b) ((a)+(b))`。

3. 无法单步调试。

4. 会导致代码膨胀。由于宏定义是文本替换，需要对代码进行展开，相比较函数调用的方式，会存在较多的冗余代码。

5. 在 C++ 语言中，使用宏无法操作类的私有数据成员。

## 如何使用 define 声明一个常数，用以表明 1 年中有多少秒（忽略闰年问题）

```c++
#define SECOND_PER_YEAR (60*60*24*365)UL
```

在以上定义中，需要注意以下 3 方面的内容。

1. 由于宏定义是预处理指令，而非语句，所以进行宏定义时，不能以分号结束。

2. 预处理只会执行简单的替换，不会计算表达式的值，所以需要注意括号的使用，直接写出是如何计算出一年中有多少秒，而不是计算出实际的值。

3. 考虑到可能存在数据溢出问题，更加规范化的写法是使用长整型，即 UL 类型，告诉编译器这个常数是长整型数。

## 含参数的宏与函数有什么区别

含参数的宏有时完成的是函数实现的功能，但是并非所有的函数都可以被含参数的宏替代。具体而言，含参数的宏与函数的特点如下：

1. 函数调用时，首先求出实参表达式的值，然后带入形参，而使用带参的宏只是进行简单的字符替换。

2. 函数调用是在程序运行时处理的，它需要分配临时的内存单元，在函数调用的时候需要参数传递、压栈与弹栈操作；而宏展开则是在编译时进行的，在展开时并不分配内存单元，也不进行值的传递处理，也没有“返回值”的概念。也就是说，函数调用占用的是运行时间，而宏替换占用的是编译时间。因此，使用宏会有更好的执行效率。

3. 对函数中的实参和形参都要定义类型，两者的类型要求一致，如果不一致，应进行类型转换；而宏不存在类型问题，宏名无类型，它的参数也无类型，只是一个符号代表，展开时带入指定的字符即可。宏定义时，字符串可以是任何类型的数据。

4. 使用宏次数多时，宏展开后源程序会变得很长，因为每展开一次都使程序内容增长，而函数调用不使源程序变长。

5. 参数每次用于宏定义时，它们都将重新求值，由于多次求值，具有副作用的参数可能会产生不可预料的结果。而参数在函数被调用前只求值一次，在函数中多次使用参数并不会导致多种求值过程，参数的副作用并不会造成任何特殊的问题。

6. 在 C++ 语言中，宏不能访问对象的私有成员，而成员函数就可以访问。

7. 可以在函数体内设置断点进行单步调试，但是不能在宏定义中设置断点进行单步调试。

一般来说，用宏代表简短的表达式比较合适。

## 宏定义平方运算 `#define SQR(X) X*X` 是否正确

错误。出现的问题都是由于宏定义是文本替换导致的，对于这类问题，最好的解决方法就是通过添加括号来明确操作的优先级。

```c++
#define SQR(X) (X)*(X)
```

因此在使用宏定义的时候，一定要有一个清晰的概念：它会在编译的时候展开直接进行文本替换，这样在定义宏的时候就可以避免很多错误，比如对用到宏定义参数的时候，可以通过加括号等方法来避免错误。

## 如何判断一个变量是有符号数还是无符号数

1. 采用取反操作。对于这个变量，分两种情况分析：一种情况是它为某种类型的值（判断某一个具体的值是有符号数还是无符号数）；另一种情况是它为某种类型（判断给定的类型是有符号类型还是无符号类型）。对于值而言，如果**这个数以及其求反后的值都大于 0，则该数为无符号数**，反之则为有符号数，因为数据在计算机中都是以二进制的 0 或 1 存储的，正数以 0 开头，负数以 1 开头，求反操作符会把所有的 1 改为 0，所有的 0 改为 1。如果是有符号数，那么取反之后，开头的 0 会被改为 1，开头的 1 会被改为 0，开头为 1 时即表示该数为负数，如果是无符号数则不会受此影响。对于类型而言，也同样适用。

对于为值的情况，可以采用如下宏定义的方式：

```c++
#define ISUNSIGNED(a) (a>=0&&～a>=0)
```

对于为类型的情况，可以采用如下宏定义的方式：

```c++
#define ISUNSIGNED(type) ((type)0-1>0)
```

2. 由于无符号数和有符号数相减的结果为无符号数，所以还可以采用以下方法判断：

```c++
#include <iostream>

int main() {
  unsigned int a = 100;
  int b = -1;

  if (a < 0) {
    std::cout << "a is a signed number" << std::endl;
  } else {
    if (b - a > 0) {
      std::cout << "a is an unsigned number" << std::endl;
    } else {
      std::cout << "a is a signed number" << std::endl;
    }
  }

  return 0;
}
```

3. 通过改变符号位判断。把变量 a 进行一个位运算，将最高位`置 1`，判断是否大于 0。

```c++
#include <iostream>

#define IS_UNSIGNED(a) ((a) | (1 << 31)) > 0

int main() {
  unsigned int a = 100;

  if (IS_UNSIGNED(a)) {
    std::cout << "a is unsigned" << std::endl;
  } else {
    std::cout << "a is signed" << std::endl;
  }

  return 0;
}
```

## `#define TRACE(S) (printf("%s\n", #S), S)` 是什么意思

`#` 进行宏字符串连接，在宏中把参数解释为字符串，不可以在语句中直接使用。在宏定义中，`printf("%s\n", #S)` 被解释为 `printf("%s\n","S")`。

```c++
#include <cstring>
#include <iostream>

#define TRACE(S) (printf("%s\n", #S), S)

int main() {
  int a = 5;
  int b = TRACE(a);

  const char *c = "Hello";
  char d[50];
  strcpy(d, TRACE(c));

  std::cout << d << std::endl;

  return 0;
}
```

上例中的代码用到了逗号表达式，为了能准确地理解上述程序的运行结果，下面首先介绍逗号表达式：逗号表达式从左往右计算，但返回右边的数据值作为表达式值。例如：

```c++
int c=(1,2); // c 的值为 2
```

## 枚举和 define 有什么不同

两者只有很小的区别。在 C 语言中，枚举为整型，枚举常量为 int 型，因此它们都可以和其他整型类别混用，而不会出错，而且枚举优点众多：能自动赋值；调试器在检验枚举变量时，可以显示符号值；服从数据块作用域规则。具体而言，两者的区别表现在以下 6 个方面：

1. 枚举常量是实体中的一种，而宏定义不是实体。

2. 枚举常量属于常量，但宏定义不是常量。

3. 枚举常量具有类型，但宏没有类型，枚举变量具有与普通变量相同的性质，如作用域、值等，但是宏没有。

4. #define 宏常量是在预编译阶段进行简单替换，枚举常量则是在编译的时候确定其值。

5. 一般在编译器里，可以调试枚举常量，但是不能调试宏常量。

6. 枚举可以一次定义大量相关的常量，而 #define 宏一次只能定义一个。

## typdef 和 define 有什么区别

typedef 与 define 都是替一个对象取一个别名，以此来增强程序的可读性，但是它们在使用和作用上也存在着以下 4 个方面的不同。

### 原理不同

`#define` 是 C 语言中定义的语法，它是预处理指令，在预处理时进行简单而机械的字符串替换，不做正确性检查，不管含义是否正确照样代入，只有在编译已被展开的源程序时，才会发现可能的错误并报错。

typedef 是关键字，它在编译时处理，所以 typedef 具有类型检查的功能。它在自己的作用域内给一个已经存在的类型一个别名，但是不能在一个函数定义里面使用标识符 typedef。例如，`typedef int INTEGER`，这以后就可用 INTEGER 来代替 int 作整型变量的类型说明了，例如：

```c++
typedef int INTEGER

INTEGER a, b;
```

用 typedef 定义数组、指针、结构等类型将带来很大的方便，不仅使程序书写简单而且使意义更为明确，因而增强了可读性。例如：

```c++
typedef int a[10];
```

表示 a 是整型数组类型，数组长度为 10。然后就可用 a 说明变量，例如语句 `a s1,s2;` 完全等效于语句 `int s1[10],s2[10];`。同理，`typedef void (*p)(void)` 表示 p 是一种指向 void 型的指针类型。

### 功能不同

typedef 用来定义类型的别名，这些类型不仅包含内部类型（int、char 等），还包括自定义类型（如 struct），可以起到使类型易于记忆的功能。

```c++
typedef int (*PF) (const char*, const char*);
```

定义一个指向函数的指针的数据类型 PF，其中函数返回值为 int，参数为 const char *。

typedef 还有另外一个重要的用途，那就是定义机器无关的类型。例如，可以定义一个叫 REAL 的浮点类型，在目标机器上它可以获得最高的精度：`typedef long double REAL`，在不支持 long double 的机器上，该 typedef 看起来会是下面这样：typedef double REAL，在 double 都不支持的机器上，该 typedef 看起来会是这样：typedef float REAL。

#define 不只是可以为类型取别名，还可以定义常量、变量、编译开关等。

### 作用域不同

#define 没有作用域的限制，只要是之前预定义过的宏，在以后的程序中都可以使用，而 typedef 有自己的作用域。

### 对指针的操作不同

两者修饰指针类型时，作用不同。

```c++
#define INTPTR1 int*
typedef int* INTPTR2;
INTPTR1 p1,p2;
INTPTR2 p3,p4;
```

`INTPTR1 p1,p2` 和 `INTPTR2 p3,p4` 的效果截然不同。`INTPTR1 p1,p2` 进行字符串替换后变成 `int * p1,p2`，要表达的意义是声明一个指针变量 p1 和一个整型变量 p2。而 `INTPTR2 p3,p4`，由于 INTPTR2 是具有含义的，告诉我们是一个指向整型数据的指针，那么 p3 和 p4 都为指针变量，这句相当于` int * p1, * p2`。从这里可以看出，进行宏替换是不含任何意义的替换，仅仅为字符串替换；而用 typedef 为一种数据类型起的别名是带有一定含义的。

程序示例如下：

```c++
#define INTPTR1 int*
typedef int*INTPTR2;
int a=1;
int b=2;
int c=3;
const INTPTR1 p1=&a;
const INTPTR2 p2=&b;
INTPTR2 const p3=&c;
```

上述代码中，`const INTPTR1 p1` 表示 p1 是一个常量指针，即不可以通过 p1 去修改 p1 指向的内容，但是 p1 可以指向其他内容。而对于 `const INTPTR2 p2`，由于 INTPTR2 表示的是一个指针类型，因此用 const 去限定，表示封锁了这个指针类型，因此 p2 是一个指针常量，不可使 p2 再指向其他内容，但可以通过 p2 修改其当前指向的内容。`INTPTR2 const p3` 同样声明的是一个指针常量。

## C++ 中宏定义与内联函数有什么区别

宏代码本身不是函数，但使用起来却像函数，预处理器用复制宏代码的方式代替函数调用，省去了参数压栈、生成汇编语言的 CALL 调用、返回参数、执行 return 等过程，从而提高了速度。

内联函数是代码被插入到调用者代码处的函数。对于 C++ 而言，内联函数（inline）的作用也不是万能的，它的使用是有所限制的，它只适合函数体内代码简单的函数使用，不能包含复杂的结构控制语句（如 while、switch），并且内联函数本身不能直接调用递归函数（自己内部还调用自己的函数）。

inline 函数可以被定义为递归函数，但是，一旦被定义为递归函数，这个函数将会失去 inline 的功能，因为在编译阶段，编译器无法知道递归的深度。

两者的区别主要表现在以下两个方面：第一，宏定义是在预处理阶段进行代码替换，而内联函数是在编译阶段插入代码；第二，宏定义没有类型检查，而内联函数有类型检查。

## 内联函数与普通函数的区别有哪些

内联函数的参数传递机制与普通函数相同，但是编译器会在每个调用内联函数的地方将内联函数的内容展开，这样既避免了函数调用的开销，又没有宏机制的缺陷。

内联函数和普通函数最大的区别在于其内部的实现，普通函数在被调用时，系统首先要跳跃到该函数的入口地址，执行函数体，执行完成后，再返回到函数调用的地方，函数始终只有一个复制；而内联函数则不需要进行一个寻址的过程，当执行到内联函数时，此函数展开，如果在 N 处调用了此内联函数，则此函数就会有 N 个代码段的复制。

内联函数也并非是万能的，在使用的过程中也存在一定的局限性，如果函数体过大，编译器也会放弃内联方式，而采用普通的方式调用函数。此时，内联函数就和普通函数执行效率一样了。

## 定义常量谁更好？#define 还是 const

define 与 const 都能定义常量，效果虽然一样，但是各有侧重。define 既可以替代常数值，又可以替代表达式，甚至是代码段，但是容易出错，而 const 的引入可以增强程序的可读性，它使程序的维护与调试变得更加方便。具体而言，它们的差异主要表现在以下 3 个方面。

1. define 只是用来进行单纯的文本替换，define 常量的生命周期止于编译期，不分配内存空间，它**存在于程序的代码段**，在实际程序中，它只是一个常数；而 const 常量存在于程序的数据段，并在堆栈中分配了空间，const 常量在程序中确确实实存在，并且可以被调用、传递。

2. const 常量有数据类型，而 define 常量没有数据类型。编译器可以对 const 常量进行类型安全检查，如类型、语句结构等，而 define 不行。

3. 很多 IDE 支持调试 const 定义的常量，而不支持 define 定义的常量。

由于 const 修饰的变量可以排除程序之间的不安全性因素，保护程序中的常量不被修改，而且对数据类型也会进行相应的检查，极大地提高了程序的健壮性，所以一般更加倾向于用 const 来定义常量类型。

```c++

```
