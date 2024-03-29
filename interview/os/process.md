---
date: 2022-10-29T12:00:55+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "进程管理"  # 文章标题
url:  "posts/cpp/interview/os/process"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 进程与线程有什么区别

进程是具有一定独立功能的程序关于某个数据集合上的一次运行活动，它是系统进行资源分配和调度的一个独立单位。

线程是进程的一个实体，是 CPU 调度和分配的基本单位，线程自己基本上不拥有系统资源，只拥有一些在运行中必不可少的资源（如程序计数器、一组寄存器和栈），但是，它可以与同属一个进程的其他的线程共享进程所拥有的全部资源。

在没有实现线程的操作系统中，**进程**既是**资源分配的基本单位**，又是调度的基本单位，它是系统中并发执行的单元。而在实现了线程的操作系统中，进程是资源分配的基本单位，而**线程是调度的基本单位**，是系统中并发执行的单元。

引入线程主要有以下 4 个方面的优点：

1. 易于调度。

2. 提高并发性。通过线程可以方便有效地实现并发。

3. 开销小。创建线程比创建进程要快，所需要的开销也更少。

4. 有利于发挥多处理器的功能。通过创建多线程，每个线程都在一个处理器上运行，从而实现应用程序的并行，使每个处理器都得到充分运行。

需要注意的是，尽管线程与进程很相似，但两者也存在着很大的不同，区别如下：

1. 一个线程必定属于也只能属于一个进程；而一个进程可以拥有多个线程并且至少拥有一个线程。

2. 属于一个进程的所有线程共享该进程的所有资源，包括打开的文件、创建的 Socket 等。不同的进程互相独立。

3. 线程又被称为轻量级进程。进程有进程控制块，线程也有线程控制块。但线程控制块比进程控制块小得多。线程间切换代价小，进程间切换代价大。

4. 进程是程序的一次执行，线程可以理解为程序中一个程序片段的执行。

5. 每个进程都有独立的内存空间，而线程共享其所属进程的内存空间。

## 程序、进程与线程的区别是什么

| 名称 | 描述 |
| -------- | -------- |
| 程序 | 一组指令的有序结合，是静态的指令，是永久存在的 |
| 进程 | 具有一定独立功能的程序关于某个数据集合上的一次运行活动，是系统进行资源分配和调度的一个独立单元。进程的存在是暂时的，是一个动态概念 |
| 线程 | 线程的一个实体，是 CPU 调度和的基本单元，是比进程更小的能独立运行的基本单元。本身基本上不拥有系统资源，只拥有一些在运行中必不可少的资源（如程序计数器、一组寄存器和栈）。一个线程可以创建和撤销另一个线程，同一个进程中的多个线程之间可以并发执行 |

## 线程同步有哪些机制

1. 临界区：通过对多线程的串行化来访问公共资源或一段代码，速度快，适合控制数据访问。在任意时刻只允许一个线程访问共享资源，如果有多个线程试图访问共享资源，那么当有一个线程进入后，其他试图访问共享资源的线程将会被挂起，并一直等到进入临界区的线程离开，临界在被释放后，其他线程才可以抢占。

2. 互斥量：为协调对一个共享资源的单独访问而设计，只有拥有互斥量的线程，才有权限去访问系统的公共资源，因为互斥量只有一个，所以能够保证资源不会同时被多个线程访问。互斥不仅能实现同一应用程序的公共资源安全共享，还能实现不同应用程序的公共资源安全共享。

3. 信号量：为控制一个具有有限数量的用户资源而设计。它允许多个线程在同一个时刻去访问同一个资源，但一般需要限制同一时刻访问此资源的最大线程数目。

4. 事件：用来通知线程有一些事件已发生，从而启动后继任务的开始。

### 内核线程和用户线程的区别

根据操作系统内核是否对线程可感知，可以把线程分为内核线程和用户线程。

内核线程的建立和销毁都是由操作系统负责、通过系统调用完成的，操作系统在调度时，参考各进程内的线程运行情况做出调度决定。如果一个进程中没有就绪态的线程，那么这个进程也不会被调度占用 CPU。

和内核线程对应的是用户线程。用户线程指不需要内核支持而在用户程序中实现的线程，其不依赖于操作系统核心，用户进程利用线程库提供创建、同步、调度和管理线程的函数来控制用户线程。用户线程多见于一些历史悠久的操作系统，如 UNIX 操作系统，不需要用户态 / 核心态切换，速度快，操作系统内核不知道多线程的存在，因此一个线程阻塞将使得整个进程（包括它的所有线程）阻塞。由于这里的处理器时间片分配是以进程为基本单位的，所以每个线程执行的时间相对减少。为了在操作系统中加入线程支持，采用了在用户空间增加运行库来实现线程，这些运行库被称为“线程包”，用户线程是不能被操作系统所感知的。

引入用户线程有以下 4 个方面的优势：

1. 可以在不支持线程的操作系统中实现。

2. 创建和销毁线程、线程切换等线程管理的代价比内核线程少得多。

3. 允许每个进程定制自己的调度算法，线程管理比较灵活。

4. 线程能够利用的表空间和堆栈空间比内核级线程多。

用户线程的缺点主要有以下两点：

1. 同一进程中只能同时有一个线程在运行，如果有一个线程使用了系统调用而阻塞，那么整个进程都会被挂起。

2. 页面失效也会导致整个进程被挂起。

内核线程的优缺点刚好跟用户线程相反。实际上，操作系统可以使用混合的方式来实现线程。

```c++

```
