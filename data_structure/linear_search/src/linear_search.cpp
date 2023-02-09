// 头文件————————————————————
#include <iostream>
#include <vector>

// 命名空间
using namespace std;

// 自定义数据类型————————————————————
typedef int ELEM_TYPE; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 定义
// 分块查找中，索引表元素
typedef struct IndexElem
{
    ELEM_TYPE maxKey; // 键值分量：各块的最大关键字
    ELEM_TYPE first;  // 链值分量：各块的第一条记录的地址/指针
} IndexElem;
// struct IndexElem：结构体数据类型的名称
// 如创建一个索引表元素的语句：struct IndexElem elem;
// 若结构体数据类型内，存在指向该结构体的指针数据类型，则必须完整命名结构体数据类型的名称
// 如索引表元素结构体IndexElem内，若存在指向该结构体的指针数据类型，则命名语句为：typedef struct IndexElem而不是typedef struct
// }IndexElem;：typedef给结构体数据类型起的别名，可简化语句
// 如创建一个索引表元素的语句：IndexElem elem;
// 结构体数据类型的名称和别名尽量一致，以方便记忆、使用

// 函数声明————————————————————
void use_example();                                             // 使用示例
int seqSearch(const vector<ELEM_TYPE> &sTable, ELEM_TYPE sKey); // 顺序/线性查找  无序顺序表
int seqSearch2(vector<ELEM_TYPE> &sTable2, ELEM_TYPE sKey);     // 顺序/线性查找  无序顺序表    使用哨兵机制
int binSearch(const vector<ELEM_TYPE> &sTable, ELEM_TYPE sKey); // 折半/二分查找
int insSearch(const vector<ELEM_TYPE> &sTable, ELEM_TYPE sKey); // 插值查找
int fibSearch(vector<ELEM_TYPE> &sTable3, ELEM_TYPE sKey);      // 斐波那契查找

// 函数定义————————————————————
// 使用示例
void use_example()
{
    // 顺序/线性查找 无序顺序表————————————————————
    const vector<ELEM_TYPE> sTable = {1, 2, 3, 4, 5}; // 创建查找表 向量数据类型的常量

    int sResult = -1; // 查找结果
    // 约定：
    // 查找成功：返回记录的位置，记录的位置>-1
    // 查找失败：返回-1

    sResult = seqSearch(sTable, 3); // 顺序/线性查找 无序顺序表
    cout << sResult << endl;        // 输出：2

    // 顺序/线性查找 无序顺序表    使用哨兵机制————————————————————
    // 约定：第一个位置为哨兵    -1为无效数据
    vector<ELEM_TYPE> sTable2 = {-1, 2, 3, 4, 5}; // 创建查找表2

    // 约定：
    // 查找成功：返回记录的位置，记录的位置>0
    // 查找失败：返回0

    sResult = seqSearch2(sTable2, 3); // 顺序/线性查找   无序顺序表    使用哨兵机制
    cout << sResult << endl;          // 输出：2

    // 折半/二分查找————————————————————
    sResult = binSearch(sTable, 3); // 折半/二分查找
    cout << sResult << endl;        // 输出：2

    // 插值查找————————————————————
    sResult = insSearch(sTable, 3); // 插值查找
    cout << sResult << endl;        // 输出：2

    // 斐波那契查找————————————————————
    vector<ELEM_TYPE> sTable3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 创建查找表3

    sResult = fibSearch(sTable3, 3); // 斐波那契查找
    cout << sResult << endl;
    // 输出：
    // 斐波那契数列：0 1 1 2 3 5 8 13 21 34
    // 基准斐波那契数的下标：7
    // 查找表：1 2 3 4 5 6 7 8 9 10 10
    //  2

    // 分块/索引顺序查找————————————————————
    struct IndexElem indexTable[10]; // 创建索引表

    return;
}

// 顺序/线性查找 无序顺序表
// 适用：
// 线性表
// 注意：有序线性表的顺序查找和有序顺序表的折半查找，思想不同
// 平均查找长度（ASL）：
// 查找成功：(n+1)/2。n为数据规模
// 查找失败：n或n+1（使用哨兵机制）
// 时间复杂度：O(n)
// 空间复杂度：O(1)。未使用额外辅助空间
// 有序表查找失败的平均查找长度（ASL）：n/2+n/(n+1)。其他相同
int seqSearch(const vector<ELEM_TYPE> &sTable, ELEM_TYPE sKey) // 参数：查找表，需查找的关键字
{
    for (int i = 0; i < sTable.size(); ++i) // 循环遍历
    {
        if (sTable[i] == sKey) // 查找成功
        {
            return i;
        }
    }

    return -1; // 查找失败
}

// 顺序/线性查找 无序顺序表    使用“哨兵”机制
int seqSearch2(vector<ELEM_TYPE> &sTable2, ELEM_TYPE sKey) // 参数：查找表，需查找的关键字
{
    // 约定：第一个位置为哨兵
    sTable2[0] = sKey; // 设置哨兵

    int i = sTable2.size() - 1; // 循环变量
    while (sTable2[i] != sKey)  // 循环遍历    每循环只比较1次而不是2次
    {
        --i;
    }

    return i; // 查找成功或查找失败
}

