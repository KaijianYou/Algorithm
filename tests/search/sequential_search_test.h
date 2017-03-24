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
        vector<int> v(20);
        fillVectorWithRandomInt(v, 0, 20);

        cout << "vector element:" << endl << "\t";
        printContainer(v.begin(), v.end());

        cout << "Enter the number you want to search: ";
        int key;
        cin >> key;

        if (sequentialSearch(v.begin(), v.end(), key) != v.end()) {
            cout << "Found " << key << endl;
        } else {
            cout << "Target " << key << " can not found" << endl;
        }

        cout << endl;

        const int size = 20;
        int arr[size] = { 0 };
        fillArrayWithRandomInt(arr, 20, 0, 20);

        cout << "array element:" << endl << "\t";
        printArray(arr, size);

        cout << "Enter the number you want to search: ";
        cin >> key;

        int index = 0;
        if ((index = sequentialSearch(arr, 0, size, key)) != size) {
            cout << "Found " << key << " at index " << index << endl;
        } else {
            cout << "Target " << key << " can not found" << endl;
        }
    }
}

#endif  // ALGORITHM_SEQUENTIAL_SEARCH_TEST_H
