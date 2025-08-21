//@ 2010年42题
//@ 考察内容：顺序表
//@ 难度：中等（最优）  简单（暴力）
//@ 状态：暴力（完成）  最优（TODO）


//@ 题目：数组偏移
/*************************************************************************
        > File Name: 2010.数组偏移_暴力.cpp
        > Author: Shallow 
        > Mail: 1737951602@qq.com 
        > Created Time: Thu 21 Aug 2025 11:42:10 AM CST
 ************************************************************************/

#include <stdio.h>

void rotate_array(int *nums, int n, int p) {
    int temp[n];
    int i = 0;
    for (int j = p; j < n; j++) temp[i++] = nums[j];
    for (int j = 0; j < p; j++) temp[i++] = nums[j];
    for (int j = 0; j < n; j++) nums[j] = temp[j];
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


//! 注意：返回值不可为局部数组
// int *func(int a[], int p, int n) {
//     int res[n];
//     int i = 0;
//     for (int j = p; j < n; j++) {
//         res[i++] = a[j];
//     }
//     for (int j = 0; j < p; j++) {
//         res[i++] = a[j];
//     }
//     return res;
// }
