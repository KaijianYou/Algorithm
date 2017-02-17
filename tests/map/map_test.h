#ifndef ALGORITHM_MAP_TEST_H
#define ALGORITHM_MAP_TEST_H

#include <iostream>
#include <string>

#include "../../algorithm/map/map_based_on_binary_search_tree.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::string;

    void testMapBasedOnBinarySearchTree()
    {
        typedef Map<string, int>::value_type entry;
        entry arr[] = {
            entry("Bob", 1230), entry("Baldwin", 2285),
            entry("George", 1782), entry("Mary", 4323)
        };
        int arrSize = sizeof(arr) / sizeof(*arr);

        Map<string, int> m(arr, arr + arrSize);

        cout << "m elements:" << endl;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            cout << "\tm[\"" << (*iter).first << "\"] = " << (*iter).second << endl;
        }
        cout << endl;

        auto ret = m.find("Bob");
        if (ret != m.end()) {
            cout << "m[\"Bob\"] = " << (*ret).second << endl;
        }
        cout << endl;

        ret = m.begin();
        m.erase(ret);
        m.insert(entry("Louis", 6649));

        cout << "m elements:" << endl;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            cout << "\tm[\"" << (*iter).first << "\"] = " << (*iter).second << endl;
        }
        cout << endl;

        m.erase(m.begin(), m.end());
        if (m.empty()) {
            cout << "now m is empty" << endl;
        }
    }
}

#endif  // ALGORITHM_MAP_TEST_H
