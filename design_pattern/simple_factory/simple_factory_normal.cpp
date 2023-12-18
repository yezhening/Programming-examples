#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

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

// 简单工厂类
class SimpleFactory
{
public:
    // 静态方法依据类型创建不同的具体产品
    static AbstractProduct *create_concrete_product(const string &concrete_product_type)
    {
        if (concrete_product_type == "A")
        {
            return new ConcreteProductA();
        }
        else if (concrete_product_type == "B")
        {
            return new ConcreteProductB();
        }
        else
        {
            cerr << "Unknown type of concrete product" << endl;

            return nullptr;
        }
    }
};

// 客户端
int main()
{
    // 使用简单工厂创建不同类型的具体产品
    AbstractProduct *concrete_product_a = SimpleFactory::create_concrete_product("A"); // 创建具体产品对象 A
    if (concrete_product_a != nullptr)
    {
        concrete_product_a->func();

        delete concrete_product_a;
    }

    AbstractProduct *concrete_product_b = SimpleFactory::create_concrete_product("B"); // 创建具体产品对象 B
    if (concrete_product_b != nullptr)
    {
        concrete_product_b->func();

        delete concrete_product_b;
    }

    AbstractProduct *concrete_product_c = SimpleFactory::create_concrete_product("C"); // 创建具体产品对象 C
    if (concrete_product_c != nullptr)
    {
        concrete_product_c->func();

        delete concrete_product_c;
    }

    return 0;
}
/*
输出：
ConcreteProductA
ConcreteProductB
Unknown type of concrete product
*/