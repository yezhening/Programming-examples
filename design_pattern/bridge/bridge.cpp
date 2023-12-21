#include <iostream>

using std::cout;
using std::endl;

// 抽象实现类
class AbstractImplementation
{
public:
    virtual void impl_func() = 0;
};

// 具体实现类 A
class ConcreteImplementationA : public AbstractImplementation
{
public:
    void impl_func() override
    {
        cout << "ConcreteImplementationA" << endl;

        return;
    }
};

// 具体实现类 B
class ConcreteImplementationB : public AbstractImplementation
{
public:
    void impl_func() override
    {
        cout << "ConcreteImplementationB" << endl;

        return;
    }
};

// 抽象抽象类
// 桥接过程1：抽象抽象类 封装（保护权限） 抽象实现指针（实际上指向一个具体实现对象）
class AbstractAbstraction
{
public:
    AbstractAbstraction(AbstractImplementation *abst_impl) : abst_impl(abst_impl) {}
    ~AbstractAbstraction()
    {
        delete this->abst_impl;
    }

    virtual void abst_func() = 0;

protected:
    AbstractImplementation *abst_impl;
};

// 具体抽象类 A
class ConcreteAbstractionA : public AbstractAbstraction
{
public:
    ConcreteAbstractionA(AbstractImplementation *abst_impl) : AbstractAbstraction(abst_impl) {}

    // 桥接过程2：
    void abst_func() override // 形式上调用 抽象的方法
    {
        cout << "ConcreteAbstractionA" << endl; // 实际上调用 抽象的内容+ 实现的方法
        this->abst_impl->impl_func();           // + 实现的方法

        return;
    }
};

// 具体抽象类 B
class ConcreteAbstractionB : public AbstractAbstraction
{
public:
    ConcreteAbstractionB(AbstractImplementation *abst_impl) : AbstractAbstraction(abst_impl) {}

    void abst_func() override
    {
        cout << "ConcreteAbstractionB" << endl;
        this->abst_impl->impl_func();

        return;
    }
};

// 客户端
int main()
{
    // 具体实现 A 对象
    AbstractImplementation *abst_impl_A = new ConcreteImplementationA();
    // 具体抽象 A 对象
    AbstractAbstraction *abst_abst_A = new ConcreteAbstractionA(abst_impl_A); // 桥接抽象内容 A 和实现内容 A
    abst_abst_A->abst_func();
    delete abst_abst_A; // delete abst_impl_A

    AbstractImplementation *abst_impl_B = new ConcreteImplementationB();
    AbstractAbstraction *abst_abst_B = new ConcreteAbstractionB(abst_impl_B);
    abst_abst_B->abst_func();
    delete abst_abst_B; // delete abst_impl_B

    return 0;
}
/*
输出：
ConcreteAbstractionA
ConcreteImplementationA
ConcreteAbstractionB
ConcreteImplementationB
*/