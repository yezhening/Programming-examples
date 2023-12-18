#include <iostream>

using std::cout;
using std::endl;

// 抽象原型类
class AbstractPrototype
{
public:
    // 注意：
    // 抽象类不能实例化，不需要显式定义构造方法
    // 如果抽象类的派生类有指针等需要动态内存分配的属性，为了正确释放基类和派生类的资源，派生类需要重写析构方法，基类需要定义虚析构方法
    virtual ~AbstractPrototype() = default;

    virtual AbstractPrototype *clone() const = 0; // 克隆方法
    virtual void func() = 0;
};

// 具体原型类
class ConcretePrototype : public AbstractPrototype
{
public:
    ConcretePrototype(int data) : data(new int(data)) {}
    ~ConcretePrototype() override
    {
        delete this->data;
    }

    // 拷贝构造函数
    // 注意浅拷贝和深拷贝问题

    // 非指针属性：不存在浅拷贝和深拷贝问题
    // 静态内存分配/栈区的指针属性：不存在浅拷贝和深拷贝问题
    // 动态内存分配/堆区的指针属性：存在浅拷贝和深拷贝问题，不应使用浅拷贝，应使用深拷贝

    // 浅拷贝：复制值
    // 深拷贝：创建新对象再复制值

    // unique_ptr<> 可以移动，不可以（浅）拷贝
    // shared_ptr<> 可以（浅/深）拷贝

    // ConcretePrototype(const ConcretePrototype &other) : data(other.data) // 浅拷贝
    // {
    //     cout << "Shallow copy" << endl;
    // }
    ConcretePrototype(const ConcretePrototype &other) : data(new int(*(other.data))) // 深拷贝
    {
        cout << "Deep copy" << endl;
    }

    // 克隆方法创建当前具体原型对象的副本
    AbstractPrototype *clone() const override
    {
        return new ConcretePrototype(*this);
    }

    void func() override
    {
        cout << "ConcretePrototype: " << *(this->data) << endl;
    }

private:
    int *data;
};

// 客户端
int main()
{
    // 创建具体原型对象
    ConcretePrototype *original = new ConcretePrototype(10);
    original->func();

    // 克隆具体原型对象
    AbstractPrototype *clone = original->clone();
    clone->func();

    delete clone;
    delete original;

    return 0;
}
/*
输出：
ConcretePrototype: 10
Deep copy
ConcretePrototype: 10
*/