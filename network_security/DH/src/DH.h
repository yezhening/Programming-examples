#ifndef DH_DH_H_
#define DH_DH_H_

#include <iostream> //cout、endl

using std::cout;
using std::endl;

// Diffie-Hellman类
class DH
{
public:
    DH();                         // 构造
    unsigned int GetPrivateKey(); // 获取私钥
    unsigned int GetPublicKey(const unsigned int &x); // 获取公钥
    unsigned int GetKey(const unsigned int &y, const unsigned int &x); // 获取密钥

private:
    // 提示：算法未明确说是正数，但大多使用正数
    unsigned int GetPrimeNum();                                                                    // 获取素数
    bool PrimalityTest(const unsigned int &n, const unsigned int &a);                              // Miller-Rabin素性测试
    unsigned int QuickPowMod(const unsigned int &a, const unsigned int &q, const unsigned int &n); // 蒙哥马利快速幂模运算
    unsigned int QuickMulMod(const unsigned int &a, const unsigned int &b, const unsigned int &c); // 快速乘
    unsigned int GetPrimitiveRoot();                                                               // 获取本原根

    unsigned int p_arg_; // 参数p
    unsigned int a_arg_; // 参数a
};

#endif // DH_DH_H_