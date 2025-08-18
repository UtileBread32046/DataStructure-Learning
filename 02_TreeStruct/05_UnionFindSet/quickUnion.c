#include <stdio.h>
#include <stdlib.h>
#include "quickUnion.h"

QuickUnionSet *createQuickUnionSet(int n) {
    QuickUnionSet *set = malloc(sizeof(QuickUnionSet));
    if (set == NULL) {
        fprintf(stderr, "set malloc failed!\n");
        return NULL;
    }
    set->n = n;
    set->data = malloc(sizeof(Element) * n);
    set->parent = malloc(sizeof(int) * n);
    set->size = malloc(sizeof(int) * n);
    return set; // 别忘了返回创建的内容!!!
}

void releaseQuickUnionSet(QuickUnionSet *set) {
    if (set) {
        if (set->data)
            free(set->data);
        if (set->parent)
            free(set->parent);
        if (set->size)
            free(set->size);
        free(set);
        printf("The set has been cleared!\n");
    }
}

void initQuickUnionSet(QuickUnionSet *set, Element *data, int n) {
    for (int i = 0; i < n; i++) {
        set->data[i] = data[i];
        set->parent[i] = i; // 初始父节点默认为自身
        set->size[i] = 1; // 初始大小为1
    }
}

static int findIndex(const QuickUnionSet *set, Element val) {
    for (int i = 0; i < set->n; i++) {
        if (set->data[i] == val)
            return i;
    }
    printf("Find value %d failed!\n", val);
    return -1;
}
#ifndef PATH_COMPRESS
static int findRoot(const QuickUnionSet *set, Element val) { // 寻找元素对应的根节点
    int index = findIndex(set, val);
    if (index == -1)
        return -1;
    while (set->parent[index] != index) // 若当前位置索引等于自身, 则表明达到根节点位置
        index = set->parent[index];
    return index;
}
#else // 路径压缩模式
    #ifndef RECURSION
        #ifdef STACK // 压栈, 弹栈操作
static StackNode *push(StackNode *stack, int index) { // 压栈
    // 尾插法
    StackNode *new_node = malloc(sizeof(StackNode));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return NULL;
    }
    new_node->index = index;
    new_node->next = stack; // 指向尾部的指针
    return new_node; // 传回尾指针
}
static StackNode *pop(StackNode *stack, int *index) { // 弹栈
    StackNode *temp = stack;
    stack = stack->next;
    *index = temp->index; // 传入指针类型的值, 可通过解引用直接修改参数
    free(temp);
    return stack;
}
        #endif
    #endif

static int findRoot(QuickUnionSet *set, Element val) {
    int index = findIndex(set, val); // 每进入新一层, 根据最新数据更新索引指向当前层
    if (index == -1)
        return -1;
    #ifdef RECURSION // 递归式
    if (set->parent[index] == index) { // 直接使用index索引, 保证路径中每一点均在递归过程中实现路径压缩
        return index;
    }
    int rootIndex = findRoot(set, set->data[ set->parent[index] ]); // 移动到父节点位置继续进行递归(此处传入父节点位置的数据)
    set->parent[index] = rootIndex;
    return rootIndex;
    #elifdef STACK // 使用#elifdef; 如果使用#elif时会检测值是否为0, 如只判断是否定义, 则需使用defined()
    // 创建一个临时栈, 将途经的索引信息压入栈
    StackNode *stack = NULL;
    while (set->parent[index] != index) {
        stack = push(stack, index); // 压栈
        index = set->parent[index]; // 移动到上一级
    }
    while (stack) { // 寻找到根节点后, 依次弹栈将索引重新赋值
        int tempIndex;
        stack = pop(stack, &tempIndex); // 更新传入的临时索引为存储的路径索引
        set->parent[tempIndex] = index; // 统一赋值为根节点处索引
    }
    return index; // 返回根节点索引
    #else
    int rootIndex = index;
    while (set->parent[rootIndex] != rootIndex)
        rootIndex = set->parent[rootIndex]; // 使用循环找到根节点索引
    while (index != rootIndex) {
        int parentIndex = set->parent[index]; // 暂存父节点索引
        set->parent[index] = rootIndex; // 统一为根节点
        index = parentIndex; // 移动索引
    }
    return rootIndex;
    #endif
}
#endif
int isSameGroup(const QuickUnionSet *set, Element a, Element b) {
    int rootA = findRoot(set, a);
    int rootB = findRoot(set, b);
    if (rootA == -1 || rootB == -1) {
        printf("Find value %d failed!\n", (rootA == -1) ? a : b);
        return -1;
    }
    return rootA == rootB; // 返回元素a, b的根节点比较结果
}

void uniteGroup(QuickUnionSet *set, Element a, Element b) {\
    int rootA = findRoot(set, a);
    int rootB = findRoot(set, b);
    if (rootA == -1 || rootB == -1) {
        printf("Find value %d failed!\n", (rootA == -1) ? a : b);
        return;
    }
    if (rootA != rootB) {
        if (set->size[rootA] < set->size[rootB]) { // 采用size空间优化法, 将规模小的组接到更大的组上
            set->parent[rootA] = rootB; // 将规模较小的根节点的父节点指针指向规模大的根节点
            set->size[rootB] += set->size[rootA]; // 更新规模较大的根节点空间信息
        } else {
            set->parent[rootB] = rootA;
            set->size[rootA] += set->size[rootB];
        }
    }
}