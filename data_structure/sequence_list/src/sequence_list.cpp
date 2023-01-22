// 头文件————————————————————
#include <iostream>
using namespace std;

// 宏————————————————————
#define MAX_SIZE 100 // 最大大小

// 自定义数据类型————————————————————
typedef int ELEM_TYPE; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 定义
typedef struct
{
    ELEM_TYPE data[MAX_SIZE]; // 数据
    int length;               // 当前长度
    // 最大大小>=当前长度
} SqList;

// 函数声明————————————————————
void use_example();                                          // 使用示例
void init_list(SqList &sqList);                              // 初始化
bool insert_elem(SqList &sqList, int posi, ELEM_TYPE elem);  // 插入
bool delete_elem(SqList &sqList, int posi, ELEM_TYPE &elem); // 删除
int find_elem(SqList sqList, ELEM_TYPE elem);                // 按值查找
bool get_elem(SqList sqList, int posi, ELEM_TYPE &elem);     // 按序查找

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
    SqList sqList;

    // 初始化
    init_list(sqList);
    cout << sqList.length << endl; // 输出：0

    // 插入
    ELEM_TYPE ins_elem1 = 100;
    ELEM_TYPE ins_elem3 = 300;
    ELEM_TYPE ins_elem2 = 200;

    insert_elem(sqList, 1, ins_elem1);
    insert_elem(sqList, 2, ins_elem3);
    insert_elem(sqList, 2, ins_elem2); // 元素在表中的排列：100，200，300

    // 删除
    ELEM_TYPE del_elem = 0;

    delete_elem(sqList, 2, del_elem); // 元素在表中的排列：100，300

    cout << del_elem << endl; // 输出：200

    // 按值查找
    int fin_posi = 0;
    ELEM_TYPE fin_elem = 100;

    fin_posi = find_elem(sqList, fin_elem);

    cout << fin_posi << endl; // 输出：1

    // 获取元素
    ELEM_TYPE ge_elem = 0;

    get_elem(sqList, 2, ge_elem);

    cout << ge_elem << endl; // 输出：300

    return;
}

// 初始化
void init_list(SqList &sqList) // 参数：表
{
    sqList.length = 0; // 当前长度为0
}

// 注意：元素的位置=数组下标+1
// 插入
// 时间复杂度：O(n)
bool insert_elem(SqList &sqList, int posi, ELEM_TYPE elem) // 参数：表，元素的插入位置，元素
{
    if (posi < 1 || posi > sqList.length + 1) // 元素的插入位置不合法
    {
        return false;
    }
    // 元素的合法插入位置为表的第一个位置到最后一个位置的后一个位置

    if (sqList.length == MAX_SIZE) // 表满
    {
        return false;
    }
    // 判决条件可以是：>=

    for (int i = sqList.length; i >= posi; i--) // 元素移动位置
    {
        sqList.data[i] = sqList.data[i - 1];
    }
    // 临界条件不容易理解
    // 需移动length-posi+1个元素

    sqList.data[posi - 1] = elem; // 插入
    sqList.length++;              // 表长增加

    return true;
}

// 删除
// 时间复杂度：O(n)
bool delete_elem(SqList &sqList, int posi, ELEM_TYPE &elem) // 参数：表，元素的删除位置，元素
{
    if (posi < 1 || posi > sqList.length) // 元素的删除位置不合法
    {
        return false;
    }
    // 元素的合法删除位置为表的第一个位置到最后一个位置

    if (sqList.length == 0) // 表空
    {
        return false;
    }

    elem = sqList.data[posi - 1]; // 获取删除的元素

    for (int i = posi; i < sqList.length; i++) // 元素移动位置
    {
        sqList.data[i - 1] = sqList.data[i];
    }
    // 临界条件不容易理解
    // 需移动length-posi个元素

    sqList.length--; // 表长减少

    return true;
}

// 按值查找
// 时间复杂度：O(n)
int find_elem(SqList sqList, ELEM_TYPE elem) // 参数：表，元素   返回值：元素在表中的位置
{
    for (int i = 0; i < sqList.length; i++) // 遍历表
    {
        if (sqList.data[i] == elem) // 查找到
        {
            return i + 1;
        }
    }

    return 0;
}

// 按序查找
// 时间复杂度：O(1)
bool get_elem(SqList sqList, int posi, ELEM_TYPE &elem) // 参数：表，元素的获取位置，元素
{
    if (posi < 1 || posi > sqList.length) // 元素的查找位置不合法
    {
        return false;
    }
    // 元素的合法查找位置为表的第一个位置到最后一个位置

    if (sqList.length == 0) // 表空
    {
        return false;
    }

    elem = sqList.data[posi - 1]; // 获取元素

    return true;
}
