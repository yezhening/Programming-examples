#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

// 抽象产品类 A
class AbstractProductA
{
public:
    AbstractProductA() = default;
    virtual ~AbstractProductA() = default;

    virtual void func() = 0;
};

// 具体产品类 A1
class ConcreteProductA1 : public AbstractProductA
{
public:
    ConcreteProductA1() = default;
    ~ConcreteProductA1() override = default;

    void func() override
    {
        cout << "ConcreteProductA1" << endl;
    }
};

// 具体产品类 A2
class ConcreteProductA2 : public AbstractProductA
{
public:
    ConcreteProductA2() = default;
    ~ConcreteProductA2() override = default;

    void func() override
    {
        cout << "ConcreteProductA2" << endl;
    }
};

// 抽象产品类 B
class AbstractProductB
{
public:
    AbstractProductB() = default;
    virtual ~AbstractProductB() = default;

    virtual void func() = 0;
};

// 具体产品类 B1
class ConcreteProductB1 : public AbstractProductB
{
public:
    ConcreteProductB1() = default;
    ~ConcreteProductB1() override = default;

    void func() override
    {
        cout << "ConcreteProductB1" << endl;
    }
};

// 具体产品类 B2
class ConcreteProductB2 : public AbstractProductB
{
public:
    ConcreteProductB2() = default;
    ~ConcreteProductB2() override = default;

    void func() override
    {
        cout << "ConcreteProductB2" << endl;
    }
};

// 抽象工厂类
class AbstractFactory
{
public:
    AbstractFactory() = default;
    virtual ~AbstractFactory() = default;

    virtual unique_ptr<AbstractProductA> create_product_a() const = 0;
    virtual unique_ptr<AbstractProductB> create_product_b() const = 0;
};

// 具体工厂类 1
class ConcreteFactory1 : public AbstractFactory
{
public:
    ConcreteFactory1() = default;
    virtual ~ConcreteFactory1() = default;

    inline unique_ptr<AbstractProductA> create_product_a() const override
    {
        return make_unique<ConcreteProductA1>();
    }

    inline unique_ptr<AbstractProductB> create_product_b() const override
    {
        return make_unique<ConcreteProductB1>();
    }
};

// 具体工厂类 2
class ConcreteFactory2 : public AbstractFactory
{
public:
    ConcreteFactory2() = default;
    virtual ~ConcreteFactory2() = default;

    inline unique_ptr<AbstractProductA> create_product_a() const override
    {
        return make_unique<ConcreteProductA2>();
    }

    inline unique_ptr<AbstractProductB> create_product_b() const override
    {
        return make_unique<ConcreteProductB2>();
    }
};

// 客户端
int main()
{
    // 使用抽象工厂创建不同类型的具体产品
    unique_ptr<AbstractFactory> concrete_factory_1 = make_unique<ConcreteFactory1>();          // 创建具体工厂对象1
    unique_ptr<AbstractProductA> concrete_product_a1 = concrete_factory_1->create_product_a(); // 创建具体产品对象 A1
    unique_ptr<AbstractProductB> concrete_product_b1 = concrete_factory_1->create_product_b(); // 创建具体产品对象 B1
    concrete_product_a1->func();
    concrete_product_b1->func();

    unique_ptr<AbstractFactory> concrete_factory_2 = make_unique<ConcreteFactory2>();          // 创建具体工厂2
    unique_ptr<AbstractProductA> concrete_product_a2 = concrete_factory_2->create_product_a(); // 创建具体产品对象 B1
    unique_ptr<AbstractProductB> concrete_product_b2 = concrete_factory_2->create_product_b(); // 创建具体产品对象 B1
    concrete_product_a2->func();
    concrete_product_b2->func();

    return 0;
}
/*
输出：
ConcreteProductA1
ConcreteProductB1
ConcreteProductA2
ConcreteProductB2
*/