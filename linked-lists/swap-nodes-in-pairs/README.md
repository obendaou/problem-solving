# Swap Nodes in Pairs

[Original problem](https://leetcode.com/problems/swap-nodes-in-pairs/)

Swap adjacent nodes of an acyclic singly linked list without changing their values. Keep an unpaired last node in place.

The second node of the first pair becomes the returned head. For each pair, save the suffix, reconnect the previous pair's tail to the current second node, point the second node to the first, and point the first to the suffix. The first node is now the tail to retain for the next iteration.

For 10 → 20 → 30 → 40 → 50, the first iteration produces 20 → 10 → 30 → 40 → 50 and retains 10 as the previous tail. The next iteration reconnects 10 to 40 and produces 20 → 10 → 40 → 30 → 50. The final 50 has no partner.

The iterative version avoids the call stack of the recursive approach. Each pair takes constant work, giving O(n) time and O(1) extra space. The repository implementation follows the saved pointer updates and passed length 0–128 checks for node identity, order, unchanged values and null termination.

## Solution

[solution.cpp](solution.cpp)

The local [ListNode header](../list-node.h) makes this source usable outside LeetCode. Use LeetCode's supplied node type when submitting there.
