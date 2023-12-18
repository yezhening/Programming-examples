// 饿汉式：程序启动时（main() 执行前） 创建单例对象（不管用不用都提前创建）
#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
public:
    // 公有静态获取单例对象方法
    inline static Singleton &getInstance() // 返回引用的原因：保证是同一单例对象而不是副本；减少返回值的拷贝开销；返回值拷贝被删除
    {
        return singleton; // 直接返回单例对象：因为在程序启动时（main() 执行前）已经创建单例对象，且线程安全，无需其他逻辑
    }

private:
    // 私有构造方法
    Singleton()
    {
        cout << "Singleton()" << endl;
    }

    // 私有或删除拷贝构造方法和拷贝赋值运算符
    // 设置为私有：允许类内将单例对象作为参数或返回值传递（公有静态获取单例对象方法 可以返回值而不是引用）
    // 设置为删除：禁止拷贝
    // 设置为私有和删除：禁止拷贝
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    // 私有静态单例对象
    static Singleton singleton;
};

// 在类外初始化私有静态单例对象 注意：
// 静态非 const 整数类型（short 和 int 等） 或 静态非 constexpr 内置类型（char 和 float 等）的成员属性 只能在类外初始化
// 因为构造方法是私有权限，所以在类外只能是隐式调用无参构造方法
// 如果单例类需要传参并初始化成员属性，可以考虑额外 定义设置成员属性方法 或 在公有静态获取单例对象方法中设置成员属性
Singleton Singleton::singleton; // 隐式调用无参构造方法

// 客户端
int main()
{
    // 创建或获取单例对象
    Singleton &singleton_1 = Singleton::getInstance(); // 使用引用的原因：保证是同一单例对象而不是副本；减少返回值的拷贝开销；返回值拷贝被删除
    Singleton &singleton_2 = Singleton::getInstance();

    // 输出单例对象地址：地址相同，说明是同一单例对象
    cout << "Singleton_1: " << &singleton_1 << endl;
    cout << "Singleton_2: " << &singleton_2 << endl;

    return 0;
}
/*
输出：
Singleton()
Singleton_1: 0x407030
Singleton_2: 0x407030
*/