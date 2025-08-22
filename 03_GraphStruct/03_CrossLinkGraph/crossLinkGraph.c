#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crossLinkGraph.h"

CrossListGraph * createCrossListGraph(int n) {
    CrossListGraph *graph = malloc(sizeof(CrossListGraph));
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
    graph->arcNum = 0;
    return graph;
}

void releaseCrossListGraph(CrossListGraph *graph) {
    if (graph) {
        if (graph->vertices) {
            for (int i = 0; i < graph->vertexNum; i++) {
                Arc *inArc = graph->vertices[i].in; // 根据入度或出度对弧空间依次进行释放
                Arc *temp = NULL;
                while (inArc) {
                    temp = inArc;
                    inArc = inArc->head_next;
                    free(temp);
                    graph->arcNum--;
                }
            }
            graph->vertexNum = 0;
            free(graph->vertices);
        }
        printf("The graph has been cleared: %d vertex and %d arc left.\n", graph->vertexNum, graph->arcNum);
        free(graph);
    }
}

void initCrossListGraph(CrossListGraph *graph, char *names[]) {
    if (graph) {
        for (int i = 0; i < graph->vertexNum; i++) {
            graph->vertices[i].id = i;
            graph->vertices[i].name = names[i];
            graph->vertices[i].in = graph->vertices[i].out = NULL;
        }
    }
}

void addArcToGraph(CrossListGraph *graph, int tail, int head, int weight) {
    Arc *new_arc = malloc(sizeof(Arc));
    if (new_arc == NULL) {
        fprintf(stderr, "arcs malloc failed!\n");
        return;
    }
    new_arc->weight = weight;
    graph->arcNum++;
    // 使用头插法
    new_arc->head = head; // 弧头, 入度
    new_arc->head_next = graph->vertices[head].in;
    graph->vertices[head].in = new_arc;
    new_arc->tail = tail; // 弧尾, 出度
    new_arc->tail_next = graph->vertices[tail].out;
    graph->vertices[tail].out = new_arc;
}

int vertexInDegree(const CrossListGraph *graph, int index) {
    if (graph) {
        int count = 0;
        Arc *arc = graph->vertices[index].in; // 选取入度弧
        while (arc) {
            count++;
            arc = arc->head_next; // 沿入度的弧链表进行遍历
        }
        return count;
    }
    return 0;
}

int vertexOutDegree(const CrossListGraph *graph, int index) {
    if (graph) {
        int count = 0;
        Arc *arc = graph->vertices[index].out; // 选取出度弧
        while (arc) {
            count++;
            arc = arc->tail_next; // 沿出度的弧链表进行遍历
        }
        return count;
    }
    return 0;
}