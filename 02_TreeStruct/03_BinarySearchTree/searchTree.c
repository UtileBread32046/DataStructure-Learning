#include "searchTree.h"
#include <stdio.h>
#include <stdlib.h>
// #define RECURSION // 调用递归函数(注释掉改行代码即可开启非递归)

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
#ifdef RECURSION // 采用条件编译的方式选择递归或非递归的函数
    if (tree) {
        tree->root = insertTreeNode(tree->root, val); // 从根节点开始插入新节点, 一路返回插入后的地址路径
        tree->count++;
    }
#else // 非递归模式
    TreeNode *cur = tree->root; // 从根节点出发的当前节点指针
    TreeNode *pre = NULL; // 引入辅助指针, 指向前一位的节点指针, 初始为空
    while (cur) { // 当节点存在时
        pre = cur; // 先将前一位指针移动到当前节点位置, 再移动当前的指针
        if (val < cur->data)
            cur = cur->left;
        else if (val > cur->data)
            cur = cur->right;
        else
            return; // 默认二叉树中不可包含重复元素, 若有则直接返回
    }
    TreeNode *node = createTreeNode(val);
    if (pre) { // 此时跳出循环且pre存在, 则为正常位置
        if (val < pre->data)
            pre->left = node;
        else
            pre->right = node;
    } else { // 当pre为空时, 则未进入while循环, 即证明树中不存在根节点
        tree->root = node;
    }
    tree->count++;
#endif
}

static TreeNode *maxValueLeft(TreeNode *node) {
    // 在删除度为2的节点时, 若选择前驱节点法, 则应找到左子树中的最右侧节点, 即为中序遍历结果中所需要的前驱节点
    while (node->right) {
        node = node->right;
    } // 在跳出此循环后, node便已达到最右侧
    return node;
}
static TreeNode *minValueRight(TreeNode *node) {
    // 同理, 若选择后继节点法, 则应找到右子树中的最左侧节点, 即为所需要的后继节点
    while (node->left) {
        node = node->left;
    }
    return node;
}
static TreeNode *deleteTreeNode(SearchTree *tree, TreeNode *node, Element val) {
    if (node == NULL) { // 当节点为空时即为未找到
        printf("Find value %d failed!\n", val);
        return NULL;
    }
    if (val < node->data) // 当需要删除的值小于当前节点数值时
        node->left = deleteTreeNode(tree, node->left, val); // 寻找左子树(同时传回地址)
    else if (val > node->data)
        node->right = deleteTreeNode(tree, node->right, val);
    else { // 当值恰好相等时
        TreeNode *temp = NULL; // 设置一个临时节点
        if (node->left == NULL) { // 当左子树为空(不存在)时, 节点只可能存在或不存在右子树, 当前节点的度为0或1(不算父节点)
            temp = node->right; // 将temp赋值为右子树而非node自身, 防止free掉node后temp成为野指针
            free(node); // 执行删除操作, 释放当前节点
            tree->count--;
            return temp; // 返回右子树状态(空或右子树的根)
        }
        if (node->right == NULL) { // 在上一个if判断成立返回后剩下的情况下(即左子树一定存在), 若右子树不存在, 当前节点的度为1
            temp = node->left;
            free(node);
            tree->count--;
            return temp; // 返回左子树状态
        }
        // 当以上两种状态均返回后, 剩下的状态即为左右子树均存在的情况, 当前节点的度为2
        /* 前驱节点法 */
        temp = maxValueLeft(node->left);
        node->data = temp->data; // 用得到的前驱/后继节点的值覆盖掉当前节点
        node->left = deleteTreeNode(tree, node->left, temp->data); // 从左子树路径再次进行递归, 将左子树中的重复值删除(该点因为位于最左子树的最右侧, 故度必为0或1)
        /* 后继节点法 */
        // temp = minValueRight(node->right);
        // node->data = temp->data;
        // node->right = deleteTreeNode(tree, node->right, temp->data);
    }
    return node; // 将更新后的当前节点返回上级
}
void deleteSearchTree(SearchTree *tree, Element val) {
#ifdef RECURSION
    if (tree)
        deleteTreeNode(tree, tree->root, val);
#else //  非递归式
    TreeNode *pre = NULL;
    TreeNode *node = tree->root;
    while (node) { // 寻找数据相符的节点
        if (val < node->data) {
            pre = node; // 移动前置节点指针
            node = node->left;
        } else if (val > node->data) {
            pre = node;
            node = node->right;
        } else
            break;
    }

    if (node == NULL) { // 未找到节点
        printf("Find value %d failed!\n", val);
        return;
    }
    TreeNode *temp = NULL;
    if (node->left == NULL) { // 当左子树为空时, 节点度数为0或1
        temp = node->right;
        pre->right = temp; // 连接右子树
        free(node);
        tree->count--;
    } else if (node->right == NULL) {
        temp = node->left;
        pre->left = temp;
        free(node);
        tree->count--;
    } else { // 此时节点度数为2
        temp = node->right; // 移动到右子树的根节点
        TreeNode *parent =  NULL;
        while (temp->left) { // 寻找后继节点及其父节点
            parent = temp;
            temp = temp->left;
        }
        if (parent) // 父节点的左子树为后继节点, 而后继节点只可能存在右子树
            parent->left = temp->right;
        else // 若右子树根节点即为最小值
            node->right = temp->right;
        free(temp);
        tree->count--;
    }
#endif
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
