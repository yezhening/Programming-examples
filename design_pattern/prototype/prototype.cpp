#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

// 抽象原型类
class AbstractPrototype
{
public:
    AbstractPrototype() = default;
    virtual ~AbstractPrototype() = default;

    virtual inline unique_ptr<AbstractPrototype> clone() const = 0; // 克隆方法

    virtual void func() = 0;
};

// 具体原型类
class ConcretePrototype : public AbstractPrototype
{

public:
    ConcretePrototype(int data) : data(make_unique<int>(data)) {}
    ~ConcretePrototype() override = default;

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
    ConcretePrototype(const ConcretePrototype &other) : data(make_unique<int>(*(other.data))) // 深拷贝
    {
        cout << "Deep copy" << endl;
    }

    // 克隆方法创建当前具体原型对象的副本
    inline unique_ptr<AbstractPrototype> clone() const override
    {
        return make_unique<ConcretePrototype>(*this); // 调用拷贝构造函数（类比：ConcretePrototype clone(*this)）
    }

    void func() override
    {
        cout << "ConcretePrototype: " << *this->data << endl;
    }

private:
    unique_ptr<int> data;
};

// 客户端
int main()
{
    // 创建具体原型对象
    unique_ptr<ConcretePrototype> original = make_unique<ConcretePrototype>(10);
    original->func();

    // 克隆具体原型对象
    unique_ptr<AbstractPrototype> clone = original->clone();
    clone->func();

    return 0;
}
/*
输出：
ConcretePrototype: 10
Deep copy
ConcretePrototype: 10
*/