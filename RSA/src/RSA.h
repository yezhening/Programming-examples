#ifndef RSA_RSA_H_
#define RSA_RSA_H_

#include <iostream> //cout、endl、string
#include <vector>   // vector

using std::string;
using std::vector;

class RSA
{
public:
    RSA();                                                                            // 构造
    void Encrypt(const string &plaintext_str, vector<unsigned int> &ciphertext_int);  // 加密
    void Decrypt(const vector<unsigned int> &ciphertext_int, string &plaintext_str1); // 解密

private:
    void KeyGen(); // 密钥生成

    unsigned int GetPrimeNum();                                                                    // 获取素数
    bool PrimalityTest(const unsigned int &n, const unsigned int &a);                              // Miller-Rabin素性测试
    unsigned int QuickPowMod(const unsigned int &a, const unsigned int &q, const unsigned int &n); // 蒙哥马利快速幂模运算
    unsigned int QuickMulMod(const unsigned int &a, const unsigned int &b, const unsigned int &c); // 快速乘模

    unsigned int ExGcd(const unsigned int &a, const unsigned int &b, unsigned int &x, unsigned int &y); // 扩展欧几里得算法
    unsigned int GetMulInverse(const unsigned int &a, const unsigned int &b);                           // 求乘法逆元

    unsigned int p_arg_; // p参数
    // 提示：参数>=0，使用unsigned int更符合语义
    unsigned int q_arg_;            // q参数
    unsigned int n_arg_;            // n参数
    unsigned int n_Euler_func_arg_; // n的欧拉函数参数
    unsigned int e_arg_;            // e参数
    unsigned int d_arg_;            // d参数
};

#endif // RSA_RSA_H_