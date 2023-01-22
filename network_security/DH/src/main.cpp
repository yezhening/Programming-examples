#include "DH.h"

int main(int argc, char **argv)
{
    DH *dh = new DH(); // DH对象

    // 用户A
    unsigned int xa = dh->GetPrivateKey(); // 1.获取私钥
    cout << "用户A的密钥生成：\t" << endl;
    cout << "私钥xa：\t" << xa << endl;

    unsigned int ya = dh->GetPublicKey(xa); // 2.获取公钥
    cout << "公钥ya：\t" << ya << endl;
    cout << endl;

    // 用户B
    unsigned int xb = dh->GetPrivateKey(); // 1.获取私钥
    cout << "用户B的密钥生成：\t" << endl;
    cout << "私钥xb：\t" << xb << endl;

    unsigned int yb = dh->GetPublicKey(xb); // 2.获取公钥
    cout << "公钥yb：\t" << yb << endl;
    cout << endl;

    // 用户A
    unsigned int ka = dh->GetKey(yb, xa); // 3.密钥生成
    cout << "用户A计算产生密钥：\t" << endl;
    cout << "密钥ka：\t" << ka << endl;
    cout << endl;

    // 用户B
    unsigned int kb = dh->GetKey(ya, xb); // 3.密钥生成
    cout << "用户B计算产生密钥：\t" << endl;
    cout << "密钥kb：\t" << kb << endl;

    delete dh;

    return 0;
}
