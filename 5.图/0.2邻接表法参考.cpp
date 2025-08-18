#include <iostream>

// --- 常量与类型定义 ---
#define MAX_VERTEX_NUM 20
typedef char VertexType;
typedef int QElemType; // 队列元素是顶点下标

// --- 数据结构定义 (C++风格的struct) ---
struct ArcNode {
    int adjvex;
    ArcNode *nextarc;
};

struct VNode {
    VertexType data;
    ArcNode *firstarc;
};

struct ALGraph {
    VNode vertices[MAX_VERTEX_NUM];
    int vexnum, arcnum;
};

// --- 辅助数据结构：手动实现的循环队列 (核心！) ---
struct SqQueue {
    QElemType data[MAX_VERTEX_NUM];
    int front, rear;
};

void InitQueue(SqQueue &Q) { Q.front = Q.rear = 0; }
bool QueueEmpty(const SqQueue &Q) { return Q.front == Q.rear; }
void EnQueue(SqQueue &Q, QElemType e) {
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAX_VERTEX_NUM;
}
QElemType DeQueue(SqQueue &Q) {
    QElemType e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAX_VERTEX_NUM;
    return e;
}
// --- 队列实现结束 ---

bool visited[MAX_VERTEX_NUM];

/**
 * @brief 在图中定位顶点v的位置（数组下标）
 * @param G 图的引用
 * @param v 顶点值
 */
int LocateVex(const ALGraph &G, VertexType v) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].data == v) return i;
    }
    return -1;
}

/**
 * @brief 创建无向图 (使用引用和new)
 */
void CreateUDG(ALGraph &G) {
    std::cout << "请输入图的顶点数和边数 (vexnum arcnum): ";
    std::cin >> G.vexnum >> G.arcnum;

    std::cout << "请输入 " << G.vexnum << " 个顶点的值 (用空格隔开): ";
    for (int i = 0; i < G.vexnum; ++i) {
        std::cin >> G.vertices[i].data;
        G.vertices[i].firstarc = nullptr;
    }

    std::cout << "请输入 " << G.arcnum << " 条边，每条边输入两个顶点 (v1 v2):" << std::endl;
    for (int k = 0; k < G.arcnum; ++k) {
        VertexType v1, v2;
        std::cin >> v1 >> v2;

        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);

        // 使用 new 分配内存
        ArcNode *p1 = new ArcNode();
        p1->adjvex = j;
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1;
        
        ArcNode *p2 = new ArcNode();
        p2->adjvex = i;
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;
    }
}

/**
 * @brief DFS核心递归 (使用引用)
 */
void DFS(const ALGraph &G, int v_idx) {
    std::cout << G.vertices[v_idx].data << " ";
    visited[v_idx] = true;

    ArcNode *p = G.vertices[v_idx].firstarc;
    while(p) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex);
        }
        p = p->nextarc;
    }
}

/**
 * @brief DFSTraverse主函数
 */
void DFSTraverse(const ALGraph &G) {
    std::cout << "深度优先遍历 (DFS): ";
    for (int i = 0; i < G.vexnum; ++i) visited[i] = false;
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) DFS(G, i);
    }
    std::cout << std::endl;
}

/**
 * @brief BFSTraverse主函数 (使用手写队列)
 */
void BFSTraverse(const ALGraph &G) {
    std::cout << "广度优先遍历 (BFS): ";
    for (int i = 0; i < G.vexnum; ++i) visited[i] = false;
    
    SqQueue Q;
    InitQueue(Q);

    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            std::cout << G.vertices[i].data << " ";
            visited[i] = true;
            EnQueue(Q, i);
            
            while (!QueueEmpty(Q)) {
                int u_idx = DeQueue(Q);
                ArcNode *p = G.vertices[u_idx].firstarc;
                while(p) {
                    int w_idx = p->adjvex;
                    if (!visited[w_idx]) {
                        std::cout << G.vertices[w_idx].data << " ";
                        visited[w_idx] = true;
                        EnQueue(Q, w_idx);
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    std::cout << std::endl;
}


int main() {
    ALGraph G;
    CreateUDG(G);

    DFSTraverse(G);
    BFSTraverse(G);

    return 0;
}