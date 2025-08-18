#ifndef QUICK_FIND_H
#define QUICK_FIND_H
typedef int Element;
// 并查集: 快速查找版
typedef struct {
    int n; // 记录并查集中元素个数
    Element *data; // 存放具体数据, 利用索引建立数据之间关系
    int *groupID; // 每个元素所在组的ID信息, 可通过索引查找
} QuickFindSet;

QuickFindSet *createQuickFindSet(int n);
void releaseQuickFindSet(QuickFindSet *set);
void initQuickFindSet(QuickFindSet *set, const Element *data, int n); // 初始化并查集元素
int isSameGroup(QuickFindSet *set, Element a, Element b); // 查找, 判断两元素是否同属一个组
void uniteGroup(QuickFindSet *set, Element a, Element b); // 合并, 将两元素合并到同一组

#endif //QUICK_FIND_H
