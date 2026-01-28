#include <stack>
#include <utility>
#include <vector>

/*
1:选择排序
*/
void selectSort(std::vector<int>& nums)
{
    int size = nums.size();
    for (int i = 0;i < size - 1;i++)
    {
        int k = i;
        for(int j = k + 1;j < size;j++)
        {
            if (nums[j] < nums[k])
            {
                k = j;
            }
        }

        std::swap(nums[i],nums[k]);
    }
}


/*
2:冒泡排序
*/
void bubbleSort(std::vector<int>& nums)
{
    int size = nums.size();
    bool flag = false;
    for (int i = size - 1;i > 0;i++)
    {
        for (int j = 0; j < i;j++)
        {
            if (nums[j] > nums[j+1])
            {
                std::swap(nums[j],nums[j+1]);
                flag = true;
            }
        }

        if (!flag) {break;};
    }
}


/*
3:插入排序
*/
void insertSort(std::vector<int>& nums)
{
    for (int i = 1;i < nums.size();i++)
    {
        int base = nums[i];
        int j    = i - 1;
        
        while (j >= 0 && nums[j] > base)
        {
            nums[j+1] = nums[j];
            j--;
        } // 此时，j是[0,i-1]中从右往左数第一个小于等于base的index，所以base应当放在j+1
        nums[j+1] = base;
    }
}


/*
4:快速排序
*/

/*
-快速排序的核心操作是“哨兵划分”，其目标是：选择数组中的某个元素作为“基准数”，
将所有小于基准数的元素移到其左侧，而大于基准数的元素移到其右侧

-算法思想是分治+递归

-有一个需要注意的是如果选取的哨兵值一开始在最左边，那么我们需要先移动右指针
*/

int partition(std::vector<int> &nums, int left, int right) 
{
    int pivot = nums[left]; //  注意保存基准值
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[j] >= pivot)
            j--;
        while (i < j && nums[i] <= pivot)
            i++;
        std::swap(nums[i], nums[j]);
    }
    
    nums[left] = nums[i];
    nums[i] = pivot;  // ⚠️不要写nums[i] = nums[left] !!!!!!!

    return i;
}

/* 快速排序 */
void quickSort(std::vector<int> &nums, int left, int right) 
{
    // 子数组长度为 1 时终止递归
    if (left >= right)
        return;
    // 哨兵划分
    int pivot = partition(nums, left, right);
    // 递归左子数组、右子数组
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}


/* 
 * 快速排序分区函数 - 哨兵划分法
 * 
 * 为什么必须让 j 指针先移动？
 * 
 * 关键洞察：哨兵在最左侧，最终要交换到 i/j 相遇点。
 * 必须保证相遇点的值 <= 哨兵值，否则分区会出错。
 * 
 * j 先移动时，当 j 碰到 i 停止，有两种情况：
 * 
 * 1. i 从未移动（原地不动）
 *    - 此时 nums[i] = 哨兵自身（nums[left]）
 *    - 哨兵 <= 哨兵 ✓ 安全
 * 
 * 2. i 已经移动过（说明发生过交换）
 *    - 上次交换把右边的小值换到了 i 位置
 *    - 所以现在 nums[i] < 哨兵 ✓ 安全
 * 
 * 如果 i 先移动，当 i 碰到 j 停止，则可能：
 * 
 * 1. j 从未移动
 *    - nums[j] 可能 > 哨兵 ❌ 危险！
 * 
 * 2. j 移动过
 *    - 上次交换把左边的大值换到了 j 位置
 *    - 所以 nums[j] > 哨兵 ❌ 更糟！
 * 
 * 因此，j 必须先移动，才能保证最终 nums[i] <= 哨兵。
 * 
 * 示例反证：[3, 1, 2, 5]
 * i 先移动会直接找到 5，交换后得到 [5, 1, 2, 3]
 * 违反了"左边都小"的分区原则。
 */


/*
为了控制递归栈的深度，可以优化原来的写法
*/
/* 快速排序（递归深度优化） */
void quickSortPro(std::vector<int> &nums, int left, int right) {
    // 子数组长度为 1 时终止
    while (left < right) {
        // 哨兵划分操作
        int pivot = partition(nums, left, right);
        // 对两个子数组中较短的那个执行快速排序
        if (pivot - left < right - pivot) {
            quickSortPro(nums, left, pivot - 1); // 递归排序左子数组
            left = pivot + 1;                 // 剩余未排序区间为 [pivot + 1, right]
        } else {
            quickSortPro(nums, pivot + 1, right); // 递归排序右子数组
            right = pivot - 1;                 // 剩余未排序区间为 [left, pivot - 1]
        }
    }
}


/*
迭代吗快速排序的关键是维护一个栈，记录所有需要排序的子区间的端点
*/
void quickSortIterative(std::vector<int>& nums,int left,int right)
{
    if (left >= right) return;

    std::stack<int> s;
    s.push(left);
    s.push(right);

    while (!s.empty())
    {
        int r = s.top();
        s.pop();
        int l = s.top();
        s.pop();

        int pivotIndex = partition(nums, l, r); 
        
        if(pivotIndex - 1 > l)
        {
            s.push(l);
            s.push(pivotIndex - 1);
        }

        if (pivotIndex + 1 < r)
        {
            s.push(pivotIndex + 1);
            s.push(r);
        }
    }
}

