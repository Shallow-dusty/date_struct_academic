/*************************************************************************
    > File Name: solve.cpp
    > Author:
    > Mail:
    > Created Time:
 ************************************************************************/
#include <iostream>
#include <cstdlib>
#include <queue>
#include <climits>
using namespace std;

int min_num(int a, int b, int c) {
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    return a;
    int min_dis = INT_MAX;
int func(queue<int> que1, queue<int> que2, queue<int> que3) ;
    int i = 0, j = 0, k = 0, op;
    i = que1.pop();
    j 
    int temp = find_dis(que1[1], que2[2], k);
    if (temp < min_dis) min_dis = temp;
    op = find_mind(a, b, c, i, j, k);
    if (op == 1) i++;
    if (op == 2) j++;
    if (op == 3) k++;
}

int main() {
    int m, n, k, x;
    queue<int> que1, que2, que3;
    cin >> m >> n >> k;
    for (int i = 0; i < m; i++) {
        cin >> x;
        que1.push(x);
    }
    for (int i = 0; i < n; i++) {
        cin >> x;
        que2.push(x);
    }
    for (int i = 0; i < k; i++) {
        cin >> x;
        que3.push(x);
    }
    cout << func(que1, que2, que3) << endl;
    return 0;
}