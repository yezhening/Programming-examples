#include <ctime>   //time()
#include <cstdlib> //srand()、rand()

#include "RSA.h"

using std::cerr;
using std::cout;
using std::endl;

// 构造
RSA::RSA()
{
    this->KeyGen(); // 密钥生成

    cout << "密钥生成: \t" << endl;
    cout << "参数p: \t" << this->p_arg_ << endl;
    cout << "参数q: \t" << this->q_arg_ << endl;
    cout << "参数n: \t" << this->n_arg_ << endl;
    cout << "参数n的欧拉函数: \t" << this->n_Euler_func_arg_ << endl;
    cout << "参数e: \t" << this->e_arg_ << endl;
    cout << "参数d: \t" << this->d_arg_ << endl;
    cout << endl;
}

// 加密
// 参数：字符串类型的明文，无符号整型的密文
void RSA::Encrypt(const string &plaintext_str, vector<unsigned int> &ciphertext_int)
{
    cout << "加密：\t" << endl;
    cout << "字符串类型的明文：\t" << plaintext_str << endl;

    // 1.依据ASCII码将明文的字符串数据类型转换为无符号整数类型
    unsigned int p = 0; // 明文分组   1个字符1个数字为1个明文分组
    // 提示：要求明文分组P < 参数n，依据ASCII范围0~255必 < n，不再处理
    vector<unsigned int> plaintext_int(plaintext_str.size(), 0); // 无符号整数类型的明文    1个字符为1个数字

    for (int i = 0; i < plaintext_str.size(); ++i)
    {
        p = plaintext_str[i]; // 注意：利用自动类型转换
        plaintext_int[i] = (p);
    }

    cout << "无符号整数类型的明文：\t";
    for (int num : plaintext_int)
    {
        cout << num << " ";
    }
    cout << endl;

    // 2.加密
    unsigned int c = 0; // 密文分组   1个数字明文加密得1个数字密文，1个数字为1个密文分组

    for (int i = 0; i < plaintext_int.size(); ++i) // 对每个明文分组，蒙哥马利快速模幂加密
    {
        c = this->QuickPowMod(plaintext_int[i], this->e_arg_, this->n_arg_);
        ciphertext_int[i] = c;
    }

    cout << "无符号整数类型的密文：\t";
    for (int num : ciphertext_int)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    return;
}

// 解密
void RSA::Decrypt(const vector<unsigned int> &ciphertext_int, string &plaintext_str1)
{
    cout << "解密：\t" << endl;
    cout << "无符号整数类型的密文：\t";
    for (int num : ciphertext_int)
    {
        cout << num << " ";
    }
    cout << endl;

    // 1.解密
    unsigned int p = 0;                                           // 明文分组 1个数字密文解密得1个数字明文，1个数字为1个明文分组
    vector<unsigned int> plaintext_int(ciphertext_int.size(), 0); // 无符号整数类型的明文    1个字符为1个数字

    for (int i = 0; i < ciphertext_int.size(); ++i) // 对每个密文分组，蒙哥马利快速模幂解密
    {
        p = this->QuickPowMod(ciphertext_int[i], this->d_arg_, this->n_arg_);
        plaintext_int[i] = p;
    }

    cout << "无符号整数类型的明文：\t";
    for (int num : plaintext_int)
    {
        cout << num << " ";
    }
    cout << endl;

    // 2.依据ASCII码将明文的无符号整数类型转换为字符串数据类型
    char p_str = '\0'; // 字符类型的明文分组    1个数字1个字符为1个明文分组
    for (int i = 0; i < plaintext_int.size(); ++i)
    {
        p_str = static_cast<char>(plaintext_int[i]); // 注意：利用强制类型转换
        plaintext_str1[i] = (p_str);
    }

    cout << "字符串类型的明文：\t" << plaintext_str1 << endl;

    return;
}

