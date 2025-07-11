#ifndef SORT_TEST_H
#define SORT_TEST_H
#include <cstring>
#include <ctime>
#include <cstdlib>
#define SMALL_DATA 5000
#define BIG_DATA 10'000'000
__attribute__((constructor)) //? GGG/Clang扩展标识该函数会再main前自动调用
void __init__Rand() {
    srand(time(0));
}

bool check(int *arr, int l, int r) {
    for (int i = l; i < r - 1; i++) {
        if (arr[i + 1] < arr[i]) return false;
    }
    return true;
}

int *getRandData(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);    
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

#define TEST(func, arr, n) { \
    cout << "TEST : " << #func; \
    int *temp = (int *)malloc(sizeof(int) * n); \
    memcpy(temp, arr, sizeof(int) * n); \
    long long b = clock(); \
    func(temp, 0, n); \
    long long e = clock(); \
    if (check(temp, 0, n)) { \
        cout << "\tOK!" << endl; \
    } else { \
        cout << "\tFailed" << endl; \
    } \
    cout << (e - b) * 1000 / CLOCKS_PER_SEC << endl; \
    free(temp); \
}



#endif