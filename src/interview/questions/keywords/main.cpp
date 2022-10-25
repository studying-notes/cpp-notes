#include <cstring>
#include <iostream>

class String {
public:
  String(const char *str = NULL);        // 普通构造函数
  String(const String &other);           // 拷贝构造函数
  ~String(void);                         // 析构函数
  String &operator=(const String &other);// 赋值函数
  friend std::ostream &operator<<(std::ostream &os, const String &str);

private:
  char *m_data;// 用于保存字符串
};

String::String(const char *str) {
  if (str == NULL) {
    m_data = new char[1];
    *m_data = '\0';
  } else {
    int length = strlen(str);
    m_data = new char[length + 1];
    strcpy(m_data, str);
  }
}

String::String(const String &other) {
  int length = strlen(other.m_data);
  m_data = new char[length + 1];
  strcpy(m_data, other.m_data);
}

String::~String(void) { delete[] m_data; }

String &String::operator=(const String &other) {
  if (this == &other)
    return *this;
  delete[] m_data;
  int length = strlen(other.m_data);
  m_data = new char[length + 1];
  strcpy(m_data, other.m_data);
  return *this;
}

std::ostream &operator<<(std::ostream &os, const String &str) {
  os << str.m_data;
  return os;
}

int main() {
  String a("abcdefg");
  std::cout << a << std::endl;
  String b(a);
  std::cout << b << std::endl;
  String c = b;
  std::cout << c << std::endl;

  return 0;
}
