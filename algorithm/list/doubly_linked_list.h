#ifndef ALGORITHM_DOUBLY_LINKED_LIST_H
#define ALGORITHM_DOUBLY_LINKED_LIST_H

#include <stdexcept>

#include "doubly_linked_list_node.h"

namespace myalgorithm {
    using std::range_error;

    // 双向循环链表的简单实现
    template <typename T>
    class List {
    public:
        class Iterator;
        class ConstIterator;

        List();
        List(int n, const T &value = T());
        List(T *first, T *last);
        List(const List &obj);
        ~List();

        List& operator=(const List &rhs);

        bool empty() const;
        int size() const;

        void push_front(const T &item);
        void push_back(const T &item);
        void pop_front();
        void pop_back();

        T& front();
        T& back();
        const T& front() const;
        const T& back() const;

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

        Iterator insert(Iterator pos, const T &item);
        Iterator erase(Iterator pos);

    private:
        DLLNode<T> *header;
        int _size;

        // 分配新节点空间，并返回指向它的指针
        DLLNode<T>* getNode(const T &item);
        
        // 在 curr 节点前面插入值为 item 的新节点
        DLLNode<T>* _insert(DLLNode<T> *curr, const T &item);
        
        // 从链表中删除 curr 节点
        void _erase(DLLNode<T> *curr);
        
        // 清空链表节点
        void clear();
    };

    template <typename T>
    DLLNode<T>* List<T>::getNode(const T &item)
    {
        DLLNode<T> *newNode = new DLLNode<T>(item);
        return newNode;
    }

    template <typename T>
    DLLNode<T>* List<T>::_insert(DLLNode<T> *curr, const T &item)
    {
        DLLNode<T> *newNode = getNode(item);
        DLLNode<T> *prevNode = curr->prev;
        newNode->next = curr;
        newNode->prev = prevNode;
        prevNode->next = newNode;
        curr->prev = newNode;

        return newNode;
    }

    template <typename T>
    void List<T>::_erase(DLLNode<T> *curr)
    {
        if (curr->next == curr) {
            return;
        }

        DLLNode<T> *prevNode = curr->prev;
        DLLNode<T> *nextNode = curr->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete curr;
    }

    template <typename T>
    void List<T>::clear()
    {
        while (header->next != header) {
            _erase(header->next);
        }

        _size = 0;
        delete header;
    }

    template <typename T>
    List<T>::List() : _size(0)
    {
        header = new DLLNode<T>;
    }

    template <typename T>
    List<T>::List(int _size, const T &value) : _size(_size)
    {
        header = new DLLNode<T>;
        for (int i = 0; i < _size; ++i) {
            _insert(header->next, value);
        }
    }

    template <typename T>
    List<T>::List(T *first, T *last) : _size(0)
    {
        header = new DLLNode<T>;
        for (T *curr = first; curr != last; ++curr) {
            _insert(header, *curr);
            ++_size;
        }
    }

    template <typename T>
    List<T>::List(const List<T> &obj) : _size(obj._size)
    {
        header = new DLLNode<T>;
        DLLNode<T> *curr = obj.header->next;
        DLLNode<T> *end = obj.header;
        while (curr != end) {
            _insert(header, curr->value);
            curr = curr->next;
        }
    }

    template <typename T>
    List<T>::~List()
    {
        clear();
    }

    template <typename T>
    List<T>& List<T>::operator=(const List<T> &rhs)
    {
        if (this == &rhs) {
            return *this;
        }

        clear();

        header = new DLLNode<T>;
        DLLNode<T> *curr = rhs.header->next;
        DLLNode<T> *end = rhs.header;
        while (curr != end) {
            _insert(header, curr->value);
            curr = curr->next;
        }
        _size = rhs._size;

        return *this;
    }

    template <typename T>
    bool List<T>::empty() const
    {
        return size() == 0;
    }

    template <typename T>
    int List<T>::size() const
    {
        return _size;
    }

    template <typename T>
    void List<T>::push_front(const T &item)
    {
        _insert(header->next, item);
        ++_size;
    }

    template <typename T>
    void List<T>::push_back(const T &item)
    {
        _insert(header, item);
        ++_size;
    }


    template <typename T>
    void List<T>::pop_front()
    {
        if (empty()) {
            throw underflow_error("List.pop_front(): list is empty");
        }

        _erase(header->next);
        --_size;
    }

    template <typename T>
    void List<T>::pop_back()
    {
        if (empty()) {
            throw underflow_error("List.pop_back(): list is empty");
        }

        _erase(header->prev);
        --_size;
    }

    template <typename T>
    T& List<T>::front()
    {
        return header->next->value;
    }

    template <typename T>
    T& List<T>::back()
    {
        return header->prev->value;
    }

    template <typename T>
    const T& List<T>::front() const
    {
        return header->next->value;
    }

    template <typename T>
    const T& List<T>::back() const
    {
        return header->prev->value;
    }

    // 迭代器
    template <typename T>
    class List<T>::Iterator {
    public:
        friend class List<T>;
        friend class List<T>::ConstIterator;

