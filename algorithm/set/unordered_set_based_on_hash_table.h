#ifndef ALGORITHM_UNORDERED_SET_BASED_ON_HASH_TABLE_H
#define ALGORITHM_UNORDERED_SET_BASED_ON_HASH_TABLE_H

#include "../hash/hash_table.h"

namespace myalgorithm {
    // 基于哈希表的无序集合的简单实现
    template <typename T, typename HashFunc>
    class UnorderedSet {
    public:
        typedef typename HashTable<T, HashFunc>::Iterator Iterator;
        typedef typename HashTable<T, HashFunc>::ConstIterator ConstIterator;

        UnorderedSet(int tableSize = 1237, const HashFunc &hf = HashFunc());
        UnorderedSet(T *first, T *last, int tableSize = 1237, const HashFunc &hf = HashFunc());

        bool empty() const;
        int size() const;

        Iterator find(const T &item);
        ConstIterator find(const T &item) const;

        pair<Iterator, bool> insert(const T &item);
        void erase(Iterator pos);
        int erase(const T &item);
        void erase(Iterator first, Iterator last);

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

    private:
        HashTable<T, HashFunc> hashTable;
    };

    template <typename T, typename HashFunc>
    UnorderedSet<T, HashFunc>::UnorderedSet(int tableSize, const HashFunc &hf) : hashTable(tableSize, hf)
    {}

    template <typename T, typename HashFunc>
    UnorderedSet<T, HashFunc>::UnorderedSet(T *first, T *last, int tableSize, const HashFunc &hf) :
            hashTable(first, last, tableSize, hf)
    {}

    template <typename T, typename HashFunc>
    bool UnorderedSet<T, HashFunc>::empty() const
    {
        return size() == 0;
    }

    template <typename T, typename HashFunc>
    int UnorderedSet<T, HashFunc>::size() const
    {
        return hashTable.size();
    }

    template <typename T, typename HashFunc>
    typename UnorderedSet<T, HashFunc>::Iterator UnorderedSet<T, HashFunc>::find(const T &item)
    {
        return hashTable.find(item);
    }

    template <typename T, typename HashFunc>
    typename UnorderedSet<T, HashFunc>::ConstIterator UnorderedSet<T, HashFunc>::find(const T &item) const
    {
        return hashTable.find(item);
    }

    template <typename T, typename HashFunc>
    pair<typename UnorderedSet<T, HashFunc>::Iterator, bool> UnorderedSet<T, HashFunc>::insert(const T &item)
    {
        return hashTable.insert(item);
    }

    template <typename T, typename HashFunc>
    void UnorderedSet<T, HashFunc>::erase(Iterator pos)
    {
        if (empty()) {
            throw underflow_error("UnorderedSet.erase(): set is empty");
        }

        hashTable.erase(pos);
    }

    template <typename T, typename HashFunc>
    void UnorderedSet<T, HashFunc>::erase(Iterator first, Iterator last)
    {
        if (empty()) {
            throw underflow_error("UnorderedSet.erase(): set is empty");
        }

        hashTable.erase(first, last);
    }

    template <typename T, typename HashFunc>
    int UnorderedSet<T, HashFunc>::erase(const T &item)
    {
        hashTable.erase(item);
    }

    template <typename T, typename HashFunc>
    typename UnorderedSet<T, HashFunc>::Iterator UnorderedSet<T, HashFunc>::begin()
    {
        return hashTable.begin();
    }

    template <typename T, typename HashFunc>
    typename UnorderedSet<T, HashFunc>::Iterator UnorderedSet<T, HashFunc>::end()
    {
        return hashTable.end();
    }

    template <typename T, typename HashFunc>
    typename UnorderedSet<T, HashFunc>::ConstIterator UnorderedSet<T, HashFunc>::begin() const
    {
        return hashTable.begin();
    }

    template <typename T, typename HashFunc>
    typename UnorderedSet<T, HashFunc>::ConstIterator UnorderedSet<T, HashFunc>::end() const
    {
        return hashTable.end();
    }
}

#endif  // ALGORITHM_UNORDERED_SET_BASED_ON_HASH_TABLE_H