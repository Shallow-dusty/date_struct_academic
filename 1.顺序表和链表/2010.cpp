#include <iostream>
using namespace std;


int *func(int a[], int p, int n) {
    int res[n];
    int i = 0;
    for (int j = p; j < n; j++) {
        res[i++] = a[j];
    }
    for (int j = 0; j < p; j++) {
        res[i++] = a[j];
    }
    return res;
}


int main() {
    const int n = 10;
    int a[n];
    for (int i = 0; i < n; i++) 
        a[i] = i;
    int p;
    cin >> p;
    func(a, p, n);
    
}