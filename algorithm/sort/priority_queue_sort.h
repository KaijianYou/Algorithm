#ifndef ALGORITHM_PRIORITY_QUEUE_SORT_H
#define ALGORITHM_PRIORITY_QUEUE_SORT_H

#include <vector>
#include <queue>

namespace myalgorithm {
    using std::vector;
    using std::priority_queue;

    // 使用优先级队列排序
    template <typename T>
    void priorQueueSort(vector<T> &v)
    {
        // 此处为升序排序，若要降序排序，下面一句可以改为：
        // priority_queue<T, vector<T>, greater<typename vector<T>::value_type>> pq;
        priority_queue<T> pq;
        // 时间复杂度：O(n * log(n))
        for (int i = 0; i < v.size(); ++i) {
            pq.push(v[i]);
        }

        // 时间复杂度：O(n * log(n))
        for (int i = v.size() - 1; i >= 0; --i) {
            v[i] = pq.top();
            pq.pop();
        }
    }
}

#endif  // ALGORITHM_PRIORITY_QUEUE_SORT_H