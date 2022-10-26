#include <cstring>
#include <iostream>

#define TRACE(S) (printf("%s\n", #S), S)

int main() {
  int a = 5;
  int b = TRACE(a);

  const char *c = "Hello";
  char d[50];
  strcpy(d, TRACE(c));

  std::cout << d << std::endl;

  return 0;
}
