#include "linkQueue.h"
#include <stdio.h>
#include <stdlib.h>

LinkQueue* createLinkQueue() {
    LinkQueue *queue = malloc(sizeof(LinkQueue));
    if (queue == NULL) {
        fprintf(stderr, "queue malloc failed!\n");
        return NULL;
    }
    queue->count = 0;
    queue->front = queue->rear = NULL; // 以空指针为末尾
    return queue;
}

void releaseLinkQueue(LinkQueue *queue) {
    if (queue) { // 当队列存在时
        while (queue->front != NULL) { // 当队首指针指向空时恰好清空
            QueueNode *temp = queue->front;
            queue->front = temp->next;
            free(temp);
            queue->count--;
        }
        printf("The queue has been cleared: %d element left.\n", queue->count);
        free(queue); // 释放队头
    }
}

int enLinkQueue(LinkQueue *queue, Element value) {
    // 出队时需使用front指针后移, 故将新节点放到老节点的后面(老节点next->新节点)
    QueueNode *new_node = malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed\n");
        return -1;
    }
    new_node->data = value;
    new_node->next = NULL; // 尾插法中新节点指向空
    // 注意下面逻辑关系, 应避免出现新节点自指现象
    if (queue->front == NULL) // 当首次出现新节点时
        queue->front = queue->rear = new_node; // 初始状态下队首队尾指针均为空, 如果使用NULL->next会报错
    else {
        queue->rear->next = new_node; // 使队尾指针指向的老节点指向新节点
        queue->rear = new_node; // 更新队尾指针
    }
    queue->count++;
    return 0;
}

int deLinkQueue(LinkQueue *queue, Element *value) {
    if (queue->front == NULL) { // 判断条件应为队首指针是否为空而不是两指针是否相等
        printf("dequeue the element failed (empty)\n");
        return -1;
    }
    QueueNode *temp = queue->front;
    queue->front = temp->next;
    *value = temp->data;
    free(temp);
    queue->count--;
    if (queue->front == NULL)
        queue->rear = NULL; // 将队尾指针置空, 避免野指针
    return 0;
}
