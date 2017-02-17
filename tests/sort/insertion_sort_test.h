#ifndef ALGORITHM_INSERTION_SORT_TEST_H
#define ALGORITHM_INSERTION_SORT_TEST_H

#include <vector>
#include <functional>

#include "../../algorithm/sort/insertion_sort.h"
#include "../../util/utils.h"
#include "../../util/timer.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testInsertionSort()
    {
        const int testSize = 10000;
        vector<int> vec(static_cast<unsigned long>(testSize));

        fillVectorWithRandomInt(vec, 0, testSize);
        cout << "Before sorting: " << endl;
        printContainer(vec.begin(), vec.end());
        cout << endl;

        Timer timer;
        timer.start();

        insertionSort(vec, std::less<int>());  // 升序排序
        // insertionSort(vec, std::greater<int>());  // 降序排序

        timer.stop();

        cout << "After sorting: " << endl;
        printContainer(vec.begin(), vec.end());
        cout << endl;

        cout << "Time taken: " << timer.time() << " ms" << endl;
    }
}

#endif  // ALGORITHM_INSERTION_SORT_TEST_H