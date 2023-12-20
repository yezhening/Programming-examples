#include <iostream>

using std::cout;
using std::endl;

// 子系统类（多个）（被管理者）
// 子系统 A 类
class SubsystemA
{
public:
    void func_A()
    {
        cout << "func_A()" << endl;
    }
};

// 子系统 B 类
class SubsystemB
{
public:
    void func_B()
    {
        cout << "func_B()" << endl;
    }
};

// 外观类（管理者）
class Facade
{
public:
    Facade() : subsystem_A(), subsystem_B() {} // 子系统类的 默认构造方法初始化 子系统对象

    // 外观类的方案方法 调用子系统对象的方法 搭配成不同方案（不同对象、方法（内容）和时序/步骤等）
    // 方案1
    void option1()
    {
        subsystem_A.func_A();
        subsystem_B.func_B();
    }

    // 方案2
    void option2()
    {
        subsystem_B.func_B();
        subsystem_A.func_A();
    }

    // 方案n...

private:
    // 外观类 封装 子系统对象
    SubsystemA subsystem_A;
    SubsystemB subsystem_B;
};

// 客户端
int main()
{
    // 客户端只知道外观类，不知道子系统类
    Facade facade;

    facade.option1(); // 使用方案1
    facade.option2(); // 使用方案2

    return 0;
}
/*
输出：
func_A()
func_B()
func_B()
func_A()
*/