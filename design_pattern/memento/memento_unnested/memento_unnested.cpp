#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// 备忘录类（保存 发起者对象 的状态）
// 备忘录类 封装 状态属性，保存状态方法，获取状态方法
class Memento
{
public:
    Memento(string state) : state(state) {} // 保存状态

    // 设置状态

    // 获取状态
    string get_state()
    {
        return this->state;
    }

private:
    string state; // 状态
};

// 发起者类（需要保存和恢复状态 的对象）
// 发起者类 封装 状态属性，设置状态方法，创建备忘录（保存状态）方法（将状态交给备忘录保存），恢复备忘录（恢复状态）方法（从备忘录获取/恢复状态）
class Initiator
{
public:
    // 设置状态
    void set_state(string state)
    {
        this->state = state;
        cout << "Current state: " << this->state << endl;
    }

    // 获取状态

    // 创建备忘录（保存状态）
    Memento create_memento()
    {
        return Memento(this->state); // 将状态交给备忘录保存
    }

    // 恢复备忘录（恢复状态）
    void restore_memento(Memento memento)
    {
        this->state = memento.get_state(); // 从备忘录获取/恢复状态
        cout << "State restores to: " << this->state << endl;
    }

private:
    string state; // 状态
};

// 管理者类（管理备忘录对象）
// 管理者类 封装 添加备忘录方法，获取备忘录方法
class Administrator
{
public:
    // 添加备忘录
    void add_memento(Memento memento)
    {
        this->memento_vec.push_back(memento);
    }

    // 获取备忘录
    const Memento get_memento(int index)
    {
        return this->memento_vec.at(index);
    }

private:
    vector<Memento> memento_vec;
};

// 客户端
int main()
{
    // 发起者对象
    Initiator initiator;
    // 管理者对象
    Administrator administrator;

    initiator.set_state("State 1"); // 设置状态
    // 备忘录对象
    Memento memento_1 = initiator.create_memento(); // 1. 创建备忘录（保存状态）
    administrator.add_memento(memento_1);           // 2. 添加备忘录

    initiator.set_state("State 2");                   // 设置状态
    Memento memento_2 = administrator.get_memento(0); // 3. 获取备忘录
    initiator.restore_memento(memento_2);             // 4. 恢复备忘录（恢复状态）
    // 备忘录过程：
    // 发起者 调用 创建备忘录（保存状态）方法 -> 管理者 调用 添加备忘录方法
    // 管理者 调用 获取备忘录方法 -> 发起者 调用 恢复备忘录（恢复状态）方法

    return 0;
}
/*
输出：
Current state: State 1
Current state: State 2
State restores to: State 1
*/