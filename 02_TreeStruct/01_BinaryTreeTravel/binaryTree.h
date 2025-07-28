#ifndef BINARY_TREE_H
#define BINARY_TREE_H
typedef int Element;
typedef struct _node{
    Element data;
    struct _node *left; // 左子节点指针
    struct _node *right; // 右子节点指针
} TreeNode;
typedef struct {
    TreeNode *root; // 根节点指针
    int count;
} BinaryTree;

BinaryTree *createBinaryTree(TreeNode *root); // 传入一个根节点, 从根节点开始生成树
TreeNode *createTreeNode(Element value); // 产生新节点
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right); // 传入四个参数(二叉树, 父节点, 左子节点, 右子节点)进行插入操作
void visitTreeNode(TreeNode *node); // 自定义访问节点时将执行的操作
// 以下三种遍历方式均属于 DFS(Depth-First Search: 深度优先遍历) 的一种实现方式
void preorderTraversal(BinaryTree *tree); // 前序遍历
void inorderTraversal(BinaryTree *tree); // 中序遍历
void postorderTraversal(BinaryTree *tree); // 后序遍历
// 层序遍历属于 BFS(Breadth-First Search)
void levelOrderTraversal(BinaryTree *tree); // 层序遍历

#endif //BINARY_TREE_H
