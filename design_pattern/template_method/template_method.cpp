#include <iostream>

using std::cout;
using std::endl;

// 抽象类
class Abstraction
{
public:
    // 抽象类 定义 模板方法
    void template_method() // 形式上 调用 模板方法
    {
        cout << "template_method()" << endl;
        // 实际上 调用 步骤方法。即 哪些 步骤方法 何时 调用（规定组合内容和执行时序） （抽象的模板，不变行为）
        step_func_1();
        step_func_2();
    }

protected:
    // 抽象类 声明 步骤方法（零个或多个）（由派生类重写/实现）
    // 步骤方法1
    virtual void step_func_1() = 0;
    // 步骤方法2
    virtual void step_func_2() = 0;
};

// 具体1类
// 具体类（零个或多个） 重写/实现 步骤方法 （具体的步骤，变化行为）
class Concreteness1 : public Abstraction
{
protected:
    void step_func_1() override
    {
        cout << "Concreteness1 - step_func_1()" << endl;
    }

    void step_func_2() override
    {
        cout << "Concreteness1 - step_func_2()" << endl;
    }
};

// 具体1类
class Concreteness2 : public Abstraction
{
protected:
    void step_func_1() override
    {
        cout << "Concreteness2 - step_func_1()" << endl;
    }

    void step_func_2() override
    {
        cout << "Concreteness2 - step_func_2()" << endl;
    }
};

// 客户端
int main()
{
    // 抽象类指针（实际上指向一个具体类）
    Abstraction *abstraction_1 = new Concreteness1();
    abstraction_1->template_method(); // 抽象类指针（实际上指向一个具体类） 调用 抽象类/父类的模板方法 就是一个方案
    delete abstraction_1;

    cout << endl;

    Abstraction *abstraction_2 = new Concreteness2();
    abstraction_2->template_method();
    delete abstraction_2;

    return 0;
}
/*
输出：
template_method()
Concreteness1 - step_func_1()
Concreteness1 - step_func_2()

template_method()
Concreteness2 - step_func_1()
Concreteness2 - step_func_2()
*/