#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;
#define MAX_OP 10
#define KEY(n) (n ? n->key : -1)


struct Node {
    int key;
    Node *lchild, *rchild;
};

Node *getNewNode(int key) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->key = key; 
    p->rchild = p->lchild = nullptr;
    return p;
}

Node *insert(Node *root, int key) {
    if (root == nullptr) return getNewNode(key);
    if (key == root->key) return root; //工程上BST一般不允许键重复
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

Node *predecessor(Node *root) {
    // if (root == nullptr || root->lchild == nullptr) return nullptr;
    //$ 空指针保护：理论需要，但本程序该函数只写在删除度为2的节点中，则其必然有左孩子
    Node *temp = root->lchild;
    while (temp->rchild) {
        temp = temp->rchild;
    }
    return temp;
}


Node *erase(Node *root, int key) {
    if (root == nullptr) return root;
    if (key < root->key) root->lchild = erase(root->lchild, key);
    else if (key > root->key) root->rchild = erase(root->rchild, key);
    else {
        if (root->lchild == nullptr && root->rchild == nullptr) {
            free(root);
            return nullptr;
        } 
        else if (root->lchild == nullptr || root->rchild == nullptr) {
           Node *temp = root->lchild ? root->lchild : root->rchild;
           free(root);
           return temp; 
        }
        else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
        return root;
    }
    return root;
}

void clear(Node *root) {
    if (root == nullptr) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}

void output(Node *root) {
    if (root == nullptr) return ;
    printf("(%d: %d , %d)\n", KEY(root), KEY(root->lchild), KEY(root->rchild));
    output(root->lchild);
    output(root->rchild);
    return ;
}

void in_order(Node *root) {
    if (root == nullptr) return ;
    in_order(root->lchild);
    // printf("(%d : %d , %d)\n", KEY(root), KEY(root->lchild), KEY(root->rchild)); 
    cout << root->key << " ";
    in_order(root->rchild);
    return ; 
}

int main() {
    srand(time(0));
    Node *root = nullptr;
    for (int i = 0; i < MAX_OP; i++) {
        int key = rand() % 100;
        cout << "insert " << key << " to binary search tree" << endl;
        root = insert(root, key); 
    }
    output(root);
    printf("in order : ");
    in_order(root);
    cout << endl;
    int x;
    while (~scanf("%d", &x)) {
        printf("erase %d from binary search tree\n", x);
        root = erase(root, x);
        in_order(root);
        cout << endl;
    }

    clear(root);
    return 0;
}


