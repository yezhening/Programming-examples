#include <sstream> // istringstream

#include "polynomial.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::istringstream;
using std::string;

int main()
{
    // 终端输入被除数和除数
    // int 型向量表示多项式，x作为形式参数无具体意义只有方便理解的展示意义，索引表示次数，值表示系数
    // 如 {1, 2}，索引0值1表示1x⁰，索引1值2表示2x¹，所以多项式是：2x¹ + 1x⁰ = 2x + 1
    // 1. 被除数
    vector<int> dividend_vec(0);

    cout << "被除数系数，从高到低位输入，空格分隔，回车结束: " << endl;
    string input("");
    getline(cin, input); // 从终端获取一行输入

    istringstream iss(input); // 字符串 -> 输入流对象
    int num(0);
    while (iss >> num) // 输入流对象 -> 数字
    {
        dividend_vec.insert(dividend_vec.begin(), num); // 从后往前插入
    }

    // 2. 除数
    vector<int> divisor_vec(0);

    cout << "除数系数，从高到低位输入，空格分隔，回车结束: " << endl;
    input = "";
    getline(cin, input);

    iss.clear(); // 清楚流状态，否则获取不到数字
    iss.str(input);
    num = 0;
    while (iss >> num)
    {
        divisor_vec.insert(divisor_vec.begin(), num);
    }

    // 多项式类表示多项式，进一步封装
    const Polynomial dividend(dividend_vec);
    const Polynomial divisor(divisor_vec);
    cout << "被除数: " << dividend << endl;
    cout << "除数: " << divisor << endl;

    // 多项式除法求商
    Polynomial quotient = dividend / divisor;
    cout << "商: " << quotient << endl;

    // 多项式除法求余数
    Polynomial remainder = dividend % divisor;
    cout << "余数: " << remainder << endl;

    return 0;
}