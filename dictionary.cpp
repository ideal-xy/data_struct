#include <iostream>
#include <vector>
#include "linearList.h"


template <typename K,typename E>
struct pairNode
{
    std::pair<K,E> element; // 这是数对
    pairNode<K,E>* next;
};

template <typename K,typename E>
class sortedChain
{
private:
    pairNode<K,E>* firstNode;
    int dSize;
public:
    sortedChain() {}
    ~sortedChain() {}
    void insert(const std::pair<K,E>& thePair);
};




template <typename K,typename E>
class dictionary
{
private:
    

public:
    dictionary() {}
    ~dictionary() {}
    
};

template <typename K,typename E>
void sortedChain<K,E>::insert(const std::pair<K,E>& thePair)
{
    pairNode<K,E>* p = firstNode;
    pairNode<K,E>* tp = nullptr;

    while (p != nullptr && p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }

    if (p != nullptr && p->element.first == thePair.first)
    {
        p->element.second = thePair.second;
        return;
    }

    pairNode<K,E>* newNode = new pairNode<K,E>(thePair,p); // 注意这一行
    if (tp == nullptr)
    {
        firstNode = newNode;
    }
    else
    {
        tp->next = newNode; //与这一行的关系，no need for newNode.next = p
    }
    dSize++;
    return;
}