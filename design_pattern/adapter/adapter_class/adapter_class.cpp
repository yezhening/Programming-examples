#include <iostream>

using std::cout;
using std::endl;

// 被适配类（客户端 不兼容/无法使用/实际上使用 的接口；被适配者）
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
// 适配器类 多继承 被适配类和目标类;
// 适配器类 私有继承（封装） 被适配类
class Adapter : public Target, private Adaptee
{
public:
    // 适配器类中 形式上使用的接口 调用 实际上使用的接口（适配过程）
    void target_func() const override // 形式上使用的接口
    {
        Adaptee::adaptee_func(); // 实际上使用的接口

        return;
    }
};

// 客户端
int main()
{
    // 客户端 可以只知道 目标类和适配器类，不知道被适配类
    Target *target = new Adapter();
    target->target_func(); // 形式上使用的接口
    delete target;

    return 0;
}
/*
输出：
adaptee_func()
*/