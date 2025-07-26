#include <stdio.h>
#include "linkQueue.h"

void test2() {
    LinkQueue *queue = createLinkQueue();
    if (queue == NULL) {
        fprintf(stderr, "ERROR\n");
        return;
    }
    for (int i = 1; i <= 5; i++) {
        enLinkQueue(queue, i);
    }
    Element value;
    printf("There are %d elements in the queue:\n", queue->count);
    while (deLinkQueue(queue, &value) == 0) {
        printf("%d\t", value);
    }
    printf("\n");
    releaseLinkQueue(queue);
}

int main() {
    test2();
    return 0;
}