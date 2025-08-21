//@ 2010年42题
//@ 考察内容：顺序表
//@ 难度：中等（最优）  简单（暴力）
//@ 状态：暴力（完成）  最优（完成）


//@ 题目：数组偏移
#include <stdio.h>
void reserve_arr(int *arr, int l, int r) {
    for (int i = l, j = r - 1; i < j; i++, j--) {
        arr[i] ^= arr[j];
        arr[j] ^= arr[i];
        arr[i] ^= arr[j];
    }
    return ;
}

void rotate_array(int *nums, int n, int p) {
    reserve_arr(nums, 0, p);
    reserve_arr(nums, p, n);
    reserve_arr(nums, 0, n);
    return ;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int arr[n + 5];
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }
    rotate_array(arr, n, k);
    for (int i = 0; i < n; i++) {
        if (i != 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}