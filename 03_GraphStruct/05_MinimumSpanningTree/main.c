#include <stdio.h>
#include <stdlib.h>
#include "Kruskal.h"

static void setupMatrixGraph(MatrixGraph *graph) { // 创建邻接矩阵式图结构
    char *names[] = {"A", "B", "C", "D", "E", "F", "G"};
    initMatrixGraph(graph, names, sizeof(names)/sizeof(names[0]), 0, 0); // 无向图, 默认权值为0
    addEdgeToGraph(graph, 0, 1, 12); // A - B: 12
    addEdgeToGraph(graph, 0, 5, 16); // A - F: 16
    addEdgeToGraph(graph, 0, 6, 14); // A - G: 14
    addEdgeToGraph(graph, 1, 2, 10); // B - C: 10
    addEdgeToGraph(graph, 1, 5, 7); // B - F: 7
    addEdgeToGraph(graph, 2, 3, 3); // C - D: 3
    addEdgeToGraph(graph, 2, 4, 5); // C - E: 5
    addEdgeToGraph(graph, 2, 5, 6); // C - F: 6
    addEdgeToGraph(graph, 3, 4, 4); // D - E: 4
    addEdgeToGraph(graph, 4, 5, 2); // E - F: 2
    addEdgeToGraph(graph, 4, 6, 8); // E - G: 8
    addEdgeToGraph(graph, 5, 6, 9); // F - G: 9
}
void test1() {
    printf("==========test1===========\n");
    MatrixGraph graph;
    setupMatrixGraph(&graph);
    printf("There are %d vertices and %d edges in the graph.\n", graph.vertexNum, graph.edgeNum);

    EdgeSet *edges = malloc(sizeof(EdgeSet) * graph.edgeNum); // 申请空间元素个数应为图中的总边数
    if (edges == NULL) {
        fprintf(stderr, "edges malloc failed!\n");
        return;
    }
    initEdgeSet(&graph, edges);
    sortEdgeSet(edges, graph.edgeNum);
    for (int i = 0; i < graph.edgeNum; i++) {
        printf("%s - %s: %d\n", graph.vertices[edges[i].begin].name, graph.vertices[edges[i].end].name, edges[i].weight);
    }

    EdgeSet *result = malloc(sizeof(EdgeSet) * (graph.vertexNum-1)); // 最小生成树的总边数 = 图中顶点数 - 1
    if (result == NULL) {
        fprintf(stderr, "result malloc failed!\n");
        free(edges); // 将已经申请空间的边集数组释放
        return;
    }
    int sum = KruskalAlgorithm(edges, graph.vertexNum, graph.edgeNum, result);
    printf("\n==Kruskal Minimum Spanning Tree==\n");
    for (int i = 0; i < graph.vertexNum-1; i++) {
        printf("%s - %s: %d\n", graph.vertices[result[i].begin].name, graph.vertices[result[i].end].name, result[i].weight);
    }
    printf("Total Weight: %d\n", sum);

    free(edges);
    free(result);
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}