#ifndef THREAD_TREE_H
#define THREAD_TREE_H

typedef int Element;
typedef struct _node {
    Element data;
    struct _node *left;
    struct _node *right;
    int lTag; // left tag: 左标记, 0表示left指向左子树, 1表示left指向前驱节点
    int rTag; // right tag: 右标记, 0表示right指向右子树, 1表示right指向后继节点
} TreeNode;
typedef struct {
    TreeNode *root;
    int count;
} ThreadTree;

TreeNode *createTreeNode(Element val);
ThreadTree *createThreadTree(TreeNode *root);
void releaseThreadTree(ThreadTree *tree);
void insertThreadTree(ThreadTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right);
void visitTreeNode(TreeNode *node);
// 对二叉树进行线索化, 将原本的隐式递归回溯转化为显示的指针回溯, 节省时间和内存开销
void inorderThreadingTree(ThreadTree *tree); // 进行中序线索化: 按照中序遍历的结果将每个节点的左右子树分别指向其前驱后继节点
void inorderThreadingTraversal(ThreadTree *tree); // 对线索化后的树进行遍历

#endif //THREAD_TREE_H
