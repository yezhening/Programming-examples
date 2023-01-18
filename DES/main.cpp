//预处理指令——————————
//自定义头文件
#include "DES.h"

//函数声明——————————
void compareStrBit(string str1, string str2); //比较两字符串不同的位数

//主函数——————————
int main()
{
    DES *des = new DES(); //数据加密标准对象
    //提示：
    //复杂类型/自定义类型可能占用空间大，堆区比栈区大，需要在堆区手动管理
    //手动管理：使用new创建对象，使用delete释放对象->搭配使用

    const string plainText("yezhenin"); //明文
    const string key("91002705");       //密钥
    string cipherTextASCII("");         //密文的ASCII码
    //提示：
    //密文的ASCII码没有必要转换为字符，因为：
    // 1.转换的字符无意义
    // 2.转换的字符可能为非打印字符
    string plainTextASCII(""); //明文的ASCII码

    des->encrypt(plainText, key, cipherTextASCII); //加密
    //参数：明文（已知），密钥（已知），密文的ASCII码（未知）

    des->decrypt(cipherTextASCII, key, plainTextASCII); //解密
    //参数：密文的ASCII码（已知），密钥（已知），明文的ASCII码（未知）

    //字符转ASCII码转换器网址：https://www.qqxiuzi.cn/bianma/ascii.htm
    // ASCII码转字符转换器网址：https://www.asciim.cn/m/tools/convert_ascii_to_string.html

    //雪崩效应测试
    //提示：
    //由设计接口：测试明文变化需要考虑到字节层面，传递明文参数；测试密文变化需要考虑到位层面，传递密文的ASCII码参数
    //因为加密和解密过程相似，所以变化密文进行测试

    string cipherTextCo = "0000110101111001101000001011100001101001111000010100000001011011"; //密文正确码
    string plainTextCo = "0111100101100101011110100110100001100101011011100110100101101110";  //明文正确码

    //第一组
    string cipherTextEr = cipherTextCo;           //密文错误码为密文正确码
    cipherTextEr[0] = 1;                          //修改1位：0->1
    string plainTextEr("");                       //明文错误码
    des->decrypt(cipherTextEr, key, plainTextEr); //解密
    //参数：密文错误码（已知），密钥（已知），明文错误码（未知）
    compareStrBit(plainTextCo, plainTextEr); //比较两字符串不同的位数

    //第二组
    cipherTextEr = cipherTextCo;                  //密文错误码为密文正确码
    cipherTextEr[0] = 1;                          //修改1位：0->1
    cipherTextEr[63] = 0;                         //修改1位：1->0
    plainTextEr = "";                             //明文错误码
    des->decrypt(cipherTextEr, key, plainTextEr); //解密
    //参数：密文错误码（已知），密钥（已知），明文错误码（未知）
    compareStrBit(plainTextCo, plainTextEr); //较两字符串不同的位数

    //第三组
    cipherTextEr = cipherTextCo;                  //密文错误码为密文正确码
    cipherTextEr[0] = 1;                          //修改1位：0->1
    cipherTextEr[1] = 1;                          //修改1位：0->1
    cipherTextEr[63] = 0;                         //修改1位：1->0
    plainTextEr = "";                             //明文错误码
    des->decrypt(cipherTextEr, key, plainTextEr); //解密
    //参数：密文错误码（已知），密钥（已知），明文错误码（未知）
    compareStrBit(plainTextCo, plainTextEr); //较两字符串不同的位数

    delete des;

    return 0;
}

//比较两字符串不同的位数
void compareStrBit(string str1, string str2)
{
    int diffBitCount = 0; //不同位计数
    for (int i = 0; i < str1.size(); ++i)
    {
        if (str1[i] != str2[i])
        {
            ++diffBitCount;
        }
    }

    cout << "不同位数：\t" << diffBitCount << endl;
    cout << endl;

    return;
}