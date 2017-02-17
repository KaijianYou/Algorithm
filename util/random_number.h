#ifndef ALGORITHM_RANDOM_NUMBER_H
#define ALGORITHM_RANDOM_NUMBER_H

#include <random>

namespace myalgorithm {
    // 随机数类，用于产生随机数
    class RandomNumber {
    public:
        RandomNumber(unsigned seed) : e(seed) {}
        RandomNumber() : e(static_cast<unsigned>(time(0))) {}

        void seed(unsigned seed) { e.seed(seed); }

        unsigned min() { return e.min(); }
        unsigned max() { return e.max(); }

        int randomInt(const int lowerBound, const int upperBound)
        {
            std::uniform_int_distribution<unsigned> u(lowerBound, upperBound);
            return u(e);
        }

        double randomDouble(const double lowerBound, const double upperBound)
        {
            std::uniform_real_distribution<double> u(lowerBound, upperBound);
            return u(e);
        }

    private:
        std::default_random_engine e;
    };
}

#endif  // ALGORITHM_RANDOM_NUMBER_H