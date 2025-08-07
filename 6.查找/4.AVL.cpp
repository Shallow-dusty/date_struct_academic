#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
//$ AVL树的命名是有两个提出者命名，与average无关

struct Node {
    int key, h;
    Node *lchild, *rchild;
} ;

Node __NIL;
#define NIL (&__NIL)
#define H(n) (n->h)
#define L(n) (n->lchild)
#define R(n) (n->rchild)
#define K(n) (n->key)
__attribute__((constructor)) //$设置下一行函数的属性：先于主函数执行且无需手动调用
void init_NIL() {
    NIL->key = -1;
    NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->h = 1;
    p->lchild = p->rchild = NIL; //$ 虚拟空节点（需要频繁访问左右子树高度）
    return p;
}

void update_height(Node *root) {
    root->h = H(L(root)) > H(R(root)) ? H((L(root))) + 1 : H(R(root)) + 1;
    return ;
}

Node *left_rotate(Node *root) {
    cout << "left rotate : " << K(root) << endl;
    Node *new_node = root->rchild; //左旋以后新根节点为原根节点右子树
    root->rchild = new_node->lchild;//新根左旋后失去左子树，变为原根的右子树（原根的左旋后失去右子树变为根）
    new_node->lchild = root;
    update_height(root); //先更新旋转后的子节点的高度(顺序不可变)
    update_height(new_node);
    return new_node;
}

Node *right_rotate(Node *root) {
    cout << "right rotate : " << K(root) << endl;
    Node *new_node = root->lchild;
    root->lchild = new_node->rchild;
    new_node->rchild = root;
    update_height(root);
    update_height(new_node);
    return new_node;
}

const char *type_str[5] {
    "",
    "maintain type : LL",
    "maintain type : LR",
    "maintain type : RR",
    "maintain type : RL",
};

Node *maintain(Node *root) {
    if (abs(H(L(root)) - H(R(root))) <= 1) return root;
    int type = 0; //调试代码：标记失衡类型,初始为0
    if (H(L(root)) > H(R(root))) { //至此确认第一个字母为L
        if (H(L(root->lchild)) < H(R(root->lchild))) { //即LR类型
            root->lchild = left_rotate(root->lchild);
            type += 1; //LR类型为2
        }
        root = right_rotate(root); //无论LR还是LL都需要大右旋
        type += 1; //LL类型为1
    } else { //第一个字母为R
        type = 2; 
        if (H(L(root->rchild)) > H(R(root->rchild))) { //即RL类型
            root->rchild = right_rotate(root->rchild);
            type += 1; //RL类型为4
        }
        root = left_rotate(root);
        type += 1; //RR类型为3
    }
    printf("%s\n", type_str[type]);
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    update_height(root);
    return maintain(root);
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) { //必须写成！=形式，由于NIL的使用，直接判真会无限循环
        temp = temp->rchild;
    }
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (key < root->key) {
        root->lchild = erase(root->lchild, key);
    }
    else if (key > root->key) root->rchild = erase(root->rchild, key);
    else {
        if (root->lchild == NIL || root->rchild == NIL) { //度为1和度为0的情况实际兼容
            Node *temp = root->lchild != NIL ? root->lchild : root->rchild; //找到唯一子孩子
            free(root);
            return temp; // 当度为0时，temp = rchild = NIL，等价于删除后返回空节点
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    update_height(root);
    return maintain(root);
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

Node *find(Node *root, int key) {
    if (root == NIL) return NIL;
    if (root->key == key) return root;
    if (key < root->key) return find(root->lchild, key);
    else return find(root->rchild, key);
}




void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d[%d] | %d %d)\n", 
        K(root), H(root), 
        K(L(root)), K(R(root))
    );
    output(root->lchild);
    output(root->rchild);
    return ;
}


int main() {
    srand(time(0));
    Node *root = NIL;
    int x;
    //insert test
    while (cin >> x) {
        if (x == -1) break;
        cout << "insert " << x << " to AVL Tree" << endl;
        root = insert(root, x);
        output(root);
    }
    //erase test
    while (cin >> x) {
        if (x == -1) break;
        cout << "erase " << x << " from AVL Tree" << endl;
        root = erase(root, x);
        output(root);
    }
    //find test
    while (cin >> x) {
        if (x == -1) break;
        cout << "find " << x << " in AVL Tree : " << (find(root, x) != NIL) << endl;
    }
    return 0;
}