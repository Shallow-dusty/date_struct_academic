#include <stdio.h>
#define max_n 10000

int FindMidNum(int *a, int *b, int n) {
    int temp[2*n];
    int p = 0, q = 0, i = 0;
    while (p != n - 1 || q != n - 1) {
        if (p == n - 1) temp[i++] = a[p++];
        else if (q == n - 1) temp[i++] = b[q++];
        else if (a[p] < b[q]) temp[i++] = a[p++];
        else temp[i++] = b[q];
    }
    return temp[(2 * n - 1) / 2];
}


int main() {
    int n, arr1[max_n + 5] = {0}, arr2[max_n + 5] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", arr1 + i);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", arr2 + i);
    }
    printf("%d\n", FindMidNum(arr1, arr2, n));
    return 0;
}