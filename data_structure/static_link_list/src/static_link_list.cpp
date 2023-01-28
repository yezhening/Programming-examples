// 头文件————————————————————
#include <iostream>
using namespace std;

// 自定义数据类型————————————————————
typedef int ELEM_TYPE; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 定义
// 结点
typedef struct LNode
{
    ELEM_TYPE data;     // 数据
    struct LNode *next; // 指向直接后继结点的指针
} LNode;
// struct LNode：结构体数据类型的名称
// 如创建一个结点的语句：struct LNode node;
// 若结构体数据类型内存在指向该结构体的指针数据类型，则必须完整命名结构体数据类型的名称
// 如结点结构体LNode内存在指向该结构体的指针数据类型next，则命名语句为：typedef struct LNode而不是typedef struct
// LNode：typedef给结构体数据类型起的别名，可简化语句
// 如创建一个结点的语句：LNode node;
// 结构体数据类型的名称和别名尽量一致，以方便记忆、使用

// 函数声明————————————————————
void use_example();                                                  // 使用示例
void create_list_head(LNode *&head, ELEM_TYPE value[], int count);   // 创建  头插法
void create_list_tail(LNode *&head, ELEM_TYPE value[], int count);   // 创建  尾插法
LNode *find_node(LNode *head, ELEM_TYPE elem);                       // 按值查找
LNode *get_node(LNode *head, int i);                                 // 按序查找
void insert_node(LNode *&head, int posi, LNode *node);               // 插入  前插
void insert_node_exten(LNode *&head, int posi, LNode *node);         // 插入  扩展：前插转后插
void delele_node(LNode *&head, int posi);                            // 删除  前删
void delele_node_exten(LNode *&head, int posi);                      // 删除  前删转后删
int get_length(LNode *head);                                         // 获取表长
void clear_list(LNode *&head);                                       // 清空
void merge_list_increase(LNode *head1, LNode *head2, LNode *&head3); // 合并两递增表成递增表
void merge_list_reduce(LNode *head1, LNode *head2, LNode *&head3);   // 合并两递增表成递减表

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
    struct LNode *head; // 头指针，指向头结点或第一个结点
    // 或LNode *head;
    // 一般头指针变量名为链表表名    这里用head见明知意，表示是头指针

    ELEM_TYPE value[3]; // 数据数组
    value[0] = 100;
    value[1] = 200;
    value[2] = 300;

    create_list_tail(head, value, 3); // 创建    尾插法  元素在表中的排列：100，200，300

    // 按值查找
    LNode *node; // 结点指针

    node = find_node(head, 100); // 按值查找

    cout << node->data << endl; // 输出：100

    // 按序查找
    node = get_node(head, 2); // 按序查找

    cout << node->data << endl; // 输出：200

    // 插入  前插
    node = (LNode *)malloc(sizeof(LNode)); // 创建新结点   结点指针指向新结点
    node->data = 400;                      // 初始化新结点的数据域

    insert_node(head, 3, node); // 插入 前插 元素在表中的排列：100，200，400，300

    // 插入  扩展：前插转后插
    node = (LNode *)malloc(sizeof(LNode)); // 创建新结点   结点指针指向新结点
    node->data = 500;                      // 初始化新结点的数据域

    insert_node_exten(head, 3, node); // 插入    扩展：前插转后插    元素在表中的排列：100，200，500，400，300

    LNode *p;       // 移动结点指针
    p = head->next; // 初始化移动结点指针 指向第一个结点（头结点的下一个结点）

    while (p != NULL) // 遍历
    {
        cout << p->data << endl; // 输出：100，200，500，400，300

        p = p->next; // 移动结点指针
    }

    // 删除  前删
    delele_node(head, 3); // 删除  前删  元素在表中的排列：100，200，400，300

    // 删除  前删转后删
    delele_node_exten(head, 3); // 删除  前删转后删  元素在表中的排列：100，200，300

    p = head->next; // 初始化移动结点指针 指向第一个结点（头结点的下一个结点）

    while (p != NULL) // 遍历
    {
        cout << p->data << endl; // 输出：100，200，300

        p = p->next; // 移动结点指针
    }

    // 获取表长
    int list_length = 0; // 表长

    list_length = get_length(head);

    cout << list_length << endl; // 输出：3

    // 清空
    clear_list(head);

    list_length = get_length(head);

    cout << list_length << endl; // 输出：0

    // 合并两递增表成递增表
    struct LNode *head1; // 递增表1的头指针，指向头结点或第一个结点

    ELEM_TYPE value1[3]; // 数据数组1
    value1[0] = 100;
    value1[1] = 300;
    value1[2] = 500;

    create_list_tail(head1, value1, 3); // 创建    尾插法  元素在表中的排列：100，300，500

    struct LNode *head2; // 递增表2的头指针，指向头结点或第一个结点

    ELEM_TYPE value2[3]; // 数据数组2
    value2[0] = 200;
    value2[1] = 400;
    value2[2] = 600;

    create_list_tail(head2, value2, 3); // 创建    尾插法  元素在表中的排列：200，400，600

    struct LNode *head3; // 新递增表的头指针，指向头结点或第一个结点

    merge_list_increase(head1, head2, head3); // 合并两递增表成递增表

    p = head3->next;  // 移动结点指针    指向新递增表的第一个结点
    while (p != NULL) // 遍历
    {
        cout << p->data << endl; // 输出：100，200，300，400，500，600

        p = p->next; // 移动结点指针
    }

    // 合并两递增表成递减少表
    create_list_tail(head1, value1, 3); // 创建    尾插法  元素在表中的排列：100，300，500
    create_list_tail(head2, value2, 3); // 创建    尾插法  元素在表中的排列：200，400，600
    clear_list(head3);                  // 清空

    merge_list_reduce(head1, head2, head3); // 合并两递增表成递减表

    p = head3->next;  // 移动结点指针    指向新递减表的第一个结点
    while (p != NULL) // 遍历
    {
        cout << p->data << endl; // 输出：600，500，400，300，200，100

        p = p->next; // 移动结点指针
    }

    return;
}

