#ifndef ALGORITHM_BINARY_TREE_UTIL_H
#define ALGORITHM_BINARY_TREE_UTIL_H

#include <iostream>
#include <string>
#include <queue>

#include "binary_tree_node.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::string;
    using std::queue;

    // 二叉树中序遍历
    // 访问顺序：左子树 -> 根节点 -> 右子树
    template <typename T>
    void inorderTraversal(BTreeNode<T> *treeNode, const string &separator = "  ")
    {
        if (treeNode != nullptr) {
            inorderTraversal<T>(treeNode->left, separator);
            cout << treeNode->value << separator;
            inorderTraversal<T>(treeNode->right, separator);
        }
    }

    // 二叉树前序遍历
    // 访问顺序：根节点 -> 左子树 -> 右子树
    template <typename T>
    void preorderTraversal(BTreeNode<T> *treeNode, const string &separator = "  ")
    {
        if (treeNode != nullptr) {
            cout << treeNode->value << separator;
            preorderTraversal<T>(treeNode->left, separator);
            preorderTraversal<T>(treeNode->right, separator);
        }
    }

    // 二叉树后序遍历
    // 访问顺序：左子树 -> 右子树 -> 根节点
    template <typename T>
    void postorderTraversal(BTreeNode<T> *treeNode, const string &separator = "  ")
    {
        if (treeNode != nullptr) {
            postorderTraversal<T>(treeNode->left, separator);
            postorderTraversal<T>(treeNode->right, separator);
            cout << treeNode->value << separator;
        }
    }

    // 二叉树层次遍历
    // 按层次访问元素，首先是根节点，然后是第一层的子节点，第二层的子节点，以此类推
    template <typename T>
    void levelorderTraversal(BTreeNode<T> *treeNode, const string &separator = "  ")
    {
        queue<BTreeNode<T>*> treeNodeQueue;
        treeNodeQueue.push(treeNode);   // 将根节点插入队列

        BTreeNode<T> *node;
        while (!treeNodeQueue.empty()) {
            // 删除队首元素（节点），输出该节点值。
            // 该节点若有左右子节点，则分别将其插入队列
            node = treeNodeQueue.front();
            treeNodeQueue.pop();
            cout << node->value << separator;

            if (node->left != nullptr) {
                treeNodeQueue.push(node->left);
            }

            if (node->right != nullptr) {
                treeNodeQueue.push(node->right);
            }
        }
    }

    // 遍历二叉树中的节点，并删除每个节点
    template <typename T>
    void deleteTree(BTreeNode<T> *treeNode)
    {
        if (treeNode != nullptr) {
            deleteTree(treeNode->left);
            deleteTree(treeNode->right);
            delete treeNode;
        }
    }

    // 删除树中所有节点
    template <typename T>
    void clearTree(BTreeNode<T> *&treeNode)
    {
        deleteTree(treeNode);
        treeNode = nullptr;
    }

    // 复制二叉树（使用后序遍历），并返回新二叉树的根节点的指针
    template <typename T>
    BTreeNode<T>* copyTree(BTreeNode<T> *treeNode)
    {
        if (treeNode == nullptr) {
            return nullptr;
        }

        BTreeNode<T> *leftCopy = copyTree(treeNode->left);
        BTreeNode<T> *rightCopy = copyTree(treeNode->right);
        BTreeNode<T> *newTreeNode =
            new BTreeNode<T>(treeNode->value, leftCopy, rightCopy);

        return newTreeNode;
    }

    // 叶节点计数
    template <typename T>
    void countLeave(BTreeNode<T> *treeNode, int &count)
    {
        if (treeNode != nullptr) {
            // 某节点的左右节点均为空，则该节点为叶节点
            if (treeNode->left == nullptr && treeNode->right == nullptr) {
                ++count;
            }

            countLeave(treeNode->left, count);
            countLeave(treeNode->right, count);
        }
    }

    // 计算二叉树中的节点数目
    template <typename T>
    void countNodes(BTreeNode<T> *treeNode, int &count)
    {
        if (treeNode != nullptr) {
            countNodes(treeNode->left, count);
            ++count;
            countNodes(treeNode->right, count);
        }
    }

    // 计算二叉树中的节点数目
    template <typename T>
    int countNodes(BTreeNode<T> *treeNode)
    {
        if (treeNode != nullptr) {
            return 1 + countNodes(treeNode->left) + countNodes(treeNode->right);
        } else {
            return 0;
        }
    }

    // 计算二叉树中有子节点的节点数
    template <typename T>
    int countSubNodes(BTreeNode<T> *treeNode)
    {
        int n = 0;
        if (treeNode != nullptr) {
            if (treeNode->left != nullptr || treeNode->right != nullptr) {
                n++;
            }
            return n + countSubNodes(treeNode->left) + countSubNodes(treeNode->right);
        } else {
            return 0;
        }
    }

    // 计算只有一个子节点的内部节点数
    template <typename T>
    int countOneChildNodes(BTreeNode<T> *treeNode)
    {
        if (treeNode == nullptr) {
            return 0;
        }

        if (treeNode->left == nullptr && treeNode->right == nullptr) {
            return 0;
        } else if (treeNode->left != nullptr && treeNode->right == nullptr) {
            return 1 + countOneChildNodes(treeNode->left);
        } else if (treeNode->left == nullptr && treeNode->right != nullptr) {
            return 1 + countOneChildNodes(treeNode->right);
        } else {
            return countOneChildNodes(treeNode->left) + countOneChildNodes(treeNode->right);
        }
    }

    // 计算二叉树中的边数
    template <typename T>
    int countEdges(BTreeNode<T> *treeNode)
    {
        int edges = 0;
        int leftEdges = 0, rightEdges = 0;

        if (treeNode != nullptr) {
            if (treeNode->left != nullptr) {
                edges++;
            }

            if (treeNode->right != nullptr) {
                edges++;
            }

            leftEdges = countEdges(treeNode->left);
            rightEdges = countEdges(treeNode->right);

            return edges + leftEdges + rightEdges;
        } else {
            return 0;
        }
    }

    // 计算树的深度
    template <typename T>
    int countDepth(BTreeNode<T> *treeNode)
    {
        int depthLeftLeaf = 0;
        int depthRightLeaf = 0;
        int depthValue = 0;
        if (treeNode == nullptr) {
            // 空树的深度为 -1
            depthValue = -1;
        } else {
            //根节点的深度等于左右子树深度的较大值加一
            depthLeftLeaf = countDepth(treeNode->left);
            depthRightLeaf = countDepth(treeNode->right);
            depthValue = (depthLeftLeaf > depthRightLeaf ? depthLeftLeaf : depthRightLeaf) + 1;
        }

        return depthValue;
    }
}

#endif  // ALGORITHM_BINARY_TREE_UTIL_H
