// 头文件————————————————————
#include <iostream>

// 命名空间
using namespace std;

// 自定义数据类型————————————————————
typedef int ELEM_TYPE; // 数据的（数据）类型 依据数据的实际类型定义

// 结构体
// 结点
typedef struct TBTNode
{
    ELEM_TYPE data; // 数据

    int lTag;               // 左线索标志    可用bool数据类型
    int rTag;               // 右线索标志
    struct TBTNode *lChild; // 指向左孩子结点的指针
    struct TBTNode *rChild; // 指向右孩子结点的指针
    // 约定：
    // 当lTag=0时，lChild为指针，指向左孩子结点；当lTag=1时，lChild为线索，指向直接前驱结点
    // 当rTag=0时，rChild为指针，指向右孩子结点；当rTag=1时，rChild为线索，指向直接后继结点
} TBTNode;
// struct TBTNode：结构体数据类型的名称
// 如创建一个结点的语句：struct TBTNode node;
// 若结构体数据类型内，存在指向该结构体的指针数据类型，则必须完整命名结构体数据类型的名称
// 如结点结构体TBTNode内，存在指向该结构体的指针数据类型lChild和rChild，则命名语句为：typedef struct TBTNode而不是typedef struct
// }TBTNode;：typedef给结构体数据类型起的别名，可简化语句
// 如创建一个结点的语句：TBTNode node;
// 结构体数据类型的名称和别名尽量一致，以方便记忆、使用

// 函数声明————————————————————
void use_example();                       // 使用示例
void createTBTree(struct TBTNode *&root); // 创建 前序法

void inThread(struct TBTNode *cur, struct TBTNode *&pre); // 线索化    中序遍历法
void createInThread(struct TBTNode *root);                // 线索化创建    中序遍历法
struct TBTNode *inFirst(struct TBTNode *cur);             // 获取第一个结点    中序遍历法
struct TBTNode *inNext(struct TBTNode *cur);              // 获取后继结点    中序遍历法
void inOrderTraverse(struct TBTNode *root);               // 中序遍历

void preThread(struct TBTNode *cur, struct TBTNode *&pre); // 线索化    前序遍历法
void preOrderTraverse(struct TBTNode *root);               // 前序遍历

void postThread(struct TBTNode *cur, struct TBTNode *&pre); // 线索化    后序遍历法
// 后序遍历：复杂，需要知道结点双亲->使用带标志域的三叉链表

