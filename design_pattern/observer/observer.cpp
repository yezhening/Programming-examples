#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// 抽象观察者类
class AbstractObserver
{
public:
    // 更新方法
    virtual void update(string message) = 0;
};

// 具体观察者
class ConcreteObserver : public AbstractObserver
{
public:
    ConcreteObserver(string name) : name(name) {}

    // （重写）更新方法
    void update(string message) override
    {
        cout << "Observer " << this->name << " receives message: " << message << endl;
    }

private:
    string name; // 名称
};

// 抽象目标类
class AbstractTarget
{
public:
    virtual ~AbstractTarget()
    {
        for (AbstractObserver *observer : this->observer_vec)
        {
            delete observer;
        }
        this->observer_vec.clear();
    }

    // 添加观察者方法
    void add_observer(AbstractObserver *observer)
    {
        this->observer_vec.push_back(observer);
    }

    // 移除观察者方法
    void remove_observer(AbstractObserver *observer)
    {
        vector<AbstractObserver *>::iterator it = std::remove(this->observer_vec.begin(), this->observer_vec.end(), observer);
        this->observer_vec.erase(it, this->observer_vec.end());
        // 移除的观察者可能还需要，这里不 delete，由客户端构造和析构
    }

    // 通知观察者方法
    void notify_observer(string message)
    {
        for (AbstractObserver *observer : this->observer_vec) // 形式上 调用 具体目标对象的 通知观察者方法
        {
            observer->update(message); // 实际上 调用 具体观察者对象的 更新方法
        }
    }

    // 设置状态方法
    void set_state(string state)
    {
        this->state = state;
        this->notify_observer("State changes to: " + this->state); // 设置状态后，通知观察者
    }

    // 获取状态方法
    // string get_state()
    // {
    //     return this->state;
    // }

private:
    // 抽象观察者指针（实际上指向一个具体观察者对象）的集合属性
    vector<AbstractObserver *> observer_vec;
    string state; // 状态属性
};

// 具体目标类
class ConcreteTarget : public AbstractTarget
{
    // 简单实现，不需要额外内容
};

// 客户端
int main()
{
    // 具体目标类
    ConcreteTarget concrete_target;

    // 具体观察者对象
    AbstractObserver *concrete_observer_1 = new ConcreteObserver("concrete_observer_1");
    AbstractObserver *concrete_observer_2 = new ConcreteObserver("concrete_observer_2");

    // 添加观察者
    concrete_target.add_observer(concrete_observer_1); // 具体观察者对象1 观察 具体目标
    concrete_target.add_observer(concrete_observer_2); // 具体观察者对象2 观察 具体目标

    // 设置状态
    concrete_target.set_state("state1");
    // 观察过程：
    // 目标设置（改变）状态 -> 通知观察者 -> 观察者更新
    // concrete_target.set_state() -> this->notify_observer() -> observer->update()

    // 移除观察者
    concrete_target.remove_observer(concrete_observer_1);
    delete concrete_observer_1;

    // 设置状态
    concrete_target.set_state("state2");

    // 局部变量 concrete_target 销毁，隐式析构 delete concrete_observer_2

    return 0;
}
/*
输出：
Observer concrete_observer_1 receives message: State changes to: state1
Observer concrete_observer_2 receives message: State changes to: state1
Observer concrete_observer_2 receives message: State changes to: state2
*/