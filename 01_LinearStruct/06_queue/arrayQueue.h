#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
#define MaxQueueSize 5 // 定义队列最大容量
// 使用数组实现顺序表, 通过取余运算进行循环索引, 实现循环队列
typedef int Element;
typedef struct {
    Element data[MaxQueueSize]; // 在栈上申请队列的数据空间
    int front; // 队首索引
    int rear; // 队尾索引
} ArrayQueue;

void initArrayQueue(ArrayQueue *queue);
int enArrayQueue(ArrayQueue *queue, Element value);
int deArrayQueue(ArrayQueue *queue, Element *value);

#endif //ARRAY_QUEUE_H
