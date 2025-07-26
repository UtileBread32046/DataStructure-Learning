#ifndef CHAIN_LIST_H
#define CHAIN_LIST_H

// 头指针版链表
// 核心思想: 引入虚拟头节点dummy, 在不破坏头指针的特性情况下, 仿照头节点法完成一系列操作
typedef int Element_t;
typedef struct _node {
    Element_t val;
    struct _node *next;
} node_t;
typedef struct {
    node_t *header; // 头指针
    int count;
} ChainList_t;

void initChainList(ChainList_t *list);
void destroyChainList(ChainList_t* list); // 销毁链表中除头节点以外的元素区域
int pushfrontChainList(ChainList_t *list, Element_t value);
int insertPosChainList(ChainList_t *list, int pos, Element_t value);
int deleteChainList(ChainList_t *list, Element_t value);
void showChainList(const ChainList_t *list);

#endif //CHAIN_LIST_H
