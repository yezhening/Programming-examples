#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>

using std::ostream;
using std::vector;

// 多项式类
class Polynomial
{
public:
    explicit Polynomial(const vector<int> &p) : poly_vec(p) {} // 私有成员只能在类的成员函数内部被初始化

    // 重载运算符 “<<” 输出多项式
    // friend：类外会用该运算符访问类的成员，不写报错：too many parameters for this operator function
    // 返回输出流对象引用，可以链式操作
    friend ostream &operator<<(ostream &output, const Polynomial &obj);

    // 重载运算符 “/” 进行多项式除法
    // 返回值：商
    // 参数：除数
    Polynomial operator/(const Polynomial &divisor) const; // const表示不会改变调用该方法的被除数

    // 重载运算符 “%” 进行多项式除法求余
    // 返回值：余数
    // 参数：除数
    // 照搬除法逻辑，只改动最后return的返回值，最后的余数就是最后更新的被除数
    Polynomial operator%(const Polynomial &divisor) const; // const表示不会改变调用该方法的被除数

private:
    const vector<int> poly_vec; // 多项式的向量表示
};

#endif // POLYNOMIAL_H