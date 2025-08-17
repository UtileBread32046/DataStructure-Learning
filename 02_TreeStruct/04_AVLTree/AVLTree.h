#ifndef AVL_TREE_H
#define AVL_TREE_H
typedef int Element;
typedef struct _node {
    Element data;
    struct _node *left;
    struct _node *right;
    int height; // 记录当前节点高度(左右子树高度的最大值+1), 用于计算平衡二叉树中的平衡因子(左子树高度 - 右子树高度)
} TreeNode;
typedef struct {
    int count;
    TreeNode *root;
} AVLTree;

TreeNode *createTreeNode(Element val);
AVLTree *createAVLTree();
void releaseAVLTree(AVLTree *tree);
void insertAVLTree(AVLTree *tree, Element val);
void visitTreeNode(const TreeNode *node);
void inorderAVLTree(const AVLTree *tree); // 使用中序遍历对平衡二叉树进行遍历
int heightAVLTree(const AVLTree *tree); // 获取平衡二叉树的高度

#endif //AVL_TREE_H
