#ifndef ALGORITHM_BINARY_TREE_NODE_H
#define ALGORITHM_BINARY_TREE_NODE_H

namespace myalgorithm {
    // 二叉树节点
    template <typename T>
    struct BTreeNode {
        T value;
        BTreeNode<T> *left;
        BTreeNode<T> *right;

        BTreeNode()
        {}

        BTreeNode(const T &value, BTreeNode<T> *left = nullptr, BTreeNode<T> *right = nullptr) :
                value(value), left(left), right(right)
        {}
    };
}

#endif  // ALGORITHM_BINARY_TREE_NODE_H