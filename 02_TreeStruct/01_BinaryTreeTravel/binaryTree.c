#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

BinaryTree *createBinaryTree(TreeNode *root) {
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    if (tree == NULL) {
        fprintf(stderr, "tree malloc failed!\n");
        return NULL;
    }
    if (root) { // 当根节点存在时
        tree->count = 1;
        tree->root = root;
    }
    else {
        tree->count = 0;
        tree->root = NULL;
    }
    return tree;
}

TreeNode * createTreeNode(Element value) {
    TreeNode *new_node = malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return NULL;
    }
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right) {
    if (tree && parent) { // 当二叉树和父节点存在时
        if (left) { // 当左子节点存在时
            parent->left = left;
            tree->count++;
        }
        if (right) { // 当右子节点存在时
            parent->right = right;
            tree->count++;
        }
    }
}

void visitTreeNode(TreeNode *node) {
    if (node) // 当节点存在时
        printf("%c\t", node->data);
}

// 使用递归思想实现对二叉树节点的深度优先遍历
// 使用静态函数对外部隐藏
static void preorder(TreeNode *node) {
    // 前序遍历: 根左右
    if (node) { // 当节点存在时
        visitTreeNode(node);
        preorder(node->left);
        preorder(node->right);
    }
}
static void inorder(TreeNode *node) {
    // 中序遍历: 左根右
    if (node) {
        inorder(node->left);
        visitTreeNode(node);
        inorder(node->right);
    }
}
static void postorder(TreeNode *node) {
    // 后序遍历: 左右根
    if (node) {
        postorder(node->left);
        postorder(node->right);
        visitTreeNode(node);
    }
}

void preorderTraversal(BinaryTree *tree) {
    preorder(tree->root); // 从根节点开始进行递归遍历
    printf("\n");
}

void inorderTraversal(BinaryTree *tree) {
    inorder(tree->root);
    printf("\n");
}

void postorderTraversal(BinaryTree *tree) {
    postorder(tree->root);
    printf("\n");
}

// 使用队列实现对二叉树的广度优先遍历
/*
 *  1. 引入任务队列, 使根节点入队
 *  2. 从任务队列中取出一个节点并进行访问或处理
 *  3. 若取出的节点存在左右子节点, 则将其左右子节点入队
 */
void levelOrderTraversal(BinaryTree *tree) {
    // 此处不需要二次利用, 在栈上申请即可, 故使用循环顺序队列进行遍历元素的存储
    #define MaxQueueSize 8 // 定义队列最大容量
    TreeNode *queue[MaxQueueSize]; // 队列里元素应为节点地址

    int front = 0, rear = 0; // 初始化队列首位下标
    queue[rear] = tree->root; // 放入根节点
    rear = (rear+1) % MaxQueueSize; // 更新队尾下标

    while (front != rear) {
        TreeNode *node = queue[front]; // 取出队首下标所在的节点
        front = (front+1) % MaxQueueSize; // 更新队首下标
        visitTreeNode(node); // 对取出的节点进行访问
        if (node->left) { // 若节点具有左子树
            queue[rear] = node->left;
            rear = (rear+1) % MaxQueueSize;
        }
        if (node->right) { // 若节点具有右子树
            queue[rear] = node->right;
            rear = (rear+1) % MaxQueueSize;
        }
    }
    printf("\n");
}