// 函数定义————————————————————
// 创建  头插法
// 时间复杂度：O(n)
// 注意：参数使用*&，指向指针的引用数据类型
// 若只使用*，指针数据类型，在函数体中并未进行解引用调用修改*head的值，使用malloc()修改的是head的值
// 所以是值拷贝，函数返回后数据丢失。地址拷贝需要引用数据类型的配合
void create_list_head(LNode *&head, ELEM_TYPE value[], int count) // 参数：头指针，数据数组，数据数量
{
    head = (LNode *)malloc(sizeof(LNode)); // 创建头结点，头指针指向头结点
    head->next = NULL;                     // 初始化头结点的指针域

    LNode *node; // 新结点指针

    for (int i = 0; i < count; i++) // 循环创建链表
    {
        node = (LNode *)malloc(sizeof(LNode)); // 创建新结点，新结点指针指向新结点
        node->data = value[i];                 // 初始化新结点的数据域

        node->next = head->next; // 初始化新结点的指针域
        head->next = node;
        // 插入到链表的头结点和前一新结点之间
        // 链表描述：头结点->当前新结点->前一新结点->...->空
        // 若无头结点：head=node;
    }

    return;
}

// 创建  尾插法
// 时间复杂度：O(n)
void create_list_tail(LNode *&head, ELEM_TYPE value[], int count) // 参数：头指针，数据数组，数据数量
{
    head = (LNode *)malloc(sizeof(LNode)); // 创建头结点，头指针指向头结点
    head->next = NULL;                     // 初始化头结点的指针域

    LNode *tail; // 尾指针，尾指针始终指向最后一个结点
    tail = head; // 初始化尾指针  指向最后一个结点（头结点）

    LNode *node; // 新结点指针

    for (int i = 0; i < count; i++) // 循环创建链表
    {
        node = (LNode *)malloc(sizeof(LNode)); // 创建新结点，新结点指针指向新结点
        node->data = value[i];                 // 初始化新结点的数据域

        tail->next = node; // 插入到链表的头结点和前一新结点之间
        tail = tail->next; // 移动尾指针
        // 或者tail=node;
    }

    tail->next = NULL; // 尾指针指向空   创建完成
    // 链表描述：头结点->...->前一新结点->当前新结点->空

    return;
}

// 按值查找
// 时间复杂度：O(n)
LNode *find_node(LNode *head, ELEM_TYPE elem) // 参数：头指针，元素  返回值：结点指针
{
    LNode *p;       // 移动结点指针
    p = head->next; // 初始化移动结点指针 指向第一个结点（头结点的下一个结点）

    while (p != NULL) // 遍历
    {
        if (p->data == elem) // 匹配
        {
            break; // 退出查找
        }

        p = p->next; // 若不匹配，移动结点指针
    }

    return p; // 若找到返回结点指针，否则返回空指针
}

