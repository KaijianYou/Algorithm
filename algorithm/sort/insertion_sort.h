#ifndef ALGORITHM_INSERTION_SORT_H
#define ALGORITHM_INSERTION_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 插入排序
    // 假定第一个元素已经处于正确的位置，还需在 1 到 size - 1 的位置范围内进行
    // size - 1 次遍历来排序剩余的元素
    // 每个元素 target 都要与它前面的元素一一进行比较，只要没有比到表的起点位置
    // 而且 target 一直小于被比较的元素，在大于或等于 target 的第一个元素处停止比较，
    // 期间一直将元素后移一个位置，然后把 target 插入到这个元素的前一个位置
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void insertionSort(vector<T> &vec, Comparator comp)
    {
        for (int i = 1; i < vec.size(); ++i) {
            int j = i;
            T temp = vec[i];
            while (j > 0 && temp < vec[j - 1]) {
                vec[j] = vec[j - 1];
                --j;
            }
            vec[j] = temp;
        }
    }

    // 递归实现插入排序
    template <typename T, typename Comparator>
    void insertionSort(vector<T> &vec, int first, int last, Comparator comp)
    {
        if (first == last) {
            return;
        } else {
            insertionSort(vec, first, last - 1, comp);
            int j = last - 1;
            T temp = vec[j];
            while (j > first && comp(temp, vec[j - 1])) {
                vec[j] = vec[j - 1];
                --j;
            }
            vec[j] = temp;
        }
    }
}

#endif  // ALGORITHM_INSERTION_SORT_H