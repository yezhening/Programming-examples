// 头文件————————————————————
#include <iostream>

// 命名空间————————————————————
using namespace std;

// 自定义数据类型————————————————————
typedef int ElemType; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 链队列结点
typedef struct LinkNode
{
    ElemType data;         // 数据
    struct LinkNode *next; // 指针
} LinkNode;

// 链队列
// 因为需要保存两个结点指针，所以新定义结构体封装
typedef struct LinkQueue
{
    LinkNode *front; // 队头结点指针
    LinkNode *rear;  // 队尾结点指针
} LinkQueue;

// 函数声明————————————————————
void use_example();                                 // 使用示例
void init(LinkQueue &linkQueue);                    // 初始化
void enQueue(LinkQueue &linkQueue, ElemType elem);  // 入队
bool deQueue(LinkQueue &linkQueue, ElemType &elem); // 出队

// 主函数————————————————————
int main()
{
    use_example(); // 使用示例

    return 0;
}

// 函数定义————————————————————
// 使用示例
void use_example()
{
    // 创建
    LinkQueue linkQueue; // 队列

    // 初始化
    init(linkQueue);

    // 入队
    ElemType elem1 = 100;
    ElemType elem2 = 200;
    ElemType elem3 = 300;

    enQueue(linkQueue, elem1);
    enQueue(linkQueue, elem2);
    enQueue(linkQueue, elem3); // 元素在栈中的排列：100，200，300

    // 出队
    ElemType elem4 = 0;
    ElemType elem5 = 0;

    deQueue(linkQueue, elem4);
    deQueue(linkQueue, elem5);

    cout << elem4 << endl; // 输出：100
    cout << elem5 << endl; // 输出：200

    return;
}

// 初始化
void init(LinkQueue &linkQueue) // 参数：队列
{
    linkQueue.front = linkQueue.rear = (LinkNode *)malloc(sizeof(LinkNode)); // 创建头结点   队列的队头、尾结点指针指向头结点
    linkQueue.front->next = nullptr;                                         // 头结点的指针指向空   即：linkQueue.rear->next = nullptr;
}

// 入队
// 时间复杂度：O(1)
void enQueue(LinkQueue &linkQueue, ElemType elem) // 参数：队列，元素
{
    LinkNode *newNode; // 新结点指针

    newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 创建新结点

    newNode->data = elem; // 初始化新结点的数据

    // 入队
    linkQueue.rear->next = newNode;
    linkQueue.rear = newNode;
}

// 出栈
// 时间复杂度：O(1)
bool deQueue(LinkQueue &linkQueue, ElemType &elem) // 参数：队列，元素
{
    if (linkQueue.front == linkQueue.rear) // 队空
    {
        return false;
    }

    LinkNode *tempNode = nullptr; // 临时结点指针

    elem = linkQueue.front->next->data; // 获取、保存数据

    // 出队
    tempNode = linkQueue.front->next;
    linkQueue.front->next = tempNode->next;

    // 易漏边界条件：如果除头结点只剩一个元素，该元素出队后，将队尾结点指针指向队头指针指向的头结点
    if (linkQueue.rear == tempNode)
    {
        linkQueue.rear = linkQueue.front;
    }

    free(tempNode); // 释放结点空间

    return true;
}