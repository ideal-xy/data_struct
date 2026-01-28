/*
这一节，我们给出中序遍历的迭代写法。
*/
#include<stack>
#include<vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
访问顺序为:左-根-右
*/
std::vector<int> inOrderTraversal(TreeNode* root)
{
    std::vector<int> visit;
    std::stack<TreeNode*> stk;
    TreeNode* cur;

    while(cur != nullptr || !stk.empty())
    {
        while(cur != nullptr)
        {
            stk.push(cur);
            cur = cur->left;
        } // 一条道走到黑

        cur = stk.top();
        stk.pop();
        visit.push_back(cur->val);

        cur = cur->right;
    }

    return visit;
}


/*
访问顺序为：根-左-右
*/
std::vector<int> preOrder(TreeNode* root)
{
    std::vector<int> visit;
    if (root == nullptr) { return visit;};

    std::stack<TreeNode*> stk;
    stk.push(root);

    while(!stk.empty())
    {
        TreeNode* cur = stk.top();
        stk.pop();
        visit.push_back(cur->val);


        if( cur->right != nullptr ) { stk.push(cur->right); };
        if( cur->left != nullptr ) { stk.push(cur->left); };

        return visit;
    }
    
    return visit;
}


std::vector<int> postOrder(TreeNode* root)
{
    std::vector<int> visit;
    std::stack<TreeNode*> s;
    TreeNode* cur = root;
    TreeNode* lastvist = nullptr;

    while(cur != nullptr || !s.empty())
    {
        while (cur != nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }

        TreeNode* topNode = s.top();

        if (topNode->right == nullptr || topNode->right == lastvist)
        {
            visit.push_back(topNode->val);
            lastvist = topNode;
            s.pop();
        }
        else
        {
            cur = topNode->right;
        }    
    }

    return visit;

}
