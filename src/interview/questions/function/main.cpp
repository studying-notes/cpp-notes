#include <iostream>

class A {
public:
  A() {
    A(10);
    Print();
  }
  A(int j) : i(j) {
    std::cout << "Call A(int j)" << std::endl;
  }
  void Print() {
    std::cout << "Call Print()" << std::endl;
  }
  int i;
};

int main() {
  A a;
  std::cout << a.i << std::endl;
  return 0;
}
