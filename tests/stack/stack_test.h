#ifndef ALGORITHM_STACK_BASED_ON_VECTOR_TEST_H
#define ALGORITHM_STACK_BASED_ON_VECTOR_TEST_H

#include <iostream>

#include "../../algorithm/stack/stack_based_on_vector.h"
//#include "../../algorithm/stack/stack_based_on_array.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testStackBasedOnVector()
    {
        int arr[] = { 34, 65, 88, 43, 23, 10, 57, 39 };
        Stack<int> intStack;

        for (auto element : arr) {
            intStack.push(element);
        }

        while (!intStack.empty()) {
            cout << "pop: " << intStack.top() << endl;
            intStack.pop();
        }
        cout << endl;

        cout << "intStack size: " << intStack.size() << endl;
    }
}

#endif  // ALGORITHM_STACK_BASED_ON_VECTOR_TEST_H