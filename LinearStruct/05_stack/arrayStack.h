#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H
#define MaxStackSize 5 // 规定数组栈的最大容量
typedef int Element;
// 此处使用数组定义顺序栈(不使用指针), 且规定其不可扩容(用以讨论栈的特性)
typedef struct {
    Element data[MaxStackSize];
    int top;
} ArrayStack;

// 递增空栈版
void initArrayStack(ArrayStack *stack);
int isEmptyArrayStack(const ArrayStack *stack);             // 判断栈空
int isFullArrayStack(const ArrayStack *stack);                  // 判断栈满
void pushArrayStack(ArrayStack *stack, Element value); // 入栈(压栈)
void popArrayStack(ArrayStack *stack);                              // 出栈(弹栈)
Element getTopArrayStack(ArrayStack *stack);                 // 获取栈顶元素
void showArrayStack(ArrayStack *stack, int sum);
int releaseArrayStack(ArrayStack *stack, int sum);

#endif //ARRAY_STACK_H
