---
date: 2022-02-18T21:06:59+08:00
author: "Rustle Karl"

title: "C++ 判断文件是否存在的几种方法"
url:  "posts/cpp/examples/fs/exists"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

一般而言，下述方法都可以检查文件是否存在：

- 使用 ifstream 打开文件流，成功则存在，失败则不存在
- 以 fopen 读方式打开文件，成功则存在，否则不存在
- 使用 access 函数获取文件状态，成功则存在，否则不存在
- 使用 stat 函数获取文件状态，成功则存在，否则不存在

```c++
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

inline bool exists_test0 (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

inline bool exists_test2 (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

inline bool exists_test3 (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
```

stat() 函数的方式性能最好。
