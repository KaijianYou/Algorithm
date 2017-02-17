#ifndef ALGORITHM_BINARY_SEARCH_TREE_NODE_H
#define ALGORITHM_BINARY_SEARCH_TREE_NODE_H

#include <string>

namespace myalgorithm {
    using std::string;
    
    template <typename T>
    struct BSTreeNode {
        T value;
        BSTreeNode<T> *left;
        BSTreeNode<T> *right;
        BSTreeNode<T> *parent;

        BSTreeNode(const T &value, BSTreeNode *left = nullptr, 
                   BSTreeNode *right = nullptr, BSTreeNode *parent = nullptr) :
                value(value), left(left), right(right), parent(parent)
        {}
    };

    struct BSTreeShadowNode {
        string valueStr;  // 把树节点值格式化后的字符串
        int level;
        int column;
        BSTreeShadowNode *left;
        BSTreeShadowNode *right;

        BSTreeShadowNode()
        {}
    };
}

#endif  // ALGORITHM_BINARY_SEARCH_TREE_NODE_H