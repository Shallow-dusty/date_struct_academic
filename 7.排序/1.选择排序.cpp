#include <iostream>
#include "sort_test.h"
using namespace std;
void select_sort(int *arr, int l, int r) {
    for (int i = l; i < r - 1; i++) { // 扫描所有填充位置，最后一个自动完成
        int ind = i; //代表当前的填充位置
        for (int j = i + 1; j < r; j++) { //找最小值
            if (arr[ind] > arr[j]) 
                ind = j;
        }
        swap(arr[i], arr[ind]);
    }
    return ;
}




int main() {
    int *arr = getRandData(SMALL_DATA);
    TEST(select_sort, arr, SMALL_DATA);
    delete(arr);
    return 0;
}