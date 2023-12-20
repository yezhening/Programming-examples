// 安全方式：组件类没有管理子对象的方法，树枝类有管理子对象的方法
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// 组件类
class Component
{
public:
    virtual ~Component() {}

    virtual void func() = 0;
};

// 树叶类（树的叶节点）
// 树叶类 继承 组件类，重写 虚方法
class Leaf : public Component
{
public:
    Leaf(int value) : value(value) {}

    void func() override
    {
        cout << "Leaf: " << this->value << endl;

        return;
    }

private:
    int value;
};

// 树枝类（树的非叶节点）
// 树枝类 继承 组件类，封装 组件类的集合（实际上包含零个或多个树叶对象或树枝对象），重写 虚方法
class Branch : public Component
{
public:
    Branch() : component_vec() {} // vector<> 的 默认构造方法初始化 属性
    ~Branch()
    {
        for (Component *component : this->component_vec)
        {
            delete component;
        }
    }

    void add(Component *component)
    {
        this->component_vec.push_back(component);
    }

    void func() override
    {
        cout << "Branch: " << endl;
        for (Component *component : this->component_vec)
        {
            component->func();
        }
    }

private:
    vector<Component *> component_vec;
};

// 客户端

int main()
{
    // 树叶
    Leaf *leaf_1 = new Leaf(10);
    Leaf *leaf_2 = new Leaf(20);
    Leaf *leaf_3 = new Leaf(30);

    // 树枝
    Branch *branch_1 = new Branch();
    branch_1->add(leaf_1);
    branch_1->add(leaf_2);

    // 树枝/根
    Branch *branch_2 = new Branch();
    branch_2->add(leaf_3);
    branch_2->add(branch_1);

    // 客户端 以相同的方式处理/一致地使用 简单和复杂元素/单个和组合对象
    leaf_2->func();
    cout << endl;
    branch_2->func();

    delete branch_2; // 会自动递归 delete branch_1、leaf_2、leaf_1 和 leaf_3

    return 0;
}
/*
Leaf: 20

Branch:
Leaf: 30
Branch:
Leaf: 10
Leaf: 20
*/