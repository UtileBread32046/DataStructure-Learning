#include "linkStack.h"
#include <stdio.h>
#include <stdlib.h>

LinkStack *createLinkStack() {
    LinkStack *stack = malloc(sizeof(LinkStack));
    if (stack == NULL) {
        fprintf(stderr, "stack malloc failed!");
        return NULL;
    }
    stack->count = 0;
    stack->top = NULL; // 以空指针为末尾
    return stack;
}

void releaseLinkStack(LinkStack *stack) {
    if (stack) { // 当栈存在时
        while (stack->top != NULL) {
            StackNode *temp = stack->top;
            stack->top = temp->next;
            free(temp);
            stack->count--;
        }
        printf("The stack has been cleared: %d elements left.\n", stack->count);
    }
}

int pushLinkStack(LinkStack *stack, Element value) {
    StackNode *new_node = malloc(sizeof(StackNode));
    if (new_node == NULL) {
        fprintf(stderr, "new_node malloc failed!\n");
        return -1;
    }
    // 将新节点放到老节点的前面(新节点next指向老节点), 方便出栈操作
    new_node->data = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->count++;
    return 0;
}

int popLinkStack(LinkStack *stack) {
    if (stack->top == NULL) {
        fprintf(stderr, "pop the stack failed (empty)\n");
        return -1;
    }
    StackNode *temp = stack->top;
    stack->top = temp->next;
    free(temp);
    stack->count--;
    return 0;
}

void showLinkStack(const LinkStack *stack) {
    StackNode *temp = stack->top;
    printf("There are %d element in the stack:\n", stack->count);
    while (temp != NULL) {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
