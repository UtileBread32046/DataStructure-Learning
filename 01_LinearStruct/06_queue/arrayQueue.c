#include "arrayQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initArrayQueue(ArrayQueue *queue) {
    memset(queue->data, 0, sizeof(queue->data)); // 数组会依次被赋值, 故可不写
    queue->front = queue->rear = 0;
}

int enArrayQueue(ArrayQueue *queue, Element value) {
    // 预留空位判别法(空出一格位置, 用以判断两索引位置是否重叠)
    if ((queue->rear+1) % MaxQueueSize == queue->front) {
        printf("enqueue the element %d failed (full)\n", value);
        return -1;
    }
    queue->data[queue->rear] = value;
    queue->rear++;
    queue->rear %= MaxQueueSize;
    return 0;
}

int deArrayQueue(ArrayQueue *queue, Element *value) { // 使用指针可避免形参无法修改原值的问题
    if (queue->front == queue->rear) {
        printf("dequeue the element failed (empty)");
        return -1;
    }
    *value = queue->data[queue->front]; // 将传入的指向输出值的指针赋值
    queue->front++;
    queue->front %= MaxQueueSize;
    return 0;
}
