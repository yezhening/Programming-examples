// 头文件————————————————————
#include <iostream>

// 命名空间————————————————————
using namespace std;

// 宏————————————————————
#define MaxSize 100 // 栈的最大大小

// 自定义数据类型————————————————————
typedef int ElemType; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 顺序栈
typedef struct SqStack
{
    ElemType data[MaxSize]; // 数据
    int topPointer;         // 栈顶指针
    // 注意：定义为指向栈顶位置而不是栈顶位置的后一位置
    // 值是索引，取值范围：-1——MaxSize-1，可作为判断栈空和栈满条件
} SqStack;

// 函数声明————————————————————
void use_example();                         // 使用示例
void init(SqStack &sqStack);                // 初始化
bool push(SqStack &sqStack, ElemType elem); // 入栈
bool pop(SqStack &sqStack, ElemType &elem); // 出栈

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
    SqStack sqStack;

    // 初始化
    init(sqStack);
    cout << sqStack.topPointer << endl; // 输出：-1

    // 入栈
    ElemType elem1 = 100;
    ElemType elem2 = 200;
    ElemType elem3 = 300;

    push(sqStack, elem1);
    push(sqStack, elem2);
    push(sqStack, elem3); // 元素在栈中的排列：100，200，300

    // 出栈
    ElemType elem4 = 0;
    ElemType elem5 = 0;

    pop(sqStack, elem4);
    pop(sqStack, elem5);

    cout << elem4 << endl; // 输出：300
    cout << elem5 << endl; // 输出：200

    return;
}

// 初始化
void init(SqStack &sqStack) // 参数：栈
{
    sqStack.topPointer = -1; // 栈顶指针的值，即索引为-1，不存在元素
}

// 入栈
// 时间复杂度：O(1)
bool push(SqStack &sqStack, ElemType elem) // 参数：栈，元素
{
    // 注意：判断合法条件
    if (sqStack.topPointer == MaxSize - 1) // 栈满
    {
        return false;
    }

    ++sqStack.topPointer;                    // 栈顶指针+1
    sqStack.data[sqStack.topPointer] = elem; // 元素入栈

    return true;
}

// 出栈
// 时间复杂度：O(1)
bool pop(SqStack &sqStack, ElemType &elem) // 参数：栈，元素
{
    if (sqStack.topPointer == -1) // 栈空
    {
        return false;
    }

    elem = sqStack.data[sqStack.topPointer]; // 获取、保存元素
    --sqStack.topPointer;                    // 栈顶指针-1   元素出栈

    return true;
}