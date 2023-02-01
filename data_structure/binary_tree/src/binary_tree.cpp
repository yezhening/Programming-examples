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
typedef struct BTNode
{
    ELEM_TYPE data;        // 数据
    struct BTNode *lChild; // 指向左孩子结点的指针
    struct BTNode *rChild; // 指向右孩子结点的指针
} BTNode;
// struct BTNode：结构体数据类型的名称
// 如创建一个结点的语句：struct BTNode node;
// 若结构体数据类型内，存在指向该结构体的指针数据类型，则必须完整命名结构体数据类型的名称
// 如结点结构体BTNode内，存在指向该结构体的指针数据类型lChild和rChild，则命名语句为：typedef struct BTNode而不是typedef struct
// }BTNode;：typedef给结构体数据类型起的别名，可简化语句
// 如创建一个结点的语句：BTNode node;
// 结构体数据类型的名称和别名尽量一致，以方便记忆、使用

// 函数声明————————————————————
void use_example();                     // 使用示例
void createBTree(struct BTNode *&root); // 创建 前序法

void preOrderTraverse(struct BTNode *root);                                              // 前序遍历    递归法
void inOrderTraverse(struct BTNode *root);                                               // 中序遍历    递归法
void postOrderTraverse(struct BTNode *root);                                             // 后序遍历    递归法
void levelOrderTraverse(struct BTNode *root, int layer, vector<vector<ELEM_TYPE>> &res); // 层序遍历   递归法

void preOrderTraverse2(struct BTNode *root);   // 前序遍历  迭代法
void inOrderTraverse2(struct BTNode *root);    // 中序遍历  迭代法
void postOrderTraverse2(struct BTNode *root);  // 后序遍历  迭代法
void levelOrderTraverse2(struct BTNode *root); // 层序遍历   迭代法

int getDepth(struct BTNode *root); // 获取深度/高度

// 函数定义————————————————————
// 使用示例
void use_example()
{
    // 创建
    struct BTNode *root; // 根结点指针

    createBTree(root); // 创建 前序法
    // 构造三层二叉树：
    // 第一层：1
    // 第二层：2，3
    // 第三层：-1，-1，-1，4
    // 输入数据：1，2，-1，-1，3，-1，4，-1，-1

    preOrderTraverse(root); // 前序遍历  递归法   输出：1，2，3，4
    cout << endl;

    inOrderTraverse(root); // 中序遍历   递归法   输出：2，1，3，4
    cout << endl;

    postOrderTraverse(root); // 后序遍历 递归法    输出：2，4，3，1
    cout << endl;

    vector<vector<ELEM_TYPE>> res; // 层序遍历 递归法 输出：1，2，3，4
    levelOrderTraverse(root, 0, res);
    for (vector<ELEM_TYPE> vec : res)
    {
        for (ELEM_TYPE data : vec)
        {
            cout << data;
        }
    }
    cout << endl;

    preOrderTraverse2(root); // 前序遍历  迭代法   输出：1，2，3，4
    cout << endl;

    inOrderTraverse2(root); // 中序遍历  迭代法    输出：2，1，3，4
    cout << endl;

    postOrderTraverse2(root); // 后序遍历  迭代法    输出：2，4，3，1
    cout << endl;

    levelOrderTraverse2(root); // 层序遍历 迭代法 输出：1，2，3，4
    cout << endl;

    cout << getDepth(root) << endl; // 获取深度/高度 输出：3

    return;
}

// 创建 前序法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
// 注意：参数使用*&，指向指针的引用数据类型
// 若只使用*：指针数据类型，在函数体中并未进行解引用调用修改*root的值，使用malloc()修改的是root的值
// 所以是值拷贝，函数返回后数据丢失。地址拷贝需要引用数据类型的配合
void createBTree(struct BTNode *&root) // 参数：根结点指针
{
    ELEM_TYPE value = 0; // 值
    cin >> value;        // 获取输入值

    if (value == -1) // 空树  约定值为-1时无结点
    {
        root = nullptr; // 根结点指针指向空
    }
    else // 非空树
    {
        root = (struct BTNode *)malloc(sizeof(struct BTNode)); // 创建根结点，根结点指针指向根结点

        root->data = value;        // 初始化根结点的数据域
        createBTree(root->lChild); // 递归构造左子树
        createBTree(root->rChild); // 递归构造右子树
    }

    return;
}

// 前序遍历  递归法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
void preOrderTraverse(struct BTNode *root) // 参数：根结点指针
{
    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        cout << root->data;             // 输出数据
        preOrderTraverse(root->lChild); // 前序遍历左子树
        preOrderTraverse(root->rChild); // 前序遍历右子树
    }

    return;
}

