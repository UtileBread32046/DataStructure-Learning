#ifndef DOUBLE_LINK_LOOP_H
#define DOUBLE_LINK_LOOP_H
typedef int Element;
typedef struct _node {
    Element val;
    struct _node *prev;
    struct _node *next;
} DNode, DList; // 此处DNode为节点类型别名, DList为链表类型别名(实际指向头节点)
typedef struct {

};
void initDoubleList(DList *header);
void releaseDoubleList(DList* header);
int pushfrontDoubleList(DList* header, Element value);
int pushbackDoubleList(DList* header, Element value);
void showDoubleList(const DList* header);
void deleteDoubleList(DList* header, Element value);


#endif //DOUBLE_LINK_LOOP_H
