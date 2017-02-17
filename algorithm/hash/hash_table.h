#ifndef ALGORITHM_HASH_TABLE_H
#define ALGORITHM_HASH_TABLE_H

#include <utility>
#include <vector>
#include <stdexcept>

namespace myalgorithm {
    using std::pair;
    using std::vector;
    using std::range_error;
    using std::underflow_error;

    // 整型的哈希函数对象
    struct HashInt {
        unsigned int operator()(int item) const
        {
            unsigned int hashValue = static_cast<unsigned int>(item);
            hashValue *= hashValue;
            hashValue /= 256;

            return hashValue % 65536;
        }
    };

    // HashTable 类
    // HashFunc 用来指定 HashTable 对象使用的哈希函数
    template<typename T, typename HashFunc>
    class HashTable {
    public:
        class Iterator;
        class ConstIterator;

        HashTable(int numBuckets, const HashFunc &hf = HashFunc());
        HashTable(T *first, T *last, int numBuckets, const HashFunc &hf = HashFunc());
        virtual ~HashTable();

        bool empty() const;
        int size() const;

        Iterator find(const T &item);
        ConstIterator find(const T &item) const;

        pair<Iterator, bool> insert(const T &item);
        int erase(const T &item);
        void erase(Iterator pos);
        void erase(Iterator first, Iterator last);

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

    private:
        int numBuckets;
        vector<list<T>> bucket;
        HashFunc hf;
        int hashTableSize;
    };

    template<typename T, typename HashFunc>
    HashTable<T, HashFunc>::HashTable(int numBuckets, const HashFunc &hf) :
        numBuckets(numBuckets), bucket(numBuckets), hf(hf), hashTableSize(0)
    {}

    template<typename T, typename HashFunc>
    HashTable<T, HashFunc>::HashTable(T *first, T *last, int numBuckets, const HashFunc &hf) :
            numBuckets(numBuckets), bucket(numBuckets), hf(hf), hashTableSize(0)
    {
        while (first != last) {
            insert(*first++);
        }
    }

    template <typename T, typename HashFunc>
    HashTable<T, HashFunc>::~HashTable()
    {}

    template<typename T, typename HashFunc>
    bool HashTable<T, HashFunc>::empty() const
    {
        return size() == 0;
    }

    template<typename T, typename HashFunc>
    int HashTable<T, HashFunc>::size() const
    {
        return hashTableSize;
    }

    template<typename T, typename HashFunc>
    class HashTable<T, HashFunc>::Iterator {
    public:
        friend class HashTable<T, HashFunc>;
        friend class HashTable<T, HashFunc>::ConstIterator;

        Iterator();

        T &operator*();

        bool operator==(const Iterator &rhs) const;
        bool operator!=(const Iterator &rhs) const;

        Iterator &operator++();
        Iterator operator++(int);

    private:
        HashTable<T, HashFunc> *hashTable;
        int currBucket;
        typename list<T>::iterator currLocation;

        Iterator(HashTable<T, HashFunc> *hashTable, int currBucket,
                 typename list<T>::iterator currLocation);

        void findNext();
    };

    template<typename T, typename HashFunc>
    HashTable<T, HashFunc>::Iterator::Iterator(HashTable<T, HashFunc> *hashTable,
                                               int currBucket,
                                               typename list<T>::iterator currLocation) :
            hashTable(hashTable), currBucket(currBucket), currLocation(currLocation)
    {}

    template<typename T, typename HashFunc>
    void HashTable<T, HashFunc>::Iterator::findNext()
    {
        for (int i = currBucket + 1; i < hashTable->numBuckets; ++i) {
            if (!hashTable->bucket[i].empty()) {
                currBucket = i;
                currLocation = hashTable->bucket[i].begin();
                return;
            }
        }

        currBucket = -1;  // at the end()
    }

    template<typename T, typename HashFunc>
    HashTable<T, HashFunc>::Iterator::Iterator()
    {}

    template<typename T, typename HashFunc>
    T &HashTable<T, HashFunc>::Iterator::operator*()
    {
        if (currBucket == -1) {  // dereference end()
            throw range_error("HashTable::Iterator.*: reference error");
        }

        return *currLocation;
    }

