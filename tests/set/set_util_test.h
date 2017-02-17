#ifndef ALGORITHM_SET_UTIL_TEST_H
#define ALGORITHM_SET_UTIL_TEST_H

#include <iostream>
#include <set>

#include "../../algorithm/set/set_util.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::set;

    void testSubSet()
    {
        int arrA[] = { 4, 6, 9, 0, 2, 1 };
        int arrASize = sizeof(arrA) / sizeof(*arrA);
        set<int> setA(arrA, arrA + arrASize);

        int arrB[] = { 4, 0, 2 };
        int arrBSize = sizeof(arrB) / sizeof(*arrB);
        set<int> setB(arrB, arrB + arrBSize);

        int arrC[] = { 4, 6, 7, 2 };
        int arrCSize = sizeof(arrC) / sizeof(*arrC);
        set<int> setC(arrC, arrC + arrCSize);

        if (subset(setB, setA)) {
            cout << "setB is subset of setA" << endl;
        }

        if (subset(setC, setA)) {
            cout << "setC is subset of setA" << endl;
        }

        if (subset(setA, setC)) {
            cout << "setA is subset of setC" << endl;
        }
        cout << endl;

        if (subset2(setB, setA)) {
            cout << "setB is subset of setA" << endl;
        }

        if (subset2(setC, setA)) {
            cout << "setC is subset of setA" << endl;
        }

        if (subset2(setA, setC)) {
            cout << "setA is subset of setC" << endl;
        }
        cout << endl;
    }

    void testSetOperation()
    {
        int arrA[] = { 32, 54, 87, 9, 43, 8, 15 };
        int arrASize = sizeof(arrA) / sizeof(*arrA);
        set<int> setA(arrA, arrA + arrASize);

        int arrB[] = { 54, 87, 77, 90, 0, 5 };
        int arrBSize = sizeof(arrB) / sizeof(*arrB);
        set<int> setB(arrB, arrB + arrBSize);

        set<int> unionSet = setA + setB;
        cout << "Union set:\n\t";
        printContainer(unionSet.begin(), unionSet.end());
        cout << endl;

        set<int> differSet = setA - setB;
        cout << "Difference set:\n\t";
        printContainer(differSet.begin(), differSet.end());
        cout << endl;

        set<int> interSet = setA * setB;
        cout << "Intersaction set:\n\t";
        printContainer(interSet.begin(), interSet.end());
        cout << endl;
    }

    void testPowerSet()
    {
        int arr[] = { 3, 5, 1, 2, 3, 9 };
        int arrSize = sizeof(arr) / sizeof(arrSize);

        set<int> s(arr, arr + arrSize);
        cout << "s elements:\n\t";
        for (auto iter = s.begin(); iter != s.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl;

        set<set<int>> powerSet = getPowerSet(s);
        cout << "Number of subsets: " << powerSet.size() << endl;
        cout << "power set:" << endl;
        printPowerSet(powerSet);
        cout << endl;
    }
}

#endif  // ALGORITHM_SET_UTIL_TEST_H