#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// 产品类
class Product
{
public:
    void set_part_a(const string &part_a)
    {
        this->part_a = part_a;
    }

    void set_part_b(const string &part_b)
    {
        this->part_b = part_b;
    }

    inline void show() const
    {
        cout << "Product parts: " << this->part_a << ", " << this->part_b << endl;
    }

private:
    string part_a;
    string part_b;
};

// 抽象建造者类
class AbstractBuilder
{
public:
    virtual void build_part_a() = 0; // 建造产品方法
    virtual void build_part_b() = 0;
    virtual Product get_product() = 0; // 获取产品方法
};

// 具体建造者类
class ConcreteBuilder : public AbstractBuilder
{
public:
    ConcreteBuilder() : product() {} // 使用默认构造函数创建产品对象

    void build_part_a() override
    {
        this->product.set_part_a("Part A");
    }

    void build_part_b() override
    {
        this->product.set_part_b("Part B");
    }

    inline Product get_product() override
    {
        return this->product;
    }

private:
    Product product;
};

// 指挥者类
class Director
{
public:
    Director(AbstractBuilder *abstract_builder) : abstract_builder(abstract_builder){};

    void build() // 建造方法
    {
        this->abstract_builder->build_part_a();
        this->abstract_builder->build_part_b();
    }

private:
    AbstractBuilder *abstract_builder;
};

// 客户端
int main()
{
    // 创建具体建造者对象
    AbstractBuilder *concrete_builder = new ConcreteBuilder();

    // 创建指挥者对象
    Director director(concrete_builder);

    // 建造过程
    director.build();

    // 获取产品
    Product product = concrete_builder->get_product();

    // 展示产品
    product.show();

    delete concrete_builder;

    return 0;
}
/*
输出：
Product parts: Part A, Part B
*/