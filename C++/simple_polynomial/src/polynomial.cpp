#include <windows.h> // GetConsoleOutputCP()

#include "polynomial.h"

using std::abs;
using std::cout;
using std::endl;
using std::string;

// 重载运算符 “<<” 输出多项式
// 不需要friend、类作用域声名，因为是类外的运算符
ostream &operator<<(ostream &output, const Polynomial &obj)
{
    UINT terminal_code_page = GetConsoleOutputCP(); // 获取当前终端的输出代码页
    if (terminal_code_page != 65001)
    {
        system("chcp 65001"); // 终端切换使用utf8字符集显示，以可以显示utf8的上标
        // 注意：会切换终端页，需要重新运行程序
    }
    else // 65001
    {
    }

    for (int i = obj.poly_vec.size() - 1; i >= 0; --i) // 从高位到低位    i既表示索引也表示次数
    {
        // 1. 系数的符号
        // 正数显示+，负数不显示-，系数负数已有-
        if (obj.poly_vec.at(i) >= 0)
        {
            cout << "+";
        }
        else // obj.poly.at(i) < 0
        {
            // cout << " - ";
        }

        // 2. 系数
        cout << obj.poly_vec.at(i);

        // 3. 形式参数
        cout << "x";

        // 4. 次数
        // 上标号的utf8编码
        // 如：0上标号⁰的utf8编码在索引0为\u2070，1上标号¹的utf8编码在索引1为\u00B9，以此类推
        vector<string> superscript_utf8{"\u2070", "\u00B9", "\u00B2", "\u00B3", "\u2074", "\u2075", "\u2076", "\u2077", "\u2078", "\u2079"};

        cout << superscript_utf8.at(i);
    }

    return output;
}

// 重载运算符 “/” 进行多项式除法
// 返回值：商
// 参数：除数
Polynomial Polynomial::operator/(const Polynomial &divisor) const // const表示不会改变调用该方法的被除数
{
    // 1. 准备被除数、除数和商
    // 解封装，获取被除数和除数向量
    // 1.1 方便操作
    // 1.2 不再是const，可以修改再封装出去
    vector<int> dividend_vec(this->poly_vec);  // 被除数
    vector<int> divisor_vec(divisor.poly_vec); // 除数

    // 商初始的次数是被除数最高项次数 - 除数最高项次数 + 1
    // 如：
    // 4x³ + 3x² + 2x + 1，的个数是4，最高项次数次数是 4 - 1 = 3
    // x² + 2x + 1的个数是3，最高项次数次数是 3 - 1 = 2
    // 最高项相除，4x³ / x² = 4x，商的最高项次数是 3 - 2 = 1
    // 因为索引从0开始，所以需要+1，商系数的个数是1 + 1 = 2，初始化为0
    vector<int> quotient_vec((dividend_vec.size() - 1) - (divisor_vec.size() - 1) + 1, 0); // 商

    // 2. 除法运算
    // 2.1 如果被除数最高项次数 < 除数最高项次数，即 dividend_vec.size() - 1 < divisor_vec.size() - 1，商返回0
    // 如：4x³ + 3x² + 2x + 1 / x⁵ + 2x + 3，被除数最高项 4x³ 次数4 < 除数最高项 x⁵ 次数5，无法除，返回0（只有1个元素，索引0值0）
    if ((dividend_vec.size() - 1) < (divisor_vec.size() - 1))
    {
        quotient_vec.resize(1, 0);
    }

    // 2.2 如果 >=，进行除法
    while ((dividend_vec.size() - 1) >= (divisor_vec.size() - 1))
    {
        // 2.2.1 求商的系数，取被除数和除数的最高次项（在向量的尾端）的系数进行除法，向下取整
        // 如：4x³ / x² = 4x，系数是4
        // int coefficient = dividend_vec.back() / divisor_vec.back();
        // 如果被除数的系数小于除数的系数，无法再除可能会死循环

        // 取被除数和除数计算项的的绝对值
        int dividend_abs = abs(dividend_vec.back());
        int divisor_abs = abs(divisor_vec.back());

        // 如果被除数的系数小于除数的系数，无法再除，退出循环
        if (dividend_abs < divisor_abs)
        {
            break;
        }

        // 求商的系数的绝对值
        int coefficient_abs = dividend_abs / divisor_abs;

        // 商的符号由被除数和除数的符号决定
        int dividend_sign = (dividend_vec.back() < 0) ? -1 : 1;
        int divisor_sign = (divisor_vec.back() < 0) ? -1 : 1;
        int coefficient = (dividend_sign * divisor_sign) * coefficient_abs;

        // 2.2.2 求商的次数
        // 如：4x³ / x² = 4x，被除数索引次数3，除数索引次数2，3 - 2 = 1，商次数是1
        int degree = (dividend_vec.size() - 1) - (divisor_vec.size() - 1);

        // 2.2.3 将商的系数插入到商的次数位置
        quotient_vec[degree] = coefficient;

        // 2.2.4 被除数减小，需要减去当前的除数乘以商
        // 循环对除数的每一项，从高位到低位
        for (int i = divisor_vec.size() - 1; i >= 0; --i)
        {
            // 2.2.4.1 求应该减去数的系数
            // 如：除数 x² * 商 4x = 4x³，应减去的系数是4
            int coefficient1 = divisor_vec[i] * coefficient;

            // 2.2.4.2 求应该减去数的次数
            // 如：除数 x² * 商 4x = 4x³，应减去的次数是3
            // 因为多项式相乘的次数会相加，所以用除数的次数 + 商的次数 = 被除数应该减去数的次数
            int degree1 = i + degree;

            // 2.2.4.3 在被除数相应的次数位置，减去相应的系数，即实现更新操作
            dividend_vec[degree1] -= coefficient1;
        }

        // 如果被除数的系数已被更新为空，则去除
        // 如：在更新时，被除数最高项为 4x³，除数 x² * 商 4x = 4x³，4x³ - 4x³ = 0，在被除数索引次数3的系数为0，已不需要则去除
        while ((dividend_vec.size() > 0) && (dividend_vec.back() == 0))
        {
            dividend_vec.pop_back();
        }

        // 输出迭代信息
        // cout << "余项: " << Polynomial(dividend_vec) << endl;
        // cout << "当前商: " << Polynomial(quotient_vec) << endl;
    }

    return Polynomial(quotient_vec); // 封装商并返回
}

