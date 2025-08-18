/*************************************************************************
    > File Name: solve.cpp
    > Author:
    > Mail:
    > Created Time:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
void swap(int a, int b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

    
void quick_sort(int *arr, int l, int r) {
    if (r - l < 2){
        if (r - l == 0) return ;
        if (arr[l] > arr[l + 1]) swap(arr[l], arr[l + 1]);
        return ;
    }
    int x = l, y = r - 1, z = arr[l];
    while (x < y) {
        while (x < y && arr[y] >= z) --y;
        if (x < y) arr[x++] = arr[y];
        while (x < y && arr[x] <= z) ++x;
        if (x < y) arr[y--] = arr[x];
    }
    arr[x] = z;
    quick_sort(arr, l, x);
    quick_sort(arr, x + 1, r);
    return ;
}


int setPartition(int a[], int n) {
    quick_sort(a, 0, n);
    int sum1 = 0, sum2 = 0;
    for (int i = 0, j = n / 2; i < j, j < n; i++, j++) {
        sum1 += a[i];
        sum2 += a[j];
    }
    return abs(sum1 - sum2);
}

int main(){
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * (n));
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }
    printf("%d\n", setPartition(arr, n));
    return 0;
}