#ifndef ALGORITHM_BINARY_TREE_UTIL_H
#define ALGORITHM_BINARY_TREE_UTIL_H

#include <iostream>

#include "../../algorithm/tree/binary_tree_util.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    // 创建一棵如下的二叉树：
    //      b
    //    /   \
    //   e     d
    //  / \   / \
    // c   k p   g
    //    /       \
    //   h         o
    BinaryTreeNode<char>* buildTree()
    {
        BinaryTreeNode<char> *root, *e, *d, *c, *k, *p, *g, *h, *o;
        o = new BinaryTreeNode<char>('o', nullptr, nullptr);
        h = new BinaryTreeNode<char>('h', nullptr, nullptr);
        g = new BinaryTreeNode<char>('g', nullptr, o);
        p = new BinaryTreeNode<char>('p', nullptr, nullptr);
        c = new BinaryTreeNode<char>('c', nullptr, nullptr);
        k = new BinaryTreeNode<char>('k', h, nullptr);
        d = new BinaryTreeNode<char>('d', p, g);
        e = new BinaryTreeNode<char>('e', c, k);
        root = new BinaryTreeNode<char>('b', e, d);

        return root;
    }

    void testTreeTraversal()
    {
        BinaryTreeNode<char> *root = buildTree();

        cout << "Preorder scan:    ";
        preorderTraversal(root);
        cout << endl;

        cout << "Inorder scan:     ";
        inorderTraversal(root);
        cout << endl;

        cout << "Postorder scan:   ";
        postorderTraversal(root);
        cout << endl;

        cout << "Level-order scan: ";
        levelorderTraversal(root);
        cout << endl;
    }

    void testCopyTree()
    {
        BinaryTreeNode<char> *origRoot = buildTree();
        cout << "level-order scan orig tree: ";
        levelorderTraversal(origRoot);
        cout << endl;

        BinaryTreeNode<char> *newRoot = copyTree(origRoot);
        cout << "level-order scan new tree:  ";
        levelorderTraversal(newRoot);
        cout << endl;
    }

    void testCountTree()
    {
        BinaryTreeNode<char> *root = buildTree();

        int numLeaves = 0;
        countLeave(root, numLeaves);
        cout << "Leaves:        " << numLeaves << endl;

        int numNodes = 0;
        countNodes(root, numNodes);
        cout << "Nodes:         " << numNodes << endl;
        cout << "Nodes:         " << countNodes(root) << endl;

        cout << "SubNodes:      " << countSubNodes(root) << endl;

        cout << "OneChildNodes: " << countOneChildNodes(root) << endl;

        cout << "Edges:         " << countEdges(root) << endl;

        cout << "Depth:         " << countDepth(root) << endl;
    }
}

#endif  // ALGORITHM_BINARY_TREE_UTIL_H
