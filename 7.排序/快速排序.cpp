#include <iostream>
#include <algorithm>
#include "sort_test.h"
using namespace std;


void quick_sort(int *arr, int l, int r) {
    if (r - l < 2){
        if (r - l == 1) return ;
        if (arr[l] > arr[l + 1]) swap(l, l + 1);
    }
    
    return ;
}




int main() {
    return 0;
}