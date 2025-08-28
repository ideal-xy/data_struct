/*
来学习一下堆，首先堆是一种完全二叉树，对于一个深度为h为二叉树，其1到h-1层都是满的，h层所有的叶节点都在最左边
最小堆：对于所有的父节点，子代节点的值都大于它，则称为最小堆，最大堆就是反过来的
最大堆就是越往上面值越大

一般意义上，我们认为只要满足两点就是一个堆，1.一颗完全二叉树
                                            2.每个节点的值大于等于（或小于等于）其子树中每个节点的值

首先得知道，完全二叉树有一个非常好的性质，对于任意一个父节点的index n来说（这里n从0算，它的子节点的index一定是2n+1,2n+2
这意味着我们可以使用数组来表示它，而不是非要使用树这个数据结构（但是如果n从1开始计算的话，其子节点的index则就是2n，2n+1,可以节省一次计算

*/

#include <cstring>
#include <new>

void inplace_swap(int* array,int i,int j);

class Heap 
{
private:
    int* array;
    int max_size;
    int count = 0;

public:
    Heap(int n)
    {
        array = new int[n];
        max_size = n;
    }

    Heap(int arr[],int max_size,int n)
    {
        array = static_cast<int*>(::operator new(sizeof(int) * max_size));
        std::memcpy(array,arr,sizeof(int));
        count = n;     
    }

    ~Heap()
    {
        delete [] array;
    }


    void insert(int data)
    {
        if (this->count >= this->max_size)
        {
            return;
        }
        
        this->count ++; //  先放在最后一个节点的位置
        array[count] = data;
        int current = count;

        while (current/2 > 0 && this->array[current] > this->array[current/2])
        {
            inplace_swap(this->array, current, current/2);
            current = (current >> 1);
        }
    }
   
    void heaplify(int i)
    {
        while (true)
        {
            int maxPos = i;
            if (i*2 <= this->count && this->array[i*2] > this->array[i]) 
            {
                maxPos = 2*i;
            }

            if (i* 2 + 1 <= this->count && this->array[2*i + 1] <= count)
            {
                maxPos = 2*i + 1;
            }

            if(maxPos == i) break;
            inplace_swap(this->array, i, maxPos);
            i = maxPos;
        }
    }

    /*
    注意我们这里的堆化是从上往下的对话，插入操作中每次都是把新的元素放置在最后一个叶节点的位置
    所以进行的是从下到上的堆化，
    */

    void clearMax()
    {
        if (count == 0)
        {
            return;
        }

        this->array[1] = this->array[this->count];
        this->count --;
        heaplify(1);
    }
    /*
    类似的，我们可以实现删除堆中任意一个节点的操作，实现方式是把最后一个叶节点与待删除的节点交换，然后把count--
    最后从带删除的那个位置开始从上到下heaplify即可。
    */

    /*
    有一种排序叫做堆排序，给定一组数据，要对其进行堆排序，首先要建堆
    根据堆的存储规律，从1到n/2 都是非叶节点，后面的都是叶节点，我们从n/2开始，到1结束每次都从下往上
    */

    void buildHeap()
    {
        for (int i = this->count/2;i>=1;--i)
        {
            heaplify(i);
        }
    }

    /*
    建堆这个操作的时间复杂度为O(n),如果你要的是降序排序，这个任务已经完成了，接下来写一下升序排序的一些东西
    */

    void ascending()
    {
        this->buildHeap();
        while(this->count > 1)
        {
            inplace_swap(this->array, count, 1);
            count --;
            heaplify(1);
        }
    }




    friend void inplace_swap(int* array,int i,int j);

};

void inplace_swap(int* array,int i,int j) 
{
    array[j] = array[i] ^ array[j];
    array[i] = array[i] ^ array[j];
    array[j] = array[i] ^ array[j];
}