    template<typename T, typename HashFunc>
    bool HashTable<T, HashFunc>::Iterator::operator==(const Iterator &rhs) const
    {
        if (currBucket == rhs.currBucket) {
            if (currBucket == -1) {  // end() == end()
                return true;
            } else {
                return currLocation == rhs.currLocation;
            }
        } else {
            return false;
        }
    }

    template<typename T, typename HashFunc>
    bool HashTable<T, HashFunc>::Iterator::operator!=(const Iterator &rhs) const
    {
        if (currBucket != rhs.currBucket) {
            return true;
        } else {
            if (currBucket == -1) {
                return false;
            } else {
                return currLocation != rhs.currLocation;
            }
        }
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::Iterator&
    HashTable<T, HashFunc>::Iterator::operator++()
    {
        if (++currLocation == hashTable->bucket[currBucket].end()) {
            findNext();
        }

        return *this;
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::Iterator
    HashTable<T, HashFunc>::Iterator::operator++(int)
    {
        Iterator iter = *this;

        if (++currLocation == hashTable->bucket[currBucket].end()) {
            findNext();
        }

        return iter;
    }


    template<typename T, typename HashFunc>
    class HashTable<T, HashFunc>::ConstIterator {
    public:
        friend class HashTable<T, HashFunc>;

        friend class HashTable<T, HashFunc>::Iterator;

        ConstIterator();

        const T &operator*();

        bool operator==(const ConstIterator &rhs) const;

        bool operator!=(const ConstIterator &rhs) const;

        ConstIterator &operator++();

        ConstIterator operator++(int);

    private:
        const HashTable<T, HashFunc> *hashTable;
        int currBucket;
        typename list<T>::const_iterator currLocation;

        ConstIterator(const HashTable<T, HashFunc> *hashTable, int currBucket,
                      typename list<T>::const_iterator currLocation);

        void findNext();
    };

    template<typename T, typename HashFunc>
    HashTable<T, HashFunc>::ConstIterator::ConstIterator(
        const HashTable<T, HashFunc> *hashTable,
        int currBukcet,
        typename list<T>::const_iterator currLocation) :
        hashTable(hashTable),
        currBucket(currBucket),
        currLocation(currLocation) {}

    template<typename T, typename HashFunc>
    void HashTable<T, HashFunc>::ConstIterator::findNext()
    {
        for (int i = currBucket + 1; i < hashTable->numBuckets; ++i) {
            if (!hashTable->bucket[i].empty()) {
                currBucket = i;
                currLocation = hashTable->bucket[i].begin();
                return;
            }
        }

        currBucket = -1;  // at the end()
    }

    template<typename T, typename HashFunc>
    HashTable<T, HashFunc>::ConstIterator::ConstIterator() {}

    template<typename T, typename HashFunc>
    const T &HashTable<T, HashFunc>::ConstIterator::operator*()
    {
        if (currBucket == -1) {  // dereference end()
            throw range_error("HashTable::ConstIterator.*: reference error");
        }

        return *currLocation;
    }

    template<typename T, typename HashFunc>
    bool HashTable<T, HashFunc>::ConstIterator::operator==(
        const ConstIterator &rhs) const
    {
        if (currBucket == rhs.currBucket) {
            if (currBucket == -1) {  // end() == end()
                return true;
            } else {
                return currLocation == rhs.currLocation;
            }
        } else {
            return false;
        }
    }

    template<typename T, typename HashFunc>
    bool HashTable<T, HashFunc>::ConstIterator::operator!=(
        const ConstIterator &rhs) const
    {
        if (currBucket != rhs.currBucket) {
            return true;
        } else {
            if (currBucket == -1) {
                return false;
            } else {
                return currLocation != rhs.currLocation;
            }
        }
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::ConstIterator&
    HashTable<T, HashFunc>::ConstIterator::operator++()
    {
        if (++currLocation == hashTable->bucket[currBucket].end()) {
            findNext();
        }

        return *this;
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::ConstIterator
    HashTable<T, HashFunc>::ConstIterator::operator++(int)
    {
        ConstIterator iter = *this;

        if (++currLocation == hashTable->bucket[currBucket].end()) {
            findNext();
        }

        return *this;
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::Iterator
    HashTable<T, HashFunc>::find(const T &item)
    {
        int hashIndex = static_cast<int>(hf(item) % numBuckets);
        for (typename list<T>::iterator bucketIter = bucket[hashIndex].begin();
             bucketIter != bucket[hashIndex].end(); ++bucketIter) {
            if (item == *bucketIter) {
                return Iterator(this, hashIndex, bucketIter);
            }
        }

        return end();
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::ConstIterator
    HashTable<T, HashFunc>::find(const T &item) const
    {
        int hashIndex = static_cast<int>(hf(item) % numBuckets);
        for (typename list<T>::const_iterator
                 bucketIter = bucket[hashIndex].begin();
             bucketIter != bucket[hashIndex].end(); ++bucketIter) {
            if (item == *bucketIter) {
                return ConstIterator(this, hashIndex, bucketIter);
            }
        }

        return end();
    }

    template<typename T, typename HashFunc>
    pair<typename HashTable<T, HashFunc>::Iterator, bool>
    HashTable<T, HashFunc>::insert(const T &item)
    {
        int hashIndex = static_cast<int>(hf(item) % numBuckets);
        typename list<T>::iterator bucketIter = bucket[hashIndex].begin();
        for ( ; bucketIter != bucket[hashIndex].end(); ++bucketIter) {
            if (*bucketIter == item) {
                break;
            }
        }

        bool success = false;
        if (bucketIter == bucket[hashIndex].end()) {
            bucketIter = bucket[hashIndex].insert(bucketIter, item);
            ++hashTableSize;
            success = true;
        }

        return pair<Iterator, bool>(Iterator(this, hashIndex, bucketIter), success);
    }

    template<typename T, typename HashFunc>
    int HashTable<T, HashFunc>::erase(const T &item)
    {
        if (empty()) {
            throw underflow_error(
                "HashTable.erase(): HashTable table is empty");
        }

        int numErased = 0;
        Iterator iter = find(item);
        if (iter != end()) {
            erase(iter);
            numErased = 1;
        }

        return numErased;
    }

    template<typename T, typename HashFunc>
    void HashTable<T, HashFunc>::erase(Iterator pos)
    {
        if (empty()) {
            throw underflow_error(
                "HashTable.erase(): HashTable table is empty");
        }

        if (pos == end()) {
            throw range_error("Hahs.erase(): invalid iterator");
        }

        bucket[pos.currBucket].erase(pos.currLocation);
        --hashTableSize;
    }

    template<typename T, typename HashFunc>
    void HashTable<T, HashFunc>::erase(Iterator first, Iterator last)
    {
        if (empty()) {
            throw underflow_error("HashTable.erase(): HashTable table is empty");
        }

        while (first != last) {
            erase(first++);
        }
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::Iterator HashTable<T, HashFunc>::begin()
    {
        typename HashTable<T, HashFunc>::Iterator iter;
        iter.hashTable = this;
        iter.currBucket = -1;
        iter.findNext();

        return iter;
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::Iterator HashTable<T, HashFunc>::end()
    {
        typename HashTable<T, HashFunc>::Iterator iter;
        iter.hashTable = this;
        iter.currBucket = -1;

        return iter;
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::ConstIterator HashTable<T, HashFunc>::begin() const
    {
        typename HashTable<T, HashFunc>::ConstIterator iter;
        iter.hashTable = this;
        iter.currBucket = -1;
        iter.findNext();

        return iter;
    }

    template<typename T, typename HashFunc>
    typename HashTable<T, HashFunc>::ConstIterator HashTable<T, HashFunc>::end() const
    {
        typename HashTable<T, HashFunc>::ConstIterator iter;
        iter.hashTable = this;
        iter.currBucket = -1;

        return iter;
    }
}

#endif  // ALGORITHM_HASH_TABLE_H