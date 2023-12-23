#include <iostream>

using std::cout;
using std::endl;

// 接收者类
// 接收者类 封装 行为方法
class Receiver
{
public:
    void action()
    {
        cout << "Receiver" << endl;
    }
};

// 抽象命令类
// 抽象命令类 封装 执行方法
class AbstractCommand
{
public:
    virtual void execute() = 0;
};

// 具体命令类
// 具体命令类 重写 执行方法
// 具体命令类 封装 接收者对象
class ConcreteCommand : public AbstractCommand
{
public:
    ConcreteCommand() : receiver() {} // 接收者类的默认构造方法 初始化 接收者对象

    virtual void execute() override // 形式上 调用 具体命令对象的执行方法
    {
        receiver.action(); // 实际上 调用 接收者对象的行为方法
    }

private:
    Receiver receiver;
    // 如果在 抽象命令类 封装 接收者对象，接收者类型一致
    // 如果在 具体命令类 封装 接收者对象，接收者类型可以不同
};

// 发送者类
class Sender
{
public:
    // 设置命令方法
    void set_command(AbstractCommand *abstract_command)
    {
        this->abstract_command = abstract_command;
    }

    // 执行命令方法
    void execute_command() // 形式上 调用 发送者对象的执行命令方法
    {
        this->abstract_command->execute(); // 实际上 调用 具体命令对象的执行方法
    }

private:
    // 封装 抽象命令指针（实际上指向一个具体命令对象）
    AbstractCommand *abstract_command;
};

// 客户端
int main()
{
    // 抽象命令指针（实际上指向一个具体命令对象）
    AbstractCommand *abstract_command = new ConcreteCommand();

    // 发送者对象
    Sender sender;
    sender.set_command(abstract_command); // 设置命令
    sender.execute_command();             // 执行命令
    // 命令执行过程：发送者 调用 执行命令方法 -> 命令 调用 执行方法 -> 接收者 调用 行为方法
    // ender.execute_command() -> this->abstract_command->execute() -> receiver.action()

    delete abstract_command;

    return 0;
}
/*
输出：
Receiver
*/