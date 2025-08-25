#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "../01_MatrixGraph/matrixGraph.h" // 从上级目录../中找到邻接矩阵表图中的头文件进行引用

typedef struct {
    int begin; // 边的起点
    int end; // 终点
    int weight; // 权重值
} EdgeSet; // 边集数组的元素结构

void initEdgeSet(const MatrixGraph *graph, EdgeSet *edges); // 从邻接矩阵中初始化边集数组
void sortEdgeSet(EdgeSet *edges, int n); // 对边集数组进行排序
int KruskalAlgorithm(const EdgeSet *edges, int vertexNum, int edgeNum, EdgeSet *result);

#endif //KRUSKAL_H
