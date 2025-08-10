#include <stdio.h>
#include <stdlib.h>
#include "threadTree.h"

TreeNode *createTreeNode(Element val) {
    TreeNode *node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "node malloc failed!\n");
        return NULL;
    }
    node->data = val;
    node->left = node->right = NULL;
    node->lTag = node->rTag = 0;
    return node;
}

ThreadTree *createThreadTree(TreeNode *root) {
    ThreadTree *tree = malloc(sizeof(ThreadTree));
    if (tree == NULL) {
        fprintf(stderr, "tree malloc failed!\ n");
        return NULL;
    }
    if (root) { // 当根节点存在时
        tree->root = root;
        tree->count = 1;
    } else {
        tree->root = NULL;
        tree->count = 0;
    }
    return tree;
}

static void freeTreeNode(ThreadTree *tree, TreeNode *node) {
    // 通过后序遍历, 使用递归完成释放操作
    if (node) {
        if (node->lTag == 0) // 注意判断是否存在真实左右子树
            freeTreeNode(tree, node->left);
        if (node->rTag == 0)
            freeTreeNode(tree, node->right);
        free(node);
        tree->count--;
    }
}

void releaseThreadTree(ThreadTree *tree) {
    freeTreeNode(tree, tree->root);
    printf("The tree has been cleared: %d element left.\n", tree->count);
}

void insertThreadTree(ThreadTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right) {
    if (tree && parent) { // 当树存在且明确父节点时
        parent->left = left; // 更新父节点的左右指针
        parent->right = right;
        if (left)
            tree->count++;
        if (right)
            tree->count++;
    }
}

void visitTreeNode(TreeNode *node) {
    if (node) // 当节点存在时
        printf("%c\t", node->data);
}
static TreeNode *pre = NULL; // 静态全局指针(用于指向中序遍历中当前节点的前驱节点, 比当前节点慢一拍)
static void inorderThread(TreeNode *node) { // 静态函数, 用于进行单个节点的线索化连接
    if (node) { // 当节点存在时
        // 中序遍历: 左根右, 当递归到最左侧节点时再进行处理
        inorderThread(node->left); // 拆分任务, 对左子树进行线索化, 直到分解到最左端
        if (node->left == NULL) { // 若当前节点的左子树不存在, 连接前驱节点
            node->left = pre; // 使节点的左指针指向上一个被访问节点
            node->lTag = 1; // 标记为线索, 指向前驱节点
        }
        if (pre && pre->right == NULL) { // 若中序遍历中当前节点的前驱节点存在且前驱节点的右子树不存在时, 将前驱节点连接到其后继(即当前节点)
            pre->right = node; // 将前驱节点链接到当前节点
            pre->rTag = 1; // 标记为线索, 指向后继节点
        }
        pre = node; // 处理完当前节点的前驱以及前驱节点的后继后, 移动前驱节点的指针, 向后移一位; 右子树的前驱节点就是当前节点
        inorderThread(node->right); // 对右子树进行线索化
    }
}
void inorderThreadingTree(ThreadTree *tree) {
    if (tree) {
        inorderThread(tree->root);
    }
}

void inorderThreadingTraversal(ThreadTree *tree) {
    // 遍历时即按照中序遍历的步骤: 先移动到当前根节点的最左侧节点, 按照线索依次进行遍历, 再移动到右子树作为新的根节点循环操作
    TreeNode *node = tree->root;

    /* 法一 */
    // while (node->lTag == 0)
    //     node = node->left;
    // while (node) {
    //     visitTreeNode(node);
    //     if (node->rTag == 1)
    //         node = node->right;
    //     else {
    //         node = node->right;
    //         if (node) { // 注意判断移动到右子树时新的根节点是否存在
    //             while (node->lTag == 0 && node->left != NULL)
    //                 node = node->left;
    //         }
    //     }
    // }

    /* 法二 */
    while (node) { // 当节点存在时
        while (node->lTag == 0)
            node = node->left; // 移动到最左侧节点(线索化后的首个节点)
        visitTreeNode(node); // 访问该节点
        while (node->rTag == 1 && node->right) { // 沿线索向右遍历(当线索存在且后继节点存在时)
            node = node->right;
            visitTreeNode(node);
        }
        node = node->right; // 当线索断开为右子树时, 以右子树为新的根节点, 重新开始循环, 直到右子树不存在
    }
}
