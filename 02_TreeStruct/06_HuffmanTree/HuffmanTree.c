#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanTree.h"

static void selectMinWeight(HuffmanTree tree, int n, int *index1, int *index2) { // 选择最小权重节点函数
    int temp = -1;
    for (int i = 0; i < n; i++) {
        if (tree[i].parent == 0) { // 寻找到第一个没有父节点的节点
            temp = i;
            break;
        }
    }
    for (int i = 1; i < n; i++) {
        if (tree[i].parent == 0 && tree[i].weight < tree[temp].weight) // 寻找第一个没有父节点的最小权重节点
            temp = i;
    }
    *index1 = temp;

    for (int i = 0; i < n; i++) {
        if (i != *index1 && tree[i].parent == 0) { // 需保证temp != index1, 否则最终可能将index1的值赋给index2
            temp = i;
            break;
        }
    }
    for (int i = 1; i < n; i++) {
        if (i != *index1 && tree[i].parent == 0 && tree[i].weight < tree[temp].weight) // 寻找第二个最小权重节点
            temp = i;
    }
    *index2 = temp;
}
HuffmanTree createHuffmanTree(const int *weightTable, int n) {
    int sum = 2*n-1; // n个叶子节点生成的哈夫曼树共有2n-1个节点
    HuffmanTree tree = malloc(sizeof(TreeNode) * sum);
    if (tree == NULL) {
        fprintf(stderr, "tree malloc failed!\n");
        return NULL;
    }
    for (int i = 0; i < sum; i++) {
        tree[i].parent = 0; // 初始父节点默认为0
        if (i < n) {
            tree[i].weight = weightTable[i]; // 将已知的权重进行初始化
            tree[i].left = -1; // 叶子节点不存在子树
            tree[i].right = -1;
        }
    }
    int index1, index2;
    for (int i = n; i < sum; i++) {
        selectMinWeight(tree, i, &index1, &index2); // 寻找到剩余节点中两个权重最小的
        // 更新子节点
        tree[index1].parent = i;
        tree[index2].parent = i;
        // 更新父节点
        tree[i].left = index1;
        tree[i].right = index2;
        tree[i].weight = tree[index1].weight + tree[index2].weight;
    }
    return tree;
}
#ifdef RECURSION
static void coding(HuffmanTree tree, int nodeIndex, HuffmanCode *codes, int *sum, int n, HuffmanCode temp) { // 此处的codes代表一个char*的集合, 需要加上星号*
    TreeNode *node = &tree[nodeIndex]; // 通过传入下标的方式在函数内部直接访问tree[nodeIndex], 避免栈空间的浪费, 且易于索引获取
    if (node->left == -1 && node->right == -1) { // 叶子节点(即带有信息的节点)
        temp[(*sum)] = '\0'; // 储存字符串的结束符; 编码的索引范围为[0, (*sum)-1], 故存储到(*sum)位置
        codes[nodeIndex] = malloc(sizeof(char) * ((*sum)+1) ); // 为每个codes[i]分配存储编码的字符数组内存
        if (codes[nodeIndex] == NULL) {
            fprintf(stderr, "code malloc failed!\n");
            return;
        }
        memcpy(codes[nodeIndex], temp, (*sum)+1); // 将临时存储的编码拷贝到编码表中
        return;
    }
    if (node->left >= 0) {
        temp[*sum] = '0';
        (*sum)++; // 通过指针解引用改变上层参数; 注意运算优先级: *sum++等价于*(sum++), 此处必须注明为(*sum)++
        coding(tree, node->left, codes, sum, n, temp);
        (*sum)--; // 回溯后撤回一位, 继续寻找右子树
    }
    if (node->right >= 0) {
        temp[*sum] = '1';
        (*sum)++;
        coding(tree, node->right, codes, sum, n, temp);
        (*sum)--;
    }
}
#else
#endif
HuffmanCode *createHuffmanCode(HuffmanTree tree, int n) {
    HuffmanCode *codes = malloc(sizeof(HuffmanCode) * n);
    if (codes == NULL) {
        fprintf(stderr, "codes malloc failed!\n");
        return NULL;
    }

#ifdef RECURSION
    int sum  = 0; // 记录编码长度
    // 哈夫曼编码最大长度不超过叶子节点数(n), 至少应分配n+1个字节(预留结束符\0的位置)
    HuffmanCode temp = malloc(sizeof(char) * (n+1)); // 设置临时编码记录; 若使用sizeof(HuffmanCode)则是申请的指针大小, 而非存储编码所需的字符数组大小
    if (temp == NULL) {
        fprintf(stderr, "temp malloc failed!\n");
        free(codes); // 释放已分配的codes, 防止内存泄漏
        return NULL;
    }
    coding(tree, 2*n-2, codes, &sum, n, temp); // 根节点是第2n-1个节点, 下标为2n-2
    free(temp); // 释放临时编码, 避免内存泄漏
#else
#endif
    return codes;
}