---
date: 2020-10-28T22:41:04+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "计算机考研之算法基本概念"  # 文章标题
url:  "posts/cpp/postgrad/complexity"  # 设置网页链接，默认使用文件名
tags: [ "cpp", "c" ]  # 自定义标签
series: [ "计算机考研笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 排序优先级
chapter: false  # 设置为章节

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

- [算法的特性](#算法的特性)
- [算法的设计目标](#算法的设计目标)
- [算法复杂度](#算法复杂度)
- [数据结构的基本概念](#数据结构的基本概念)
  - [数据](#数据)
  - [数据元素](#数据元素)
  - [数据对象](#数据对象)
  - [数据结构](#数据结构)
  - [数据的逻辑结构](#数据的逻辑结构)
    - [线性结构](#线性结构)
    - [非线性结构](#非线性结构)
  - [数据的物理结构](#数据的物理结构)
    - [顺序存储方法](#顺序存储方法)
    - [链式存储方法](#链式存储方法)
    - [索引存储方法](#索引存储方法)
    - [散列存储方法](#散列存储方法)
  - [判断数据结构类型](#判断数据结构类型)

算法可以理解为由基本运算及规定的运算顺序所构成的完整的**解题步骤**，或者看成按照要求设计好的有限的确切的**计算序列**。

## 算法的特性

有穷性、确定性、可行性、存在输入/输出。

- 可行性：算法中的所有操作都必须通过已经实现的基本操作进行运算，并在有限次内实现，而且人们用笔和纸做有限次运算后也可完成。

## 算法的设计目标

正确性、可读性、健壮性和算法效率（高效率和低存储空间）。

## 算法复杂度

时间复杂度即算法中基本操作的执行次数。

空间复杂度即算法运行时所需存储空间的度量。

## 数据结构的基本概念

### 数据

数据是对客观事物的符号表示，在计算机科学中是指所有能输入到计算机中并且被计算机程序处理的符号的总称。

### 数据元素

数据元素是数据的基本单位，是数据结构的最小单位，在计算机程序中通常将其作为个整体进行考虑和处理。有时，一个数据元素可由若干数据项组成。

### 数据对象

数据对象是性质相同的数据元素的集合，是数据的一个子集。

### 数据结构

数据结构是指相互之间存在一种或多种特定关系的数据元素的集合。数据结构包括 3 方面的内容逻辑结构、存储结构和对数据的运算。

### 数据的逻辑结构

数据的逻辑结构是对数据之间关系的描述，它与数据的存储结构无关，同一种逻辑结构可以有多种存储结构。归纳起来数据的逻辑结构主要有以下两大类。

#### 线性结构

简单地说，线性结构是一个数据元素的有序（次序）集合。它有以下 4 个基本特征：

- 集合中必存在唯一的个“第一个元素”
- 集合中必存在唯一的一个“最后一个元素”。
- 除最后一个元素之外，其他数据元素均有唯一的“后继”
- 除第一个元素之外，其他数据元素均有唯一的“前驱”。

数据结构中，线性结构是指数据元素之间存在着“一对一”的线性关系的数据结构。

#### 非线性结构

与线性结构不同，非线性结构中的结点存在着一对多的关系，它又可以细分为树形结构和图形结构。

### 数据的物理结构

数据的物理结构又称为存储结构，是数据的逻辑结构在计算机中的表示（又称映像）。它包括数据元素的表示和关系的表示。当数据元素是由若干数据项构成的时候，数据项的表示称为数据域。数据元素之间的关系在计算机中有两种不同的表示方法：顺序映像和非顺序映像。对应的两种不同的存储结构分别是顺序存储结构和链式存储结构。顺序映像是借助数据元素在存储器中的相对位置来表示数据元素之间的逻辑关系；非顺序映像是借助指针表示数据元素之间的逻辑关系。实际上，在数据结构中有以下 4 种常用的存储方法。

#### 顺序存储方法

顺序存储方法是存储结构类型中的一种，该方法是把逻辑上相邻的结点存储在物理位置上相邻的存储单元中，结点之间的逻辑关系由存储单元的邻接关系来体现。由此得到的存储结构称为顺序存储结构，通常顺序存储结构是借助于计算机程序设计语言的数组来描述的。

#### 链式存储方法

链式存储方法不要求逻辑上相邻的结点在物理位置上也相邻，结点间的逻辑关系是由附加的指针字段表示的。由此得到的存储结构表示称为链式存储结构，通常借助于计算机程序设计语言的指针类型来描述它。

#### 索引存储方法

索引存储方法在存储结点信息时除建立存储结点信息外，还建立附加的索引表来标识结点的地址索引项的一般形式是 `<关键字，地址>`。关键字标识唯一一个结点，地址作为指向结点的指针。

#### 散列存储方法

散列存储方法的基本思想是根据结点的关键字通过散列函数直接计算出该结点的存储地址。这种存储方法本质上是顺序存储方法的扩展。

### 判断数据结构类型

判断是否与数据的存储结构无关，只需要看这种结构到底有没有具体到使用顺序存储还是链式存储，如果已经具体到了那就一定和数据的存储结构有关。例如，栈并没有说明是用顺序栈还是用链栈来实现，所以是逻辑结构。线索树很明显是要用链式存储来实现，故与数据的存储结构有关，以此类推。