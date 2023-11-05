#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::cout;
using std::endl;
using std::pair;
using std::sort;
using std::unordered_map;
using std::vector;

// 并查集类
class DisjointSet
{
public:
    // 构造并查集
    // 参数：等价关系元素值的大小/范围，等价关系集合向量
    DisjointSet(const int &e_q_s, const vector<pair<int, int>> &e_r_v) : eq_rel_size(e_q_s), eq_rel_vec(e_r_v)
    {
        // 1. 初始化元素父节点向量，大小是等价关系元素值的大小/范围，每个元素的父节点约定为自身
        this->parent_vec.resize(this->eq_rel_size); // 元素父节点的向量的大小是等价关系元素值的大小/范围
        for (int i = 0; i < this->eq_rel_size; ++i)
        {
            parent_vec[i] = i;
        }

        // 2. 初始化元素深度向量，大小是等价关系元素值的大小/范围，每个元素作为根节点约定为0即第0层
        // 合并操作依据树的深度优化，即优先将深度大的树的根挂接到深度小的树的根
        this->depth_vec.resize(this->eq_rel_size, 0);

        // 3. 按照字典序排序等价关系集合向量
        sort(this->eq_rel_vec.begin(), this->eq_rel_vec.end());

        // 4. 合并集合
        for (const auto &eq_rel_pair : eq_rel_vec) // 对每一个等价关系集合，如：{1, 2}
        {
            // 4.1 分别查找两关系元素的根节点
            int first_root = this->find_parent(eq_rel_pair.first);
            int second_root = this->find_parent(eq_rel_pair.second);

            // 4.2 依据根节点情况合并挂接
            if (first_root == second_root) // 相等不操作
            {
                continue;
            }
            else // first_root != second_root
            {
                if (this->depth_vec[first_root] < this->depth_vec[second_root]) // 优先将深度大的树的根挂接到深度小的树的根
                {
                    this->parent_vec[first_root] = second_root;
                }
                else if (this->depth_vec[first_root] > this->depth_vec[second_root])
                {
                    this->parent_vec[second_root] = first_root;
                }
                else // == 树的深度相等，约定将第二个根挂接到第一个根，第一个根的深度加深一层
                {
                    this->parent_vec[second_root] = first_root;
                    ++this->depth_vec[first_root];
                }
            }
        }

        // 5. 构建结果
        unordered_map<int, vector<int>> root_vec{}; // 哈希表，记录 根节点值-该根节点下的元素向量，一个向量是一棵新树
        for (int i = 0; i < this->eq_rel_size; ++i) // 遍历元素值
        {
            int root = this->find_parent(i); // 取根节点
            root_vec[root].push_back(i);
        }

        for (const pair<int, vector<int>> &pair_tree : root_vec) // 遍历每棵树，加入到结果集
        {
            this->disjoint_set.insert(this->disjoint_set.begin(), pair_tree.second);
        }
    }

    // 获取并查集
    inline vector<vector<int>> get_disjoint_set() const
    {
        return this->disjoint_set;
    }

    // 打印并查集
    inline void print_disjoint_set() const
    {
        cout << "并查集: " << endl;
        for (const vector<int> set : this->disjoint_set)
        {
            for (const int num : set)
            {
                cout << num << " ";
            }
            cout << endl;
        }

        return;
    }

private:
    const int eq_rel_size;             // 等价关系元素值的大小/范围
    vector<pair<int, int>> eq_rel_vec; // 等价关系集合向量

    vector<int> parent_vec; // 记录元素父节点的向量
    vector<int> depth_vec;  // 记录元素深度的向量，约定元素值/树的根是索引，根的深度从0、1往上加

    vector<vector<int>> disjoint_set; // 并查集，并查集类固有的本质内容

    // 递归查找当前元素值的根节点
    int find_parent(int x)
    {
        // 1. 递归逻辑
        // 如果不是，parent[x] != x，则使用当前节点的父节点作为参数，调用当前函数，递归继续找爷节点：find_parent(parent[x])
        // 把找到的根节点记录在查找路径中每个节点的 元素父节点的向量 中：parent_vec[x] =
        // 相当于把该些节点，都挂接到根节点上，树变得扁平

        // 即路径压缩优化：在并查集中，每个元素都有一个父节点，通常在查找操作中，我们会沿着父节点链一直向上找到根节点
        // 这个过程就是在寻找元素所在集合的过程。但是，在普通的查找操作中，路径的长度可能会很长，导致后续的查找操作效率较低。
        // 路径压缩是一种优化技术，它的思想是：当我们在进行查找操作时，不仅找到元素所在集合的根节点，
        // 还顺便将经过的所有节点的父节点都设置为根节点。这样，当下次再次查找这些节点时，路径就会更短，查找效率就会更高。

        // 如：1为根节点，23为子节点，有1 - 2 - 3的三层树，从叶节点3开始找，找到1根节点，然后依次递归返回把2、3的根节点设置为1
        // 成为1 - 2，1 - 3的两层树
        if (parent_vec[x] != x)
        {
            parent_vec[x] = find_parent(parent_vec[x]);
        }

        // 1. 递归出口
        // 如果x的父节点是自己，说明它是根节点，返回
        // parent_vec[x] == x
        // 把return放在if会有到不了该条件if的警告：control reaches end of non-void function [-Wreturn-type]
        return parent_vec[x];
    }
};

int main()
{
    const int eq_rel_size = 9;                                                                          // 等价关系元素值的大小/范围
    const vector<pair<int, int>> eq_rel_vec = {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {0, 2}, {4, 6}, {0, 8}}; // 等价关系集合向量，内容必须是0~ eq_rel_size - 1（并查集类的逻辑定义了）

    DisjointSet ds(eq_rel_size, eq_rel_vec); // 并查集对象
    ds.print_disjoint_set();                 // 打印并查集

    return 0;
}