#include <stdio.h>

int *bubble_sort(int x[], const int len);


void main() {
    int i;
    int *p;
    int A[10] = {6, 66, 29, 31, 55, 72, 34, 75, 22, 18};
    p = bubble_sort(A, 10);
    for (i = 0; i < 10; i++)
        printf("%d ", p[i]);
}

int *bubble_sort(int x[], const int len) {
    int i, j, temp;
    for (i = 0; i < len; i++) {
        for (j = len - 1; j > i; j--) {
            if (x[j] < x[j - 1]) {
                temp = x[j];
                x[j] = x[j - 1];
                x[j - 1] = temp;
            }
        }
    }
    return x;
}
