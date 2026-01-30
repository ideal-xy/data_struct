

/*
We will eatablish binary search tree in this file
Author : Xu Yan
Date : Nov 25,2025
*/
#include <cstddef>
struct TreeNode
{
    int value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int num):value(num) {}
};

class SearchTree
{
private:
    TreeNode* root;

    explicit SearchTree(int num) 
    {
        root = new TreeNode(num);
    }

public:
    TreeNode* search(int num)
    {
        TreeNode* cur = root;
        while (cur != nullptr)
        {
            if (cur->value < num)
            {
                cur = cur->right;
            }
            else if (cur->value > num) 
            {
                cur = cur->left;
            }
            else 
            {
                break;
            }
        }
        return cur;
    }

    /*
    Whether element of value can be inserrted is a problem
    */
    void insert(int num)
    {
        if (root == nullptr)
        {
            root = new TreeNode(num);
            return;
        }

        TreeNode* cur = root;
        TreeNode* father = nullptr;
        while (cur != nullptr)
        {
            if (cur->value == num)
            {
                return; 
            }
            father = cur;
            if (cur->value < num)
            {
                cur = cur->right;
            }
            else 
            {
                cur = cur->left;
            }
        }

        TreeNode* node = new TreeNode(num);
        if (father->value < num)
        {
            father->right = node;
        }
        else
        {
            father->left = node;
        }
    }

    void remove(int num)
    {
        if (root == nullptr)
        {
            return;
        }

        TreeNode* cur = root;
        TreeNode* father = nullptr;
        while (cur != nullptr)
        {
            if (cur->value == num)
            {
                break;
            }
            father = cur;
            if (cur->value < num)
            {
                cur = cur->right;
            }
            else 
            {
                cur = cur->left;
            }
        }

        if (cur == nullptr)
        {
            return;
        }

        if (cur->left == nullptr || cur->right == nullptr)
        {
            auto child = cur->left != nullptr ? cur->left : cur->right;
            if (cur != root)
            {
                if (father->left == cur)
                {
                    father->left = child;
                }
                else 
                {
                    father->right = child;
                }
            }
            else 
            {
                root = child;
            }
            delete cur;
        }
        else {
            TreeNode* tmp = cur->right;
            while (tmp->left != nullptr)
            {
                tmp = tmp->left;
            } 
            /*
            我们要找的节点是在右子树中最接近cur->value的元素，这个元素一定是大于cur->value
            且小于cur->right->value的
            我们要用这个替代cur->value
            但是直接替换过来的话，那个元素不久重复了吗而且那个元素旁边还有很多逻辑关系没有理清楚
            没事！我们有递归，递归太牛逼了卧槽
            */
            int tmpval = tmp->value;
            remove(tmpval);
            cur->value = tmpval;
        }
    }


    TreeNode* findMin(TreeNode* root)
    {
        while (root->left != nullptr)
            root = root->left;

        return root;
    }

    TreeNode* findMax(TreeNode* root)
    {
        while (root->right != nullptr)
            root = root->right;

        return root;
    }



    TreeNode* remove_2(TreeNode* root,int key)
    {
        if (root == nullptr) return nullptr; 

        if (key < root->value) root->left = remove_2(root->left, key);
        if (key > root->value) root->right = remove_2(root->right,key);

        // 找到了要删除的节点
        if (root->left == nullptr)
        {
            TreeNode* tmp = root->right;
            delete root;
            return tmp;
        }
        
        if (root->right == nullptr)
        {
            TreeNode* tmp = root->left;
            delete root;
            return tmp;
        }

        if (root->left != nullptr && root->right != nullptr)
        {
            TreeNode* successor = findMin(root->right);
            root->value = successor->value;
            root->right = remove_2(root->right, root->value);
        }

        return root;
    }

};




