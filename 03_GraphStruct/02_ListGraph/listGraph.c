#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listGraph.h"

ListGraph * createListGraph(int n) {
    ListGraph *graph = malloc(sizeof(ListGraph));
    if (graph == NULL) {
        fprintf(stderr, "graph malloc failed!\n");
        return NULL;
    }
    graph->vertexNum = n;
    graph->arcNum = 0; // 默认弧数为0
    graph->directed = 0;
    graph->vertices = malloc(sizeof(Vertex) * n);
    if (graph->vertices == NULL) {
        fprintf(stderr, "vertices malloc failed!\n");
        free(graph); // 中途某处分配失败时应当将所有已分配的空间释放掉, 防止内存泄漏
        return NULL;
    }
    memset(graph->vertices, 0, sizeof(Vertex) * n); // 注意分配内存的空间大小应当是数据类型*元素个数
    return graph;
}

void releaseListGraph(ListGraph *graph) {
    if (graph) {
        if (graph->vertices)
            free(graph->vertices);
        free(graph);
        printf("The graph has been cleared!\n");
    }
}

void initListGraph(ListGraph *graph, char *names[], int directed) {
    if (graph) {
        graph->directed = directed;
        for (int i = 0; i < graph->vertexNum; i++) {
            graph->vertices[i].id = i;
            graph->vertices[i].visited = 0;
            graph->vertices[i].name = names[i];
            graph->vertices[i].firstArc = NULL;
        }
    }
}

static Arc *createArc(int tail, int weight) { // 创建一个新弧
    Arc *arc = malloc(sizeof(Arc));
    if (arc == NULL) {
        fprintf(stderr, "arc malloc failed!\n");
        return NULL;
    }
    arc->tail = tail;
    arc->weight = weight;
    arc->next = NULL;
    return arc;
}
void addArcToGraph(ListGraph *graph, int v1, int v2, int weight) {
    if (v1 < 0 || v2 < 0 || v1 >= graph->vertexNum || v2 >= graph->vertexNum) {
        printf("The index is out of range!\n");
        return;
    }
    if (v1 == v2) {
        printf("The two indices are same!\n"); // indices: index的复数形式
        return;
    }
    Arc *arc = createArc(v2, weight);
    arc->next = graph->vertices[v1].firstArc;
    graph->vertices[v1].firstArc = arc; // 头插法: head->node1->node2->NULL --- head->new_node1->node1->node2->NULL
    graph->arcNum++;
    if (graph->directed == 0) { // 若为无向图, 则再以v2为首, v1为尾连接一条弧
        Arc *arc2 = createArc(v1, weight);
        arc2->next = graph->vertices[v2].firstArc;
        graph->vertices[v2].firstArc = arc2;
    }
}

void initVertexVisited(ListGraph *graph) {
    if (graph) {
        for (int i = 0; i < graph->vertexNum; i++)
            graph->vertices[i].visited = 0;
    }
}

void visitVertexInGraph(Vertex *v) {
    if (v)
        printf("%s\t", v->name);
}

static void DFSGraphVertices(ListGraph *graph, int index) {
    Arc *pos = graph->vertices[index].firstArc; // 设置辅助指针, 进行遍历
    visitVertexInGraph(&graph->vertices[index]); // 访问当前顶点
    graph->vertices[index].visited = 1; // 记录访问状态
    while (pos) { // 不断移动指针直至遍历完成
        if (graph->vertices[pos->tail].visited == 0) { // 若当前弧的弧尾指向顶点未访问时
            DFSGraphVertices(graph, pos->tail); // 对弧尾顶点进行递归, 寻找其所连接的其他顶点
        }
        pos = pos->next; // 移动到下一条弧上, 继续进行循环和递归
    }
}
void DFSListGraph(ListGraph *graph, int index) {
    if (graph) {
        printf("DFS Traversal: ");
        initVertexVisited(graph);
        DFSGraphVertices(graph, index);
        printf("\n");
    }
}

static void BFSGraphVertices(ListGraph *graph, int index) {
    int *queue = malloc(sizeof(int) * graph->vertexNum); // 使用队列进行广度优先遍历; 注意应当申请数据类型*元素个数的空间
    if (queue == NULL) {
        fprintf(stderr, "queue malloc failed!\n");
        return;
    }
    int front = 0, rear = 0;
    queue[rear] = index;
    graph->vertices[rear].visited = 1; // 标记入队元素已访问
    rear++;
    while (front != rear) {
        int cur = queue[front]; // 队首元素出队
        visitVertexInGraph(&graph->vertices[cur]); // 访问顶点
        front = (front+1) % graph->vertexNum; // 循环队列
        Arc *pos = graph->vertices[cur].firstArc; // 设置辅助指针, 指向顶点所在的弧
        while (pos) {
            if (graph->vertices[pos->tail].visited == 0) { // 若弧尾顶点未访问
                queue[rear] = pos->tail; // 入队
                rear = (rear+1) % graph->vertexNum;
                graph->vertices[pos->tail].visited = 1; // 标记入队元素为已访问
            }
            pos = pos->next; // 移向下一个弧继续进行遍历
        }
    }
    free(queue); // 释放临时队列
}
void BFSListGraph(ListGraph *graph, int index) {
    if (graph) {
        printf("BFS Traversal: ");
        initVertexVisited(graph);
        BFSGraphVertices(graph, index);
        printf("\n");
    }
}
