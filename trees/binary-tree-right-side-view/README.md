# Binary Tree Right Side View

[Original problem](https://leetcode.com/problems/binary-tree-right-side-view/)

## Problem

Return the node values visible from the right side, from top to bottom. An empty tree returns an empty result.

## My approach

Use the same FIFO queue and level-size counter as in [Level Order Traversal](../binary-tree-level-order-traversal/README.md). Process every node and enqueue left before right. When the counter reaches zero, the just-popped node is the last on its level. Append only that node's value and take a fresh queue-size snapshot.

Because nodes are dequeued left to right within a level, the last node is the rightmost one. A rightmost node does not need to be a right child: a left child can be the only node at its depth.

## Dry run

For root 8 with children 3 and 12, and a left child 6 under 3, the levels are [8], [3, 12], and [6]. The last node of each level gives [8, 12, 6].

## Complexity and validation

**O(n) time:** each node is queued and popped once. **O(w) auxiliary space**, excluding the output, where w is the maximum width: the queue holds at most parts of two consecutive levels.

The repository version follows my saved queue-and-counter approach. It passed targeted C++17 checks and 2,000 seeded tree comparisons against a DFS reference, with UndefinedBehaviorSanitizer enabled.

## Solution

[solution.cpp](solution.cpp) uses the repository's [TreeNode definition](../maximum-depth-of-binary-tree/tree-node.h).
