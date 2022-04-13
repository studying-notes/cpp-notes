---
date: 2022-03-08T16:06:23+08:00
author: "Rustle Karl"

title: "vcpkg 管理 C 和 C++ 库"
url:  "posts/cpp/quickstart/compile/vcpkg"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 官方文档

https://github.com/microsoft/vcpkg/blob/master/README_zh_CN.md

## 基本用法

```shell
vcpkg install cryptopp
```

这种情况，一切都是默认。

### MinGW

https://github.com/microsoft/vcpkg/blob/master/docs/users/mingw.md#Using-Mingw-w64-natively-on-Windows

```shell
pacman -S --needed git base-devel mingw-w64-x86_64-toolchain
# All
```

```shell
source shell mingw64   # for x64, or "mingw32" for x86
source shell mingw32   # for x64, or "mingw32" for x86
```

```shell
export VCPKG_DEFAULT_TRIPLET=x64-mingw-dynamic
export VCPKG_DEFAULT_HOST_TRIPLET=x64-mingw-dynamic
```

```shell
export VCPKG_DEFAULT_TRIPLET=x86-mingw-dynamic
export VCPKG_DEFAULT_HOST_TRIPLET=x86-mingw-dynamic
```

```shell
vcpkg install cryptopp
```

```shell
vcpkg install cryptopp:x64-mingw-dynamic
```

```shell
vcpkg install cryptopp:x64-mingw-static
```

```shell
vcpkg install cryptopp:x86-mingw-dynamic
vcpkg install cryptopp --triplet=x86-mingw-dynamic
```

```shell
vcpkg install cryptopp:x86-mingw-static
```

这个无语，还是 64 位的，编译不出 32 位。不必再试了，根本编译不出 32 位的。其他库也编译不出 32 位的。

## 环境变量

### Cmd

```shell
set HTTPS_PROXY=http://localhost:8118
set HTTP_PROXY=http://localhost:8118
```

### Powershell

```shell
$Env:HTTPS_PROXY="http://localhost:8118"
$Env:HTTP_PROXY="http://localhost:8118"
```

vcpkg install boost
