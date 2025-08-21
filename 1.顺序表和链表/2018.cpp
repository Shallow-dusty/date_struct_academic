//@ 2018年41题
//@ 考察内容：顺序表
//@ 难度：Easy
//@ 状态：已完成

//@ 题目：找未出现的最小整数
/*************************************************************************
    > File Name: solve.cpp
    > Author:
    > Mail:
    > Created Time:
 ************************************************************************/

#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int findMissMin(int arr[], int n) {
    int a[n] = {0};
    // for (int i = 0; i < n; i++) a[i] = i;
    a[0] = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0)
            a[arr[i]] = 1;
    }
    for (int i = 1; i < n; i++) {
        if (a[i] == 0) return i;
    }
    return -1;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }
    printf("%d\n", findMissMin(arr, n));
    free(arr);
    return 0;
}