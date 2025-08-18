#ifndef QUICK_UNION_H
#define QUICK_UNION_H
#define PATH_COMPRESS // 定义路径压缩模式的宏, 注释掉该行代码可采用非压缩
// #define RECURSION // 定义递归式宏
#define STACK // 定义栈式宏
// 注释掉上两个宏可采用非递归模式

typedef int Element;
typedef struct {
    int n;
    Element *data;
    int *parent; // 存储指向父节点的指针
    int *size; // 存储空间大小(某个根节点下的总节点数)
} QuickUnionSet;
// 使用链式栈时需要定义节点
typedef struct _stack_node {
    int index; // 用于存储索引
    struct _stack_node *next;
} StackNode;

QuickUnionSet *createQuickUnionSet(int n);
void releaseQuickUnionSet(QuickUnionSet *set);
void initQuickUnionSet(QuickUnionSet *set, Element *data, int n);
int isSameGroup(const QuickUnionSet *set, Element a, Element b);
void uniteGroup(QuickUnionSet *set, Element a, Element b);

#endif //QUICK_UNION_H
