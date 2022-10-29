#include <stdio.h>

void counting_sort(int A[], int k, int n);

void main() {
    int A[8] = {2, 5, 3, 0, 2, 3, 0, 3};
    int k = 5;
    int n = 8;
    counting_sort(A, k, n);
}

void counting_sort(int A[], int k, int n) {
    int B[n];
    int C[k + 1];
    int j, i;
    for (i = 0; i < k + 1; i++) {
        C[i] = 0;
    }
    for (j = 0; j < n; j++) {
        C[A[j]] += 1;
    }
    for (i = 1; i < k + 1; i++) {
        C[i] += C[i - 1];
    }
    for (j = n - 1; j > -1; j--) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]] -= 1;
    }
    for (i = 0; i < n; i++)
        printf("%d ", B[i]);
}
