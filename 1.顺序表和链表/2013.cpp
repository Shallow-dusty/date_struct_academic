#include <stdio.h>
#define MAX_N 10000

int main_element(int *arr, int n) {
    int cand = 0, count = 0;
    for (int i = 0; i < n; i++) {
        if (count == 0) {
            cand = arr[i]; 
            count = 1;
        }
        else {
            if (arr[i] == cand) count++;
            else count--;
        }
   } 
   count = 0;
   for (int i = 0; i < n; i++) if(arr[i] == cand) count++;
   if (count > n / 2) return cand;
   return -1;
}

int main() {
    int n, arr[MAX_N + 5] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }
    printf("%d\n", main_element(arr, n));
    return 0;
}