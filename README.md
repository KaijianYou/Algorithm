# Algorithm
My data structures and algorithm exercise.  
Build with LLVM 8.0.0 (clang-800.0.42.1) and CMake 3.6.
  
学习数据结构与算法过程中做的一些练习。
学习用的主要书籍是 **《数据结构 C++ 语言描述 ——应用模板标准库（STL）(第 2 版)》**
  
## algorithm
一些数据结构和算法的简单实现。  
* array: algorithms for array.
* graph: directed graph and algorithms for graph (bfs, dfs etc.).
* hash: hash table based on vector and list.
* heap: algorithms for heap.
* list: singly linked list and doubly circular linked list.
* map: map based on binary search tree and pair.
* queue: priority queue based on heap, priority queue based on vector and queue based on singly linked list.
* recursion: eight queens, tower of hanoi and package problem.
* search: algorithms for searching.
* set: set based on binary search tree, multiset based on list, unordered set based on hash table and algorithms for set.
* sort: algorithms for sorting.
* stack: stack based on array and stack based on vector.
* string: algorithms for string.
* tree: binary tree and binary search tree.
* vector: bits based vector and vector based on dynamic array.
  
## util
工具类和方法。  
  
## tests
algorithm 中的数据结构和算法的使用示例和测试用例。  
  
####附：常用排序算法的时间复杂度和空间复杂度
lg: 以 2 为底的对数。
d: 位数

| 排序算法 | 最差时间复杂度 | 平均时间复杂度 | 空间复杂度 | 稳定度 |
| :--: | :--: | :--: | :--: | :--: |
| 冒泡 (bubble) 排序 | O(n^2) | O(n^2) | O(1) | 稳定 |
| 快速 (quick) 排序 | O(n^2) | O(n\*lg(n)) | O(n\*lg(n)) ~ O(n) | 不稳定 |
| 选择 (selection) 排序 | O(n^2) | O(n^2) | O(1) | 不稳定 |
| 归并 (merge) 排序 | O(n\*lg(n)) | O(n\*lg(n)) | O(n) | 稳定 |
| 插入 (insertion) 排序 | O(n^2) | O(n^2) | O(1) | 稳定 |
| 堆 (heap) 排序 | O(n\*lg(n)) | O(n\*lg(n)) | O(1) | 不稳定 |
| 基数 (radix) 排序 | O(dn) | O(dn) | O(n) | 稳定 |
| 希尔 (shell) 排序 | O(n^2) | O(n^1.3) | O(1) | 不稳定 |
