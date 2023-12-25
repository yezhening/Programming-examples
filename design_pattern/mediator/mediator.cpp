#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// 注意 类的定义顺序
// 前置声明
class AbstractMediator;

// 抽象同事类
class AbstractColleague
{
public:
    AbstractColleague(AbstractMediator *mediator) : mediator(mediator) {}

    // 发送消息
    virtual void send_message(string message) = 0;
    // 接收消息
    virtual void recv_message(string message) = 0;

protected:
    // 抽象中介者指针（实际上指向一个具体中介者对象）（同事 需要认识 中介者）
    AbstractMediator *mediator;
};

// 抽象中介者类
class AbstractMediator
{
public:
    // 转发消息
    virtual void forward_message(string message, AbstractColleague *colleague) = 0;
};

// 具体中介者类（协调交互 的对象）
class ConcreteMediator : public AbstractMediator
{
public:
    // 设置同事
    void set_colleague_A(AbstractColleague *colleague)
    {
        this->colleague_A = colleague;
    }

    void set_colleague_B(AbstractColleague *colleague)
    {
        this->colleague_B = colleague;
    }

    // 转发消息
    void forward_message(string message, AbstractColleague *colleague) override // 形式上 调用 具体中介者类的 转发消息方法
    {
        if (colleague == this->colleague_A)
        {
            this->colleague_B->recv_message(message); // 实际上 调用 具体同事类的 接收消息方法（中介者 转发消息，同事 接收消息）
        }
        else if (colleague == this->colleague_B) // 发送者 是 同事B
        {
            this->colleague_A->recv_message(message); // 接收者 是 同事A
        }
    }

private:
    // 抽象同事指针（实际上指向一个具体同事对象）（中介者 需要认识 同事）
    AbstractColleague *colleague_A;
    AbstractColleague *colleague_B;
};

// 具体同事A类（需要交互 的对象）
class ConcreteColleagueA : public AbstractColleague
{
public:
    ConcreteColleagueA(AbstractMediator *mediator) : AbstractColleague(mediator) {}

    // 发送消息
    void send_message(string message) override // 形式上 调用 具体同事A类的 发送消息方法
    {
        cout << "Colleague A sends message: " << message << endl;

        mediator->forward_message(message, this); // 实际上 调用 具体中介者类的 转发消息方法（当前同事 发送消息，委托 中介者 转发消息）。发送者 是 同事A（this）
    }

    // 接收消息
    void recv_message(string message) override
    {
        std::cout << "Colleague A receives message: " << message << std::endl;
    }
};

// 具体同事类B
class ConcreteColleagueB : public AbstractColleague
{
public:
    ConcreteColleagueB(AbstractMediator *mediator) : AbstractColleague(mediator) {}

    void send_message(string message) override
    {
        cout << "Colleague B sends message: " << message << endl;

        mediator->forward_message(message, this);
    }

    void recv_message(string message) override
    {
        cout << "Colleague B receives message: " << message << endl;
    }
};

// 客户端
int main()
{
    // 具体中介者指针（实际上指向一个具体中介者对象）
    ConcreteMediator *mediator = new ConcreteMediator();
    // 具体同事指针（实际上指向一个具体同事对象）（同事 需要认识 中介者）
    ConcreteColleagueA *colleague_A = new ConcreteColleagueA(mediator);
    ConcreteColleagueB *colleague_B = new ConcreteColleagueB(mediator);

    // 设置中介者的同事对象（中介者 需要认识同事）
    mediator->set_colleague_A(colleague_A);
    mediator->set_colleague_B(colleague_B);

    // 同事对象间 委托中介者 交互
    colleague_A->send_message("Hello from Colleague A");
    colleague_B->send_message("Hi from Colleague B");

    delete colleague_B;
    delete colleague_A;
    delete mediator;

    return 0;
}
/*
输出：
Colleague A sends message: Hello from Colleague A
Colleague B receives message: Hello from Colleague A
Colleague B sends message: Hi from Colleague B
Colleague A receives message: Hi from Colleague B
*/