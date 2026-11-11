# Middle of the Linked List

[Original problem](https://leetcode.com/problems/middle-of-the-linked-list/)

Return the middle node of an acyclic singly linked list. For an even length, return the **second** middle. For an empty list, return null.

Start slow and fast at the head. As long as fast can take two steps, move fast twice and slow once. Return slow when the loop ends.

| Input | Fast at termination | Slow returned |
| --- | --- | --- |
| 10 → 20 → 30 → 40 | null after two jumps | 30 |
| 10 → 20 → 30 → 40 → 50 | 50 after two jumps | 30 |

After k iterations, slow has moved k links and fast has moved 2k. The loop stops after floor(n / 2) iterations, leaving slow at index floor(n / 2). That index gives the requested second middle for even n.

The traversal takes O(n) time and O(1) extra space. It passed length 0–128 checks for returned node identity and unchanged links, including repeated values.

## Solution

[solution.cpp](solution.cpp)

The local [ListNode header](../list-node.h) makes this source usable outside LeetCode. Use LeetCode's supplied node type when submitting there.
