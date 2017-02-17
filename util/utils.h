#ifndef ALGORITHM_UTILS__H
#define ALGORITHM_UTILS__H

#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <list>

#include "random_number.h"
#include "../algorithm/search/sequential_search.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;
    using std::map;
    using std::list;

    template <typename T>
    void fillVectorWithRandomInt(vector<T> &vec, const int lowerBound, const int upperBound)
    {
        static RandomNumber rnd;
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i] = rnd.randomInt(lowerBound, upperBound);
        }
    }

    template <typename T>
    void fillArrayWithRandomInt(T arr[], size_t size, const int lowerBound, const int upperBound)
    {
        static RandomNumber rnd;
        for (size_t i = 0; i < size; ++i) {
            arr[i] = rnd.randomInt(lowerBound, upperBound);
        }
    }

    template <typename T>
    void printArray(const T arr[], int size, const string &separator = "  ")
    {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << separator;
        }
        cout << endl;
    }

    template <typename Iterator>
    void printContainer(Iterator first, Iterator last, const string &separator = "  ")
    {
        for (Iterator iter = first; iter != last; ++iter) {
            cout << *iter << separator;
        }
        cout << endl;
    }

    template <typename Key, typename Value>
    void printMap(const map<Key, Value> &m, const string &separator = "  ")
    {
        for (typename map<Key, Value>::const_iterator iter = m.begin();
            iter != m.end(); ++iter) {
            cout << (*iter).first << "  " << (*iter).second << separator;
        }
        cout << endl;
    }

    // 删除数组中的冗余元素
    // 把数组中冗余的元素通过交换放到数组尾部，返回数组中不同元素的个数
    template <typename T>
    int removeArrayDupElements(T arr[], int size)
    {
        int currSize = size;
        for (int i = 0; i < currSize - 1; ++i) {
            for (int j = i + 1; j < currSize; ++j) {
                if (arr[i] == arr[j]) {
                    while ((arr[j] == arr[currSize - 1]) &&
                           (j != currSize - 1)) {
                        --currSize;
                    }
                    T temp = arr[j];
                    arr[j] = arr[currSize - 1];
                    arr[currSize - 1] = temp;
                    --currSize;
                }
            }
        }

        return currSize;
    }

    // 删除向量中的冗余元素
    // 把向量中冗余的元素通过交换放到向量尾部，最后通过调整向量大小来删除冗余元素
    template <typename T>
    void removeVectorDupElements1(vector<T> &vec)
    {
        int currSize = static_cast<int>(vec.size());
        for (int i = 0; i < currSize - 1; ++i) {
            for (int j = i + 1; j < currSize; ++j) {
                if (vec[i] == vec[j]) {
                    while ((vec[j] == vec[currSize - 1]) &&
                           (j != currSize - 1)) {
                        --currSize;
                    }
                    int temp = vec[j];
                    vec[j] = vec[currSize - 1];
                    vec[currSize - 1] = temp;
                    --currSize;
                }
            }
        }

        vec.resize(currSize);
    }

    // 删除向量中的冗余元素（效率非常低）
    template <typename T>
    void removeVectorDupElements2(vector<T> &vec)
    {
        // 从索引 1 处开始遍历向量，将当前索引处的元素与它之前的所有元素一一比较，如果发现
        // 相同元素，则从当前索引开始，后面的所有元素向前移动一个位置，然后将向量大小减一
        for (int i = 1; i < vec.size(); ++i) {
            int j = i;
            while (j > 0 && vec[i] != vec[j - 1]) {
                --j;
            }
            if (j != 0) {
                for (int k = i; k < vec.size() - 1; ++k) {
                    vec[k] = vec[k + 1];
                }
                vec.resize(vec.size() - 1);
                --i;
            }
        }
    }

    // 删除向量中的冗余元素
    template <typename T>
    void removeVectorDupElements3(vector<T> &vec)
    {
        vector<T> tempVec;
        tempVec.push_back(vec[0]);

        // 从索引 1 处开始遍历原向量，将当前索引处的元素与它之前的所有元素一一比较，如果没有发现
        // 相同元素，则将当前元素添加到临时向量中
        for (int i = 1; i < vec.size(); ++i) {
            int j = i;
            while (j > 0 && vec[i] != vec[j - 1]) {
                --j;
            }
            if (j == 0) {
                tempVec.push_back(vec[i]);
            }
        }

        for (int i = 0; i < tempVec.size(); ++i) {
            vec[i] = tempVec[i];
        }
        vec.resize(tempVec.size());
    }

    // 删除向量中的冗余元素
    template <typename T>
    void removeVectorDupElements4(vector<T> &vec)
    {
        vector<T> tempVec;
        for (int i = 0; i < vec.size(); ++i) {
            int index;
            // 根据索引遍历向量元素，用顺序查找当前元素第一次出现的索引，若该索引等于当前元素的索引，
            // 即表明当前元素还没有重复出现过，于是把它添加到临时向量中
            if ((index = sequentialSearch(vec, 0, i, vec[i])) == i) {
                tempVec.push_back(vec[i]);
            }
        }

        for (int i = 0; i < tempVec.size(); ++i) {
            vec[i] = tempVec[i];
        }
        vec.resize(tempVec.size());
    }

    // 删除链表中的冗余元素
    template <typename T>
    void removeListDupElements(list<T> &lst)
    {
        for (typename list<T>::iterator currIter = lst.begin();
             currIter != lst.end(); ++currIter) {
            typename list<T>::iterator scanIter = currIter;
            ++scanIter;
            while (scanIter != lst.end()) {
                if (*scanIter == *currIter) {
                    scanIter = lst.erase(scanIter);
                } else {
                    ++scanIter;
                }
            }
        }
    }

    // 删除有序链表中的冗余元素
    template <typename T>
    void removeOrderedListDupElements(list<T> &lst)
    {
        for (typename list<T>::iterator currIter = lst.begin();
             currIter != lst.end(); ++currIter) {
            typename list<T>::iterator scanIter = currIter;
            ++scanIter;
            while (scanIter != lst.end() && *scanIter == *currIter) {
                scanIter = lst.erase(scanIter);
            }
        }
    }

    // 判断回文
    template <typename T>
    bool isPalindrome(const list<T> &lst)
    {
        list<T> copyList = lst;
        while (copyList.size() > 1 ) {
            if (copyList.front() != copyList.back()) {
                return false;
            }
            copyList.pop_front();
            copyList.pop_back();
        }
        return true;
    }
}

#endif  // ALGORITHM_UTILS__H