---
date: 2022-11-06T08:35:59+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "new 与 malloc 的区别"  # 文章标题
url:  "posts/cpp/docs/grammar/new"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

new 的功能是在堆区新建一个对象，并返回该对象的指针。新建对象将调用该类的构造函数，因为如果不构造的话，就不能称之为一个对象。

而 malloc 只是机械的分配一块内存，如果用 mallco 在堆区创建一个对象的话，是不会调用构造函数的严格说来用 malloc 不能算是新建了一个对象，只能说是分配了一块与该类对象匹配的内存而已，然后强行把它解释为这是一个对象。

用 delete 去释放一个堆区的对象，会调用该对象的析构函数。用 free 去释放一个堆区的对象，不会调用该对象的析构函数。

```c++
#include <iostream>
#include <malloc.h>

class Object {
private:
  int member;

public:
  Object() {
    member = 10;
  }

  void Print() {
    std::cout << "member is " << member << std::endl;
  }
};

int main() {
  auto *pObject1 = (Object *) malloc(sizeof(Object));
  pObject1->Print();

  auto *pObject2 = new Object;
  pObject2->Print();

  return 0;
}
```

```
member is 1904876720
member is 10
```

```c++
int main() {
  auto *a = (int *) malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    std::cout << a[i] << ", ";
  }

  std::cout << std::endl;

  auto *b = new int[10];
  for (int i = 0; i < 10; i++) {
    std::cout << b[i] << ", ";
  }

  return 0;
}
```

```
-1852695376, 576, -1852702384, 576, 0, 0, 0, 0, 0, 0, 
-1854065504, 576, -1852696208, 576, 0, 0, 0, 0, 0, 0, 
```


## 二级

### 三级

```c++

```

```c++

```
