#include <stdio.h>
#include "matrixGraph.h"

void test1() {
    printf("==========test1===========\n");
    MatrixGraph graph;
    char* names[] = {"v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"};
    initMatrixGraph(&graph, names, sizeof(names)/sizeof(names[0]), 0, 0);
    addEdgeToGraph(&graph, 0, 1, 1);
    addEdgeToGraph(&graph, 0, 2, 1);
    addEdgeToGraph(&graph, 1, 3, 1);
    addEdgeToGraph(&graph, 1, 4, 1);
    addEdgeToGraph(&graph, 2, 5, 1);
    addEdgeToGraph(&graph, 2, 6, 1);
    addEdgeToGraph(&graph, 3, 7, 1);
    addEdgeToGraph(&graph, 4, 7, 1);
    addEdgeToGraph(&graph, 5, 6, 1);

    printf("There are %d vertices and %d edges in the graph:\n", graph.nodeNum, graph.edgeNum);
    DFSMatrixGraph(&graph, 0);
    BFSMatrixGraph(&graph, 0);
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}