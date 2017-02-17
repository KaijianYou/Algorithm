#ifndef ALGORITHM_BINARY_SEARCH_TEST_H
#define ALGORITHM_BINARY_SEARCH_TEST_H

#include <iostream>
#include <vector>
#include <functional>

#include "../../algorithm/search/binary_search.h"
#include "../../util/utils.h"
#include "../../algorithm/sort/shell_sort.h"

namespace myalgorithm {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::vector;
    using std::less;

    void testBinarySearch()
    {
        const int testSize = 20;

        vector<int> vec1(testSize);
        fillVectorWithRandomInt(vec1, 0, testSize);

        shellSort(vec1, less<int>());  // 将向量元素按升序排列

        cout << "vector element:" << endl << "\t";
        printContainer(vec1.begin(), vec1.end());

        cout << "Enter the number you want to search: ";
        int target;
        cin >> target;

        int index = -1;
        if ((index = binarySearch(vec1, target)) != -1) {
            cout << "Found " << target << " at index " << index << endl;
        } else {
            cout << "Target " << target << " can not found" << endl;
        }

        cout << endl;

        vector<int> vec2(testSize);
        fillVectorWithRandomInt(vec2, 0, testSize);

        shellSort(vec2, less<int>());  // 将向量元素按升序排列

        cout << "vector element:" << endl << "\t";
        printContainer(vec2.begin(), vec2.end());

        cout << "Enter the number you want to search: ";
        cin >> target;

        if ((index = binarySearch(vec2, 0, vec2.size(), target)) != -1) {
            cout << "Found " << target << " at index " << index << endl;
        } else {
            cout << "Target " << target << " can not found" << endl;
        }

        cout << endl;

        vector<int> vec3(testSize);
        fillVectorWithRandomInt(vec3, 0, testSize);

        shellSort(vec3, less<int>());

        int arr[testSize] = { 0 };
        int i = 0;
        for (auto element : vec3) {
            arr[i++] = element;
        }

        cout << "array element:" << endl << "\t";
        printArray(arr, testSize);

        cout << "Enter the number you want to search: ";
        cin >> target;

        if ((index = binarySearch(arr, 0, testSize, target)) != testSize) {
            cout << "Found " << target << " at index " << index << endl;
        } else {
            cout << "Target " << target << " can not found" << endl;
        }
    }
}

#endif  // ALGORITHM_BINARY_SEARCH_TEST_H