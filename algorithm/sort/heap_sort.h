#ifndef ALGORITHM_HEAP_SORT_H
#define ALGORITHM_HEAP_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 删除元素
    // 重新调整堆的元素顺序，使其维持堆的特性
    template <typename T, typename Comparator>
    void adjustHeap(vector<T> &v, int first, int last, Comparator comp)
    {
        int currIndex = first;
        T target = v[first];

        int childIndex = 2 * currIndex + 1;
        while (childIndex < last) {
            if ((childIndex + 1 < last) && comp(v[childIndex], v[childIndex + 1])) {
                childIndex = childIndex + 1;
            }

            if (comp(target, v[childIndex])) {
                v[currIndex] = v[childIndex];
                currIndex = childIndex;
                childIndex = 2 * currIndex + 1;
            } else {
                break;
            }
        }

        v[currIndex] = target;
    }

    // 删除堆的根节点
    template <typename T, typename Comparator>
    void popHeap(vector<T> &v, int last, Comparator comp)
    {
        T temp = v[0];
        v[0] = v[last - 1];
        v[last - 1] = temp;

        adjustHeap(v, 0, last - 1, comp);
    }

    // 向量堆化
    template <typename T, typename Comparator>
    void makeHeap(vector<T> &v, Comparator comp)
    {
        int last = v.size();
        int heapPos = (last - 2) / 2;
        while (heapPos >= 0) {
            adjustHeap(v, heapPos, last, comp);
            --heapPos;
        }
    }

    // 堆排序
    template <typename T, typename Comparator>
    void heapSort(vector<T> &v, Comparator comp)
    {
        makeHeap(v, comp);

        for (int i = static_cast<int>(v.size()); i > 1; --i) {
            popHeap(v, i, comp);
        }
    }
}

#endif  // ALGORITHM_HEAP_SORT_H