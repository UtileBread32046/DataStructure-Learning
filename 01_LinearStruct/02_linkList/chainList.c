#include "chainList.h"
#include <stdio.h>
#include <stdlib.h>

void initChainList(ChainList_t *list) { // 在数据区上空间已存在, 无需申请, 只需对表头的元素进行初始化
    list->count = 0;
    list->header = NULL;
}

void destroyChainList(ChainList_t* list) {
    node_t dummy;
    dummy.next = list->header;
    node_t *p = &dummy;
    while (p->next) {
        node_t* temp = p->next;
        p->next = temp->next;
        free(temp);
        list->count--;
    }
    printf("The list has been cleared: %d elements left.\n", list->count);
    list->header = NULL; // 将头指针更新为空指针
}

int pushfrontChainList(ChainList_t *list, Element_t value) {
    node_t dummy; // 引入栈上的虚拟头节点, 函数返回后自动销毁
    dummy.next = list->header; // 头插法可省略dummy节点, 但删除操作需要
    node_t *p = &dummy; // 引入指向新"头节点"的指针
    // 类比头节点版进行实现
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    new_node->next = p->next;
    new_node->val = value;
    p->next = new_node;
    list->count++; // 更新链表信息
    list->header = dummy.next; // 更新链表头指针(dummy.next随p更改, 但原list->header并未更改)
    return 0;
}

int insertPosChainList(ChainList_t *list, int pos, Element_t value) {
    node_t dummy; // 引入虚拟头节点
    dummy.next = list->header;
    if (pos < 0 || pos > list->count) { // 别忘了讨论边界值!
        fprintf(stderr, "index invalid!\n");
        return -1;
    }
    node_t *p = &dummy;
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    int sum = 0;
    while (sum < pos) {
        sum++;
        p = p->next;
    }
    new_node->val = value;
    new_node->next = p->next;
    p->next = new_node;
    list->header = dummy.next; // 更新链表头指针
    list->count++;
    return 0;
}

int deleteChainList(ChainList_t *list, Element_t value) {
    node_t dummy;
    dummy.next = list->header;
    node_t *p = &dummy;
    while (p->next && p->next->val != value) { // 合并判断条件
        // if (p->next->val == value) {
        //     break;
        // }
        p = p->next;
    }
    if (p->next == NULL) {
        printf("find value %d failed!\n", value);
        return -1;
    }
    node_t *temp = p->next;
    p->next = temp->next;
    free(temp);
    list->count--; // 更新表头信息
    list->header = dummy.next; // 别忘了更新头指针! (dummy.next修改但是list->header未变)
    return 0;
}

void showChainList(const ChainList_t *list) {
    node_t *p = list->header; // 从头指针指向的元素开始
    printf("There are totally %d elements in the list:\n", list->count);
    while (p) { // 遍历所有节点
        printf("%d\t", p->val);
        p = p->next;
    }
    printf("\n");
}
