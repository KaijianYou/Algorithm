#ifndef ALGORITHM_BUBBLE_SORT_H
#define ALGORITHM_BUBBLE_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 冒泡排序
    // Comparator 是函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void bubbleSort(vector<T> &vec, Comparator comp)
    {
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < vec.size() - i - 1; ++j) {
                if (comp(vec[j + 1], vec[j])) {
                    T temp = vec[j];
                    vec[j] = vec[j + 1];
                    vec[j + 1] = temp;
                }
            }
        }
    }

    // 冒泡排序
    // 每一轮排序中用一个标识指示是否有交换操作发生，如果没有，则本轮排序结束
    template <typename T, typename Comparator>
    void bubbleSort2(vector<T> &vec, Comparator comp)
    {
        int size = vec.size();
        bool hasChanged = false;
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - 1 - i; ++j) {
                if (comp(vec[j + 1], vec[j])) {
                    int temp = vec[j + 1];
                    vec[j + 1] = vec[j];
                    vec[j] = temp;
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