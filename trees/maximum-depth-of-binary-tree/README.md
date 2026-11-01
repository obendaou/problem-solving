# Maximum Depth of Binary Tree

[Original problem](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

## Problem

Return the number of nodes on the longest path from the root to a leaf. An empty tree has depth 0; a single node has depth 1.

The input is a binary tree with no cycles or shared child nodes.

## My approach

I solve the same problem recursively for the left and right subtrees.

- If the current node is null, return 0.
- Find the maximum depth of each child subtree.
- Take the larger result and add 1 for the current node.

My initial explanation treated leaves and one-child nodes separately. Those cases all follow from the same rule: an absent subtree contributes 0.

## Solution

[Source file](solution.cpp):

```cpp
#include <algorithm>
#include "tree-node.h"

int maxDepth(TreeNode* root)
{
    if (!root) return 0;
    return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
```

This preserves my submitted function, adding the standard header, an explicit `std::max`, and a local [TreeNode definition](tree-node.h) so it can compile outside LeetCode.

On LeetCode, use its supplied `TreeNode` and place the function inside `class Solution`; do not add the local node definition there.

## Dry run

Consider a root 3 with a left leaf 9 and a right child 20. Node 20 has leaf children 15 and 7.

| Subtree root | Left subtree depth | Right subtree depth | Returned depth |
| --- | --- | --- | --- |
| 9 | 0 | 0 | 1 |
| 15 | 0 | 0 | 1 |
| 7 | 0 | 0 | 1 |
| 20 | 1 | 1 | 2 |
| 3 | 1 | 2 | 3 |

The answer is 3. This table shows how results combine; C++ does not require the two arguments to `std::max` to be evaluated left-to-right.

## Why it works

An empty tree has no nodes on a root-to-leaf path, so its depth is 0.

For a nonempty tree, any such path starts at the current root and continues into one of its child subtrees. Assuming the recursive calls return the correct subtree depths, the longest path has length `1 + max(leftDepth, rightDepth)`.

Applying this rule from the empty subtrees back toward the root produces the correct result for the whole tree.

## Counting time complexity

Let n be the number of nodes.

Each non-null node is processed once. Its own work is constant: a null check, two recursive calls, one maximum comparison, and one addition. The recursive calls account for work at other nodes; they do not make every node visit the whole tree again.

The recurrence is:

```text
T(tree) = T(left subtree) + T(right subtree) + O(1)
```

Both subtrees must be visited. Even though the result is a maximum, the function does not choose only one subtree to explore.

**Total time: O(n)** for a nonempty tree. Empty input takes O(1).

## Counting extra space

Let h be the number of nodes on the longest root-to-leaf path.

Recursive calls remain on the call stack while waiting for their children to return. The largest number of simultaneously active calls is proportional to one root-to-leaf path, not all calls made during the entire run.

Each active call stores constant-size state, so **extra space is O(h)** for a nonempty tree. Null-child calls add only a constant to the maximum stack depth.

| Tree shape | Height | Extra space |
| --- | --- | --- |
| Balanced | O(log n) | O(log n) |
| A chain of n nodes | n | O(n) |

The input nodes already exist, so their storage is not counted as extra space. The function does not copy the tree.

Very deep trees can exceed the environment's recursion limit or call-stack capacity. An iterative traversal is an alternative for those inputs; it is not implemented in this entry.

## Edge cases and validation

The published function was compiled with C++17, `-Wall -Wextra -Werror`, and UndefinedBehaviorSanitizer.

It passed six directed cases:

- Empty tree: 0.
- One node: 1.
- Unequal subtree depths: 3.
- A complete 31-node tree: 5.
- A 200-node left chain: 200.
- A 200-node right chain: 200.

It also matched an independent breadth-first level-counting reference on **1,000 seeded randomized trees** with 0–100 nodes.

## What I learned

- A null-subtree base case also handles leaves and single-child nodes naturally.
- Recursive work adds across both child subtrees.
- Recursion space depends on simultaneously active calls.
- Tree height and number of nodes are different quantities.

## Practice context

I proposed the recursive subtree approach and submitted this compact function. I then asked for help deriving time and extra-space complexity. The analysis above is an explanatory addition, not a claim that I independently derived it during practice.
