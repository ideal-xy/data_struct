#include <iostream>
#include <algorithm>
#include <sstream>

template <typename T>
struct chainNode // 这个结构体描述的是链表的每一个节点
{
    T element;
    chainNode<T>* next;

    chainNode() {}
    chainNode(const T& element)
    {
        this->element = element;
    }
    chainNode(const T& element,chainNode<T>* next)
    {
        this->element = element;
        this->next  = next;
    }
};


template <typename T>
class chain
{
private:
    chainNode<T>* firstNode;
    int listSize;

public:
    chain(int initialCapacity)
    {
        if (initialCapacity < 1)
        {
            std::ostringstream s;
            s << "Initial capacity" << initialCapacity << "must be > 0" << '\n';
            throw illegalparameter(s.str());
        }
        firstNode = nullptr;
        listSize = 0;
    }

    chain(const chain<T>& theList)
    {
        listSize = theList.listSize;

        if (listSize == 0)
        {
            firstNode = nullptr;
            return;
        }

        chainNode<T>* sourceNode = theList.firstNode;
        firstNode = new chainNode<T>(sourceNode->element); 
        sourceNode = sourceNode ->next;
        chainNode<T>* targetNode = firstNode;
    
        while (sourceNode != nullptr)
        {
            targetNode->next = new chainNode<T>(sourceNode->element); // 第一次执行这行代码的时候实现了对firstNode指向的节点（头节点）的指针域的修改 在此之前还是空指针
            targetNode = targetNode ->next;
            sourceNode = sourceNode->next;
        }
        targetNode->next == nullptr;
    }

    ~chain()
    {
        while (firstNode != nullptr)
        {
            chainNode<T>* nextNode = firstNode ->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }

    T& get(int index) const
    {
        chainNode<T>* currentNode = firstNode;
        for(int i=0;i<index;++i)
        {
            currentNode = currentNode->next;
        }
        return currentNode->element;
    }
    
    void checkIndex(int index)
    {
        if (index <0 && index >=listSize){
            std::ostringstream s;
            s << "Initial capacity" << initialCapacity << "must be > 0" << '\n';
            throw illegalparameter(s.str());
        }
    }
    int getIndex(const T& element)
    {
        chainNode<T>* currentNode = firstNode;
        int index = 0;
        while (currentNode != nullptr && currentNode->element != element)
        {
            currentNode = currentNode->next;
            ++index;
        }

        if (currentNode == nullptr)
        {
            return -1;
        }
        return index;
        
    }

    void erase(int index)
    {
        checkIndex(index);
        chainNode<T>* deleteNode;

        if (index == 0)
        {
            deleteNode = firstNode;
            firstNode = firstNode->next;
        }
        else
        {
            chainNode<T>* p = firstNode;
            for (int i = 0;i<index -1;++I)
            {
                p = p->next;
            }
            deleteNode = p->next;
            p->next = p->next->next;
        }   
        --listSize;
        delete deleteNode;
        deleteNode = nullptr;
    }

    void insert(int index,const T& element)
    {
        if (index<0 || index > listSize)
        {
            std::ostringstream s;
            s << "Initial capacity" << initialCapacity << "must be > 0" << '\n';
            throw illegalparameter(s.str());
        }
        
        if (index == 0)
        {
            firstNode = new chainNode<T> (element,firstNode);
        }

        else
        {
            chainNode<T>* p = firstNode;
            for (int i = 0;i<index-1;++i)
            {
                p = p->next;
            }
            p->next = new chainNode<T> (element,p->next);
        }
    }

    void clear()
    {
        while (firstNode != nullptr)
        {
            chainNode<T>* nextNode = firstNode ->next;
            delete firstNode;
            firstNode = nextNode;
        }
        listSize = 0;
    }

    
    void output(std::ostream& out) const
    {
        for (chainNode<T>* currentNode = firstNode;currentNode != nullptr;currentNode = currentNode->next)
        {
            out << currentNode->element << " ";
        }
    }
 
    std::ostream& operator<< (std::ostream& out,const chain<T>& x)
    {
        x.output(out);
        return out;
    }
    
    class iterator
{
private:
    chainNode<T>* node;

public:

    iterator(chainNode<T>* theNode == nullptr)
    {
        node = theNode;
    }

    T& operator*() const {return node->element;}
    T* operator->() const {return &(node->element);}

    iterator operator++()
    {
        node = node->next;
        return *this;
    }

    iterator operator++(int)
    {
        iterator old = *this;
        node = node->next;
        return old;
    }

    bool operator!=(iterator it)
    {
        return (node != it.node);
    }
     
    bool operator=(iterator it)
    {
        return (node == it.node);
    }

    iterator begin() const
    {
        return iterator(firstNode);
    }

    iterator end() const
    {
        return iterator(nullptr);
    }
    
};


    
    
    


};