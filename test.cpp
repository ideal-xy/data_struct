#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>




int main() {
    std::vector<int> vec = {1, 2, 3, 4};
    int arr[5] = {1,2,3,4,5};
    
    // 将 vec 的元素复制到 std::cout，用空格分隔
    std::transform(vec.begin(),vec.end()-1,std::ostream_iterator<int>(std::cout," - "),[](int x){return x*x;});
    std::cout << std::pow((vec.back()),2)<< '\n';
    std::copy_if(arr,arr+std::size(arr),std::ostream_iterator<int>(std::cout," "),[](int x){return x%2 == 0;});
    std::cout << std::endl;

    // 输出: 1 2 3 4 
    return 0;
}