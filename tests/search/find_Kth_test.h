#ifndef ALGORITHM_FIND_KTH_TEST_H
#define ALGORITHM_FIND_KTH_TEST_H

#include <iostream>
#include <vector>

#include "../../algorithm/search/find_Kth.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    void testFindKth()
    {
        vector<int> v(10);
        fillVectorWithRandomInt(v, 0, 10);

        removeVectorDupElements1(v);

        cout << "Vector elements: " << endl;
        printContainer(v.begin(), v.end());
        cout << endl;

        int k = 5;
        findKth(v, 0, static_cast<int>(v.size()), k);

        if (k % 10 == 1) {
            cout << "The 1st ";
        } else if (k % 10 == 2) {
            cout << "The 2nd ";
        } else {
            cout << "The " << k << "th ";
        }
        cout << "largest element is " << v[k - 1] << endl;
    }
}

#endif  // ALGORITHM_FIND_KTH_TEST_H
