#ifndef ALGORITHM_DOUBLY_LINKED_LIST_UTIL_TEST_H
#define ALGORITHM_DOUBLY_LINKED_LIST_UTIL_TEST_H

#include <iostream>

#include "../../algorithm/list/doubly_linked_list_util.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testDoublyLinkedListUtil()
    {
        DLLNode<int> *header = new DLLNode<int>;

        insert(header, 5);
        push_front(header, 9);
        push_back(header, 0);

        cout << "1 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        cout << "front: " << front(header) << endl;
        cout << "back: " << back(header) << endl;
        cout << endl;

        erase(header->next);
        cout << "2 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        pop_front(header);
        pop_back(header);
        cout << "3 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        insertAfter(header->next, 6);
        cout << "4 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        int arr[] = { 4, 6, 0, 3, 8 };
        for (auto element : arr) {
            insertOrder(header, element);
        }

        cout << "5 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        reverseDLList(header);
        cout << "6 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        clear(header);
        cout << "7 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        for (auto element : arr) {
            insertOrder(header, element);
        }
        cout << "8 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;

        eraseRange(header->next->next, header);

        cout << "9 - list elements: ";
        printDoublyLinkedList(header);
        cout << endl << endl;
    }
}

#endif  // ALGORITHM_DOUBLY_LINKED_LIST_UTIL_TEST_H
