#ifndef ALGORITHM_PRIORITY_QUEUE_BASED_ON_VECTOR_H
#define ALGORITHM_PRIORITY_QUEUE_BASED_ON_VECTOR_H

#include <vector>
#include <stdexcept>

namespace myalgorithm {
    using std::vector;
    using std::underflow_error;

    // 基于向量的优先级队列的简单实现
    template <typename T>
    class PriorityQueue {
    public:
        PriorityQueue();
        virtual ~PriorityQueue();

        void push(const T &item);
        void pop();

        T& top();
        const T& top() const;

        bool empty() const;
        int size() const;

    private:
        vector<T> _vector;
        int maxIndex;
        bool recomputeMaxIndex;  // 是否需要重新计算最大元素的索引

        int findMaxIndex() const;
    };

    template <typename T>
    PriorityQueue<T>::PriorityQueue()
    {}

    template <typename T>
    PriorityQueue<T>::~PriorityQueue()
    {}

    template <typename T>
    void PriorityQueue<T>::push(const T &item)
    {
        _vector.push_back(item);
        recomputeMaxIndex = true;
    }

    template <typename T>
    void PriorityQueue<T>::pop()
    {
        if (empty()) {
            throw underflow_error("PriorityQueue.pop(): queue is empty");
        }

        if (recomputeMaxIndex) {
            maxIndex = findMaxIndex();
            recomputeMaxIndex = false;
        }

        _vector[maxIndex] = _vector[_vector.size() - 1];
        _vector.pop_back();
        recomputeMaxIndex = true;
    }

    template <typename T>
    T& PriorityQueue<T>::top()
    {
        if (empty()) {
            throw underflow_error("PriorityQueue.top(): queue is empty");
        }

        if (recomputeMaxIndex) {
            maxIndex = findMaxIndex();
            recomputeMaxIndex = false;
        }

        return _vector[maxIndex];
    }

    template <typename T>
    const T& PriorityQueue<T>::top() const
    {
        if (empty()) {
            throw underflow_error("PriorityQueue.top(): queue is empty");
        }

        if (recomputeMaxIndex) {
            maxIndex = findMaxIndex();
            recomputeMaxIndex = false;
        }

        return _vector[maxIndex];
    }

    template <typename T>
    bool PriorityQueue<T>::empty() const
    {
        return _vector.empty();
    }

    template <typename T>
    int PriorityQueue<T>::size() const
    {
        return static_cast<int>(_vector.size());
    }

    template <typename T>
    int PriorityQueue<T>::findMaxIndex() const
    {
        int tmpMaxIndex = 0;
        for (int i = 1; i < _vector.size(); ++i) {
            if (_vector[i] > _vector[tmpMaxIndex]) {
                tmpMaxIndex = i;
            }
        }

        return tmpMaxIndex;
    }
}

#endif  // ALGORITHM_PRIORITY_QUEUE_BASED_ON_VECTOR_H