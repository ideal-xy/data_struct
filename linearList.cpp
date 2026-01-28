#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

template <typename T>
class arrayList
{
private:
    T *element;
    int arrayLength;
    int listSize;

public:
    arrayList(int initialCapacity)
    {
        if (initialCapacity < 1)
        {
            std::ostringstream s;
            s << "Initial capacity = " << initialCapacity << "must be > 0";
            throw illegalParameterValue(s.str());
        }
        arrayLength = initialCapacity;
        element = new T[arrayLength];
        listSize = 0;
    }

    arrayList(const arrayList<T> &theList)
    {
        arrayLength = theList.arrayLength;
        listSize = theList.listSize;
        element = new T[arrayLength];
        std::copy(theList.element, theList.element + listSize, element);
    }

    void checkIndex(int index) const
    {
        if (index < 0 || index >= listSize)
        {
            std::ostringstream s;
            s << "index =" << index << "size =" << listSize;
            throw illegalParameterValue(s.str());
        }
    }

    T &get(int index) const
    {
        checkIndex(index);
        return element[index];
    }

    int indexOf(const T &theElement)
    {
        int theindex = int(std::find(element, element + listSize, theElement) - element);

        if (theindex == listSize)
        {
            return -1; // not found
        }

        return theindex;
    }

    void erase(int theIndex)
    {
        check(theIndex);
        std::copy(element + theIndex + 1, element + listSize, element + theIndex);
        element[listSize--].~T();
    }

    void insert(int theIndex, const T &theElement)
    {
        if (theIndex < 0 || theIndex > listSize)
        {
            std::ostringstream s;
            s << "index =" << theIndex << "size = " << listSize;
            throw illegalIndex(s.str());
        }

        if (listSize == arrayLength)
        {
            changeLength(element, arrayLength, arrayLength * 2);
            arrayLength *= 2;

            std::copy_backward(element + theIndex, element + listSize, element + listSize + 1); // 😡 非常重要 防止元素被覆盖 因此选择逆向拷贝
            element[theIndex] = theElement;
        }
    }

    void merge(const arrayList<T> &other)
    {
        int newSize = listSize + other.listSize;

        if (newSize >= arrayLength)
        {
            changeLength(element, arrayLength, arrayLength * 2);
        }

        std::copy(other.element, other.element + other.listSize, element + listSize);
        listSize = newSize;
    }

    void output(std::ostream &out) const
    {
        copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
    }

    friend std::ostream &operator<<(std::ostream &out, const arrayList<T> &x);
};

template <typename T>
void changeLength(T *&a, int oldlength, int newlength) // 注意 T*&a 从类型上来说 是类的私有成员 而不是类的对象
{
    if (newlength < 0)
        throw illegalparameter("new length must be >= 0");
    T *temp = new T[newlength];
    int number = (oldlength < newlength ? oldlength : newlength);
    copy(a, a + number, temp);

    delete[] a;
    a = temp;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}

template <typename T>
class iterator
{
private:
    T *m_position;

public:
    iterator(T *position = 0) : m_position = position {}

    T &operator*() const { return *m_position; }
    T *operator->() const { return m_position; }

    iterator &operator++()
    {
        ++m_position;
        return *this;
    }

    iterator operator++(int)
    {
        old_iterator = *this;
        ++m_position;
        return old;
    }
};

template <typename T>
class vectorList
{
private:
    std::vector<T> *element;

public:
    vectorList(int initialCapacity)
    {
        if (initialCapacity < 1)
        {
            throw illegalParameter("error!!");
        }
        element = new std::vector<T>;
        element->reserve(initialCapacity);
    }

    vectorList(const vectorList<T> &theList)
    {
        element = new std::vector<T>(*(theList.element));
    }

    ~vectorList()
    {
        delete[] element;
    }

    int getSize()
    {
        return static_cast<int>(element->size());
    }

    void checkIndex(int theIndex)
    {
        if (theIndex >= static<int>(element->size()))
        {
            throw illegalParameter("error!!");
        }
    }

    void erase(int theIndex)
    {
        checkIndex(theIndex);
        element->erase(element->begin() + theIndex);
    }

    void insert(int theIndex, const T &theElemet)
    {
        if (theIndex < 0 || theIndex >= static_cast<int>(element->size()))
            throw illegalParameter("error!!");

        element->insert(element->begin() + theIndex, theElemet);
    }
};

int main()
{
    std::vector<int> vec{1, 2, 3};

    return 0;
}