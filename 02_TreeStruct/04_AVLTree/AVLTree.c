#include "AVLTree.h"
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
    node->height = 1;
    return node;
}

AVLTree * createAVLTree() {
    AVLTree *tree = malloc(sizeof(AVLTree));
    if (tree == NULL) {
        fprintf(stderr, "tree malloc failed!\n");
        return NULL;
    }
    tree->count = 0;
    tree->root = NULL;
    return tree;
}

static void deleteTreeNode(AVLTree *tree, TreeNode *node) {
    if (node) {
        deleteTreeNode(tree, node->left);
        deleteTreeNode(tree, node->right);
        free(node);
        tree->count--;
    }
}
void releaseAVLTree(AVLTree *tree) {
    deleteTreeNode(tree, tree->root);
    printf("The tree has been cleared: %d element left.\n", tree->count);
    free(tree);
}

static int max(int a, int b) { // 自定义最大值函数
    return (a > b) ? a : b;
}
static int getHeight(TreeNode *node) {
    if (node)
        return node->height;
    return 0; // 若节点不存在, 则返回0 (防止访问空指针报错)
}
static void refreshHeight(TreeNode *node) { // 自定义刷新节点高度函数
    if (node)
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}
        /* 左旋操作 */
/* 1. 将x-y, y-Ly断开
 * 2. 将y往左上提, x往左下放
 * 3. 连接y-x, x-Ly
 *           x                                 y
 *         /   \                             /    \
 *       Lx   y        ----->      x     Ry
 *            /   \                       /  \
 *          Ly  Ry                  Lx  Ly
 */
static TreeNode *leftRotate(TreeNode *x) {
    TreeNode *y = x->right;
    x->right = y->left; // 将x指向Ly
    y->left = x;
    refreshHeight(x); // 更新x节点的高度(左右子树最大高度+1)
    refreshHeight(y); // 注意顺序, 一定要先更新x再更新y (x此时是y的左子树)
    return y; // 返回新的根节点
}
        /* 右旋操作 */
/* 1. 将x-y, y-Ry断开
 * 2. 将y往右上提, x往右下放
 * 3. 连接y-x, x-Ry
 *         x                                 y
 *       /   \                              /   \
 *      y    Rx     ----->       Ly    x
 *    /   \                                     /   \
 *   Ly  Ry                              Ry  Rx
 */
static TreeNode *rightRotate(TreeNode *x) {
    TreeNode *y = x->left;
    x->left = y->right;
    y->right = x;
    refreshHeight(x);
    refreshHeight(y);
    return y;
}
static int getBalance(TreeNode *node) { // 获取当前节点平衡因子
    if (node)
        return getHeight(node->left) - getHeight(node->right);
}
static TreeNode *rotateOperation(TreeNode *node, int balance, int val) { // 自定义旋转操作函数
    if (balance > 1) {
        if (val > node->left->data) // LR
            node->left = leftRotate(node->left); // LR: 先左旋左子树, 转化为LL(若为LL则无此步骤)
        return rightRotate(node); // LL: 右旋根节点
    }
    if (balance < -1) {
        if (val < node->right->data) // RL
            node->right = rightRotate(node->right);
        return leftRotate(node); // RR
    }
    return node; // 节点正常, 不执行操作
}
static TreeNode *insertTreeNode(AVLTree *tree, TreeNode *node, Element val) {
    // 使用递归逐级传递指针完成插入操作
    if (node == NULL) {
        tree->count++;
        return createTreeNode(val); // 当移动到空节点时, 返回新创建的节点地址
    }
    if (val < node->data)
        node->left = insertTreeNode(tree, node->left, val); // 左子树插入
    else if (val > node->data)
        node->right = insertTreeNode(tree, node->right, val); // 右子树插入
    // 更新节点高度信息
    refreshHeight(node); // 当前节点在回归的过程, 需依次更新该路径中节点的高度, 同时检测平衡因子, 发现失衡节点并进行处理
    // 计算平衡因子进行旋转
    int balance = getBalance(node);
    return rotateOperation(node, balance, val); // 进行旋转操作
}
void insertAVLTree(AVLTree *tree, Element val) {
    if (tree->root)
        tree->root = insertTreeNode(tree, tree->root, val); // 注意别忘了将插入的结果返回根节点, 防止旋转操作导致树的根节点发生变化
    else { // 当树不存在时
        tree->root = createTreeNode(val);
        tree->count++;
    }
}

void visitTreeNode(const TreeNode *node) {
    if (node)
        printf("<%d: %d>   ", node->data, node->height); // 输出节点信息的格式为: <数据: 高度>
}

static void inorderTraversal(const TreeNode *node) {
    if (node) {
        inorderTraversal(node->left);
        visitTreeNode(node);
        inorderTraversal(node->right);
    }
}
void inorderAVLTree(const AVLTree *tree) {
    if (tree) {
        printf("There are %d elements in the tree:\n", tree->count);
        inorderTraversal(tree->root);
        printf("\n");
    }
}

int heightAVLTree(const AVLTree *tree) {
    return getHeight(tree->root);
}
