// 头文件————————————————————
#include <iostream>
#include <vector>

// 命名空间
using namespace std;

// 自定义数据类型————————————————————
typedef int ELEM_TYPE; // 数据的（数据）类型 依据数据的实际类型定义

// 函数声明————————————————————
void use_example();                        // 使用示例
void insertSort(vector<ELEM_TYPE> &elems); // 直接插入排序
void binarySort(vector<ELEM_TYPE> &elems); // 折半插入排序
void shellSort(vector<ELEM_TYPE> &elems);  // 希尔排序

void bubbleSort1(vector<ELEM_TYPE> &elems);                    // 冒泡排序    简单版
void bubbleSort2(vector<ELEM_TYPE> &elems);                    // 冒泡排序  正版
void bubbleSort3(vector<ELEM_TYPE> &elems);                    // 冒泡排序  改进版
void quickSort(vector<ELEM_TYPE> &elems, int left, int right); // 快速排序

void selectSort(vector<ELEM_TYPE> &elems);                    // 简单选择排序
void heapAdjust(vector<ELEM_TYPE> &elems, int low, int high); // 堆调整    大顶堆法
void heapSort(vector<ELEM_TYPE> &elems);                      // 堆排序  大顶堆法

void merge(vector<ELEM_TYPE> &elems, int low, int mid, int high); // 二路归并
void mergeSort(vector<ELEM_TYPE> &elems, int low, int high);      // 二路归并排序   递归法  分治法

// 函数定义————————————————————
// 使用示例
void use_example()
{
    // 创建
    vector<ELEM_TYPE> elems = {4, 2, 1, 3, 5}; // 需排序元素的向量

    // 插入类排序————————————————————
    insertSort(elems); // 直接插入排序

    cout << "直接插入排序: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：直接插入排序：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    binarySort(elems); // 折半插入排序

    cout << "折半插入排序: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：折半插入排序：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    shellSort(elems); // 希尔排序

    cout << "希尔排序: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：希尔排序：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    // 交换类排序————————————————————
    bubbleSort1(elems); // 冒泡排序    简单版

    cout << "冒泡排序    简单版: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：冒泡排序    简单版：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    bubbleSort2(elems); // 冒泡排序  正版

    cout << "冒泡排序    正版: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：冒泡排序    正版：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    bubbleSort3(elems); // 冒泡排序  改进版

    cout << "冒泡排序    改进版: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：冒泡排序    改进版：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    // 快速排序
    quickSort(elems, 0, elems.size() - 1);

    cout << "快速排序: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：快速排序：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    // 选择类排序————————————————————
    // 简单选择排序
    selectSort(elems);

    cout << "简单选择排序: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：简单选择排序：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    // 堆排序    大顶堆法
    heapSort(elems);

    cout << "堆排序    大顶堆法: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：堆排序    大顶堆法：4 1 2 3 5
    // 注意：第一个元素不参与排序

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    // 归并类排序————————————————————
    // 二路归并排序   递归法  分治法
    mergeSort(elems, 0, elems.size() - 1);
    // 注意：闭区间

    cout << "二路归并排序   递归法  分治法: ";
    for (int elem : elems)
    {
        cout << elem << " ";
    }
    cout << endl;
    // 输出：二路归并排序   递归法  分治法：1 2 3 4 5

    // 恢复需排序元素向量
    elems[0] = 4;
    elems[1] = 2;
    elems[2] = 1;
    elems[3] = 3;
    elems[4] = 5;

    return;
}

// 直接插入排序
// 时间复杂度：O(n²)。n为数据规模
// 时间复杂度：数据规模×比较次数
// 最好：O(n)。n为数据规模。（有序）
// 平均：O(n²)。n为数据规模
// 最坏：O(n²)。n为数据规模。（无序的逆序）
// 空间复杂度：O(1)。未使用额外辅助空间
// 稳定性：稳定
void insertSort(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    int i = 0; // 循环变量
    int j = 0;
    int temp = 0; // 需排序元素

    // 第一个元素values[0]前无元素，不需要排序
    // 从第二个元素values[1]开始遍历，需要排序
    for (i = 1; i < elems.size(); ++i)
    {
        temp = elems[i]; // 记录需排序元素
        // 需排序元素前的元素向后移动时，会覆盖需排序元素

        // 遍历需排序元素前的元素
        // 比较需排序元素和需排序元素前的元素
        for (j = i - 1; j >= 0; --j)
        {
            if (temp < elems[j]) // 需排序元素<需排序元素前的元素   1.比较   <：稳定性体现
            {
                elems[j + 1] = elems[j]; // 需排序元素前的元素向后移动 2.移动
            }
            else //>=
            {
                break;
            }
        }

        // 遍历需排序元素前的元素结束时：需排序元素>=需排序元素前的元素    有插入位置
        elems[j + 1] = temp; // 插入
    }

    return;
}

