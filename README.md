# ADT-SortedMultiMap-BinarySearchTree

  Sorted multi map abstract data type implemented on a binary search tree over an array. The container stores key-value pairs of a generic type, sorted by the keys 
based on a given relation. The binary search tree is represented over a dynamic array, meaning that the nodes are stored in a contiguous block of memory,
reducing the drawbacks of fragmentation given by a BST having as links pointers. Each node in the BST has the indices in the array of its left and right
children.

The container has the following methods implemented:
  - Add
  - Remove
  - Search
  - Size
  - IsEmpty

The iterator upon its creating performs an in-order traversal of the BST and stores in an array the indices of the nodes in the sorted order. The iterator
provides the following methods:
  - First
  - Next
  - IsValid
  - GetCurrent
