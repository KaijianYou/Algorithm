#ifndef ALGORITHM_FIND_KTH_H
#define ALGORITHM_FIND_KTH_H

#include <vector>
#include <functional>

#include "../sort/quick_sort.h"

namespace myalgorithm {
    using std::vector;

    // 搜索第 k 大的元素
    // 运用递归划分子表方法查找
    // 执行完成后，v[k - 1] 即是 v 中第 k 大元素
    // 此种方法不能处理有重复元素的情况
    template <typename T>
    void findKth(vector<T> &vec, int first, int last, int k)
    {
        // 定位中心值的索引
        int pivotIndex = locatePivot(vec, first, last, std::less<T>());
        if (pivotIndex == k) {  // 如果索引等于 k，结束查找
            return;
        } else if (k < pivotIndex) {  // 索引大于 k，则继续在左子表 [first, pivotIndex) 中查找
            findKth(vec, first, pivotIndex, k);
        } else {  // 索引小于 k，则继续在右子表 [pivotIndex, last) 中查找
            findKth(vec, pivotIndex + 1, last, k);
        }
    }
}

#endif  // ALGORITHM_FIND_KTH_H