#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <numeric>
/*
* nums:待排序的数组
* n:尚未完成排序的元素数量
* i:第一个被堆化的元素的索引，从上往下堆化(大顶堆)
*/
void heaplify(std::vector<int>& nums,int n,int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // // 如果左子节点比父节点大
    if (left < n && nums[left] > nums[largest])
        largest = left;
    // 如果右子节点比父节点还要大，说明右节点的值是三个节点中最大的
    if (right < n && nums[right] > nums[largest])
        largest = right;

    // 父节点不是最大的，需要进行交换，并递归
    if (largest != i)
    {
        std::swap(nums[i],nums[largest]);
        heaplify(nums, n, largest);
    }

}

void heapSort(std::vector<int>& nums)
{
    int n = nums.size(); 

    for (int i = n / 2 - 1;i >= 0;i--)
        heaplify(nums, n, i);

    for (int i = n - 1;i > 0;i--)
    {
        std::swap(nums[0],nums[i]);
        heaplify(nums, i, 0);
    }
}


void printArray(const std::vector<int>& arr) {

    for (int i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

int main() 
{
    std::vector<int> arr(1000000);
    auto arr1 = arr;
    std::iota(arr.begin(), arr.end(), 0);  // 0到99999
    std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});

    auto start = std::chrono::high_resolution_clock::now();
    heapSort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "运行时间: " << duration.count() << " 毫秒" << std::endl;
    

    auto start1 = std::chrono::high_resolution_clock::now();
    std::sort(arr1.begin(),arr1.end());
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    std::cout << "运行时间: " << duration1.count() << " 毫秒" << std::endl;

    return 0;
}

/*
堆排序运行时间: 253 毫秒
std::sort()运行时间: 1 毫秒
*/