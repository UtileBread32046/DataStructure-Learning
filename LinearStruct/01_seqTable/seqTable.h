#ifndef SEQ_TABLE_H
#define SEQ_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 定义数据空间の存储类型
typedef int Element_t; // 后缀 _t 用于指明为typedef定义的类型

// 打包表头类型(使用匿名结构体)
typedef struct {
    Element_t *data; // 存储表中数据空间の首地址
    int pos; // 指向数据空间中待插入的位置(也能表示当前元素个数)
    int capacity; // 当前表的最大容量
} SEQTable_t; // 命名

// 表头在堆上申请, 提供给其他函数使用, 需要释放接口
SEQTable_t *createSeqTable(int n); // 在堆上创建表头(n为申请的数据空间)
void releaseSeqTable(SEQTable_t *table); // 释放表头和表中指向的数据存储空间
int pushbackSeqTable(SEQTable_t* table, Element_t value); // 尾插法
int insertPosSeqTable(SEQTable_t* table, int index, Element_t value); // 索引插入法
int deleteSeqTable(SEQTable_t* table, Element_t value); // 按值删除
int findSeqTable(const SEQTable_t* table, Element_t value); // 按值查找
void showSeqTable(const SEQTable_t * table); // 展示当前顺序表(使用const防止被修改)

#endif //SEQ_TABLE_H
