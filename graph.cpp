/*
* 实现无向图
*/

#include <cstddef>
#include <utility>
#include <vector>
class Graph
{
private:
    std::vector<int> vertices;
    std::vector<std::vector<int>> adjMat;

public:
    /*
    * edges：里面存储的是所有的边关系
    */
    Graph(const std::vector<int>& vectices,const std::vector<std::pair<int, int>>& edges)
    {
        for (int val : vertices)
        {
            addVertex(val);
        }

        for (const std::pair<int, int>& edge : edges)
        {
            addEdge(edge.first,edge.second);
        }
    }

    size_t size() const
    {
        return vertices.size();
    }

    void addVertex(int val) 
    {
        int n = size();
        vertices.push_back(val); // 添加一行
        adjMat.emplace_back(std::vector<int>(n,0)); // 添加一列
        for (std::vector<int>& row : adjMat)
        {
            row.push_back(0);
        }
        // 在addEdge函数中建立起边的关系
    }

    void addEdge(int i,int j)
    {
        // 略去越界检查
        /* ··· */
        adjMat[i][j] = adjMat[j][i] = 1;
        
    }



    
};