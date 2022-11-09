#include <cstdio>
#include <memory.h>

#define len(array) (sizeof(array) / sizeof(array[0]))

void print_array(const int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[length - 1]);
}

void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] += array[i];
    array[i] = array[j] - array[i];
    array[j] -= array[i];
  }
}

int min(int a, int b) {
  return a < b ? a : b;
}

int main() {
  const int m = 3, n = 3;
  int array[m][n] = {
      {1, 4, 3},
      {8, 7, 5},
      {2, 1, 5},
  };// 17

  // 记录距离
  int dist[m + 1][n + 1];
  memset(dist, 0, (m + 1) * (n + 1) * sizeof(int));

  // 处理边界情况
  for (int i = 1; i < m; i++) {
    dist[i + 1][0] = dist[i][0] + array[i][0];
  }
  for (int i = 1; i < n; i++) {
    dist[0][i + 1] = dist[0][i] + array[0][i];
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      // 最短的路径一定是之前最短路径加上当前路径
      dist[i + 1][j + 1] = min(dist[i + 1][j], dist[i][j + 1]) + array[i][j];
    }
  }

  // 打印二维数组
  int x = m + 1, y = n + 1;
  for (int i = 0; i < x * y; ++i) {
    printf("%d ", dist[i / y][i % y]);
    if ((i + 1) % y == 0)
      printf("\n");
  }
}
