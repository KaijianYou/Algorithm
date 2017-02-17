#ifndef ALGORITHM_QUEUE_TEST_H
#define ALGORITHM_QUEUE_TEST_H

#include <iostream>

#include "../../algorithm/queue/queue_based_on_singly_linked_list.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testQueue()
    {
        Queue<int> pq;
        cout << "Initial pq size: " << pq.size() << endl;
        cout << endl;

        pq.push(3);
        pq.push(7);
        cout << "pq size: " << pq.size() << endl;
        cout << endl;

        pq.push(5);
        cout << "pq front: " << pq.front() << endl;
        cout << endl;

        while (!pq.empty()) {
            cout << "pq pop: " << pq.front() << endl;
            pq.pop();
        }
        cout << endl;

        cout << "pq size: " << pq.size() << endl;
    }
}

#endif  // ALGORITHM_QUEUE_TEST_H