// 函数定义————————————————————
// 使用示例
void use_example()
{
    struct TBTNode *root; // 根结点指针

    createTBTree(root); // 创建 前序法
    // 构造三层二叉树：
    // 第一层：1
    // 第二层：2，3
    // 第三层：-1，-1，-1，4
    // 输入数据：1，2，-1，-1，3，-1，4，-1，-1

    createInThread(root); // 线索化创建    中序遍历法

    inOrderTraverse(root); // 中序遍历  输出：2，1，3，4
    cout << endl;

    struct TBTNode *root1; // 根结点指针1

    createTBTree(root1); // 创建 前序法
    // 构造三层二叉树：
    // 第一层：1
    // 第二层：2，3
    // 第三层：-1，-1，-1，4
    // 输入数据：1，2，-1，-1，3，-1，4，-1，-1

    struct TBTNode *pre = nullptr; // 前驱结点指针  指向空
    preThread(root1, pre);         // 线索化    前序遍历法

    preOrderTraverse(root1); // 前序遍历  输出：1，2，3，4
    cout << endl;

    struct TBTNode *root2; // 根结点指针2

    createTBTree(root2); // 创建 前序法
    // 构造三层二叉树：
    // 第一层：1
    // 第二层：2，3
    // 第三层：-1，-1，-1，4
    // 输入数据：1，2，-1，-1，3，-1，4，-1，-1

    struct TBTNode *pre1 = nullptr; // 前驱结点指针1  指向空
    postThread(root2, pre1);        // 线索化    后序遍历法

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
void createTBTree(struct TBTNode *&root) // 参数：根结点指针
{
    ELEM_TYPE value = 0; // 值
    cin >> value;        // 获取输入值

    if (value == -1) // 空树  约定值为-1时无结点
    {
        root = nullptr; // 根结点指针指向空
    }
    else // 非空树
    {
        root = (struct TBTNode *)malloc(sizeof(struct TBTNode)); // 创建根结点，根结点指针指向根结点

        root->data = value;         // 初始化根结点的数据域
        root->lTag = 0;             // 初始化根结点的左线索标志
        root->rTag = 0;             // 初始化右结点的左线索标志
        createTBTree(root->lChild); // 递归构造左子树
        createTBTree(root->rChild); // 递归构造右子树
    }

    return;
}

// 线索化    中序遍历法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
void inThread(struct TBTNode *cur, struct TBTNode *&pre) // 参数：当前结点指针，前驱结点指针
{
    if (cur == nullptr) // 空树
    {
    }
    else // 非空树
    {
        inThread(cur->lChild, pre); // 当前结点的左子树线索化

        // 线索化
        if (cur->lChild == nullptr) // 当前结点的左孩子结点为空   建立当前结点的前驱线索
        {
            cur->lTag = 1;     // 当前结点的左线索标志置1
            cur->lChild = pre; // 当前结点的左孩子结点指针指向前驱结点
        }
        if (pre != nullptr && pre->rChild == nullptr) // 前驱结点不为空且前驱结点的右孩子结点为空   建立前驱结点的后继线索
        {
            pre->rTag = 1;     // 前驱结点的右线索标志置1
            pre->rChild = cur; // 前驱结点的右孩子结点指针指向当前结点
        }

        pre = cur; // 更新结点指针：前驱结点指针指向当前结点

        inThread(cur->rChild, pre); // 当前结点的右子树线索化
    }

    return;
}

// 线索化创建    中序遍历法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
void createInThread(struct TBTNode *root) // 参数：根结点指针
{
    struct TBTNode *pre = nullptr; // 前驱结点指针  指向空

    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        inThread(root, pre); // 线索化 中序遍历法

        // 已更新结点指针：前驱结点指针指向最后一个结点
        // 处理最后一个结点：必为叶子结点，右孩子结点为空
        pre->rTag = 1;
        pre->rChild = nullptr;
    }

    return;
}

// 获取第一个结点    中序遍历法
// 时间复杂度：O(n)。n为数据规模
// 时间复杂度：树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
// 空间复杂度：O(1)。未使用辅助空间
struct TBTNode *inFirst(struct TBTNode *cur) // 参数：当前结点指针    返回值：以当前结点为根的树，中序遍历时的第一个结点
{
    // 以当前结点为根的树，中序遍历的第一个结点是最左下结点
    while (cur->lTag == 0) // 当前结点的左线索标志为0
    {
        cur = cur->lChild; // 更新当前结点指针指向当前结点的左孩子结点
    }

    return cur;
}

// 获取后继结点    中序遍历法
// 时间复杂度：O(n)。n为数据规模
// 时间复杂度：树的深度/高度或直接获取
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模。或O(1)
// 最坏：n。n为数据规模
// 空间复杂度：O(1)。未使用辅助空间
struct TBTNode *inNext(struct TBTNode *cur) // 参数：当前结点指针    返回值：中序遍历时，当前结点的后继结点
{
    // 若当前结点的右线索标志为0，存在以当前结点的右孩子结点为根的右子树，获取第一个结点
    // 若当前结点的右线索标志为1，右孩子结点指针指向直接后继结点，直接获取
    if (cur->rTag == 0)
    {
        return inFirst(cur->rChild);
    }
    else
    {
        return cur->rChild;
    }
}

// 中序遍历
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(1)。未使用辅助空间
void inOrderTraverse(struct TBTNode *root) // 参数：根结点指针
{
    for (struct TBTNode *cur = inFirst(root); cur != nullptr; cur = inNext(cur))
    {
        cout << cur->data; // 访问结点的数据
    }

    return;
}

