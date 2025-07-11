#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
//@ 1. 二叉树前中后序遍历 2.二叉树线索化（将二叉树遍历的递归改为非递归————类似于链表的访问方式）
//todo : 前序和后序线索化的建立
//todo : 线索化建立的再理解
struct Node {
    int key;
    int ltag, rtag; // 1代表为thread, 0代表为edge
    Node *lchild, *rchild;
};

Node *getNewNode(int key) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->key = key;
    p->ltag = 0;
    p->rtag = 0;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    if (root->ltag == 0) //只沿着实际的边销毁
        clear(root->lchild);
    if (root->rtag == 0)
        clear(root->rchild);
    free(root);
    return ;
}

Node *insert(Node *root, int key) { //$ 改为引用传递写法: Node *&root(而非Node &*root————c++语法不支持）
    if (root == NULL) return getNewNode(key);
    if (rand() % 2) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

//# 线索化建立（（中序））
Node *pre_node = NULL, *inorder_node = NULL;
void __build_inorder_thread(Node *root) {
    if (root == NULL) return ;
    if (root->ltag == 0) __build_inorder_thread(root->lchild);
    if (inorder_node == NULL) inorder_node = root;
    if (root->lchild == NULL) {
        root->lchild = pre_node; // 建立当前节点的前驱
        root->ltag = 1;
    }
    if (pre_node && pre_node->rchild == NULL) { // 建立前一个节点的后继
        pre_node->rchild = root;
        pre_node->rtag = 1;
    }
    pre_node = root;
    if (root->rtag == 0) __build_inorder_thread(root->rchild);
    return ;
}

void build_inorder_thread(Node *root) {
    __build_inorder_thread(root);
    pre_node->rchild = NULL;
    pre_node->rtag = 1;
    return ;
}

Node *getNext(Node *root) {
    if (root->rtag == 1) return root->rchild;
    root = root->rchild;
    while (root->ltag == 0 && root->lchild) { //? 第二个条件几乎无作用
        root = root->lchild;
    }
    return root;
}

//!-------------------------------------------------------------------------------//
//# 前序遍历
void pre_order(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->key);
    if (root->ltag == 0) pre_order(root->lchild);
    if (root->rtag == 0) pre_order(root->rchild);
    return ;
}

//# 中序遍历————修改：线索化
void in_order(Node *root) {
    if (root == NULL) return ;
    if (root->ltag == 0) in_order(root->lchild);
    printf("%d ", root->key);
    if (root->rtag == 0) in_order(root->rchild);
    return ;
}

//# 后序遍历
void post_order(Node *root) {
    if (root == NULL) return ;
    if (root->ltag == 0) post_order(root->lchild);
    if (root->rtag == 0) post_order(root->rchild);
    printf("%d ", root->key);
    return ;
}
//!---------------------------------------------------------------------------------//

int main() {
    srand(time(0));
    Node *root = NULL;
    for (int i = 0; i < 10; i++) {
        root = insert(root, rand() % 100); //注意insert传入的参数为root的副本，，故insert不会改变root本身
    }
    build_inorder_thread(root);
    pre_order(root);
    cout << endl;
    in_order(root);
    cout << endl;
    post_order(root);
    cout << endl;
    // like linklist
    Node *node =inorder_node;
    while (node) {
        cout << node->key << " ";
        node = getNext(node);
    }
    cout << endl;
    clear(root);
    return 0;
}