[TOC]

# 说明

## 大（素）数讨论

- 实际的RSA需要操作大（素）数
- 因为大（素）数结合RSA的代码实现较复杂，所以本代码未实现大（素）数部分，（简单）实现RSA部分
- 网络上有很多大数实现的思路和代码资料，有兴趣可以参阅

### 部分资料

- [生成1024比特随机数-编程语言-CSDN问答](https://ask.csdn.net/questions/7514078)
- [RSA 大数的处理 - 简书 (jianshu.com)](https://www.jianshu.com/p/1e139541c4eb)
- [大整数类的实现 - 万户侯 - 博客园 (cnblogs.com)](https://www.cnblogs.com/billsedison/archive/2010/12/25/1916626.html)
- [C++大整数运算（一）：概述 – kedixa的博客](https://blog.kedixa.top/2017/cpp-bigint-overview/)
- [RSA与大数运算（C语言）_cmj198799的博客-CSDN博客](https://blog.csdn.net/cmj198799/article/details/6883274)
- [RSA与大数运算 - 勇敢蘑菇 - 博客园 (cnblogs.com)](https://www.cnblogs.com/shoule/p/15950488.html)
- [BigInt (BIG INTEGERS) in C++ with Example - GeeksforGeeks](https://www.geeksforgeeks.org/bigint-big-integers-in-c-with-example/)

### 作者理解

> 注意：理解中部分基于学校计算机网络安全课程的实验要求

可能性：

- 能够实现自定义大数数据结构/类及其上的相关算法
- 但是，将其嵌入RSA算法的实现，无论是对于实验量、实验要求时长，都相对复杂些

复杂性的体现：

- 如果使用相对面向数学计算、大数据应用的语言，如Python，直接调现有的库，可能认为无所不能。需要学习使用库的成本，相对的，就没有对“自定义大数结构和运算”这一“造轮子、拧螺丝”的底层理解
- 如果使用面向底层原理的语言，如C和C++，可能也有库可以直接调用，但可能没有Python那么方便使用
- 如果想自定义大数结构和运算，就需要对底层如语言支持的数据类型有一定的规划和了解。设计的这个大数结构和运算必须能够在RSA算法中被应用，而RSA算法中稍复杂的数学算法更会限制这个大数类的设计。RSA算法中，对简单数的操作已经相对复杂，再进一步对大数操作，复杂度就提升了
- 搜索网上单纯对大数的自定义代码实现（C和C++语言），几百行快至千行还是有的，再针对RSA算法进行重构，代码量会更多

可能的实现：

1.使用十进制数数组/向量表示大数。大数的各个位是数组中的一个元素

- 实验要求：1024位的参数p，1024位的参数q，可能为2048位的参数n
- 实验要求需要使用二进制进行运算，另外，相应数论中使用二进制相对十进制有更简便快捷的算法
- 1024位二进制约为309位十进制数，2048位不太清楚。也就是说，十进制数组初始化大小是不太确定的。就C++而言，向量最好初始化大小，否则在未定义大小的基础上不断添加元素，可能会造成预先分配的向量空间不够，出现越界、向量空间扩容重分配等未知不好定位问题
- 几百位十进制的大数运算，在加法进位、减法借位、乘法等运算中，需要对每位操作，嵌套循环、循环次数、记录借位标志等情况很复杂

2.使用二进制数数组/向量表示大数。大数的各个位是数组中的一个元素

- 能够满足实验要求的1024位
- 但对于可能的2048位参数n，可能也不明确向量的初始化大小
- 千位二进制相对百位十进制，定义每位操作，嵌套循环、循环次数、记录借位标志等情况会更加复杂

3.使用2^32进制数组/向量表示大数。大数的各个位是数组中的一个元素

- 是最可能实现的方案
- 要求1024位二进制
- 语言的内置类型范围最多为64位二进制，考虑到乘法运算会使位数扩大，如超过64位而表示不了，则折中选取32位二进制，可用int数据类型表示
- 再考虑到参数>0，可用unsigned int数据类型表示
- 即：相对于1.使用十进制，2.使用二进制，该方案使用2\^32进制。数组中一个0~9范围内的数字，它的基数为2\^32
- 1024 ÷ 32 = 32，则参数pq的数组/向量长度缩减为32，大大简化各种运算时的操作
- 但是，基数为2\^32，则在语言的表现层面，最小操作粒度是2\^32。比如用unsigned int数据类型的数字0表示0 × 2\^32的大数，用unsigned int数据类型的数字1表示1 × 2\^32的大数。而数字0-1即大数0-2^32的间的各种数字，在宏观层面应该是操作不到、不好操作的
- 再考虑到RSA算法中，可以使用大数运算求得p、q、n参数。但是，对于后续细粒度的n - 1、n的欧拉函数 = (p - 1)(q - 1) = p × q + p + q - 1等对较小数1，应该是操作不到、不好操作的
- 更不用考虑后续RSA其他数学算法了

总结：

- 可能性：大数可以实现，但不好实现。可以调库也可以自定义
- 复杂度：纯大数相对简单，考虑编程语言、为了适应RSA算法，大数结构和运算的设计相对复杂
- 可能的实现：方案都可能可以实现，综合考虑实验目的、实验量和实验时长等问题，成本可能会很高

## 参考资料

- 《密码编码学与网络安全——原理与实践(第五版)》作者：William Stallings
- [Miller-Rabin 素性检测 - kentle - 博客园 (cnblogs.com)](https://www.cnblogs.com/kentle/p/14975056.html)
- [Miller-Rabin素数测试算法_forever_dreams的博客-CSDN博客_millerrabin素数测试算法](https://blog.csdn.net/forever_dreams/article/details/82314237)
- [素性测试的Miller-Rabin算法完全解析 （C语言实现、Python实现）_heshiip的博客-CSDN博客_millerrabin算法c代码](https://blog.csdn.net/heshiip/article/details/95679397)
- [米勒-拉宾素性检验(MillerRabbin)算法详解_1900_的博客-CSDN博客_米勒拉宾素性检验](https://zpf1900.blog.csdn.net/article/details/85197424?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1-85197424-blog-51457540.pc_relevant_landingrelevant&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1-85197424-blog-51457540.pc_relevant_landingrelevant&utm_relevant_index=2)
- [扩展欧几里得算法（详细推导+代码实现+应用）_胡小涛的博客-CSDN博客_扩展欧几里得算法代码](https://blog.csdn.net/lovecyr/article/details/105372427)
- [求解乘法逆元的方法_默_silence的博客-CSDN博客_求乘法逆元](https://blog.csdn.net/weixin_43772166/article/details/104254604)
- [计算乘法逆元 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/370615983)