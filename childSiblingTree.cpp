#include <cstddef>
#include <vector>
#include <iostream>
#include <stdexcept>

template<typename T>
struct TreeNode
{
    T data;
    TreeNode<T>* firstChild;
    TreeNode<T>* nextSibling;

    TreeNode(const T& val) : data(val),firstChild(nullptr),nextSibling(nullptr) {}
};

template <typename T>
class Tree
{
private:
    TreeNode<T>* root;

public:

    Tree() :root(nullptr) {}

    Tree(const Tree<T>& other)
    {
        root = copy(other.root);
    }

    ~Tree()
    {
        destroy(root);
    }

    void destroy(TreeNode<T>* node)
    {
        if(!node) return;
        destroy(node->firstChild);
        destroy(node->nextSibling);
        delete node;
        node->nextSibling = nullptr;
        node->firstChild = nullptr;
    }

    TreeNode<T>* copy(TreeNode<T>* node)
    {
        if(!node) return nullptr;

        TreeNode<T>* newNode = new TreeNode<T>(node->data);
        newNode->firstChild = copy(node->firstChild);
        newNode->nextSibling = copy(node->nextSibling);

        return newNode;
    }

    void addChild(TreeNode<T>* parentNode,const T& val)
    {
        if(!parentNode) ;

        TreeNode<T>* newNode = new TreeNode<T>(val);

        if(!parentNode->firstChild)
        {
            parentNode->firstChild = newNode;
        }
        else
        {
            TreeNode<T>* sibling = parentNode->firstChild;
            while(sibling)
            {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = newNode;
        }
    }

    int getHeight(TreeNode<T>* node)
    {
        if(!node)
        {
            return 0;
        }

        int maxHeght = 1;
        TreeNode<T>* chileNode = node->firstChild;
        while (chileNode) 
        {
            int childHeight = getHeight(childHeight);
            maxHeght = (maxHeght > childHeight) ? maxHeght : childHeight;
            chileNode = chileNode->nextSibling;
        }

        return maxHeght;
    }
    
    TreeNode<T>* findParent(TreeNode<T>* currentNode,TreeNode<T>* childNode) // currentNode 可以取为root指针
    {
        if(!currentNode || currentNode == childNode )
        {
            return nullptr;
        }

        TreeNode<T>* child = currentNode->firstChild;
        while(child)
        {
            if(child == childNode)
            {
                return currentNode;
            }

            TreeNode<T>* result = findParent(child->firstChild, childNode);
            if(result)
            {
                return result;
            }

            child = child->nextSibling;
        }
        return nullptr;
    }
    
};

