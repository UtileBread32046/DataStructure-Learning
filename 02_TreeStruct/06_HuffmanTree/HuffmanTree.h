#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#define RECURSION // 递归编码模式, 注释掉可开启非递归

// 采用顺序存储的方式, 定义哈夫曼树的节点结构, 并使用下表索引来标识不同的节点
typedef struct {
    int weight; // 节点权重, 用于表示在编码中的出现次数
    int parent; // 指向父节点的索引
    int left; // 指向左子树的索引
    int right; // 指向右子树的索引
} TreeNode, *HuffmanTree; // 定义为节点结构和表头结构(表头默认为指针类型, 不需要额外加星号*)
typedef char* HuffmanCode; // 定义哈夫曼编码类型(指向字符串的指针)

HuffmanTree createHuffmanTree(const int *weightTable, int n); // 通过传入的权重表和元素个数进行创建, 返回树的根节点指针
HuffmanCode *createHuffmanCode(HuffmanTree tree, int n); // 根据哈夫曼树创建哈夫曼编码, 返回一个存储多个字符串编码的数组(首地址)

#endif //HUFFMAN_TREE_H
