#ifndef ALGORITHM_BINARY_SEARCH_TREE_H
#define ALGORITHM_BINARY_SEARCH_TREE_H

#include <sstream>
#include <iomanip>
#include <queue>

#include "binary_search_tree_node.h"

namespace myalgorithm {
    using std::queue;
    using std::ostringstream;
    using std::ends;
    using std::setw;

    // 第一个插入的节点为根节点，随后插入的元素如果比当前节点小，则设为当前节点的左子节点，
    // 反之，设为右子节点
    // 不能存储重复元素
    template <typename T>
    class BinarySearchTree {
    public:
        class Iterator;
        class ConstIterator;

        BinarySearchTree();
        BinarySearchTree(T *first, T *last);
        BinarySearchTree(const BinarySearchTree &obj);
        virtual ~BinarySearchTree();

        BinarySearchTree& operator=(const BinarySearchTree &rhs);

        int size() const;
        bool empty() const;

        // 显示二叉树，maxCharacters 是输出节点值所需要的最大字符数
        void displayTree(int maxCharacters);

        // pair.second 如果为 true，pair.first 指向新插入的元素的位置；
        // pair.second 如果未 false，pair.first 指向现有元素的位置
        pair<Iterator, bool> insert(const T &item);

        Iterator find(const T &item);
        ConstIterator find(const T &item) const;
        
        int count(const T &item) const;

        // 删除节点值为 item 的节点，并返回删除的节点的个数
        int erase(const T &item);

        // 删除迭代器 pos 指向的节点
        void erase(Iterator pos);

        // 删除迭代器范围在 [first, last) 中的所有节点
        void erase(Iterator first, Iterator last);

        // 返回指向中序遍历二叉树时的第一个节点的迭代器
        Iterator begin();
        // 返回指向 nullptr 的迭代器
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

        // 查找与 item 值匹配的节点并返回它的深度，没有找到则返回 -1
        int treeNodeLevel(const T &item);

    private:
        BSTreeNode<T> *root;
        int treeSize;

        BSTreeNode<T>* getTreeNode(const T &item, BSTreeNode<T> *left, BSTreeNode<T> *right, BSTreeNode<T> *parent);
        // 复制树节点
        BSTreeNode<T>* copyTree(BSTreeNode<T> *treeNode);
        // 删除树节点
        void deleteTree(BSTreeNode<T> *treeNode);
        
        BSTreeNode<T>* findNode(const T &item) const;
        
        BSTreeShadowNode* buildShadowTree(BSTreeNode<T> *treeNode, int level, int &column);
        void deleteShadowTree(BSTreeShadowNode *ts);
    };

    template <typename T>
    BSTreeNode<T>*BinarySearchTree<T>::getTreeNode(const T &item, BSTreeNode<T> *left,
                                     BSTreeNode<T> *right, BSTreeNode<T> *parent)
    {
        return new BSTreeNode<T>(item, left, right, parent);
    }

    template <typename T>
    BSTreeNode<T>* BinarySearchTree<T>::copyTree(BSTreeNode<T> *treeNode)
    {
        if (treeNode == nullptr) {
            return nullptr;
        }

        BSTreeNode<T> *leftCopy = copyTree(treeNode->left);
        BSTreeNode<T> *rightCopy = copyTree(treeNode->right);
        BSTreeNode<T> *newNode = getTreeNode(treeNode->value, leftCopy, rightCopy, nullptr);

        if (leftCopy != nullptr) {
            leftCopy->parent = newNode;
        }
        if (rightCopy != nullptr) {
            rightCopy->parent = newNode;
        }

        return newNode;
    }

    template <typename T>
    void BinarySearchTree<T>::deleteTree(BSTreeNode<T> *treeNode)
    {
        if (treeNode != nullptr) {
            deleteTree(treeNode->left);
            deleteTree(treeNode->right);
            delete treeNode;
        }
    }

