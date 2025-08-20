#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

typedef struct _arc { // 定义有向图中的弧(边)结构
    int tail; // 弧尾顶点的索引
    int weight; // 弧的权重
    struct _arc *next; // 指向下一条弧的地址
} Arc;
typedef struct {
    int id; // 顶点编号
    int visited; // 记录访问状态
    char* name; // 顶点名称
    Arc *firstArc; // 指向从当前顶点出发的第一条弧(即邻接弧链表的头节点)
} Vertex;
typedef struct {
    int vertexNum; // 记录顶点数
    int arcNum; // 记录弧数
    int directed; // 记录图是否有方向z
    Vertex *vertices; // 顶点集合
} ListGraph;

ListGraph *createListGraph(int n); // 在堆上申请邻接表图结构
void releaseListGraph(ListGraph *graph);
void initListGraph(ListGraph *graph, char *names[], int directed); // 对生成的图进行初始化; char *names[]: 等价于char **names, 存储char*类型的char*数组
void addArcToGraph(ListGraph *graph, int v1, int v2, int weight); // 向图中添加弧(v1: 起点, 弧尾tail; v2: 终点, 弧头head)
void initVertexVisited(ListGraph *graph); // 重置顶点访问状态
void visitVertexInGraph(Vertex *v); // 访问顶点函数
void DFSListGraph(ListGraph *graph, int index); // 深度优先遍历; index: 起点下标
void BFSListGraph(ListGraph *graph, int index); // 广度优先遍历

#endif // LIST_GRAPH_H
