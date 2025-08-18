/*************************************************************************
    > File Name: solve.cpp
    > Author:
    > Mail:
    > Created Time:
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct node{
    int data;
    struct node*next;
} Node;

Node *getNewNode(int x) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    return p;
}

void change_list(Node *h) {
    Node *p = h, *q = h;
    while (q && q->next) {
        p = p->next;
        q = q->next->next;
    }
    Node *head2 = p->next;
    p->next = nullptr;

    Node *pre = nullptr, *curr = head2;
       while (curr) {
        Node *temp = curr->next;
        curr->next = pre;
        pre = curr;
        curr = temp;
    }
    Node *temp2 = pre->next, *temp1 = h->next;
    Node *p1 = h, *p2 = pre;
    while (temp1 == nullptr || temp1->next == nullptr) {
        p1 = temp1->next;
        p2 = temp2->next;
        h->next = temp1;
        temp1->next = temp2;
        temp2 = p1->next;
        temp2 = p2->next; 
    }
    
}

int main() {
    int n, x;
    scanf("%d", &n);
    Node head, *tail = &head;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        tail->next = getNewNode(x);
        tail = tail->next;
    }
    change_list(&head);
    for (Node *p = head.next; p != NULL; p = p->next) {
        if (p != head.next) printf(" ");
        printf("%d", p->data);
    }
    printf("\n");
    return 0;
}
