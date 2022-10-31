#include <cstdlib>
#include <stdio.h>

void print_array(const int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[length - 1]);
}

void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] = array[j] + array[i];
    array[i] = array[j] - array[i];
    array[j] = array[j] - array[i];
  }
}

int partition(int array[], int start, int end) {
  // start, end 都可以取到
  int pivot = array[start];
  while (start < end) {
    while (start < end && array[start] < pivot)
      start++;
    while (start < end && array[end] > pivot)
      end--;
    swap(array, start, end);
  }
  array[start] = pivot;
  return start;
}

void quick_sort(int array[], int start, int end) {
  // start, end 都可以取到
  if (start < end) {
    int mid = partition(array, start, end);
    quick_sort(array, start, mid);
    quick_sort(array, mid + 1, end);
  }
}

int main() {
  //  int array[] = {38, 65, 97, 76, 13, 27, 49};
  int array[] = {1, 3, 5, 2, 4, 6, 7, 8};
  int length = sizeof(array) / sizeof(array[0]);
  print_array(array, length);
  quick_sort(array, 0, length);
  print_array(array, length);
  return 0;
}
