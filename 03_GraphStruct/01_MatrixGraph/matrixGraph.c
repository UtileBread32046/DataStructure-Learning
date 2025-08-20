#include <stdio.h>
#include <string.h>
#include "matrixGraph.h"

void initMatrixGraph(MatrixGraph *graph, char *names[], int vertexNum, int directed, int edgeValue) {
    graph->vertexNum = vertexNum; // 顶点数
    graph->edgeNum = 0; // 边数(默认为0)
    graph->directed = directed; // 图是否有方向
    memset(graph->vertices, 0, sizeof(MatrixVertex)); // 将顶点的内存空间初始化为0, 避免使用未定义的垃圾值(随机值)
    memset(graph->edges, 0, sizeof(MatrixEdge) * MAX_SIZE * MAX_SIZE); // 将邻接矩阵的所有元素初始化为0, 避免内存中有垃圾值; 初始化空间是整个矩阵而非顶点集的大小
    for (int i = 0; i < vertexNum; i++) {
        graph->vertices[i].id = i; // 对图中顶点集中下标为i的结构进行初始化
        graph->vertices[i].name = names[i];
        for (int j = 0; j < vertexNum; j++)
            graph->edges[i][j] = edgeValue; // 对图中边集下标为(i, j)的边赋值(默认权重值)
    }
}

static int judgeEdgeExistence(MatrixGraph *graph, int v1, int v2) { // 通过两顶点间边的权重值判断边是否存在
    int weight = graph->edges[v1][v2];
    if (0 < weight && weight < INF) {
        return 1; // 存在边
    }
    return 0; // 不存在
}
void addEdgeToGraph(MatrixGraph *graph, int v1, int v2, int weight) {
    if (v1 < 0 || v2 < 0 ||  v1 > graph->vertexNum || v2 > graph->vertexNum) {
        printf("The index is out of range!\n");
        return;
    }
    if (judgeEdgeExistence(graph, v1, v2) == 0) { // 当边不存在时
        graph->edges[v1][v2] = weight; // 赋予权重, 即添加边
        if (graph->directed == 0) // 若为无向图
            graph->edges[v2][v1] = weight; // 无向图的邻接矩阵为对称矩阵, 可自动将对称点的权重赋值
        graph->edgeNum++; // 更新图中记录的边数
    }
}

void visitVertexInGraph(MatrixVertex *v) {
    if (v)
        printf("%s\t", v->name);
}

static int visitedVertices[MAX_SIZE] = {0}; // 存储已访问的节点
void initVisitedVertices(int *visitedVertices) {
    if (visitedVertices)
        memset(visitedVertices, 0, sizeof(int) * MAX_SIZE); // 将访问的数组空间覆盖为0; 注意大小应当是int数据类型大小*类型个数
}

static void DFSGraphVertices(MatrixGraph *graph, int index) {
    visitVertexInGraph(&graph->vertices[index]); // 访问图中顶点集中下标为index的顶点, 注意取地址符&
    visitedVertices[index] = 1; // 标记访问信息
    for (int i = 0; i < graph->vertexNum; i++) {
        if (judgeEdgeExistence(graph, index, i) && visitedVertices[i] == 0) { // 依次遍历所有节点, 当两点间存在边(邻接)且未被访问过时
            DFSGraphVertices(graph, i); // 对下标为i的顶点进行递归, 进而寻找i所连接的其他顶点
        }
    }
}
void DFSMatrixGraph(MatrixGraph *graph, int index) {
    if (graph) {
        printf("DFS Mode: ");
        initVisitedVertices(visitedVertices);
        DFSGraphVertices(graph, index);
        printf("\n");
    }
}

static void BFSGraphVertices(MatrixGraph *graph, int index) {
    int queue[MAX_SIZE] = {0}; // 使用队列进行广度遍历
    int front = 0, rear = 0;
    queue[rear] = index; // 将起始位置入队
    rear++;
    visitedVertices[front] = 1; // 将已经入队的节点记录为已访问
    while (front != rear) { // 当队列非空时
        int cur = queue[front]; // 将当前队列中的队首元素出队
        visitVertexInGraph(&graph->vertices[cur]); // 访问队首元素索引对应的节点

        front = (front+1) % MAX_SIZE; // 循环队列
        for (int i = 0; i < graph->vertexNum; i++) {
            if (judgeEdgeExistence(graph, cur, i) && visitedVertices[i] == 0) {
                queue[rear] = i; // 将检测到的未访问的邻接节点依次入队
                visitedVertices[rear] = 1; // 记录入队节点而非出队, 从而避免仍未出队的节点被重新入队
                rear = (rear+1) % MAX_SIZE;
            }
        }
    }
}
void BFSMatrixGraph(MatrixGraph *graph, int index) {
    if (graph) {
        printf("BFS Mode: ");
        initVisitedVertices(visitedVertices);
        BFSGraphVertices(graph, index);
        printf("\n");
    }
}
