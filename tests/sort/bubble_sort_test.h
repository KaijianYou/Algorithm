#ifndef ALGORITHMSORT_BUBBLE_SORT_TEST_H
#define ALGORITHMSORT_BUBBLE_SORT_TEST_H

#include <vector>
#include <functional>

#include "../../algorithm/sort/bubble_sort.h"
#include "../../util/utils.h"
#include "../../util/timer.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testBubbleSort()
    {
        const int testSize = 10000;
        vector<int> v(static_cast<unsigned long>(testSize));

        fillVectorWithRandomInt(v, 0, testSize);
        cout << "Before sorting: " << endl;
        printContainer(v.begin(), v.end());
        cout << endl;

        Timer timer;
        timer.start();

        bubbleSort(v, std::less<int>());  // 升序排序
        // bubbleSort(v, std::greater<int>());  // 降序排序

        timer.stop();

        cout << "After sorting: " << endl;
        printContainer(v.begin(), v.end());
        cout << endl;

        cout << "Time taken: " << timer.time() << " ms" << endl;
    }
}

#endif  // ALGORITHMSORT_BUBBLE_SORT_TEST_H