#include "arrayStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initArrayStack(ArrayStack *stack) {
    memset(stack, 0, sizeof(stack->data)); // 使用<string.h>中的memset为栈中数据进行批量初始化
    stack->top = 0; // 空栈的初始指针指向带插入位置
}

int isEmptyArrayStack(const ArrayStack *stack) {
    return stack->top == 0; // 直接返回栈顶指针, 判断是否在底部
}

int isFullArrayStack(const ArrayStack *stack) {
    return stack->top == MaxStackSize; // 下标从0开始, 到MaxStackSize恰好满栈
}

void pushArrayStack(ArrayStack *stack, Element value) {
    if (!isFullArrayStack(stack)) {
        // 递增空栈の入栈: 先赋值, 再后移指针
        stack->data[stack->top] = value;
        stack->top++;
    }
    else
        printf("push the element %d in the stack failed! (full)\n", value);
}

void popArrayStack(ArrayStack *stack) {
    stack->top--;
    // 此处不需要将原来的数据抹除
}

Element getTopArrayStack(ArrayStack *stack) {
    int pos = stack->top-1; // 此处不可改变原有的top值, 故引入临时变量 (不能写成top--, 否则也会改变原始值)
    return stack->data[pos];
}

void showArrayStack(ArrayStack *stack, const int sum) {
    // 采用循环弹栈依次获取栈中元素
    int initial = stack->top;
    printf("There are %d elements in the stack:\n", sum);
    while (!isEmptyArrayStack(stack)) {
        Element val = getTopArrayStack(stack); // 先获取元素后出栈
        printf("%d\t", val);
        stack->top--;
    }
    stack->top = initial;
    printf("\n");
}

int releaseArrayStack(ArrayStack *stack, int sum) {
    while (sum > 0) {
        popArrayStack(stack);
        sum--;
    }
    return sum;
}
