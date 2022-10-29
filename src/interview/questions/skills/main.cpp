#include <cstdio>

int main();

void run() {
  printf("run\n");
  main();
}

int main() {
  printf("main\n");
  run();
}
