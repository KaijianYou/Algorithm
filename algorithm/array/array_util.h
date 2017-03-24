#ifndef ALGORITHM_ARRAY_UTIL_H
#define ALGORITHM_ARRAY_UTIL_H

#include "../search/sequential_search.h"

namespace myalgorithm {
    // 输出数组中只出现过一次的元素的个数
    template <typename T>
    int numUnique(const T arr[], int size)
    {
        int uniqueCount = 0;
        for (int i = 0; i < size; ++i) {
            T key = arr[i];
            int index;
            if ((index = sequentialSearch(arr, 0, i, key)) == i) {
                if ((index = sequentialSearch(arr, i + 1, size, key)) == size) {
                    uniqueCount++;
                }
            }
        }

        return uniqueCount;
    }
}

#endif  // ALGORITHM_ARRAY_UTIL_H