// 中序遍历  递归法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
void inOrderTraverse(struct BTNode *root) // 参数：根结点指针
{
    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        inOrderTraverse(root->lChild); // 中序遍历左子树
        cout << root->data;            // 输出数据
        inOrderTraverse(root->rChild); // 中序遍历右子树
    }

    return;
}

// 后序遍历  递归法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
void postOrderTraverse(struct BTNode *root) // 参数：根结点指针
{
    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        postOrderTraverse(root->lChild); // 后序遍历左子树
        postOrderTraverse(root->rChild); // 后序遍历右子树
        cout << root->data;              // 输出数据
    }

    return;
}

// 层序遍历  递归法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
// 空间复杂度：存储结点数据的二维向量：n。n为数据规模
void levelOrderTraverse(struct BTNode *root, int layer, vector<vector<ELEM_TYPE>> &res) // 参数：根结点指针，层次，记录结点数据的二维向量
{
    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        // 一维向量vec记录一层中，从左到右结点的数据
        // 二维向量res记录从上到下每一层的vec

        // 因为向量大小从0开始，约定：层次从0开始，根结点为第0层，根结点的孩子结点为第1层，依次类推
        // 每遍历到新的层次，当前层次layer等于res的大小，如：
        // 第一层：layer为0，res.size()为0
        // 第二层：layer为1，res已记录第0层的vec，res.size()为1
        // 每遍历到新的层次，创建vec，res记录vec

        // 依据layer定位res中的vec，记录结点的数据

        // 核心思想：
        // 本质：前序递归遍历，需要递归访问根结点的左子树和右子树
        // 访问结点顺序：中->左->右，处理结点顺序：每层的左->右
        // 所以需要结合vec、layer和res记录层次遍历结点的数据

        if (layer == res.size())
        {
            vector<ELEM_TYPE> vec;
            res.push_back(vec);
        }

        res[layer].push_back(root->data);

        if (root->lChild != nullptr) // 根结点的左孩子结点不为空
        {
            levelOrderTraverse(root->lChild, layer + 1, res);
        }

        if (root->rChild != nullptr) // 根结点的右孩子结点不为空
        {
            levelOrderTraverse(root->rChild, layer + 1, res);
        }
    }

    return;
}

// 前序遍历  迭代法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模/用户栈规模
void preOrderTraverse2(struct BTNode *root) // 参数：根结点指针
{
    constexpr int maxSize = 10;             // 指向结点的指针的向量/栈的初始化大小    大小>=结点数
    vector<struct BTNode *> stack(maxSize); // 指向结点的指针的向量/栈
    int top = -1;                           // 指向栈顶结点的指针

    struct BTNode *visitNode = nullptr; // 指向访问结点的指针

    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        ++top;
        stack[top] = root; // 根结点入栈

        while (top != -1) // 栈不为空时，循环
        {
            visitNode = stack[top]; // 指向访问结点的指针指向栈顶结点
            --top;                  // 栈顶结点出栈

            cout << visitNode->data; // 访问结点的数据

            if (visitNode->rChild != nullptr) // 右孩子结点不为空
            {
                ++top;
                stack[top] = visitNode->rChild; // 右孩子结点入栈
            }

            if (visitNode->lChild != nullptr) // 左孩子结点不为空
            {
                ++top;
                stack[top] = visitNode->lChild; // 左孩子结点入栈
            }
        }
    }

    return;
}

// 中序遍历  迭代法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模/用户栈规模
void inOrderTraverse2(struct BTNode *root) // 参数：根结点指针
{
    constexpr int maxSize = 10;             // 指向结点的指针的向量/栈的初始化大小    大小>=结点数
    vector<struct BTNode *> stack(maxSize); // 指向结点的指针的向量/栈
    int top = -1;                           // 指向栈顶结点的指针

    struct BTNode *visitNode = root; // 指向访问结点的指针    指向根结点

    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        // 注意：栈顶结点/根结点出栈并访问后，还没有访问右子树
        // 可能存在栈空，右子树不为空的情况，需要继续遍历/循环
        // 指向访问结点的指针指向栈顶结点/根结点的右孩子结点，若指针不空，则存在右子树，需要继续遍历/循环
        while (top != -1 || visitNode != nullptr) // 栈不为空或指向访问结点的指针不为空时，循环
        {
            // 左孩子结点循环入栈
            while (visitNode != nullptr) // 指向访问结点的指针不为空
            {
                ++top;
                stack[top] = visitNode; // 指向访问结点的指针入栈

                visitNode = visitNode->lChild; // 指向访问结点的指针指向访问结点的左孩子结点
            }

            if (top != -1) // 栈不为空
            {
                visitNode = stack[top]; // 指向访问结点的指针指向栈顶结点
                --top;                  // 栈顶结点出栈

                cout << visitNode->data; // 访问结点的数据

                visitNode = visitNode->rChild; // 指向访问结点的指针指向栈顶结点/根结点的右孩子结点
            }
        }
    }

    return;
}

