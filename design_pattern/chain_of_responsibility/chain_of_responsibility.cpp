#include <iostream>

using std::cout;
using std::endl;

// 请求类
class Request
{
public:
    Request(int type) : type(type) {}

    // 获取请求的类型
    int get_type()
    {
        return this->type;
    }

private:
    int type; // 请求的类型
};

// 抽象处理者类
class AbstractHandler
{
public:
    virtual ~AbstractHandler()
    {
        delete this->successor;
    }

    // 设置继任者方法
    void set_successor(AbstractHandler *successor)
    {
        this->successor = successor;
    }

    // 处理请求方法
    virtual void handle_request(Request request)
    {
        if (this->successor != nullptr) // 如果有继任者，继任者 调用 处理请求方法处理请求
        {
            this->successor->handle_request(request);
        }
        else // 如果没有继任者，无法处理请求
        {
            cout << "Request not handled" << endl;
        }
    }

protected:
    // 抽象处理者类 封装 抽象处理者指针（实际上指向一个具体处理者对象，该对象是当前具体处理对象的下一个具体处理对象/下一个处理者/继任者）
    AbstractHandler *successor = nullptr; // 默认没有继任者
};

// 具体处理者1类
// 具体处理者类 重写 处理请求方法
class ConcreteHandler1 : public AbstractHandler
{
public:
    void handle_request(Request request) override
    {
        // 获取并判断请求的类型
        if (request.get_type() == 1) // 如果有权处理请求，当前具体处理对象处理请求
        {
            cout << "ConcreteHandler1 handles the request" << endl;
        }
        else // 如果无权处理请求，调用基类/抽象处理者类的处理请求方法（将请求交给继任者处理）
        {
            AbstractHandler::handle_request(request);
        }
    }
};

// 具体处理者2
class ConcreteHandler2 : public AbstractHandler
{
public:
    void handle_request(Request request) override
    {
        if (request.get_type() == 2)
        {
            cout << "ConcreteHandler2 handles the request" << endl;
        }
        else
        {
            AbstractHandler::handle_request(request);
        }
    }
};

// 客户端
int main()
{
    // 抽象处理者指针（实际上指向一个具体处理者对象）
    AbstractHandler *concrete_handler_1 = new ConcreteHandler1();
    AbstractHandler *concrete_handler_2 = new ConcreteHandler2();

    // 设置处理者链：concrete_handler_1 -> concrete_handler_2
    concrete_handler_1->set_successor(concrete_handler_2);

    // 请求对象
    Request request_1(1); // 1类型的请求
    Request request_2(2);
    Request request_3(3);

    // 处理请求
    concrete_handler_1->handle_request(request_1);
    concrete_handler_1->handle_request(request_2);
    concrete_handler_1->handle_request(request_3);
    // 1类型的请求，具体处理1对象有权处理
    // 2类型的请求，具体处理1对象无权处理，将请求交给继任者处理；具体处理2对象有权处理
    // 3类型的请求，具体处理1对象无权处理，将请求交给继任者处理；具体处理2对象无权处理，没有继任者；无法处理请求

    delete concrete_handler_1; // 递归析构 delete concrete_handler_2

    return 0;
}
/*
输出：
ConcreteHandler1 handles the request
ConcreteHandler2 handles the request
Request not handled
*/