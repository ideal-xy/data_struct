
/*
首先要有几个关键认知：
1:传统的二叉链表存储二叉树枝只能体现一种父子关系，但是不可以得到每一个节点的前驱或者后继
2:在含有n个节点的二叉树中，有n-1条边，n+1个空指针（叶节点的格式比满节点的个数始终多1）
3:我们可以考虑把这n+1个空指针用起来，存储节点的前驱和后继信息
4:我们使用如下的方式：
         1:原本为空的右指针改为指向该节点在中序遍历序列中的后继（在访问此节点之后即将要访问的节点）
         2:原本为空的左指针改为指向该节点在中序遍历序列中的前驱（在访问此节点之前访问的节点）
         3.线索二叉树的节点结构发生变化，增加两个标识域，用于确认指针是指向前驱/后继，还是左/右子代
*/
template<typename T>
struct ThreadNode
{
    T data;
    int ltag,rtag;
    ThreadNode<T> *lchild;
    ThreadNode<T> *rchild;
};

// 我们约定指针p指向当前正在访问的节点，pre指向p的前驱
template<typename T>
void InTread(ThreadNode<T> *p,ThreadNode<T> *pre)
{
    if (p != nullptr) 
    {
        InTread(p->lchild, pre);
        // 当从左子树递归返回，即将访问p节点时，执行以下操作：
        if(p->lchild == nullptr)
        {
            p->lchild = pre; //  注意这一行，如果我们访问一个节点的左孩子发现其为空，那么就把他的左指针指向pre
            p->ltag = 1;
        }
        // 在中序遍历中，当一个节点p没有左孩子时，它的前驱节点正是那个在它之前被访问的节点，也就是pre。
        // 这行代码就把这个“断掉”的左指针利用起来，指向了它的前驱。

        if (pre != nullptr && pre->rchild == nullptr)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        // 当我们访问到节点p时，我们知道pre是刚刚被访问的节点。
        // 如果pre没有右孩子，那么根据中序遍历的定义，它的后继节点正好就是当前我们正在访问的p。
        // 所以这行代码就把pre的“断掉”的右指针利用起来，指向了它的后继p。

        // 我们已经完成了对节点p的访问和线索化处理，
        // 在即将进入p的右子树之前，p就变成了“刚刚被访问过的节点”。
        // 所以我们需要更新pre，让它指向p。这样，当递归进入右子树时，
        pre = p;
        InTread(p->rchild, pre);
    }
}

// 但是最后一个pre节点是没有处理的
template<typename T>
void createThreadTree(ThreadNode<T>* root)
{
    ThreadNode<T>* pre = nullptr;
    if(root != nullptr)
    {
        InTread(root, pre);
        pre->rchild = nullptr;
        pre->rtag = 1;
    }
}