#include <stdio.h>
#include <stdlib.h>
#include "multiListGraph.h"

MultiListGraph *createMultiListGraph(int n) {
    MultiListGraph *graph = malloc(sizeof(MultiListGraph));
    if (graph == NULL) {
        fprintf(stderr, "graph malloc failed!\n");
        return NULL;
    }
    graph->vertices = malloc(sizeof(Vertex) * n);
    if (graph->vertices == NULL) {
        fprintf(stderr, "vertices malloc failed!\n");
        free(graph);
        return NULL;
    }
    graph->vertexNum = n;
    graph->edgeNum = 0;
    return graph;
}

void releaseMultiListGraph(MultiListGraph *graph) {
    if (graph) {
        if (graph->vertices) {
            for (int i = 0; i < graph->vertexNum; i++) {
                Edge *edge = graph->vertices[i].firstEdge;
                Edge *temp = NULL;
                while (edge) {
                    // 在遍历edge时, 如果不进行任何判断, 则会导致释放了vi指向的edge空间后,                                                                                  \
                        在vj处重新访问了这块已释放的空间(vj的firstEdge指针本身的取值不为空, 因此可以进入循环, 但其指向的空间已被释放),         \
                        此时会导致访问了同一块空间而造成重复释放的错误
                    if (i == edge->iVertex) { // 规定只在下标为edge的i端时进行释放
                        temp = edge;
                        edge = edge->iNext;
                        free(temp);
                        graph->edgeNum--;
                    }
                    else // 当下标为edge的j端时
                        edge = edge->jNext; // 沿着jNext的链表寻找与j端顶点相关联的其他边, 重新进入while循环, 检查是否存在以该顶点为i端的边
                }
            }
            graph->vertexNum = 0;
            free(graph->vertices);
        }
        printf("The graph has been cleared: %d vertex and %d edge left.\n", graph->vertexNum, graph->edgeNum);
        free(graph);
    }
}

void initMultiListGraph(MultiListGraph *graph, char *names[]) {
    if (graph) {
        for (int i = 0; i < graph->vertexNum; i++) {
            graph->vertices[i].id = i;
            graph->vertices[i].name = names[i];
            graph->vertices[i].firstEdge = NULL; // 别忘了初始化指针信息, 防止访问到空指针
        }
    }
}

void addEdgeToGraph(MultiListGraph *graph, int vi, int vj, int weight) {
    if (vi < 0 || vj < 0 || vi > graph->vertexNum || vj > graph->vertexNum) {
        printf("The index is out of range!\n");
        return;
    }
    Edge *new_edge = malloc(sizeof(Edge));
    if (new_edge == NULL) {
        fprintf(stderr, "edge malloc failed!\n");
        return;
    }
    new_edge->weight = weight;
    graph->edgeNum++;
    // 头插法
    new_edge->iVertex = vi; // 顶点vi端
    new_edge->iNext = graph->vertices[vi].firstEdge;
    graph->vertices[vi].firstEdge = new_edge;
    new_edge->jVertex = vj; // 顶点vj端
    new_edge->jNext = graph->vertices[vj].firstEdge;
    graph->vertices[vj].firstEdge = new_edge;
}

static void unlinkEdgeFromList(MultiListGraph *graph, int v, Edge *edge) { // 自定义移除链表中指定边函数
    Edge **ppLink = &graph->vertices[v].firstEdge; // 使用二级指针, 存储了指向顶点 v 的第一条边的指针(一级指针), 可以直接操作该指针本身
    while (*ppLink && *ppLink != edge) { // 对二级指针**ppLink进行一次解引用, 得到指向当前所在边的指针, 如果存在且不为需要删除的目标边时
        if (v == edge->iVertex) // 判断当前顶点是边的i端还是j端
            ppLink = &(*ppLink)->iNext; // 沿i端链表走; 更新二级指针, 获取下一个边指针(iNext)的地址, 使ppLink指向iNext指针本身(而非iNext指向的内容)
        else
            ppLink = &(*ppLink)->jNext; // 沿j端链表走
    }
    if (*ppLink) { // 若*ppLink存在, 则说明 未更新的firstEdge指针 或 链表中的某处iNext/jNext指针 所指向的下一位置即为目标边
        Edge *temp = (v == edge->iVertex) ? edge->iNext : edge->jNext; // 根据目标顶点与目标边的关系确定链表下一位置(下一个边指针)
        *ppLink = temp; // 通过二级指针修改当前边指针所指向的内容, 令当前指针(指向要删除的边的前一处指针)跳过目标边, 直接指向下一边
    }
}
void deleteEdgeFromGraph(MultiListGraph *graph, int vi, int vj) {
    Edge *edge = graph->vertices[vi].firstEdge; // 以与顶点vi相关联的边为起点
    while (edge) {
        if (edge->iVertex == vi && edge->jVertex== vj) // 当寻找到目标边(i端顶点为vi, j端顶点为vj)时跳出循环
            break;
        if (edge->iVertex == vi) // 沿i端链表继续
            edge = edge->iNext;
        else // 沿j端链表继续
            edge = edge->jNext;
    }
    if (edge == NULL) {
        printf("There is no edge between %s and %s!\n", graph->vertices[vi].name, graph->vertices[vj].name);
        return;
    }
    unlinkEdgeFromList(graph, vi, edge); // 从i端链表移除edge
    unlinkEdgeFromList(graph, vj, edge); // 从j端链表移除edge
    graph->edgeNum--;
    free(edge); // 释放辅助指针
}

static void resetEdgeVisitedStatus(MultiListGraph *graph) {
        for (int i = 0; i < graph->vertexNum; i++) {
            Edge *edge = graph->vertices[i].firstEdge;
            while (edge) {
                edge->visited = 0;
                edge = edge->iNext; // 沿顶点i的路径依次进行遍历
            }
        }
}
void showMultiListGraph(MultiListGraph *graph) {
    if (graph) {
        resetEdgeVisitedStatus(graph);
        for (int i = 0; i < graph->vertexNum; i++) {
            Edge *edge = graph->vertices[i].firstEdge;
            while (edge && edge->visited == 0) { // 此处应判断边存在且未被访问(防止重复访问)
                printf("<%s---%s>\n", graph->vertices[edge->iVertex].name, graph->vertices[edge->jVertex].name);
                edge->visited = 1;
                edge = edge->iNext; // 沿顶点i的路径依次进行遍历
            }
        }
    }
}