#ifndef ALGORITHM_MAP_BASED_ON_BINARY_TREE_H
#define ALGORITHM_MAP_BASED_ON_BINARY_TREE_H

#include "../tree/binary_search_tree.h"
#include "pair.h"

namespace myalgorithm {
    // map 基于二叉搜索树的简单实现
    // 使用二叉搜索树作为内部存储容器，用 Pair 作为二叉搜索树的模板类型参数
    template <typename Key, typename T>
    class Map {
    public:
        typedef typename BinarySearchTree<Pair<const Key, T>>::Iterator Iterator;
        typedef typename BinarySearchTree<Pair<const Key, T>>::ConstIterator ConstIterator;

        typedef Pair<const Key, T> value_type;

        Map();
        Map(value_type *first, value_type *last);
        Map(const Map &obj);
        virtual ~Map();

        Map operator=(const Map &obj);
        T& operator[](const Key &key);

        bool empty() const;
        int size() const;

        Iterator find(const Key &key);
        ConstIterator find(const Key &key) const;

        int count(const Key &key) const;

        pair<Iterator, bool> insert(const value_type &pairValue);
        int erase(const Key &key);
        void erase(Iterator pos);
        void erase(Iterator first, Iterator last);

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

    private:
        BinarySearchTree<Pair<const Key, T>> tree;
    };

    template <typename Key, typename T>
    Map<Key, T>::Map()
    {}

    template <typename Key, typename T>
    Map<Key, T>::Map(value_type *first, value_type *last) : tree(first, last)
    {}

    template <typename Key, typename T>
    Map<Key, T>::Map(const Map<Key, T> &obj) : tree(obj.tree)
    {}

    template <typename Key, typename T>
    Map<Key, T>::~Map()
    {}

    template <typename Key, typename T>
    Map<Key, T> Map<Key, T>::operator=(const Map<Key, T> &obj)
    {
        if (this != &obj) {
            tree = obj.tree;
        }

        return *this;
    }

    template <typename Key, typename T>
    T& Map<Key, T>::operator[](const Key &key)
    {
        value_type tmp(key, T());
        Iterator iter = tree.inesrt(tmp).first;
        return (*iter).second;
    }

    template <typename Key, typename T>
    bool Map<Key, T>::empty() const
    {
        return size() == 0;
    }

    template <typename Key, typename T>
    int Map<Key, T>::size() const
    {
        return tree.size();
    }

    template <typename Key, typename T>
    typename Map<Key, T>::Iterator Map<Key, T>::find(const Key &key)
    {
        return tree.find(value_type(key, T()));
    }

    template <typename Key, typename T>
    typename Map<Key, T>::ConstIterator Map<Key, T>::find(const Key &key) const
    {
        return tree.find(value_type(key, T()));
    }

    template <typename Key, typename T>
    int Map<Key, T>::count(const Key &key) const
    {
        return tree.count(value_type(key, T()));
    }

    template <typename Key, typename T>
    pair<typename Map<Key, T>::Iterator, bool> Map<Key, T>::insert(const value_type &pairValue)
    {
        pair<Iterator, bool> p = tree.insert(pairValue);
        return pair<Iterator, bool>(p.first, p.second);
    }

    template <typename Key, typename T>
    int Map<Key, T>::erase(const Key &key)
    {
        return tree.erase(value_type(key, T()));
    }

    template <typename Key, typename T>
    void Map<Key, T>::erase(Iterator pos)
    {
        tree.erase(pos);
    }

    template <typename Key, typename T>
    void Map<Key, T>::erase(Iterator first, Iterator last)
    {
        tree.erase(first, last);
    }

    template <typename Key, typename T>
    typename Map<Key, T>::Iterator Map<Key, T>::begin()
    {
        return tree.begin();
    }

    template <typename Key, typename T>
    typename Map<Key, T>::Iterator Map<Key, T>::end()
    {
        return tree.end();
    }

    template <typename Key, typename T>
    typename Map<Key, T>::ConstIterator Map<Key, T>::begin() const
    {
        return tree.begin();
    }

    template <typename Key, typename T>
    typename Map<Key, T>::ConstIterator Map<Key, T>::end() const
    {
        return tree.end();
    }
}

#endif  // ALGORITHM_MAP_BASED_ON_BINARY_TREE_H