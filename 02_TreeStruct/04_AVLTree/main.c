#include <stdio.h>
#include "AVLTree.h"

void test1() {
    printf("==================test1====================\n");
    AVLTree *tree = createAVLTree();
    Element data[] = {10, 20, 30, 40, 50, 60, 68, 80, 25, 7, 55}; // 测试用数据集
    for (size_t i = 0; i < sizeof(data)/sizeof(data[0]); i++)
        insertAVLTree(tree, data[i]);
    inorderAVLTree(tree);
    printf("Tree Height: %d\n", heightAVLTree(tree));
    releaseAVLTree(tree);
}

int main() {
    test1();
    printf("===========================================\n");
    return 0;
}