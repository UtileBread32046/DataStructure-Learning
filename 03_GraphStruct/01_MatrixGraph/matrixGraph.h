#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H
#define MAX_SIZE 20 // 定义申请数组的最大长度
#define INF 1E3 // 定义权重的最大值(即边的权重不可能超过该值); 1E3 = 10^3 = 1000

// 定义邻接矩阵的顶点结构类型, 用于表示顶点的信息
typedef struct {
    int id; // 顶点编号
    char* name; // 顶点名称
} MatrixVertex;
typedef int MatrixEdge; // 定义邻接矩阵的边类型(记录边的权重值)
// 图的邻接矩阵表示法
typedef struct {
    int vertexNum; // 记录实际的顶点个数
    int edgeNum; // 记录边个数
    int directed; // 记录图是否有方向
    MatrixVertex vertices[MAX_SIZE]; // 定义顶点集
    MatrixEdge edges[MAX_SIZE][MAX_SIZE]; // 定义边集(邻接矩阵)
} MatrixGraph;

void initMatrixGraph(MatrixGraph *graph, char *names[], int num, int directed, int edgeValue); // 在栈上初始化图的信息; edgeValue: 边的值
void addEdgeToGraph(MatrixGraph *graph, int v1, int v2, int weight); // 使用顶点的下标添加边(顶点1, 顶点2, 权值)
void visitVertexInGraph(MatrixVertex *v); // 访问顶点函数
void initVisitedVertices(int *visited); // 初始化/重置 存储已访问顶点的列表
void DFSMatrixGraph(MatrixGraph *graph, int index); // 深度优先搜索; index: 起点下标
void BFSMatrixGraph(MatrixGraph *graph, int index); // 广度优先搜索

#endif //MATRIX_GRAPH_H
