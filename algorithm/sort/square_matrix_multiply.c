#include <stdio.h>

void square_matrix_multiply(int A[4][4], int B[4][4]);


void main() {
    int A[4][4] = {{1,  2,  3,  4},
                   {4,  5,  6,  7},
                   {7,  8,  9,  10},
                   {11, 12, 13, 14}};
    int B[4][4] = {{1,  2,  3,  4},
                   {4,  5,  6,  7},
                   {7,  8,  9,  10},
                   {11, 12, 13, 14}};
    square_matrix_multiply(A, B);
}

void square_matrix_multiply(int A[4][4], int B[4][4]) {
    static int C[4][4];
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            C[i][j] = 0;
            for (k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            printf("%d\t", C[i][j]);
        }
        printf("%d\n");
    }
}
