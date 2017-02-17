#ifndef ALGORITHM_SINGLY_LINKED_LIST_UTIL_TEST_H
#define ALGORITHM_SINGLY_LINKED_LIST_UTIL_TEST_H

#include <iostream>

#include "../../algorithm/list/singly_linked_list_util.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testSinglyLinkedListUtil()
    {
        SLLNode<int> *front = nullptr;
        int arr[] = { 5, 7, 8, 3, 2 };
        for (auto element : arr) {
            insertFront(front, element);
        }

        cout << "1 - list elements: ";
        printLinkedList(front);
        cout << endl;

        eraseFront(front);
        cout << "2 - list elements: ";
        printLinkedList(front);
        cout << endl;

        erase(front, 8);
        insertFront(front, 7);
        cout << "3 - list elements: ";
        printLinkedList(front);
        cout << endl;

        eraseAll(front, 7);
        cout << "4 - list elements: ";
        printLinkedList(front);
        cout << endl;

        erase(front);
        cout << "5 - list elements: ";
        printLinkedList(front);
        cout << endl;

        SLLNode<int> *back = nullptr;
        for (auto element : arr) {
            insertFront(front, back, element);
        }

        cout << "6 - list elements: ";
        printLinkedList(front);
        cout << endl;

        eraseFront(front, back);
        eraseBack(front, back);

        cout << "7 - list elements: ";
        printLinkedList(front);
        cout << endl;

        insertBack(front, back, 9);

        cout << "8 - list elements: ";
        printLinkedList(front);
        cout << endl;

        SLLNode<int> *newFront = copy(front);
        cout << "9 - list elements: ";
        printLinkedList(newFront);
        cout << endl;

        cout << "10 - list elements: ";
        outputReverse(front);
    }
}

#endif  // ALGORITHM_SINGLY_LINKED_LIST_UTIL_TEST_H