#ifndef ALGORITHM_ARRAY_UTIL_TEST_H
#define ALGORITHM_ARRAY_UTIL_TEST_H

#include <iostream>

#include "../../algorithm/array/array_util.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testNumUnique()
    {
        const int arrSize = 10;
        int arr[arrSize] = { 0 };
        fillArrayWithRandomInt(arr, arrSize, 0, arrSize);

        cout << "arr elements:\n\t";
        printArray(arr, arrSize);

        cout << "The quantity of unique element: " << numUnique(arr, arrSize) << endl;
    }
}

#endif  // ALGORITHM_ARRAY_UTIL_TEST_H
