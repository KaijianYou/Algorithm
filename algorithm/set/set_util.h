#ifndef ALGORITHM_SET_UTIL_H
#define ALGORITHM_SET_UTIL_H

#include <set>

namespace myalgorithm {
    using std::set;

    // 判断 lhs 是否是 rhs 的子集，是则返回 true，否则返回 false
    template <typename T>
    bool subset(const set<T> &lhs, const set<T> &rhs)
    {
        bool foundInRhs = false;
        for (auto lhsIter = lhs.begin(); lhsIter != lhs.end(); ++lhsIter) {
            for (auto rhsIter = rhs.begin(); rhsIter != rhs.end(); ++rhsIter) {
                if (*lhsIter == *rhsIter) {
                    foundInRhs = true;
                }
            }

            if (foundInRhs) {
                foundInRhs = false;
            } else {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    bool subset2(const set<T> &lhs, const set<T> &rhs)
    {
        auto lhsIter = lhs.begin(), rhsIter = rhs.begin();
        while (lhsIter != lhs.end() && rhsIter != rhs.end()) {
            if (*lhsIter < *rhsIter) {
                return false;
            } else if (*lhsIter == *rhsIter) {
                lhsIter++;
                rhsIter++;
            } else {
                rhsIter++;
            }
        }

        return !(lhsIter != lhs.end() && rhsIter == rhs.end());
    }

    // 集合相等运算
    template <typename T>
    bool operator==(const set<T> &lhs, const set<T> &rhs)
    {
        auto lhsIter = lhs.cbegin(), rhsIter = rhs.cbegin();
        if (lhs.size() == rhs.size()) {
            while (lhsIter != lhs.cend() && *lhsIter++ == *rhsIter++) {
                ;
            }

            if (lhsIter != lhs.cend()) {
                return false;
            } else {
                return true;
            }
        }

        return false;
    }

    // 集合并集运算
    template <typename T>
    set<T> operator+(const set<T> &lhs, const set<T> &rhs)
    {
        set<T> unionSet;
        for (auto iter = lhs.cbegin(); iter != lhs.cend(); ++iter) {
            unionSet.insert(*iter);
        }

        for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter) {
            unionSet.insert(*iter);
        }

        return unionSet;
    }

    // 集合差集运算
    template <typename T>
    set<T> operator-(const set<T> &lhs, const set<T> &rhs)
    {
        set<T> differSet;
        auto lhsIter = lhs.cbegin(), rhsIter = rhs.cbegin();
        while (lhsIter != lhs.cend() && rhsIter != rhs.cend()) {
            if (*lhsIter < *rhsIter) {
                differSet.insert(*lhsIter++);
            } else if (*rhsIter < *lhsIter) {
                rhsIter++;
            } else {
                lhsIter++;
                rhsIter++;
            }
        }

        if (lhsIter != lhs.cend()) {
            while (lhsIter != lhs.cend()) {
                differSet.insert(*lhsIter++);
            }
        }

        return differSet;
    }

    // 集合交集运算
    template <typename T>
    set<T> operator*(const set<T> &lhs, const set<T> &rhs)
    {
        set<T> intersectionSet;
        auto lhsIter = lhs.cbegin(), rhsIter = rhs.cbegin();
        while (lhsIter != lhs.cend() && rhsIter != rhs.cend()) {
            if (*lhsIter < *rhsIter) {
                lhsIter++;
            } else if (*rhsIter < *lhsIter) {
                rhsIter++;
            } else {
                intersectionSet.insert(*lhsIter++);
                rhsIter++;
            }
        }

        return intersectionSet;
    }

    // 返回一个集合的幂集
    template <typename T>
    set<set<T>> getPowerSet(set<T> &s)
    {
        set<T> emptySet;  // 空集
        set<set<T>> powerSet;  // 幂集
        if (s.empty()) {
            powerSet.insert(emptySet);
        } else {
            set<set<T>> sPrime;  // 幂集，不包含集合 s 的第一个元素
            set<set<T>> sPrimePlus;  // 根据 sPrime 创建的子集的集合，包含 s 的第一个元素

            // 从 s 中删除第一个元素，并再次计算幂集 sPrime
            T temp = *(s.begin());
            s.erase(s.begin());
            sPrime = getPowerSet(s);

            set<T> tempSet;  // sPrime 中的集合
            for (auto sIter = sPrime.begin(); sIter != sPrime.end(); ++sIter) {
                tempSet = *sIter;
                tempSet.insert(temp);
                sPrimePlus.insert(tempSet);
            }

            // s 的幂集是 sPrime 和 sPrimePlus 的并集
            powerSet = sPrime + sPrimePlus;
        }

        return powerSet;
    }

    // 输出集合中的每一个子集
    template <typename T>
    void printPowerSet(set<set<T>> &powerSet)
    {
        int count = 0;
        for (auto setIter = powerSet.begin(); setIter != powerSet.end(); ++setIter) {
            set<T> s = *setIter;
            if (s.empty()) {
                cout << "{}" << "\t";
            } else {
                cout << "{";
                for (auto iter = s.begin(); iter != s.end(); ) {
                    cout << *iter;
                    if (++iter != s.end()) {
                        cout << ", ";
                    }
                }
                cout << "}" << "  ";
            }

            if (++count % 5 == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }
}

#endif  // ALGORITHM_SET_UTIL_H