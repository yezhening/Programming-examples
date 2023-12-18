#include <iostream>

using std::cout;
using std::endl;

// 抽象产品类 A
class AbstractProductA
{
public:
    virtual void func() = 0;
};

// 具体产品类 A1
class ConcreteProductA1 : public AbstractProductA
{
public:
    void func() override
    {
        cout << "ConcreteProductA1" << endl;
    }
};

// 具体产品类 A2
class ConcreteProductA2 : public AbstractProductA
{
public:
    void func() override
    {
        cout << "ConcreteProductA2" << endl;
    }
};

// 抽象产品类 B
class AbstractProductB
{
public:
    virtual void func() = 0;
};

// 具体产品类 B1
class ConcreteProductB1 : public AbstractProductB
{
public:
    void func() override
    {
        cout << "ConcreteProductB1" << endl;
    }
};

// 具体产品类 B2
class ConcreteProductB2 : public AbstractProductB
{
public:
    void func() override
    {
        cout << "ConcreteProductB2" << endl;
    }
};

// 抽象工厂类
class AbstractFactory
{
public:
    virtual AbstractProductA *create_product_a() const = 0;
    virtual AbstractProductB *create_product_b() const = 0;
};

// 具体工厂类 1
class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *create_product_a() const override
    {
        return new ConcreteProductA1();
    }

    AbstractProductB *create_product_b() const override
    {
        return new ConcreteProductB1();
    }
};

// 具体工厂类 2
class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA *create_product_a() const override
    {
        return new ConcreteProductA2();
    }

    AbstractProductB *create_product_b() const override
    {
        return new ConcreteProductB2();
    }
};

// 客户端
int main()
{
    // 使用抽象工厂创建不同类型的具体产品
    AbstractFactory *concrete_factory_1 = new ConcreteFactory1();                   // 创建具体工厂对象1
    AbstractProductA *concrete_product_a1 = concrete_factory_1->create_product_a(); // 创建具体产品对象 A1
    AbstractProductB *concrete_product_b1 = concrete_factory_1->create_product_b(); // 创建具体产品对象 B1
    concrete_product_a1->func();
    concrete_product_b1->func();
    delete concrete_product_b1;
    delete concrete_product_a1;
    delete concrete_factory_1;

    AbstractFactory *concrete_factory_2 = new ConcreteFactory2();                   // 创建具体工厂2
    AbstractProductA *concrete_product_a2 = concrete_factory_2->create_product_a(); // 创建具体产品对象 B1
    AbstractProductB *concrete_product_b2 = concrete_factory_2->create_product_b(); // 创建具体产品对象 B1
    concrete_product_a2->func();
    concrete_product_b2->func();
    delete concrete_product_b2;
    delete concrete_product_a2;
    delete concrete_factory_2;

    return 0;
}
/*
输出：
ConcreteProductA1
ConcreteProductB1
ConcreteProductA2
ConcreteProductB2
*/