#ifndef ALGORITHM_QUEUE_BASED_ON_SINGLY_LINKED_LIST_H
#define ALGORITHM_QUEUE_BASED_ON_SINGLY_LINKED_LIST_H

#include "../../algorithm/list/singly_linked_list_node.h"

namespace myalgorithm {
    // 基于单向链表的队列的简单实现
    template <typename T>
    class Queue {
    public:
        Queue();
        Queue(const Queue<T> &obj);
        virtual ~Queue();

        void push(const T &item);
        void pop();

        T& front();
        const T& front() const;

        bool empty() const;
        int size() const;

        Queue<T>& operator=(const Queue<T> &rhs);

    private:
        SLLNode<T> *_front;
        SLLNode<T> *_back;
        int _size;

        // 复制队列
        void copy(const Queue<T> &obj);

        // 清空链表
        void clear();

        // 分配新节点
        SLLNode<T>* getNode(const T &item);
    };

    template <typename T>
    void Queue<T>::copy(const Queue<T> &obj)
    {
        _front = _back = nullptr;

        SLLNode<T> *curr = obj._front;
        if (curr != nullptr) {
            _front = _back = getNode(curr->value);
            while ((curr = curr->next) != nullptr) {
                _back = _back->next = getNode(curr->value);
            }
        }

        _size = obj._size;
    }

    template <typename T>
    void Queue<T>::clear()
    {
        SLLNode<T> *toBeDelete = nullptr;
        while (_front != nullptr) {
            toBeDelete = _front;
            _front = _front->next;
            delete toBeDelete;
        }
    }

    template <typename T>
    SLLNode<T>* Queue<T>::getNode(const T &item)
    {
        SLLNode<T> *newNode = new SLLNode<T>(item);
        return newNode;
    }

    template <typename T>
    Queue<T>::Queue() : _front(nullptr), _back(nullptr), _size(0)
    {}

    template <typename T>
    Queue<T>::Queue(const Queue<T> &obj)
    {
        clear();
        copy();
    }

    template <typename T>
    Queue<T>::~Queue()
    {
        clear();
    }

    template <typename T>
    void Queue<T>::push(const T &item)
    {
        SLLNode<T> *newNode = getNode(item);
        if (_front == nullptr) {
            _front = _back = newNode;
        } else {
            _back = _back->next = newNode;
        }

        _size += 1;
    }

    template <typename T>
    void Queue<T>::pop()
    {
        if (empty()) {
            throw underflow_error("Queue.pop(): queue is emtpy");
        }

        SLLNode<T> *toBeDelete = _front;
        _front = _front->next;
        if (_front == nullptr) {
            _back = nullptr;
        }

        delete toBeDelete;

        _size -= 1;
    }

    template <typename T>
    T& Queue<T>::front()
    {
        return _front->value;
    }

    template <typename T>
    const T& Queue<T>::front() const
    {
        return _front->value;
    }

    template <typename T>
    bool Queue<T>::empty() const
    {
        return size() == 0;
    }

    template <typename T>
    int Queue<T>::size() const
    {
        return _size;
    }

    template <typename T>
    Queue<T>& Queue<T>::operator=(const Queue<T> &rhs)
    {
        clear();
        copy(rhs);

        return *this;
    }
}

#endif  // ALGORITHM_QUEUE_BASED_ON_SINGLY_LINKED_LIST_H