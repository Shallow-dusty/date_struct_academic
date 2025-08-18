#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
using namespace std;

#define MAX_N 100000

typedef struct Node {
    int weight;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->weight = val;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

Node *build_tree(char *str) {
    stack<Node *> s;
    Node *p = NULL, *temp;
    int num = 0, flag = 1;
    for (int i = 0; str[i]; i++) {
        switch (str[i]) {
            case '(': {
                    if (num != 0) {
                        temp = getNewNode(num);
                        if (!s.empty() && flag == 1) s.top()->lchild = temp;
                        else if (!s.empty() && flag == 2) s.top()->rchild = temp;
                        s.push(temp);
                    }
                    flag = 1, num = 0;
                } break;
            case ')': {
                    if (num != 0) {
                        temp = getNewNode(num);
                        if (!s.empty()) s.top()->rchild = temp;
                    }
                    if (!s.empty()) p = s.top(), s.pop();
                    flag = 1, num = 0;
                } break;
            case ' ': break;
            case ',': {
                    if (num != 0) {
                        temp = getNewNode(num);
                        if (!s.empty()) s.top()->lchild = temp;
                    }
                    flag = 2, num = 0;
                } break;
            default:
                num = num * 10 + (str[i] - '0');
        }
    }
    if (p == NULL) p = getNewNode(num);
    return p;
}

int dfs(Node *root, int depth) {
    if (root == nullptr) return 0;
    if (root->lchild == nullptr && root->rchild == nullptr) return depth * root->weight;
    int l_wpl = dfs(root->lchild, depth + 1);
    int r_wpl = dfs(root->rchild, depth + 1);
    return r_wpl + l_wpl;
}

int WPL(Node *root) {
    return dfs(root, 0);
}

int main() {
    char str[MAX_N + 5] = {0};
    scanf("%s", str);
    Node *root = build_tree(str);
    printf("%d\n", WPL(root));
    return 0;
}