// 折半插入排序
// 时间复杂度：O(n²)。n为数据规模
// 时间复杂度：数据规模×比较次数
// 最好：O(nlogn)。n为数据规模
// 平均：O(n²)。n为数据规模
// 最坏：O(n²)。n为数据规模
// 空间复杂度：O(1)。未使用额外辅助空间
// 稳定性：稳定
void binarySort(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    int i = 0; // 循环变量
    int j = 0;
    int temp = 0; // 需排序元素

    int left = 0;                 // 左位置指针
    int right = elems.size() - 1; // 右位置指针
    int mid = 0;                  // 中间位置指针

    // 第一个元素elems[0]前无元素，不需要排序
    // 从第二个元素elems[1]开始遍历，需要排序
    for (i = 1; i < elems.size(); ++i)
    {
        temp = elems[i]; // 记录需排序元素
        // 需排序元素前的元素向后移动时，会覆盖需排序元素

        // 折半查找插入位置  1.比较
        left = 0;      // 更新左位置指针
        right = i - 1; // 更新右位置指针
        // 查找范围：0~i-1

        while (left <= right) // 左位置指针<=右位置指针时，循环
        {
            mid = left + (right - left) / 2; // 取中间位置

            if (temp == elems[mid]) // 需排序元素=中间位置元素时，在右区间查找    稳定性体现
            {
                left = mid + 1;
            }
            else if (temp > elems[mid]) // 需排序元素>中间位置元素，在右区间查找
            {
                left = mid + 1;
            }
            else if (temp < elems[mid]) // 需排序元素<中间位置元素，在左区间查找
            {
                right = mid - 1;
            }
        }

        // 折半查找插入位置结束时：可推导插入位置为right + 1
        //  right + 1 ~ i - 1的元素向后移动  2.移动
        for (j = i - 1; j >= right + 1; --j)
        {
            elems[j + 1] = elems[j];
        }

        elems[right + 1] = temp; // 插入
    }

    return;
}

// 希尔排序
// 时间复杂度：O(n的1.3次方)~O(n²) 。n为数据规模
// 时间复杂度：增量的函数/选取规则（仍是数学难题）
// 最好：O(n的1.3次方)。n为数据规模（n在特定范围）
//  O(n的1.5次方)。n为数据规模（增量选取规则：2的k次方+1，...，5，3，1。k为整数，k>=1，2的k次方+1 < n）
// 最坏：O(n²)。n为数据规模。（增量选取规则：[n/2]下取整，[n/4]下取整，...，1）
// 空间复杂度：O(1)。未使用额外辅助空间
// 稳定性：不稳定（依据增量划分序列时，可能改变元素的相对位置）
void shellSort(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    int i = 0; // 循环变量
    int j = 0;
    int temp = 0; // 需排序元素

    // 增量/步长范围：elems.size() / 2 ~ 1
    // 步长变化规则：step /= 2
    // 对每步长序列进行直接插入排序  类比直接插入排序过程
    for (int step = elems.size() / 2; step >= 1; step /= 2)
    {
        // 需排序元素位置：step ~ elems.size() - 1
        // 需要比较需排序元素和需排序元素前的元素，从步长的位置开始才有意义
        for (i = step; i < elems.size(); ++i)
        {
            temp = elems[i]; // 记录需排序元素
            // 需排序元素前的元素向后移动时，会覆盖需排序元素

            // 遍历需排序元素前的元素
            // 比较需排序元素和需排序元素前的元素
            // 需排序元素前的元素位置：j = i - step ~ 0
            for (j = i - step; j >= 0; j -= step)
            {
                if (temp < elems[j]) // 需排序元素<需排序元素前的元素   1.比较
                {
                    elems[j + step] = elems[j]; // 需排序元素前的元素向后移动 2.移动/交换
                }
                else //>=
                {
                    break;
                }
            }

            // 遍历需排序元素前的元素结束时：需排序元素>=需排序元素前的元素    有插入位置
            elems[j + step] = temp; // 插入
        }
    }

    return;
}

