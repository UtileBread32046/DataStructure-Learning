#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H
#include <stdlib.h>
typedef int Element;
typedef struct _node {
    Element data;
    struct _node *left;
    struct _node *right;
} TreeNode;
typedef struct {
    int count;
    TreeNode *root;
} SearchTree;

TreeNode *createTreeNode(Element val);
SearchTree *createSearchTree();
void releaseSearchTree(SearchTree *tree);
void insertSearchTree(SearchTree *tree, Element  val);
void visitTreeNode(TreeNode *node);
void inorderSearchTree(const SearchTree *tree); // 使用中序遍历检查二叉搜索树的结构(中序遍历结果必为递增数列)
int heightSearchTree(const SearchTree *tree); // 使用递归计算树的高度(最大值)
TreeNode *findTreeNode(const SearchTree *tree, Element val); // 查找二叉树中是否包含特定元素

#endif //SEARCH_TREE_H
