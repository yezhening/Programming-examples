//预处理指令——————————
//标准库头文件
#include <bitset>    //<bitset>
#include <algorithm> //reverse()
#include <string>    //stoi()

//自定义头文件
#include "DES.h"

//命名空间
//提示：
//使用using声明而不是using指示，以体现命名空间的作用
//本项目并未体现命名空间的作用，因为只使用一个命名空间std
using std::bitset;

//加密
void DES::encrypt(const string &plainText, const string &key, string &cipherTextASCII) //参数：明文，密钥，密文的ASCII码
{
    cout << "加密过程：————————————————————" << endl;

    //对明文和密钥：
    cout << "明文：\t" << plainText << endl;
    cout << "密钥：\t" << key << endl;

    // 0.初始化为二进制  8字节->64位
    string plainTextASCII("");                        //明文的ASCII码   64位
    this->byteStrToBitStr(plainText, plainTextASCII); // 8字节字符串转64位字符串 依据ASCII码
    this->plainTextASCII = plainTextASCII;            //记录明文的ASCII码
    cout << "明文的ASCII码：\t" << this->plainTextASCII << endl;
    string keyASCII("");                  //密钥的ASCII码   64位
    this->byteStrToBitStr(key, keyASCII); // 8字节字符串转64位字符串 依据ASCII码
    this->keyASCII = keyASCII;            //记录密钥的ASCII码
    cout << "密钥的ASCII码：\t" << this->keyASCII << endl;
    cout << endl;

    //对密钥：
    // 1.密钥的选择置换 64->56位
    string keySeRep(56, '-'); //密钥的选择置换   56位
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    for (int i = 0; i < this->keySeRepTable.size(); ++i)
    {
        //置换规则：依据置换表，输入的第57位是输出的第1位->输入的第56位是输出的第0位
        //注意：下标从0开始
        keySeRep[i] = this->keyASCII[this->keySeRepTable[i] - 1];
    }
    cout << "密钥的选择置换：\t" << keySeRep << endl;

    // 2.轮密钥生成
    //提示：预先生成
    string preKey(keySeRep);  //上一轮密钥 56位
    string nextKey("");       //下一轮密钥 56位
    string wheelKey(48, '-'); //轮密钥 48位
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    //提示：
    //在循环外而不是循环中声明并初始化/定义对象，避免重复进行对象的构造和析构，减少开销
    //但可读性差

    // 16轮轮函数
    //注意：轮数从1开始
    for (int wheelCount = 1; wheelCount <= 16; ++wheelCount) //轮数计数
    {
        //轮密钥生成
        //参数：上一轮密钥（56位），轮数（从1开始），下一轮密钥（56位），轮密钥（48位）
        this->wheelKeyGener(preKey, wheelCount, nextKey, wheelKey);

        this->wheelKeys[wheelCount - 1] = wheelKey; //记录轮密钥
        //注意：轮数从1开始，轮密钥下标从0开始
        //注意：记录轮密钥（48位）而不是下一轮密钥（56位）

        //注意：
        //循环外定义的变量可能需要更新
        //循环内定义的变量为局部变量，不需要更新，方便
        preKey = nextKey; //更新上一轮密钥 56位
        nextKey = "";     //更新下一轮密钥 56位
        //轮密钥每轮都通过下标填充，不需要更新
    }

    //对明文：
    // 1.初始置换IP 64->64位
    string plainTextIp(64, '-'); //明文的初始置换IP   64位
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    for (int i = 0; i < this->ipTable.size(); ++i)
    {
        //置换规则：依据置换表，输入的第58位是输出的第1位->输入的第57位是输出的第0位
        //注意：下标从0开始
        plainTextIp[i] = this->plainTextASCII[this->ipTable[i] - 1];
    }
    cout << "明文的初始置换IP：\t" << plainTextIp << endl;
    cout << endl;

    // 2.轮函数F
    string plainTextWheelF(""); //明文的轮函数  64位
    wheelFunc(plainTextIp, keySeRep, plainTextWheelF);
    //参数：明文的初始置换IP，密钥的选择置换，明文的轮函数
    cout << "明文的轮函数F：\t" << plainTextWheelF << endl;

    // 3.左右置换/轮函数F的第16轮不进行左右置换 64->64位
    string left(plainTextWheelF.substr(0, 32));   //左 范围：0~31
    string right(plainTextWheelF.substr(32, 32)); //右 范围：32~63
    string plainTextLeRiRep = right + left;       //明文的左右置换
    cout << "明文的左右置换：\t" << plainTextLeRiRep << endl;

    // 4.逆初始置换IP-1 64->64位
    string plainTextIIp(64, '-'); //明文的逆初始置换IP-1
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    for (int i = 0; i < this->iIpTable.size(); ++i)
    {
        //置换规则：依据置换表，输入的第40位是输出的第1位->输入的第39位是输出的第0位
        //注意：下标从0开始
        plainTextIIp[i] = plainTextLeRiRep[this->iIpTable[i] - 1];
    }
    cout << "明文的逆初始置换IP-1：\t" << plainTextIIp << endl;
    cout << endl;

    this->cipherTextASCII = plainTextIIp; //记录密文的ASCII码   密文的ASCII码为明文的逆初始置换IP-1
    cout << "密文的ASCII码：\t" << this->cipherTextASCII << endl;
    cout << endl;

    cipherTextASCII = plainTextIIp; //记录结果   密文的ASCII码为明文的逆初始置换IP-1

    return;
}

