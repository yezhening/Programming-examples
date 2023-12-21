#include <iostream>
#include <unordered_map>

using std::cout;
using std::endl;
using std::pair;
using std::unordered_map;

// 抽象享元类
class AbstractFlyweight
{
public:
    virtual void func(int external_state) = 0;
    // 外部状态（不需要共享的内容）：对象的可变状态，不可以被多个对象共享，取决于外部环境，需要时作为参数传递给具体享元/具体不共享对象
};

// 具体享元类（需要共享的内容）
// 具体享元类 有内部状态，可以 有外部状态
class ConcreteFlyweight : public AbstractFlyweight
{
public:
    ConcreteFlyweight(int internal_state) : internal_state(internal_state) {}

    void func(int external_state) override
    {
        cout << "external_state: " << external_state << endl;
        cout << "internal_state: " << this->internal_state << endl;
    }

private:
    int internal_state;
    // 内部状态（需要共享的内容）：对象的不变状态，可以被多个对象共享，不取决于外部环境，通常存储在具体享元对象内部
};

// 具体不共享类（不需要共享的内容）
// 具体不共享类 没有内部状态，有外部状态
class ConcreteUnshared : public AbstractFlyweight
{
public:
    void func(int external_state) override
    {
        cout << "external_state: " << external_state << endl;
    }
};

// 享元工厂
class FlyweightFactory
{
public:
    // 统一析构
    ~FlyweightFactory()
    {
        for (pair<int, AbstractFlyweight *> p : this->flyweight_unmap)
        {
            delete p.second;
        }
    }

    // 享元工厂 获取抽象享元指针（实际上指向一个具体享元对象）
    AbstractFlyweight *
    get_concrete_flyweight(int key)
    {
        // 若不存在创建
        if (this->flyweight_unmap.find(key) == this->flyweight_unmap.end())
        {
            this->flyweight_unmap[key] = new ConcreteFlyweight(key);
        }

        // 若存在返回
        return this->flyweight_unmap[key];
    }

    // 享元工厂 获取抽象享元指针（实际上指向一个具体不共享对象）
    AbstractFlyweight *get_concrete_unshared()
    {
        return new ConcreteUnshared();
    }

private:
    unordered_map<int, AbstractFlyweight *> flyweight_unmap;
    // 享元工厂 封装 享元集合（实际上 封装 具体享元对象）
    // 具体享元对象是共享的，具有共性，可以用工厂/集合统一管理
    // 具体不共享对象是不共享的，不具有共性，一般不统一管理，需要时再创建
};

// 客户端
int main()
{
    // 享元工厂对象
    FlyweightFactory flyweight_factory;

    // 抽象享元指针（实际上指向具体享元对象）
    AbstractFlyweight *concrete_flyweight_1 = flyweight_factory.get_concrete_flyweight(10); // 设置内部状态
    concrete_flyweight_1->func(100);                                                        // 传递外部状态

    AbstractFlyweight *concrete_flyweight_2 = flyweight_factory.get_concrete_flyweight(10); // 获取同一个具体享元对象，共享的体现
    concrete_flyweight_2->func(200);                                                        // 不共享的体现

    // 抽象享元指针（实际上指向具体不共享对象）
    AbstractFlyweight *concrete_unshared = flyweight_factory.get_concrete_unshared();
    concrete_unshared->func(300); // 传递外部状态；不共享的体现

    delete concrete_unshared; // 显式析构具体不共享对象
    // 析构享元工厂对象时 隐式析构享元对象

    return 0;
}
/*
输出：
external_state: 100
internal_state: 10
external_state: 200
internal_state: 10
external_state: 300
*/