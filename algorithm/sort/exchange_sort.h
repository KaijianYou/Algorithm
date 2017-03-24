#ifndef ALGORITHM_EXCHANGE_SORT_H
#define ALGORITHM_EXCHANGE_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 交换排序
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void exchangeSort(vector<T> &v, Comparator comp)
    {
        for (int i = 0; i < v.size() - 1; ++i) {
            for (int j = i + 1; j < v.size(); ++j) {
                if (comp(v[j], v[i])) {
                    T temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
                }
            }
        }
    }
}

#endif  // ALGORITHM_EXCHANGE_SORT_H