// 密钥生成
void RSA::KeyGen()
{
    // 1. 选择p，q。p和q为素数，p不等于q
    // 注意：将随机种子提取放在循环外、相同函数外，以避免时间相近获取的随机数相同
    unsigned int seed = time(nullptr); // 随机种子
    srand(seed);                       // 设置随机种子

    this->p_arg_ = this->GetPrimeNum(); // 获取p参数
    this->q_arg_ = this->GetPrimeNum(); // 获取q参数

    // 2. 计算n = p × q
    this->n_arg_ = this->p_arg_ * this->q_arg_;
    // 提示：第一次写习惯中文用了×号而不是*...

    // 3. 计算n的欧拉函数 = (p - 1) × (q - 1)
    this->n_Euler_func_arg_ = (this->p_arg_ - 1) * (this->q_arg_ - 1);

    // 4. 选择e。 e为整数，e和n的欧拉函数互素，1 < e < n的欧拉函数
    // 选择3或17或65537，e越大相对的d越小，两值比较平衡
    // 注意：e和n的欧拉函数互素，不能想当然的选取
    if (this->n_Euler_func_arg_ % 65537 != 0)
    {
        this->e_arg_ = 65537;
    }
    else if (this->n_Euler_func_arg_ % 17 != 0)
    {
        this->e_arg_ = 17;
    }
    else if (this->n_Euler_func_arg_ % 3 != 0)
    {
        this->e_arg_ = 3;
    }
    else // 极端几乎不可能情况
    {
        cerr << "无法选取参数e" << endl;
        exit(EXIT_FAILURE); // 程序直接退出
    }

    // 5. 计算d。d × e % n的欧拉函数 = 1，d < n的欧拉函数
    this->d_arg_ = GetMulInverse(this->e_arg_, this->n_Euler_func_arg_);
    // 注意：对n的欧拉函数而不是参数n

    return;
}

// 获取素数
unsigned int RSA::GetPrimeNum()
{
    unsigned int random = 0;     // 随机数
    unsigned int random_odd = 0; // 随机奇数

    unsigned int n = 0;              // 素性测试的参数n 循环中需要重新初始化
    unsigned int a = 0;              // 素性测试的参数a
    bool primality_test_res = false; // 一次素性测试结果    false不是素数true可能为素数
    bool prime_flag = false;         // 素数标志，最终素性测试结果。false0不是素数，true1可能为素数
    // 提示：初始化在循环外的变量在循环中注意是否需要更新、重新初始化

    while (1) // 循环
    {
        // 1.1随机取一个期望大小的奇数
        // 1.1.1取随机数
        random = rand(); // 随机数 一般是4~5位数，不超过unsigned int的表示范围

        // 1.1.2取奇数
        if (random % 2 == 0) // 如果是偶数，+1成为奇数
        {
            random_odd = random + 1;
        }
        else // 奇数不额外操作
        {
            random_odd = random;
        }

        // 1.2使用素性测试判断
        n = random_odd;

        for (int i = 0; i < 128; ++i) // 选取128个参数a，测试128次
        {
            //  1.2.1随机选择相关参数a。满足a为整数，1 < a < n - 1
            a = rand() % (n - 1); // 0 ~ n - 2
            // 注意：
            // 因为运行时间段相近，第一次a取的随机数可能和n相等
            // 则计算后结果必为1，而后1 + 1 = 2
            // 将设置随机种子代码提取出函数后，排除该错误
            if (a == 0) // 如果是0，令a = 2 > 1
            {
                a += 2;
            }
            if (a == 1) // 如果是1，令a = 2 > 1
            {
                ++a;
            }

            primality_test_res = PrimalityTest(random_odd, a); // 素性测试

            if (primality_test_res == true) // 一次测试结果可能为素数
            {
                prime_flag = true; // 标记可能为素数
            }
            else if (primality_test_res == false) // 只要有一次素性测试不是素数，则必不为素数
            {
                prime_flag = false;

                break; // 不再用a测试，需要重新选取随机奇数
            }
        }

        if (prime_flag == true) // 随机奇数可能为素数，
        {
            break; // 退出循环
        }
        // 否则随机奇数不是素数，进入循环，再重新进行1.1取随机奇数，1.2素性测试步骤
    }

    return random_odd; // 获得素数
}

