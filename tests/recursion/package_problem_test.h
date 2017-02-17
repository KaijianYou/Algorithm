#ifndef ALGORITHM_PACKAGE_PROBLEM_TEST_H
#define ALGORITHM_PACKAGE_PROBLEM_TEST_H

#include <iostream>
#include <vector>

#include "../../algorithm/recursion/package_problem.h"

namespace myalgorithm {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::vector;

    void testPackageProblem()
    {
        Item items[] = {
            Item(2, 1), Item(3, 4), Item(4, 3), Item(5, 6), Item(6, 8)
        };
        int numItems = sizeof(items) / sizeof(*items);

        vector<Item> itemVec(items, items + numItems);

        cout << "Enter the capacity of package: ";
        int capacity;
        cin >> capacity;

        Knapsack knapsack(itemVec, capacity);
        knapsack.displayMaxValueMatrix();
        cout << endl;
        knapsack.displayKnapsack();
    }
}

#endif  // ALGORITHM_PACKAGE_PROBLEM_TEST_H
