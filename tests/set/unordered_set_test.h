#ifndef ALGORITHM_UNORDERED_SET_TEST_H
#define ALGORITHM_UNORDERED_SET_TEST_H

#include <iostream>

#include "../../algorithm/set/unordered_set_based_on_hash_table.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testUnorderedSet()
    {
        int arr[] = { 4, 5, 8, 9, 6, 1, 0, 2 };
        int arrSize = sizeof(arr) / sizeof(arrSize);

        UnorderedSet<int, HashInt> us(arr, arr + arrSize);
        cout << "Initial us size: " << us.size() << endl;

        cout << "us elements:\n\t";
        printContainer(us.begin(), us.end());
        cout << endl;

        auto ret = us.find(9);
        if (ret != us.end()) {
            cout << *ret << endl;
        }
        cout << endl;

        us.erase(ret);
        cout << "us elements:\n\t";
        printContainer(us.begin(), us.end());
        cout << endl;

        us.insert(11);
        us.insert(3);
        cout << "us elements:\n\t";
        printContainer(us.begin(), us.end());
        cout << endl;

        cout << "us size: " << us.size() << endl;
    }
}

#endif  // ALGORITHM_UNORDERED_SET_TEST_H
