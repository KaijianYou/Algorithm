#ifndef ALGORITHM_HASH_TABLE_TEST_H
#define ALGORITHM_HASH_TABLE_TEST_H

#include <iostream>

#include "../../algorithm/hash/hash_table.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cin;
    using std::cout;
    using std::endl;

    void testHashTable()
    {
        const int testSize = 12;
        int intArr[testSize] = { 0 };
        fillArrayWithRandomInt(intArr, testSize, 0, testSize * 2);

        cout << "Array elements:" << endl;
        printArray(intArr, testSize);
        cout << endl;

        HashTable<int, HashInt> ht(7);
        for (int i = 0; i < testSize; ++i) {
            pair<HashTable<int, HashInt>::Iterator, bool> result = ht.insert(intArr[i]);
            if (!result.second) {
                cout << "Duplicate value: " << intArr[i] << endl;
            }
        }
        cout << endl;

        cout << "Hash table size: " << ht.size() << endl;
        cout << "Hash table elements:" << endl;
        printContainer(ht.begin(), ht.end());
        cout << endl;

        cout << "Enter the number you want to delete: ";
        int key;
        cin >> key;

        auto iter = ht.find(key);
        if (iter == ht.end()) {
            cout << "Target " << key << " can not found" << endl;
        } else {
            ht.erase(iter);
        }
        cout << endl;

        cout << "Hash table size: " << ht.size() << endl;
        cout << "Hash table elements:" << endl;
        printContainer(ht.begin(), ht.end());
        cout << endl;
    }
}

#endif  // ALGORITHM_HASH_TABLE_TEST_H
