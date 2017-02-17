#ifndef ALGORITHM_BINARY_SEARCH_TREE_TEST_H
#define ALGORITHM_BINARY_SEARCH_TREE_TEST_H

#include <iostream>
#include <string>

#include "../../algorithm/tree/binary_search_tree.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::string;

    void testBinarySearchTree()
    {
        BinarySearchTree<char> bstree;
        string str = "pattern";

        for (int i = 0; i < str.length(); ++i) {
            pair<BinarySearchTree<char>::Iterator, bool> result = bstree.insert(str[i]);
            if (!result.second) {
                cout << str[i] << " is a duplicate letter" << endl;
            }
        }
        cout << endl;

        cout << "Initial tree: " << endl;
        bstree.displayTree(1);
        cout << endl;

        bstree.erase('a');
        cout << "Tree after deleting 'a': " << endl;
        bstree.displayTree(1);
        cout << endl;

        auto iter = bstree.find('t');
        if (iter != bstree.end()) {
            bstree.erase(iter);
        }
        cout << "Tree after deleting 'p': " << endl;
        bstree.displayTree(1);
    }
}

#endif  // ALGORITHM_BINARY_SEARCH_TREE_TEST_H