#include <iostream>
#include <algorithm>
#include <sstream>

template <typename T>
struct chainNode // 这个结构体描述的是链表的每一个节点
{
    T element;
    chainNode<T>* next;
    chainNode<T>* previous;
    int x=1;
    chainNode() {}
    chainNode(const T& element)
    {
        this->element = element;
        this->next = nullptr;
        this->previous = nullptr;
    }

    chainNode(const T& element,chainNode<T>* next,chainNode<T>* previous)
    {
        this->element = element;
        this->next  = next;
        this->previous = previous;
    }
};


template <typename T>
class doublyList
{
private:
    int m_listSize;
    chainNode<T>* m_firstNode;
    chainNode<T>* m_lastNode;

public:
    doublyList(int initialCapacity)
    {
        if (initialCapacity < 1)
        {
            std::ostringstream s;
            s << "Initial capacity" << initialCapacity << "must be > 0" << '\n';
            throw illegalparameter(s.str());
        }

        m_firstNode = nullptr;
        m_lastNode = nullptr;
        m_listSize = initialCapacity;
    }

    doublyList(const doublyList<T>& other)
    {
        doublyList<T>* sourceNode = other.m_firstNode;
        
        if (other.m_listSize == 0)
        {
            m_firstNode = nullptr;
            m_lastNode = nullptr;
            m_listSize = 0;
            return;
        }
        if (other.m_listSize == 1)
        {
            m_firstNode = new chainNode<T>(other.m_firstNode->element);
            m_lastNode = m_firstNode;
            m_listSize = 1;
            return;
        }
        else
        {
            chainNode<T>* sourceNode = other.m_firstNode;
            m_firstNode = new chainNode<T>(sourceNode->element);

            chainNode<T>* targetNode = m_firstNode;

            sourceNode = sourceNode->next;

            chainNode<T>* targetNode2 = new chainNode<T> (sourceNode->element);
            targetNode2->previous = targetNode;
            targetNode->next = targetNode2;
            sourceNode = sourceNode->next;

            while (sourceNode != nullptr)
            {
                targetNode2->next = new chainNode<T>(sourceNode->element);
                targetNode = targetNode->next;
                targetNode2 = targetNode2->next;
                targetNode2->previous = targetNode;//  🤡🤡🤡 这三行可以使用 targetNode2->next->previous = targetNode2 替代 🤡🤡🤡
                targetNode->next = targetNode2; 
                sourceNode = sourceNode->next;
            }
            m_lastNode = targetNode2;
            m_listSize = other.m_listSize;

        }
    }

    ~doublyList()
    {
        while (m_firstNode != nullptr)
        {
            chainNode<T>* cNode = m_firstNode->next;
            delete m_firstNode;
            m_firstNode = cNode;
        }
    }
    
    void checkIndex(int index)
    {
        if (index < 0 || index>m_listSize )
        {
             std::ostringstream s;
            s << "Initial capacity" << initialCapacity << "must be > 0" << '\n';
            throw illegalparameter(s.str());
        }

    }

    void insert(const T& theElement)
    {
        if (index < 0 || index>m_listSize )
        {
             std::ostringstream s;
            s << "Initial capacity" << initialCapacity << "must be > 0" << '\n';
            throw illegalparameter(s.str());
        }

        if (index == 0)
        {
            m_firstNode = new chainNode<T>(nullptr,theElement,m_firstNode);
            return;
        }

        else
        {
            chainNode<T>* p = m_firstNode;
            for(int i=0;i<index-1;++i)
            {
                p = p->next;
            }
            chainNode<T>* newNode = new chainNode<T> (p,theElement,p->next);

            if (newNode->next != nullptr)
            {
                newNode->next->previous = newNode;
            }
            else{
                m_lastNode = newNode;
            }
        }
        ++m_listSize;
    }

    void erase(int index)
    {
        checkIndex(index);
        chainNode<T>* deleteNode;

        if(index == 0)
        {
            deleteNode = m_firstNode;
            m_firstNode = m_firstNode->next;
           
            if (m_firstNode == nullptr)
            {
                m_firstNode->previous = nullptr;
            }
            else
            {
                m_lastNode = nullptr;
            }
        }

        else
        {
            chainNode<T>* p = m_firstNode;
            for (int i=1;i<index-1;++i)
            {
               p = p->next;
            }
            deleteNode = p->next;
            if(p->next->next == nullptr) // 删除的是尾节点
            {
                m_lastNode = p;
                p->next = nullptr;
            }
            else{ // 中间节点 则不管尾节点 直接跳过被删除的 连接前后节点
                p->next = p->next->next;
                deleteNode->next->previous = p;
            }
        }

        delete deleteNode;
        deleteNode = ptr; 
        m_listSize -- ;
    }

    int getIndex(const T& element)
    {
        chainNode<T>* currentNode = m_firstNode;
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

    void clear()
    {
        while (m_firstNode != nullptr)
        {
            chainNode<T>* nextNode = m_firstNode ->next;
            delete firstNode;
            m_firstNode = nextNode;
        }
        listSize = 0;
    }
    

    void output(std::ostream& out)
    {
        for (chainNode<T>& node = m_firstNode;node != nullptr;node = node.next)
        {
            out << node.element << " ";
        }
    }

    std::ostream& operator<< (std::ostream& out,doublyList<T>& x)
    {
        x.output(out);
        return out;
    }

    class iterator
    {
    private:
       chainNode<T>* node;

    public:
        iterator(chainNode<T>* node = nullptr)
        {
            this->node = node;
        }

        T& operator* () {return node->element; }
        T* operator->() {return &(node->element);}

        iterator operator++(int)
        {
            iterator old = *this;
            node = node->next;
            return old;
        }

        iterator operator++()
        {
            node = node->next;
            return *this;
        }

        iterator operator--()
        {
            node = node->previous;
            return *this;
        }

        iterator operator--(int)
        {
            iterator old = *this;
            node = node->previous;
            return old;
        }

        iterator begin()
        {
            return iterator(m_firstNode);
        }
        iterator end()
        {
            return iterator(m_lastNode);
        }
    }









};