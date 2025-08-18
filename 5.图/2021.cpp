/*************************************************************************
    > File Name: solve.cpp
    > Author:
    > Mail:
    > Created Time:
 ************************************************************************/

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXV 30

typedef struct{ //图的定义
        int numVertices, numEdges; //图中实际的顶点数和边数。
        char Verticeslist[MAXV]; //顶点表。MAXV为已定义常量。
        int Edge[MAXV][MAXV];//邻接矩阵。
} MGraph;

void Create_MGraph(MGraph &G);

void Create_MGraph(MGraph &G) {
    int x, y;
    char c1, c2;
    cin >> G.numVertices >> G.numEdges;
    memset(G.Edge, 0, sizeof(G.Edge));
    for (int i = 0; i < G.numVertices; i++) {
        cin >> G.Verticeslist[i];
    }
    for (int i = 0; i < G.numEdges; i++) {
        cin >> c1 >> c2;
        for (int j = 0; j < G.numVertices; j++) {
            if (c1 == G.Verticeslist[j]) x = j;
            if (c2 == G.Verticeslist[j]) y = j;
        }
        G.Edge[x][y] = G.Edge[y][x] = 1;
    }
    return ;
}

int IsExistEL(MGraph G) {
    int cnt = 0; 
    for (int i = 0; i < G.numEdges; i++) {
        int count = 0;
        for (int j = 0; j < G.numEdges; j++) {
            if (G.Edge[i][j]) count++; 
        }
        if (count % 2) {
            cnt++;
        }
    }
    if (cnt == 0 || cnt == 2) return 1;
    else return 0;
}

int main() {
    MGraph G;
    int sum = 0;
    Create_MGraph(G);
    printf("%s\n", IsExistEL(G) ? "YES" : "NO");
    return 0;
}