---
date: 2022-02-21T00:07:56+08:00
author: "Rustle Karl"

title: "CMake 详解"
url:  "posts/cpp/quickstart/cmake"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

```shell
cmake --help
```

找到 Generators 章节，列出的即支持的平台。我们要编译到 visual studio 2019，即如下 cmd。

```shell
cmake -G "Visual Studio 16 2019" -D CMAKE_INSTALL_PREFIX=${your_install_path}
```
