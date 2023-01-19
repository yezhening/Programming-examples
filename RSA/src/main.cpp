#include "RSA.h"

int main()
{
    RSA *rsa = new RSA;

    string plaintext_str("yezhening");                            // 字符串类型的明文
    vector<unsigned int> ciphertext_int(plaintext_str.size(), 0); // 无符号整数类型的密文
    string plaintext_str1(plaintext_str.size(), '\0');            // 字符串类型的明文   解密后的明文

    rsa->Encrypt(plaintext_str, ciphertext_int);  // 加密得密文
    rsa->Decrypt(ciphertext_int, plaintext_str1); // 解密得明文

    delete rsa;

    return 0;
}