#ifndef ALGORITHM_SINGLY_LINKED_LIST_NODE_H
#define ALGORITHM_SINGLY_LINKED_LIST_NODE_H

namespace myalgorithm {
    template <typename T>
    struct SLLNode {
        T value;
        SLLNode<T> *next;

        SLLNode() : next(nullptr)
        {}

        SLLNode(const T &value, SLLNode<T> *next = nullptr) : value(value), next(next)
        {}
    };
}

#endif  // ALGORITHM_SINGLY_LINKED_LIST_NODE_H
