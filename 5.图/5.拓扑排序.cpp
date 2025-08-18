#include <iostream>
using namespace std;
#define MAX_VERTEX_NUM 20
typedef char VertexType;
struct ArcNode {
    int adjvex;
    ArcNode *nextarc;
};

struct VNode {
    VertexType data;
    ArcNode *firstarc;
};

struct ADLGraph{
    VNode vertices[MAX_VERTEX_NUM];
    int vexnum, arcnum;
};

struct SqStack{
    int data[MAX_VERTEX_NUM];
    int top;
};

void init_stack(SqStack &s) {
    s.top = -1;
}

bool isEmpty(const SqStack &s) {
    return s.top == -1;
}

void push(SqStack &s, int e) {
    s.data[++s.top] = e;
}

int pop(SqStack &s) {
    return s.data[s.top--];
}

bool topo_logic_sort(ADLGraph &g) {
    SqStack s;
    init_stack(s);
    for (int i = 0; i < g.vexnum; i++) {
    }
    return true;
}











