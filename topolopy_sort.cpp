/*
* 图G存在拓扑序当且仅当其是有向无环图（DAG）
*/


#include <iostream>
#include <list>
#include <queue>
#include <vector>

/*
* indegree是每个节点的入度数组
* 为了不破坏输入，在代码中会先拷贝这个数组
*/

bool toposort(int n,const std::vector<std::list<int>>& graph,
              const std::vector<int>& indegree)
{
    std::vector<int> topoOrder(n);
    std::queue<int> que;

    auto degree = indegree;

    for (auto i : degree) // 找到所有的入度为0的节点
    {
        if (degree[i] == 0) que.push(i);
    }

    while (!que.empty()) 
    {
        int u = que.front();
        que.pop();
        topoOrder.push_back(u);

        for (auto v : graph[u])
        {
            if (--degree[v] == 0) que.push(v);
        }
    }

    return (topoOrder.size() == n) ? true : false;
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n,m;
    std::cin >> n >> m;

    std::vector<std::list<int>> graph(n+1);
    std::vector<int> indegree(n+1,0);

    for (int i=0;i < m;i++)
    {
        int u,v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }

}

/*
* 我们还可以使用dfs的方法来判断一个有向图是否有环
* dfs过程中的递归路径上其他的节点必定是与u连通的，
* 如果这条路径不存在环的话，那么一定不会在递归路径中遇到已经被染色的节点，
* 反之则这条路径存在环。
*/

std::vector<std::vector<int>> graph;
std::vector<int> state;

bool dfs(int i)
{
    state[i] = 1;

    for (auto v : graph[i])
    {
        if (state[v] == 1) return true;
        if (state[v] == 0)
        {
            if (dfs(v)) return true;
        }
    }

    state[i] = 2;
    return false;
}

