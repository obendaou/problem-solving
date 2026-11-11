# Linked List Cycle

[Original problem](https://leetcode.com/problems/linked-list-cycle/)

Detect whether a singly linked list contains a cycle, without modifying its links.

Start both pointers at the head. Move slow one link and fast two links. Check that fast and its next node exist before taking the two-step jump. Compare the pointers **after moving**, using node identity rather than comparing values.

For A → B → C → B, the pointers are at B and C after the first move, and both at C after the second. In an acyclic list, fast instead reaches the end. Inside a cycle of length L, fast gains one link on slow per iteration modulo L, so the two meet within L further iterations.

Time is O(n) over distinct reachable nodes and extra space is O(1). The published code passed 8,385 cyclic and acyclic cases, including self-loops, repeated values and every possible cycle entry for lengths up to 128. The checks also verified that links were unchanged.

## Solution

[solution.cpp](solution.cpp)

The local [ListNode header](../list-node.h) makes this source usable outside LeetCode. Use LeetCode's supplied node type when submitting there.
