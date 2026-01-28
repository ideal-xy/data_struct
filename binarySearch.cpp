/*
这一节写二分查找，分开区间和闭区间查找
*/
#include <vector>

/* 二分查找（左闭右开区间） */
int binarySearchLCRO(std::vector<int> &nums, int target) 
{
  // 初始化左闭右开区间 [0, n) ，即 i, j 分别指向数组首元素、尾元素+1
  int i = 0, j = nums.size();
  // 循环，当搜索区间为空时跳出（当 i = j 时为空）
  while (i < j) 
  {
    int m = i + (j - i) / 2; // 计算中点索引 m
    if (nums[m] < target)    // 此情况说明 target 在区间 [m+1, j) 中
      i = m + 1;
    else if (nums[m] > target) // 此情况说明 target 在区间 [i, m) 中
      j = m;
    else // 找到目标元素，返回其索引
      return m;
  }
  // 未找到目标元素，返回 -1
  return -1;
}

/* 二分查找（双闭区间） */
int binarySearchLCRC(std::vector<int> &nums, int target) 
{
  // 初始化双闭区间 [0, n-1] ，即 i, j 分别指向数组首元素、尾元素
  int i = 0, j = nums.size() - 1;
  // 循环，当搜索区间为空时跳出（当 i > j 时为空）
  while (i <= j) 
  {
    int m = i + (j - i) / 2; // 计算中点索引 m
    if (nums[m] < target)    // 此情况说明 target 在区间 [m+1, j] 中
      i = m + 1;
    else if (nums[m] > target) // 此情况说明 target 在区间 [i, m-1] 中
      j = m - 1;
    else // 找到目标元素，返回其索引
      return m;
  }
  // 未找到目标元素，返回 -1
  return -1;
}

/*
1:计算中点索引时候要防止溢出,所以不使用 int m = (j + i) / 2
2:注意开区间和闭区间的右指针的初始值是不一样的
3:注意开区间和闭区间的while循环条件是不一样的
*/

/*
二分查找不仅可用于搜索目标元素，还可用于解决许多变种问题，比如搜索目标元素的插入位置。
*/

/*
注意一个事实，我们使用二分查找在一个vector中查找target(LORO)，如果查找到了那么nums[i]
= nums[j] = target
如果没有查找到，那么i和j出的元素是第一个大于targe的元素，于是i-1和j-1就是最后一个小于target的元素
*/

/* 二分查找插入点（无重复元素） */
int binarySearchInsertionSimple(std::vector<int> &nums, int target) 
{
  int i = 0, j = nums.size() - 1; // 初始化双闭区间 [0, n-1]
  while (i <= j) 
  {
    int m = i + (j - i) / 2; // 计算中点索引 m
    if (nums[m] < target) 
    {
      i = m + 1; // target 在区间 [m+1, j] 中
    } else if (nums[m] > target) 
    {
      j = m - 1; // target 在区间 [i, m-1] 中
    } else 
    {
      return m; // 找到 target ，返回插入点 m 
    }
  }
  // 未找到 target ，返回插入点 i（第一个大于等于target的index）
  return i;
}

/* 二分查找插入点（存在重复元素） */
int binarySearchInsertion(std::vector<int> &nums, int target) 
{
    int i = 0, j = nums.size() - 1; // 初始化双闭区间 [0, n-1]
    while (i <= j) 
    {
        int m = i + (j - i) / 2; // 计算中点索引 m
        if (nums[m] < target) 
        {
            i = m + 1; // target 在区间 [m+1, j] 中
        } else if (nums[m] > target) 
        {
            j = m - 1; // target 在区间 [i, m-1] 中
        } else {
            j = m - 1; // 首个小于 target 的元素在区间 [i, m-1] 中
        }
    }
    // 返回插入点 i
    return i; // 这是nums中第一个大于等于target元素的索引
}

/*
1:不管nums中有无target，这个`binarySearchInsertionSimple`函数的返回值都是nums中第一个大于等于target的元素的index
2:如果nums中有多个target，需要我们查找最左边的target的index或者最右边的target的index
*/

// 闭区间写法结束时
// i指向第一个大于target的元素（或超出数组）
// j指向最后一个小于target的元素（或-1）
// 且 i = j + 1

// 开区间写法结束时
// i=j，指向第一个大于或等于target的元素
// 具体需要检查是否等于target

/*
 * 我们知道，当数组不包含 target 时，最终 i 和 j 会分别指向首个大于、小于 target 的元素。
 * 
 * 因此，如图 10-8 所示，我们可以构造一个数组中不存在的元素，用于查找左右边界。
 * 
 * - 查找最左一个 target：可以转化为查找 target - 0.5，并返回指针 i。
 * - 查找最右一个 target：可以转化为查找 target + 0.5，并返回指针 j。
 */

 /*
 注意：这种做法包含了target-0.5或者target+0.5包含在nums中的可能性,所以需要检查返回的index对应的元素是多少
 */