// Miller-Rabin素性测试
bool RSA::PrimalityTest(const unsigned int &n, const unsigned int &a) // 参数：随机奇数，参数a
{
    // 1.2.2找到相关参数k，q。满足n - 1 = 2 ^ k × q。k、q为整数，k > 0，q为奇数
    unsigned int k = 0;
    unsigned int q = n - 1;

    // 提示：
    // 很多算法都只说明要找到k、q，却不说怎么找
    // 找k，q的代码也含糊其辞的
    while ((q & 1) == 0)
    {
        ++k;
        q >>= 1;
    }
    // 理解：
    // q & 1：即q的二进制表示与二进制位1与运算，取q二进制表示的最低位0或1
    // 如101 & 1 = 101 & 001 = 001 = 1
    // 如0010 & 1 = 0010 & 0001 = 0

    // 在最低位中，基数2 ^ 0 = 1，所以如果值是0，则1 × 0 = 0为偶数；值是1，则1 × 1 = 1为奇数
    // 所以，如果运算结果为0，则是偶数，可以提取一个因子2
    // while：连续提取因子2
    // 每提取一个因子2，则++k，k是因子2的计数
    // q >>= 1：将q的二进制表示右移缩小，继续对最低位判断提取因子2
    // 直到不能连续提取因子2，则q即为所求

    // 如十进制13 - 1 = 12 = 二进制1100，在第1、2位提取因子2为2 ^ 2 = 4
    // 所以12 = 2 ^ 2 × 3。k = 2，q = 3
    // 如十进制7 - 1 = 6 = 二进制110，在第1位提取1个因子2为2 ^ 1 = 2
    // 所以6 = 2 ^ 1 × 3。k = 1，q = 3

    // 提示：注意k、q的取值条件
    // 对正整数素数，除了2为偶数，其他数必为奇数
    // 奇数-1必为偶数，必至少能提取1个公因子2，则k至少为1 > 0满足
    // 由算法性质，知提取所有的公因子2，则结果q必为奇数满足
    // 一般q数很大，所以在接下来的步骤需要用蒙哥马利快速模幂算法

    // 1.2.3计算a ^ q % n
    unsigned int aq_mod_n = this->QuickPowMod(a, q, n);

    // cout << n << endl;
    // cout << k << endl;
    // cout << q << endl;
    // cout << a << endl;
    // cout << aq_mod_n << endl;

    // 1.2.4运用二次探测定理的逆否命题判断
    // 正命题大概：探测，所有解只有1或n-1，则可能为素数
    // 逆否命题大概：探测，存在解不为1且不为n-1，则必定不是素数
    // 可以用正命题也可以用逆否命题判断。以下用正命题和逆否命题判断
    // 第一个判断条件：未探测时，a ^ q % n == 1，则可能为素数
    if (aq_mod_n == 1)
    {
        return true;
    }

    // 第二个判断条件：二次探测时，只要存在不为1且不为n-1，则必定不是素数
    for (int j = 0; j < k; ++j) // 0 ~ k-1
    {
        aq_mod_n = this->QuickPowMod(aq_mod_n, 2, n);
        // 对序列二次探测 计算a ^ (q × 2 ^ j) % n = aq_mod_n ^ (2 ^ j) % n。每次循环都幂2相当于(2 ^ j)

        if (aq_mod_n != 1 && aq_mod_n != n - 1)
        {
            return false;
        }
    }
    return true; // 第二个判断条件：二次探测时，若没有因判断为合数而返回，则可能为素数
}

// 蒙哥马利快速幂模运算
// 参数：a ^ q % n
// 返回值：a ^ q % n
unsigned int RSA::QuickPowMod(const unsigned int &a, const unsigned int &q, const unsigned int &n)
{
    // 原理：
    //  幂运算性质：a ^ q = a ^ q1 × a ^ q2。q = q1 + q2
    //  模运算性质：(a × b) % n = [(a % n) × (b % n)] % n
    // 所以：a ^ q % n = (a ^ q1 × a ^ q2) % n = [(a ^ q1 % n) × (a ^ q2 % n)] % n
    unsigned int res = 1;
    unsigned int a_temp = a; // 运算中会改变a的值，暂存
    unsigned int q_temp = q; // 运算中会改变q的值，暂存

    // 提示：很多算法代码含糊其辞的
    while (q_temp > 0)
    {
        if ((q_temp & 1) == 1)
        {
            res = this->QuickMulMod(res, a_temp, n);
        }

        a_temp = this->QuickMulMod(a_temp, a_temp, n);

        q_temp >>= 1;
    }
    // 理解：
    // 算法是针对十进制数的二进制表示进行运算的

    // while (q_temp > 0)：对比素性测试的内容：while ((q & 1) == 0)
    // 这里是判断值，需要判断所有二进制位，所以只要q在后面的右移位中值不为0，就循环。而素性测试中是判断位

    // if ((q_temp & 1) == 1)：最低位为1时，该位有效，需要计算并更新结果
    // 快速乘算法：res = (res × a_temp) % n
    // 该步骤相当于每次计算单个的(a ^ q2 % n)，然后和之前的(a ^ q1 % n)相乘作为新的结果
    // 其中第一个res是更新结果，第二个res是之前的结果，a_temp是当前的基数
    // 基数：在循环中对每一位都会更新基数（见后面步骤），在二进制表示为1时，该基数有效

    // a_temp = QuickMulMod(a_temp, a_temp, n);相当于a_temp = a_temp × a_temp % n
    // 如初始a_temp = 2，则不断更新为2 ^ 0 = 1，2 ^ 1 = 2
    // 再进行%保证基数不超过范围

    return res;
}

