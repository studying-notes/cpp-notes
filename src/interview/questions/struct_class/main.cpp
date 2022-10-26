#include <iostream>

typedef union {
  double i;
  int k[5];
  char c;
} DATE;

typedef struct data {
  int cat;
  DATE cow;
  double dog;
} too;

int main() {
  DATE max;

  std::cout << "Size of DATE: " << sizeof(max) << std::endl;
  std::cout << "Size of too: " << sizeof(too) << std::endl;

  return 0;
}
