#ifndef ALGORITHM_PRIORITY_QUEUE_BASED_ON_HEAP_H
#define ALGORITHM_PRIORITY_QUEUE_BASED_ON_HEAP_H

#include <stdexcept>

#include <vector>
#include <functional>

namespace myalgorithm {
    using std::greater;
    using std::vector;
    using std::underflow_error;
    
    // 基于堆的优先级队列的简单实现
    template <typename T, typename Comparator = greater<T>>
    class PriorityQueue {
    public:
        PriorityQueue();
        PriorityQueue(T *first, T *last);
        PriorityQueue(const PriorityQueue &obj);
        virtual ~PriorityQueue();

        PriorityQueue operator=(const PriorityQueue &obj);

        int size() const;
        bool empty() const;

        void push(const T &item);
        void pop();

        T& top();
        const T& top() const;

    private:
        vector<T> _vector;
        Comparator comp;

        void pushHeap();
        void popHeap();
        void adjustHeap(int first, int last);
    };

    template <typename T, typename Comparator>
    void PriorityQueue<T, Comparator>::pushHeap()
    {
        int last = static_cast<int>(_vector.size());
        int currIndex = last - 1;
        T target = _vector[last - 1];

        int parentPos = (currIndex - 1) / 2;
        while (currIndex != 0) {
            if (comp(target, _vector[parentPos])) {
                _vector[currIndex] = _vector[parentPos];
                currIndex = parentPos;
                parentPos = (currIndex - 1) / 2;
            } else {
                break;
            }
        }

        _vector[currIndex] = target;
    }

    template <typename T, typename Comparator>
    void PriorityQueue<T, Comparator>::popHeap()
    {
        int last = static_cast<int>(_vector.size());
        T temp = _vector[0];
        _vector[0] = _vector[last - 1];
        _vector[last - 1] = temp;

        adjustHeap(0, last - 1);
    }

    template <typename T, typename Comparator>
    void PriorityQueue<T, Comparator>::adjustHeap(int first, int last)
    {
        int currIndex = first;
        T target = _vector[first];

        int childIndex = 2 * currIndex + 1;
        while (childIndex < last) {
            if ((childIndex + 1 < last) && comp(_vector[childIndex + 1], _vector[childIndex])) {
                childIndex = childIndex + 1;
            }

            if (comp(_vector[childIndex], target)) {
                _vector[currIndex] = _vector[childIndex];
                currIndex = childIndex;
                childIndex = 2 * currIndex + 1;
            } else {
                break;
            }
        }

        _vector[currIndex] = target;
    }

    template <typename T, typename Comparator>
    PriorityQueue<T, Comparator>::PriorityQueue()
    {}

    template <typename T, typename Comparator>
    PriorityQueue<T, Comparator>::PriorityQueue(T *first, T *last)
    {
        while (first != last) {
            push(*first++);
        }
    }

    template <typename T, typename Comparator>
    PriorityQueue<T, Comparator>::PriorityQueue(const PriorityQueue &obj)
        : _vector(obj._vector), comp(obj.comp)
    {}

    template <typename T, typename Comparator>
    PriorityQueue<T, Comparator>::~PriorityQueue()
    {}

    template <typename T, typename Comparator>
    PriorityQueue<T, Comparator> PriorityQueue<T, Comparator>::operator=(const PriorityQueue &obj)
    {
        if (this != &obj) {
            comp = obj.comp;
            _vector = obj._vector;
        }

        return *this;
    }

    template <typename T, typename Comparator>
    int PriorityQueue<T, Comparator>::size() const
    {
        return static_cast<int>(_vector.size());
    }

    template <typename T, typename Comparator>
    bool PriorityQueue<T, Comparator>::empty() const
    {
        return size() == 0;
    }

    template <typename T, typename Comparator>
    void PriorityQueue<T, Comparator>::push(const T &item)
    {
        _vector.push_back(item);
        pushHeap();
    }

    template <typename T, typename Comparator>
    void PriorityQueue<T, Comparator>::pop()
    {
        if (empty()) {
            throw underflow_error("PriorityQueue.pop(): queue is empty");
        }

        popHeap();  // 把最大元素复制到向量结尾
        _vector.pop_back();
    }

    template <typename T, typename Comparator>
    T& PriorityQueue<T, Comparator>::top()
    {
        if (empty()) {
            throw underflow_error("PriorityQueue.top(): queue is empty");
        }

        return _vector[0];
    }

    template <typename T, typename Comparator>
    const T& PriorityQueue<T, Comparator>::top() const
    {
        if (empty()) {
            throw underflow_error("PriorityQueue.top(): queue is empty");
        }

        return _vector[0];
    }
}

#endif  // ALGORITHM_PRIORITY_QUEUE_BASED_ON_HEAP_H