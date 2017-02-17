#ifndef ALGORITHM_BIT_BASED_ON_VECTOR_TEST_H
#define ALGORITHM_BIT_BASED_ON_VECTOR_TEST_H

#include <iostream>

#include "../../algorithm/vector/bit_based_on_vector.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testBitBasedOnVector()
    {
        int arr[] = { 1, 0, 1, 1, 0, 1 };
        int arrSize = sizeof(arr) / sizeof(*arr);

        Bit x(arr, arrSize), y(arrSize), z(arrSize);
        cout << "original x: " << x << endl;
        cout << "original y: " << y << endl;
        cout << "origianl z: " << z << endl;

        y.set(0);
        cout << "y: " << y << endl;
        y.set(4);
        cout << "y: " << y << endl;

        x.clear(2);
        cout << "x: " << x << endl;

        z = x | y;
        cout << "z: " << z << endl;
        z = ~x;
        cout << "z: " << z << endl;

        x = x << 2;
        cout << "x: " << x << endl;

        y = y >> 3;
        cout << "y: " << y << endl;

        z = x ^ y;
        cout << "z: " << z << endl;
        z = 31;
        cout << "z: " << z << endl;
        z = 'a';
        cout << "z: " << z << endl;
    }
}

#endif  // ALGORITHM_BIT_BASED_ON_VECTOR_TEST_H
