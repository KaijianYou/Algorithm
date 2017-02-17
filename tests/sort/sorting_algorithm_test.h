#ifndef ALGORITHM_SORTSING_ALGORITHM_TEST_H
#define ALGORITHM_SORTSING_ALGORITHM_TEST_H

#include <iostream>
#include <vector>
#include <functional>

#include "../../algorithm/sort/bubble_sort.h"
#include "../../algorithm/sort/exchange_sort.h"
#include "../../algorithm/sort/heap_sort.h"
#include "../../algorithm/sort/insertion_sort.h"
#include "../../algorithm/sort/merge_sort.h"
#include "../../algorithm/sort/priority_queue_sort.h"
#include "../../algorithm/sort/quick_sort.h"
#include "../../algorithm/sort/radix_sort.h"
#include "../../algorithm/sort/selection_sort.h"
#include "../../algorithm/sort/shell_sort.h"
#include "../../util/random_number.h"
#include "../../util/timer.h"

namespace myalgorithm {
    using std::vector;
    using std::less;
    using std::greater;
    using std::cout;
    using std::endl;

    enum SortType {
        SELECTION, INSERTION, BUBBLE, EXCHANGE, SHELL,
        RADIX, PRIORQUEUE, HEAP, MERGE, QUICK
    };

    enum TestType { RANDOM, ASCENDING, DESCENDING };

    void timeSort(SortType sortType, TestType testType, int size)
    {
        vector<int> vec(size);
        RandomNumber rnd;

        if (testType == RANDOM) {
            for (int i = 0; i < size; ++i) {
                vec[i] = rnd.randomInt(1, size + 1);
            }
        } else if (testType == ASCENDING) {
            for (int i = 0; i < size; ++i) {
                vec[i] = i + 1;
            }
        } else {
            for (int i = 0; i < size; ++i) {
                vec[i] = size - i;
            }
        }

        Timer timer;
        switch (sortType) {
        case SELECTION: {
            timer.start();
            selectionSort(vec, less<int>());
            timer.stop();
            cout << "Seleciton sort:    " << timer.time() << " ms" << endl;
            break;
        }
        case INSERTION: {
            timer.start();
            insertionSort(vec, less<int>());
            timer.stop();
            cout << "Insertion sort:    " << timer.time() << " ms" << endl;
            break;
        }
        case BUBBLE: {
            timer.start();
            bubbleSort(vec, less<int>());
            timer.stop();
            cout << "Bubble sort:       " << timer.time() << " ms" << endl;
            break;
        }
        case EXCHANGE: {
            timer.start();
            exchangeSort(vec, less<int>());
            timer.stop();
            cout << "Exchange sort:     " << timer.time() << " ms" << endl;
            break;
        }
        case SHELL: {
            timer.start();
            shellSort(vec, less<int>());
            timer.stop();
            cout << "Shell sort:        " << timer.time() << " ms" << endl;
            break;
        }
        case RADIX: {
            int radix = 1;
            while ((size = size / 10) != 0) {
                ++radix;
            }
            timer.start();
            radixSort(vec, radix);
            timer.stop();
            cout << "Radix sort:        " << timer.time() << " ms" << endl;
            break;
        }
        case PRIORQUEUE: {
            timer.start();
            priorQueueSort(vec);
            timer.stop();
            cout << "Prior queue sort:  " << timer.time() << " ms" << endl;
            break;
        }
        case HEAP: {
            timer.start();
            heapSort(vec, less<int>());
            timer.stop();
            cout << "Heap sort:         " << timer.time() << " ms" << endl;
            break;
        }
        case MERGE: {
            timer.start();
            mergeSort(vec, 0, vec.size(), less<int>());
            timer.stop();
            cout << "Merge sort:        " << timer.time() << " ms" << endl;
            break;
        }
        case QUICK: {
            timer.start();
            quickSort(vec, 0, vec.size(), less<int>());
            timer.stop();
            cout << "Quick sort:        " << timer.time() << " ms" << endl;
            break;
        }
        default: break;
        }
    }

    void testSortingAlgorithm()
    {
        const int testSize = 10000;

        cout << "Sorting random numbers:" << endl;

        timeSort(SELECTION, DESCENDING, testSize);
        timeSort(BUBBLE, DESCENDING, testSize);
        timeSort(INSERTION, DESCENDING, testSize);
        timeSort(EXCHANGE, DESCENDING, testSize);
        timeSort(SHELL, DESCENDING, testSize);
        timeSort(RADIX, DESCENDING, testSize);
        timeSort(PRIORQUEUE, DESCENDING, testSize);
        timeSort(HEAP, DESCENDING, testSize);
        timeSort(MERGE, DESCENDING, testSize);
        timeSort(QUICK, DESCENDING, testSize);

        cout << endl;

        cout << "Sorting ascending numbers:" << endl;

        timeSort(SELECTION, ASCENDING, testSize);
        timeSort(BUBBLE, ASCENDING, testSize);
        timeSort(INSERTION, ASCENDING, testSize);
        timeSort(EXCHANGE, ASCENDING, testSize);
        timeSort(SHELL, ASCENDING, testSize);
        timeSort(RADIX, ASCENDING, testSize);
        timeSort(PRIORQUEUE, ASCENDING, testSize);
        timeSort(HEAP, ASCENDING, testSize);
        timeSort(MERGE, ASCENDING, testSize);
        timeSort(QUICK, ASCENDING, testSize);

        cout << endl;

        cout << "Sorting descending numbers:" << endl;

        timeSort(SELECTION, RANDOM, testSize);
        timeSort(BUBBLE, RANDOM, testSize);
        timeSort(INSERTION, RANDOM, testSize);
        timeSort(EXCHANGE, RANDOM, testSize);
        timeSort(SHELL, RANDOM, testSize);
        timeSort(RADIX, RANDOM, testSize);
        timeSort(PRIORQUEUE, RANDOM, testSize);
        timeSort(HEAP, RANDOM, testSize);
        timeSort(MERGE, RANDOM, testSize);
        timeSort(QUICK, RANDOM, testSize);

        cout << endl;
    }
}

#endif  // ALGORITHM_SORTSING_ALGORITHM_TEST_H