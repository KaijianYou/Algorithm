#ifndef ALGORITHM_SHELL_SORT_H
#define ALGORITHM_SHELL_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 希尔排序
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void shellSort(vector<T> &v, Comparator comp)
    {
        int N = v.size();
        int delta = 0;
        // 计算初始增量
        for ( ; delta <= N / 9; delta = 3 * delta + 1) {
            ;
        }

        for ( ; delta > 0; delta = (delta - 1) / 3) {
            // 对子表进行插入排序
            for (int i = 0; i < delta; ++i) {
                for (int j = i + delta; j < N; j += delta) {
                    int k = j;
                    T temp = v[k];
                    while (k >= delta && comp(temp, v[k - delta])) {
                        v[k] = v[k - delta];
                        k -= delta;
                    }
                    v[k] = temp;
                }
            }
        }
    }

    // 希尔排序
    template <typename T, typename Comparator>
    void shellSort2(vector<T> &v, Comparator comp)
    {
        int N = v.size();
        int delta = 0;
        // 计算初始增量
        for ( ; delta <= N / 9; delta = 3 * delta + 1) {
            ;
        }

        for ( ; delta > 0; delta = (delta - 1) / 3) {
            for (int i = delta; i < N; ++i) {
                int j = i;
                T temp = v[j];
                while (j >= delta && comp(temp, v[j - delta])) {
                    v[j] = v[j - delta];
                    j -= delta;
                }
                v[j] = temp;
            }
        }
    }
}

#endif  // ALGORITHM_SHELL_SORT_H