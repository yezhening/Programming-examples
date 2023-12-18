#include <iostream>

using std::cout;
using std::endl;

// 抽象产品类
class AbstractProduct
{
public:
    virtual void func() = 0;
};

// 具体产品类 A
class ConcreteProductA : public AbstractProduct
{
public:
    void func() override
    {
        cout << "ConcreteProductA" << endl;
    }
};

// 具体产品类 B
class ConcreteProductB : public AbstractProduct
{
public:
    void func() override
    {
        cout << "ConcreteProductB" << endl;
    }
};

// 抽象工厂类
class AbstractFactory
{
public:
    virtual AbstractProduct *create_concrete_product() const = 0;
};

// 具体工厂类 A
class ConcreteFactoryA : public AbstractFactory
{
public:
    AbstractProduct *create_concrete_product() const override
    {
        return new ConcreteProductA();
    }
};

// 具体工厂类 B
class ConcreteFactoryB : public AbstractFactory
{
public:
    AbstractProduct *create_concrete_product() const override
    {
        return new ConcreteProductB();
    }
};

// 客户端
int main()
{
    // 使用工厂方法创建不同类型的具体产品
    AbstractFactory *concrete_factory_a = new ConcreteFactoryA();                        // 创建具体工厂对象 A
    AbstractProduct *concrete_product_a = concrete_factory_a->create_concrete_product(); // 创建具体产品对象 A
    concrete_product_a->func();
    delete concrete_product_a;
    delete concrete_factory_a;

    AbstractFactory *concrete_factory_b = new ConcreteFactoryB();                        // 创建具体工厂对象 B
    AbstractProduct *concrete_product_b = concrete_factory_b->create_concrete_product(); // 创建具体产品对象 B
    concrete_product_b->func();
    delete concrete_product_b;
    delete concrete_factory_b;

    return 0;
}
/*
输出：
ConcreteProductA
ConcreteProductB
*/