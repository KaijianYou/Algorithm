#ifndef ALGORITHM_HEAP_SORT_H
#define ALGORITHM_HEAP_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    // 删除元素
    // 重新调整堆的元素顺序，使其维持堆的特性
    template <typename T, typename Comparator>
    void adjustHeap(vector<T> &vec, int first, int last, Comparator comp)
    {
        int currIndex = first;
        T target = vec[first];

        int childIndex = 2 * currIndex + 1;
        while (childIndex < last) {
            if ((childIndex + 1 < last) && comp(vec[childIndex], vec[childIndex + 1])) {
                childIndex = childIndex + 1;
            }

            if (comp(target, vec[childIndex])) {
                vec[currIndex] = vec[childIndex];
                currIndex = childIndex;
                childIndex = 2 * currIndex + 1;
            } else {
                break;
            }
        }

        vec[currIndex] = target;
    }

    // 删除堆的根节点
    template <typename T, typename Comparator>
    void popHeap(vector<T> &vec, int last, Comparator comp)
    {
        T temp = vec[0];
        vec[0] = vec[last - 1];
        vec[last - 1] = temp;

        adjustHeap(vec, 0, last - 1, comp);
    }

    // 向量堆化
    template <typename T, typename Comparator>
    void makeHeap(vector<T> &vec, Comparator comp)
    {
        int last = vec.size();
        int heapPos = (last - 2) / 2;
        while (heapPos >= 0) {
            adjustHeap(vec, heapPos, last, comp);
            --heapPos;
        }
    }

    // 堆排序
    template <typename T, typename Comparator>
    void heapSort(vector<T> &vec, Comparator comp)
    {
        makeHeap(vec, comp);

        for (int i = static_cast<int>(vec.size()); i > 1; --i) {
            popHeap(vec, i, comp);
        }
    }
}

#endif  // ALGORITHM_HEAP_SORT_H