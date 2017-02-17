#ifndef ALGORITHM_RADIX_SORT_TEST_H
#define ALGORITHM_RADIX_SORT_TEST_H

#include <vector>
#include <functional>

#include "../../algorithm/sort/radix_sort.h"
#include "../../util/utils.h"
#include "../../util/timer.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testRadixSort()
    {
        const int testSize = 10000;
        vector<int> vec(static_cast<unsigned long>(testSize));

        fillVectorWithRandomInt(vec, 0, testSize);
        cout << "Before sorting: " << endl;
        printContainer(vec.begin(), vec.end());
        cout << endl;

        Timer timer;
        timer.start();

        int size = testSize;
        int radix = 1;
        while ((size = size / 10) != 0) {
            ++radix;
        }
        radixSort(vec, radix);  // 升序排序
        // radixSort(vec, radix);  // 降序排序

        timer.stop();

        cout << "After sorting: " << endl;
        printContainer(vec.begin(), vec.end());
        cout << endl;

        cout << "Time taken: " << timer.time() << " ms" << endl;
    }
}

#endif  // ALGORITHM_RADIX_SORT_TEST_H