// 按序查找
// 时间复杂度：O(n)
LNode *get_node(LNode *head, int i) // 参数：头指针，元素查找的位置   返回值：结点指针
{
    LNode *p;       // 移动结点指针
    p = head->next; // 初始化移动结点指针 指向第一个结点（头结点的下一个结点）

    if (i < 0) // 不存在负数的位置
    {
        return NULL; // 返回空指针
    }

    if (i == 0) // 第0个位置是头结点
    {
        return head; // 返回头指针
    }

    for (int j = 1; j < i; j++) // 遍历
    {

        if (p != NULL) // 不匹配
        {
            p = p->next; // 移动结点指针
        }
        else // 匹配
        {
            break; // 退出查找
        }
    }

    return p; // 若找到返回结点指针，否则返回空指针
}

// 插入  前插
// 时间复杂度：O(n)
// 因为需遍历找到元素插入位置之前的结点
void insert_node(LNode *&head, int posi, LNode *node) // 参数：头指针，元素插入的位置，结点
{
    LNode *p;                     // 移动结点指针
    p = get_node(head, posi - 1); // 初始化移动结点指针 指向第posi-1个位置的结点

    node->next = p->next; // 插入 在第posi-1个位置的结点之后，占据第posi个位置，在原第posi个位置的结点之前
    p->next = node;

    return;
}

// 插入  扩展：前插转后插
// 时间复杂度：O(1)
// 直接在元素插入位置之后的结点插入，再交换结点数据
void insert_node_exten(LNode *&head, int posi, LNode *node) // 参数：头指针，元素插入的位置，结点
{
    LNode *p;                 // 移动结点指针
    p = get_node(head, posi); // 初始化移动结点指针 指向第posi个位置的结点

    node->next = p->next; // 插入 在第posi个位置的结点之后
    p->next = node;

    ELEM_TYPE temp; // 临时数据

    temp = p->data; // 交换第posi个位置的结点和新结点的数据
    p->data = node->data;
    node->data = temp;

    return;
}

// 删除  前删
// 时间复杂度：O(n)
// 因为需遍历找到元素删除位置之前的结点
void delele_node(LNode *&head, int posi) // 参数：头指针，元素删除的位置
{
    LNode *p;                     // 移动结点指针
    p = get_node(head, posi - 1); // 初始化移动结点指针 指向第posi-1个位置的结点

    LNode *q;    // 被删结点指针
    q = p->next; // 初始化被删结点指针 指向第posi个位置的结点

    p->next = q->next; // 修改指针指向   第posi-1个位置的结点的指针指向第posi+1个位置的结点
    // 或者p->next=p->next->next;

    free(q); // 删除被删结点指针指向的结点，释放内存
}

// 删除  前删转后删
// 时间复杂度：O(1)
// 交换结点数据，直接删除元素删除位置之后的结点
void delele_node_exten(LNode *&head, int posi) // 参数：头指针，元素删除的位置
{
    LNode *p;                 // 移动结点指针
    p = get_node(head, posi); // 初始化移动结点指针 指向第posi个位置的结点

    LNode *q;    // 被删结点指针
    q = p->next; // 初始化被删结点指针 指向第posi+1个位置的结点

    p->data = q->data; // 交换第posi个位置和第posi+1个位置结点的数据 此时需删除的是第posi+1个位置的结点
    // 或者p->data=p->next->data
    p->next = q->next; // 修改指针指向   第posi个位置的结点的指针指向第posi+2个位置的结点
    // 或者p->next=p->next->next;

    free(q); // 删除被删结点指针指向的结点，释放内存
}

// 获取表长
int get_length(LNode *head) // 参数：头指针  返回值：表长
{
    LNode *p;       // 移动结点指针
    p = head->next; // 初始化移动结点指针 指向第一个结点（头结点的下一个结点）

    int length = 0; // 表长

    while (p != NULL) // 遍历 有结点
    {
        length++;    // 表长递增
        p = p->next; // 移动指针
    }

    return length; // 返回表长
}

// 清空
void clear_list(LNode *&head) // 参数：头指针
{
    LNode *p;       // 被删结点指针
    p = head->next; // 初始化被删结点指针 指向第一个结点（头结点的下一个结点）

    LNode *q; // 记录结点指针 指向被删结点的下一个结点

    while (p != NULL) // 遍历    有结点
    {
        q = p->next; // 记录被删结点的下一个结点

        free(p); // 删除被删结点指针指向的结点，释放内存

        p = q; // 移动指针    指向下一个被删结点
    }

    head->next = NULL; // 头结点的指针域置空 当退出遍历时已无数据结点
}

