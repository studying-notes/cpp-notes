#include <iostream>

int main() {
  char c = 1;
  int i = 2;
  long l = 3;
  unsigned long ul = 4;
  auto r = c + i + l + ul;
  std::cout << std::boolalpha << (typeid(ul) == typeid(unsigned long)) << std::endl;
  return 0;
}
