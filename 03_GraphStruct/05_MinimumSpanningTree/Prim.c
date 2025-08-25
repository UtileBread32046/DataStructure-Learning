#include <stdio.h>
#include <stdlib.h>
#include "Prim.h"

static void initializeTemporaryArray(const MatrixGraph *graph,  int **cost, int **visitedVertices, int **activatedVertices) { // 使用二级指针修改参数原值
    *cost = malloc(sizeof(int) * graph->vertexNum); // 设置开销数组, 记录当前位置到其他未激活顶点所需的权值
    if (*cost == NULL) {
        fprintf(stderr, "cost malloc failed!\n");
        return;
    }
    for (int i = 0; i < graph->vertexNum; i++)
        // 将初始值赋为自定义的"无限大", 从而寻找最小值
        (*cost)[i] = INF;  // 注意运算符优先级顺序, 一定要将*cost括起来!!!

    *visitedVertices = malloc(sizeof(int) * graph->vertexNum); // 设置访问数组, 检查当前顶点是否已被访问
    if (*visitedVertices == NULL) {
        fprintf(stderr, "visited malloc failed!\n");
        free(*cost);
        return;
    }
    for (int i = 0; i < graph->vertexNum; i++)
        (*visitedVertices)[i] = 0; // 全部初始化为0

    *activatedVertices = malloc(sizeof(int) * graph->vertexNum); // 设置激活数组, 检查当前顶点是否已被激活
    if (*activatedVertices == NULL) {
        fprintf(stderr, "visited malloc failed!\n");
        free(*cost);
        free(*visitedVertices);
        return;
    }
    for (int i = 0; i < graph->vertexNum; i++)
        (*activatedVertices)[i] = 0; // 全部初始化为0
}

static int findMinValueInCost(const MatrixGraph *graph, const int* cost, const int* activatedVertices) {
    int min = -1;
    for (int i = 0; i < graph->vertexNum; i++) {
        if (!activatedVertices[i]) { // 仅考虑未激活顶点
            if (min == -1 || cost[min] > cost[i])
                min = i; // 寻找当前开销列表中的最小值索引
        }
    }
    return min;
}

static void saveResult(EdgeSet **result, const int* cost, int **activatedVertices, int index, int min, int *sum, int *count) { // 存储结果
    (*result)[*count].begin = index;
    (*result)[*count].end = min;
    (*result)[*count].weight = cost[min];
    *sum += (*result)[*count].weight; // 更新总权值
    (*count)++; // 更新总个数
    (*activatedVertices)[min] = 1; // 更新激活状态
}

int PrimAlgorithm(const MatrixGraph *graph, int start, EdgeSet *result) {
    int *cost = NULL;
    int *visitedVertices = NULL;
    int *activatedVertices = NULL;
    initializeTemporaryArray(graph, &cost, &visitedVertices, &activatedVertices); // 初始化信息数组

    int sum = 0; // 记录总权值
    int count = 0; // 记录总个数
    int new = start; // 新激活的顶点下标, 开始时即为用于初始化的顶点下标
    activatedVertices[start] = 1;

    while (count < graph->vertexNum - 1) {
        for (int i = 0; i < graph->vertexNum; i++) {
            if (activatedVertices[i] == 1) continue;
            // 若该顶点未被激活, 则使用最新激活的顶点更新花销数组cost (无需遍历全部已激活的顶点, 降低时间复杂度)
            if (0 < graph->edges[i][new] && graph->edges[i][new] < INF && graph->edges[i][new] < cost[i]) {
                // 若两顶点间存在边且未记录(默认的花销权值为无限大)或比已记录的花销权值更小时, 进行更新
                cost[i] = graph->edges[i][new];
                visitedVertices[i] = new; // 记录访问信息"由谁访问的"
            }
        }
        new = findMinValueInCost(graph, cost, activatedVertices); // 新激活的顶点应为cost中的最小值
        saveResult(&result, cost, &activatedVertices, visitedVertices[new], new, &sum, &count); // 注意应传入visited记录中的信息而非循环索引
    }
    free(cost); // 释放临时数组
    free(visitedVertices);
    free(activatedVertices);
    return sum; // 返回总权值
}