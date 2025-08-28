/*
C++中，std::unordered_map的功能相当于哈希映射，顾名思义，它存储的简直对不按照
任何排序顺序来排列，它根据键的哈希值将键值分配到不同的bucket中，这样可以
更快地通过键直接访问元素
*/

#include <string>
#include <unordered_map>
#include <iostream>

std::unordered_map<int, long> umap2;

int fib(int n)
{
    if (n <= 1)
    {
        return n;
    }

    if (umap2.count(n))
    {
        return umap2[n];
    }

    else 
    {
        return umap2[n] = fib(n-1) + fib(n-2);
    }
}

int main()
{
    std::unordered_map<std::string, int> umap;

    umap["apple"] = 10;
    umap["mango"] = 20;
    umap["cherry"] = 30;

    // for (auto it:umap) 
    // {
    //     std::cout <<it.first << ' ' << it.second;
    // }

    std::cout << umap.count("apple");
    
}



