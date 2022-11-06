#include <iostream>

void swap(int array[], int i, int j) {
  if (i != j) {
    array[j] = array[j] ^ array[i];
    array[i] = array[j] ^ array[i];
    array[j] = array[j] ^ array[i];
  }
}

void reverse_array(int array[], int begin, int end) {
  while (begin < end) {
    swap(array, begin++, end--);
  }
}

void spin(int array[], int n, int m) {
  int l = n - m;
  reverse_array(array, 0, l - 1);
  reverse_array(array, l, n - 1);
  reverse_array(array, 0, n - 1);
}
