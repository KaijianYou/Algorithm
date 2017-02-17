#ifndef ALGORITHM_TIMER_H
#define ALGORITHM_TIMER_H

#include <ctime>

namespace myalgorithm {
    // 计时类，用于程序运行计时
    class Timer {
    public:
        Timer() : startTime(0), endTime(0) {}

        void start()
        {
            startTime = clock();
        }

        void stop()
        {
            endTime = clock();
        }

        // 返回 ms
        double time() const
        {
            return static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000;
        }

    private:
        clock_t startTime;
        clock_t endTime;
    };
}

#endif  // ALGORITHM_TIMER_H