#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> vec(13);
    
    // 从标准输入读取整数，直到遇到非整数输入或文件结束（Ctrl+D）
    std::copy(
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>(),  // 默认构造表示流结束
        vec.begin()
    );

    // 输出读取的元素
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}