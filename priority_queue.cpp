#include <vector>
#include <functional>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue 
{
private:
    std::vector<T> heap;
    Compare comp;
    
    
    
    void sift_up(int index) //  实际上就是二次堆的插入操作，新元素放置在最后一个叶节点
    {
        while (index > 0) 
        {
            int parent = (index - 1) / 2;
            if (comp(heap[parent], heap[index])) 
            {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else 
            {
                break;
            }
        }
    }
    

    void sift_down(int index)  // 实际上是堆化 heaplify
    {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
            
            if (left < size && comp(heap[largest], heap[left])) 
            {
                largest = left;
            }

            if (right < size && comp(heap[largest], heap[right])) 
            {
                largest = right;
            }

            if (largest != index) 
            {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } 
            else 
            {
                break;
            }
        }
    }
    
public:
    void push(const T& value) 
    {
        heap.push_back(value);
        sift_up(heap.size() - 1);
    }
    
    void pop() 
    {
        if (heap.empty()) return;
        std::swap(heap[0], heap.back());
        heap.pop_back();
        if (!heap.empty()) 
        {
            sift_down(0);
        }
    }
    
    const T& top() const 
    {
        return heap[0];
    }
    
    bool empty() const 
    {
        return heap.empty();
    }
    
    size_t size() const 
    {
        return heap.size();
    }
};