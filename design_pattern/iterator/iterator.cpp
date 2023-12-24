#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// 项目类（需要迭代 的对象）
class Item
{
public:
    Item(string name) : name(name) {}

    // 获取名称
    string get_name()
    {
        return this->name;
    }

private:
    string name; // 名称
};

// 抽象迭代器类
class AbstractIterator
{
public:
    virtual Item *get_first() = 0; // 获取第一个项目
    virtual Item *get_next() = 0;  // 获取下一个项目
};

// 具体迭代器类（帮助迭代 的对象）
class ConcreteIterator : public AbstractIterator
{
public:
    ConcreteIterator(vector<Item *> item_vec) : item_vec(item_vec), cur_index(0) {}

    // 获取第一个项目
    Item *get_first() override
    {
        Item *item = this->item_vec[0];

        if (item != nullptr) // 有第一个项目
        {
            return item; // 返回第一个项目
        }
        else // 无第一个项目
        {
            return nullptr; // 返回空指针
        }
    }

    // 获取下一个项目
    Item *get_next() override
    {
        if ((this->cur_index < (this->item_vec.size() - 1)) == true)
        // 索引 = 大小 - 1
        // 如果 项目的当前索引 小于 项目集合的大小 - 1，返回 true，有下一个项目
        // 如果 项目的当前索引 等于或大于 项目集合的大小 - 1，返回 false，无下一个项目
        {
            ++this->cur_index;
            Item *item = this->item_vec[this->cur_index];

            return item;
        }
        else
        {
            return nullptr;
        }
    }

private:
    vector<Item *> item_vec; // 项目指针（实际上指向一个项目对象）的集合
    size_t cur_index;        // 项目集合的当前索引
};

// 抽象聚合类
class AbstractAggregate
{
public:
    virtual AbstractIterator *create_iterator() = 0; // 创建迭代器
};

// 具体聚合类（连接 项目集合 和 迭代器，获取 并 使用 项目集合 创建 迭代器）
class ConcreteAggregate : public AbstractAggregate
{
public:
    ConcreteAggregate(vector<Item *> item_vec) : item_vec(item_vec) {}

    // 创建迭代器（抽象迭代器指针类型 的 具体迭代器指针）
    AbstractIterator *create_iterator() override
    {
        return new ConcreteIterator(this->item_vec);
    }

private:
    vector<Item *> item_vec;
};

// 客户端
int main()
{
    // 项目对象的集合
    Item *item_1 = new Item("Item1");
    Item *item_2 = new Item("Item2");
    Item *item_3 = new Item("Item3");
    vector<Item *> item_vec = {item_1, item_2, item_3};

    // 具体聚合对象
    ConcreteAggregate aggregate(item_vec);

    // 抽象迭代器指针类型 的 具体迭代器指针
    AbstractIterator *iterator = aggregate.create_iterator(); // 创建迭代器

    // 使用 具体迭代器指针 遍历 项目对象的集合
    for (Item *item = iterator->get_first(); item != nullptr; item = iterator->get_next())
    {
        cout << "Item: " << item->get_name() << endl;
    }

    delete iterator;
    for (Item *item : item_vec)
    {
        delete item;
    }

    return 0;
}
/*
输出：
Item: Item1
Item: Item2
Item: Item3
*/