// 后序遍历  迭代法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模/用户栈规模
void postOrderTraverse2(struct BTNode *root) // 参数：根结点指针
{
    // 核心思想：
    // 反前序遍历：中->右->左
    // 逆后序遍历 = 反前序遍历
    // 后序遍历 = 逆逆后序遍历->反前序遍历中，访问结点出栈1、入栈2再出栈2的顺序

    constexpr int maxSize = 10;              // 指向结点的指针的向量/栈的初始化大小    大小>=结点数
    vector<struct BTNode *> stack1(maxSize); // 指向结点的指针的向量/栈1 反前序遍历使用
    vector<struct BTNode *> stack2(maxSize); // 指向结点的指针的向量/栈2 逆逆后序遍历使用
    int top1 = -1;                           // 指向栈1顶结点的指针1
    int top2 = -1;                           // 指向栈2顶结点的指针2

    struct BTNode *visitNode = nullptr; // 指向访问结点的指针

    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        // 反前序遍历过程
        ++top1;
        stack1[top1] = root; // 根结点入栈1

        while (top1 != -1) // 栈1不为空时，循环
        {
            visitNode = stack1[top1]; // 指向访问结点的指针指向栈1顶结点
            --top1;                   // 栈1顶结点出栈1

            ++top2;
            stack2[top2] = visitNode; // 访问结点入栈2

            // 反前序遍历与前序遍历操作相反
            if (visitNode->lChild != nullptr) // 左孩子结点不为空
            {
                ++top1;
                stack1[top1] = visitNode->lChild; // 左孩子结点入栈1
            }

            if (visitNode->rChild != nullptr) // 右孩子结点不为空
            {
                ++top1;
                stack1[top1] = visitNode->rChild; // 右孩子结点入栈1
            }
        }

        // 逆逆后序遍历过程
        while (top2 != -1) // 栈2不为空时，循环
        {
            visitNode = stack2[top2]; // 指向访问结点的指针指向栈2顶结点
            --top2;                   // 栈2顶结点出栈2

            cout << visitNode->data; // 访问结点的数据
        }
    }

    return;
}

// 层序遍历  迭代法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：指向结点的指针的向量/循环队列的大小
void levelOrderTraverse2(struct BTNode *root) // 参数：根结点指针
{
    constexpr int maxSize = 10;             // 指向结点的指针的向量/循环队列的初始化大小    大小尽量>=结点数
    vector<struct BTNode *> queue(maxSize); // 指向结点的指针的向量/循环队列
    int front = 0;                          // 指向队列头结点的指针
    int rear = 0;                           // 指向队列尾结点的下一结点的指针

    struct BTNode *visitNode = nullptr; // 指向访问结点的指针

    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        queue[rear] = root; // 根结点入队
        rear = (rear + 1) % maxSize;

        while (front != rear) // 队列不为空，循环
        {
            visitNode = queue[front];      // 指向访问结点的指针指向队列头结点
            front = (front + 1) % maxSize; // 队列头结点出队

            cout << visitNode->data; // 访问结点的数据

            if (visitNode->lChild != nullptr) // 左子树不为空
            {
                queue[rear] = visitNode->lChild; // 左子树的根结点入队
                rear = (rear + 1) % maxSize;
            }

            if (visitNode->rChild != nullptr) // 右子树不为空
            {
                queue[rear] = visitNode->rChild; // 右子树的根结点入队
                rear = (rear + 1) % maxSize;
            }
        }
    }

    return;
}

// 获取深度/高度
// 本质：后序遍历
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
int getDepth(struct BTNode *root) // 参数：根结点指针
{
    int lDepth = 0; // 左子树的深度
    int rDepth = 0; // 右子树的深度
    int depth = 0;  // 深度=左子树深度和右子树深度间的最大值+1

    if (root == nullptr) // 空树
    {
        depth = 0;
    }
    else // 非空树
    {
        lDepth = getDepth(root->lChild); // 后序遍历获取左子树的深度
        rDepth = getDepth(root->rChild); // 后序遍历获取右子树的深度
        if (lDepth < rDepth)
        {
            depth = rDepth + 1;
        }
        else
        {
            depth = lDepth + 1;
        }
    }

    return depth;
}

// 主函数————————————————————
int main()
{
    use_example(); // 使用示例

    return 0;
}