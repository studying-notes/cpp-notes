#include <stdio.h>

void max_heapify(int A[], int i, int size);

void build_max_heap(int A[], int size);

void heap_sort(int A[], int size);


void main() {
    int A[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int size = 10;
    int i;
    build_max_heap(A, size);
    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);

    printf("\n");

    int B[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    heap_sort(B, size);
    for (i = 0; i < 10; i++)
        printf("%d ", *(B + i));
}

void max_heapify(int A[], int i, int size) {
    int l, r, largest, temp;
    l = 2 * i;
    r = 2 * i + 1;
    if (l <= size && A[l - 1] > A[i - 1]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r <= size && A[r - 1] > A[largest - 1]) {
        largest = r;
    }
    if (largest != i) {
        temp = A[i - 1];
        A[i - 1] = A[largest - 1];
        A[largest - 1] = temp;
        max_heapify(A, largest, size);
    }
}

void build_max_heap(int A[], int size) {
    int i;
    for (i = size / 2; i > 0; i--) {
        max_heapify(A, i, size);
    }
}

void heap_sort(int A[], int size) {
    int i, temp;
    build_max_heap(A, size);
    for (i = size - 1; i > 0; i--) {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        max_heapify(A, 1, i);
    }
}
