# Count Deepest Leaves

## Problem

Return how many leaves are at the greatest depth in a binary tree. Return 0 for an empty tree. Depth is counted in nodes, so the root has depth 1.

## My approach

Traverse the tree with DFS. Pass the current depth by value so each child inherits its parent's depth without changing its sibling's. Share the deepest depth seen and its count by reference across the traversal.

- If the current depth exceeds the maximum, update the maximum and reset the count to 1.
- If it ties the maximum, increment the count.
- Otherwise, keep the current summary.

The count can temporarily include internal nodes, but at the final maximum depth every node must be a leaf: a child would have greater depth.

## Dry run

Consider two root-to-leaf paths: 8 → 3 → 6 → 9 and 8 → 10 → 14 → 11.

| Node | Depth | Maximum after visit | Count after visit |
| --- | --- | --- | --- |
| 8 | 1 | 1 | 1 |
| 3 | 2 | 2 | 1 |
| 6 | 3 | 3 | 1 |
| 9 | 4 | 4 | 1 |
| 10 | 2 | 4 | 1 |
| 14 | 3 | 4 | 1 |
| 11 | 4 | 4 | 2 |

Return **2**. The second branch sees the same depth-4 record set by the first branch.

## Complexity and validation

**O(n) time** because each node is visited once. **O(h) extra space** because only one root-to-node path is active on the recursion stack at a time.

Passed targeted cases and 2,000 comparisons with a breadth-first reference that counts nodes on the last level.

## Solution

[solution.cpp](solution.cpp) uses the repository's [TreeNode definition](../maximum-depth-of-binary-tree/tree-node.h).
