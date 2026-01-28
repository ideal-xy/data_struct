#include <algorithm>
#include <cmath>
#include <cstdlib>
/*
In this file,we will eatablish AVL tree
*/
struct TreeNode
{
    int value; // 节点的值
    int height; // 节点高度
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int x) : value(x) {}
};

class AvlTree
{
private:
    TreeNode* root;

public:
    int height(TreeNode* node)
    {
        return node == nullptr ? -1 : node->height;
    }

    void updateHeight(TreeNode* node)
    {
        node->height = std::max(height(node->left),height(node->right)) + 1;
    }

    /*
    节点的平衡因子（balance factor）定义为节点左子树的高度减去右子树的高度，同时规定空节点的平衡因子为 
    我们同样将获取节点平衡因子的功能封装成函数，方便后续使用：
    */

    int balancefactor(TreeNode* node)
    {
        if (node == nullptr)
        {
            return 0;      
        }

        return height(node->left) - height(node->right);
    }

    /*
    我们把平衡因子绝对值大于1的节点称为失去平衡的节点
    */
    TreeNode* rightRotate(TreeNode* node)
    {
        TreeNode* child = node->left;
        TreeNode* grandChild = child->right;
        /*
        以child为原点，把node向右旋转
        */
        child->right = node;
        node->left = grandChild;
        updateHeight(node);
        updateHeight(child);

        return child;
    } // 我们返回的是旋转后子树的根节点，原来这个子树的根节点是node

    TreeNode* leftRotate(TreeNode* node)
    {
        TreeNode* child = node->right;
        TreeNode* grandChld = child->left;
        
        child->left = node;
        node->right = grandChld;

        return child;
    }
    /*
    左旋大致是要应付这样的情况：可以观察到node1是失衡的节点
    其左右子树的特点是右边深左边浅，于是需要对node1进行左旋操作
    node3的右子树是不用动的，但是其左子树可能是nullptr也有可能是非空的
    但是不管怎么样，都需要把转移到即将被左旋的node1的右子树上
    之所以是右子树是因为左子树已经有节点了（也有可能没有）

            node1
      node2         node3
                node4     node5
                            node6
    
    */

    TreeNode* rotate(TreeNode* node)
    {
        int balancFactor = balancefactor(node);
        if (std::abs(balancFactor) <= 1)
        {
            return node;
        }

        if (balancFactor > 1)
        {
            if (balancefactor(node->left) >= 0)
            {
                return rightRotate(node);
            }
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        else {
            if (balancefactor(node->right) <= 0)
            {
                leftRotate(node);
                return node;
            }
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
    }

    TreeNode* insertHepler(TreeNode* root,int val)
    {
        if (root == nullptr)
        {
            return new TreeNode(val);
        }

        if (val < root->value)
        {
           root->left = insertHepler(root->left, val);
        }
        if (val > root->value)
        {
            root->right = insertHepler(root->right, val);
        }
        else {
            return root;
        }
        updateHeight(root);
        return rotate(root);
    }
    

};


