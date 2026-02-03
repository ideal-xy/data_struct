/*
* 使用回溯算法解决全排列问题
*/  

// 输入一个整数数组，数组中可能包含重复元素，返回所有不重复的排列。

#include <unordered_set>
#include <vector>
#include <iostream>


void dfs1(std::vector<int>& nums,std::vector<std::vector<int>>& ans,std::vector<bool>& used,std::vector<int>& path)
{
    int size = nums.size();
    if (path.size() == size)
    {
        ans.push_back(path);
        return;
    
    }
    for (int i = 0;i < size;i++)
    {
        if (used[i]) continue;

        used[i] = true;
        path.push_back(nums[i]);
        dfs1(nums, ans, used, path);
        path.pop_back();
        used[i] = false;
        
        
    }
}


int main1()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<int> nums;
    
    int x;
    while (std::cin >> x) 
    {
        nums.push_back(x);
    }

    std::vector<std::vector<int>> ans;
    std::vector<bool> used;
    used.resize(nums.size(),false);
    std::vector<int> path;

    dfs1(nums,ans,used,path);

    for(auto& vec : ans)
    {
        for (auto val : vec)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

void dfs2(std::vector<int>& path,std::vector<int>& nums,std::vector<bool>& used,std::vector<std::vector<int>>& ans)
{
    if (path.size() == nums.size())
    {
        ans.push_back(path);
        return;
    }

    std::unordered_set<int> duplicated;
    
    for (int i = 0;i < nums.size();i++)
    {
        if (used[i] == true || duplicated.find(nums[i]) != duplicated.end()) continue;

        duplicated.emplace(nums[i]);
        used[i] = true;
        path.push_back(nums[i]);

        dfs2(path,nums,used,ans);

        used[i] = false;
        path.pop_back();
    }
}

int main2()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<int> nums;
    
    int x;
    while (std::cin >> x) 
    {
        nums.push_back(x);
    }

    std::vector<std::vector<int>> ans;
    std::vector<bool> used;
    used.resize(nums.size(),false);
    std::vector<int> path;

    dfs2(path,nums,used,ans);

    for(auto& vec : ans)
    {
        for (auto val : vec)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}


int main()
{
    main2();
    std::cout << "hello" << std::endl;
    return 0;
}

