#ifndef ALGORITHM_DOUBLY_LINKED_LIST_UTIL_H
#define ALGORITHM_DOUBLY_LINKED_LIST_UTIL_H

#include <iostream>

#include "doubly_linked_list_node.h"

namespace myalgorithm {
    // 打印双向循环链表的节点
    template <typename T>
    void printDoublyLinkedList(DLLNode<T> *header, const std::string &separator = "  ")
    {
        DLLNode<T> *curr = header->next;
        while (curr != header) {
            cout << curr->value << separator;
            curr = curr->next;
        }
    }

    // 在双向循环链表 curr 节点前插入新节点，并返回指向新节点的指针
    template <typename T>
    DLLNode<T>* insert(DLLNode<T> *curr, const T &item)
    {
        DLLNode<T> *newNode = new DLLNode<T>(item);
        DLLNode<T> *prevNode = curr->prev;

        newNode->next = curr;
        newNode->prev = prevNode;
        prevNode->next = newNode;
        curr->prev = newNode;

        return newNode;
    }

    // 双向循环链表删除指定节点
    template <typename T>
    void erase(DLLNode<T> *curr)
    {
        // 只有一个头结点，即空链表
        if (curr->next == curr) {
            return;
        }

        DLLNode<T> *prevNode = curr->prev;
        DLLNode<T> *nextNode = curr->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete curr;
    }

    // 双向循环链表插入表头节点
    template <typename T>
    void push_front(DLLNode<T> *header, const T &item)
    {
        insert(header->next, item);
    }

    // 双向循环链表插入表尾节点
    template <typename T>
    void push_back(DLLNode<T> *header, const T &item)
    {
        insert(header, item);
    }

    // 删除双向循环链表表头节点
    template <typename T>
    void pop_front(DLLNode<T> *header)
    {
        erase(header->next);
    }

    // 删除双向循环链表表尾节点
    template <typename T>
    void pop_back(DLLNode<T> *header)
    {
        erase(header->prev);
    }

    // 返回双向循环链表的表头节点值
    template <typename T>
    T& front(DLLNode<T> *header)
    {
        return header->next->value;
    }

    // 返回双向循环链表的表尾节点值
    template <typename T>
    T& back(DLLNode<T> *header)
    {
        return header->prev->value;
    }

    // 清空双向循环链表
    template <typename T>
    void clear(DLLNode<T> *header)
    {
        while (header->next != header) {
            erase(header->next);
        }
    }

    // 在双向循环链表 curr 节点后插入新节点
    template <typename T>
    void insertAfter(DLLNode<T> *curr, const T &item)
    {
        DLLNode<T> *newNode = new DLLNode<T>(item);
        newNode->prev = curr;
        newNode->next = curr->next;
        curr->next->prev = newNode;
        curr->next = newNode;
    }

    // 在双向循环链表中插入新节点，同时维持链表节点按照升序排列
    template <typename T>
    void insertOrder(DLLNode<T> *header, const T &item)
    {
        DLLNode<T> *curr = header->next;
        DLLNode<T> *end = header;
        while (curr != end && curr->value < item) {
            curr = curr->next;
        }

        DLLNode<T> *newNode = new DLLNode<T>(item);
        curr->prev->next = newNode;
        newNode->prev = curr->prev;
        curr->prev = newNode;
        newNode->next = curr;
    }

    // 从双向链表中把 [first, last) 范围内的所有节点删除
    template <typename T>
    void eraseRange(DLLNode<T> *first, DLLNode<T> *last)
    {
        DLLNode<T> *curr = first;
        while (curr != last) {
            DLLNode<T> *toBeDelete = curr;
            curr = curr->next;
            toBeDelete->prev->next = toBeDelete->next;
            toBeDelete->next->prev = toBeDelete->prev;
        }
    }

    // 把双向循环链表中的节点倒序排列
    template <typename T>
    void reverseDLList(DLLNode<T> *header)
    {
        DLLNode<T> *first = header->next;
        DLLNode<T> *last = header->prev;
        while (first != last && last != first->prev) {
            T exchangeTemp = first->value;
            first->value = last->value;
            last->value = exchangeTemp;
            first = first->next;
            last = last->prev;
        }
    }   
}

#endif  // ALGORITHM_DOUBLY_LINKED_LIST_UTIL_H