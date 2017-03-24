#ifndef ALGORITHM_EXCHANGE_SORT_TEST_H
#define ALGORITHM_EXCHANGE_SORT_TEST_H

#include <vector>
#include <functional>

#include "../../algorithm/sort/exchange_sort.h"
#include "../../util/utils.h"
#include "../../util/timer.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testExchangeSort()
    {
        const int testSize = 10000;
        vector<int> v(static_cast<unsigned long>(testSize));

        fillVectorWithRandomInt(v, 0, testSize);
        cout << "Before sorting: " << endl;
        printContainer(v.begin(), v.end());
        cout << endl;

        Timer timer;
        timer.start();

        exchangeSort(v, std::less<int>());  // 升序排序
        // exchangeSort(v, std::greater<int>());  // 降序排序

        timer.stop();

        cout << "After sorting: " << endl;
        printContainer(v.begin(), v.end());
        cout << endl;

        cout << "Time taken: " << timer.time() << " ms" << endl;
    }
}

#endif // ALGORITHM_EXCHANGE_SORT_TEST_H