/*************************************************************************
    > File Name: solve.cpp
    > Author: huguang
    > Mail: hug@haizeix.com
    > Created Time: 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef struct Node {
    int data;
    struct Node *link;
} Node;

struct Node *getNewNode(int x) {
    struct Node *p = (struct Node *)malloc(sizeof(struct Node));
    p->data = x;
    p->link = NULL;
    return p;
}

int find_last_k(struct Node *head, int k) {
    Node *p = head, *q = head;
    int count = 0;
    while (p && count < k) {
        p = p->link;
        count++;
    }
    if (count < k) return 0;
    while (p) {
        p = p->link;
        q = q->link;
    }
    cout << q->data << endl;
    return 1;
}

int main() {
    int n, x, k;
    scanf("%d", &n);
    struct Node head, *tail = &head;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        tail->link = getNewNode(x);
        tail = tail->link;
    }
    scanf("%d", &k);
    printf("find last k : %d\n", find_last_k(head.link, k));
    return 0;
}