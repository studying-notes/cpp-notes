---
date: 2022-11-05T10:39:02+08:00  # 创建日期
author: "Rustle Karl"  # 作者

title: "map 键值对容器"  # 文章标题
url:  "posts/cpp/libraries/standard/map"  # 设置网页永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 基本用法

```c++
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  map<int, string> kv;

  // 插入
  // 用数组方式插入数据
  kv[1] = "A";
  // 用pair方式插入数据
  kv.insert(pair<int, string>(2, "B"));
  // 用value_type方式插入数据
  kv.insert(map<int, string>::value_type(3, "C"));

  // 取出
  // 用数组方式取出数据
  string a = kv[1];
  cout << a << endl;
  // 用迭代器方式取出数据
  auto item1 = kv.find(2);
  if (item1 != kv.end()) {
    cout << item1->second << endl;
  }

  // 遍历
  for (auto &i : kv) {
    cout << i.first << " " << i.second << endl;
  }

  // 删除
  // 通过关键词删除
  kv.erase(1);
  // 通过一个条目对象删除
  auto item2 = kv.find(2);
  if (item2 != kv.end()) {
    kv.erase(item2);
  }

  return 0;
}
```

## 基本操作函数

- begin() 返回指向 map 头部的迭代器

- clear(） 删除所有元素

- count() 返回指定元素出现的次数

- empty() 如果 map 为空则返回 true

- end() 返回指向 map 末尾的迭代器

- equal_range() 返回特殊条目的迭代器对

- erase() 删除一个元素

- find() 查找一个元素

- get_allocator() 返回 map 的配置器

- insert() 插入元素

- key_comp() 返回比较元素 key 的函数

- lower_bound() 返回键值 > =给定元素的第一个位置

- max_size() 返回可以容纳的最大元素个数

- rbegin() 返回一个指向 map 尾部的逆向迭代器

- rend() 返回一个指向 map 头部的逆向迭代器

- size() 返回 map 中元素的个数

- swap() 交换两个 map

- upper_bound() 返回键值 > 给定元素的第一个位置

- value_comp() 返回比较元素 value 的函数
