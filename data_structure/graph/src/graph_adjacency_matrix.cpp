// 头文件————————————————————
#include <iostream>

// 命名空间————————————————————
using namespace std;

// 宏————————————————————
#define MAX_VERTEX_NUM 5 // 最大顶点数

// 自定义数据类型————————————————————
// 邻接矩阵：
// 顶点数据类型
// 可使用结构体记录其他信息
typedef int VertexType;

// 边数据类型
// 若是有权图，则为浮点型
typedef int EdgeType;

// 图的邻接矩阵
typedef struct
{
    int vexNum;                                     // 顶点数
    int edgeNum;                                    // 边数
    VertexType vexs[MAX_VERTEX_NUM];                // 顶点表
    EdgeType edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 边表 邻接矩阵
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
// 空间复杂度：O(1)。未使用额外辅助空间
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
        graph.vexs[i] = i; // 顶点序号/数据为下标：0，1，2，3，4
    }

    // 初始化边表
    //  0表示无边，1表示有边
    // 注意：无向图的1条边，在邻接矩阵中需要赋值2次
    graph.edges[0][1] = 1;
    graph.edges[1][0] = 1;

    graph.edges[0][2] = 1;
    graph.edges[2][0] = 1;

    graph.edges[1][3] = 1;
    graph.edges[3][1] = 1;

    graph.edges[2][3] = 1;
    graph.edges[3][2] = 1;

    return;
}

// 深度优先遍历1
// 时间复杂度：依据存储结构
// ：遍历点数×查找每点的邻接点的时间 = O(v×v) = O(v²)。v为点数（理解：遍历每一行）
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
    cout << graph.vexs[i] << " "; // 访问顶点
    g_visited[i] = true;          // 已访问标志置位

    // 对顶点i的邻接顶点j：若未访问，则递归进行深度优先遍历2
    for (int j = 0; j < graph.vexNum; ++j) // 注意循环终止条件
    {
        if (graph.edges[i][j] == 1 && g_visited[j] == false)
        {
            dfs(graph, j);
        }
    }

    return;
}

// 广度优先遍历1
// 时间复杂度：依据存储结构
// ：遍历点数×查找每点的邻接点的时间 = O(v×v) = O(v²)。v为点数（理解：遍历每一行）
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

    cout << graph.vexs[i] << " "; // 访问顶点
    g_visited[i] = true;          // 已访问标志置位

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

        // 对顶点i的邻接顶点j：若未访问，则迭代进行广度优先遍历2
        for (int j = 0; j < graph.vexNum; ++j) // 注意循环终止条件
        {
            if (graph.edges[i][j] == 1 && g_visited[j] == false)
            {
                cout << graph.vexs[j] << " "; // 访问顶点
                g_visited[j] = true;          // 已访问标志置位

                // 顶点下标入队
                // 注意：是顶点下标入队
                queue[rear] = j;
                rear = (rear + 1) % MAX_VERTEX_NUM;
            }
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