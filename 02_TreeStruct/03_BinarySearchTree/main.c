#include <stdio.h>
#include <stdlib.h>
#include <time.h> // 调用随机数生成和时刻记录
#include "searchTree.h"

void test1() {
    printf("==============test1====================\n");
    int data[] = {55, 33, 100, 22, 80, 45, 130, 8, 120, 40};
    SearchTree *tree = createSearchTree();
    if (tree) {
        for (size_t i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
            insertSearchTree(tree, data[i]);
        }
    }
    deleteSearchTree(tree, 55);
    inorderSearchTree(tree);
    printf("\n");
    printf("The tree root is %d.\n", tree->root->data);
    printf("The height of tree is %d.\n", heightSearchTree(tree));
    releaseSearchTree(tree);
}

static void linearSearch(const Element *data, int n, Element val, int times) {
    int find = 0;
    while (times--) {
        for (int i = 0; i < n; i++) {
            if (data[i] == val) {
                find = 1;
                break;
            }
        }
    }
    if (find == 1)
        printf("The value %d has been found!\n", val);
    else
        printf("Find value %d failed!\n", val);
}
static void TreeSearch(const Element *data, int n, Element val, int times) {
    SearchTree *tree = createSearchTree();
    for (int i = 0; i < n; i++)
        insertSearchTree(tree, data[i]);
    TreeNode *node = NULL;
    while (times--)
        node = findTreeNode(tree, val);
    if (node) {
        printf("The value %d has been found!\n", val);
    } else {
        printf("Find value %d failed!\n", val);
    }
}
void test2() {
    printf("==============test2====================\n");
    // 测试在查找失败的情况下, 线性查找与二叉搜索树查找各自的时间效率
    int n = 1000000; // 设置元素数量
    Element scope = n + 5000; // 设置取值范围
    Element target  = scope + 1; // 设置目标数值
    Element *data = malloc(sizeof(Element)*n); // 申请数据空间
    int times = 1000; // 设置查找次数(循环多次以提高差异)
    srand(time(NULL)); // 初始化随机数生成器; srand(): 以括号内的整数为种子; time(NULL): 获取当前时间值(不保存到变量中)
    for (int i = 0; i < n; i++)
        data[i] = rand()%scope + 1; // 给数据空间中依次赋值区间[1, scope]内的任意数值

    /* 线性搜索 */
    clock_t start = clock(); // 记录此处时刻
    linearSearch(data, n, target, times);
    clock_t end = clock();
    // 先将时钟周期差值转化为double类型保证计算精度, 再除以CLOCKS_PER_SEC, 将时钟周期数转化为以秒为单位的时间
    printf("The time of LinearSearch is %lfs.\n", (double)(end-start) / CLOCKS_PER_SEC); // %lf: long double, 双精度浮点数

    /* 二叉搜索树搜索 */
    // 此处对于单次查找统计了二叉树构建的时间, 若涉及多次查找,  可舍去
    start = clock(); // 重新复制即可
    TreeSearch(data, n, target, times);
    end = clock();
    printf("The time of TreeSearch is %lfs.\n", (double)(end-start) / CLOCKS_PER_SEC);

    free(data); // 清除数据集
    // 不难发现, 当查找次数较低时, 二叉搜索树的创建时间会占据较大比重, 但当查找次数较大时, 二叉搜索树的查找特性便会更占优势
}

int main() {
    test1();
    // test2();
    printf("=======================================\n");
    return 0;
}