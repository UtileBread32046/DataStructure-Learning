#include "searchTree.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode *createTreeNode(Element val) {
    TreeNode *node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "node malloc failed!\n");
        return NULL;
    }
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

SearchTree * createSearchTree() {
    SearchTree *tree = malloc(sizeof(SearchTree));
    if (tree == NULL) {
        fprintf(stderr, "tree malloc failed!\n");
        return NULL;
    }
    tree->count = 0;
    tree->root = NULL;
    return tree;
}

static void freeTreeNode(SearchTree *tree, TreeNode *node) {
    if (node) {
        freeTreeNode(tree, node->left);
        freeTreeNode(tree, node->right);
        free(node);
        tree->count--;
    }
}

void releaseSearchTree(SearchTree *tree) {
    freeTreeNode(tree, tree->root);
    printf("The tree has been cleared: %d elements left.\n", tree->count);
}

static TreeNode *insertTreeNode(TreeNode *node, Element val) {
    if (node == NULL) // 当递归至空节点(即可进行插入操作时)
        return createTreeNode(val); // 将传入的数据参数存储为一个新节点并返回给上一级(即插入当前节点)
    // 使用递归/分治思想, 判断要插入的元素与根节点的大小, 从而拆解任务
    // 原则上二叉搜索树中不存在重复节点
    if (val < node->data) { // 当插入的元素比当前根节点小时
        node->left = insertTreeNode(node->left, val); // 转化为左子树的任务, 使用返回值更新左子树
    } else if (val > node->data) {
        node->right = insertTreeNode(node->right, val);
    }
    return node; // 当node != NULL时, 需要将当前节点作为子树传递给上一层
}
void insertSearchTree(SearchTree *tree, Element val) {
    if (tree) {
        tree->root = insertTreeNode(tree->root, val); // 从根节点开始插入新节点, 一路返回插入后的地址路径
        tree->count++;
    }
}

void visitTreeNode(TreeNode *node) {
    printf("%d\t", node->data);
}

static void inorderTraversal(TreeNode *node) {
    if (node) {
        inorderTraversal(node->left);
        visitTreeNode(node);
        inorderTraversal(node->right);
    }
}
void inorderSearchTree(const SearchTree *tree) {
    printf("There are %d elements in the tree:\t", tree->count);
    inorderTraversal(tree->root);
}

static int heightTreeNode(TreeNode *node) { // 计算当前节点的高度(深度)
    if (node == NULL) { // 当当前节点不存在(即越过叶子节点时)
        return 0; // 返回高度的初始值
    }
    // 不断向上返回下一层的子树高度
    int leftHeight = heightTreeNode(node->left); // 记录左子树高度
    int rightHeight = heightTreeNode(node->right); // 记录右子树高度
    // 每个节点的高度 = 左右子树中最高的高度 + 1
    if (leftHeight > rightHeight) // 当左子树高度大于右子树时, 返回自增后的左子树
        return ++leftHeight; // 使用前缀++, 先增大值再进行返回
    return ++rightHeight;
}
int heightSearchTree(const SearchTree *tree) {
    return heightTreeNode(tree->root);
}

TreeNode *findTreeNode(const SearchTree *tree, Element val) {
    TreeNode *node = tree->root;
    while (node) {
        if (val > node->data) { // 当查找值 > 节点值时
            node = node->right; // 跳转到右子树进行查找
        } else if (val < node->data) {
            node = node->left;
        } else {
            break;
        }
    }
    return node;
}
