// 头文件————————————————————
#include <iostream>

// 命名空间————————————————————
using namespace std;

// 宏————————————————————
#define MaxSize 100 // 队列的最大大小

// 自定义数据类型————————————————————
typedef int ElemType; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 顺序循环队列
typedef struct SqQueue
{
    ElemType data[MaxSize]; // 数据
    int front;              // 队头指针  定义为指向队头元素位置  出队：先出后移
    int rear;               // 队尾指针  定义为指向队尾元素位置的下一个位置  入队：先入后移
} SqQueue;

// 函数声明————————————————————
void use_example();                             // 使用示例
void init(SqQueue &sqQueue);                    // 初始化
bool enQueue(SqQueue &sqQueue, ElemType elem);  // 入队
bool deQueue(SqQueue &sqQueue, ElemType &elem); // 出队

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
    SqQueue sqQueue;

    // 初始化
    init(sqQueue);
    cout << sqQueue.front << endl; // 输出：0
    cout << sqQueue.rear << endl;  // 输出：0

    // 入队
    ElemType elem1 = 100;
    ElemType elem2 = 200;
    ElemType elem3 = 300;

    enQueue(sqQueue, elem1);
    enQueue(sqQueue, elem2);
    enQueue(sqQueue, elem3); // 元素在栈中的排列：100，200，300

    // 出队
    ElemType elem4 = 0;
    ElemType elem5 = 0;

    deQueue(sqQueue, elem4);
    deQueue(sqQueue, elem5);

    cout << elem4 << endl; // 输出：100
    cout << elem5 << endl; // 输出：200

    return;
}

// 初始化
void init(SqQueue &sqQueue) // 参数：队列
{
    // 定义队头指针和队尾指针指向索引/位置0为队空
    sqQueue.front = 0;
    sqQueue.rear = 0;
}

// 入队
// 时间复杂度：O(1)
bool enQueue(SqQueue &sqQueue, ElemType elem) // 参数：队列，元素
{
    if ((sqQueue.rear + 1) % MaxSize == sqQueue.front) // 队满
    {
        return false;
    }

    sqQueue.data[sqQueue.rear] = elem;           // 元素入队
    sqQueue.rear = (sqQueue.rear + 1) % MaxSize; // 队尾指针循环+1

    return true;
}

// 出队
// 时间复杂度：O(1)
bool deQueue(SqQueue &sqQueue, ElemType &elem) // 参数：队列，元素
{
    if (sqQueue.front == sqQueue.rear) // 队空
    {
        return false;
    }

    elem = sqQueue.data[sqQueue.front];            // 获取、保存元素
    sqQueue.front = (sqQueue.front + 1) % MaxSize; // 队头指针循环+1   元素出队

    return true;
}