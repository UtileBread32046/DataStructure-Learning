#include <stdio.h>
#include "seqTable.h"

void test1() {
    SEQTable_t *table1 = createSeqTable(5);
    if (table1 == NULL) { // 创建表失败
        return;
    }
    for (int i = 0; i < 5; i++) {
        pushbackSeqTable(table1, 100+i); // 依次推入顺序表末尾
    }
    pushbackSeqTable(table1, 105);
    insertPosSeqTable(table1, 5, 200);
    deleteSeqTable(table1, 101);
    showSeqTable(table1); // 展示顺序表
    releaseSeqTable(table1); // 释放顺序表
}

int main()
{
    printf("This is a test!\n");
    test1();
    return 0;
}