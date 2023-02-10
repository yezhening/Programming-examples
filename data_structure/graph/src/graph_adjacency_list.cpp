// 头文件————————————————————
#include <iostream>

// 命名空间————————————————————
using namespace std;

// 宏————————————————————
#define MAX_VERTEX_NUM 5 // 最大顶点数

// 自定义数据类型————————————————————
// 邻接表：
// 边表结点
typedef struct EdgeNode
{
    int adjVex;            // 邻接顶点的下标 注意：邻接顶点在邻接表的下标
    struct EdgeNode *next; // 指向下一个边表结点的指针
    // int info;              //边的其他信息，如权值
} EdgeNode;
// struct EdgeNode：结构体数据类型的名称
// 如创建一个结点的语句：struct EdgeNode node;
// 若结构体数据类型内存在指向该结构体的指针数据类型，则必须完整命名结构体数据类型的名称
// 如结点结构体EdgeNode内存在指向该结构体的指针数据类型next，则命名语句为：typedef struct EdgeNode而不是typedef struct
// EdgeNode：typedef给结构体数据类型起的别名，可简化语句
// 如创建一个结点的语句：EdgeNode node;
// 结构体数据类型的名称和别名尽量一致，以方便记忆、使用

// 顶点表结点
typedef struct
{
    int data;                   // 顶点的数据    注意：不同于邻接顶点在邻接表的下标
    struct EdgeNode *firstEdge; // 指向第一个边表结点的指针
} VertexNode;

// 图的邻接表
typedef struct
{
    int vexNum;                         // 顶点数
    int edgeNum;                        // 边数
    VertexNode adjList[MAX_VERTEX_NUM]; // 邻接表
} Graph;

// 全局变量
// 已访问标志数组
// 遍历时，未访问的顶点为false，已访问的顶点为true
bool g_visited[MAX_VERTEX_NUM];

// 函数声明————————————————————
void use_example();             // 使用示例
void createGraph(Graph &graph); // 创建图
void dfsTraverse(Graph graph);  // 深度优先遍历1
void dfs(Graph graph, int i);   // 深度优先遍历2
void bfsTraverse(Graph graph);  // 广度优先遍历1
void bfs(Graph graph, int i);   // 广度优先遍历2

// 函数定义————————————————————
// 使用示例
void use_example()
{
    Graph graph;
    createGraph(graph); // 创建图

    dfsTraverse(graph); // 深度优先遍历1
    // 输出：0 1 3 2 4
    cout << endl;

    bfsTraverse(graph); // 广度优先遍历1
    // 输出：0 1 2 3 4
    cout << endl;

    return;
}

// 创建图
// 时间复杂度：O(n+e)。n为顶点数，e为边数
// 空间复杂度：
//  O(1)。未使用额外辅助空间
//  O(e)。e为边数（边表结点空间）
void createGraph(Graph &graph) // 参数：图
{
    // 构建无向非连通图：
    //  5个顶点：0，1，2，3，4
    //  6条边：0-1，0-2，1-3，2-3
    // 顶点0，1，2，3是一个连通分量，为矩形：0-1-2-3-0
    // 顶点4是一个连通分量

    // 初始化顶点数
    graph.vexNum = 5; // 5个顶点

    // 初始化边数
    graph.edgeNum = 4; // 4条边

    // 初始化顶点表
    for (int i = 0; i < graph.vexNum; ++i)
    {
        graph.adjList[i].data = i; // 顶点序号/数据为下标：0，1，2，3，4 注意：初始化顶点数据为  顶点在邻接表的下标
        graph.adjList[i].firstEdge = nullptr;
    }

    // 初始化边表
    struct EdgeNode *node = nullptr; // 边表节点

    // 0->1->2：顶点0的邻接点是顶点1和顶点2
    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1); // 创建边表结点
    node->adjVex = 2;                                              // 顶点0的邻接点是顶点2
    node->next = graph.adjList[0].firstEdge;                       // 头插法
    graph.adjList[0].firstEdge = node;

    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1);
    node->adjVex = 1;
    node->next = graph.adjList[0].firstEdge;
    graph.adjList[0].firstEdge = node;

    // 1->0->3：顶点1的邻接点是顶点0和顶点3
    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1); // 创建边表结点
    node->adjVex = 3;                                              // 顶点1的邻接点是顶点3
    node->next = graph.adjList[1].firstEdge;                       // 头插法
    graph.adjList[1].firstEdge = node;

    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1);
    node->adjVex = 0;
    node->next = graph.adjList[1].firstEdge;
    graph.adjList[1].firstEdge = node;

    // 2->0->3：顶点2的邻接点是顶点0和顶点3
    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1); // 创建边表结点
    node->adjVex = 3;                                              // 顶点2的邻接点是顶点3
    node->next = graph.adjList[2].firstEdge;                       // 头插法
    graph.adjList[2].firstEdge = node;

    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1);
    node->adjVex = 0;
    node->next = graph.adjList[2].firstEdge;
    graph.adjList[2].firstEdge = node;

    // 3->1->2：顶点3的邻接点是顶点1和顶点2
    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1); // 创建边表结点
    node->adjVex = 2;                                              // 顶点3的邻接点是顶点2
    node->next = graph.adjList[3].firstEdge;                       // 头插法
    graph.adjList[3].firstEdge = node;

    node = (struct EdgeNode *)malloc(sizeof(struct EdgeNode) * 1);
    node->adjVex = 1;
    node->next = graph.adjList[3].firstEdge;
    graph.adjList[3].firstEdge = node;

    // 注意：无向图的1条边，在邻接表中需要赋值2次

    return;
}

