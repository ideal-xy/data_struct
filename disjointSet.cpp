class UnionSet
{
private:
    int *father;
    int* rank;

public:
    UnionSet(int n)
    {
        father = new int[n];
        rank = new int[n];
        for (int i = 0;i < n;++i)
        {
            father[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionSet()
    {
        delete [] father;
        delete [] rank;
    }

    int find_root(int x)
    {
       return x == father[x] ? x : (father[x] = find_root(x)); //  注意赋值表达是有返回值的
    }


    void merge(int i,int j) // 把前者合并到后者所在的树上
    {
        father[find_root(i)] = find_root(j);
    }

    /*
    我们应该把简单的树往复杂的树上合并，而不是相反。因为这样合并后，到根节点距离变长的节点个数比较少。
    我们用一个数组rank[]记录每个根节点对应的树的深度（如果不是根节点，其rank相当于以它作为根节点的子树的深度）。
    一开始，把所有元素的rank（秩）设为1。合并时比较两个根节点，把rank较小者往较大者上合并。
    */

    void merge_by_rank(int x,int y)
    {
        int i = find_root(x);
        int j = find_root(y);

        if(rank[i] <= rank[j])
        {
            father[i] = j;
        }

        else 
        {
            father[j] = i;
        }

        if(rank[i] == rank[j] && i != j)
        {
            rank[j] ++ ; // 前面已经决定了秩相等的时候怎么合并
        }
        
    }

};