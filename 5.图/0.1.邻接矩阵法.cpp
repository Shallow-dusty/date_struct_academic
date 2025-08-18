#include <iostream>

// --- 常量与类型定义 ---
#define MAX_VERTEX_NUM 20
#define INFINITY 65535 // 用一个很大的数代表无穷大，用于带权图

typedef char VertexType; // 顶点数据类型
typedef int EdgeType;    // 边的权值类型
typedef int QElemType;   // 队列元素类型

// --- 数据结构定义 ---

// 图结构 (Matrix Graph)
struct MGraph {
    VertexType Vex[MAX_VERTEX_NUM];             // 顶点表
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵，即边表
    int vexnum, arcnum;                         // 图的当前顶点数和弧数
};

// --- 辅助数据结构：手动实现的循环队列 (同上一个版本) ---
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


// 全局访问标记数组
bool visited[MAX_VERTEX_NUM];


/**
 * @brief 在图中定位顶点v的位置（数组下标）
 */
int LocateVex(const MGraph &G, VertexType v) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.Vex[i] == v) return i;
    }
    return -1;
}

/**
 * @brief 创建无向网 (Undirected Network)。对于无权图，边的权值可视为1。
 */
void CreateUDN(MGraph &G) {
    std::cout << "请输入图的顶点数和边数 (vexnum arcnum): ";
    std::cin >> G.vexnum >> G.arcnum;

    std::cout << "请输入 " << G.vexnum << " 个顶点的值 (用空格隔开): ";
    for (int i = 0; i < G.vexnum; ++i) {
        std::cin >> G.Vex[i];
    }

    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            // 如果是无权图，可初始化为0
            G.Edge[i][j] = INFINITY; 
        }
    }

    std::cout << "请输入 " << G.arcnum << " 条边，每条边输入两个顶点及权重 (v1 v2 w):" << std::endl;
    for (int k = 0; k < G.arcnum; ++k) {
        VertexType v1, v2;
        EdgeType w;
        std::cin >> v1 >> v2 >> w; // 如果是无权图，w可固定为1

        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);

        G.Edge[i][j] = w;
        G.Edge[j][i] = w; // 因为是无向网，矩阵对称
    }
}

/**
 * @brief 打印邻接矩阵
 */
void PrintGraph(const MGraph &G) {
    std::cout << "\n--- 图的邻接矩阵表示 ---" << std::endl;
    // 打印列头
    std::cout << "    ";
    for(int i = 0; i < G.vexnum; ++i) {
        std::cout.width(5);
        std::cout << G.Vex[i];
    }
    std::cout << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for(int i = 0; i < G.vexnum; ++i) {
        // 打印行头
        std::cout << G.Vex[i] << " | ";
        for(int j = 0; j < G.vexnum; ++j) {
            std::cout.width(5);
            if(G.Edge[i][j] == INFINITY) {
                std::cout << "∞";
            } else {
                std::cout << G.Edge[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------\n" << std::endl;
}


/**
 * @brief 邻接矩阵的深度优先遍历 (核心递归)
 */
void DFS(const MGraph &G, int v_idx) {
    std::cout << G.Vex[v_idx] << " ";
    visited[v_idx] = true;

    // 核心区别：通过遍历矩阵行来查找邻接点
    for (int j = 0; j < G.vexnum; ++j) {
        // 如果存在边 (v_idx, j) 且 顶点j 未被访问
        if (G.Edge[v_idx][j] != INFINITY && !visited[j]) {
            DFS(G, j);
        }
    }
}

/**
 * @brief 深度优先遍历主函数
 */
void DFSTraverse(const MGraph &G) {
    std::cout << "深度优先遍历 (DFS): ";
    for (int i = 0; i < G.vexnum; ++i) visited[i] = false;
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) DFS(G, i);
    }
    std::cout << std::endl;
}


/**
 * @brief 邻接矩阵的广度优先遍历主函数
 */
void BFSTraverse(const MGraph &G) {
    std::cout << "广度优先遍历 (BFS): ";
    for (int i = 0; i < G.vexnum; ++i) visited[i] = false;

    SqQueue Q;
    InitQueue(Q);

    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            std::cout << G.Vex[i] << " ";
            visited[i] = true;
            EnQueue(Q, i);

            while (!QueueEmpty(Q)) {
                int u_idx = DeQueue(Q);

                // 核心区别：通过遍历矩阵行来查找邻接点
                for (int j = 0; j < G.vexnum; ++j) {
                    // 如果存在边 (u_idx, j) 且 顶点j 未被访问
                    if (G.Edge[u_idx][j] != INFINITY && !visited[j]) {
                        std::cout << G.Vex[j] << " ";
                        visited[j] = true;
                        EnQueue(Q, j);
                    }
                }
            }
        }
    }
    std::cout << std::endl;
}

// --- 主函数：测试 ---
int main() {
    MGraph G;
    CreateUDN(G);
    PrintGraph(G);

    DFSTraverse(G);
    BFSTraverse(G);

    return 0;
}

/*
测试用例 (无权图，权重统一输入1):

请输入图的顶点数和边数 (vexnum arcnum): 5 6
请输入 5 个顶点的值 (用空格隔开): A B C D E
请输入 6 条边，每条边输入两个顶点及权重 (v1 v2 w):
A B 1
A C 1
A D 1
B E 1
C D 1
D E 1

*/