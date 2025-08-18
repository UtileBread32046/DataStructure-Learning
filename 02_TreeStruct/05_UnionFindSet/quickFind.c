#include <stdio.h>
#include <stdlib.h>
#include "quickFind.h"

QuickFindSet *createQuickFindSet(int n) {
    QuickFindSet *set = malloc(sizeof(QuickFindSet));
    if (set == NULL) {
        fprintf(stderr, "set malloc failed!\n");
        return NULL;
    }
    set->n = n;
    set->data = malloc(sizeof(Element) * n); // 申请出n个元素的数据空间
    set->groupID = malloc(sizeof(int) * n); // 申请出n个元素的组别空间
    return set;
}

void releaseQuickFindSet(QuickFindSet *set) {
    // 依次将手动申请的空间free掉
    if (set) {
        if (set->data)
            free(set->data);
        if (set->groupID)
            free(set->groupID);
        free(set);
        printf("The set has been cleared!\n");
    }
}

void initQuickFindSet(QuickFindSet *set, const Element *data, int n) {
    for (int i = 0; i < n; i++) {
        set->data[i] = data[i]; // 依次给并查集中的数据赋值
        set->groupID[i] = i; // 默认每个元素的根节点是自己, 故组别信息赋值为自己所在位置的索引
    }
}

static int findIndex(const QuickFindSet *set, Element val) { // 自定义寻找元素下标函数
    for (int i = 0; i < set->n; i++) { // 需要遍历整个并查集
        if (set->data[i] == val)
            return i;
    }
    return -1; // 查找失败
}
int isSameGroup(QuickFindSet *set, Element a, Element b) {
    int indexA = findIndex(set, a);
    int indexB = findIndex(set, b);
    if (indexA == -1 || indexB == -1) {
        printf("Find value %d failed!\n", (indexA == -1) ? a : b);
        return -1;
    }
    return set->groupID[indexA] == set->groupID[indexB]; // 直接返回判断两个索引处所在组别信息的结果, 1为真, 0为假
}

void uniteGroup(QuickFindSet *set, Element a, Element b) {
    // 将b所在组别的信息全部更新为a所在的 (b所在部门成员全部迁移到a部门领导下)
    int indexA = findIndex(set, a);
    int indexB = findIndex(set, b);
    int bID = set->groupID[indexB]; // 将元素b对应的id提前储存, 防止被更改而错误赋值
    if (indexA == -1 || indexB == -1) { // 检查元素是否存在
        printf("Find value %d failed!\n", (indexA == -1) ? a : b);
        return;
    }
    for (int i = 0; i < set->n; i++) {
        if (set->groupID[i] == bID)
            set->groupID[i] = set->groupID[indexA];
    }
}
