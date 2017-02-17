#ifndef ALGORITHM_HEAP_UTIL_TEST_H
#define ALGORITHM_HEAP_UTIL_TEST_H

#include <iostream>
#include <vector>
#include <functional>

#include <iostream>

#include "../../algorithm/heap/heap_util.h"
#include "../../algorithm/sort/heap_sort.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::vector;
    using std::greater;
    using std::less;

    void testHeapUtil()
    {
        int arr[] = { 33, 16, 28, 10, 7, 20, 17, 4, 5, 3 };
        vector<int> vecA, vecB;

        for (auto element : arr) {
            vecA.push_back(element);
            pushHeap(vecA, vecA.size(), greater<int>());

            vecB.push_back(element);
            pushHeap(vecB, vecB.size(), less<int>());
        }

        if (isHeap(vecA, vecA.size(), greater<int>())) {
            cout << "The elements of vecA can build a max heap" << endl;
        } else {
            cout << "The elements of vecA cannot build a max heap" << endl;
        }

        if (isHeap(vecB, vecB.size(), greater<int>())) {
            cout << "The elements of vecB can build a max heap" << endl;
        } else {
            cout << "The elements of vecB cannot build a max heap" << endl;
        }

        cout << endl;

        cout << "Max heap:\n\t";
        while (!vecA.empty()) {
            popHeap(vecA, vecA.size(), less<int>());
            cout << vecA.back() << "  ";
            vecA.pop_back();
        }
        cout << endl;

        cout << "Min heap:\n\t";
        while (!vecB.empty()) {
            popHeap(vecB, vecB.size(), greater<int>());
            cout << vecB.back() << "  ";
            vecB.pop_back();
        }
        cout << endl;

        vector<int> vecC;
        for (auto element : arr) {
            vecC.push_back(element);
            pushHeap(vecC, vecC.size(), greater<int>());
        }
        cout << endl;

        eraseHeap(vecC, 1, vecC.size(), greater<int>());

        cout << "Max heap:\n\t";
        while (!vecC.empty()) {
            popHeap(vecC, vecC.size(), less<int>());
            cout << vecC.back() << "  ";
            vecC.pop_back();
        }
        cout << endl;
    }
}

#endif  // ALGORITHM_HEAP_UTIL_TEST_H
