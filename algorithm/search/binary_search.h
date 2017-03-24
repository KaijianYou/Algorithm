#ifndef ALGORITHM_BINARY_SEARCH_H
#define ALGORITHM_BINARY_SEARCH_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 二分查找
    // 如果找到 key，则返回其索引；否则返回 -1
    template <typename T>
    int binarySearch(const vector<T> &arr, const T &key)
    {
        int low = 0;
        int high = arr.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] < key) {
                low = mid + 1;
            } else if (arr[mid] > key) {
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
    int binarySearch(const T arr[], int first, int last, const T &key)
    {
        int origLast = last;
        while (first < last) {
            int mid = first + (last - first) / 2;
            if (key == arr[mid]) {
                return mid;
            } else if (key < arr[mid]) {
                last = mid;
            } else {
                first = mid + 1;
            }
        }

        return origLast;
    }

    // 递归实现二分查找
    // last 为指向最后一个元素后的位置索引
    // 若没有找到 key，返回 -1
    template <typename T>
    int binarySearch(const vector<T> &v, int first, int last, const T &key)
    {
        if (first < last) {
            int mid = first + (last - first) / 2;
            if (v[mid] == key) {
                return mid;
            } else if (v[mid] > key) {
                return binarySearch(v, first, mid, key);
            } else {
                return binarySearch(v, mid + 1, last, key);
            }
        } else {
            return -1;
        }
    }
}

#endif  // ALGORITHM_BINARY_SEARCH_H