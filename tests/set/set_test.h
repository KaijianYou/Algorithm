#ifndef ALGORITHM_SET_TEST_H
#define ALGORITHM_SET_TEST_H

#include <iostream>

#include "../../algorithm/set/set_based_on_binary_search_tree.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testSet()
    {
        int arr[] = { 5, 6, 8, 1, 2, 0, 3, 0, 5, 6, 2 };
        int arrSize = sizeof(arr) / sizeof(*arr);

        Set<int> setA;
        cout << "Initial setA size: " << setA.size() << endl;
        for (auto element : arr) {
            setA.insert(element);
        }
        cout << "setA size: " << setA.size() << endl;

        cout << "setA elements:\n\t";
        printContainer(setA.begin(), setA.end());
        cout << endl;

        Set<int> setB(setA);
        cout << "setB elements:\n\t";
        printContainer(setA.begin(), setA.end());
        cout << endl;

        if (setB.contains(1)) {
            cout << "elete 1 from setB" << endl;
            setB.erase(1);
        }
        cout << "setB elements:\n\t";
        printContainer(setB.begin(), setB.end());
        cout << endl;

        auto ret = setA.find(8);
        setA.erase(ret);
        cout << "setA elements:\n\t";
        printContainer(setA.begin(), setA.end());
    }
}

#endif  // ALGORITHM_SET_TEST_H