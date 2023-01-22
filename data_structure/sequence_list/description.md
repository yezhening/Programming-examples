[TOC]

# 说明

## 顺序表的不同定义形式

数组数据类型：

```c
typedef int ELEM_TYPE; //数据的（数据）类型 依据数据的实际类型定义

ElEM_TYPE sqList[MAX_SIZE]; //数据
int length; //当前长度
```

静态结构体数据类型：

```c
#define MAX_SIZE 100 //最大大小

typedef int ELEM_TYPE; //数据的（数据）类型 依据数据的实际类型定义 

typedef struct
{
    ELEM_TYPE data[MAX_SIZE]; //数据
    int length;               //当前长度
    //最大大小>=当前长度
} SqList;
```

动态结构体数据类型：

```c
#define MAX_SIZE 100 //最大大小

typedef struct
{
    ELEM_TYPE *data; //数据
    int length; //当前长度
}SqList;

//初始化数据
L.data=(ELEM_TYPE*)malloc(sizeof(ELEM_TYPE)*MAX_SIZE); 
```

## 参考资料

- 《2023版数据结构高分笔记》主编：率辉
- 《2023年计算机组成原理考研复习指导》组编：王道论坛
- 《大话数据结构》作者：程杰