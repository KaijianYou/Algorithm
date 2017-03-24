#ifndef ALGORITHM_MERGE_SORT_H
#define ALGORITHM_MERGE_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 索引范围 [first, mid) 和 [mid, last) 内的元素已经排好序，将它们归并到有序序列中
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void merge(vector<T> &v, int first, int mid, int last, Comparator comp)
    {
        vector<T> tempVec;
        int i = first;
        int j = mid;
        while (i < mid && j < last) {
            if (comp(v[i], v[j])) {
                tempVec.push_back(v[i]);
                ++i;
            } else {
                tempVec.push_back(v[j]);
                ++j;
            }
        }

        while (i < mid) {
            tempVec.push_back(v[i]);
            ++i;
        }

        while (j < last) {
            tempVec.push_back(v[j]);
            ++j;
        }

        i = first;
        for (int i = 0; i < tempVec.size(); ++i) {
            v[i] = tempVec[i];
            ++i;
        }
    }

    // 归并排序
    template <typename T, typename Comparator>
    void mergeSort(vector<T> &v, int first, int last, Comparator comp)
    {
        if (first + 1 < last) {
            int mid = first + (last - first) / 2;

            mergeSort(v, first, mid, comp);
            mergeSort(v, mid, last, comp);
            merge(v, first, mid, last, comp);
        }
    }
}

#endif  // ALGORITHM_MERGE_SORT_H