// 8字节字符串转64位字符串 依据ASCII码
void DES::byteStrToBitStr(const string &str, string &bitStr) //参数：8字节字符串，64位字符串
{
    for (const char &ch : str)
    {
        bitStr += bitset<8>(ch).to_string(); // 1字节字符转8位字符串    字符->bitset对象->字符串
    }

    return;
}

//轮密钥生成
//参数：上一轮密钥（56位），轮数（从1开始），下一轮密钥（56位），轮密钥（48位）
void DES::wheelKeyGener(const string &preKey, const int &wheelCount, string &nextKey, string &wheelKey)
{
    // 2.1等分上一轮密钥为上一轮左右    56->28+28位
    //注意：substr()的参数：开始下标，子串大小
    string preLeft(preKey.substr(0, 28));   //上一轮左  范围：0~27
    string preRight(preKey.substr(28, 28)); //上一轮右  范围：28~55

    // 2.2上一轮左右各循环左移/旋转
    //上一轮左的左移
    //局部翻转
    //注意：轮数从1开始，下标从0开始
    //注意：reverse()是左闭右开区间[)
    reverse(preLeft.begin(), preLeft.begin() + this->keyLeftMoveTable[wheelCount - 1]); //翻转[0,1)或[0,2)
    reverse(preLeft.begin() + this->keyLeftMoveTable[wheelCount - 1], preLeft.end());   //翻转[1,n)或[2,n)
    //整体翻转
    reverse(preLeft.begin(), preLeft.end()); //翻转[0,n)

    //上一轮右的左移位
    //局部翻转
    //注意：轮数从1开始，下标从0开始
    //注意：reverse()是左闭右开区间[)
    reverse(preRight.begin(), preRight.begin() + this->keyLeftMoveTable[wheelCount - 1]); //翻转[0,1)或[0,2)
    reverse(preRight.begin() + this->keyLeftMoveTable[wheelCount - 1], preRight.end());   //翻转[1,n)或[2,n)
    //整体翻转
    reverse(preRight.begin(), preRight.end()); //翻转[0,n)

    // 2.3拼接上一轮左右得下一轮密钥    28+28->56位
    nextKey = preLeft + preRight;

    // 2.4下一轮密钥的压缩置换得轮密钥    56->48位
    for (int i = 0; i < this->keyComRepTable.size(); ++i)
    {
        //置换规则：依据置换表，输入的第14位是输出的第1位->输入的第13位是输出的第0位
        //注意：下标从0开始
        wheelKey[i] = nextKey[this->keyComRepTable[i] - 1];
    }

    return;
}

