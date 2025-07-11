#ifndef SORT_TEST
#define SORT_TEST

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#define SMALL_DATA 5000
#define BIG_DATA 10'000'000


__attribute__((constructor))
void __init() {
    cout << "init rand" << endl;
    srand(time(0));
}

bool check(int *arr, int l, int r) {
    // for (int i = l; i < r - 1; i++) {
    //     if (arr[i] > arr[i + 1]) return false;
    // }
    for (int i = l + 1; i < r; i++) { //$ 可读性更高且符合标准库写法
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}


int *getRandData(int n) {
    // int *arr = (int *)malloc(sizeof(int) * n);
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

#define TEST(func, arr, n) { \
    cout << "TEST : " << #func; \
    int *temp = new int[n]; \
    memcpy(temp, arr, sizeof(int) * n); \
    long long b = clock(); \
    func(temp, 0, n); \
    long long e = clock(); \
    if (check(temp, 0, n)) { \
        cout << " is OK !" << endl; \
    } else { \
        cout << "is Failed !" << endl; \
    } \
    cout << n << "items sort " <<  "cost : " << (e - b) * 1000 / CLOCKS_PER_SEC << "ms" << endl; \
}

#endif