# Binary Tree Preorder Traversal

[Original problem](https://leetcode.com/problems/binary-tree-preorder-traversal/)

## Problem

Return the values of a binary tree in preorder. An empty tree returns an empty vector.

## My approach

Create a local result vector for each traversal and pass it to the recursive helper by reference. A null node does nothing. For each real node, append its value, traverse the left subtree, then traverse the right subtree.

Each call appends exactly the preorder of its subtree. The node comes first, and the two recursive calls append their subtrees in the required order. The empty-tree base case makes the same rule work for leaves and nodes with one child.

## Dry run

Start at 8. Its left subtree is 3 with right child 6, and its right subtree is 10 with children 9 and 14. The visits are **8, 3, 6, 10, 9, 14**.

## Why the vector is local

A member vector can retain values between calls unless reset. Returning a member vector by value also leaves its storage separate from the returned vector. One local vector per traversal avoids stale state, and passing it by reference lets all helper calls append to the same output.

## Complexity and validation

- **Time:** O(n), one visit per node.
- **Extra space:** O(h) for the call stack, excluding the O(n) output. Height h can be n for a skewed tree.

Passed targeted cases, including a call on an empty tree after a nonempty traversal, and 2,000 comparisons with an iterative preorder reference.

## Solution

[solution.cpp](solution.cpp) uses the repository's [TreeNode definition](../maximum-depth-of-binary-tree/tree-node.h).
