#include <cstddef>
#include <algorithm>
#include <iostream>



struct HNode
{
    int weight;
    HNode* lchild;
    HNode* rchild;
};

/*
这个函数帮助我们找到当前森林中权重最小的两个节点
*/
void selectMin(HNode* forest[],int n,int& min1_idx,int& min2_idx)
{
    min1_idx = -1;
    min2_idx = -1;

    for (int i = 0; i < n; ++i) 
    {
        if (forest[i] != nullptr) 
        {
            min1_idx = i;
            break;
        }
    }
    for (int i = 0; i < n; ++i) 
    {
        if (forest[i] != nullptr && i != min1_idx) 
        {
            min2_idx = i;
            break;
        }
    }

    /*
    上面的循环让我们找到前俩个非空节点，如果min2_idx还是-1的话，说明这个
    数组中只有一个非空节点了
    */
    if (min2_idx == -1) return;

    if (forest[min1_idx]->weight > forest[min2_idx]->weight) 
    {
        std::swap(min1_idx, min2_idx);
    } // 确保min1_idx的权小于另外一个

    for (int i = 0; i < n; ++i) 
    {
        if (forest[i] != nullptr && i != min1_idx && i != min2_idx) 
        {
            if (forest[i]->weight < forest[min1_idx]->weight) 
            {
                min2_idx = min1_idx; 
                min1_idx = i;
            } else if (forest[i]->weight < forest[min2_idx]->weight) 
            {
                min2_idx = i;
            }
        }
    }
    
}

HNode* createHuffmanTree(int arr[],int n)
{
    HNode* forest[n];
    HNode* root = nullptr;
    int root_index = 0;

    for(int i=0;i < n;++i) 
    {
        HNode* temp;
        temp = static_cast<HNode*>(::operator new(sizeof(HNode)));
        temp->weight = arr[i];
        temp->lchild = temp->rchild = nullptr;
        forest[i] = temp;
    }

    /*
    通过上面的循环，我们创建了一个森林，这是我们构建霍夫曼树的第一步
    */

    if(n == 1)
    {
        return forest[n];
    }

    for(int i=0; i < n-1;++i)
    {
        int min1_idx = -1;
        int min2_idx = -1;

        selectMin(forest, n, min1_idx,min2_idx);

        if(min2_idx == -1) // 这说明只剩一个节点了
        {
            root_index = min1_idx;
            break;
        }
        
        HNode* min1_node = forest[min1_idx];
        HNode* min2_node = forest[min2_idx];

        HNode* parent;
        parent = static_cast<HNode*>(::operator new(sizeof(HNode)));
        parent->weight = min1_node->weight + min2_node->weight;
        parent->lchild = min1_node;
        parent->rchild = min2_node;

        forest[min1_idx] = parent;
        forest[min2_idx] = nullptr;
        
    }

    return forest[root_index]; // 返回根节点
}

int calculateWPL(HNode* root,int len)
{
    if(root == nullptr)
    {
        return 0;
    }
    else if (root->lchild == nullptr && root->rchild == nullptr) 
    {
        return root->weight * len;
    }
    else 
    {
        return calculateWPL(root->lchild, len + 1) + calculateWPL(root->rchild, len + 1);

    }
}

void huffmanCoding(HNode* root,int len,int arr[])
{
    if(root == nullptr)
    {
        return;
    }

    if(root != nullptr)
    {
        if(root->lchild == nullptr && root->rchild == nullptr) //  遇到叶节点的处理方式
        {
            std::cout << "权重为" << root->weight << "的字符的huffman编码为" << std::endl;
            for(int i=0;i < len;++i)
            {
                std::cout << arr[i] << "-";
            }
        }

        else 
        {
        arr[len] = 1;
        huffmanCoding(root->lchild, len + 1, arr);

        arr[len] = 0;
        huffmanCoding(root->rchild, len + 1, arr);
        }
    }
}
