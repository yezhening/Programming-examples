// 头文件————————————————————
#include <iostream>

// 命名空间————————————————————
using namespace std;

// 函数声明————————————————————
void useExample();                                      // 使用示例
int index(const string &mainStr, const string &subStr); // 暴力/简单/朴素算法  返回主串与子串匹配的第一个位置索引

// 函数定义————————————————————
// 使用示例
void useExample()
{
    const string mainStr = "abcde"; // 主串
    const string subStr = "cd";     // 子串

    cout << index(mainStr, subStr) << endl; // 输出：2

    return;
}

// 暴力/简单/朴素算法  返回主串与子串匹配的第一个位置索引
int index(const string &mainStr, const string &subStr) // 参数：主串，子串
{
    int i = 0; // 主串的匹配位置
    int j = 0; // 子串的匹配位置
    // int k = i; //记录每轮匹配时主串和子串匹配的起始位置  用于匹配失败时主串匹配位置的定位回溯

    while (i < mainStr.size() && j < subStr.size()) // 遍历主串和子串进行匹配
    {
        if (mainStr[i] == subStr[j]) // 匹配成功
        {
            ++i; // 继续匹配主串的下一个位置
            ++j; // 继续匹配子串的下一个位置
        }
        else // 匹配失败
        {
            i = i - j + 1; // 主串匹配位置回溯 或：i = ++k;
            j = 0;         // 子串匹配位置回溯为0
        }
    }

    if (j == subStr.size()) // 遍历完子串，表明匹配成功
    {
        return i - subStr.size(); // 返回主串与子串匹配的第一个位置索引  或：return k;
    }
    else // 匹配失败
    {
        return -1; // 返回-1
    }
}

// 主函数————————————————————
int main()
{
    useExample(); // 使用示例

    return 0;
}