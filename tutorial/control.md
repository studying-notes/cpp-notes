---
date: 2020-10-25T15:10:50+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C++ 控制语句"  # 文章标题
# description: "文章描述"
url:  "posts/cpp/tutorial/control"  # 设置网页永久链接
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

## 转向语句

### break

无条件地结束 switch 语句或循环语句，包括 while、do_while 和 for 语句的执行，转向执行语句块的后续语句。

### continue

用于循环体中，终止当前一次循环，不执行 continue 的后续语句，而转向循环入口继续执行。

### return

用于返回表达式的值，把控制权返回调用点，中断函数的执行。

### goto

无条件转向语句，它与标号语句配合使用。

标号语句是指在任意语句（包括空语句）之前冠以“标号”和冒号指示的语句，表示 goto语句的转向入口。标号语句本身对程序的正常控制流程没有影响。

goto 语句和标号语句要求出现在同一个函数体中，即不能从一个函数转向执行另一个函数体中的语句。

在一个函数体内，可以有多个转向同一“标号”的 goto 语句，但不能有多个“标号”相同的语句。



