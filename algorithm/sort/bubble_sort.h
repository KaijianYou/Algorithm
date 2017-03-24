#ifndef ALGORITHM_BUBBLE_SORT_H
#define ALGORITHM_BUBBLE_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 冒泡排序
    // Comparator 是函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void bubbleSort(vector<T> &v, Comparator comp)
    {
        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < v.size() - i - 1; ++j) {
                if (comp(v[j + 1], v[j])) {
                    T temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
    }

    // 冒泡排序
    // 每一轮排序中用一个标识指示是否有交换操作发生，如果没有，则本轮排序结束
    template <typename T, typename Comparator>
    void bubbleSort2(vector<T> &v, Comparator comp)
    {
        int size = v.size();
        bool hasChanged = false;
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - 1 - i; ++j) {
                if (comp(v[j + 1], v[j])) {
                    int temp = v[j + 1];
                    v[j + 1] = v[j];
                    v[j] = temp;
                    hasChanged = true;
                }
            }

            if (hasChanged) {
                hasChanged = false;
            } else {
                break;
            }
        }
    }
}

#endif  // ALGORITHM_BUBBLE_SORT_H