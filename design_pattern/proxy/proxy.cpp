#include <iostream>

using std::cout;
using std::endl;

// 抽象服务类
class AbstractService
{
public:
    virtual void func() const = 0;
};

// 具体服务类（被代理者）
class ConcreteService : public AbstractService
{
public:
    void func() const override
    {
        cout << "func()" << endl;

        return;
    }
};

// 代理类（代理者）
class Proxy : public AbstractService // 代理类 继承（多态） 抽象服务类，和具体服务类有相同的对外 方法/接口
{

public:
    Proxy() : concrete_service(){}; // 具体服务类的默认构造方法 初始化 具体服务对象

    void func() const override // 代理类 封装/隐藏 具体服务对象，调用代理对象的方法 func()，实际上是 func() 内部调用具体服务对象的方法
    {
        this->concrete_service.func(); // 2. 具体服务对象 调用 方法

        return;
    }

private:
    ConcreteService concrete_service;
};

// 客户端
int main()
{
    Proxy proxy; // 代理类的默认构造方法 初始化 代理对象

    proxy.func(); // 1. 代理对象 调用 方法

    return 0;
}
/*
输出：
func()
*/