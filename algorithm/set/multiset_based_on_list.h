#ifndef ALGORITHM_MULTISET_BASED_ON_LIST_H
#define ALGORITHM_MULTISET_BASED_ON_LIST_H

#include <list>
#include <utility>

namespace myalgorithm {
    using std::list;
    using std::pair;

    // 基于 STL list 的多重集合的简单实现
    template <typename T>
    class MultiSet {
    public:
        typedef typename list<T>::iterator Iterator;
        typedef typename list<T>::const_iterator ConstIterator;

        MultiSet();
        MultiSet(T *first, T *last);

        bool empty() const;
        int size() const;

        int count(const T &item) const;
        Iterator find(const T &item);
        ConstIterator find(const T &item) const;

        pair<Iterator, Iterator> equal_range(const T &item);
        pair<ConstIterator, ConstIterator> equal_range(const T &item) const;

        Iterator insert(const T &item);
        int erase(const T &item);
        void erase(Iterator pos);
        void erase(Iterator first, Iterator last);

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

    private:
        list<T> multisetList;

        int distance(Iterator first, Iterator last);
        int distance(ConstIterator first, ConstIterator last) const;
    };

    template <typename T>
    MultiSet<T>::MultiSet()
    {}

    template <typename T>
    MultiSet<T>::MultiSet(T *first, T *last)
    {
        for ( ; first != last; ++first) {
            insert(*first);
        }
    }

    template <typename T>
    int MultiSet<T>::distance(Iterator first, Iterator last)
    {
        int length = 0;
        for (Iterator iter = first; iter != last; ++iter) {
            ++length;
        }

        return count;
    }

    template <typename T>
    int MultiSet<T>::distance(ConstIterator first, ConstIterator last) const
    {
        int length = 0;
        for (ConstIterator iter = first; iter != last; ++iter) {
            ++length;
        }

        return length;
    }

    template <typename T>
    bool MultiSet<T>::empty() const
    {
        return size() == 0;
    }

    template <typename T>
    int MultiSet<T>::size() const
    {
        return static_cast<int>(multisetList.size());
    }

    template <typename T>
    pair<typename MultiSet<T>::Iterator, typename MultiSet<T>::Iterator>
    MultiSet<T>::equal_range(const T &item)
    {
        Iterator lowerBound = end();
        Iterator upperBound = end();
        for (Iterator iter = begin(); iter != end(); ++iter) {
            if (*iter == item && lowerBound == end()) {
                lowerBound = iter;
            }
            if (*iter == item) {
                upperBound = iter;
            }
        }

        if (upperBound != end()) {
            ++upperBound;
        }

        return pair<Iterator, Iterator>(lowerBound, upperBound);
    }

    template <typename T>
    pair<typename MultiSet<T>::ConstIterator, typename MultiSet<T>::ConstIterator>
    MultiSet<T>::equal_range(const T &item) const
    {
        ConstIterator lowerBound = end();
        ConstIterator upperBound = end();
        for (ConstIterator iter = begin(); iter != end(); ++iter) {
            if (*iter == item && lowerBound == end()) {
                lowerBound = iter;
            }
            if (*iter == item) {
                upperBound = iter;
            }
        }

        if (upperBound != end()) {
            ++upperBound;
        }

        return pair<ConstIterator, ConstIterator>(lowerBound, upperBound);
    }

    template <typename T>
    int MultiSet<T>::count(const T &item) const
    {
        pair<ConstIterator, ConstIterator> range = equal_range(item);
        return distance(range.first, range.second);
    }

    template <typename T>
    typename MultiSet<T>::Iterator MultiSet<T>::find(const T &item)
    {
        Iterator iter = begin();
        for ( ; iter != end(); ++iter) {
            if ((*iter) == item) {
                break;
            }
        }

        return iter;
    }

    template <typename T>
    typename MultiSet<T>::ConstIterator MultiSet<T>::find(const T &item) const
    {
        ConstIterator iter = begin();
        for ( ; iter != end(); ++iter) {
            if ((*iter) == item) {
                break;
            }
        }

        return iter;
    }

    template <typename T>
    typename MultiSet<T>::Iterator MultiSet<T>::insert(const T &item)
    {
        pair<Iterator, Iterator> range = equal_range(item);
        return multisetList.insert(range.second, item);
    }

    template <typename T>
    int MultiSet<T>::erase(const T &item)
    {
        if (empty()) {
            throw underflow_error("MultiSet.erase(): set is empty");
        }

        int size = count(item);
        for (Iterator iter = begin(); iter != end(); ) {
            if ((*iter) == item) {
                multisetList.erase(iter++);
            } else {
                ++iter;
            }
        }

        return size;
    }

    template <typename T>
    void MultiSet<T>::erase(Iterator pos)
    {
        if (empty()) {
            throw underflow_error("MultiSet.erase(): set is empty");
        }

        multisetList.erase(pos);
    }

    template <typename T>
    void MultiSet<T>::erase(Iterator first, Iterator last)
    {
        if (empty()) {
            throw underflow_error("MultiSet.erase(): set is empty");
        }

        for (Iterator iter = first; iter != last; ) {
            multisetList.erase(iter++);
        }
    }

    template <typename T>
    typename MultiSet<T>::Iterator MultiSet<T>::begin()
    {
        return multisetList.begin();
    }

    template <typename T>
    typename MultiSet<T>::Iterator MultiSet<T>::end()
    {
        return multisetList.end();
    }

    template <typename T>
    typename MultiSet<T>::ConstIterator MultiSet<T>::begin() const
    {
        return multisetList.begin();
    }

    template <typename T>
    typename MultiSet<T>::ConstIterator MultiSet<T>::end() const
    {
        return multisetList.end();
    }
}

#endif  // ALGORITHM_MULTISET_BASED_ON_LIST_H