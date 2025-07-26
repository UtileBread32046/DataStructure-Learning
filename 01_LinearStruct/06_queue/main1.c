#include "arrayQueue.h"
#include <stdio.h>

void test1() {
    ArrayQueue queue;
    initArrayQueue(&queue);
    for (int i = 1; i <= 5; i++) {
        enArrayQueue(&queue, i);
    }
    Element value;
    printf("Dequeue:\n"); // 从逻辑上只能使用出队操作进行打印值(出栈同理)
    while (deArrayQueue(&queue, &value) == 0) {
        printf("%d\t", value);
    }
    printf("\n");
}

int main() {
    test1();
    return 0;
}