#include <iostream>
using namespace std;

struct Node {
   char ch;
   int freq;
   Node *lchild, *rchild;
};

Node *getNewNode(int freq, char ch) {
   // Node *p = (Node *)malloc(sizeof(Node));
   Node *p = new Node;
   p->ch = ch;
   p->freq = freq;
   p->lchild = p->rchild = NULL;
   return p;
   
}

void clear(Node *root) {
   if (root == NULL) return ;
   clear(root->lchild);
   clear(root->rchild);
   delete(root);
   return ;
}

//交换两个节点
void swap_node(Node **node_arr, int i, int j) {
   Node *temp = node_arr[i];
   node_arr[i] = node_arr[j];
   node_arr[j] = temp;
   return ;
}
// 寻找节点数组中的最小值
int find_min_node(Node **node_arr, int n) { //扫描到索引n(包括n)
      int ind = 0;
      for (int i = 1; i <= n; i++) {
        if (node_arr[ind]->freq > node_arr[i]->freq) ind = i;
      }
      return ind;
}

//# 建立哈夫曼树
Node *buildHaffmanTree(Node **node_arr, int n) {
   // for (int i = 0; i < n; i++) {
   //    cout << node_arr[i]->ch << " " << node_arr[i]->freq << endl;
   // }

   for (int i = 1; i < n; i++) { // 合并n - 1次
   // step1: find two node 
      int ind1 = find_min_node(node_arr, n - i);
      swap_node(node_arr, ind1, n - i);
      int ind2 = find_min_node(node_arr, n - i - 1);
      swap_node(node_arr, ind2, n - i - 1);
   // step2: merge two node
      int freq = node_arr[n - i]->freq + node_arr[n - i - 1]->freq;
      Node *node = getNewNode(freq, 0);
      node->lchild = node_arr[n - i - 1];
      node->rchild = node_arr[n - i];
      node_arr[n - i - 1] = node;
   }
   return node_arr[0];
}

//# 提取哈夫曼编码
void extraHaffmanCode(Node *root, char buff[], int k) {
   buff[k] = 0;
   if (root->lchild == NULL && root->rchild == NULL) { // 叶子节点
      //? buff[k] = 0; //可放在此处，，且更合理（1. 非叶子结点时无多余赋值 2. 便于理解目的）
      cout << root->ch << " : " << buff << endl;
      return ;
   }
   buff[k] = '0';
   extraHaffmanCode(root->lchild, buff, k + 1);
   buff[k] = '1';
   extraHaffmanCode(root->rchild, buff, k + 1);
   return ;
}

int main() {
   char s[10];
   int n, freq;
   cin >> n;
   // Node ** node_arr = (Node **)malloc(sizeof(Node *) * n);
   Node **node_arr = new Node*[n];
   for (int i = 0; i < n; i++) {
      cin >> s >> freq;
      node_arr[i] = getNewNode(freq, s[0]);
   }
   Node *root = buildHaffmanTree(node_arr, n);
   char buff[1000];
   extraHaffmanCode(root, buff, 0);
   clear(root);
   return 0;
}


