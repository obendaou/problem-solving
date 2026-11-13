# Binary Tree Level Order Traversal

[Original problem](https://leetcode.com/problems/binary-tree-level-order-traversal/)

## Problem

Return the tree's values grouped by depth, from left to right within each level. An empty tree returns an empty result.

## My approach

Put the root in a FIFO queue. Keep a counter for the remaining nodes on the current level, initialized from the queue size at the start of that level. Pop a node, append its value to the current group, enqueue its left and right children in that order, and decrement the counter. When it reaches zero, start a new group only if the queue still has nodes.

The queue may hold children from the next level before the current group is finished. The counter separates the levels: when it reaches zero, the only nodes still in the queue belong to the next level. Enqueuing left before right preserves the order within each group.

## Dry run

For root 8 with children 3 and 12, and a left child 6 under 3, the second level starts with queue [3, 12] and counter 2. Popping 3 enqueues 6, leaving [12, 6] with counter 1. Popping 12 finishes the group [3, 12]; the remaining 6 starts the next group. The result is [[8], [3, 12], [6]].

## Complexity and validation

**O(n) time:** each node is queued and popped once. **O(w) auxiliary space**, excluding the output, where w is the maximum width: the queue holds at most parts of two consecutive levels.

The repository version follows my saved queue-and-counter approach. It passed targeted C++17 checks and 2,000 seeded tree comparisons against a DFS reference, with UndefinedBehaviorSanitizer enabled.

## Solution

[solution.cpp](solution.cpp) uses the repository's [TreeNode definition](../maximum-depth-of-binary-tree/tree-node.h).