// 冒泡排序  简单版
// 时间复杂度：O(n²)。n为数据规模
// 时间复杂度：数据规模×比较次数
// 最好：O(n)。n为数据规模。（有序）
// 平均：O(n²)。n为数据规模
// 最坏：O(n²)。n为数据规模。（无序的逆序）
// 空间复杂度：O(1)。未使用额外辅助空间
// 稳定性：稳定
void bubbleSort1(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    int i = 0; // 循环变量
    int j = 0;
    int temp = 0; // 需排序元素

    // 遍历需排序元素
    // 需排序元素位置：0 ~ elems.size() - 2
    //  elems.size()个元素需elems.size() - 1次比较
    for (i = 0; i < elems.size() - 1; ++i)
    {
        // 遍历需排序元素后的元素
        // 需排序元素后的元素位置：i + 1 ~ elems.size() - 1
        for (j = i + 1; j < elems.size(); ++j)
        {
            if (elems[i] > elems[j]) // 需排序元素>需排序元素后的元素   1.比较   稳定性体现
            {
                // 2.移动/交换
                temp = elems[i];
                elems[i] = elems[j];
                elems[j] = temp;
            }
        }
    }

    return;
}

// 冒泡排序  正版
void bubbleSort2(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    int i = 0; // 循环变量
    int j = 0;
    int temp = 0; // 需排序元素

    // 遍历需排序位置
    // 需排序位置：0 ~ elems.size() - 2
    //  elems.size()个元素需elems.size() - 1次比较

    // 注意：
    // 排序位置而不是元素：一趟排序确定一个位置
    for (i = 0; i < elems.size() - 1; ++i)
    {
        // 遍历需排序位置后的元素
        // 需排序位置后的元素位置：i + 1 ~ elems.size() - 1

        // 注意：
        // 从后往前遍历
        // 两两相邻元素排序  思想体现
        for (j = elems.size() - 1; j > i; --j)
        {
            if (elems[j - 1] > elems[j]) // 前需排序元素>后需排序元素   1.比较   稳定性体现
            {
                // 2.移动/交换
                temp = elems[j - 1];
                elems[j - 1] = elems[j];
                elems[j] = temp;
            }
        }
    }

    return;
}

// 冒泡排序  改进版
void bubbleSort3(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    int i = 0; // 循环变量
    int j = 0;
    int temp = 0; // 需排序元素

    bool flag = false;
    // 标志：
    //  true：一趟排序中，有交换过程，序列无序，算法继续进行
    //  false：一趟排序中，无交换过程，序列有序，算法结束

    // 遍历需排序位置
    // 需排序位置：0 ~ elems.size() - 2
    //  elems.size()个元素需elems.size() - 1次比较

    // 注意：
    // 排序位置而不是元素：一趟排序确定一个位置
    for (i = 0; i < elems.size() - 1; ++i)
    {
        // 遍历需排序位置后的元素
        // 需排序位置后的元素位置：i + 1 ~ elems.size() - 1

        // 注意：
        // 从后往前遍历
        // 两两相邻元素排序  思想体现
        for (j = elems.size() - 1; j > i; --j)
        {
            if (elems[j - 1] > elems[j]) // 前需排序元素>后需排序元素   1.比较   稳定性体现
            {
                // 2.移动/交换
                temp = elems[j - 1];
                elems[j - 1] = elems[j];
                elems[j] = temp;

                flag = true; // 有交换过程
            }
        }

        if (flag == false) // 无交换过程
        {
            return;
        }
    }

    return;
}

// 快速排序
// 时间复杂度：O(nlogn)。n为数据规模
// 最好：O(nlogn)。n为数据规模。（无序）
// 平均：O(nlogn)。n为数据规模。
// 最坏：O(n²)。n为数据规模。（有序或无序的逆序）
// 空间复杂度：O(logn)。n为数据规模
// 空间复杂度：递归调用栈的大小/树的深度/高度
// 最好：O(logn)。n为数据规模（平衡树）
// 平均：O(logn)。n为数据规模
// 最坏：O(n)。n为数据规模（斜树）
// 稳定性：不稳定（依据枢轴划分并交换时，可能改变元素的相对位置）
// 注意：时间复杂度和空间复杂度是平均而不是最坏情况

