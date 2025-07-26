#include "linkLoop.h"

void test1() {
    LinkLoop_t linkLoop; // 分配在栈上
    initLinkLoop(&linkLoop);
    for (int i = 101; i <= 105; i++) {
        pushbackLinkLoop(&linkLoop, i);
    }
    for (int i = 201; i <= 205; i++) {
        pushfrontLinkLoop(&linkLoop, i);
    }
    deleteLinkLoop(&linkLoop, 102);
    showLinkLoop(&linkLoop);
    destroyLinkLoop(&linkLoop);
}

int main() {
    test1();
    return 0;
}