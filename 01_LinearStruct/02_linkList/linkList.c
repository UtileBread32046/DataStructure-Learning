#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>

LinkList_t* createLinkList() {
    LinkList_t* list = NULL;
    list = malloc(sizeof(LinkList_t));
    if (list == NULL) {
        fprintf(stderr, "linkList malloc failed!\n");
        return NULL;
    }
    // 进行初始化
    list->head.val = 0;
    list->head.next = NULL; // 默认头节点直接指向末尾(空指针NULL)
    list->count = 0;
    return list;
}

void releaseLinkList(LinkList_t* list) {
    if (list) { // 当链表存在时
        node_t *p = &list->head; // 引入始终指向头节点的指针p
        node_t *temp = NULL; // 引入辅助指针
        // 头删法
        while (p->next) { // 当头节点存在后继节点时
            temp = p->next;
            p->next = temp->next;
            free(temp);
            list->count--; // 更新链表信息
        }
        free(list); // 最后释放表头
    }
}

int pushfrontLinkList(LinkList_t* list, Element_t value) {
    node_t *p = &list->head; // 引入辅助指针p, 指向头节点地址
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) { // 创建新节点失败
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    // 更新节点信息
    new_node->val = value;
    new_node->next = p->next; // 注意一定要先更新新节点信息再更新旧节点信息, 顺序颠倒则无法正常指向后继结点
    p->next = new_node;
    list->count++;
    return 0;
}

int insertPosLinkList(LinkList_t* list, int pos, Element_t value) {
    if (pos < 0 || pos > list->count) { // 判断边界值
        fprintf(stderr, "index invalid!\n");
        return -1;
    }
    node_t *p = &list->head;
    int sum = 0; // 采用计数法累计经过的节点
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) { // 创建新节点失败
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    // 寻找指定索引位置
    while (sum < pos) {
        sum++; // 累计节点+1
        p = p->next; // 指向下一节点
    }
    new_node->val = value;
    new_node->next = p->next;
    p->next = new_node;
    list->count++;
    return 0;
}

int deleteLinkList(LinkList_t* list, Element_t value) {
    node_t *p = &list->head; // 指向头节点
    while (p->next) { // 当下一节点存在时
        if (p->next->val == value) { // 检测下一节点数据
            break; // 退出循环
        }
        p = p->next;
    }
    if (p->next == NULL) {
        printf("find value %d failed!\n", value);
        return -1;
    }
    node_t *temp = p->next; // 引入临时节点
    p->next = temp->next; // 指向下下节点
    free(temp); // 释放下一节点的数据
    list->count--; // 更新链表信息
    return 0;
}

void showLinkList(const LinkList_t* list) {
    node_t *p = list->head.next; // 引入辅助指针, 指向头节点的下一节点地址
    printf("There are totally %d elements in the list:\n", list->count);
    while (p) { // 当存在后继节点时(链表的末尾始终为空指针NULL)
        printf("%d\t", p->val);
        p = p->next; // 更新节点
    }
    printf("\n");
}