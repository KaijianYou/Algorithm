#ifndef ALGORITHM_EXCHANGE_SORT_H
#define ALGORITHM_EXCHANGE_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 交换排序
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void exchangeSort(vector<T> &vec, Comparator comp)
    {
        for (int i = 0; i < vec.size() - 1; ++i) {
            for (int j = i + 1; j < vec.size(); ++j) {
                if (comp(vec[j], vec[i])) {
                    T temp = vec[i];
                    vec[i] = vec[j];
                    vec[j] = temp;
                }
            }
        }
    }
}

#endif  // ALGORITHM_EXCHANGE_SORT_H