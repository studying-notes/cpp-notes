#include <stdio.h>
#include <limits.h>

int *find_max_crossing_subarray(int A[], int low, int mid, int high);

int *find_maximum_subarray(int A[], int low, int high);


void main() {
    int A[10] = {1, -2, 3, 4, 5, 5, 4, 3, -2, 1};
    int i;
    int *p;
//    p = find_max_crossing_subarray(A, 0, 4, 9);
    p = find_maximum_subarray(A, 0, 9);
//    for (i = 0; i < 3; i++)
//        printf("%d ", p[i]);
    for (i = p[0]; i <= p[1]; i++)
        printf("%d ", A[i]);
}

int *find_max_crossing_subarray(int A[], int low, int mid, int high) {
    int sum, left_sum = INT_MIN, right_sum = INT_MIN, i, max_left, max_right;
    static int R[3];
    sum = 0;
    for (i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    sum = 0;
    for (i = mid + 1; i <= high; i++) {
        sum += A[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }
    R[0] = max_left;
    R[1] = max_right;
    R[2] = left_sum + right_sum;
    return R;
}

int *find_maximum_subarray(int A[], int low, int high) {
    int mid, left_low, left_high, left_sum, right_low, right_high, right_sum, cross_low, cross_high, cross_sum;
    int *p;
    static int R[3];
    if (high == low) {
        R[0] = low;
        R[1] = high;
        R[2] = A[low];
        return R;
    } else {
        mid = (low + high) / 2;

        p = find_maximum_subarray(A, low, mid);
        left_low = p[0];
        left_high = p[1];
        left_sum = p[2];
//        printf("%d %d %d\n", A[left_low], A[left_high], left_sum);

        p = find_maximum_subarray(A, mid + 1, high);
        right_low = p[0];
        right_high = p[1];
        right_sum = p[2];
//        printf("%d %d %d\n", A[right_low], A[right_high], right_sum);

        p = find_max_crossing_subarray(A, low, mid, high);
        cross_low = p[0];
        cross_high = p[1];
        cross_sum = p[2];
//        printf("%d %d %d\n", A[cross_low], A[cross_high], cross_sum);

        if (left_sum >= right_sum && left_sum >= cross_sum) {
            R[0] = left_low;
            R[1] = left_high;
            R[2] = left_sum;
            return R;
        } else if (right_sum >= left_sum && right_sum >= cross_sum) {
            R[0] = right_low;
            R[1] = right_high;
            R[2] = right_sum;
            return R;
        } else {
            R[0] = cross_low;
            R[1] = cross_high;
            R[2] = cross_sum;
            return R;
        }
    }
}
