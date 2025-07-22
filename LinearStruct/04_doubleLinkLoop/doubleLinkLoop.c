#include "doubleLinkLoop.h"
#include <stdio.h>
#include <stdlib.h>

void initDoubleList(DList *header) {
    header->val = 0;
    header->prev = header;
    header->next = header;
}

// 在当前文件中封装一个添加新节点的函数(对外隐藏)
static void addDNode(DNode *new_node,  DNode *prev, DNode *next) {
    // 逆时针方向动指针
    next->prev = new_node; // 后继节点的前驱指针指向新节点
    new_node->next = next; // 新节点的后继指针指向后继结点
    new_node->prev = prev; // 新节点的前驱指针指向前驱结点
    prev->next = new_node; // 前驱结点的后继指针指向新节点
}
// 移动指针进行逻辑上删除(未释放内存)
static void deleteDNode(DNode *prev, DNode *next) {
    next->prev = prev;
    prev->next = next;
}
int pushfrontDoubleList(DList *header, Element value) {
    DNode *new_node = malloc(sizeof(DNode));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    new_node->val = value;
    addDNode(new_node, header, header->next);
    header->val++; // 此处以头节点的val值作为链表节点总数
    return 0;
}

int pushbackDoubleList(DList *header, Element value) {
    DNode *new_node = malloc(sizeof(DNode));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    new_node->val = value;
    addDNode(new_node, header->prev, header); // 此处为循环链表, 头节点的前驱结点即为尾节点, 头节点自身即为后继结点
    header->val++;
    return 0;
}

void showDoubleList(const DList *header) {
    DNode *p = header->next;
    printf("There are %d elements in the list:\n", header->val);
    while (p != header) { // 当转回一圈时停止
        printf("%d\t", p->val);
        p = p->next;
    }
    printf("\n");
}

void deleteDoubleList(DList *header, Element value) {
    // 双向链表可直接找到该位置的节点, 不需要判断后继结点
    DNode *p = header->next;
    while (p != header && p->val != value)
        p = p->next;
    if (p == header) {
        printf("find value %d failed!\n", value);
        return;
    }
    deleteDNode(p->prev, p->next); // 此时p停在恰为要删除值的位置
    p->prev = p->next = NULL; // 将指针定位空, 避免野指针(可选)
    free(p);
    header->val--; // 更新表头数据
}

void releaseDoubleList(DList *header) {
    // 通过头节点进行释放
    while (header->next != header) {
        // DNode *temp = header->next; // 直接删除法
        // header->next = temp->next;
        // free(temp);

        DNode *p = header->next;
        deleteDNode(p->prev, p->next); // 辅助函数删除法
        free(p);
        header->val--;
    }
    printf("The list has been cleared: %d elements left.\n", header->val);
    // header是在栈上静态分配的, 不能使用free进行释放
}
