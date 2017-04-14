#ifndef ALGORITHM_HEAP_SORT_H
#define ALGORITHM_HEAP_SORT_H

#include <vector>

namespace myalgorithm {
    using std::vector;

    template <typename T, typename Comparator>
    void upHeap(vector<T> &v, int i, Comparator comp)
    {
        while (i != 0) {
            int parent = (i - 1) / 2;
            if (comp(v[parent], v[i])) {
                T temp = v[i];
                v[i] = v[parent];
                v[parent] = temp;
                i = parent;
            } else {
                break;
            }
        }
    }

    template <typename T, typename Comparator>
    void downHeap(vector<T> &v, int i, int size, Comparator comp)
    {
        int left = 2 * i + 1;
        while (left < size) {
            int more = left;
            int right = i * 2 + 2;
            if (right < size && comp(v[more], v[right])) {
                more = right;
            }
            if (comp(v[i], v[more])) {
                T temp = v[i];
                v[i] = v[more];
                v[more] = temp;
                i = more;
                left = i * 2 + 1;
            } else {
                break;
            }
        }
    }

    // 堆排序
    template <typename T, typename Comparator>
    void heapSort(vector<T> &v, Comparator comp)
    {
        for (int i = 0; i < v.size(); i++) {
            upHeap(v, i, comp);
        }

        for (int i = v.size() - 1; i > 0; i--) {
            T temp = v[0];
            v[0] = v[i];
            v[i] = temp;
            downHeap(v, 0, i, comp);
        }
    }
}

#endif  // ALGORITHM_HEAP_SORT_H