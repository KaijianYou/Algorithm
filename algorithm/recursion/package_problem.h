#ifndef ALGORITHM_PACKAGE_PROBLEM_H
#define ALGORITHM_PACKAGE_PROBLEM_H

#include <iostream>
#include <iomanip>
#include <vector>

#include "../../util/matrix.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::vector;
    using std::setw;
    
    // 物品
    struct Item {
        int size;   // 大小
        int value;  // 权重/价值

        Item(int size = 0, int value = 0) :
            size(size), value(value) {}
    };

    // 背包
    class Knapsack {
    public:
        Knapsack(vector<Item> &itemVec, int capacity);

        void displayKnapsack();

        void displayMaxValueMatrix();

    private:
        int capacity;  // 容量
        int numItems;
        vector<Item> itemVec;
        Matrix<int> maxValueMatrix;

        void buildMaxValueMatrix();
    };

    void Knapsack::buildMaxValueMatrix()
    {
        for (int i = 1; i <= numItems; ++i) {
            for (int cap = 1; cap <= capacity; ++cap) {
                maxValueMatrix[i][cap] = maxValueMatrix[i - 1][cap];

                if (cap - itemVec[i].size >= 0) {
                    int testMax = maxValueMatrix[i - 1][cap - itemVec[i].size] +
                                  itemVec[i].value;

                    if (testMax > maxValueMatrix[i - 1][cap]) {
                        maxValueMatrix[i][cap] = testMax;
                    }
                }
            }
        }
    }

    Knapsack::Knapsack(vector<Item> &itemVec, int capacity) :
        capacity(capacity), numItems(itemVec.size())
    {
        this->itemVec.resize(numItems + 1);
        maxValueMatrix.resize(numItems + 1, capacity + 1);

        for (int i = 1; i <= numItems; ++i) {
            this->itemVec[i] = itemVec[i - 1];
        }

        buildMaxValueMatrix();
    }

    void Knapsack::displayKnapsack()
    {
        cout << "Capacity: " << capacity
             << "  Value: " << maxValueMatrix[numItems][capacity]
             << endl;
        cout << "Contents: " << endl;

        int cap = capacity;
        for (int i = numItems; i > 0; --i) {
            if (maxValueMatrix[i][cap] != maxValueMatrix[i - 1][cap]) {
                cout << "   item" << i << "(" << itemVec[i].size << ","
                     << itemVec[i].value << ")" << endl;
                cap -= itemVec[i].size;
            }
        }
        cout << "   Unused capacity: " << cap << endl;
    }

    void Knapsack::displayMaxValueMatrix()
    {
        cout << "Value matrix: " << endl;
        cout << "    capacity";
        for (int i = 1; i <= capacity; ++i) {
            cout << setw(4) << i;
        }
        cout << endl << "Item No." << endl;

        for (int i = 1; i <= numItems; ++i) {
            cout << "   " << i << "        ";
            for (int cap = 1; cap <= capacity; ++cap) {
                cout << setw(4) << maxValueMatrix[i][cap];
            }
            cout << endl;
        }
    }
}
    
#endif  // ALGORITHM_PACKAGE_PROBLEM_H