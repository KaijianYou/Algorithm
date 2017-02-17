#ifndef ALGORITHM_SET_BASED_ON_BINARY_SEARCH_TREE_H
#define ALGORITHM_SET_BASED_ON_BINARY_SEARCH_TREE_H

#include "../tree/binary_search_tree.h"

namespace myalgorithm {
    // 基于二叉搜索树的集合的简单实现
    template <typename T>
    class Set {
    public:
        typedef typename BinarySearchTree<T>::Iterator Iterator;
        typedef typename BinarySearchTree<T>::ConstIterator ConstIterator;

        Set();
        Set(const Set &obj);
        Set(T *first, T *last);
        virtual ~Set();

        Set operator=(const Set &obj);

        bool empty() const;
        int size() const;

        Iterator find(const T &item);
        ConstIterator find(const T &item) const;
        bool contains(const T &item) const;

        // 插入值为 item 的新元素并返回一个 pair 对象，pair.first 
        // 为指向新元素的迭代器，pair.second 为 true，若元素存在，
        // 则 pair.first 为指向现有元素的迭代器，pair.second 为 false
        pair<Iterator, bool> insert(const T &item);

        // 删除迭代器 pos 指向的元素
        void erase(Iterator pos);

        // 如果 item 存在，则删除它并返回 1；否则返回 0
        int erase(const T &item);

        // 删除 [first, last) 迭代器指向范围内的元素
        void erase(Iterator first, Iterator last);

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

        friend bool operator==(const Set<T> &lhs, const Set<T> &rhs);
        friend Set<T> operator+(const Set<T> &lhs, const Set<T> &rhs);
        friend Set<T> operator-(const Set<T> &lhs, const Set<T> &rhs);
        friend Set<T> operator*(const Set<T> &lhs, const Set<T> &rhs);

    private:
        BinarySearchTree<T> tree;
    };

    template <typename T>
    Set<T>::Set()
    {}

    template <typename T>
    Set<T>::Set(T *first, T *last) : tree(first, last)
    {}

    template <typename T>
    Set<T>::Set(const Set &obj) : tree(obj.tree)
    {}

    template <typename T>
    Set<T>::~Set()
    {}

    template <typename T>
    Set<T> Set<T>::operator=(const Set<T> &obj)
    {
        if (this != &obj) {
            tree = obj.tree;
        }

        return *this;
    }

    template <typename T>
    bool Set<T>::empty() const
    {
        return size() == 0;
    }

    template <typename T>
    int Set<T>::size() const
    {
        return tree.size();
    }

    template <typename T>
    typename Set<T>::Iterator Set<T>::find(const T &item)
    {
        return tree.find(item);
    }

    template <typename T>
    typename Set<T>::ConstIterator Set<T>::find(const T &item) const
    {
        return tree.find(item);
    }

    template <typename T>
    bool Set<T>::contains(const T &item) const
    {
        if (find(item) != end()) {
            return true;
        } else {
            return false;
        }
    }

    template <typename T>
    pair<typename Set<T>::Iterator, bool> Set<T>::insert(const T &item)
    {
        return tree.insert(item);
    }

    template <typename T>
    void Set<T>::erase(Iterator pos)
    {
        if (size() == 0) {
            throw underflow_error("Set.erase(): set is empty");
        }

        if (pos == end()) {
            throw range_error("Set.erase(): invalid interator");
        }

        tree.erase(pos);
    }

    template <typename T>
    int Set<T>::erase(const T &item)
    {
        return tree.erase(item);
    }

    template <typename T>
    void Set<T>::erase(Iterator first, Iterator last)
    {
        if (empty()) {
            throw underflow_error("Set.erase(): set is empty");
        }

        tree.erase(first, last);
    }

    template <typename T>
    typename Set<T>::Iterator Set<T>::begin()
    {
        return tree.begin();
    }

    template <typename T>
    typename Set<T>::Iterator Set<T>::end()
    {
        return tree.end();
    }

    template <typename T>
    typename Set<T>::ConstIterator Set<T>::begin() const
    {
        return tree.begin();
    }

    template <typename T>
    typename Set<T>::ConstIterator Set<T>::end() const
    {
        return tree.end();
    }

    template <typename T>
    bool operator==(const Set<T> &lhs, const Set<T> &rhs)
    {
        typename Set<T>::ConstIterator lhsIter = lhs.begin();
        typename Set<T>::ConstIterator rhsIter = rhs.begin();
        if (lhs.size() == rhs.size()) {
            while (lhsIter != lhs.end() && *lhsIter++ == *rhsIter++) {
                ;
            }

            if (lhsIter != lhs.end()) {
                return false;
            } else {
                return true;
            }
        }

        return false;
    }

    template <typename T>
    Set<T> operator+(const Set<T> &lhs, const Set<T> &rhs)
    {
        Set<T> unionSet;
        for (typename Set<T>::ConstIterator iter = lhs.begin(); iter != lhs.end(); ++iter) {
            unionSet.insert(*iter);
        }

        for (typename Set<T>::ConstIterator iter = rhs.begin(); iter != rhs.end(); ++iter) {
            unionSet.insert(*iter);
        }

        return unionSet;
    }

    template <typename T>
    Set<T> operator-(const Set<T> &lhs, const Set<T> &rhs)
    {
        Set<T> differenceSet;
        typename Set<T>::ConstIterator lhsIter = lhs.begin();
        typename Set<T>::ConstIterator rhsIter = rhs.begin();

        while (lhsIter != lhs.end() && rhsIter != rhs.end()) {
            if (*lhsIter < *rhsIter) {
                differenceSet.insert(*lhsIter++);
            } else if (*rhsIter < *lhsIter) {
                rhsIter++;
            } else {
                lhsIter++;
                rhsIter++;
            }
        }

        if (lhsIter != lhs.end()) {
            while (lhsIter != lhs.end()) {
                differenceSet.insert(*lhsIter++);
            }
        }

        return differenceSet;
    }

    template <typename T>
    Set<T> operator*(const Set<T> &lhs, const Set<T> &rhs)
    {
        Set<T> intersectionSet;
        typename Set<T>::ConstIterator lhsIter = lhs.begin();
        typename Set<T>::ConstIterator rhsIter = rhs.begin();
        while (lhsIter != lhs.end() && rhsIter != rhs.end()) {
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
}

#endif  // ALGORITHM_SET_BASED_ON_BINARY_SEARCH_TREE_H