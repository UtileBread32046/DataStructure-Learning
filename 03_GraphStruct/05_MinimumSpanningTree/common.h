#ifndef COMMON_H
#define COMMON_H

// 使用公共头文件, 避免重复定义
typedef struct {
    int begin; // 边的起点
    int end; // 终点
    int weight; // 权重值
} EdgeSet; // 边集数组的元素结构

#endif // COMMON_H
