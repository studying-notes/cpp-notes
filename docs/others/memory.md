---
date: 2020-10-09T12:48:02+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "C 语言内存管理"  # 文章标题
url:  "posts/cpp/docs/others/memory"  # 设置网页链接，默认使用文件名
tags: [ "cpp", "c" ]  # 自定义标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 文章在章节中的排序优先级，正序排序
chapter: false  # 将页面设置为章节

index: true  # 文章是否可以被索引
draft: false  # 草稿
toc: true  # 是否自动生成目录
---

## 堆上内存管理函数

栈只能用来保存临时变量、局部变量和函数参数。在函数返回时，自动释放所占用的存储空间。而堆上的内存空间不会自动释放，直到调用 free() 函数，才会释放堆上的存储空间。

### malloc()

- 头文件：stdlib.h
- 声明：void * malloc(int n);
- 含义：在堆上，分配 n 个字节，并返回 void 指针类型
- 返回值：分配内存成功，返回分配的堆上存储空间的首地址；否则，返回 NULL

### calloc()

- 头文件：stdlib.h
- 声明：void *calloc(int n, int size);
- 含义：在堆上，分配 n * size 个字节，并初始化为 0，返回 void * 类型
- 返回值：同 malloc() 函数

### recalloc()

- 头文件：stdlib.h
- 声明：void * realloc(void * p,int n);
- 含义：重新分配堆上的 void 指针 p 所指的空间为 n 个字节，同时会复制原有内容到新分配的堆上存储空间。注意，若原来的 void 指针 p 在堆上的空间不大于 n 个字节，则保持不变
- 返回值：同 malloc() 函数

### free()

- 头文件：stdlib.h
- 声明：void  free (void * p);
- 含义：释放 void 指针 p 所指的堆上的空间
- 返回值：无

### memset()

- 头文件：string.h
- 声明：void * memset (void * p, int c, int n);
- 含义：对于 void 指针 p 为首地址的 n 个字节，将其中的每个字节设置为 c
- 返回值：返回指向存储区域 p 的 void 类型指针

```c
int* p = (int *) malloc(sizeof(int)*128);
```

分配 128 个整型存储单元，并将这 128 个连续的整型存储单元的首地址存储到指针变量 p 中。


```c
if (NULL == (p = (type *) malloc(sizeof (type)))) 
```

判断是否正确分配内存。

## 常见错误

### 值传递错误

```c
void getMemory(char *p) {
    p = (char *) malloc(100);
}

int main() {
    char *str = NULL;
    getMemory(str);
    strcpy(str, "error");
    printf("%s", str);
    return 0;
}
```

### 双重指针

```c
void getMemory(char **p) {
    *p = (char *) malloc(100);
}

int main() {
    char *str = NULL;
    getMemory(&str);
    strcpy(str, "error");
    printf("%s", str);
    free(str);
    return 0;
}
```

### 局部变量错误

```c
char *getMemory() {
    char p[] = "error";
    return p;
}

int main() {
    char *str = NULL;
    str = getMemory();
    printf("%s", str);
    return 0;
}
```

### 操作已释放内存指针错误

```c
int main() {
    char *str = (char *) malloc(100);
    strcpy(str, "hello");
    free(str);
    if (str != NULL) {
        strcpy(str, "world");
        printf("%s", str);
    }

    return 0;
}
```

### 通过指针相关字符常量错误

```c
void copy(char *s1, char *s2) {
    *s1 = *s2;
}

int main() {
    char *s1 = "ABC\n";
    char *s2 = "abc\n";
    copy(s1, s2);
    printf("%s", s1);
    return 0;
}
```