// 快速排序的优化
//  1.枢轴选取优化
// （1）随机法
// 需排序元素的向量中，随机选取一个元素作为枢轴
// （2）三数取中法
// 需排序元素的向量中，最左位置、中间位置和最右位置的元素排序，选取中间的元素作为枢轴
// 适用小数据规模
// （3）九数取中法
// 需排序元素的向量中，取样三次，每次取三个元素得中间元素，三个中间元素得中间元素
// 可适用大数据规模
//  2.不必要交换优化
// 备份枢轴
// 左和右位置指针遍历时，进行元素替换而不是交换
// 遍历后，枢轴放到确定位置
//  3.小数据规模优化
// 设置数据规模阈值
// 若数据规模<阈值，使用直接插入排序
// 若数据规模>=阈值，使用快速排序
//  4.递归优化
// 使用尾递归/迭代
// 示例：
/*
void quickSort(...)
{
    while (left < right) //使用while
    {
        int i = left;  //逻辑处理
        int j = right;

        ...

        quickSort(elems, left, privot - 1);  //左递归
        left = prvot + 1; //右迭代
        //左递归后，left无用，赋值为prvot + 1
        //while在下次迭代，i = pivot + 1，j = right，相当于右递归的逻辑处理
    }

    ...
}
*/
void quickSort(vector<ELEM_TYPE> &elems, int left, int right) // 参数：需排序元素的向量，左位置指针，右位置指针
{
    int i = left;  // 左位置指针    用于划分
    int j = right; // 右位置指针

    if (left < right) // 左位置指针<右位置指针时，递归
    {
        // 1.划分   确定枢轴
        ELEM_TYPE privot = elems[left];
        // 当前排序表的第一个元素作为枢轴    枢轴划分当前排序表为左排序表和右排序表

        while (i < j) // 左位置指针小于右位置指针时，循环
        {
            // 左位置指针小于右位置指针时
            // 右位置指针向左移动，直到找到比枢轴小的元素
            while (i < j)
            {
                if (elems[j] >= privot) // 右位置指针>=枢轴  向左移动    1.比较
                {
                    --j;
                }
                else //<
                {
                    break;
                }
            }

            elems[i] = elems[j]; // 比枢轴小的元素放在左指针位置  2.移动/交换

            // 左位置指针小于右位置指针时
            // 左位置指针向右移动，直到找到比枢轴大的元素
            while (i < j)
            {
                if (elems[i] <= privot) // 左位置指针<=枢轴  向右移动    1.比较
                {
                    ++i;
                }
                else //>
                {
                    break;
                }
            }

            elems[j] = elems[i]; // 比枢轴大的元素放在左指针位置  2.移动/交换
        }

        // 循环结束时，左排序表的元素比枢轴小，右排序表的元素比枢轴大
        elems[i] = privot; // 枢轴放在左位置指针 可推导

        // 2.递归
        // 注意：使用left和right
        quickSort(elems, left, privot - 1);  // 左递归
        quickSort(elems, privot + 1, right); // 右递归
    }

    return;
}

// 简单选择排序
// 时间复杂度：O(n²)。n为数据规模
// 时间复杂度：数据规模×比较次数
// 最好：O(n²)。n为数据规模
// 平均：O(n²)。n为数据规模
// 最坏：O(n²)。n为数据规模
// 空间复杂度：O(1)。未使用额外辅助空间
// 稳定性：不稳定（最小元素和需排序元素交换时，可能改变元素的相对位置）
void selectSort(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    int i = 0; // 循环变量
    int j = 0;

    int min = 0;        // 最小元素位置
    ELEM_TYPE temp = 0; // 交换时，记录暂存元素

    // 遍历需排序位置
    // 需排序位置：0 ~ elems.size() - 2
    // 最后一个位置elems.size() - 1不需要排序
    //  elems.size()个位置需elems.size() - 1趟排序

    // 注意：
    // 排序位置而不是元素：一趟排序确定一个位置
    for (i = 0; i < elems.size() - 1; ++i)
    {
        min = i; // 记录最小元素位置
        // 理解：
        //  i记录需排序位置
        //  min记录最小元素位置
        // 从最小元素位置，取最小元素，放到需排序位置

        // 遍历需排序位置后的位置
        // 比较当前最小元素和需排序位置后的位置的元素，取最小元素，放到需排序位置
        for (int j = i + 1; j < elems.size(); ++j)
        {
            if (elems[min] > elems[j]) // 当前最小元素>需排序元素位置后的位置的元素  1.比较/选择
            {
                min = j; // 记录最小元素位置
            }
        }

        // 2.移动/交换
        // 最小元素，放到需排序位置
        // 需排序位置元素，放到最小元素位置
        if (min != i) // 最小元素位置!=需排序元素位置
        {
            temp = elems[i];
            elems[i] = elems[min];
            elems[min] = temp;
        }
    }

    return;
}

