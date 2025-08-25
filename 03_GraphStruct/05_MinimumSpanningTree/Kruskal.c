#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kruskal.h"

void initEdgeSet(const MatrixGraph *graph, EdgeSet *edges) {
    int sum = 0;
    for (int i = 0; i < graph->vertexNum; i++) {
        for (int j = i+1; j < graph->vertexNum; j++) { // 遍历邻接矩阵对角线上方的三角形区域
            if (graph->edges[i][j] > 0) { // 将带权值的边放入边集数组中
                edges[sum].begin = i;
                edges[sum].end = j;
                edges[sum].weight = graph->edges[i][j];
                sum++;
            }
        }
    }
}

void sortEdgeSet(EdgeSet *edges, int n) {
    EdgeSet temp; // 使用临时变量用于交换顺序
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (edges[i].weight > edges[j].weight) { // 冒泡排序
                memcpy(&temp, &edges[i], sizeof(EdgeSet)); // 使用取地址符, 访问目标地址, 将数据进行拷贝
                memcpy(&edges[i], &edges[j], sizeof(EdgeSet));
                memcpy(&edges[j], &temp, sizeof(EdgeSet));
            }
        }
    }
}

static int getRoot(int *set, int v) { // 获取当前顶点所在组别的根节点下标
    while (set[v] != v)
        v = set[v];
    return v;
}
int KruskalAlgorithm(const EdgeSet *edges, int vertexNum, int edgeNum, EdgeSet *result) { // 一种贪心算法
    int *unionFindSet = malloc(sizeof(int) * vertexNum); // 使用并查集的分组思想判断生成树中是否会产生环(判断两顶点是否处于同一组)
    if (unionFindSet == NULL) {
        fprintf(stderr, "set malloc failed!\n");
        return -1;
    }
    for (int i = 0; i < vertexNum; i++)
        unionFindSet[i] = i; // 初始化并查集, 每个顶点的组别根节点默认为自身

    int count = 0;
    int sum = 0;
    for (int i = 0; i < edgeNum; i++) {
        int rootA = getRoot(unionFindSet, edges[i].begin); // 获取每条边上两顶点的组别根节点下标
        int rootB = getRoot(unionFindSet, edges[i].end);
        if (rootA != rootB) { // 若两根节点不等时, 则取当前边连接两顶点不会构成环
            unionFindSet[rootB] = rootA; // 将两个顶点所在组别信息进行合并
            memcpy(&result[count], &edges[i], sizeof(EdgeSet)); // 将总边集数组中符合条件的边拷贝到结果集合中
            sum += result[count].weight;
            count++; // 更新总量
        }
    }
    free(unionFindSet); // 释放临时并查集
    return sum; // 返回最小生成树的总权值
}