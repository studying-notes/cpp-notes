---
date: 2022-02-06T08:06:32+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "getopt 解析命令行参数"  # 文章标题
# description: "文章描述"
url:  "posts/cpp/libraries/standard/getopt"  # 设置网页永久链接
tags: [ "cpp", "c", "标准库"]  # 标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 排序优先级
chapter: false  # 设置为章节

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

C 提供了两个函数可以用来解析命令行参数：getopt、getopt_long。

getopt 可以解析短参数，短参数就是指选项前只有一个 “-”，而 getopt_long 则支持短参数跟长参数。

## getopt函数

### 函数定义

```cpp
#include<unistd.h>
int getopt(int argc,char * const argv[],const char *optstring);

extern char *optarg;   //当前选项参数字串
extern int optind;     //argv 的当前索引值
```

### 函数参数

- argc: 通常为 main 函数中的 argc
- argv: 通常为 main 函数中的 argv
- optstring: 用来指定选项的内容，它由多个部分组成，表示的意义分别为：
  - 单个字符，表示选项。
  - 单个字符后接一个冒号：表示该选项后必须跟一个参数。参数紧跟在选项后或者以空格隔开。该参数的指针赋给 optarg。
  - 单个字符后跟两个冒号，表示该选项后可以跟一个参数，也可以不跟。如果跟一个参数，参数必须紧跟在选项后不能以空格隔开。该参数的指针赋给 optarg。

### 函数返回值

调用该函数将返回解析到的当前选项，该选项的参数将赋给 optarg，如果该选项没有参数，则 optarg 为 NULL。

### 函数实例

```cpp
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int opt=0;
    int a=0;
    int b=0;
    char s[50];

    while((opt=getopt(argc,argv,"ab:"))!=-1)
    {
        switch(opt)
        {
            case 'a':a=1;break;
            case 'b':b=1;strcpy(s,optarg);break; 
        }
    }

    if(a)
        printf("option a\n");
    if(b)
        printf("option b:%s\n",s);

    return 0;
}
```

```shell
./main -a
```

## getopt_long函数

与 getopt 不同的是，getopt_long 还支持长参数。

### 函数定义

```cpp
#include <getopt.h>
int getopt_long(int argc, char * const argv[],const char *optstring,const struct option *longopts, int *longindex);
```

### 函数参数及返回值

前面三个参数跟 getopt 函数一样，解析到短参数时返回值跟 getopt 一样，而长参数的解析则与 longopts 参数相关，该参数使用如下的结构：

```cpp
struct option {
    //长选项名
    const char *name;
    /*
    　　表示参数的个数
    　　no_argument(或者0)，表示该选项后面不跟参数值
    　　required_argument(或者1)，表示该选项后面一定跟一个参数
    　　optional_argument(或者2)，表示该选项后面的参数可选
    */
    int has_arg;
    int *flag;  //如果 flag 为 NULL，则函数会返回下面 val 参数的值；否则返回 0，并将 val 的值赋予 flag 所指向的内存
    int val;     //配合 flag 来决定返回值
};
```

参数 longindex，表示当前长参数在 longopts 中的索引值，如果不需要可以置为 NULL。

### 函数实例

```cpp
#include <stdio.h>
#include <string.h>
#include <getopt.h>

int learn=0;
static const struct option long_option[]={
   {"name",required_argument,NULL,'n'},
   {"learn",no_argument,&learn,1},
   {NULL,0,NULL,0}
};

int main(int argc,char *argv[])
{
    int opt=0;

    while((opt=getopt_long(argc,argv,"n:l",long_option,NULL))!=-1)
    {
        switch(opt)
        {
            case 0:break;
            case 'n':printf("name:%s ",optarg);                             
        }
    }

    if(learn)
        printf("learning\n");
}
```

```shell
./main --name Who --l
```
