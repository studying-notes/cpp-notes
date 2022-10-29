#include <stdio.h>

void selection_sort();

void selection_sort_solu();

void main() {
//    selection_sort();
    selection_sort_solu();
}

void selection_sort() {
    int i, j;
    int A[10] = {14, 81, 87, 40, 41, 84, 48, 59, 24, 76};

    for (i = 0; i < 10; i++) {
        for (j = 1; j < 10 - i; j++) {
            if (A[i] > A[i + j]) {
                A[i] = A[i + j] + A[i];
                A[i + j] = A[i] - A[i + j];
                A[i] = A[i] - A[i + j];
            }
        }
    }
    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);
}

void selection_sort_solu() {
    int i, j, n = 10, smallest, temp;
    int A[10] = {14, 81, 87, 40, 41, 84, 48, 59, 24, 76};

    for (i = 0; i < n - 1; i++) {
        smallest = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] < A[smallest])
                smallest = j;
        }
        temp = A[smallest];
        A[smallest] = A[i];
        A[i] = temp;
    }
    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);
}
