#include <stdio.h>
#include <stdlib.h>

#define max_n 10000

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}

void output(Node *head) {
    for (Node *p = head; p; p = p->next) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
    return ;
}
int flag[max_n];
void delete_once(Node *head, int pos) {
    Node * p = head->next, *q = NULL;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    q = p->next;
    p->next = q->next;
    free(q);
}


void delete_node(Node *head) {
    Node *p = head->next;
    int pos = 0;
    while (p) {
        if (flag[abs(p->data)]) {
            delete_once(head->next, pos);
            pos--;
        }
        else flag[abs(p->data)] = 1;
        p = p->next;
        pos++;
    }
}

int main() {
    Node head, *tail = &head;
    head.next = NULL;
    int m, arr[max_n + 5] = {0};
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", arr + i);
        tail->next = getNewNode(arr[i]);
        tail = tail->next;
    }
    delete_node(head.next);
    output(head.next);
    return 0;
}