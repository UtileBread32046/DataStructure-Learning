#ifndef LINK_STACK_H
#define LINK_STACK_H
// 在堆上分配的链式栈
typedef int Element;
typedef struct _node {
    Element data;
    struct _node *next;
} StackNode;
typedef struct { // 将栈顶指针进行封装, 有便于操作
    StackNode *top;
    int count;
} LinkStack;

LinkStack* createLinkStack(); // 在堆上申请栈
void releaseLinkStack(LinkStack *stack);
int pushLinkStack(LinkStack *stack, Element value);
int popLinkStack(LinkStack *stack);
void showLinkStack(const LinkStack *stack);

#endif //LINK_STACK_H
