#include "linkStack.h"
#include <stdio.h>
#include <stdlib.h>

void test2() {
    LinkStack *stack = createLinkStack();
    if (stack == NULL) {
        fprintf(stderr, "ERROR");
    }
    for (int i = 1; i <= 5; i++) {
        pushLinkStack(stack, i);
    }
    popLinkStack(stack);
    showLinkStack(stack);
    releaseLinkStack(stack);
}

int main() {
    test2();
    return 0;
}