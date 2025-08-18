#include <stdio.h>
#include "quickFind.h"

static void examine(QuickFindSet *set) {
    printf("||    data    |   groupID  ||\n");
    for (int i = 0; i < set->n; i++) {
        printf("||       %d       |       %d       ||\n", set->data[i], set->groupID[i]);
    }
}
static void judge(QuickFindSet *set, int a, int b) {
    examine(set);
    if (isSameGroup(set, a, b) == 1) {
        printf("True\tThe numbers %d and %d are in the same group!\n", a, b);
    } else {
        printf("False\tThe numbers %d and %d are not in the same group!\n", a, b);
    }
    printf("\n");
}
void test1() {
    printf("==========test1===========\n");
    int n = 9;
    Element data[n];
    for (int i = 0; i < n; i++)
        data[i] = i;
    QuickFindSet *set = createQuickFindSet(n);
    initQuickFindSet(set, data, n);

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

    releaseQuickFindSet(set);
}

int main() {
    test1();
    printf("=========================\n");
    return 0;
}