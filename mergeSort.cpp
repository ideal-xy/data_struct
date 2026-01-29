#include <cstdlib>


/*
 * 将一个数组中的两个相邻有序区间合并成一个
 *
 * 参数说明：
 *     a -- 包含两个有序区间的数组（升序）
 *     start -- 第1个有序区间的起始地址。
 *     mid   -- 第1个有序区间的结束地址。也是第2个有序区间的起始地址。
 *     end   -- 第2个有序区间的结束地址。
 */

void merge(int a[],int start,int mid,int end)
{
    int* tmp = (int*)malloc((end - start + 1) * sizeof(int));
    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end)
    {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }

    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= end)
        tmp[k++] = a[j++];

    for (i = 0;i < k;i++)
        a[start + i] = tmp[i];
    
    free(tmp);
}