---
date: 2022-03-05T22:28:16+08:00
author: "Rustle Karl"

title: "Makefile 详解"
url:  "posts/cpp/quickstart/Makefile"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 调试

### 只打印命令而不执行

```shell
make -n
```

```shell
make --just-print
```

### 只执行不打印命令

```shell
make -s
```

```shell
make --slient
```
