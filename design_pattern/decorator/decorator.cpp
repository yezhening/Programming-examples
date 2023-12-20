#include <iostream>

using std::cout;
using std::endl;

// 抽象组件类
class AbstractComponent
{
public:
    virtual ~AbstractComponent() = default;

    virtual void func() = 0;
};

// 具体组件类（被装饰者）
class ConcreteComponent : public AbstractComponent
{
public:
    void func() override
    {
        cout << "component" << endl;
    }
};

// 抽象装饰类
// 抽象装饰类 继承 抽象组件类
class AbstractDecorator : public AbstractComponent
{
public:
    // 注意浅拷贝和深拷贝问题：相同组件不同组件，需要浅拷贝
    AbstractDecorator(AbstractComponent *abstract_component) : abstract_component(abstract_component) {}
    virtual ~AbstractDecorator() override
    {
        delete this->abstract_component;
    }

    // 抽象装饰类 重写 抽象组件类的方法
    // 形式上 调用 装饰类的方法
    // 实际上 调用 抽象组件指针/具体组件对象的方法（原本内容） + 装饰类的额外内容（装饰内容）（重点理解）
    void func() override
    {
        if (this->abstract_component != nullptr)
        {
            this->abstract_component->func();
        }
    }

private:
    // 抽象装饰类 封装 抽象组件指针（实际上会指向一个具体组件对象）（装饰者包装被装饰者）
    AbstractComponent *abstract_component;
};

// 具体装饰 A 类
class ConcreteDecoratorA : public AbstractDecorator
{
public:
    ConcreteDecoratorA(AbstractComponent *abstract_component) : AbstractDecorator(abstract_component) {}

    // 具体装饰类 重写 抽象组件类的方法
    void func() override // 形式上 调用 装饰类的方法
    {
        AbstractDecorator::func();            // 实际上 调用 抽象组件指针/具体组件对象的方法（原本内容）
        cout << "ConcreteDecoratorA" << endl; // + 装饰类的额外内容（装饰内容）（重点理解）
    }
};

// 具体装饰 B 类
class ConcreteDecoratorB : public AbstractDecorator
{
public:
    ConcreteDecoratorB(AbstractComponent *abstract_component) : AbstractDecorator(abstract_component) {}

    // 具体装饰类 重写 抽象组件类的方法
    void func() override // 形式上 调用 装饰类的方法
    {
        AbstractDecorator::func();            // 实际上 调用 抽象组件指针/具体组件对象的方法（原本内容）
        cout << "ConcreteDecoratorB" << endl; // + 装饰类的额外内容（装饰内容）（重点理解）
    }
};

// 客户端
int main()
{
    // 注意同一组件不同装饰的重复析构问题
    // AbstractComponent *abstract_component = new ConcreteComponent(); // 抽象组件指针/具体组件对象

    // // 抽象组件指针/具体装饰 A 对象装饰组件
    // AbstractComponent *concrete_decorator_A = new ConcreteDecoratorA(abstract_component);
    // concrete_decorator_A->func(); // 形式上 调用 装饰类的方法

    // AbstractComponent *concrete_decorator_B = new ConcreteDecoratorB(abstract_component);
    // concrete_decorator_B->func();

    // delete concrete_decorator_B; // 第一次 delete abstract_component
    // delete concrete_decorator_A; // 第二次 delete abstract_component
    // delete abstract_component;   // 第三次 delete abstract_component

    // 解决1：使用智能指针，shared_ptr<>
    // 解决2：手动实现引用计数机制
    // 解决3：程序结束自动释放全部
    // 解决4：使用相同组件的不同副本
    // 解决5：使用不同组件
    // 解决n...
    // 使用解决5
    AbstractComponent *abstract_component_a = new ConcreteComponent(); // 抽象组件指针/具体组件对象
    // 抽象组件指针/具体装饰 A 对象装饰组件
    AbstractComponent *concrete_decorator_A = new ConcreteDecoratorA(abstract_component_a);
    concrete_decorator_A->func(); // 形式上 调用 装饰类的方法
    delete concrete_decorator_A;  // 第一次 delete abstract_component
    // delete abstract_component_a;  // 第二次 delete abstract_component

    AbstractComponent *abstract_component_b = new ConcreteComponent();
    AbstractComponent *concrete_decorator_B = new ConcreteDecoratorB(abstract_component_b);
    concrete_decorator_B->func();
    delete concrete_decorator_B;

    return 0;
}