//@ 二叉树基础定义和操作
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAX_NODE 10

struct Node {
    int key;
    Node* lchild, *rchild;
};

// 获取新结点
Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

// 销毁树
void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

// 插入值为key的节点（随机插入）
Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (rand() % 2) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

//数组模拟队列
Node *queue[MAX_NODE + 5];
int head, tail;

//广度优先遍历
void bfs(Node *root) {
    if (root == NULL) return ;
    head = tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node *node = queue[head];
        printf("\nnode:%d \n", node->key);
        if (node->lchild) {
            queue[tail++] = node->lchild;
            printf("%d->%d(left)\n", node->key, node->lchild->key);
        }
        if (node->rchild) {
            queue[tail++] = node->rchild;
            printf("%d->%d(right)\n", node->key, node->rchild->key);
        }
        head++;
    }
    return ;
}


int tot = 0; //时间戳
//深度优先遍历
void dfs(Node *root) {
    if (root == NULL) return ;
    int start = tot;
    tot++;
    if (root->lchild) dfs(root->lchild);
    if (root->rchild) dfs(root->rchild);
    tot++;
    int end = tot;
    printf("%d : [%d, %d]\n", root->key, start, end);
    return ;
}


int main() {
    srand(time(0));
    Node *root = NULL;
    for (int i = 0; i < 10; i++) {
        root = insert(root, rand() % 100);
    }
    bfs(root);
    dfs(root);
    clear(root);
    return 0;
}