// 线索化    前序遍历法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
void preThread(struct TBTNode *cur, struct TBTNode *&pre) // 参数：当前结点指针，前驱结点指针
{
    if (cur == nullptr) // 空树
    {
    }
    else // 非空树
    {
        // 线索化
        if (cur->lChild == nullptr) // 当前结点的左孩子结点为空   建立当前结点的前驱线索
        {
            cur->lTag = 1;     // 当前结点的左线索标志置1
            cur->lChild = pre; // 当前结点的左孩子结点指针指向前驱结点
        }
        if (pre != nullptr && pre->rChild == nullptr) // 前驱结点不为空且前驱结点的右孩子结点为空   建立前驱结点的后继线索
        {
            pre->rTag = 1;     // 前驱结点的右线索标志置1
            pre->rChild = cur; // 前驱结点的右孩子结点指针指向当前结点
        }

        pre = cur; // 更新结点指针：前驱结点指针指向当前结点

        // 注意：有限制条件
        if (cur->lTag == 0) // 当前结点的左线索标志为0，存在左孩子结点
        {
            preThread(cur->lChild, pre); // 当前结点的左子树线索化
        }
        if (cur->rTag == 0) // 当前结点的左线索标志为0，存在右孩子结点
        {
            preThread(cur->rChild, pre); // 当前结点的右子树线索化
        }
    }

    return;
}

// 前序遍历
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(1)。未使用辅助空间
void preOrderTraverse(struct TBTNode *root) // 参数：根结点指针
{
    struct TBTNode *cur = nullptr; // 当前结点指针  指向空

    if (root == nullptr) // 空树
    {
    }
    else // 非空树
    {
        cur = root; // 当前结点指针指向根结点

        while (cur != nullptr) // 当前结点不为空时，说明未遍历完，循环
        {
            while (cur->lTag == 0) // 当前结点的左线索标志为0，左孩子结点不为空
            {
                cout << cur->data; // 访问当前结点的数据
                cur = cur->lChild; // 当前结点指针指向当前结点的左孩子结点：中->左
            }

            // 当前结点的左线索标志为1，左孩子结点为空
            cout << cur->data; // 访问当前结点的数据
            cur = cur->rChild;
            // 若当前结点的右线索标志为0，右孩子结点不为空，当前结点指针指向当前结点的右孩子结点：中->左（空）->右
            // 若当前结点的右线索标志为1，右孩子结点为空，当前结点指针指向当前结点的直接后继结点
        }
    }

    return;
}

// 线索化    后序遍历法
// 时间复杂度：O(n)。n为数据规模
// 空间复杂度：O(n)。n为数据规模
// 空间复杂度：递归调用栈的规模/树的深度/高度：
// 最好：[log以2为底的n]下取整+1或[log以2为底的(n+1)]上取整。n为数据规模
// 最坏：n。n为数据规模
void postThread(struct TBTNode *cur, struct TBTNode *&pre) // 参数：当前结点指针，前驱结点指针
{
    if (cur == nullptr) // 空树
    {
    }
    else // 非空树
    {

        postThread(cur->lChild, pre); // 当前结点的左子树线索化

        postThread(cur->rChild, pre); // 当前结点的右子树线索化

        // 线索化
        if (cur->lChild == nullptr) // 当前结点的左孩子结点为空   建立当前结点的前驱线索
        {
            cur->lTag = 1;     // 当前结点的左线索标志置1
            cur->lChild = pre; // 当前结点的左孩子结点指针指向前驱结点
        }
        if (pre != nullptr && pre->rChild == nullptr) // 前驱结点不为空且前驱结点的右孩子结点为空   建立前驱结点的后继线索
        {
            pre->rTag = 1;     // 前驱结点的右线索标志置1
            pre->rChild = cur; // 前驱结点的右孩子结点指针指向当前结点
        }

        pre = cur; // 更新结点指针：前驱结点指针指向当前结点
    }

    return;
}

// 主函数————————————————————
int main()
{
    use_example(); // 使用示例

    return 0;
}