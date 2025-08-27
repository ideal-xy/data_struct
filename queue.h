#include <iostream>

template <typename T>
class queue
{
private:
    T* queue;
    int queueFront;
    int queueBack;
    int arraylength;

public:
    queue()
    {}

    queue(int num) 
    {
        arraylength = num;
        queue = new T[num];
        queueFront = queueBack = 0;
    }

    ~queue()
    {
        delete [] queue;
    }
    void push(T element)
    {
        if ((queueBack+1)%arraylength == queueFront)
        {
            T* newQueue = new T[2*arraylength];

            int start = (queueFront+1) % arraylength;
            if (start < 2)
                std::copy(queue+start,queue +start +arraylength - 1,newQueue);
            else
        {
            std::copy(queue+start,queue+arraylength,newQueue);
            std::copy(queue,queue+queueBack+1,newQueue+arraylength-start);
        }

        queueFront = 2*arraylength - 1;
        queueBack = arraylength - 2;
        arraylength *= 2;
        delete [] queue;
        queue = newQueue;
        }
        

        queueBack = (queueBack+1) % arraylength;
        queue[queueBack] = element;
    }

    void pop()
    {
        if empty()
            throw queueEmpty();
        queueFront = (queueFront + 1) % arraylength;
        queue[queueFront].~T();
    }

    bool empty()
    {
        return queueBack == queueFront;
    }
    
    T front()
    {
        return queue[(queueFront+1)+arraylength];
    }


};