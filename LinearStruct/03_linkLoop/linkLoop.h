#ifndef LINK_LOOP_H
#define LINK_LOOP_H
// 定义数据类型和节点
typedef int Element_t;
typedef struct _node {
    Element_t val;
   struct _node *next;
} node_t;
typedef struct{
    int count;
    node_t header; // 头节点(空间)
    node_t *rear; // 尾指针
} LinkLoop_t;

void initLinkLoop(LinkLoop_t *linkLoop);
int pushfrontLinkLoop(LinkLoop_t* linkLoop, Element_t value);
int pushbackLinkLoop(LinkLoop_t* linkLoop, Element_t value);
void showLinkLoop(const LinkLoop_t* linkLoop);
int deleteLinkLoop(LinkLoop_t* linkLoop, Element_t value);
void destroyLinkLoop(LinkLoop_t* linkLoop);

#endif //LINK_LOOP_H
