#include <iostream>
#include <algorithm>

template <typename T>
struct binaryNode
{
    T element;
    binaryNode<T>* leftChild;
    binaryNode<T>* rightChild;

    binaryNode(const T& theElement) 
    {
        leftChild = rightChild = nullptr;
        element = theElement;
    }
    binaryNode(const T& theElement,binaryNode* leftChild,binaryNode* rightChild)
    {
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->element = theElement;
    }

    T getElement() {return element;}

};

template <typename T>
void visit(binaryNode<T>* x)
{
    std:cout << x->element;
}

template <typename T>
void preOrder(binaryNode<T>* t)
{
    visit(t);
    preOrder(t->leftChild);
    preOrder(t->rightChild);
}

template <typename T>
void inOrder(binaryNode<T>* t)
{
    inOrder(t->leftChild);
    visit(t);
    inOrder(t->rightChild);
}

template <typename T>
void postOrder(binaryNode<T>* t)
{
   postOrder(t->leftChild);
   postOrder(t->rightChild);
   visit(t);
}

template <typename T>
void infix(binaryNode<T>* t)
{
    if (t != nullptr)
    {
        std::cout << '(';
        infix(t->leftChild);
        std::cout << t->element;
        infix(t->rightChild);
        std::cout << ')';
    }
}

template <typename T>
void levelOrder(binaryNode<T>* t)
{
    std::queue<binaryNode<T>*> q;
    while (t != nullptr)
    {
        visit(t);
        if (t->leftChild != nullptr)
        {
            q.push(t->leftChild);
        }
        if (t->rightChild != nullptr)
        {
            q.push(t->rightChild);
        }

        try{t = q.front();}
        catch(emptyQueue){return;}

        q.pop();

        }
}

template <typename E>
class linkedBinaryTree{

private:
    binaryNode<E>* root;
    int treeSize;

    static void (*visit)(binaryNode<E>*);

    static void valid(binaryNode<E>* t)
    {
        if (t == nullptr)
        {
            throw illegalRoot();
        }
    }

    static void preOrder(binaryNode<E>* t)
    {
        if (t != nullptr)
        {
            visit(t);
            preOrder(t->leftChild);
            preOrder(t->rightChild);
        }
    }
    
    static void inOrder(binaryNode<E>* t)
    {
        if (t != nullptr)
        {
            inOrder(t->leftChild);
            visit(t);
            inOrder(t->rightChild);
        }
    }

    static void dispose(binaryNode<E>* t) {delete t;}

    static void levelOrder(binaryNode<E>* t)
    {
        if (t == nullptr) return;

        std::queue<binaryNode<E>*> q;
        q.push(t);

        while (!q.empty())
        {
            binaryNode<E>* current = q.front()
            q.pop()
            
            visit(current);

            if (t->leftChild != nullptr)
            {
                q.push(t->leftChild);
            }

            if (t->rightChild != nullptr)
            {
                q.push(t->rightChild);
            }
        }


    }

public:
    linkedBinaryTree() {root = nullptr;treeSize = 0;}

    ~linkedBinaryTree() { erase();}

    bool emptyz() {return treeSize == 0;}

    int size() const {return treeSize;}

    void preOrder(void (*theVisit)(binaryNode<E>*))
    {
        visit = theVisit;
        preOrder(root)
    }

    void inOrder(void (*theVisit)(binaryNode<E>*))
    {
        visit = theVisit;
        inOrder(root);
    }

    void levelOrder(void (*theVisit)(binaryNode<E>*))
    {
        visit = theVisit;
        levelOrder(root);
    }

    void erase()
    {
        postOrder(dispose);
        root = nullptr;
        treeSize = 0;
    }

};

