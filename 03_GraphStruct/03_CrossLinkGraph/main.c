#include <stdio.h>
#include "crossLinkGraph.h"

static void printDegrees(CrossListGraph *graph) {
    printf("Vertex  In-Degree  Out-Degree\n");
    int inSum = 0, outSum = 0;
    for (int i = 0; i < graph->vertexNum; i++) {
        int inDegree = vertexInDegree(graph, i);
        int outDegree = vertexOutDegree(graph, i);
        inSum += inDegree, outSum += outDegree;
        printf("  %s \t\t %d \t\t %d\n", graph->vertices[i].name, inDegree, outDegree);
    }
    printf(" sum\t\t%d\t\t%d\n", inSum, outSum);
}
void test1() {
    printf("==========test1===========\n");
    int n = 4;
    char *names[] = {"v1", "v2", "v3", "v4"};
    CrossListGraph *graph = createCrossListGraph(n);
    if (graph == NULL) {
        return;
    }
    initCrossListGraph(graph, names);
    addArcToGraph(graph, 0, 3, 1);
    addArcToGraph(graph, 1, 0, 1);
    addArcToGraph(graph, 1, 2, 1);
    addArcToGraph(graph, 2, 0, 1);
    addArcToGraph(graph, 2, 1, 1);

    printf("There are %d vertices and %d arcs in the graph:\n", graph->vertexNum, graph->arcNum);
    printDegrees(graph);

    releaseCrossListGraph(graph);
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}