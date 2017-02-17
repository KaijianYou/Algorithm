#ifndef ALGORITHM_SHELL_SORT_H
#define ALGORITHM_SHELL_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 希尔排序
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void shellSort(vector<T> &vec, Comparator comp)
    {
        int delta = 0;
        // 计算初始增量
        for ( ; delta <= vec.size() / 9; delta = 3 * delta + 1) {
            ;
        }

        for ( ; delta > 0; delta = (delta - 1) / 3) {
            // 对子表进行插入排序
            for (int i = 0; i < delta; ++i) {
                for (int j = i + delta; j < vec.size(); j += delta) {
                    int k = j;
                    T temp = vec[k];
                    while (k >= delta && comp(temp, vec[k - delta])) {
                        vec[k] = vec[k - delta];
                        k -= delta;
                    }
                    vec[k] = temp;
                }
            }
        }
    }

    // 希尔排序
    template <typename T, typename Comparator>
    void shellSort2(vector<T> &vec, Comparator comp)
    {
        int delta = 0;
        // 计算初始增量
        for ( ; delta <= vec.size() / 9; delta = 3 * delta + 1) {
            ;
        }

        for ( ; delta > 0; delta = (delta - 1) / 3) {
            for (int i = delta; i < vec.size(); ++i) {
                int j = i;
                T temp = vec[j];
                while (j >= delta && comp(temp, vec[j - delta])) {
                    vec[j] = vec[j - delta];
                    j -= delta;
                }
                vec[j] = temp;
            }
        }
    }
}

#endif  // ALGORITHM_SHELL_SORT_H