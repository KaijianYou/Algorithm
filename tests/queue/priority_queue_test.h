#ifndef ALGORITHM_PRIORITY_QUEUE_TEST_H
#define ALGORITHM_PRIORITY_QUEUE_TEST_H

#include <iostream>

//#include "../../algorithm/queue/priority_queue_based_on_heap.h"
#include "../../algorithm/queue/priority_queue_based_on_vector.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testPriorityQueue()
    {
        PriorityQueue<int> pq;
        cout << "Initial pq size: " << pq.size() << endl;
        cout << endl;

        pq.push(3);
        pq.push(10);
        cout << "pq size: " << pq.size() << endl;
        cout << endl;

        pq.push(15);
        cout << "pq top: " << pq.top() << endl;
        cout << endl;

        while (!pq.empty()) {
            cout << "pq pop: " << pq.top() << endl;
            pq.pop();
        }
        cout << endl;

        cout << "pq size: " << pq.size() << endl;
    }
}

#endif  // ALGORITHM_PRIORITY_QUEUE_TEST_H