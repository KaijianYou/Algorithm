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
    void selectionSort(vector<T> &vec, Comparator comp)
    {
        int size = vec.size();
        for (int i = 0; i < size - 1; ++i) {
            int minIndex = i;

            for (int j = i + 1; j < size; ++j) {
                if (comp(vec[j], vec[minIndex])) {
                    minIndex = j;
                }
            }

            if (minIndex != i) {
                T exchangeTemp = vec[i];
                vec[i] = vec[minIndex];
                vec[minIndex] = exchangeTemp;
            }
        }
    }

    // 双端选择排序
    // 每次循环结束，就将循环起点的元素交换为最小的元素，循环终点的元素交换为最大的元素，
    // 然后循环起点索引加一，循环终点索引减一，重复此过程，直到循环起点索引不小于循环终点索引
    template <typename T, typename Comparator>
    void deSelectionSort(vector<T> &vec, Comparator comp)
    {
        int first = 0;
        int last = vec.size() - 1;
        while (first < last) {
            int minIndex = first;
            int maxIndex = last;
            for (int i = first + 1; i < last; ++i) {
                if (comp(vec[i], vec[minIndex])) {
                    minIndex = i;
                }

                if (comp(vec[maxIndex], vec[i])) {
                    maxIndex = i;
                }
            }

            if (minIndex != first) {
                T exchangeTemp = vec[first];
                vec[first] = vec[minIndex];
                vec[minIndex] = exchangeTemp;
            }

            if (maxIndex != last) {
                T exchangeTemp = vec[last];
                vec[last] = vec[maxIndex];
                vec[maxIndex] = exchangeTemp;
            }

            ++first;
            --last;
        }
    }
}

#endif  // ALGORITHM_SELECTION_SORT_H