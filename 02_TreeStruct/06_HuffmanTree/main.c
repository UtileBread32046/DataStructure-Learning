#include <stdio.h>
#include "HuffmanTree.h"

void test1() {
    printf("==========test1===========\n");
    int weightTable[] = {5, 29, 7, 8, 14, 23, 3, 11};
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int n = sizeof(weightTable) / sizeof(weightTable[0]);
    HuffmanTree tree = createHuffmanTree(weightTable, n);
    printf("weight\t parent\t left\t right\t\n");
    for (int i = 0; i < 2*n-1; i++) {
        printf(" %d\t\t%d\t%d\t%d\n", tree[i].weight, tree[i].parent, tree[i].left, tree[i].right);
    }

    printf("\nHuffmanCode: ");
#ifdef RECURSION
    printf("__Recursion Mode__\n");
#else
    printf("__No-Recursion Mode__\n");
#endif
    HuffmanCode *codes = createHuffmanCode(tree, n);
    for (int i = 0; i < n; i++) {
        printf("%c:  %s\n", alphabet[i], codes[i]);
    }
    printf("\n");
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}