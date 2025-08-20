#include <iostream>
#include <queue>
#include <binaryTree.cpp>

using namespace std;

vector<int> levelOrder(binaryNode<int> *root)
{
    linkedBinaryTree<int> tree;
    queue<binaryNode<int> *> q;
    q.push(root); // 首先让根节点入队
    vector<int> result;
    while (!q.empty())
    {
        binaryNode<int> *current = q.front();
        q.pop();
        result.push_back(current->element);
        if (current->leftChild != nullptr)
        {
            q.push(current->leftChild);
        }
        if (current->rightChild != nullptr)
        {
            q.push(current->rightChild);
        }
    }
    return result;
}

vector<int> inOrder(binaryNode<int> *root)
{
    stack<binaryNode<int> *> s;
    binaryNode<int> *cur_ptr = root;
    vector<int> result;
    while (cur_ptr != nullptr || !s.empty())
    {
        if (cur_ptr != nullptr)
        {
            s.push(cur_ptr);
            cur_ptr = cur_ptr->leftChild;
        }
        else
        {
            result.push_back(s.top()->getElement());
            s.pop();
            cur_ptr = s.top()->rightChild;
        }
    }
    return result;
}

vector<int> preOrder(binaryNode<int> *root)
{
    stack<binaryNode<int> *> s;
    binaryNode<int> *cur_ptr = root;
    vector<int> result;
    while (cur_ptr != nullptr || !s.empty())
    {
        if (cur_ptr != nullptr)
        {
            result.push_back(cur_ptr->element);
            s.push(cur_ptr);
            cur_ptr = cur_ptr->leftChild;
        }
        else
        {
            s.pop();
            cur_ptr = s.top();
            cur_ptr = cur_ptr->rightChild;
        }
    }
}