// 合并两递增表成递增表
// 思路：遍历两递增表，比较结点的数值域数据，使用尾插法创建新递增表
// 参数：递增表1的头指针，递增表2的头指针，新递增表的头指针
void merge_list_increase(LNode *head1, LNode *head2, LNode *&head3)
{
    LNode *p;        // 移动结点指针1
    p = head1->next; // 初始化移动结点指针1 指向递增表1的第一个结点（头结点的下一个结点）

    LNode *q;        // 移动结点指针2
    q = head2->next; // 初始化移动结点指针2 指向递增表2的第一个结点（头结点的下一个结点）
    free(head2);     // 释放递增表2的头结点  因为已用移动结点指针2记录递增表2的第一个结点，数据不会丢失

    head3 = head1;      // 初始化新递增表的头指针 指向递增表1的头结点，用递增表1的头结点作为新递增表的头结点
    head3->next = NULL; // 初始化新递增表头结点的指针域，置空  因为已用移动结点指针1记录递增表1的第一个结点，数据不会丢失

    LNode *tail;  // 新递增表的尾指针    始终指向新递增表的终端结点
    tail = head3; // 初始化新递增表的尾指针  初始时新递增表为空，尾指针指向头结点

    while ((p != NULL) && (q != NULL)) // 遍历两递增表
    {
        if (p->data <= q->data) // 比较结点的数值域数据
        {
            tail->next = p; // 将数据域数值小的结点插入新递增表表尾

            p = p->next;       // 递增表1的当前结点已插入新递增表，更新移动结点指针1
            tail = tail->next; // 更新新递增表的尾指针  始终指向新递增表的终端结点
        }
        else // 同理
        {
            tail->next = q;

            q = q->next;
            tail = tail->next;
        }
    }

    tail->next = NULL;
    // 可以没有，因为最后还要将未插入的结点插入新递增表表尾，未插入结点的终端结点指针域为空

    if (p != NULL) // 若递增表2插入完成，递增表1还有未插入结点，则将剩余结点插入新递增表尾部
    {
        tail->next = p;
    }
    if (q != NULL) // 若递增表1合并完成，递增表2还有未插入结点，则将剩余结点插入新递增表尾部
    {
        tail->next = q;
    }

    return;
}

// 合并两递增表成递减表
// 思路：遍历两递增表，比较结点的数值域数据，使用头插法创建新递减表
// 参数：递增表1的头指针，递增表2的头指针，新递增表的头指针
void merge_list_reduce(LNode *head1, LNode *head2, LNode *&head3)
{
    LNode *p;        // 移动结点指针1
    p = head1->next; // 初始化移动结点指针1 指向递增表1的第一个结点（头结点的下一个结点）

    LNode *q;        // 移动结点指针2
    q = head2->next; // 初始化移动结点指针2 指向递增表2的第一个结点（头结点的下一个结点）
    free(head2);     // 释放递增表2的头结点  因为已用移动结点指针2记录递增表2的第一个结点，数据不会丢失

    head3 = head1;      // 初始化新递减表的头指针 指向递增表1的头结点，用递增表1的头结点作为新递减表的头结点
    head3->next = NULL; // 初始化新递减表头结点的指针域  因为已用移动结点指针1记录递增表1的第一个结点，数据不会丢失

    LNode *temp; // 临时结点指针 指向当前要插入新递减表表头的结点

    while ((p != NULL) && (q != NULL)) // 遍历两递增表
    {
        if (p->data <= q->data) // 比较结点的数值域数据
        {
            temp = p;    // 将临时结点指针指向数据域数值小的结点
            p = p->next; // 递增表1的当前结点已被临时结点指针记录，更新移动结点指针1

            temp->next = head3->next; // 将临时结点指针指向头结点的下一个结点
            head3->next = temp;       // 将头指针指向当前要插入新递减表表头的结点
        }
        else // 同理
        {
            temp = q;
            q = q->next;

            temp->next = head3->next;
            head3->next = temp;
        }
    }

    if (p != NULL) // 若递增表2插入完成，递增表1还有未插入结点，则取剩余结点一个个插入新递减表表头
    {
        temp = p;
        p = p->next;

        temp->next = head3->next;
        head3->next = temp;
    }
    if (q != NULL) // 若递增表1插入完成，递增表2还有未插入结点，则取剩余结点一个个插入新递减表表头
    {
        temp = q;
        q = q->next;

        temp->next = head3->next;
        head3->next = temp;
    }

    return;
}