//轮函数F
//注意：忘记加类作用域...
//参数：文本的初始置换IP，密钥的选择置换，文本的轮函数F
void DES::wheelFunc(const string &textIp, const string &keySeRep, string &textWheelF)
{
    string preText(textIp); //上一轮文本    64位
    //提示：
    //在循环外而不是循环中声明并初始化/定义对象，避免重复进行对象的构造和析构，减少开销
    //但可读性差

    // 16轮轮函数
    //注意：轮数从1开始
    for (int wheelCount = 1; wheelCount <= 16; ++wheelCount) //轮数计数
    {
        // 2.1等分上一轮文本为上一轮左右    64->32+32位
        //注意：substr()的参数：开始下标，子串大小
        string preLeft(preText.substr(0, 32));   //上一轮左   范围：0~31
        string preRight(preText.substr(32, 32)); //上一轮右 范围：32~63

        // 2.2下一轮左为上一轮右    32->32位
        string nextLeft(preRight);

        // 2.3.1下一轮右：上一轮右扩展置换E 32->48位
        string preRightERep(48, '-'); //上一轮右的扩展置换E
        //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
        //注意：初始化为不是0或1的字符，以验证上一轮右的扩展置换E是否成功
        for (int i = 0; i < this->eRepTable.size(); ++i)
        {
            //置换规则：依据置换表，输入的第32位是输出的第1位->输入的第31位是输出的第0位
            //注意：下标从0开始
            preRightERep[i] = preRight[this->eRepTable[i] - 1];
        }

        // 2.3.2下一轮右：上一轮右的扩展置换E（48位）与轮密钥（48位）异或 48w->48位
        string preRightXor(""); //上一轮右的异或
        for (int i = 0; i < preRightERep.size(); ++i)
        {
            //注意：轮数计数从1开始，轮密钥的下标从0开始
            if (preRightERep[i] == this->wheelKeys[wheelCount - 1][i]) //相同为0
            {
                preRightXor += '0';
            }
            else //不同为'1'
            {
                preRightXor += '1';
            }
        }

        // 2.3.4下一轮右：上一轮右的异或经S盒选择代替   48->32位
        string preRightSBoxSeRep(""); //上一轮右的S盒选择代替
        int sBoxCount = 0;            // S盒计数
        //注意：S盒计数从0开始
        for (int i = 0; i < preRightXor.size();) // i循环范围：0~47
        {
            string sBoxGroup(preRightXor.substr(i, 6)); // S盒组   一组从i开始取6位数
            //注意：substr()参数：开始下标，子串长度

            string rowStr{sBoxGroup[0], sBoxGroup[5]}; //行字符串：首尾2位
            //注意：初始化方式
            int rowNumber = stoi(rowStr, 0, 2); //行号
            //注意：stoi()参数：字符串，开始下标，字符串的基数

            string colStr(sBoxGroup.substr(1, 4)); //列字符串：中间4位
            //注意：初始化方式
            int colNumber = stoi(colStr, 0, 2); //列号
            //注意：stoi()参数：字符串，开始下标，字符串的基数

            int pos = rowNumber * 16 + colNumber; //位置：第rowNumber行第colNumber列
            //注意：行数从0开始，列数从0开始
            char sBoxNumber = this->sBoxSeRepTable[sBoxCount][pos]; // S盒数
            //注意：
            // S盒计数从0开始   第0盒->S1
            // S盒数是char数据类型

            preRightSBoxSeRep += bitset<4>(sBoxNumber).to_string(); // 1字节字符转4位字符串 字符->bitset对象->字符串

            sBoxCount += 1; // S盒计数+1
            i += 6;         //循环i+6
            // 注意：i变化范围：0~5，6~11，12~17，18...
        }

        // 2.3.5下一轮右：上一轮右置换P 32->32位
        string preRightPRep(32, '-'); //上一轮右的置换P
        //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
        //注意：初始化为不是0或1的字符，以验证是否成功

        for (int i = 0; i < this->pRepTable.size(); ++i)
        {
            //置换规则：依据置换表，输入的第16位是输出的第1位->输入的第15位是输出的第0位
            //注意：下标从0开始
            preRightPRep[i] = preRightSBoxSeRep[this->pRepTable[i] - 1];
        }

        // 2.3.6下一轮右：上一轮右与上一轮左异或    32->32位
        string preRightXor2(""); //下一轮右的异或2
        for (int i = 0; i < preLeft.size(); ++i)
        {
            if (preRightPRep[i] == preLeft[i]) //相同为0
            {
                preRightXor2 += '0';
            }
            else //不同为'1'
            {
                preRightXor2 += '1';
            }
        }

        string nextRight(preRightXor2); //下一轮右

        //注意：
        //循环外定义的变量可能需要更新
        //循环内定义的变量为局部变量，不需要更新，方便
        preText = nextLeft + nextRight; //更新上一轮文本

        cout << "明/密文的第" << wheelCount << "轮输出：\t" << preText << endl;
    }
    cout << endl;

    textWheelF = preText; //文本的轮函数F为上一轮文本

    return;
}

