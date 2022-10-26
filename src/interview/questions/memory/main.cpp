#include <iostream>

int main() {
  int a[] = {1, 2, 3, 4, 5};
  int i;

  std::cout << &a[5] << std::endl;
  std::cout << &i << std::endl;

  for (i = 0; i <= 5; i++) {
    a[i] = 0;
  }

  return 0;
}
