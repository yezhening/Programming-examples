#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

// 抽象产品类
class AbstractProduct
{
public:
    AbstractProduct() = default;
    virtual ~AbstractProduct() = default;

    virtual void func() = 0;
};

// 具体产品类 A
class ConcreteProductA : public AbstractProduct
{
public:
    ConcreteProductA() = default;
    ~ConcreteProductA() override = default;

    void func() override
    {
        cout << "ConcreteProductA" << endl;
    }
};

// 具体产品类 B
class ConcreteProductB : public AbstractProduct
{
public:
    ConcreteProductB() = default;
    ~ConcreteProductB() override = default;

    void func() override
    {
        cout << "ConcreteProductB" << endl;
    }
};

// 抽象工厂类
class AbstractFactory
{
public:
    AbstractFactory() = default;
    virtual ~AbstractFactory() = default;

    virtual unique_ptr<AbstractProduct> create_concrete_product() const = 0;
};

// 具体工厂类 A
class ConcreteFactoryA : public AbstractFactory
{
public:
    ConcreteFactoryA() = default;
    ~ConcreteFactoryA() override = default;

    inline unique_ptr<AbstractProduct> create_concrete_product() const override
    {
        return make_unique<ConcreteProductA>();
    }
};

// 具体工厂类 B
class ConcreteFactoryB : public AbstractFactory
{
public:
    ConcreteFactoryB() = default;
    ~ConcreteFactoryB() override = default;

    inline unique_ptr<AbstractProduct> create_concrete_product() const override
    {
        return make_unique<ConcreteProductB>();
    }
};

// 客户端
int main()
{
    // 使用工厂方法创建不同类型的具体产品
    unique_ptr<AbstractFactory> concrete_factory_a = make_unique<ConcreteFactoryA>();               // 创建具体工厂对象 A
    unique_ptr<AbstractProduct> concrete_product_a = concrete_factory_a->create_concrete_product(); // 创建具体产品对象 A
    concrete_product_a->func();

    unique_ptr<AbstractFactory> concrete_factory_b = make_unique<ConcreteFactoryB>();               // 创建具体工厂对象 B
    unique_ptr<AbstractProduct> concrete_product_b = concrete_factory_b->create_concrete_product(); // 创建具体产品对象 B
    concrete_product_b->func();

    return 0;
}
/*
输出：
ConcreteProductA
ConcreteProductB
*/