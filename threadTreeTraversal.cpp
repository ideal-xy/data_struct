/*
这一节我们实现中序线索二叉树的遍历，值得注意的是，我们不再特别特别需要头节点，因为我们已经实现了二叉树的线索化
*/

#include <iostream>

template <typename T> struct ThreadNode 
{
    T data;
    int ltag, rtag;
    ThreadNode<T> *lchild;
    ThreadNode<T> *rchild;
};

template <typename T> ThreadNode<T> *FirstNode(ThreadNode<T> *p) 
{
    while (p->ltag == 0) 
    {
        p = p->rchild;
    }
    return p;
}

template <typename T> ThreadNode<T> *NextNode(ThreadNode<T> *p) 
{
  if (p->rtag == 0) 
  {
      return FirstNode(p->rchild);
  }
  return p->rchild;
}

template <typename T> ThreadNode<T> LastNode(ThreadNode<T> *p) 
{
  while (p->rtag == 0) 
  {
    p = p->rchild;
  }
  return p;
}

template <typename T> ThreadNode<T> preNode(ThreadNode<T> *p) 
{
  if (p->ltag == 0) 
  {
    return LastNode(p->lchild);
  }
  return p->lchild;
}

template <typename T> void visit(ThreadNode<T> *node) 
{
  std::cout << node->data << std::endl;
}

template <typename T>
void inOrder(ThreadNode<T> *any_p) //  这里可以传入任意一个节点
{
  for (ThreadNode<T> *p = FirstNode(any_p); p != nullptr; p = NextNode(p)) 
  {
    visit(p);
  }
}

/*

格式化后的代码好丑......

*/
