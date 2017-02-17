#ifndef ALGORITHM_DOUBLY_LINKED_LIST_TEST_H
#define ALGORITHM_DOUBLY_LINKED_LIST_TEST_H

#include <iostream>

#include "../../algorithm/list/doubly_linked_list.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testDoublyLinkedList()
    {
        int arr[] = { 3, 5, 8, 9, 0, 6 };
        int arrSize = sizeof(arr) / sizeof(*arr);

        List<int> intList(arr, arr + arrSize);
        cout << "Initial intList size: " << intList.size() << endl;

        cout << "intList elements:\n\t";
        for (auto iter = intList.begin(); iter != intList.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl << endl;

        List<int> intList2 = intList;
        cout << "intList2 elements:\n\t";
        for (auto iter = intList2.begin(); iter != intList2.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl << endl;

        List<int> intList3(intList);
        cout << "1 - intList3 elements:\n\t";
        for (auto iter = intList3.begin(); iter != intList3.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl << endl;

        auto pos = intList3.begin();
        pos = intList3.insert(pos, 11);
        pos = intList3.insert(pos, 111);

        cout << "2 - intList3 elements:\n\t";
        for (auto iter = intList3.begin(); iter != intList3.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl << endl;

        pos = intList3.end();
        --pos;
        intList3.erase(pos);
        cout << "3 - intList3 elements:\n\t";
        for (auto iter = intList3.begin(); iter != intList3.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl << endl;

        intList3.push_front(100);
        intList3.push_back(44);
        cout << "  size=" << intList3.size() << endl;
        cout << "4 - intList3 elements:\n\t";
        for (auto iter = intList3.begin(); iter != intList3.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl << endl;

        intList3.pop_front();
        intList3.pop_back();
        cout << "intList3 front: " << intList3.front() << endl;
        cout << "intList3.back: " << intList3.back() << endl;
        cout << endl;

        for (auto iter = intList3.begin(); iter != intList3.end(); ) {
            iter = intList3.erase(iter);
        }
        cout << "intList3 size: " << intList3.size() << endl;
    }
}

#endif  // ALGORITHM_DOUBLY_LINKED_LIST_TEST_H
