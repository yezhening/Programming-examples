// 头文件————————————————————
#include <iostream>

// 命名空间————————————————————
using namespace std;

// 自定义数据类型————————————————————
typedef int ElemType; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 链栈结点
typedef struct LinkNode
{
    ElemType data;         // 数据
    struct LinkNode *next; // 指针
} LinkNode;

// 函数声明————————————————————
void use_example();                        // 使用示例
void init(LinkNode *&head);                // 初始化
void push(LinkNode *&head, ElemType elem); // 入栈
bool pop(LinkNode *&head, ElemType &elem); // 出栈

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
    LinkNode *head; // 头结点指针

    // 初始化
    init(head);

    // 入栈
    ElemType elem1 = 100;
    ElemType elem2 = 200;
    ElemType elem3 = 300;

    push(head, elem1);
    push(head, elem2);
    push(head, elem3); // 元素在栈中的排列：100，200，300

    // 出栈
    ElemType elem4 = 0;
    ElemType elem5 = 0;

    pop(head, elem4);
    pop(head, elem5);

    cout << elem4 << endl; // 输出：300
    cout << elem5 << endl; // 输出：200

    return;
}

// 初始化
void init(LinkNode *&head) // 参数：头结点指针
{
    head = (LinkNode *)malloc(sizeof(LinkNode)); // 创建头结点   头结点指针指向头结点
    head->next = nullptr;                        // 头结点的指针指向空
}

// 入栈
// 时间复杂度：O(1)
void push(LinkNode *&head, ElemType elem) // 参数：头结点指针，元素
{
    LinkNode *newNode; // 新结点指针

    newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 创建新结点

    newNode->data = elem; // 初始化新结点的数据

    // 入栈
    newNode->next = head->next;
    head->next = newNode;
}

// 出栈
// 时间复杂度：O(1)
bool pop(LinkNode *&head, ElemType &elem) // 参数：头结点指针，元素
{
    if (head->next == nullptr) // 栈空
    {
        return false;
    }

    LinkNode *tempNode = nullptr; // 临时结点指针

    elem = head->next->data; // 获取、保存数据

    // 出栈
    tempNode = head->next;
    head->next = tempNode->next;

    free(tempNode); // 释放结点空间

    return true;
}