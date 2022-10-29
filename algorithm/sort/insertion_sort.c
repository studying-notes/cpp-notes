#include <stdio.h>

void insertion_sort();

void insertion_sort_reverse();

void main() {
    insertion_sort();
    insertion_sort_reverse();
}

void insertion_sort() {
    int i, j, key;
    int A[10] = {14, 81, 87, 40, 41, 84, 48, 59, 24, 76};

//    int A[10];
//    for (i = 0; i < 10; i++)
//        scanf("%d", &A[i]);

    for (j = 1; j < 10; j++) {
        key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }

    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);
}

void insertion_sort_reverse() {
    int i, j, key;
    int A[10] = {14, 81, 87, 40, 41, 84, 48, 59, 24, 76};

//    int A[10];
//    for (i = 0; i < 10; i++)
//        scanf("%d", &A[i]);

    for (j = 1; j < 10; j++) {
        key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] < key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }

    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);
}