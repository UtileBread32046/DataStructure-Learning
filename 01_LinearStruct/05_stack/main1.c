#include "arrayStack.h"
#include <stdio.h>

void test1() {
    ArrayStack stack; // 此处选择在栈上定义顺序栈
    initArrayStack(&stack);
    int sum = 0;
    for (int i = 1; i <= 7; i++) {
        if (!isFullArrayStack(&stack)) sum++;
        pushArrayStack(&stack, i);
    }
    showArrayStack(&stack, sum);
    sum = releaseArrayStack(&stack, sum);
    printf("The stack has been cleared: %d elements left.\n", sum);
}

int main() {
    test1();
    return 0;
}