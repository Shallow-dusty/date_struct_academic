#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50

typedef struct Node {
    char data;
    struct Node *next;
} Node;

Node *getNewNode(char val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}

int getLength(Node *str) {
    Node *p = str->next;
    int len = 0;
    while (p) {
        len++;
        p = p->next;    
    }
    return len;
}

char solve(Node *str1, Node *str2) {
    int len1 = getLength(str1);
    int len2 = getLength(str2);
    // int diff = (len1 - len2) ? len1 > len2 : (len2 - len1);
    int diff = 0;
    Node *short_w = nullptr, *long_w = nullptr;
    if (len1 > len2) {
        short_w = str2, long_w = str1;
        diff = len1 - len2;
    } else {
        short_w = str1, long_w = str2;
        diff = len2 - len1;
    }
    Node *p = long_w->next, *q = short_w->next;
    while (diff--) p = p->next;
    while (p != q) {
        p = p->next;
        q = q->next;
    }
    return p->data;
}

void build_list(char *str1, char *str2, Node **arr) {
    int n = 0;
    for (int i = strlen(str1) - 1, j = strlen(str2) - 1; i >= 0 && j >= 0; i--, j--) {
        if (str1[i] != str2[j]) break;
        n++;
    }
    Node ret1, ret2, *p;
    ret1.next = NULL, ret2.next = NULL;
    for (int i = strlen(str1) - 1; i >= 0 && n; i--, n--) {
        p = getNewNode(str1[i]);
        p->next = ret1.next;
        ret1.next = p;
    }
    ret2.next = ret1.next;
    for (int i = strlen(str1) - n - 1; i >= 0; i--) {
        p = getNewNode(str1[i]);
        p->next = ret1.next;
        ret1.next = p;
    }
    for (int i = strlen(str2) - n - 1; i >= 0; i--) {
        p = getNewNode(str2[i]);
        p->next = ret2.next;
        ret2.next = p;
    }
    arr[0] = ret1.next;
    arr[1] = ret2.next;
    return ;
}

int main() {
    char str1[MAX_N] = {0}, str2[MAX_N] = {0};
    scanf("%s%s", str1, str2);
    Node *arr[2] = {0};
    build_list(str1, str2, arr);
    printf("%c\n", solve(arr[0], arr[1]));
    return 0;
}