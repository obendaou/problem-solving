# Reverse Linked List

[Original problem](https://leetcode.com/problems/reverse-linked-list/)

Reverse an acyclic singly linked list in place and return the new head.

Maintain a reversed prefix headed by `last` and an untouched suffix headed by `curr`. Save the next node before changing the current link. Point the current node back to `last`, move `last` forward to it, and resume at the saved node.

For 10 → 20 → 30, the first iteration leaves `last` at 10 → null and `curr` at 20 → 30. After all three iterations, `last` heads 30 → 20 → 10 → null.

Each node is processed once with three pointers, so time is O(n) and extra space is O(1). The published code passed length 0–128 checks for node identity, order, unchanged values and null termination.

## Solution

[solution.cpp](solution.cpp)

The local [ListNode header](../list-node.h) makes this source usable outside LeetCode. Use LeetCode's supplied node type when submitting there.
