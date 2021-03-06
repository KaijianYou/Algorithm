#ifndef ALGORITHM_VECTOR_TEST_H
#define ALGORITHM_VECTOR_TEST_H

#include <iostream>
#include <string>

#include "../../algorithm/vector/vector_based_on_dynamic_array.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::string;

    void testVectorBasedOnDynamicArray()
    {
        Vector<int> intVec(10);
        cout << "intVec size: " << intVec.size() << endl;

        for (int i = 0; i < 5; ++i) {
            intVec.push_back(i);
            cout << "intVec size: " << intVec.size()
                 << "    capacity: " << intVec.capacity() << endl;
        }
        cout << endl;

        cout << "intVec elements:\n\t";
        for (int i = 0; i < intVec.size(); ++i) {
            cout << intVec[i] << "  ";
        }
        cout << endl << endl;

        Vector<string> strVec(1);
        cout << "strVec size: " << strVec.size() << endl;

        strVec[0] = "vector";
        strVec.push_back("based");
        cout << "strVec size: " << strVec.size()
             << "    capacity: " << strVec.capacity() << endl;

        strVec.push_back("on");
        cout << "strVec size: " << strVec.size()
             << "    capacity: " << strVec.capacity() << endl;

        strVec.push_back("dynamic array");
        cout << "strVec size: " << strVec.size()
             << "    capacity: " << strVec.capacity() << endl;

        cout << endl;

        cout << "strVec elements:\n\t";
        printContainer(strVec.begin(), strVec.end());
        cout << endl << endl;

        Vector<int> vA(5), vB;
        for (int i = 1; i < 8; ++i) {
            vB.push_back(i);
            cout << "vB push: " << i << endl;
        }
        cout << endl;

        while (!vB.empty()) {
            cout << "vB pop: " << vB.back() << endl;
            vB.pop_back();
        }
        cout << "vB size: " << vB.size()
             << "    capacity: " << vB.capacity() << endl;

        cout << endl;

        Vector<int> v;
        for (int i = 0; i < 10; ++i) {
            v.push_back(i);
        }

        v.insert(0, 10);
        v.insert(11, 20);
        v.insert(5, 3);

        cout << "v elements:\n\t";
        printContainer(v.begin(), v.end());
        cout << endl << endl;

        v.erase(12);
        v.erase(0);
        v.erase(4);

        cout << "v elements:\n\t";
        printContainer(v.begin(), v.end());
        cout << endl;
    }
}

#endif  // ALGORITHM_VECTOR_TEST_H