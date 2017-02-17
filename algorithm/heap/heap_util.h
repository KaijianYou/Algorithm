#ifndef ALGORITHM_HEAP_UTIL_H
#define ALGORITHM_HEAP_UTIL_H

#include <vector>
#include <stdexcept>

namespace myalgorithm {
    using std::vector;
    
    // 从堆中 [0, last) 删除索引为 i 的元素，并调整堆以继续维持堆的特性
    // Comparator 是关系函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void eraseHeap(vector<T> &vec, int i, int last, Comparator comp)
    {
        if (vec.empty()) {
            throw std::underflow_error("vector is empty");
        }

        if (i != last - 1) {
            T temp = vec[i];
            vec[i] = vec[last - 1];
            vec[last - 1] = temp;

            int currIndex = i;
            T target = vec[currIndex];
            int childIndex = currIndex * 2 + 1;
            while (childIndex < last - 1) {
                if ((childIndex + 1 < last - 1) && comp(vec[childIndex + 1], vec[childIndex])) {
                    childIndex += 1;
                }

                if (comp(vec[childIndex], target)) {
                    vec[currIndex] = vec[childIndex];
                    currIndex = childIndex;
                    childIndex = currIndex * 2 + 1;
                } else {
                    break;
                }
            }
            vec[currIndex] = target;

            currIndex = i;
            target = vec[currIndex];
            int parentIndex = (currIndex - 1) / 2;
            while (parentIndex >= 0) {
                parentIndex = (currIndex - 1) / 2;
                if (comp(target, vec[parentIndex])) {
                    vec[currIndex] = vec[parentIndex];
                    currIndex = parentIndex;
                    parentIndex = (currIndex - 1) / 2;
                } else {
                    break;
                }
            }
            vec[currIndex] = target;
        }

        vec.pop_back();
    }

    // 判断 [0, last) 索引范围内的元素是否构成一个堆
    // Comparator 是关系函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    bool isHeap(const vector<T> &vec, int last, Comparator comp)
    {
        if (vec.empty()) {
            return false;
        }

        if (vec.size() == 1) {
            return true;
        }

        int lastParentIndex = (last - 2) / 2;  // 索引范围内的最后一个父节点
        // 从最后一个父节点开始遍历到根节点（索引为 0），判断父节点是否大于或小于左右两个子节点
        for (int currIndex = lastParentIndex; currIndex >= 0; --currIndex) {
            int leftChildIndex = currIndex * 2 + 1;
            if (!comp(vec[currIndex], vec[leftChildIndex])) {
                return false;
            }

            int rightChildIndex = currIndex * 2 + 2;
            if (rightChildIndex < last && !comp(vec[currIndex], vec[rightChildIndex])) {
                return false;
            }
        }

        return true;
    }

    // 恢复堆的顺序
    // [0, last - 1) 范围中的向量元素是一个堆，将 v[last - 1] 元素插入到堆中，
    // 使 [0, last) 是一个堆，函数对象 comp 用于比较元素
    // Comparator 是关系函数对象类型，用来比较元素大小
    template <typename T, typename Comparator>
    void pushHeap(vector<T> &vec, int last, Comparator comp)
    {
        int currIndex = last - 1;
        T temp = vec[last - 1];

        int parentIndex = (currIndex - 1) / 2;
        while (currIndex != 0) {
            if (comp(temp, vec[parentIndex])) {
                vec[currIndex] = vec[parentIndex];
                currIndex = parentIndex;
                parentIndex = (currIndex - 1) / 2;
            } else {
                break;
            }
        }

        vec[currIndex] = temp;
    }
}

#endif  // ALGORITHM_HEAP_UTIL_H