// 深度优先遍历1
// 时间复杂度：依据存储结构
// 对邻接表：遍历点数+查找每点的邻接点的时间 = O(v+e)。v为点数，e为边数（理解：遍历点表和边表，因为是链式存储结构）
// 空间复杂度：O(v)。v为点数/辅助空间规模/递归栈规模
void dfsTraverse(Graph graph) // 参数：图
{
    // 初始化已访问标志数组
    for (int i = 0; i < graph.vexNum; ++i)
    {
        g_visited[i] = false;
    }

    for (int i = 0; i < graph.vexNum; ++i)
    {
        if (g_visited[i] == false) // 若顶点未访问
        {
            dfs(graph, i); // 深度优先遍历2        从下标为i的顶点开始
        }
        // 注意：
        // 使用下标判断顶点的已访问标志
        // 使用下标对顶点进行深度优先遍历2
    }
    // 连通图执行一次，非连通图执行多次
    // 非连通无向图执行连通分量数次，非强连通有向图的非强连通分量不一定能遍历所有点

    return;
}

// 深度优先遍历2
void dfs(Graph graph, int i) // 参数：图，开始顶点下标
{
    cout << graph.adjList[i].data << " "; // 访问顶点
    g_visited[i] = true;                  // 已访问标志置位

    struct EdgeNode *node = graph.adjList[i].firstEdge; // 取边表结点

    // 对顶点i的邻接顶点：若未访问，则递归进行深度优先遍历2
    while (node != nullptr)
    {
        if (g_visited[node->adjVex] == false)
        {
            dfs(graph, node->adjVex); // 注意参数
        }

        node = node->next;
    }

    return;
}

// 广度优先遍历1
// 时间复杂度：依据存储结构
// 对邻接表：遍历点数+查找每点的邻接点的时间=O(v+e)。v为点数，e为边数（理解：遍历点表和边表，因为是链式存储结构）
// 空间复杂度：O(v)。v为点数/辅助空间规模
void bfsTraverse(Graph graph)
{
    // 初始化已访问标志数组
    for (int i = 0; i < graph.vexNum; ++i)
    {
        g_visited[i] = false;
    }

    for (int i = 0; i < graph.vexNum; ++i)
    {
        if (g_visited[i] == false) // 若顶点未访问
        {
            bfs(graph, i); // 广度优先遍历2        从下标为i的顶点开始
        }
        // 注意：
        // 使用下标判断顶点的已访问标志
        // 使用下标对顶点进行广度优先遍历2
    }
    // 连通图执行一次，非连通图执行多次
    // 非连通无向图执行连通分量数次，非强连通有向图的非强连通分量不一定能遍历所有点

    return;
}

// 广度优先遍历2
void bfs(Graph graph, int i) // 参数：图，开始顶点下标
{
    // 初始化队列    简单定义
    int queue[MAX_VERTEX_NUM]; // 循环队列
    int front = 0;             // 队列头指针
    int rear = 0;              // 队列尾指针

    cout << graph.adjList[i].data << " "; // 访问顶点
    g_visited[i] = true;                  // 已访问标志置位

    // 顶点下标入队
    // 注意：是顶点下标入队
    queue[rear] = i;
    rear = (rear + 1) % MAX_VERTEX_NUM;

    while (front != rear) // 队列不为空时，循环遍历
    {
        // 顶点下标出队
        // 注意：是顶点下标出队
        i = queue[front];
        front = (front + 1) % MAX_VERTEX_NUM;

        struct EdgeNode *node = graph.adjList[i].firstEdge; // 取边表结点

        // 对顶点i的邻接顶点：若未访问，则迭代进行广度优先遍历2
        while (node != nullptr) // 注意循环终止条件
        {
            if (g_visited[node->adjVex] == false)
            {
                cout << node->adjVex << " ";    // 访问顶点
                g_visited[node->adjVex] = true; // 已访问标志置位

                // 顶点下标入队
                // 注意：是顶点下标入队
                queue[rear] = node->adjVex;
                rear = (rear + 1) % MAX_VERTEX_NUM;
            }

            node = node->next; // 取下一个边表结点
        }
    }

    return;
}

// 主函数————————————————————
int main()
{
    use_example(); // 使用示例

    return 0;
}