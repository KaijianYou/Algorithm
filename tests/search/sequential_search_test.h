#ifndef ALGORITHM_SEQUENTIAL_SEARCH_TEST_H
#define ALGORITHM_SEQUENTIAL_SEARCH_TEST_H

#include <iostream>
#include <vector>

#include "../../algorithm/search/sequential_search.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    void testSequentialSearch()
    {
        vector<int> vec(20);
        fillVectorWithRandomInt(vec, 0, 20);

        cout << "vector element:" << endl << "\t";
        printContainer(vec.begin(), vec.end());

        cout << "Enter the number you want to search: ";
        int target;
        cin >> target;

        if (sequentialSearch(vec.begin(), vec.end(), target) != vec.end()) {
            cout << "Found " << target << endl;
        } else {
            cout << "Target " << target << " can not found" << endl;
        }

        cout << endl;

        const int size = 20;
        int arr[size] = { 0 };
        fillArrayWithRandomInt(arr, 20, 0, 20);

        cout << "array element:" << endl << "\t";
        printArray(arr, size);

        cout << "Enter the number you want to search: ";
        cin >> target;

        int index = 0;
        if ((index = sequentialSearch(arr, 0, size, target)) != size) {
            cout << "Found " << target << " at index " << index << endl;
        } else {
            cout << "Target " << target << " can not found" << endl;
        }
    }
}

#endif  // ALGORITHM_SEQUENTIAL_SEARCH_TEST_H
