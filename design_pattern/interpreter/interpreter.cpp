#include <unordered_map>
#include <iostream>

using std::cout;
using std::endl;
using std::unordered_map;

// 抽象表达式类
class AbstractExpression
{
public:
    // 解释
    virtual int interpret(unordered_map<char, int> context_unmap) = 0;
};

// 终结符表达式类（树叶结点；用于将 变量 解释为 值）
class TerminalExpression : public AbstractExpression
{
public:
    TerminalExpression(char var) : var(var) {}

    // 解释
    int interpret(unordered_map<char, int> context_unmap) override
    {
        return context_unmap[this->var];
    }

private:
    // 变量
    char var;
};

// 非终结符表达式类（树枝结点；用于将 表达式 解释为 操作）
class NonTerminalExpression : public AbstractExpression
{
public:
    NonTerminalExpression(AbstractExpression *expr_1, AbstractExpression *expr_2) : expr_1(expr_1), expr_2(expr_2) {}

    // 解释
    int interpret(unordered_map<char, int> context_unmap) override // 形式上 调用 非终结符表达式类的 解释方法
    {
        // 这里 解释为 加法操作
        return expr_1->interpret(context_unmap) + expr_2->interpret(context_unmap); // 实际上 调用 终结符表达式类 或 非终结符表达式类的 解释方法（递归）
    }

private:
    // 抽象表达式指针（实际上指向一个 终结符表达式对象 或 非终结符表达式对象）
    AbstractExpression *expr_1;
    AbstractExpression *expr_2;
};

// 上下文类（用于 设置和获取 变量和值的映射）
class Context
{
public:
    Context() : context_unmap() {} // unordered_map<> 的默认构造方法 初始化

    // 设置 变量和值的映射
    void set_var_value(char var, int value)
    {
        this->context_unmap[var] = value;
    }

    // 获取 变量和值的映射
    unordered_map<char, int> get_var_value()
    {
        return this->context_unmap;
    }

private:
    // 上下文/变量和值的映射
    unordered_map<char, int> context_unmap;
};

// 客户端
int main()
{
    // 构建表达式：a + b
    AbstractExpression *expr_1 = new TerminalExpression('a'); // 抽象表达式指针（实际上指向一个终结符表达式对象)
    AbstractExpression *expr_2 = new TerminalExpression('b');
    AbstractExpression *expr_3 = new NonTerminalExpression(expr_1, expr_2); // 抽象表达式指针（实际上指向一个非终结符表达式对象）

    Context context; // 上下文对象
    // 设置 变量和值的映射
    context.set_var_value('a', 10);
    context.set_var_value('b', 20);

    //  获取 变量和值的映射
    unordered_map<char, int> context_unmap = context.get_var_value();

    // 解释
    int result = expr_3->interpret(context_unmap);
    cout << "Result: " << result << endl;
    // 创建过程：
    // 反向创建：先创建树叶，后创建树枝
    // 解释过程：
    // 正向解释：先解释树枝，后解释树叶（树状递归）

    delete expr_3;
    delete expr_2;
    delete expr_1;

    return 0;
}
/*
输出：
Result: 30
*/