// 折半/二分查找
// 适用：
// 有序顺序表
// 平均查找长度（ASL）：[log以2为底的(n+1)]-1。n为数据规模
// 时间复杂度：O(logn)
// 空间复杂度：O(1)。未使用额外辅助空间
int binSearch(const vector<ELEM_TYPE> &sTable, ELEM_TYPE sKey) // 参数：查找表，需查找的关键字
{
    // 约定：
    // 采用递增/升序排序
    // 循环不变量原则：左闭右闭为有效区间

    int left = 0;                  // 左位置的指针
    int right = sTable.size() - 1; // 右位置的指针

    while (left <= right) // 当左位置的指针<=右位置的指针时，循环
    {
        int mid = (left + right) / 2; // 中间位置的指针  注意：下取整
        // int mid = left + (right - left) / 2;

        if (sTable[mid] == sKey) // 查找成功
        {
            return mid;
        }
        else if (sTable[mid] > sKey) // 中间位置的的值比需查找的关键字大
        {
            right = mid - 1; // 在左半边区间查找
        }
        else if (sTable[mid] < sKey) // 中间位置的的值比需查找的关键字小
        {
            left = mid + 1; // 在左半边区间查找
        }
    }

    return -1; // 查找失败
}

// 插值查找
// 适用：
// 有序顺序表
// 时间复杂度：O(logn)。n为数据规模
// 空间复杂度：O(1)。未使用额外辅助空间
// 若数据规模大，关键字分布均匀，则性能优于折半查找
int insSearch(const vector<ELEM_TYPE> &sTable, ELEM_TYPE sKey) // 参数：查找表，需查找的关键字
{
    // 约定：
    // 采用递增/升序排序
    // 循环不变量原则：左闭右闭为有效区间

    int left = 0;                  // 左位置的指针
    int right = sTable.size() - 1; // 右位置的指针

    while (left <= right) // 当左位置的指针<=右位置的指针时，循环
    {
        int mid = left + (right - left) * (sKey - sTable[left]) / (sTable[right] - sTable[left]); // 插值位置的指针  注意：下取整
        // 与折半查找唯一不同的地方
        // 折半查找：int mid = left + (right - left) / 2;
        // 插值公式：(sKey - sTable[left]) / (sTable[right] - sTable[left])
        // 核心思想：依据需要查找的值动态确定区间的缩减幅度
        // 若(sKey - sTable[left]) / (sTable[right] - sTable[left])大，则mid大
        // 即：在区间范围内，需要查找的值与左边界相对差大，则插值位置应靠右
        // 若(sKey - sTable[left]) / (sTable[right] - sTable[left])小，则mid小
        // 即：在区间范围内，需要查找的值与左边界相对差小，则插值位置应靠左

        if (sTable[mid] == sKey) // 查找成功
        {
            return mid;
        }
        else if (sTable[mid] > sKey) // 插值位置的的值比需查找的关键字大
        {
            right = mid - 1; // 在左半边区间查找
        }
        else if (sTable[mid] < sKey) // 插值位置的的值比需查找的关键字小
        {
            left = mid + 1; // 在左半边区间查找
        }
    }

    return -1; // 查找失败
}

