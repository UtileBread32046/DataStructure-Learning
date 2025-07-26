#ifndef LINKLIST_H
#define LINKLIST_H

// 头节点版链表
typedef int Element_t;
// 定义链表中节点结构
typedef struct _node {
    Element_t val;
    struct _node *next; // 使用相同类型的结构体的指针指向后继结点(需要指向完整节点而非单个数据)
} node_t;
// 定义链表头结构(哨兵节点/哑节点)
typedef struct {
    node_t head; // 此处为空间而非指针
    int count; // 用于统计数据总数
} LinkList_t;

LinkList_t *createLinkList();
void releaseLinkList(LinkList_t* list);
int pushfrontLinkList(LinkList_t* list, Element_t value);
int insertPosLinkList(LinkList_t* list, int pos, Element_t value);
int deleteLinkList(LinkList_t* list, Element_t value);
void showLinkList(const LinkList_t* list);

#endif //LINKLIST_H
