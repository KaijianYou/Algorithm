#ifndef ALGORITHM_QUICK_SORT_H
#define ALGORITHM_QUICK_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 查找 [first, last) 索引范围内的中心值的索引
    // Comparator 是关系型函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    int partition(vector<T> &v, int first, int last, Comparator comp)
    {
        if (first == last) {
            return last;
        } else if (first == last - 1) {
            return first;
        } else {
            // 把位于中点的元素设为中心值，并交换该元素与表起点元素的位置
            // 确保左子表中的元素小（大）于中心值，右子表中的元素大（小）于中心值
            int mid = first + (last - first) / 2;
            T pivot = v[mid];
            v[mid] = v[first];
            v[first] = pivot;

            int i = first + 1;  // 从左向右开始遍历左子表的索引
            int j = last - 1;  // 从右向左开始遍历右子表的索引

            while (true) {
                // i 在左子表中向右移，在元素大（小）于中心值或 i 进入右子表时停下
                while (i <= j && comp(v[i], pivot)) {
                    ++i;
                }

                // j 在右子表中向左移，在元素小（大）于中心值或 j 进入左子表时停下
                while (j >= i && comp(pivot, v[j])) {
                    --j;
                }

                if (i >= j) {
                    break;
                }

                // 交换两个处于错误子表中的元素
                T temp = v[i];
                v[i] = v[j];
                v[j] = temp;

                ++i;
                --j;
            }

            v[first] =  v[j];
            v[j] = pivot;

            return j;
        }
    }

    // 快速排序
    template <typename T, typename Comparator>
    void quickSort(vector<T> &v, int first, int last, Comparator comp)
    {
        if (last - first <= 1) {
            return;
        } else if (last - first == 2) {
            if (comp(v[last - 1], v[first])) {
                T temp = v[last - 1];
                v[last - 1] = v[first];
                v[first] = temp;
            }

            return;
        } else {
            int pivotIndex = partition(v, first, last, comp);
            quickSort(v, first, pivotIndex, comp);
            quickSort(v, pivotIndex + 1, last, comp);
        }
    }

}

#endif  // ALGORITHM_QUICK_SORT_H