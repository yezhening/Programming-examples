// 头文件————————————————————
#include <iostream>
#include <vector>

// 命名空间————————————————————
using namespace std;

// 函数声明————————————————————
void useExample();                                                                  // 使用示例
void getNext(const string &subStr, vector<int> &next);                              // 获取next向量：值统一减一/整体右移一位的前缀表
int indexKMP(const string &mainStr, const string &subStr, const vector<int> &next); // KMP算法 返回主串与子串匹配的第一个位置索引

// 函数定义————————————————————
// 使用示例
void useExample()
{
    const string mainStr = "abcde"; // 主串
    const string subStr = "cd";     // 子串

    const int subStrSize = subStr.size(); // 子串大小

    vector<int> next(subStrSize, -1); // next向量   为子串大小，初始化值-1

    getNext(subStr, next); // 获取next向量

    cout << indexKMP(mainStr, subStr, next) << endl; // 输出：2

    return;
}

// 获取next向量：值统一减一的前缀表
void getNext(const string &subStr, vector<int> &next) // 参数：子串，next向量
{
    int i = 0;  // 子串中求next值位置的上一位置  主串/后缀的起始位置
    int j = -1; // 子串中求next值位置的上上一位置    用于定位：因为需要依据next[j]求next[j+1]    子串/前缀的起始位置

    next[0] = -1; // next向量第一个位置的值必为-1：不存在最长相等前后缀，最长相等前后缀为0，0 - 1 = -1

    while (i < subStr.size() - 1) // 遍历子串每个位置   求next值 注意：因为是上一个位置，所以需-1
    {
        // j == -1：j回退到-1，-1 + 1 = 0，最长相等前后缀的长度为0，不存在最长相等前后缀
        //++i：从主串的下一位置匹配
        //++j：j = -1 + 1 = 0，从子串的第一个位置匹配
        // next[i] = j：得next值0：
        // 因为不存在最长相等前后缀；含义：若匹配失败，则从子串的第一个位置0进行匹配

        // subStr[i] == subStr[j]：匹配成功
        //++i：继续匹配主串的下一位置
        //++j：继续匹配子串的下一位置
        // next[i] = j：得next值：
        // 因为匹配成功；含义：若匹配失败，则从后缀的j位置匹配（因为存在最长相等前后缀，可定位）

        // 注意理解：匹配时的i是求next值的位置的上一位置，next[i] = j的++i是求next值的位置

        // else：不存在最长相等前后缀，问题转换：进一步理解为模式匹配问题，递归求next[j]得定位

        if (j == -1 || subStr[i] == subStr[j])
        {
            ++i;
            ++j;

            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }

    return;
}

// KMP算法  返回主串与子串匹配的第一个位置索引
int indexKMP(const string &mainStr, const string &subStr, const vector<int> &next) // 参数：主串，子串，next向量
{
    int i = 0; // 主串的匹配位置
    int j = 0; // 子串的匹配位置

    const int mainStrSize = mainStr.size(); // 主串大小
    const int subStrSize = subStr.size();   // 子串大小

    // while (i < mainStr.size() && j < subStr.size()) //遍历主串和子串 输出错误
    while (i < mainStrSize && j < subStrSize) // 遍历主串和子串
    {
        // j == -1：子串的匹配位置回溯，匹配主串的下一位置和子串的第一个位置
        // mainStr[i] == subStr[j]：匹配成功，继续匹配主串和子串的下一个位置
        // else：匹配失败，子串的匹配位置依据next向量回溯
        if (j == -1 || mainStr[i] == subStr[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }

    if (j == subStr.size()) // 遍历完子串，表明匹配成功
    {
        return i - subStr.size(); // 返回主串与子串匹配的第一个位置索引
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