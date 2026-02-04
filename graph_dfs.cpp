/*
* 图的深度有限搜索
*/
#include <iostream>
#include <vector>


void dfs(const std::vector<std::vector<int>>& graph,std::vector<std::vector<int>>& res,std::vector<int>& path,int cur,int n)
{
    if (cur == n)
    {
        res.push_back(path);
        return;
    }

    for (int i = 1;i <= n;i++)
    {
        if (!graph[cur][n]) continue;

        path.push_back(i);
        dfs(graph, res, path, i, n);
        path.pop_back();
    }
}

int main()
{
    int n;
    std::cin >> n;
    int s,t;
    std::vector<std::vector<int>> graph(n+1,std::vector<int>(n+1,0));
    while (std::cin >> s >> t)
    {
        graph[s][t] = 1;
    }

    std::vector<std::vector<int>> res;
    std::vector<int> path;

    dfs(graph, res, path, 1,n);

}