    template <typename T>
    BSTreeNode<T>* BinarySearchTree<T>::findNode(const T &item) const
    {
        BSTreeNode<T> *curr = root;
        while ((curr != nullptr) && !(curr->value == item)) {
            if (item < curr->value) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        return curr;
    }

    template <typename T>
    BSTreeShadowNode*
    BinarySearchTree<T>::buildShadowTree(BSTreeNode<T> *treeNode, int level, int &column)
    {
        BSTreeShadowNode *newNode = nullptr;
        ostringstream ostr;

        if (treeNode != nullptr) {
            newNode = new BSTreeShadowNode;

            BSTreeShadowNode *newLeft = buildShadowTree(treeNode->left, level + 1, column);
            newNode->left = newLeft;

            ostr << treeNode->value << ends;
            newNode->valueStr = ostr.str();
            newNode->level = level;
            newNode->column = column;

            ++column;

            BSTreeShadowNode *newRight = buildShadowTree(treeNode->right, level + 1, column);
            newNode->right = newRight;
        }

        return newNode;
    }

    template <typename T>
    void BinarySearchTree<T>::deleteShadowTree(BSTreeShadowNode *ts)
    {
        if (ts != nullptr) {
            deleteShadowTree(ts->left);
            deleteShadowTree(ts->right);
            delete ts;
        }
    }

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree() : root(nullptr), treeSize(0)
    {}

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(T *first, T *last) : root(nullptr), treeSize(0)
    {
        for (T *p = first; p != last; ++p) {
            insert(*p);
        }
    }

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &obj) :
            treeSize(obj.treeSize)
    {
        root = copyTree(obj.root);
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        deleteTree(root);
        root = nullptr;
        treeSize = 0;
    }

