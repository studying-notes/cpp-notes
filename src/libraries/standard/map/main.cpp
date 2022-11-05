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
