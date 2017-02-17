#ifndef ALGORITHM_SINGLY_LINKED_LIST_UTIL_H
#define ALGORITHM_SINGLY_LINKED_LIST_UTIL_H

#include <string>

#include "singly_linked_list_node.h"

namespace myalgorithm {
    using std::string;

    // 打印单向链表节点
    template <typename T>
    void printLinkedList(SLLNode<T> *front, const string &separator = "  ")
    {
        SLLNode<T> *curr = front;
        while (curr != nullptr) {
            cout << curr->value << separator;
            curr = curr->next;
        }
    }

    // 创建链表新节点并返回指向它的指针
    template <typename T>
    SLLNode<T>* getNode(const T &value = T(), SLLNode<T> *next = nullptr)
    {
        SLLNode<T> *newNode = new SLLNode<T>(value, next);

        return newNode;
    }

    // 单向链表表头添加新节点
    template <typename T>
    void insertFront(SLLNode<T> *&front, const T &item)
    {
        SLLNode<T> *newNode = new SLLNode<T>(item);
        if (front != nullptr) {
            newNode->next = front;
        }
        front = newNode;
    }

    // 删除单向链表表头节点
    template <typename T>
    void eraseFront(SLLNode<T> *&front)
    {
        SLLNode<T> *toBeDelete = nullptr;
        if (front != nullptr) {
            toBeDelete = front;
            front = front->next;
            delete toBeDelete;
        }
    }

    // 清空单向链表
    template <typename T>
    void erase(SLLNode<T> *&front)
    {
        SLLNode<T> *toBeDelete = nullptr;
        while (front != nullptr) {
            toBeDelete = front;
            front = front->next;
            delete toBeDelete;
        }
    }

    // 删除单向链表中与 target 匹配的结点
    template <typename T>
    void erase(SLLNode<T> *&front, const T &target)
    {
        SLLNode<T> *prev = nullptr;
        SLLNode<T> *curr = front;
        while (curr != nullptr && curr->value != target) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != nullptr) {
            if (prev == nullptr) {
                front = front->next;
            } else {
                prev->next = curr->next;
            }

            delete curr;
        }
    }

    // 删除单向链表中所有与 target 匹配的节点
    template <typename T>
    void eraseAll(SLLNode<T> *&front, const T &target)
    {
        SLLNode<T> *prev = nullptr;
        SLLNode<T> *curr = front;
        SLLNode<T> *toBeDelete = nullptr;
        while (curr != nullptr) {
            if (curr->value == target) {
                toBeDelete = curr;
                if (prev == nullptr) {
                    front = curr->next;
                } else {
                    prev->next = curr->next;
                }
            }
            prev = curr;
            curr = curr->next;

            if (toBeDelete != nullptr) {
                delete toBeDelete;
                toBeDelete = nullptr;
            }
        }
    }

    // 单向链表删除表头节点
    // front 头指针，back 尾指针
    template <typename T>
    void eraseFront(SLLNode<T> *&front, SLLNode<T> *&back)
    {
        if (front != nullptr) {
            SLLNode<T> *toBeDelete = front;
            front = front->next;
            if (front == nullptr) {
                back = nullptr;
            }
            delete toBeDelete;
        }
    }

    // 单向链表删除表尾节点
    // front 头指针，back 尾指针
    template <typename T>
    void eraseBack(SLLNode<T> *&front, SLLNode<T> *&back)
    {
        if (front != nullptr) {
            SLLNode<T> *prev = nullptr;
            SLLNode<T> *curr = front;
            while (curr != back) {
                prev = curr;
                curr = curr->next;
            }

            delete back;

            if (prev == nullptr) {
                front = back = prev;
            } else {
                back = prev;
                back->next = nullptr;
            }
        }
    }

    // 单向链表添加表头节点
    // front 头指针，back 尾指针
    template <typename T>
    void insertFront(SLLNode<T> *&front, SLLNode<T> *&back, const T &item)
    {
        SLLNode<T> *newNode = new SLLNode<T>(item);
        if (front != nullptr) {
            newNode->next = front;
        } else {
            back = newNode;
        }
        front = newNode;
    }

    // 单向链表添加表尾节点
    // front 头指针，back 尾指针
    template <typename T>
    void insertBack(SLLNode<T> *&front, SLLNode<T> *&back, const T &item)
    {
        SLLNode<T> *newNode = new SLLNode<T>(item);
        if (front != nullptr) {
            back->next = newNode;
        } else {
            front = newNode;
        }
        back = newNode;
    }

    // 复制单向链表，同时维护头指针和尾指针
    template <typename T>
    SLLNode<T>* copy(SLLNode<T> *front)
    {
        if (front == nullptr) {
            return nullptr;
        }

        SLLNode<T> *newFront = new SLLNode<T>(front->value);
        SLLNode<T> *curr = front;
        SLLNode<T> *newBack = newFront;
        while ((curr = curr->next) != nullptr) {
            SLLNode<T> *newNode = new SLLNode<T>(curr->value);
            newBack = newBack->next = newNode;
        }

        return newFront;
    }

    // 逆序打印单向链表节点的值
    template <typename T>
    void outputReverse(SLLNode<T> *curr)
    {
        if (curr == nullptr) {
            return;
        }

        outputReverse(curr->next);
        cout << curr->value << " ";
    }
}

#endif  // ALGORITHM_SINGLY_LINKED_LIST_UTIL_H