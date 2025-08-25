#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "common.h"
#include "../01_MatrixGraph/matrixGraph.h" // 从上级目录../中找到邻接矩阵表图中的头文件进行引用

void initEdgeSet(const MatrixGraph *graph, EdgeSet *edges); // 从邻接矩阵中初始化边集数组
void sortEdgeSet(EdgeSet *edges, int n); // 对边集数组进行排序
int KruskalAlgorithm(const EdgeSet *edges, int vertexNum, int edgeNum, EdgeSet *result);

#endif //KRUSKAL_H
