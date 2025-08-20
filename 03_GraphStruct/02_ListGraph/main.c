#include <stdio.h>
#include "listGraph.h"

void test1() {
    printf("==========test1===========\n");
    int n = 5;
    char *names[] = {"A", "B", "C", "D", "E"};
    ListGraph *graph = createListGraph(n);
    initListGraph(graph, names, 1); // 有向图
    addArcToGraph(graph, 0, 4, 1);
    addArcToGraph(graph, 0, 3, 1);
    addArcToGraph(graph, 0, 1, 1);
    addArcToGraph(graph, 1, 4, 1);
    addArcToGraph(graph, 1, 2, 1);
    addArcToGraph(graph, 2, 0, 1);
    addArcToGraph(graph, 3, 2, 1);

    printf("There are %d vertices and %d arcs in the graph:\n", graph->vertexNum, graph->arcNum);
    DFSListGraph(graph, 0);
    BFSListGraph(graph, 0);

    releaseListGraph(graph);
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}