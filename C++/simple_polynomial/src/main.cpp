#include "polynomial.h"

using std::cout;
using std::endl;

int main()
{
    // int 型向量表示多项式，x作为形式参数无具体意义只有方便理解的展示意义，索引表示次数，值表示系数
    // 如 {1, 2}，索引0值1表示1x⁰，索引1值2表示2x¹，所以多项式是：2x¹ + 1x⁰ = 2x + 1
    const vector<int> dividend_vec{1, 2, 3, 4}; // 被除数，4x³ + 3x² + 2x + 1
    const vector<int> divisor_vec{3,2,1};        // 除数，x² + 2x + 3

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