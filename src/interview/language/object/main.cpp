#include <iostream>

class Base {
public:
  Base() {
    std::cout << "Base constructor" << std::endl;
    foo();
  }
  virtual ~Base() { std::cout << "Base destructor" << std::endl; }
  virtual void foo() { std::cout << "Base::foo()" << std::endl; }
};

class Derived : public Base {
public:
  Derived() { std::cout << "Derived constructor" << std::endl; }
  ~Derived() { std::cout << "Derived destructor" << std::endl; }
  void foo() { std::cout << "Derived::foo()" << std::endl; }
};

int main() {
  Base *b = new Derived();
  b->foo();
  delete b;
  return 0;
}
