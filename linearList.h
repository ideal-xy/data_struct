#ifndef LINEAR_LIST
#define LINEAR_LIST
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iterator>

template <typename T>
class arrayList
{
private:
    T* element;
    int arrayLength;
    int listSize;

    // 辅助函数：更改数组长度
    void changeLength(T*& arr, int oldLength, int newLength) {
        T* newArr = new T[newLength];
        std::copy(arr, arr + std::min(oldLength, newLength), newArr);
        delete[] arr;
        arr = newArr;
    }

public:
    using iterator = class arrayList<T>::iterator;  // 定义类型别名

    arrayList(int initialCapacity)
    {
        if (initialCapacity < 1)
        {
            std::ostringstream s;
            s << "Initial capacity = " << initialCapacity <<"must be > 0";
            throw std::invalid_argument(s.str());
        }
        arrayLength = initialCapacity;
        element = new T[arrayLength];
        listSize = 0; 
    }
    
    arrayList(const arrayList<T>& theList)
    {
        arrayLength = theList.arrayLength;
        listSize = theList.listSize;
        element = new T[arrayLength];
        std::copy(theList.element, theList.element + listSize, element);
    }
    
    ~arrayList() {
        delete[] element;
    }

    void checkIndex(int index) const 
    {
        if (index < 0 || index >= listSize)
        {
            std::ostringstream s;
            s << "index =" << index << "size =" << listSize;
            throw std::out_of_range(s.str());
        }
    }
    
    T& get(int index) const
    {
        checkIndex(index);
        return element[index];
    }

    int indexOf(const T& theElement)
    {
        int theindex = int (std::find(element, element + listSize, theElement) - element);
        
        if (theindex == listSize)
           { return -1; // not found
           }
        
        return theindex;
    }

    void erase(int theIndex)
    {
        checkIndex(theIndex);
        std::copy(element + theIndex + 1, element + listSize, element + theIndex);
        --listSize;
    }

    void insert(int theIndex, const T& theElement)
    {
        if (theIndex < 0 || theIndex > listSize)
        {
            std::ostringstream s;
            s << "index =" << theIndex << "size = " << listSize ;
            throw std::out_of_range(s.str());
        }

        if (listSize == arrayLength)
        {
            changeLength(element, arrayLength, arrayLength * 2);
            arrayLength *= 2;
        }

        std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
        element[theIndex] = theElement;
        ++listSize;
    }

    void merge(const arrayList<T>& other)
    {
        int newSize = listSize + other.listSize;

        if (newSize >= arrayLength) {
            changeLength(element, arrayLength, std::max(arrayLength * 2, newSize));
            arrayLength = std::max(arrayLength * 2, newSize);
        }

        std::copy(other.element, other.element + other.listSize, element + listSize);
        listSize = newSize;
    }

    void output(std::ostream& out) const
    {
        std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
    }

    void reset(int newSize)
    {
        if (newSize < 0)
        {
            throw std::invalid_argument("newSize must be non-negative");
        }

        if (newSize > arrayLength)
        {
            changeLength(element, arrayLength, 2 * std::max(arrayLength, newSize));
            arrayLength = 2 * std::max(arrayLength, newSize);
        }

        listSize = newSize;
    }

    void clear()
    {
        reset(0);
    }

    int size() const
    {
        return listSize;
    }

    void set(int index,T term)
    {
        if (index<0)
        {
            throw std::invalid_argument("Index must be non-negative");
        }

        if (index >= arrayLength)
        {
            changeLength(element,arrayLength,2*index);
            arrayLength = 2*index;
        }

        if (index>= listSize)
        {
            ++listSize;
        }

        element[index] = term;
    }

    bool empty(){
        return listSize == 0;
    }

    iterator begin()
    {
        return iterator(element);
    }
    
    iterator end()
    {
        return iterator(element + listSize);
    }

    class iterator
    {
    private:
        T* m_position;

    public:
        iterator(T* position = nullptr) : m_position(position) {}

        T& operator*() const { return *m_position; }
        T* operator->() const { return m_position; }

        iterator& operator++()
        {
            ++m_position;
            return *this;
        }

        iterator operator++(int) 
        {
            iterator old = *this;
            ++m_position;
            return old;
        }

        bool operator==(const iterator& other) const {
            return m_position == other.m_position;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };
};






template <typename T>
class vectorList
{
private:
    std::vector<T>* element;

public:
    vectorList(int initialCapacity)
    {
        if(initialCapacity<1)
        {
            throw illegalParameter("error!!");
        }
         element = new std::vector<T>;
         element->reserve(initialCapacity);
    }

    vectorList(const vectorList<T>& theList)
    {
        element = new std::vector<T>(*(theList.element));
    }

    ~vectorList()
    {
        delete [] element;
    }

    int getSize()
    {
        return static_cast<int>(element->size());
    }

    void checkIndex(int theIndex)
    {
        if (theIndex>=static<int>(element->size()))
        {
            throw illegalParameter("error!!");
        }
    }

    void erase(int theIndex)
    {
        checkIndex(theIndex);
        element -> erase(element -> begin() + theIndex);
    }

    void insert(int theIndex,const T& theElemet)
    {
        if (theIndex < 0 || theIndex >= static_cast<int>(element -> size()))
            throw illegalParameter("error!!");
        
        element -> insert(element->begin() + theIndex,theElemet);
    }


};


#endif LINEAR_LIST



