#ifndef ALGORITHM_QUICK_SORT_H
#define ALGORITHM_QUICK_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 查找 [first, last) 索引范围内的中心值的索引
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    int locatePivot(vector<T> &vec, int first, int last, Comparator comp)
    {
        if (first == last) {
            return last;
        } else if (first == last - 1) {
            return first;
        } else {
            // 把位于中点的元素设为中心值，并交换该元素与表起点元素的位置
            // 确保左子表中的元素小（大）于中心值，右子表中的元素大（小）于中心值
            int mid = first + ((last - first) >> 1);
            T pivot = vec[mid];
            vec[mid] = vec[first];
            vec[first] = pivot;

            int leftIndex = first + 1;  // 从左向右开始遍历左子表的索引
            int rightIndex = last - 1;  // 从右向左开始遍历右子表的索引

            while (true) {
                // leftIndex 在左子表中向右移，在元素大（小）于中心值或 leftIndex 进入右子表时停下
                while (leftIndex <= rightIndex && comp(vec[leftIndex], pivot)) {
                    ++leftIndex;
                }

                // rightIndex 在右子表中向左移，在元素小（大）于中心值或 rightIndex 进入左子表时停下
                while (rightIndex >= leftIndex && comp(pivot, vec[rightIndex])) {
                    --rightIndex;
                }

                if (leftIndex >= rightIndex) {
                    break;
                }

                // 交换两个处于错误子表中的元素
                T temp = vec[leftIndex];
                vec[leftIndex] = vec[rightIndex];
                vec[rightIndex] = temp;

                ++leftIndex;
                --rightIndex;
            }

            vec[first] =  vec[rightIndex];
            vec[rightIndex] = pivot;

            return rightIndex;
        }
    }

    // 快速排序
    template <typename T, typename Comparator>
    void quickSort(vector<T> &vec, int first, int last, Comparator comp)
    {
        if (last - first <= 1) {
            return;
        } else if (last - first == 2) {
            if (comp(vec[last - 1], vec[first])) {
                T temp = vec[last - 1];
                vec[last - 1] = vec[first];
                vec[first] = temp;
            }

            return;
        } else {
            int pivotIndex = locatePivot(vec, first, last, comp);
            quickSort(vec, first, pivotIndex, comp);
            quickSort(vec, pivotIndex + 1, last, comp);
        }
    }

}

#endif  // ALGORITHM_QUICK_SORT_H