// 快速乘
// 参数：a * b % c
// 返回值：a * b % c
unsigned int RSA::QuickMulMod(const unsigned int &a, const unsigned int &b, const unsigned int &c)
{
    // 原理：
    // 同快速幂模运算，将乘法转换为加法运算
    // a × b % c = [(a + a) % c] + [(a + a) % c] + ... [(a + a) % c]共b个a相加求模
    unsigned int res = 0;
    unsigned int a_temp = a;
    unsigned int b_temp = b;

    while (b_temp > 0)
    {
        if (b_temp & 1)
        {
            res = (res + a_temp) % c;
        }

        a_temp = (a_temp + a_temp) % c;

        b_temp >>= 1;
    }

    return res;
}

// 扩展欧几里得算法
// 参数和返回值：
// 由欧几里得算法，求两数a和b，a >= b的最大公约数g
// 由贝祖定理，存在令a × x + b × y = g的解x和y
// 由扩展欧几里得算法，求令a × x + b × y = gcd的一组解x，y
// 该组解x和y随后用于求乘法逆元
unsigned int RSA::ExGcd(const unsigned int &a, const unsigned int &b, unsigned int &x, unsigned int &y)
{
    // 大致思路：
    //  由欧几里得算法，求a和b的最大公约数：gcd(a，b) = gcd(b，a % b)
    //  所以是个递归过程，递归出口为右数b，即右数a % b = 0，此时左数a即为最大公约数返回
    //  此时即：gcd(g，0) = g = a × x + b × y = a × 1 + b × 0
    //  即在递归栈顶时，求得解x = 1，y = 0
    //  随后逐层返回退出递归栈，由扩展欧几里得算法推导，将x和y逐层更新，最后求得解x和y

    // 递归出口
    if (b == 0)
    {
        x = 1;
        y = 0;

        return a;
    }

    // 递归逻辑
    unsigned int g = ExGcd(b, a % b, x, y); // g是当前递归的最大公约数

    // 提示：
    // 将x和y从栈底到栈顶更新，即正向写代码逻辑递归
    // 则返回时从栈顶到栈底更新，最后求得解
    int temp = y;
    y = x - (a / b) * y;
    x = temp;

    return g; // 返回最大公约数
}

// 求乘法逆元
// 参数：a × x % b = 1的a和b
// 返回值：a模b的乘法逆元x
unsigned int RSA::GetMulInverse(const unsigned int &a, const unsigned int &b)
{
    // 大致思路：
    // 若求a模b的乘法逆元x，即a × x % b = 1
    //  即同余式：ax ≡ 1(mod b)
    //  可转换为不定方程：a × x + b × y = 1

    // 对两个素数a，b，最大公约数为1，即gcd(a，b) = 1
    // 所以：a × x + b × y = 1 = gcd(a，b)
    // 由贝祖定理，存在令a × x + b × y = gcd(a，b)的解x和y
    // 即已知a和b，求解x

    // 所以：
    // 使用扩展欧几里得算法求a × x + b × y = 1的解x
    // 由同余式，逆元z=(x % b + b) % b

    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int g = this->ExGcd(a, b, x, y); // 使用扩展欧几里得算法求a × x + b × y = 1的解x

    x = (x % b + b) % b;
    // 提示：
    // x是a模b的乘法逆元，但不能保证是正数，不能保证落在(a,b)内，所以需要更新
    // 这一步很多讲解都含糊其辞

    // 思路：如果求得x为负数，则需要转换为正数，由模运算性质保证结果不变
    // 假设x = -9，b = 20
    // 由模运算性质：对负数-9 ≡ -9 % 20 ≡ 对正数x1 % 20
    // 想办法将负数-9转换为正数x1，且保证模后结果恒等
    // 将20转换为负数，再加上一个因子构造-9，即[20 × (-1) + 11] % 20 = -9
    // 由模运算性质：-9 = -9 % 20= [20 × (-1) + 11] % 20 = {[(-20) % 20] + (11 % 20)} % 20 = [0 + (11 % 20)] % 20  = 11 % 20 = 11
    // 所以新更新的x1为11

    // x % b：缩小负数在(-b，0]范围
    // 加上1个b能够一次性转换为正数，范围在[0，b]
    // 注意如果x % b = 0时，+b = b，还需要% b使范围落在[0，b)

    return x;
}