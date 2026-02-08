/*
* 岛屿问题4:孤岛的总面积
*/
#include <cstddef>
#include <vector>
#include <iostream>
#define NOT_OK(nextx,nexty) (nextx < 0 || nextx >= graph.size() || nexty < 0 || nexty >= graph[0].size())

void dfs(std::vector<std::vector<int>>& graph,int (*ptr)[2],int x,int y)
{
    if (graph[x][y] == 0) return;
    graph[x][y] = 0;
    for (int i = 0;i < 4;i++)
    {
        int nextx = x + ptr[i][0];
        int nexty = y + ptr[i][1];
        if (NOT_OK(nextx, nexty)) continue;
        dfs(graph, ptr, nextx,nexty);
    }
}

int main()
{
    std::cin.tie(nullptr)  ;
    std::ios::sync_with_stdio(false);
    int n,m;
    std::cin >> n >> m;

    int ptr[4][2] = {0,1,1,0,-1,0,0,-1};
    std::vector<std::vector<int>> graph(n,std::vector<int>(m,0));
    for (int i = 0;i < n;i++)
    {
        for (int j = 0;j < m;j++)
        {
            std::cin >> graph[i][j];
        }
    }

    for (int i = 1;i < n - 1;i ++)
    {
        dfs(graph, ptr,i, 0);
        dfs(graph, ptr,i, m-1);
    }

    for (int i = 0;i < m;i ++)
    {
        dfs(graph, ptr,0, i);
        dfs(graph, ptr,n-1, i);
    }

    int count = 0;
    for (int i = 0;i < n;i++)
    {
        for (int j = 0;j < m;j++)
        {
            if (graph[i][j] == 1) ++count;
        }
    }

    std::cout << count;
}