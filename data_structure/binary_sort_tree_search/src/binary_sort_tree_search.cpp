// 头文件————————————————————
#include <iostream>
#include <vector>

// 命名空间
using namespace std;

// 自定义数据类型————————————————————
typedef int ELEM_TYPE; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 定义
// 结点
typedef struct BSTNode
{
    ELEM_TYPE key;          // 关键字
    struct BSTNode *lChild; // 指向左孩子结点的指针
    struct BSTNode *rChild; // 指向右孩子结点的指针
} BSTNode;
// struct BSTNode：结构体数据类型的名称
// 如创建一个结点的语句：struct BSTNode node;
// 若结构体数据类型内，存在指向该结构体的指针数据类型，则必须完整命名结构体数据类型的名称
// 如结点结构体BSTNode内，存在指向该结构体的指针数据类型lChild和rChild，则命名语句为：typedef struct BSTNode而不是typedef struct
// }BTNode;：typedef给结构体数据类型起的别名，可简化语句
// 如创建一个结点的语句：BSTNode node;
// 结构体数据类型的名称和别名尽量一致，以方便记忆、使用

// 函数声明————————————————————
void use_example();                                      // 使用示例
bool insertBSTree(struct BSTNode *&root, ELEM_TYPE key); // 插入 前序遍历
bool searchBSTree(struct BSTNode *root, ELEM_TYPE key);  // 查找   前序遍历
bool searchBSTree2(struct BSTNode *root, ELEM_TYPE key); // 查找   前序遍历   迭代法
// 删除
// 对删除结点node：
//  1.是叶子节点：直接删除node
//  2.有一棵左子树或右子树：子树作为node的双亲结点的子树，删除node（子树拼接）
//  3.有左右两棵子树：
// 取node的左子树的最大关键字结点或右子树的最小关键字结点替换node，删除node->第1或2情况（取左最小或右最大替换）
// 取中序遍历时，node的直接前驱结点或直接后继结点替换node，删除node->第1或2情况（取直接前驱或直接后继替换）

// 函数定义————————————————————
// 使用示例
void use_example()
{
    // 创建
    struct BSTNode *root; // 根结点指针

    vector<ELEM_TYPE> keys = {4, 2, 1, 3, 6, 5, 7}; // 需插入的关键字向量

    for (int key : keys)
    {
        insertBSTree(root, key);
    }
    // 构造三层二叉树：
    // 第一层：4
    // 第二层：2，6
    // 第三层：1，3，5，7

    // 查找  前序遍历    递归法
    cout << searchBSTree(root, 3) << endl;  // 输出：1
    cout << searchBSTree(root, -1) << endl; // 输出：0

    // 查找  前序遍历    迭代法
    cout << searchBSTree2(root, 3) << endl;  // 输出：1
    cout << searchBSTree2(root, -1) << endl; // 输出：0

    return;
}

// 插入  前序遍历
// 时间复杂度：O(n)。n为数据规模
// 最好：O(1)
// 最坏：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：O(1)。未使用额外辅助空间
// 最坏：n。n为数据规模
bool insertBSTree(struct BSTNode *&root, ELEM_TYPE key) // 参数：根结点指针，需插入的关键字
{
    if (root == nullptr) // 空树  有插入位置，可插入
    {
        root = (struct BSTNode *)malloc(sizeof(struct BSTNode)); // 创建根结点，根结点指针指向根结点
        root->key = key;                                         // 初始化根结点的数据域
        root->lChild = nullptr;                                  // 初始化根结点的指针域
        root->rChild = nullptr;

        return true; // 插入成功
    }
    else // 非空树   递归查找插入位置
    {
        if (key == root->key) // 需插入的关键字等于根结点的关键字，关键字已存在    无插入位置，不可插入
        {
            return false; // 插入失败
        }
        else if (key < root->key) // 需插入的关键字小于根结点的关键字，关键字不一定存在    可能有插入位置，可能可插入
        {
            return insertBSTree(root->lChild, key); // 插入左子树
        }
        else if (key > root->key) // 需插入的关键字大于根结点的关键字，关键字不一定存在    可能有插入位置，可能可插入
        {
            return insertBSTree(root->rChild, key); // 插入右子树
        }
    }

    return false;
    // 注意：
    // 在if()外，最好有返回语句
    // 因为可能不进入if()，无返回值  编译器报警告
}

// 查找   前序遍历   递归法
// 适用：
// 动态表->二叉排序树
// 时间复杂度：O(logn)~O(n)。n为数据规模
// 时间复杂度：树的深度/高度
//  O(logn)。n为数据规模（二叉排序树是平衡树）
//  O(n)。n为数据规模（二叉排序树是斜树）
// 空间复杂度：
// 空间复杂度：二叉排序树的大小或递归调用栈的规模/树的深度/高度：
//  O(1)。未使用额外辅助空间（不包括二叉排序树的大小；迭代法）
//  O(n)。n为数据规模（包括二叉排序树的大小；递归法）
bool searchBSTree(struct BSTNode *root, ELEM_TYPE key) // 参数：根结点指针，需插入的关键字    返回值：查找成功为true，查找失败为false
{
    if (root == nullptr) // 空树  无查找位置
    {
        return false; // 查找失败
    }
    else // 非空树   递归查找
    {
        if (key == root->key) // 需插入的关键字等于根结点的关键字
        {
            return true; // 查找成功
        }
        else if (key < root->key) // 需插入的关键字小于根结点的关键字
        {
            return searchBSTree(root->lChild, key); // 查找左子树
        }
        else if (key > root->key) // 需插入的关键字大于根结点的关键字
        {
            return searchBSTree(root->rChild, key); // 查找右子树
        }
    }

    return false;
}

// 查找   前序遍历   迭代法
bool searchBSTree2(struct BSTNode *root, ELEM_TYPE key) // 参数：根结点指针，需插入的关键字    返回值：查找成功为true，查找失败为false
{
    if (root == nullptr) // 空树  无查找位置
    {
        return false; // 查找失败
    }
    else // 非空树   迭代查找
    {
        while (root != nullptr)
        {
            if (key == root->key) // 需插入的关键字等于根结点的关键字
            {
                return true; // 查找成功
            }
            else if (key < root->key) // 需插入的关键字小于根结点的关键字
            {
                root = root->lChild; // 查找左子树
            }
            else if (key > root->key) // 需插入的关键字大于根结点的关键字
            {
                root = root->rChild; // 查找右子树
            }
        }
    }

    return false; // 未查找成功返回，则查找失败
}

// 主函数————————————————————
int main()
{
    use_example(); // 使用示例

    return 0;
}