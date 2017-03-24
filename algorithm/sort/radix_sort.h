#ifndef ALGORITHM_RADIX_SORT_H
#define ALGORITHM_RADIX_SORT_H

#include <vector>
#include <queue>

namespace myalgorithm {
    using std::vector;
    using std::queue;

    // 根据待排序数与 power(10^i) 关联的数位把待排序数放到相应的 digitQueue 中
    void distribute(const vector<int> &v, queue<int> digitQueue[], int power)
    {
        for (int i = 0; i < v.size(); ++i) {
            digitQueue[(v[i] / power) % 10].push(v[i]);
        }
    }

    // 依次将队列 0 ~ 9 中的待排序数复制回向量
    void collect(queue<int> digitQueue[], vector<int> &v)
    {
        int index = 0;
        // 此处为升序排序，若要降序排序，下面一句可以改为：
        // for (int digit = 9; digit >= 0; --digit)
        for (int digit = 0; digit < 10; ++digit) {
            while(!digitQueue[digit].empty()) {
                v[index] = digitQueue[digit].front();
                digitQueue[digit].pop();
                ++index;
            }
        }
    }

    // d 是向量中所有整数的最大位数
    // 重复调用此函数 d 次，每次按一个数位排序，即第 i 次把待排序数
    // 根据它与 power=10^i 关联的数位放到相应的 digitQueue[i] 中
    void radixSort(vector<int> &v, int d)
    {
        queue<int> digitQueue[10];
        int power = 1;
        for (int i = 0; i < d; ++i) {
            distribute(v, digitQueue, power);
            collect(digitQueue, v);
            power *= 10;
        }
    }
}

#endif  // ALGORITHM_RADIX_SORT_H