#include <iostream>

int main() {
  const int M = 3;
  const int N = 4;

  int a[M][N];
  int b[M][N];

  // 行存储策略
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      a[i][j] = i + j;
    }
  }

  // 列存储策略
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < M; i++) {
      b[i][j] = a[i][j];
    }
  }

  return 0;
}
