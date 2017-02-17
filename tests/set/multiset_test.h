#ifndef ALGORITHM_MULTISET_TEST_H
#define ALGORITHM_MULTISET_TEST_H

#include <iostream>

#include "../../algorithm/set/multiset_based_on_list.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testMultiSet()
    {
        int arr[] = { 3, 5, 7, 7, 8, 0, 3, 4, 5, 3 };
        int arrSize = sizeof(arr) / sizeof(*arr);

        MultiSet<int> ms(arr, arr + arrSize);
        cout << "Initial ms size: " << ms.size() << endl;

        cout << ms.count(3) << endl;

        auto iter = ms.insert(10);
        cout << "Insert " << *iter << " into ms" << endl;

        cout << "ms elements:\n\t";
        printContainer(ms.begin(), ms.end());
        cout << endl;

        ms.erase(7);
        cout << "ms elements:\n\t";
        printContainer(ms.begin(), ms.end());
        cout << endl;
    }
}

#endif  // ALGORITHM_MULTISET_TEST_H
