#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

class CCombination
{
public:
    CCombination(const int &n, const int &m) : n(n), m(m), curComb(0), combCount(0) {}

    bool next()
    {
        // 第一次进入初始化当前组合，如m=3，this->curComb为012，从012开始遍历
        if (this->curComb.empty() == true)
        {
            for (int i = 0; i < this->m; ++i)
            {
                this->curComb.push_back(i);
            }

            ++this->combCount;
            return true;
        }

        // 1. 从右向左，找到第一个不存有自己最终内容的位置
        // 如n=5，m=3，curPos为索引为3-1=2的位置，从该位置的数开始递增，即先从右边的数开始递增，递增完再到左边的数
        // curPos >= 0：防止越界
        // this->curComb.at(curPos) == this->n - this->m + curPos：因为是组合数，无序，不存有自己最终内容指的是在索引2，只能取到5-3+2=4，索引1取到5-3+1=3，索引0取到5-3+0=2
        // 继续理解：比如012，前面占了01两个位置，最后的位置能取到最大值4，第二个位置因为右边的位置占位，为了保证不重复，最大值取到3，以此类推
        // 即为了保证不重复，索引0位置取值范围0~2，1位置0~3，2位置0~4，位置达到这个数说明到了最终位置，位置应该减一，用其左边的数递增
        int curPos = this->m - 1;
        while ((curPos >= 0) && (this->curComb.at(curPos) == this->n - this->m + curPos))
        {
            --curPos;
        }

        if (curPos < 0)
        {
            return false; // 已经遍历所有组合
        }

        // 2.把这个位置上的数值加1
        ++this->curComb.at(curPos);

        // 3. 后面的数值递增
        // 指的是当前位置+1后，其右边的数“归位”，只能从比它大1的数开始，否则会重复，如 014 -> 023， 034 -> 123
        for (int right = curPos + 1; right < this->m; ++right)
        {
            this->curComb.at(right) = this->curComb.at(right - 1) + 1;
        }

        ++this->combCount;
        return true;
    }

    inline void printCurComb()
    {
        for (const int c : this->curComb)
        {
            cout << c << " ";
        }
        cout << endl;
    }

    inline void printCombCount()
    {
        cout << this->combCount << endl;
    }

private:
    const int n; // 从n个取m个
    const int m;

    vector<int> curComb; // 当前组合，存储组合的索引
    int combCount;       // 组合数的数量
};

int main()
{
    const int n = 5;
    const int m = 3;
    CCombination comb(n, m);

    while (comb.next())
    {
        comb.printCurComb();
    }
    comb.printCombCount();

    return 0;
}