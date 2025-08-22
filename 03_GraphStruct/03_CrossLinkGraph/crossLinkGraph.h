#ifndef CROSS_LINK_GRAPH_H
#define CROSS_LINK_GRAPH_H

typedef struct _arc { // 弧结构
    int weight; // 权重值
    int tail; // 弧尾顶点下标
    int head; // 弧头顶点下标
    struct _arc *tail_next; // 指向 "同一顶点出发(弧尾顶点)的 出弧链表 " 的下一位置
    struct _arc *head_next; // 指向 "指向同一顶点(弧头顶点)的 入弧链表 " 的下一位置
} Arc;
typedef struct { // 顶点结构
    int id;
    char* name;
    Arc *in; // 入度指针, 作为某一条弧上的弧头顶点
    Arc *out; // 出度指针, 作为某一条弧上的弧尾顶点
} Vertex;
typedef struct { // 十字链表式图结构
    int vertexNum;
    int arcNum;
    Vertex *vertices;
} CrossListGraph;

CrossListGraph *createCrossListGraph(int n);
void releaseCrossListGraph(CrossListGraph *graph);
void initCrossListGraph(CrossListGraph *graph, char *names[]);
void addArcToGraph(CrossListGraph *graph, int tail, int head, int weight);
int vertexInDegree(const CrossListGraph *graph, int index); // 计算顶点的入度值
int vertexOutDegree(const CrossListGraph *graph, int index); // 计算顶点的出度值

#endif // CROSS_LINK_GRAPH_H
