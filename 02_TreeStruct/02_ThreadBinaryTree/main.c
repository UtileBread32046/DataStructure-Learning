#include <stdio.h>
#include "threadTree.h"

ThreadTree *createBinaryTree() {
    TreeNode *nodeA = createTreeNode('A');
    TreeNode *nodeB = createTreeNode('B');
    TreeNode *nodeC = createTreeNode('C');
    TreeNode *nodeD = createTreeNode('D');
    TreeNode *nodeE = createTreeNode('E');
    TreeNode *nodeF = createTreeNode('F');
    TreeNode *nodeH = createTreeNode('H');
    TreeNode *nodeG = createTreeNode('G');
    TreeNode *nodeK = createTreeNode('K');
    ThreadTree *tree = createThreadTree(nodeA);
    insertThreadTree(tree, nodeA,nodeB, nodeE);
    insertThreadTree(tree, nodeB, NULL, nodeC);
    insertThreadTree(tree, nodeE, NULL, nodeF);
    insertThreadTree(tree, nodeC, nodeD, NULL);
    insertThreadTree(tree, nodeF, nodeG, NULL);
    insertThreadTree(tree, nodeG, nodeH, nodeK);
    return tree;
}

void test1() {
    ThreadTree *tree = createBinaryTree();
    printf("There are %d elements in the tree:\n", tree->count);
    inorderThreadingTree(tree);
    printf("Inorder Threading Traversal:\t");
    inorderThreadingTraversal(tree);
    printf("\n");
    releaseThreadTree(tree);
}

int main() {
    test1();
    return 0;
}
