---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP11_智能指针"
url:  "posts/cpp/docs/CPP/CPP_11/第3章_C++新特性_CPP11_智能指针"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [shared_ptr](#shared_ptr)
  - [使用方法](#使用方法)
  - [注意点](#注意点)
- [weak_ptr](#weak_ptr)
- [unique_ptr](#unique_ptr)

## shared_ptr

shared_ptr 使用了引用计数，每一个 shared_ptr 的拷贝都指向相同的内存，每次拷贝都会触发引用计数 +1，每次生命周期结束析构的时候引用计数 -1，在最后一个 shared_ptr 析构的时候，内存才会释放。

### 使用方法

```c++
struct ClassWrapper {
    ClassWrapper() {
        cout << "construct" << endl;
        data = new int[10];
    }
    ~ClassWrapper() {
        cout << "deconstruct" << endl;
        if (data != nullptr) {
            delete[] data;
        }
    }
    void Print() {
        cout << "print" << endl;
    }
    int* data;
};

void Func(std::shared_ptr<ClassWrapper> ptr) {
    ptr->Print();
}

int main() {
    auto smart_ptr = std::make_shared<ClassWrapper>();
    auto ptr2 = smart_ptr; // 引用计数+1
    ptr2->Print();
    Func(smart_ptr); // 引用计数+1
    smart_ptr->Print();
    ClassWrapper *p = smart_ptr.get(); // 可以通过get获取裸指针
    p->Print();
    return 0;
}
```

智能指针还可以自定义删除器，在引用计数为 0 的时候自动调用删除器来释放对象的内存，代码如下：

```c++
std::shared_ptr<int> ptr(new int, [](int *p){ delete p; });
```

### 注意点

- 不要用一个裸指针初始化多个 shared_ptr，会出现 double_free 导致程序崩溃
- 通过 shared_from_this() 返回 this 指针，不要把 this 指针作为 shared_ptr 返回出来，因为 this 指针本质就是裸指针，通过 this 返回可能 会导致重复析构，不能把 this 指针交给智能指针管理。

```c++
class A {
    shared_ptr<A> GetSelf() {
        return shared_from_this();
        // return shared_ptr<A>(this); 错误，会导致double free
    }  
};
```

- 尽量使用 make_shared，少用 new。
- 不要 delete get() 返回来的裸指针。
- 不是 new 出来的空间要自定义删除器。
- 要避免循环引用，循环引用导致内存永远不会被释放，造成内存泄漏。

```c++
using namespace std;
struct A;
struct B;

struct A {
    std::shared_ptr<B> bptr;
    ~A() {
        cout << "A delete" << endl;
    }
};

struct B {
    std::shared_ptr<A> aptr;
    ~B() {
        cout << "B delete" << endl;
    }
};

int main() {
    auto aaptr = std::make_shared<A>();
    auto bbptr = std::make_shared<B>();
    aaptr->bptr = bbptr;
    bbptr->aptr = aaptr;
    return 0;
}
```

上面代码，产生了循环引用，导致 aptr 和 bptr 的引用计数为 2，离开作用域后 aptr 和 bptr 的引用计数 -1，但是永远不会为 0，导致指针永远不会析构，产生了内存泄漏，如何解决这种问题呢，答案是使用 weak_ptr。

## weak_ptr

weak_ptr 是用来监视 shared_ptr 的生命周期，它不管理 shared_ptr 内部的指针，它的拷贝的析构都不会影响引用计数，纯粹是作为一个旁观者监视 shared_ptr 中管理的资源是否存在，可以用来返回 this 指针和解决循环引用问题。

- 作用 1：返回 this 指针，上面介绍的 shared_from_this() 其实就是通过 weak_ptr 返回的 this 指针。
- 作用 2：解决循环引用问题。

```c++
struct A;
struct B;

struct A {
    std::shared_ptr<B> bptr;
    ~A() {
        cout << "A delete" << endl;
    }
    void Print() {
        cout << "A" << endl;
    }
};

struct B {
    std::weak_ptr<A> aptr; // 这里改成weak_ptr
    ~B() {
        cout << "B delete" << endl;
    }
    void PrintA() {
        if (!aptr.expired()) { // 监视shared_ptr的生命周期
            auto ptr = aptr.lock();
            ptr->Print();
        }
    }
};

int main() {
    auto aaptr = std::make_shared<A>();
    auto bbptr = std::make_shared<B>();
    aaptr->bptr = bbptr;
    bbptr->aptr = aaptr;
    bbptr->PrintA();
    return 0;
}
```

输出：

```c++
A
A delete
B delete
```

## unique_ptr

std::unique_ptr 是一个独占型的智能指针，它不允许其它智能指针共享其内部指针，也不允许 unique_ptr 的拷贝和赋值。使用方法和 shared_ptr 类似，区别是不可以拷贝：

```c++
using namespace std;

struct A {
    ~A() {
        cout << "A delete" << endl;
    }
    void Print() {
        cout << "A" << endl;
    }
};


int main() {
    auto ptr = std::unique_ptr<A>(new A);
    auto tptr = std::make_unique<A>(); // error, c++11还不行，需要c++14
    std::unique_ptr<A> tem = ptr; // error, unique_ptr不允许移动
    ptr->Print();
    return 0;
}
```
