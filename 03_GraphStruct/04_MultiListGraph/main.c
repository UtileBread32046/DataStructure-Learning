#include <stdio.h>
#include "multiListGraph.h"

void test1() {
    printf("==========test1===========\n");
    int n = 5;
    char *names[] = {"v1", "v2", "v3", "v4", "v5"};
    MultiListGraph *graph = createMultiListGraph(n);
    if (graph == NULL)
        return;
    initMultiListGraph(graph, names);
    addEdgeToGraph(graph, 0, 1, 1);
    addEdgeToGraph(graph, 0, 3, 1);
    addEdgeToGraph(graph, 1, 2, 1);
    addEdgeToGraph(graph, 1, 4, 1);
    addEdgeToGraph(graph, 2, 3, 1);
    addEdgeToGraph(graph, 2, 4, 1);
    deleteEdgeFromGraph(graph, 2, 4);

    printf("There are %d vertices and %d edges in the graph:\n", graph->vertexNum, graph->edgeNum);
    showMultiListGraph(graph);
    releaseMultiListGraph(graph);
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}