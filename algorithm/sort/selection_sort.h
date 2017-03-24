#ifndef ALGORITHM_SELECTION_SORT_H
#define ALGORITHM_SELECTION_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 选择排序
    // 对数据进行 size - 1 次遍历，每一次都找出数组尾部未排序子表中的最小元素，
    // 并把它和当前循环的第一个位置的元素进行交换
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void selectionSort(vector<T> &v, Comparator comp)
    {
        int size = v.size();
        for (int i = 0; i < size - 1; ++i) {
            int minIndex = i;

            for (int j = i + 1; j < size; ++j) {
                if (comp(v[j], v[minIndex])) {
                    minIndex = j;
                }
            }

            if (minIndex != i) {
                T temp = v[i];
                v[i] = v[minIndex];
                v[minIndex] = temp;
            }
        }
    }

    // 双端选择排序
    // 每次循环结束，就将循环起点的元素交换为最小的元素，循环终点的元素交换为最大的元素，
    // 然后循环起点索引加一，循环终点索引减一，重复此过程，直到循环起点索引不小于循环终点索引
    template <typename T, typename Comparator>
    void deSelectionSort(vector<T> &v, Comparator comp)
    {
        int first = 0;
        int last = v.size() - 1;
        while (first < last) {
            int minIndex = first;
            int maxIndex = last;
            for (int i = first + 1; i < last; ++i) {
                if (comp(v[i], v[minIndex])) {
                    minIndex = i;
                }

                if (comp(v[maxIndex], v[i])) {
                    maxIndex = i;
                }
            }

            if (minIndex != first) {
                T temp = v[first];
                v[first] = v[minIndex];
                v[minIndex] = temp;
            }

            if (maxIndex != last) {
                T temp = v[last];
                v[last] = v[maxIndex];
                v[maxIndex] = temp;
            }

            ++first;
            --last;
        }
    }
}

#endif  // ALGORITHM_SELECTION_SORT_H