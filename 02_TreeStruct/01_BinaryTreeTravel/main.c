#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

BinaryTree *initTree() {
    TreeNode *nodeA = createTreeNode('A');
    TreeNode *nodeB = createTreeNode('B');
    TreeNode *nodeC = createTreeNode('C');
    TreeNode *nodeD = createTreeNode('D');
    TreeNode *nodeE = createTreeNode('E');
    TreeNode *nodeF = createTreeNode('F');
    TreeNode *nodeG = createTreeNode('G');
    TreeNode *nodeH = createTreeNode('H');
    // TreeNode *nodeI = createTreeNode('I');
    // TreeNode *nodeJ = createTreeNode('J');
    TreeNode *nodeK = createTreeNode('K');

    BinaryTree *tree = createBinaryTree(nodeA); // 以A为根节点生成二叉树
    insertBinaryTree(tree, nodeA, nodeB, nodeE);
    insertBinaryTree(tree, nodeB,NULL, nodeC);
    insertBinaryTree(tree, nodeE, NULL, nodeF);
    insertBinaryTree(tree, nodeC, nodeD, NULL);
    insertBinaryTree(tree, nodeF, nodeG, NULL);
    insertBinaryTree(tree, nodeG, nodeH, nodeK);
    return tree;
}

void test1() {
    BinaryTree *tree = initTree();
    printf("There are %d elements in the tree:\n", tree->count);
    printf("Preorder Traversal:\t ");
    preorderTraversal(tree);
    printf("Inorder Traversal:\t  ");
    inorderTraversal(tree);
    printf("Postorder Traversal:\t");
    postorderTraversal(tree);
    printf("Level Order Traversal:\t");
    levelOrderTraversal(tree);
}

int main() {
    test1();
    return 0;
}