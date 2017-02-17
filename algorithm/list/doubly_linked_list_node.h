#ifndef ALGORITHM_DOUBLY_LINKED_LIST_NODE_H
#define ALGORITHM_DOUBLY_LINKED_LIST_NODE_H

namespace myalgorithm {
    // 双向循环链表节点
    // 永远有一个头结点，链表中第一个节点是 "头结点->next"，最后一个节点是 "头结点->prev"
    template <typename T>
    struct DLLNode {
        T value;
        DLLNode<T> *prev;
        DLLNode<T> *next;

        DLLNode()
        {
            prev = this;
            next = this;
        }

        DLLNode(const T &value) : value(value), prev(this), next(this)
        {}
    };
}

#endif  // ALGORITHM_DOUBLY_LINKED_LIST_NODE_H