//解密
//注意过程：
// 1.初始置换IP
// 2.轮函数F
// 3.左右置换
// 4.逆初始置换IP-1
//提示：因为通过重构解耦合，直接复用加密函数代码，修改变量名称和注释即可
//注意：
//加密的轮函数F中，使用轮密钥K1，K2...K16，轮函数下标0，1...15
//解密的轮函数F中，使用轮密钥K16，K15...K1，轮函数下标15，14...1
//所以，解密的轮密钥生成中，反向记录轮密钥，即可复用相同的轮函数函数
void DES::decrypt(const string &cipherTextASCII, const string &key, string &plainTextASCII) //参数：密文的ASCII码，密钥，明文的ASCII码
{
    cout << "解密过程：————————————————————" << endl;

    //对密文和密钥：
    cout << "密钥：\t" << key << endl;

    this->cipherTextASCII = cipherTextASCII; //记录密文的ASCII码
    cout << "密文的ASCII码：\t" << this->cipherTextASCII << endl;
    // 0.初始化为二进制  8字节->64位
    string keyASCII("");                  //密钥的ASCII码   64位
    this->byteStrToBitStr(key, keyASCII); // 8字节字符串转64位字符串 依据ASCII码
    this->keyASCII = keyASCII;            //记录密钥的ASCII码
    cout << "密钥的ASCII码：\t" << this->keyASCII << endl;
    cout << endl;

    //对密钥：
    // 1.密钥的选择置换 64->56位
    string keySeRep(56, '-'); //密钥的选择置换   56位
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    for (int i = 0; i < this->keySeRepTable.size(); ++i)
    {
        //置换规则：依据置换表，输入的第57位是输出的第1位->输入的第56位是输出的第0位
        //注意：下标从0开始
        keySeRep[i] = this->keyASCII[this->keySeRepTable[i] - 1];
    }
    cout << "密钥的选择置换：\t" << keySeRep << endl;

    // 2.轮密钥生成
    //注意：预先生成
    string preKey(keySeRep);  //上一轮密钥 56位
    string nextKey("");       //下一轮密钥 56位
    string wheelKey(48, '-'); //轮密钥 48位
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    //提示：
    //在循环外而不是循环中声明并初始化/定义对象，避免重复进行对象的构造和析构，减少开销
    //但可读性差

    // 16轮轮函数
    //注意：轮数从1开始
    for (int wheelCount = 1; wheelCount <= 16; ++wheelCount) //轮数计数
    {
        //轮密钥生成
        //参数：上一轮密钥（56位），轮数（从1开始），下一轮密钥（56位），轮密钥（48位）
        this->wheelKeyGener(preKey, wheelCount, nextKey, wheelKey);

        //记录轮密钥
        this->wheelKeys[16 - wheelCount] = wheelKey;
        //注意：轮数从1开始，轮密钥下标从15开始
        //注意：记录轮密钥（48位）而不是下一轮密钥（56位）

        //注意：
        //循环外定义的变量可能需要更新
        //循环内定义的变量为局部变量，不需要更新，方便
        preKey = nextKey; //更新上一轮密钥 56位
        nextKey = "";     //更新下一轮密钥 56位
        //轮密钥每轮都通过下标填充，不需要更新
    }

    //对密文：
    // 1.初始置换IP 64->64位
    string cipherTextIp(64, '-'); //密文的初始置换IP   64位
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    for (int i = 0; i < this->ipTable.size(); ++i)
    {
        //置换规则：依据置换表，输入的第58位是输出的第1位->输入的第57位是输出的第0位
        //注意：下标从0开始
        cipherTextIp[i] = this->cipherTextASCII[this->ipTable[i] - 1];
        //注意：忘记修改this->plain为cipher了...
    }
    cout << "密文的初始置换IP：\t" << cipherTextIp << endl;
    cout << endl;

    // 2.轮函数F
    string cipherTextWheelF(""); //密文的轮函数  64位
    wheelFunc(cipherTextIp, keySeRep, cipherTextWheelF);
    //参数：密文的初始置换IP，密钥的选择置换，密文的轮函数
    cout << "密文的轮函数F：\t" << cipherTextWheelF << endl;

    // 3.左右置换/轮函数F的第16轮不进行左右置换 64->64位
    string left(cipherTextWheelF.substr(0, 32));   //左 范围：0~31
    string right(cipherTextWheelF.substr(32, 32)); //右 范围：32~63
    string cipherTextLeRiRep = right + left;       //密文的左右置换
    cout << "密文的左右置换：\t" << cipherTextLeRiRep << endl;

    // 4.逆初始置换IP-1 64->64位
    string cipherTextIIp(64, '-'); //密文的逆初始置换IP-1
    //注意：因为需要使用下标赋值，所以需要初始化大小以预分配空间
    //注意：初始化为不是0或1的字符，以验证是否成功
    for (int i = 0; i < this->iIpTable.size(); ++i)
    {
        //置换规则：依据置换表，输入的第40位是输出的第1位->输入的第39位是输出的第0位
        //注意：下标从0开始
        cipherTextIIp[i] = cipherTextLeRiRep[this->iIpTable[i] - 1];
    }
    cout << "密文的逆初始置换IP-1：\t" << cipherTextIIp << endl;
    cout << endl;

    this->plainTextASCII = cipherTextIIp; //记录明文的ASCII码   明文的ASCII码为密文的逆初始置换IP-1
    cout << "明文的ASCII码：\t" << this->plainTextASCII << endl;
    cout << endl;

    plainTextASCII = cipherTextIIp; //记录结果   明文的ASCII码为密文的逆初始置换IP-1

    return;
}