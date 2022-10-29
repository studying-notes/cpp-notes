#include <stdio.h>

int partition(int A[], int p, int r);

void quick_sort(int A[], int p, int r);

void tail_recursive_quick_sort(int A[], int p, int r);


void main() {
    int A[10] = {13, 18, 87, 73, 95, 31, 96, 82, 49, 30};
    int i;
    quick_sort(A, 0, 9);
//    partition(A, 0, 9);
    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);

    printf("\n");

    int B[10] = {13, 18, 87, 73, 95, 31, 96, 82, 49, 30};
    tail_recursive_quick_sort(B, 0, 9);
    for (i = 0; i < 10; i++)
        printf("%d ", B[i]);
}

int partition(int A[], int p, int r) {
    int x, i, j, temp;
    x = A[r];
    i = p;
    for (j = p; j < r; j++) {
        if (A[j] <= x) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
        }
    }
    temp = A[i];
    A[i] = A[r];
    A[r] = temp;
    return i;
}

void quick_sort(int A[], int p, int r) {
    int q;
    if (p < r) {
        q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

void tail_recursive_quick_sort(int A[], int p, int r) {
    int q;
    while (p < r) {
        q = partition(A, p, r);
        tail_recursive_quick_sort(A, p, q - 1);
        p = q + 1;
    }
}