// 斐波那契查找
// 适用：
// 有序顺序表
// 时间复杂度：O(logn)。n为数据规模
// 空间复杂度：O(n)。n为斐波那契数列的大小
// 通常性能优于折半查找
// 核心思想
//  1.创建大小合适的斐波那契数列
//  2.获取基准斐波那契数的下标：基准斐波那契数-1刚好>=查找表的大小
//  3.如果查找表的大小<基准斐波那契数-1：查找时，分隔值的下标对查找表可能越界，需要扩充查找表
//  4.查找
int fibSearch(vector<ELEM_TYPE> &sTable3, ELEM_TYPE sKey) // 参数：查找表，需查找的关键字
{
    // 1.创建大小合适的斐波那契数列
    // 大小合适：
    // 依据第2步：获取基准斐波那契数的下标：基准斐波那契数-1刚好>=查找表的大小
    // 即：斐波那契数列中，存在一个斐波那契数，该斐波那契数-1>=查找表的大小
    // 若:
    // 查找表的大小为1，查找表 = {2}
    // 斐波那契数列大小为1，斐波那契数列 = {0}
    // 有0 - 1 < 2，不满足条件
    // 若:
    // 查找表的大小为1，查找表 = {2}
    // 斐波那契数列大小为5，斐波那契数列 = {0,1,1,2,3}
    // 有3 - 1 >= 2，满足条件
    vector<int> f(10, 0); // 大小合适，初始化为0

    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i < 10; ++i)
    {
        f[i] = f[i - 2] + f[i - 1];
    }

    // 输出斐波那契数列
    cout << "斐波那契数列：";
    for (int num : f)
    {
        cout << num << " ";
    }
    cout << endl;

    // 2.获取基准斐波那契数的下标：基准斐波那契数-1刚好>=查找表的大小
    int index = 0; // 斐波那契数的下标

    // while (f[index] - 1 < sTable3.size()) //会判断为false跳过循环，导致错误
    // while (f[index] < sTable3.size()) //无错误
    int tmp = sTable3.size(); // 临时变量存储查找表的大小
    while (f[index] - 1 < tmp)
    {
        ++index;
    }

    // 输出基准斐波那契数的下标
    cout << "基准斐波那契数的下标：" << index << endl;

    // 3.如果查找表的大小<基准斐波那契数-1：查找时，分隔值的下标对查找表可能越界，需要扩充查找表
    // 扩充查找表的大小=基准斐波那契数-1
    // 理由：统一格式，方便循环或者递归的编写
    // 由斐波那契数列的性质：f[index - 2] + f[index - 1] = f[index]
    // 总共有f[index] -  1个元素
    // mid为下标有1个元素
    // 剩余f[index] - 2个元素：f[index] - 2 = (f[index - 2] - 1) + (f[index - 1] - 1)
    // 左区间有f[index - 1] - 1个元素
    // 右区间有f[index - 2] - 1个元素
    // 左、右区间元素个数的格式与之前统一
    // 否则有可能是f[index - 2]、f[index - 2] - 1、f[index - 1]、f[index - 1] - 1
    // 查找表中，下标为原查找表大小到斐波那契数-1-1的值=下标为原查找表大小-1的查找表值 即扩充值=原查找表最右边的值

    // 验证：
    // 斐波那契数列 = {0,1,1,2,3,5,8,13,21,34}
    // 查找表 = {1,2,3,4,5,6,7,8,9,10,10,10}
    // 第一次循环：
    //  index = 7
    //  f[index - 1] = f[6] = 8
    //  f[index - 1] - 1 = f[6] - 1 = 8 - 1 = 7
    //  left = 0
    //  mid = left +  f[index - 1] - 1 = 0 + 7 = 7   注意：针对下标
    // 分隔值：sTable[7] = 8
    // 左区间 = {1,2,3,4,5,6,7}  有f[index - 1] - 1 = 7个元素
    // 右区间 = {9,10,10,10} 有f[index - 2] - 1 = f[5] - 1 = 5- 1 = 4个元素
    // 以此类推
    int oldSize = sTable3.size(); // 记录原查找表的大小 在第4步需要使用

    if (sTable3.size() < f[index])
    {
        // 查找表中，下标为原查找表大小到斐波那契数 - 1 - 1的值=下标为原查找表大小-1的查找表值 即扩充值=原查找表最右边的值
        // 斐波那契数 - 1：针对大小
        // 斐波那契数 - 1 - 1：针对下标
        for (int i = sTable3.size(); i < f[index] - 1 - 1; ++i)
        {
            sTable3.push_back(sTable3[sTable3.size() - 1]); // 注意：sTable3.size()+1
        }
    }

    // 输出查找表
    cout << "查找表：";
    for (ELEM_TYPE num : sTable3)
    {
        cout << num << " ";
    }
    cout << endl;

    // 4.查找
    // 约定：
    // 采用递增/升序排序
    // 循环不变量原则：左闭右闭为有效区间

    int left = 0;                   // 左位置的指针
    int right = sTable3.size() - 1; // 右位置的指针

    // 测试案例：sKey>10，如=11时，left和mid不变，index不断-1，<0无效时仍进入循环导致错误
    while (left <= right && index >= 0) // 当左位置的指针<=右位置的指针且基准斐波那契数的下标有效时，循环
    {
        // 见第3步的解析
        // 左区间有f[index - 1] - 1个元素
        // 分隔值的元素是第f[index - 1] - 1 + 1个
        // 因为下标从0开始，所以分隔值的位置：f[index - 1] - 1
        int mid = left + f[index - 1] - 1; // 分隔值位置的指针

        if (sTable3[mid] == sKey) // 查找成功
        {
            if (mid < oldSize) // oldSize针对下标 分隔值位置的指针<原查找表的大小，对原查找表未越界
            {
                return mid; // 分隔值位置的指针即查找位置
            }
            else // 分隔值位置的指针>=原查找表的大小，对原查找表越界
            {
                // 在第3步：扩充值=原查找表最右边的值
                // 对原查找表越界的位置/扩充值查找成功->对原查找表最右边的值查找成功
                // 原查找表最右边的值的下标即查找位置
                return oldSize - 1;
            }
        }
        else if (sTable3[mid] > sKey) // 分隔值位置的的值比需查找的关键字大
        {
            right = mid - 1; // 在左半边区间查找

            index = index - 1; // 更新基准斐波那契数的下标
        }
        else if (sTable3[mid] < sKey) // 分隔值位置的的值比需查找的关键字小
        {
            left = mid + 1; // 在左半边区间查找

            index = index - 2; // 更新基准斐波那契数的下标
        }
        // 见第3步解析
        // 左区间有f[index - 1] - 1个元素    更新基准斐波那契数的下标-1
        // 右区间有f[index - 2] - 1个元素    更新基准斐波那契数的下标-2
    }

    return -1; // 查找失败
}

// 主函数————————————————————
int main()
{
    use_example(); // 使用示例

    return 0;
}