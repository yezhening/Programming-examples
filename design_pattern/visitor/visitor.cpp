#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// 注意 类的定义顺序
// 前置声明
class ConcreteElementA;
class ConcreteElementB;

// 抽象访问者类
class AbstractVisitor
{
public:
    // 访问
    virtual void visit_element_A(ConcreteElementA *element) = 0; // 接收参数是具体元素指针
    virtual void visit_element_B(ConcreteElementB *element) = 0;
};

// 抽象元素类
class AbstractElement
{
public:
    // 接收
    virtual void accept(AbstractVisitor *visitor) = 0; // 接收参数是抽象访问者指针
};

// 具体元素 A 类
class ConcreteElementA : public AbstractElement
{
public:
    // 接收
    void accept(AbstractVisitor *visitor) override // 形式上 调用 具体元素类的 接收方法
    {
        visitor->visit_element_A(this);
        // 实际上 调用 具体访问者类的 访问方法
        // 发送参数是 this，表示 允许 访问者 访问 自身
    }

    // 操作
    void operation_A()
    {
        cout << "ConcreteElementA operation" << endl;
    }
};

// 具体元素B类
class ConcreteElementB : public AbstractElement
{
public:
    void accept(AbstractVisitor *visitor) override
    {
        visitor->visit_element_B(this);
    }

    void operation_B()
    {
        cout << "ConcreteElementB operation" << endl;
    }
};

// 具体访问者类
class ConcreteVisitor : public AbstractVisitor
{
public:
    // 访问
    void visit_element_A(ConcreteElementA *element) override // 形式上 调用 具体访问者类的 访问方法
    {
        cout << "ConcreteVisitor visits ConcreteElementA" << endl;

        element->operation_A(); // 实际上 调用 具体元素类的 操作方法
    }

    void visit_element_B(ConcreteElementB *element) override
    {
        cout << "ConcreteVisitor ConcreteElementB" << endl;

        element->operation_B();
    }
};

// 当需要添加新的操作时，只需要创建新的访问者类并实现相应的方法，而不需要修改现有的元素类
// 具体访问者新类
class ConcreteVisitorNew : public AbstractVisitor
{
public:
    // 访问
    // 新的操作
    void visit_element_A(ConcreteElementA *element) override
    {
        cout << "ConcreteVisitorNew visits ConcreteElementA" << endl;

        element->operation_A();
    }

    void visit_element_B(ConcreteElementB *element) override
    {
        cout << "ConcreteVisitorNew ConcreteElementB" << endl;

        element->operation_B();
    }
};

// 对象结构类
class ObjectStructure
{
public:
    // 添加元素
    void add_element(AbstractElement *element)
    {
        this->element_vec.push_back(element);
    }

    // 移除元素

    // 接收
    void accept(AbstractVisitor *visitor) // 形式上 调用 对象结构类的 接收方法
    {
        for (AbstractElement *element : this->element_vec)
        {
            element->accept(visitor); // 实际上 调用 具体元素类的 接收方法
        }
    }

private:
    // 抽象元素指针（实际上指向一个具体元素对象）的集合
    vector<AbstractElement *> element_vec;
};

// 客户端
int main()
{
    // 具体元素对象
    ConcreteElementA element_A;
    ConcreteElementB element_B;

    // 对象结构对象
    ObjectStructure object_structure;
    object_structure.add_element(&element_A); // 对象结构 添加元素
    object_structure.add_element(&element_B);

    // 具体访问者对象
    ConcreteVisitor visitor;
    object_structure.accept(&visitor); // 对象结构 接收 访问者的访问
    // 访问过程：
    // object_structure.accept(&visitor); ->
    // 对象结构类的 接收方法，发送参数是 访问者对象（对象结构 需要 访问者访问）
    // element->accept(visitor); ->
    // 具体元素类的 接收方法，发送参数是 访问者对象（元素 需要 访问者访问）
    // visitor->visit_element_A(this);
    // 具体访问者类的 访问方法，发送参数是 具体元素对象（元素 允许 访问者访问）
    // element->operation_A();
    // 具体访问者类的 操作方法（访问者 访问 元素）

    // 具体访问者新对象
    ConcreteVisitorNew visitor_new;
    object_structure.accept(&visitor_new);

    return 0;
}
/*
输出：
ConcreteVisitor visits ConcreteElementA
ConcreteElementA operation
ConcreteVisitor ConcreteElementB
ConcreteElementB operation
ConcreteVisitorNew visits ConcreteElementA
ConcreteElementA operation
ConcreteVisitorNew ConcreteElementB
ConcreteElementB operation
*/