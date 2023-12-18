// 懒汉式：程序运行时创建单例类对象（需要用了才创建）
#include <iostream>
#include <mutex>

using std::cout;
using std::endl;
using std::lock_guard;
using std::mutex;

// 单例类
class Singleton
{
public:
    // 注意：静态对象由程序管理，不需要析构方法
    // ~Singleton()
    // {
    //     delete singleton;
    // }

    // 公有静态获取单例对象方法
    static Singleton &getsingleton() // 返回引用的原因：保证是同一单例对象而不是副本；减少返回值的拷贝开销；返回值拷贝被删除
    {
        // 线程不安全（如多个线程同时调用公有静态获取单例对象方法）
        // 使用 私有静态互斥锁 和 双重检查锁定（保证线程安全）
        if (singleton == nullptr) // 第一重检查锁定
        {
            lock_guard<mutex> mutex_lock_guard(mutex_lock); // 上锁

            // 第二次检查，确保在互斥锁区域内再次检查单例对象是否未创建
            if (singleton == nullptr) // 第二重检查锁定
            {
                singleton = new Singleton();
            }

            // 隐式解锁
        }

        return *singleton;
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
    static Singleton *singleton;

    // 私有静态互斥锁
    static mutex mutex_lock;
};

// 在类外初始化私有静态单例对象为空 和 私有静态互斥锁 注意：
// 静态非 const 整数类型（short 和 int 等） 或 静态非 constexpr 内置类型（char 和 float 等）的成员属性 只能在类外初始化
// 因为构造方法是私有权限，所以在类外只能是隐式调用无参构造方法
// 如果单例类需要传参并初始化成员属性，可以考虑额外 定义设置成员属性方法 或 在公有静态获取单例对象方法中设置成员属性
Singleton *Singleton::singleton = nullptr;
mutex Singleton::mutex_lock;

// 客户端
int main()
{
    // 创建或获取单例对象
    Singleton &singleton_1 = Singleton::getsingleton(); // 使用引用的原因：保证是同一单例对象而不是副本；减少返回值的拷贝开销；返回值拷贝被禁止
    Singleton &singleton_2 = Singleton::getsingleton();

    // 输出单例对象地址：地址相同，说明是同一单例对象
    cout << "Singleton_1: " << &singleton_1 << endl;
    cout << "Singleton_2: " << &singleton_2 << endl;

    return 0;
}
/*
输出：
Singleton()
Singleton_1: 0x2502500
Singleton_2: 0x2502500
*/