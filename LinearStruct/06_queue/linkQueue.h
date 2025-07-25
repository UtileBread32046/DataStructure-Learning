#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H
typedef int Element;
typedef struct _node {
    Element data;
    struct _node *next;
} QueueNode;
typedef struct {
    int count;
    QueueNode *front; // 队头指针
    QueueNode *rear; // 队尾指针
} LinkQueue;

LinkQueue* createLinkQueue();
void releaseLinkQueue(LinkQueue *queue);
int enLinkQueue(LinkQueue *queue, Element value);
int deLinkQueue(LinkQueue *queue, Element *value);

#endif //LINK_QUEUE_H
