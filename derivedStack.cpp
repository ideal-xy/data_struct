#include <iostream>
#include <linearList.h>

template <typename T>
class derivedStack : private arrayList<T>
{
public:
    derivedStack(int capacity = 10) : arrayList<T>(capacity) {}

    bool empty() { return arrayList<T>::empty(); }
    int size() { return arrayList<T>::size(); }
    T &top()
    {
        if ((*this).empty())
        {
            throw stackEmpty();
        }
        return get(arrayList<T>::size() - 1);
    }

    void pop()
    {
        if (empty())
            throw stackEmpty();
        erase(size() - 1);
    }

    void push(const T &theElement)
    {
        insert(size(), theElement;)
    }
};
