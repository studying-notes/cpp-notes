#include <stdio.h>

int minimum(int A[], int l);

void main() {
    int A[10] = {13, 18, 87, 73, 95, 31, 96, 82, 49, 30};
    int min;
    min = minimum(A, 10);
    printf("%d", min);
}

int minimum(int A[], int l) {
    int minimum, i;
    minimum = A[0];
    for (i = 1; i < l; i++) {
        if (minimum > A[i]) {
            minimum = A[i];
        }
    }
    return minimum;
}
