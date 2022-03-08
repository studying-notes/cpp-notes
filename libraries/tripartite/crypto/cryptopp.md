---
date: 2022-03-08T22:56:22+08:00
author: "Rustle Karl"

title: "Crypto++ 的编译与基本用法"
url:  "posts/cpp/libraries/tripartite/crypto/cryptopp"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 编译

### 下载源码

```shell
git clone https://github.com/weidai11/cryptopp.git
```

```shell
cd cryptopp
```

```shell
wget -O CMakeLists.txt https://raw.githubusercontent.com/noloader/cryptopp-cmake/master/CMakeLists.txt
```

```shell
wget -O cryptopp-config.cmake https://raw.githubusercontent.com/noloader/cryptopp-cmake/master/cryptopp-config.cmake
```

### 编译源码

#### CMake 方式

https://www.cryptopp.com/wiki/CMake

```shell
make cmake-build-release && cd cmake-build-release
```

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DDISABLE_ASM=OFF  -G "Unix Makefiles" ..
```

```shell
cps c -o Makefile
# 添加特殊参数
make -f Makefile build
```

根据情况编译：

```shell
make
```

```shell
make cryptopp-static
```

```shell
make cryptopp-shared
```

## 二级

### 三级

```shell

```

```c++

```


## 二级

### 三级

```c++

```

```c++

```


## 二级

### 三级

```c++

```

```c++

```


## 二级

### 三级

```c++

```

```c++

```


## 二级

### 三级

```c++

```

```c++

```


