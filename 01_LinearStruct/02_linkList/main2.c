#include <stdio.h>
#include "chainList.h"
#include "../01_seqTable/seqTable.h"

// 头指针式链表
// ChainList_t list; // 链表头在数据区, 存放到全局变量
void test2() {
    ChainList_t list;
    initChainList(&list);
    for (int i = 101; i <= 105; i++) {
        pushfrontChainList(&list, i);
    }
    insertPosChainList(&list, 3, 200);
    deleteChainList(&list, 105);
    showChainList(&list);
    destroyChainList(&list);
}
int main() {
    test2();
    return 0;
}