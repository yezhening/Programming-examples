#include <ctime>   //time()
#include <cstdlib> //srand()、rand()

#include "DH.h"

// 构造
DH::DH()
{
    // 全局公开量：
    //  1. 选择p。p为素数
    //  注意：将随机种子提取放在循环外、相同函数外，以避免时间相近获取的随机数相同
    unsigned int seed = time(nullptr); // 随机种子
    srand(seed);                       // 设置随机种子

    this->p_arg_ = this->GetPrimeNum(); // 获取素数

    // 2.计算a。a < p且a是p的本原根
    this->a_arg_ = this->GetPrimitiveRoot(); // 获取本原根

    cout << "全局公开量：" << endl;
    cout << "参数p：\t" << this->p_arg_ << endl;
    cout << "参数a：\t" << this->a_arg_ << endl;
    cout << endl;
}

// 获取私钥
unsigned int DH::GetPrivateKey()
{
    // 私钥要求：随机整数；简化为非负数；小于参数p
    unsigned int random = 0; // 随机数

    while (1) // 循环
    {
        random = rand(); // 随机数 一般是4~5位数，不超过unsigned int的表示范围

        if (random < this->p_arg_)
        {
            break;
        }
    }

    return random;
}

// 获取公钥
unsigned int DH::GetPublicKey(const unsigned int &x) // 参数：私钥
{
    // 公钥Y = 参数a的私钥X次方 mod p（X是以a为底的模p离散对数）
    unsigned int y = this->QuickPowMod(this->a_arg_, x, this->p_arg_);

    return y;
}

// 获取密钥
unsigned int DH::GetKey(const unsigned int &y, const unsigned int &x) // 参数：对方的公钥，本方的私钥
{
    // 密钥K = 对方的公钥Y的本方的私钥X次方 mod p
    unsigned int k = this->QuickPowMod(y, x, this->p_arg_);

    return k;
}

// 获取素数
unsigned int DH::GetPrimeNum()
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
bool DH::PrimalityTest(const unsigned int &n, const unsigned int &a) // 参数：随机奇数，参数a
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
unsigned int DH::QuickPowMod(const unsigned int &a, const unsigned int &q, const unsigned int &n)
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
unsigned int DH::QuickMulMod(const unsigned int &a, const unsigned int &b, const unsigned int &c)
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

// 获取本原根
unsigned int DH::GetPrimitiveRoot()
{
    // 大致思路：对素数p，p的欧拉函数p - 1，底数a属于（1，p），指数m属于（1，p）
    // 正向判定本原根满足：
    // 1.当m = （1，p - 1）的数时，所有a^m % p 不等于 1
    // 2.当m = p - 1时，a^m % p = 1
    // 则a为本原根

    // 逆向否定本原根满足：由正向的1.逆否命题得
    // 1.当m = （1，p - 1）的数时，存在a^m % p = 1，则a不为本原根

    // 快速正向判定本原根满足：
    // 1.当m = （p - 1的素因子）的数时，所有a^m % p 不等于 1，则a为本原根

    // 慢速正向判定本原根满足：由快速正向扩大搜索范围得
    // 1.当m = （1，p - 1）的数时，所有a^m % p 不等于 1，则a为本原根

    // 提示：
    // 可以证明暴力枚举求最小本原根的复杂度是可以接受的，采用正向逆向结合判定本原根的暴力枚举法
    // 参数p的欧拉函数为p -1
    unsigned int calcul_res = 0; // 计算结果

    // 2.1遍历（1，p）为底数
    for (unsigned int i = 2; i < this->p_arg_; ++i) // 范围：2 ~ p - 1
    {
        // 2.2遍历（1，p）为指数
        for (unsigned int j = 2; j < this->p_arg_; ++j) // 范围：2 ~ p - 1
        {
            calcul_res = this->QuickPowMod(i, j, this->p_arg_); // 计算结果 = i ^ j % p

            // 2.2.1当m = （1，p - 1）的数时，所有a^m % p 不等于 1
            // 逆否命题为当m = （1，p - 1）的数时，存在a^m % p = 1，则a不为本原根
            if ((j != this->p_arg_ - 1) && (calcul_res == 1))
            {
                break; // 退出j循环，取下一个i
            }

            // 2.2.2在2.2.1没退出j循环，且当m = p - 1时，a ^ m % p = 1
            if ((j == this->p_arg_ - 1) && (calcul_res == 1))
            {
                return i; // i为（最小）本原根，返回本原根i
            }
        }
    }

    // 提示：素数必存在本原根，存在i并返回。但代码逻辑需考虑不满足if()条件返回i的另外返回条件
    return 0; // 必不会执行
}
