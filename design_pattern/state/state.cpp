#include <iostream>

using std::cout;
using std::endl;

// 抽象状态类
// 抽象状态类 封装 处理方法
class AbstractState
{
public:
    virtual void handle() = 0;
};

// 具体状态1类
// 具体状态类 重写 处理方法
class ConcreteState1 : public AbstractState
{
public:
    void handle() override
    {
        cout << "ConcreteState1" << endl;
    }
};

// 具体状态2类
class ConcreteState2 : public AbstractState
{
public:
    void handle() override
    {
        cout << "ConcreteState2" << endl;
    }
};

// 上下文类
// 上下文类 封装 抽象状态指针（实际上指向一个具体状态对象）
class Context
{
public:
    // 转换状态方法
    void convert_state(AbstractState *next_state)
    {
        delete this->current_state;       // 删除上一个状态即当前状态
        this->current_state = next_state; // 保存下一个状态为当前状态
    }

    // 处理状态方法
    void handle_state() // 形式上 调用 上下文类的 处理状态方法
    {
        this->current_state->handle(); // 实际上 调用 具体状态对象的处理方法
    }

private:
    AbstractState *current_state = nullptr; // 当前状态，默认为空
};

// 客户端
int main()
{
    // 抽象状态指针（实际上指向一个具体状态对象）
    AbstractState *abstract_state_1 = new ConcreteState1();
    AbstractState *abstract_state_2 = new ConcreteState2();

    // 上下文对象
    Context context;

    context.convert_state(abstract_state_1); // 转换状态 nullptr -> abstract_state_1
    context.handle_state();                  // 处理状态

    context.convert_state(abstract_state_2);
    context.handle_state();

    delete abstract_state_2;
    // delete abstract_state_1; 转换状态时隐式析构

    return 0;
}
/*
输出：
ConcreteState1
ConcreteState2
*/