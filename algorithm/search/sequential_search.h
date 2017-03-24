#ifndef ALGORITHM_SEQUENTIAL_SEARCH_H
#define ALGORITHM_SEQUENTIAL_SEARCH_H

#include <list>

namespace myalgorithm {
    using std::vector;

    // 顺序查找
    // last 为指向最后一个元素后的位置索引
    // 返回 last 表示没有找到匹配值
    template <typename T>
    int sequentialSearch(const T arr[], int first, int last, const T &key)
    {
        int index = first;
        while (index != last && arr[index] != key) {
            ++index;
        }

        return index;
    }

    // 顺序查找
    template <typename T>
    typename vector<T>::iterator sequentialSearch(typename vector<T>::iterator first,
                                                  typename vector<T>::iterator last,
                                                  const T &key)
    {
        auto iter = first;
        while ((iter != last) && (*iter != key)) {
            ++iter;
        }

        return iter;
    }
}

#endif  // ALGORITHM_SEQUENTIAL_SEARCH_H