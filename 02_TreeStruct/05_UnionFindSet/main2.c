#include <stdio.h>
#include "quickUnion.h"

static void judge(QuickUnionSet *set, int a, int b) {
    if (isSameGroup(set, a, b) == 1) {
        printf("True\tThe numbers %d and %d are in the same group!\n", a, b);
    } else {
        printf("False\tThe numbers %d and %d are not in the same group!\n", a, b);
    }
    printf("\n");
}
void test1() {
    printf("==========test1===========\n");
#ifdef PATH_COMPRESS
    printf("Path Compress has taken effect: ");
    #ifdef RECURSION
    printf("_Recursion Mode_\n");
    #elif defined(STACK)
    printf("_Stack Mode_\n");
    #else
    printf("_No-Recursion Mode_\n");
    #endif
#endif
    int n = 9;
    Element data[n];
    for (int i = 0; i < n; i++)
        data[i] = i;
    QuickUnionSet *set = createQuickUnionSet(n);
    initQuickUnionSet(set, data, n);

    uniteGroup(set, 3, 4);
    uniteGroup(set, 8, 0);
    uniteGroup(set, 2, 3);
    uniteGroup(set, 5, 6);

    int a = 0, b = 0;
    printf("Please enter 2 numbers:  ");
    scanf("%d%*c%d", &a, &b); // %*c: 任意间隔字符
    judge(set, a, b);

    uniteGroup(set, 5, 1);
    uniteGroup(set, 7, 3);
    uniteGroup(set, 1, 6);
    uniteGroup(set, 4, 8);

    judge(set, a, b);

    releaseQuickUnionSet(set);
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}