// 堆调整    大顶堆法
// 参数：需排序元素的向量，闭区间[low，high]位置结点调整为大顶堆
// 关键理解：实际上，调整以low位置结点为根的树
void heapAdjust(vector<ELEM_TYPE> &elems, int low, int high)
{
    int i = low; // 调整以i位置结点为根的树    调整时，i位置可能会从上到下更新

    ELEM_TYPE temp = elems[low]; // 暂存i位置结点的关键字

    // 关键理解：
    //  j：需比较和交换结点的位置
    // 范围：以i位置结点为根的树

    // int j = 2 * i：i位置结点的左孩子结点是2 * i位置结点（依据完全二叉树的性质）
    // j <= high：位置不越界
    // j *= 2：左孩子结点的位置（依据完全二叉树的性质）

    // 每循环，比较i位置结点、2 * i位置结点和2 * i + 1位置结点的关键字
    // 即比较i位置结点、i位置结点的左孩子结点和i位置结点的右孩子结点的关键字
    for (int j = 2 * i; j <= high; j *= 2)
    {
        // 1. 比较左孩子结点和右孩子结点的关键字

        //  j < high：j不是最后一个结点的位置->i位置结点存在右孩子结点
        //  elems[j] < elems[j + 1]：左孩子结点的关键字<右孩子结点的关键字
        if (j < high && elems[j] < elems[j + 1])
        {
            ++j; // 更新需比较和交换结点的位置
        }
        // 目的：
        //  j：需比较和交换结点的位置
        // 取左孩子结点和右孩子结点中，关键字最大的位置
        //  j = 2 * i或j = 2 * i + 1

        // 2.比较i位置结点、左孩子结点和右孩子结点中，关键字最大的结点
        // i位置结点<左孩子结点和右孩子结点中，关键字最大的结点
        // 需要调整
        if (temp < elems[j])
        {
            elems[i] = elems[j]; // i位置结点的关键字赋值为j位置结点的关键字
            i = j;               // 更新i位置
        }
        else //>=    不需要调整
        {
            break; // 调整结束
        }
    }

    elems[i] = temp; // i位置结点的关键字赋值为暂存的关键字 注意：i可能已更新

    return;
}

// 堆排序    大顶堆法
// 时间复杂度：O(nlogn)。n为数据规模
// 时间复杂度：建堆和堆排序
// 建堆：O(n)。n为数据规模
// 堆排序：排序次数×调整堆/树高
// 堆排序：O(nlogn)。n为数据规模
// 最好：O(nlogn)。n为数据规模
// 平均：O(nlogn)。n为数据规模
// 最坏：O(nlogn)。n为数据规模
// 空间复杂度：O(1)。未使用额外辅助空间
// 稳定性：不稳定（需排序元素交换时，可能改变元素的相对位置）
void heapSort(vector<ELEM_TYPE> &elems) // 参数：需排序元素的向量
{
    ELEM_TYPE temp = 0; // 暂存交换结点的关键字

    // 1.建堆
    // 从完全二叉树的最后一个非叶子结点开始，从右到左，从下到上，调整结点
    // 范围：1~(elems.size() - 1) / 2
    for (int i = (elems.size() - 1) / 2; i >= 1; --i)
    {
        heapAdjust(elems, i, elems.size() - 1); // 注意：闭区间[low，high]位置结点调整为大顶堆   1.比较
    }

    // 2.堆排序
    // 范围：2~elems.size() - 1
    // 对1~elems.size() - 1个结点，需进行elems.size() - 2次排序，最后一个结点已有序
    for (int i = elems.size() - 1; i >= 2; --i)
    {
        // 交换树根结点和最右下位置结点，删除最右下位置结点，输出最右下位置结点（最右下位置结点进入有序序列）    2.移动/交换
        temp = elems[1];
        elems[1] = elems[i];
        elems[i] = temp;

        // 调整（最右下位置结点被交换到树根结点，可能不满足堆定义）  1.比较
        heapAdjust(elems, 1, i - 1);
        // 注意：i - 1：因为最右下位置结点进入有序序列，无需进行调整
    }

    return;
}

