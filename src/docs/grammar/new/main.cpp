#include <iostream>
#include <malloc.h>

class Object {
private:
  int member;

public:
  Object() {
    member = 10;
  }

  void Print() {
    std::cout << "member is " << member << std::endl;
  }
};

int main() {
  auto *a = (int *) malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    std::cout << a[i] << ", ";
  }

  std::cout << std::endl;

  auto *b = new int[10];
  for (int i = 0; i < 10; i++) {
    std::cout << b[i] << ", ";
  }

  return 0;
}
