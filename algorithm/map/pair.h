#ifndef ALGORITHM_PAIR_H
#define ALGORITHM_PAIR_H

namespace myalgorithm {
    template<typename T1, typename T2>
    struct Pair {
        T1 first;
        T2 second;

        Pair() : first(T1()), second(T2())
        {}

        Pair(const T1 &first, const T2 &second) : first(first), second(second)
        {}

        friend bool operator<(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
        {
            return lhs.first < rhs.first;
        }

        friend bool operator==(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
        {
            return lhs.first == rhs.first;
        }
    };
}

#endif  // ALGORITHM_PAIR_H