// 重载运算符 “%” 进行多项式除法求余
// 返回值：余数
// 参数：除数
// 照搬除法逻辑，只改动最后return的返回值，最后的余数就是最后更新的被除数
Polynomial Polynomial::operator%(const Polynomial &divisor) const // const表示不会改变调用该方法的被除数
{
    // 1. 准备被除数、除数和商
    // 解封装，获取被除数和除数向量
    // 1.1 方便操作
    // 1.2 不再是const，可以修改再封装出去
    vector<int> dividend_vec(this->poly_vec);  // 被除数
    vector<int> divisor_vec(divisor.poly_vec); // 除数

    // 商初始的次数是被除数最高项次数 - 除数最高项次数 + 1
    // 如：
    // 4x³ + 3x² + 2x + 1，的个数是4，最高项次数次数是 4 - 1 = 3
    // x² + 2x + 1的个数是3，最高项次数次数是 3 - 1 = 2
    // 最高项相除，4x³ / x² = 4x，商的最高项次数是 3 - 2 = 1
    // 因为索引从0开始，所以需要+1，商系数的个数是1 + 1 = 2，初始化为0
    vector<int> quotient_vec((dividend_vec.size() - 1) - (divisor_vec.size() - 1) + 1, 0); // 商

    // 2. 除法运算
    // 2.1 如果被除数最高项次数 < 除数最高项次数，即 dividend_vec.size() - 1 < divisor_vec.size() - 1，商返回0
    // 如：4x³ + 3x² + 2x + 1 / x⁵ + 2x + 3，被除数最高项 4x³ 次数4 < 除数最高项 x⁵ 次数5，无法除，返回0（只有1个元素，索引0值0）
    if ((dividend_vec.size() - 1) < (divisor_vec.size() - 1))
    {
        quotient_vec.resize(1, 0);
    }

    // 2.2 如果 >=，进行除法
    while ((dividend_vec.size() - 1) >= (divisor_vec.size() - 1))
    {
        // 2.2.1 求商的系数，取被除数和除数的最高次项（在向量的尾端）的系数进行除法，向下取整
        // 如：4x³ / x² = 4x，系数是4
        // int coefficient = dividend_vec.back() / divisor_vec.back();
        // 如果被除数的系数小于除数的系数，无法再除可能会死循环

        // 取被除数和除数计算项的的绝对值
        int dividend_abs = abs(dividend_vec.back());
        int divisor_abs = abs(divisor_vec.back());

        // 如果被除数的系数小于除数的系数，无法再除，退出循环
        if (dividend_abs < divisor_abs)
        {
            break;
        }

        // 求商的系数的绝对值
        int coefficient_abs = dividend_abs / divisor_abs;

        // 商的符号由被除数和除数的符号决定
        int dividend_sign = (dividend_vec.back() < 0) ? -1 : 1;
        int divisor_sign = (divisor_vec.back() < 0) ? -1 : 1;
        int coefficient = (dividend_sign * divisor_sign) * coefficient_abs;

        // 2.2.2 求商的次数
        // 如：4x³ / x² = 4x，被除数索引次数3，除数索引次数2，3 - 2 = 1，商次数是1
        int degree = (dividend_vec.size() - 1) - (divisor_vec.size() - 1);

        // 2.2.3 将商的系数插入到商的次数位置
        quotient_vec[degree] = coefficient;

        // 2.2.4 被除数减小，需要减去当前的除数乘以商
        // 循环对除数的每一项，从高位到低位
        for (int i = divisor_vec.size() - 1; i >= 0; --i)
        {
            // 2.2.4.1 求应该减去数的系数
            // 如：除数 x² * 商 4x = 4x³，应减去的系数是4
            int coefficient1 = divisor_vec[i] * coefficient;

            // 2.2.4.2 求应该减去数的次数
            // 如：除数 x² * 商 4x = 4x³，应减去的次数是3
            // 因为多项式相乘的次数会相加，所以用除数的次数 + 商的次数 = 被除数应该减去数的次数
            int degree1 = i + degree;

            // 2.2.4.3 在被除数相应的次数位置，减去相应的系数，即实现更新操作
            dividend_vec[degree1] -= coefficient1;
        }

        // 如果被除数的系数已被更新为空，则去除
        // 如：在更新时，被除数最高项为 4x³，除数 x² * 商 4x = 4x³，4x³ - 4x³ = 0，在被除数索引次数3的系数为0，已不需要则去除
        while ((dividend_vec.size() > 0) && (dividend_vec.back() == 0))
        {
            dividend_vec.pop_back();
        }

        // 输出迭代信息
        // cout << "余项: " << Polynomial(dividend_vec) << endl;
        // cout << "当前商: " << Polynomial(quotient_vec) << endl;
    }

    return Polynomial(dividend_vec); // 封装商并返回
}