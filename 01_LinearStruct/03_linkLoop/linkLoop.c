#include "linkLoop.h"
#include <stdio.h>
#include <stdlib.h>

void initLinkLoop(LinkLoop_t *linkLoop) {
    linkLoop->count = 0;
    linkLoop->rear = &linkLoop->header;
    linkLoop->header.next = &linkLoop->header;
}
int pushfrontLinkLoop(LinkLoop_t *linkLoop, Element_t value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    if (linkLoop->rear == &linkLoop->header) // 当表中元素从无到有时
        linkLoop->rear = new_node;
    new_node->val = value;
    new_node->next = linkLoop->header.next;
    linkLoop->header.next = new_node;
    linkLoop->count++;
    return 0;
}
int pushbackLinkLoop(LinkLoop_t *linkLoop, Element_t value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    // if (linkLoop->header.next == &linkLoop->header) // 当表中元素从无到有时
    //     linkLoop->header.next = new_node;
    new_node->val = value;
    new_node->next = linkLoop->rear->next;
    linkLoop->rear->next = new_node; // 原先的尾节点指向新尾节点
    linkLoop->rear = new_node; // 尾指针指向新尾节点
    linkLoop->count++;
    return 0;
}
void showLinkLoop(const LinkLoop_t *linkLoop) {
    node_t *p = linkLoop->header.next;
    printf("There are %d elements in the list:\n", linkLoop->count);
    while (p != &linkLoop->header) {
        printf("%d\t", p->val);
        p  = p->next;
    }
    printf("\n");
}
int deleteLinkLoop(LinkLoop_t *linkLoop, Element_t value) {
    node_t *p = &linkLoop->header;
    while (p->next != &linkLoop->header && p->next->val != value)
        p = p->next;
    if (p->next == &linkLoop->header) {
        printf("find value %d failed!\n", value);
        return -1;
    }
    node_t *temp = p->next;
    p->next = temp->next;
    free(temp);
    linkLoop->count--;
    return 0;
}
void destroyLinkLoop(LinkLoop_t *linkLoop) {
    node_t *p = &linkLoop->header;
    while (p->next != &linkLoop->header) { // 此处不能为linkLoop->rear->next(尾节点被free掉后rear->next即失去意义)
        node_t *temp = p->next;
        p->next = temp->next;
        free(temp);
        linkLoop->count--;
    }
    printf("The list has been cleared: %d elements left.", linkLoop->count);
    linkLoop->rear = NULL;

    // node_t *p = linkLoop->header.next;
    // while (p != &linkLoop->header) {
    //     node_t *temp = p;
    //     p = temp->next;
    //     free(temp);
    //     linkLoop->count--;
    // }
    // printf("The list has been cleared: %d elements left.", linkLoop->count);
    // linkLoop->rear = NULL;
}
