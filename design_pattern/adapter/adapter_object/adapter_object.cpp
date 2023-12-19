#include <iostream>

using std::cout;
using std::endl;

// 被适配类（客户端 期望/可以使用/形式上使用 的 接口；适配者）
class Adaptee
{
public:
    void adaptee_func() const
    {
        cout << "adaptee_func()" << endl;

        return;
    }
};

// 目标类（客户端 期望/可以使用/形式上使用 的 接口；适配者）
class Target
{
public:
    virtual void target_func() const = 0;
};

// 适配器类（中间者）
// 适配器类 继承 目标类
class Adapter : public Target
{
public:
    Adapter() : adaptee() {} // 被适配类的 默认构造方法初始化 被适配类对象

    // 适配器类中 形式上使用的接口 调用 实际上使用的接口（适配过程）
    void target_func() const override // 形式上使用的接口
    {
        adaptee.adaptee_func(); // 实际上使用的接口
    }

private:
    Adaptee adaptee; // 适配器类 封装 被适配类对象
};

// 客户端
int main()
{
    // 客户端 可以只知道 目标类和适配器类，不知道被适配类
    Target *target = new Adapter(); // 适配器类的 默认构造方法初始化 适配器类对象
    target->target_func();          // 形式上使用的接口
    delete target;

    return 0;
}
/*
输出：
adaptee_func()
*/