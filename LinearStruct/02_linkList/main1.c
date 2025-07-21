#include <stdio.h>
#include "linkList.h"

void test1() {
    LinkList_t* list =  createLinkList();
    if (list == NULL) { // 创建失败
        return;
    }
    for (int i = 101; i <= 105; i++) {
        pushfrontLinkList(list, i);
    }
    insertPosLinkList(list, 3, 200);
    deleteLinkList(list, 104);
    showLinkList(list);
    releaseLinkList(list);
}

int main() {
    printf("This is a test!\n");
    test1();
    return 0;
}