#include <iostream>

using std::cout;
using std::endl;

// 抽象策略类
class AbstractStrategy
{
public:
    virtual void execute() = 0;
};

// 具体策略1类
class ConcreteStrategy1 : public AbstractStrategy
{
public:
    void execute() override
    {
        cout << "ConcreteStrategy1" << endl;
    }
};

// 具体策略2类
class ConcreteStrategy2 : public AbstractStrategy
{
public:
    void execute() override
    {
        cout << "ConcreteStrategy2" << endl;
    }
};

// 上下文类
// 上下文类 封装 抽象策略指针（实际上指向一个具体策略对象）
class Context
{
public:
    Context(AbstractStrategy *strategy) : strategy(strategy) {}

    // 设置策略方法
    void set_strategy(AbstractStrategy *strategy)
    {
        this->strategy = strategy;
    }

    // 执行策略方法
    void execute_strategy() // 形式上调用 上下文对象的 执行策略方法
    {
        this->strategy->execute(); // 实际上调用 具体策略对象的 执行方法
    }

private:
    AbstractStrategy *strategy;
};

// 客户端
int main()
{
    // 具体策略对象
    ConcreteStrategy1 concrete_strategy_1;
    ConcreteStrategy2 concrete_strategy_2;

    // 上下文对象
    Context context(&concrete_strategy_1); // 设置策略
    context.execute_strategy();            // 执行策略

    context.set_strategy(&concrete_strategy_2); // 设置策略
    context.execute_strategy();

    return 0;
}
/*
输出：
ConcreteStrategy1
ConcreteStrategy2
*/