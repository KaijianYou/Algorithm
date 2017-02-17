#ifndef ALGORITHM_BINARY_SEARCH_H
#define ALGORITHM_BINARY_SEARCH_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 二分查找
    // 如果找到目标值，则返回其索引值；否则返回 -1
    template <typename T>
    int binarySearch(const vector<T> &arr, const T &target)
    {
        int low = 0;
        int high = arr.size() - 1;
        while (low <= high) {
            int mid = low + ((high - low) >> 1);
            if (arr[mid] < target) {
                low = mid + 1;
            } else if (arr[mid] > target) {
                high = mid - 1;
            } else {
                return mid;
            }
        }

        return -1;
    }

    // 二分查找
    // last 为指向最后一个元素后的位置索引
    // 返回 last 表示没有找到匹配值
    template <typename T>
    int binarySearch(const T arr[], int first, int last, const T &target)
    {
        int origLast = last;
        while (first < last) {
            int mid = first + ((last - first) >> 1);
            if (target == arr[mid]) {
                return mid;
            } else if (target < arr[mid]) {
                last = mid;
            } else {
                first = mid + 1;
            }
        }

        return origLast;
    }

    // 递归实现二分查找
    // last 为指向最后一个元素后的位置索引
    // 若没有找到目标值，返回 -1
    template <typename T>
    int binarySearch(const vector<T> &vec, int first, int last, const T &target)
    {
        if (first < last) {
            int mid = first + ((last - first) >> 1);
            if (vec[mid] == target) {
                return mid;
            } else if (vec[mid] > target) {
                return binarySearch(vec, first, mid, target);
            } else {
                return binarySearch(vec, mid + 1, last, target);
            }
        } else {
            return -1;
        }
    }
}

#endif  // ALGORITHM_BINARY_SEARCH_H