// 二路归并
// 参数：需排序元素的向量，归并闭区间[low，mid]和[mid + 1，high]序列
void merge(vector<ELEM_TYPE> &elems, int low, int mid, int high)
{
    vector<ELEM_TYPE> temp(elems.size(), 0); // 暂存需排序元素的向量
    // 因为需要修改elems，elems存储已排序元素

    // 暂存需排序元素
    for (int i = low; i <= high; ++i)
    {
        temp[i] = elems[i];
    }

    // 循环变量
    int i = low;     // 闭区间[low，mid]序列位置
    int j = mid + 1; // 闭区间[mid + 1，high]序列位置
    int k = low;     // elems位置

    // 闭区间[low，mid]序列位置和闭区间[mid + 1，high]序列位置未越界时，循环
    // 比较，取两区间中的最小元素，存储在elems位置
    while (i <= mid && j <= high)
    {
        if (temp[i] <= temp[j]) // 闭区间[low，mid]序列元素 <= 闭区间[mid + 1，high]序列元素 两两比较，稳定性体现
        {
            elems[k] = temp[i];

            ++k; // 更新位置
            ++i;
        }
        else //>
        {
            elems[k] = temp[j];

            ++k; // 更新位置
            ++j;
        }
    }

    // 闭区间[low，mid]序列位置或闭区间[mid + 1，high]序列位置越界
    // 若另一个序列有未排序元素，存储在elems位置
    while (i <= mid)
    {
        elems[k] = temp[i];

        ++k; // 更新位置
        ++i;
    }

    while (j <= high)
    {
        elems[k] = temp[j];

        ++k; // 更新位置
        ++j;
    }

    return;
}

// 二路归并排序  递归法  分治法
// 时间复杂度：O(nlogn)。n为数据规模
// 时间复杂度：归并趟数×一趟归并的操作次数
// 归并趟数：O(nlogn)。n为数据规模
// 一趟归并的操作次数：O(n)。n为数据规模
// 最好：O(nlogn)。n为数据规模
// 平均：O(nlogn)。n为数据规模
// 最坏：O(nlogn)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：暂存需排序元素辅助空间的大小或递归调用栈的大小
// 暂存需排序元素辅助空间的大小：O(n)。n为数据规模
// 递归调用栈的大小：O(logn)。n为数据规模
// 稳定性：稳定

// 二路归并排序  迭代法简介
// 循环中：更新步长/增量，两两归并，归并剩余单个序列
// 时间复杂度：无递归，比递归法更优，数量级不变
// 空间复杂度：无递归调用栈，比递归法更优，数量级不变

// 另：m = (log以k为底的n)上取整。m为归并趟数，k为归并路数，n为数据规模

// 参数：需排序元素的向量，排序闭区间[low，high]序列：左位置指针，右位置指针
void mergeSort(vector<ELEM_TYPE> &elems, int low, int high)
{
    if (low < high) // 左位置指针 < 右位置指针，区间合法
    {
        int mid = low + (high - low) / 2; // 中间位置指针    划分左右区间

        mergeSort(elems, low, mid);      // 左区间归并排序   左
        mergeSort(elems, mid + 1, high); // 右区间归并排序   右
        merge(elems, low, mid, high);    // 归并 中
    }

    return;
}

// 基数排序
// 思想：多关键字比较，无需进行比较和移动
// 类型：最高位优先（MSD）；最低位优先（LSD）
// 最高位优先（MSD）：排序最高位，排序次高位...以此类推
// 最低位优先（LSD）：分配和收集最低位，分配和收集次低位...以此类推。对每个数据分配入队列，对每个队列收集出队列数据
// 注意和理解：最高位优先能够在一定程度上确定排序，最低位优先不能
// 时间复杂度：O(d(n+r))。d为数据位数，n为数据规模，r为数据基数/取值范围。如十进制数字基数为10、小写字母基数为26
// 时间复杂度：排序趟数×分配和收集次数。排序趟数为数据位数，分配次数为数据规模，收集次数为数据基数
// 最好：O(d(n+r))
// 平均：O(d(n+r))
// 最坏：O(d(n+r))
// 空间复杂度：O(r)。r为数据基数/取值范围。如十进制数字基数为10、小写字母基数为26
// 空间复杂度：分配和收集队列的大小
// 稳定性：稳定（按位排序时，稳定性体现）

// 主函数————————————————————
int main()
{
    use_example(); // 使用示例

    return 0;
}