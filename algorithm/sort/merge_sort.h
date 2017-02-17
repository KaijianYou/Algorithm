#ifndef ALGORITHM_MERGE_SORT_H
#define ALGORITHM_MERGE_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 索引范围 [first, mid) 和 [mid, last) 内的元素已经排好序，将它们归并到有序序列中
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void merge(vector<T> &vec, int first, int mid, int last, Comparator comp)
    {
        std::vector<T> tempVec;
        int leftIndex = first;
        int rightIndex = mid;
        while (leftIndex < mid && rightIndex < last) {
            if (comp(vec[leftIndex], vec[rightIndex])) {
                tempVec.push_back(vec[leftIndex]);
                ++leftIndex;
            } else {
                tempVec.push_back(vec[rightIndex]);
                ++rightIndex;
            }
        }

        while (leftIndex < mid) {
            tempVec.push_back(vec[leftIndex]);
            ++leftIndex;
        }

        while (rightIndex < last) {
            tempVec.push_back(vec[rightIndex]);
            ++rightIndex;
        }

        leftIndex = first;
        for (int i = 0; i < tempVec.size(); ++i) {
            vec[leftIndex] = tempVec[i];
            ++leftIndex;
        }
    }

    // 归并排序
    template <typename T, typename Comparator>
    void mergeSort(vector<T> &vec, int first, int last, Comparator comp)
    {
        if (first + 1 < last) {
            int mid = first + ((last - first) >> 1);

            mergeSort(vec, first, mid, comp);
            mergeSort(vec, mid, last, comp);
            merge(vec, first, mid, last, comp);
        }
    }
}

#endif  // ALGORITHM_MERGE_SORT_H