    template <typename T>
    BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T> &obj)
    {
        if (this == &obj) {
            return *this;
        }

        deleteTree(root);
        root = copyTree(obj.root);
        treeSize = obj.treeSize;

        return *this;
    }

    template <typename T>
    int BinarySearchTree<T>::size() const
    {
        return treeSize;
    }

    template <typename T>
    bool BinarySearchTree<T>::empty() const
    {
        return size() == 0;
        // return root == nullptr;
    }

    template <typename T>
    void BinarySearchTree<T>::displayTree(int maxCharacters)
    {
        if (empty()) {
            return;
        }

        int level = 0;
        int column = 0;
        BSTreeShadowNode *shadowRoot = buildShadowTree(root, level, column);

        queue<BSTreeShadowNode *> q;
        q.push(shadowRoot);

        BSTreeShadowNode *currNode;
        int currLevel = 0;
        int currColumn = 0;
        int colWidth = maxCharacters + 1;

        while (!q.empty()) {
            currNode = q.front();
            q.pop();

            if (currNode->level > currLevel) {
                currLevel = currNode->level;
                currColumn = 0;
                cout << endl;
            }

            if (currNode->left != nullptr) {
                q.push(currNode->left);
            }

            if (currNode->right != nullptr) {
                q.push(currNode->right);
            }

            if (currNode->column > currColumn) {
                cout << setw((currNode->column - currColumn) * colWidth) << " ";
                currColumn = currNode->column;
            }

            cout << setw(colWidth) << currNode->valueStr;
            ++currColumn;
        }
        cout << endl;

        deleteShadowTree(shadowRoot);
    }

    template <typename T>
    pair<typename BinarySearchTree<T>::Iterator, bool> BinarySearchTree<T>::insert(const T &item)
    {
        BSTreeNode<T> *curr = root;
        BSTreeNode<T> *parent = nullptr;
        while (curr != nullptr) {
            parent = curr;
            // 如果树中已有匹配的值，则返回一个 pair 对象，
            // 则 pair.first 设为指向匹配节点的迭代器，pair.second 设为 false
            if (item == curr->value) {
                return pair<Iterator, bool>(Iterator(curr, this), false);
            } else if (item < curr->value) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        BSTreeNode<T> *newNode = getTreeNode(item, nullptr, nullptr, parent);

        if (parent == nullptr) {   // 父节点为 nullptr，表示树中没有节点，因此将新节点作为根节点
            root = newNode;
        } else if (item < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        newNode->parent = parent;

        ++treeSize;

        return pair<Iterator, bool>(Iterator(newNode, this), true);
    }

    template <typename T>
    int BinarySearchTree<T>::erase(const T &item)
    {
        BSTreeNode<T> *targetNode = findNode(item);
        if (targetNode == nullptr) {
            return 0;
        } else {
            erase(Iterator(targetNode, this));
            return 1;
        }
    }

    template <typename T>
    typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::begin()
    {
        BSTreeNode<T> *curr = root;
        if (curr != nullptr) {
            // 找到中序遍历二叉树时得到的第一个节点
            while (curr->left != nullptr) {
                curr = curr->left;
            }
        }

        return Iterator(curr, this);
    }

    template <typename T>
    typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::end()
    {
        return Iterator(nullptr, this);
    }

    template <typename T>
    typename BinarySearchTree<T>::ConstIterator BinarySearchTree<T>::begin() const
    {
        const BSTreeNode<T> *curr = root;
        if (curr != nullptr) {
            while (curr->left != nullptr) {
                curr = curr->left;
            }
        }

        return ConstIterator(curr, this);
    }

    template <typename T>
    typename BinarySearchTree<T>::ConstIterator BinarySearchTree<T>::end() const
    {
        return ConstIterator(nullptr, this);
    }

    template <typename T>
    class BinarySearchTree<T>::Iterator {
    public:
        friend class BinarySearchTree<T>;

        Iterator();

        T& operator*();

        bool operator==(const Iterator &rhs) const;
        bool operator!=(const Iterator &rhs) const;

        Iterator& operator++();  // 指针从当前节点移动到中序遍历时的下一个节点
        Iterator& operator--();  // 指针从当前节点移动到中序遍历时的上一个节点
        Iterator operator++(int);
        Iterator operator--(int);

    private:
        BSTreeNode<T> *ptr;
        BinarySearchTree<T> *tree;  // 指向与当前迭代器相关联的 BinarySearchTree 对象，用于访问根节点

        Iterator(BSTreeNode<T> *ptr, BinarySearchTree<T> *tree);
    };

    template <typename T>
    BinarySearchTree<T>::Iterator::Iterator(BSTreeNode<T> *ptr,
                                            BinarySearchTree<T> *tree) :
            ptr(ptr), tree(tree)
    {}

    template <typename T>
    BinarySearchTree<T>::Iterator::Iterator()
    {}

    template <typename T>
    T& BinarySearchTree<T>::Iterator::operator*()
    {
        if (ptr == nullptr) {
            throw range_error("BinarySearchTree::Iterator.*: reference error");
        }

        return ptr->value;
    }

    template <typename T>
    bool BinarySearchTree<T>::Iterator::operator==(const Iterator &rhs) const
    {
        return ptr == rhs.ptr;
    }

    template <typename T>
    bool BinarySearchTree<T>::Iterator::operator!=(const Iterator &rhs) const
    {
        return ptr != rhs.ptr;
    }

    template <typename T>
    typename BinarySearchTree<T>::Iterator& BinarySearchTree<T>::Iterator::operator++()
    {
        if (ptr == nullptr) {
            ptr = tree->root;
            if (ptr == nullptr) {
                throw underflow_error("BinarySearchTree::Iterator.++: tree is empty");
            }

            // 一直移动指针，直到它指向中序遍历时的第一个节点（即最小的节点）
            while (ptr->left != nullptr) {
                ptr = ptr->left;
            }
        } else if (ptr->right != nullptr) {
            ptr = ptr->right;
            while (ptr->left != nullptr) {
                ptr = ptr->left;
            }
        } else {
            BSTreeNode<T> *p = ptr->parent;

            // 如果当前节点是最右边的节点（即中序遍历的最后一个节点），则自增后应指向 end()
            while (p != nullptr && p->right == ptr) {
                ptr = p;
                p = p->parent;
            }
            ptr = p;
        }

        return *this;
    }

    template <typename T>
    typename BinarySearchTree<T>::Iterator& BinarySearchTree<T>::Iterator::operator--()
    {
        if (ptr == nullptr) {
            ptr = tree->root;
            if (ptr == nullptr) {
                throw underflow_error("BinarySearchTree::Iterator.--: tree is empty");
            }

            while (ptr->right != nullptr) {
                ptr = ptr->right;
            }
        } else if (ptr->left != nullptr) {
            ptr = ptr->left;
            while (ptr->right != nullptr) {
                ptr = ptr->right;
            }
        } else {
            BSTreeNode<T> *p = ptr->parent;
            while (p != nullptr && p->left == ptr) {
                ptr = p;
                p = p->parent;
            }

            ptr = p;
        }

        return *this;
    }

    template <typename T>
    typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Iterator::operator++(int)
    {
        Iterator iter = *this;
        ++*this;

        return iter;
    }

    template <typename T>
    typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Iterator::operator--(int)
    {
        Iterator iter = *this;
        --*this;

        return iter;
    }

    template <typename T>
    class BinarySearchTree<T>::ConstIterator {
    public:
        friend class BinarySearchTree<T>;

        ConstIterator();
        ConstIterator(const Iterator &pos);

        const T& operator*() const;

        bool operator==(const ConstIterator &rhs) const;
        bool operator!=(const ConstIterator &rhs) const;

        ConstIterator& operator++();  // 指针从当前节点移动到中序遍历时的下一个节点
        ConstIterator& operator--();  // 指针从当前节点移动到中序遍历时的上一个节点
        ConstIterator operator++(int);
        ConstIterator operator--(int);

    private:
        const BSTreeNode<T> *ptr;
        const BinarySearchTree<T> *tree;  // 指向与当前迭代器相关联的 BinarySearchTree 对象，用于访问根节点

        ConstIterator(const BSTreeNode<T> *ptr, const BinarySearchTree<T> *tree);
    };

    template <typename T>
    BinarySearchTree<T>::ConstIterator::ConstIterator(const BSTreeNode<T> *ptr,
                                                      const BinarySearchTree<T> *tree) :
        ptr(ptr), tree(tree)
    {}

    template <typename T>
    BinarySearchTree<T>::ConstIterator::ConstIterator()
    {}

    template <typename T>
    BinarySearchTree<T>::ConstIterator::ConstIterator(const Iterator &pos) :
            ptr(pos.ptr), tree(pos.tree)
    {}

    template <typename T>
    const T& BinarySearchTree<T>::ConstIterator::operator*() const
    {
        if (ptr == nullptr) {
            throw range_error("BinarySearchTree::ConstIterator.*: reference error");
        }

        return ptr->value;
    }

    template <typename T>
    bool BinarySearchTree<T>::ConstIterator::operator==(const ConstIterator &rhs) const
    {
        return ptr == rhs.ptr;
    }

    template <typename T>
    bool BinarySearchTree<T>::ConstIterator::operator!=(const ConstIterator &rhs) const
    {
        return ptr != rhs.ptr;
    }

    template <typename T>
    typename BinarySearchTree<T>::ConstIterator& BinarySearchTree<T>::ConstIterator::operator++()
    {
        // 当 ptr 指向 end() 时，下一个节点就是中序遍历的第一个节点
        if (ptr == nullptr) {
            ptr = tree->root;
            if (ptr == nullptr) {
                throw underflow_error("BinarySearchTree::ConstIterator.++: tree is empty");
            }

            // 一直沿左边向下，找到第一个节点
            while (ptr->left != nullptr) {
                ptr = ptr->left;
            }
        } else if (ptr->right != nullptr) {  // 如果右子树不为空，则移动到右子树，
            ptr = ptr->right;                // 并沿着左边向下，直到当前节点的左子树为空
            while (ptr->left != nullptr) {
                ptr = ptr->left;
            }
        } else {
            // 在树中上移，查找以 ptr 节点为左子节点的父节点。如果父节点为空，
            // 则停止上移。非空的父节点是下一个节点。如果最终父节点为空，
            // 则表示初始节点为树中最后一个节点，下一个节点就是 end()
            BSTreeNode<T> *p = ptr->parent;
            while (p != nullptr && p->right == ptr) {
                ptr = p;
                p = p->parent;
            }
            ptr = p;
        }

        return *this;
    }

    template <typename T>
    typename BinarySearchTree<T>::ConstIterator& BinarySearchTree<T>::ConstIterator::operator--()
    {
        if (ptr == nullptr) {
            ptr = tree->root;
            if (ptr == nullptr) {
                throw underflow_error("BinarySearchTree::ConstIterator.--: tree is empty");
            }

            while (ptr->right != nullptr) {
                ptr = ptr->right;
            }
        } else if (ptr->left != nullptr) {  // 如果左子树不为空，则移动到左子树，
            ptr = ptr->left;                // 并沿着右边向下，直到当前节点的右子树为空
            while (ptr->right != nullptr) {
                ptr = ptr->right;
            }
        } else {
            // 在树中上移，查找以 ptr 节点为右子节点的父节点。如果父节点为空，
            // 则停止上移。非空的父节点是上一个节点。如果最终父节点为空，
            // 则表示初始节点为树中第一个节点，上一个节点就是 end()
            BSTreeNode<T> *p = ptr->parent;
            while (p != nullptr && p->left == ptr) {
                ptr = p;
                p = p->parent;
            }
            ptr = p;
        }

        return *this;
    }

    template <typename T>
    typename BinarySearchTree<T>::ConstIterator
    BinarySearchTree<T>::ConstIterator::operator++(int)
    {
        ConstIterator iter = *this;
        ++*this;

        return iter;
    }

    template <typename T>
    typename BinarySearchTree<T>::ConstIterator
    BinarySearchTree<T>::ConstIterator::operator--(int)
    {
        ConstIterator iter = *this;
        --*this;

        return iter;
    }

    template <typename T>
    typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::find(const T &item)
    {
        BSTreeNode<T> *targetNode = findNode(item);
        if (targetNode != nullptr) {
            return Iterator(targetNode, this);
        } else {
            return end();
        }
    }

    template <typename T>
    typename BinarySearchTree<T>::ConstIterator BinarySearchTree<T>::find(const T &item) const
    {
        BSTreeNode<T> *targetNode = findNode(item);
        if (targetNode != nullptr) {
            return ConstIterator(targetNode, this);
        } else {
            return end();
        }
    }

    template <typename T>
    int BinarySearchTree<T>::count(const T &item) const
    {
        return (find(item) != end()) ? 1 : 0;
    }

    template <typename T>
    void BinarySearchTree<T>::erase(Iterator pos)
    {
        if (empty()) {
            throw underflow_error("BinarySearchTree.erase(): tree is empty");
        }

        BSTreeNode<T> *targetNode = pos.ptr;  // 要删除的节点
        if (targetNode == nullptr) {
            throw range_error("BinarySearchTree.erase(): reference error");
        }

        BSTreeNode<T> *parentNode = targetNode->parent;
        BSTreeNode<T> *replaceNode = nullptr;  // 取代被删除节点位置的节点
        if (targetNode->left == nullptr || targetNode->right == nullptr) {
            if (targetNode->right == nullptr) {
                replaceNode = targetNode->left;
            } else {
                replaceNode = targetNode->right;
            }

            if (replaceNode != nullptr) {
                replaceNode->parent = parentNode;
            }
        } else {
            replaceNode = targetNode->right;
            BSTreeNode<T> *parentOfReplaceNode = targetNode;

            while (replaceNode->left != nullptr) {
                parentOfReplaceNode = replaceNode;
                replaceNode = replaceNode->left;
            }

            if (targetNode == parentOfReplaceNode) {
                replaceNode->left = targetNode->left;
            } else {
                parentOfReplaceNode->left = replaceNode->right;

                if (replaceNode->right != nullptr) {
                    replaceNode->right->parent = parentOfReplaceNode;
                }

                replaceNode->left = targetNode->left;
                replaceNode->right = targetNode->right;
                replaceNode->right->parent = replaceNode;
            }

            replaceNode->left->parent = replaceNode;
            replaceNode->parent = parentNode;
        }

        // 父节点为空，则该节点为根节点，重置根节点
        if (parentNode == nullptr) {
            root = replaceNode;
        } else if (targetNode->value < parentNode->value) {
            parentNode->left = replaceNode;
        } else {
            parentNode->right = replaceNode;
        }

        delete targetNode;
        --treeSize;
    }

    template <typename T>
    void BinarySearchTree<T>::erase(Iterator first, Iterator last)
    {
        if (empty()) {
            throw underflow_error("BinarySearchTree.erase(): tree is empty");
        }

        if (first == begin() && last == end()) {
            deleteTree(root);
            root = nullptr;
            treeSize = 0;
        } else {
            for (Iterator iter = first; iter != last; ) {
                erase(iter++);
            }
        }
    }

    template <typename T>
    int BinarySearchTree<T>::treeNodeLevel(const T &item)
    {
        if (empty()) {
            throw underflow_error("BinarySearchTree.nodeLevel(): tree is empty");
        }

        int level = 0;
        BSTreeNode<T> *treeNode = root;
        while (treeNode != nullptr && item != treeNode->value) {
            if (item < treeNode->value) {
                treeNode = treeNode->left;
            } else {
                treeNode = treeNode->right;
            }

            ++level;
        }

        if (treeNode == nullptr) {
            level = -1;
        }

        return level;
    }
}

#endif  // ALGORITHM_BINARY_SEARCH_TREE_H