        Iterator();

        bool operator==(const Iterator &rhs) const;
        bool operator!=(const Iterator &rhs) const;

        T& operator*();

        Iterator& operator++();
        Iterator& operator--();
        Iterator operator++(int);
        Iterator operator--(int);

    private:
        DLLNode<T> *ptr;
        // 把给定指针转换为迭代器
        Iterator(DLLNode<T> *ptr);
    };

    template <typename T>
    List<T>::Iterator::Iterator(DLLNode<T> *ptr) : ptr(ptr)
    {}

    template <typename T>
    List<T>::Iterator::Iterator()
    {}

    template <typename T>
    bool List<T>::Iterator::operator==(const Iterator &rhs) const
    {
        return this->ptr == rhs.ptr;
    }

    template <typename T>
    bool List<T>::Iterator::operator!=(const Iterator &rhs) const
    {
        return this->ptr != rhs.ptr;
    }

    template <typename T>
    T& List<T>::Iterator::operator*()
    {
        // 如果当前节点的后继节点也是自身，则链表为空
        if (ptr->next == ptr) {
            throw range_error("List::Iterator.*: reference error");
        }

        return ptr->value;
    }

    template <typename T>
    typename List<T>::Iterator& List<T>::Iterator::operator++()
    {
        ptr = ptr->next;
        return *this;
    }

    template <typename T>
    typename List<T>::Iterator& List<T>::Iterator::operator--()
    {
        ptr = ptr->prev;
        return *this;
    }

    template <typename T>
    typename List<T>::Iterator List<T>::Iterator::operator++(int)
    {
        Iterator iter = *this;
        ptr = ptr->next;
        return iter;
    }

    template <typename T>
    typename List<T>::Iterator List<T>::Iterator::operator--(int)
    {
        Iterator iter = *this;
        ptr = ptr->next;
        return iter;
    }

    // 常量迭代器
    template <typename T>
    class List<T>::ConstIterator {
    public:
        friend class List<T>;
        friend class List<T>::ConstIterator;

        ConstIterator();
        ConstIterator(const Iterator &pos);

        bool operator==(const ConstIterator &rhs) const;
        bool operator!=(const ConstIterator &rhs) const;

        const T& operator*() const;

        ConstIterator& operator++();
        ConstIterator& operator--();
        ConstIterator operator++(int);
        ConstIterator operator--(int);

    private:
        const DLLNode<T> *ptr;
        // 把给定指针转换为迭代器
        ConstIterator(const DLLNode<T> *ptr);
    };

    template <typename T>
    List<T>::ConstIterator::ConstIterator(const DLLNode<T> *ptr) : ptr(ptr)
    {}

    template <typename T>
    List<T>::ConstIterator::ConstIterator()
    {}

    template <typename T>
    List<T>::ConstIterator::ConstIterator(const Iterator &pos) : ptr(pos.ptr)
    {}

    template <typename T>
    bool List<T>::ConstIterator::operator==(const ConstIterator &rhs) const
    {
        return ptr == rhs.ptr;
    }

    template <typename T>
    bool List<T>::ConstIterator::operator!=(const ConstIterator &rhs) const
    {
        return ptr != rhs.ptr;
    }

    template <typename T>
    const T& List<T>::ConstIterator::operator*() const
    {
        // 如果当前节点的后继节点也是自身，则链表为空
        if (ptr->next == ptr) {
            throw range_error("List::ConstIterator.*: reference error");
        }

        return ptr->value;
    }

    template <typename T>
    typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
    {
        ptr = ptr->next;
        return ptr;
    }

    template <typename T>
    typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
    {
        ptr = ptr->prev;
        return ptr;
    }

    template <typename T>
    typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
    {
        ConstIterator iter = ptr;
        ptr = ptr->next;
        return iter;
    }

    template <typename T>
    typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
    {
        ConstIterator iter = ptr;
        ptr = ptr->prev;
        return iter;
    }

    template <typename T>
    typename List<T>::Iterator List<T>::insert(Iterator pos, const T &item)
    {
        DLLNode<T> *newNode = _insert(pos.ptr, item);
        ++_size;

        return Iterator(newNode);
    }

    template <typename T>
    typename List<T>::Iterator List<T>::erase(Iterator pos)
    {
        if (empty()) {
            throw underflow_error("List.erase(): list is empty");
        }

        Iterator nextIter = pos.ptr->next;
        _erase(pos.ptr);
        --_size;

        return nextIter;
    }

    template <typename T>
    typename List<T>::Iterator List<T>::begin()
    {
        return Iterator(header->next);
    }

    template <typename T>
    typename List<T>::Iterator List<T>::end()
    {
        return Iterator(header);
    }

    template <typename T>
    typename List<T>::ConstIterator List<T>::begin() const
    {
        return ConstIterator(header->next);
    }

    template <typename T>
    typename List<T>::ConstIterator List<T>::end() const
    {
        return ConstIterator(header);
    }
}

#endif  // ALGORITHM_DOUBLY_LINKED_LIST_H