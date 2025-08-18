#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#define MAX_N 10000

#define true 1
#define false 0

typedef struct {
    int SqBiTNode[MAX_N + 5];
    //保存二叉树结点值的数组
    int ElemNum;
    //实际占用的数组元素个数
} SqBiTree;

bool isValidBST(SqBiTree T){
    for (int i = 0; i < T.ElemNum; i++) {
        if (2 * i + 2 > T.ElemNum - 1 || 2 * i + 1 > T.ElemNum - 1) continue; 
        if (T.SqBiTNode[i] == -1) continue;
        if (T.SqBiTNode[2 * i + 1] >  T.SqBiTNode[i] || T.SqBiTNode[2 * i + 2] < T.SqBiTNode[i] ) {
            return false;
        }
    }
    return true;
}


int main() {
    int n;
    scanf("%d", &n);
    SqBiTree bt;
    bt.ElemNum = n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt.SqBiTNode[i]);
    }
    printf("%d\n", isValidBST(bt));
    return 0;
}