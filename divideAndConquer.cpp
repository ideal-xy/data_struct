/*
* 这一节来看分治算法
* Q：给定一棵二叉树的preorder和inorder，从中恢复出二叉树（可以假设元素都不相同）
* 前序遍历：[ 根节点 | 左子树 | 右子树 ]
* 中序遍历：[ 左子树 | 根节点 ｜ 右子树 ]
*/

/*
* 有一个关键认识，根节点的右子节点是右子树的根节点，
* 根节点的左子节点是左子树的根节点
*/

/*
设当前树的根节点在preorder中的索引为i
设当前树的根节点在inorder中的索引为m
设当前树inorder中的索引区域记为[l,r]
那么，当前树根节点在preorder中的索引为i
      当前树的左子树的根节点在preorder中的索引为 i+1
      当前树的右子树的根节点在preorder中的索引为 i+1+(m-l)
      当前树根节点在inorder中的索引区间为[l,r]
      当前树的左子树在inorder中的索引为[l,m-1]
      当前树的右子树在inorder中的索引为[m+1,r]

      m-l的含义是左子树的节点数量

*/
#include <cstddef>
#include <unordered_map>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int val):val(val),left(nullptr),right(nullptr) {}

};

TreeNode* dfs(std::vector<int>& preorder,std::unordered_map<int, int>& inorder,int i,int l,int r)
{
    if (r - l < 0) return nullptr;

    TreeNode* root = new TreeNode(preorder[i]); // 构造当前树的根节点
    int m = inorder[preorder[i]]; // 中序遍历当前树的根节点索引

    root->left = dfs(preorder, inorder, i+1, l, m-1);
    root->right = dfs(preorder,inorder,i+1+m-l,m+1,r);

    return root;
}

TreeNode* build(std::vector<int>& preorder,std::vector<int>& inorder)
{
    std::unordered_map<int, int> inorderMap;
    int size = inorder.size();

    for (int i = 0;i < size;i++)
        inorderMap[inorder[i]] = i;

    TreeNode* root = dfs(preorder, inorderMap, 0, 0, size - 1);
    return root;
}






