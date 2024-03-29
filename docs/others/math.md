---
date: 2020-10-25T13:04:47+08:00  # 创建日期
author: "Rustle Karl"  # 作者
markup: mmark

# 文章
title: "用 CPP 进行数学计算"  # 文章标题
url:  "posts/cpp/docs/others/math"  # 设置网页永久链接
tags: [ "cpp" ]  # 自定义标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 排序优先级
chapter: false  # 设置为章节

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

## 嵌套分数

$$
\frac 1{1+\frac 1{1+\frac 1{x+y}}}
$$

```c++
#include <iostream>

using namespace std;

int main() {
    double x = 10, y = 20, result;
    result = 1 / (1 + 1 / (1 + 1 / (x + y)));
    cout << result;
}
```

## 对数、绝对值和指数

$$
\ln (1 + {\left | \frac{a+b}{a-b} \right |}^{10})
$$

```c++
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a = 10, b = 20, result;
    result = log(1 + pow(fabs((a + b) / (a - b)), 10));
    cout << result;
}
```

$$
\lg(a^2+ab+b^2)
$$

```c++
log10(a * a + a * b + b * b);
```

## 开平方与三角函数

$$
\sqrt{1+\frac{\pi}2 \cos48^{\circ} }
$$

```c++
sqrt(1 + 3.14159 / 2 * cos(48 * 3.14159 / 180));
```

$$
\cot(\frac{1-x^2}{1+x^2})
$$

```c++
1 / tan((1 - x * x) / (1 + x * x));
```






```c++

```


```c++

```

```c++

```


```c++

```

```c++

```


```c++

```

```c++

```


```c++

```




