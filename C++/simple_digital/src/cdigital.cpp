#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

class CDigital
{

public:
    CDigital(const vector<int> &bases) : bases(bases), curDig(0), digCount(0) {}

    bool next()
    {
        // 第一次进入初始化当前组合，如bases.size()=3，this->curDig为000，从000开始遍历
        if (this->curDig.empty() == true)
        {
            this->curDig.resize(bases.size(), 0); // 初始化所有位置为0

            ++this->digCount;
            return true;
        }

        // 1. 从后向前找到第一个不是该位置最大值的位置，
        int curPos = bases.size() - 1;
        while ((curPos >= 0) && (this->curDig.at(curPos) == this->bases.at(curPos) - 1)) // 是最大值就移动位置
        {
            --curPos;
        }

        if (curPos < 0)
        {
            return false; // 都是最大位置，组合结束
        }

        // 2. 然后把该位置数据加1
        ++this->curDig.at(curPos);

        // 3. 最后把后面的各个位置写对应的最小值
        // 一般进制的最小值都为0
        for (int right = curPos + 1; right < this->bases.size(); ++right)
        {
            this->curDig.at(right) = 0;
        }

        ++this->digCount;
        return true;
    }

    inline void printCurDig()
    {
        for (const int d : this->curDig)
        {
            cout << d << " ";
        }
        cout << endl;
    }

    inline void printDigCount()
    {
        cout << this->digCount << endl;
    }

private:
    const vector<int> bases; // 各个位置的进制

    vector<int> curDig; // 当前数字“组合”
    int digCount;       // 数字组合数的数量
};

int main()
{
    const vector<int> bases{4, 5, 3}; // 不同位置的进制数/取值范围 4表示0~3

    CDigital dig(bases);

    while (dig.next())
    {
        dig.printCurDig();
    }
    dig.printDigCount();

    return 0;
}