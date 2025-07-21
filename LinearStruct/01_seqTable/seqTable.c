#include "seqTable.h"

SEQTable_t* createSeqTable(int n) {
    SEQTable_t* table = NULL; // 定义表(初始为空, 防止出现野指针)
    table = malloc(sizeof(SEQTable_t)); // 根据表结构大小申请空间

    if (table == NULL) { // 检测是否申请成功
        fprintf(stderr, "SeqTable malloc failed!\n");
        return NULL; // 返回空表
    }
    table->data = malloc(sizeof(Element_t)*n); // 根据数据大小申请空间(注意一共有n个)

    if (table->data == NULL) { // 检测是否申请成功
        fprintf(stderr, "SeqTable data malloc failed!\n");
        free(table); // 当前已为table申请内存空间, 需手动进行释放, 防止内存泄露
        return NULL;
    }
    // 初始化位置和容量
    table->pos = 0;
    table->capacity = n;
    return table;
}

void releaseSeqTable(SEQTable_t* table) {
    if (table) { // 检测传入的table是否为空(防止空指针解引用引发错误)
        if (table->data) { // 检测table中的data是否为空
            free(table->data); // 释放掉data的空间
        }
        free(table); // 释放掉table的空间
    }
}

static int enlargerTable(SEQTable_t* table) { // 设置为静态函数, 为对内接口, 进行隐藏, 仅在当前文件的作用域内可见
    Element_t* temp = malloc(sizeof(Element_t)*table->capacity*2); // 2倍扩容, 申请临时数据空间, 指针类型为数据的类型, 大小为元素的单位大小*原容量*2
    if (temp == NULL) { // 扩容失败
        fprintf(stderr, "enlargerTable malloc failed!\n");
        return -1;
    }
    memcpy(temp, table->data, sizeof(Element_t)*table->pos); // 将原table中的数据拷贝到临时数据空间中, 大小为元素的单位大小*元素个数
    table->capacity*2; // 更新表头中的容量大小
    free(table->data); // 释放掉原数据空间中数据
    table->data = temp; // 将原来指向数据空间的指针进行更新
    return 0; // temp为局部变量, 函数返回后自动失效
}

int pushbackSeqTable(SEQTable_t* table, Element_t value) {
    // 可能引发错误的情况: 1. 传入的table指针为空; 2. 顺序表已满(需进行扩容)
    if (table == NULL) {
        fprintf(stderr, "table is a nullptr!\n");
        return -1; // 若table为空则失败
    }

    if (table->pos >= table->capacity && enlargerTable(table) != 0) { // 此处在判断的同时已(尝试)实现扩容
        // printf("SeqTable is full!\n");
        // fprintf(stderr, "enlargerTable failed!\n");
        fprintf(stderr, "SeqTable is full and enlargerTable failed!\n");
        return -1;
    }

    table->data[table->pos] = value; // 使用table->data[table->pos]等价于*(table->data+table->pos), 即先使指针偏移再进行解引用
    table->pos++;
    return 0;
}

int insertPosSeqTable(SEQTable_t* table, int index, Element_t value) {
    // 可能引发的错误: 1. 空间有效性判断; 2. 顺序表已满(需进行扩容); 3. 搬移数据为新数据预留位置(从后往前, 区间: [index, pos-1])
    if (index < 0 || index > table->pos) { // 此处>不取等(即可以等效为尾插法); 此处为pos而非capacity, 否则在当前pos后插入会破坏顺序表的逻辑结构
        fprintf(stderr, "index invalid!\n");
        return -1;
    }

    if (table->pos >= table->capacity && enlargerTable(table) != 0) {
        fprintf(stderr, "SeqTable is full and enlargerTable failed!\n");
        return -1;
    }

    for (int i = table->pos-1; i >= index; i--) { // i--和--i效率不同(--i不需要返回临时变量)
        table->data[i+1] = table->data[i]; // 依次搬移数据
    }
    table->data[index] = value; // 在索引位置插入值
    table->pos++; // 更新位置信息

}

int deleteSeqTable(SEQTable_t *table, Element_t value) {
    int index = findSeqTable(table, value);

    if (index == -1) {
        printf("find value %d failed!\n", value);
        return -1;
    }

    for (int i = index; i < table->pos-1; i++) { // 注意范围, pos处没有数据
        table->data[i] = table->data[i+1];
    }
    table->pos--;
    return 0;
}

int findSeqTable(const SEQTable_t *table, Element_t value) {
    for (int i = 0; i < table->pos; i++) {
        if (table->data[i] == value) {
            return i; // 返回值所在的索引位置
        }
    }
    return -1; // 查找失败
}

void showSeqTable(const SEQTable_t* table) {
    if (table == NULL)
        return;
    for (int i = 0; i < table->pos; i++) { // 此处＜不取等(pos指向的位置无数据)
        printf("%d\t", table->data[i]);
    }
    printf("\n");
}
