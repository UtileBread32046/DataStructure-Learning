#include "doubleLinkLoop.h"

void test1() {
    DList list;
    initDoubleList(&list);
    for (int i = 101; i <= 105; i++) {
        pushbackDoubleList(&list, i);
    }
    for (int i = 201; i <= 205; i++) {
        pushfrontDoubleList(&list, i);
    }
    deleteDoubleList(&list, 204);
    showDoubleList(&list);
    releaseDoubleList(&list);
}

int main() {
    test1();
    return 0;
}