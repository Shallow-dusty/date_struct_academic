/*************************************************************************
    > File Name: solve.cpp
    > Author:
    > Mail:
    > Created Time:
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;

#define max_n 100

typedef struct node{
    char data;
    struct node *left, *right;
} BTree;

BTree *getNewNode(char val) {
    BTree *p = (BTree *)malloc(sizeof(BTree));
    p->data = val;
    p->left = p->right = NULL;
    return p;
}

BTree *build_tree(char *str) {
    std::stack<BTree *> s;
    BTree *temp = NULL, *p = NULL;
    int flag = 0;
    for (int i = 0; str[i]; i++) {
        switch (str[i]) {
            case '(':
                s.push(temp);
                flag = 0;
                break;
            case ',':
                flag = 1;
                break;
            case ')':
                p = s.top();
                s.pop();
                break;
            case ' ': break;
            default:
                temp = getNewNode(str[i]);
                if (!s.empty() && flag == 0) {
                    s.top()->left = temp;
                } else if (!s.empty() && flag == 1) {
                    s.top()->right = temp;
                }
                break;
        }
    }
    if (temp && p == NULL) p = temp;
    return p;
}

int get_Level(char *op) {
    // if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
    //     return 1;
    // }
    // if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
    //     return 2;
    // }
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}


void in_order(BTree *root) {
    int depth = 0;
    if (root == nullptr) return ;
    // if (get_Level(root->data) > 0) {
        
    // }
    if (root->left){
        in_order(root->left);
    }  
    depth++;
    if (depth != 0 ) {
        cout << "(";
        cout << root->data;
        cout << ")";
    }

    if (root->right){
        in_order(root->right);
    } 
    return ;
}
void BtreeToE(BTree *root){
    
}

int main() {
    char str[max_n + 5] = {0};
    cin.getline(str, max_n);
    BTree *root = build_tree(str);
    BtreeToE(root);
    return 0;
}