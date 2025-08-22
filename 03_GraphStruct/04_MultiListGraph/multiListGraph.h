#ifndef MULTI_LIST_GRAPH_H
#define MULTI_LIST_GRAPH_H

typedef struct _edge { // 边结构
    int iVertex; // 连接下标为i的顶点
    int jVertex; // 连接下标为j的顶点
    int weight; // 权重值
    int visited; // 标记是否已访问(打印)
    struct _edge *iNext; // 指向顶点i的下一条边
    struct _edge *jNext; // 指向顶点j的下一条边
} Edge;
typedef struct { // 顶点结构
    int id;
    char *name;
    Edge *firstEdge; // 指向该顶点所关联的边的链表集合的首地址
} Vertex;
typedef struct { // 邻接多重表图结构
    int vertexNum;
    int edgeNum;
    Vertex *vertices;
} MultiListGraph;

MultiListGraph *createMultiListGraph(int n);
void releaseMultiListGraph(MultiListGraph *graph);
void initMultiListGraph(MultiListGraph *graph, char *names[]);
void addEdgeToGraph(MultiListGraph *graph, int vi, int vj, int weight);
void deleteEdgeFromGraph(MultiListGraph *graph, int vi, int vj); // 删除图中指定两点间的边
void showMultiListGraph(MultiListGraph *graph);

#endif //MULTI_LIST_GRAPH_H
