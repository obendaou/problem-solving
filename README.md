# Problem Solving

My practice repository for data structures, algorithms, and explaining how I solve problems. Each completed entry includes my reasoning, a dry run, a C++ or Python implementation, complexity analysis, and lessons learned.

## Problems

| Problem | Topic | Approach | Expected time | Extra space |
| --- | --- | --- | --- | --- |
| [Two Sum](arrays-and-hashing/two-sum/README.md) | Arrays and hash maps | One-pass complement lookup | O(n) | O(n) |
| [Count Pairs with a Given Sum](arrays-and-hashing/count-pairs/README.md) | Arrays and hash maps | Count earlier complement frequencies | O(n) | O(k), at most O(n) |
| [Longest Substring Without Repeating Characters](sliding-window/longest-substring-without-repeating-characters/README.md) | Strings and sliding window | Last-seen ASCII table | O(n) | O(1) |
| [Valid Parentheses](stacks/valid-parentheses/README.md) | Stacks | Match most recent unmatched opening | O(n) | O(n) |
| [Min Stack](stacks/min-stack/README.md) | Stacks | Store a minimum with each entry | O(1) per operation | O(n) |
| [Binary Search](binary-search/binary-search/README.md) | Binary search | Halve an inclusive search interval | O(log n) | O(1) |
| [House Robber](dynamic-programming/house-robber/README.md) | Dynamic programming | Rolling states ending at each house | O(n) | O(1) |
| [House Robber II](dynamic-programming/house-robber-ii/README.md) | Dynamic programming | Two inclusive linear ranges | O(n) | O(1) |
| [Maximum Depth of Binary Tree](trees/maximum-depth-of-binary-tree/README.md) | Trees and recursion | Combine child subtree depths | O(n) | O(h) |
| [3Sum](arrays-and-hashing/3sum/README.md) | Arrays and two pointers | Sort, fix an anchor, and scan inward | O(n²) | O(log n) typical sort stack, excluding output |
| [Boats to Save People](two-pointers/boats-to-save-people/README.md) | Greedy and two pointers | Pair heaviest with lightest when feasible | O(n log n) | O(log n) typical sort stack |
| [Minimum Size Subarray Sum](sliding-window/minimum-size-subarray-sum/README.md) | Sliding window | Expand or shrink a half-open sum window | O(n) | O(1) |
| [Permutation in String](sliding-window/permutation-in-string/README.md) | Sliding window | Compare fixed-size character frequencies | O(m + n) | O(1) |
| [Find Minimum in Rotated Sorted Array](binary-search/find-minimum-in-rotated-sorted-array/README.md) | Binary search | Preserve the minimum inside an inclusive interval | O(log n) | O(1) |
| [Search in Rotated Sorted Array](binary-search/search-in-rotated-sorted-array/README.md) | Binary search | Find pivot, select sorted half, then binary-search | O(log n) | O(1) |
| [Sorted Pair Sum](two-pointers/sorted-pair-sum/README.md) | Two pointers | Eliminate one endpoint per comparison | O(n) | O(1) |
| [Subarray Sum Equals K](arrays-and-hashing/subarray-sum-equals-k/README.md) | Prefix sums and hashing | Count earlier prefixes equal to sum minus k | O(n) expected | O(n) |
| [Squares of a Sorted Array](two-pointers/squares-of-a-sorted-array/README.md) | Binary search and two pointers | Split at first nonnegative, then merge squares | O(n) | O(1) excluding output |
| [Reverse Linked List](linked-lists/reverse-linked-list/README.md) | Linked lists | Reverse links with a saved next pointer | O(n) | O(1) |
| [Swap Nodes in Pairs](linked-lists/swap-nodes-in-pairs/README.md) | Linked lists | Rewire each pair and reconnect the previous tail | O(n) | O(1) |
| [Linked List Cycle](linked-lists/linked-list-cycle/README.md) | Linked lists | Detect when fast and slow meet | O(n) | O(1) |
| [Middle of the Linked List](linked-lists/middle-of-the-linked-list/README.md) | Linked lists | Move fast twice for every slow step | O(n) | O(1) |
| [Binary Tree Preorder Traversal](trees/binary-tree-preorder-traversal/README.md) | Trees and recursion | Visit node, left subtree, then right subtree | O(n) | O(h) |

Here, n is the input length (or node count for trees), k is the number of distinct values, h is tree height, and m/n denote the two string lengths for Permutation in String.

## Organization

- `arrays-and-hashing/`: problems involving arrays and hash maps.
- `sliding-window/`: problems involving a moving contiguous range.
- `stacks/`: problems using last-in, first-out processing.
- `binary-search/`: problems using sorted search intervals.
- `dynamic-programming/`: problems solved using reusable optimal subproblem states.
- `trees/`: problems involving tree traversal and recursive subtrees.
- `two-pointers/`: problems using coordinated inward pointer moves.
- `linked-lists/`: problems involving node pointers and links.
- Each problem directory contains a `README.md` and an implementation (`solution.cpp` or `solution.py`).
- `templates/problem-readme.md`: documentation structure for future entries.

## Learning workflow

1. Attempt the problem and explain an initial approach.
2. Trace examples, including edge cases.
3. Implement and check the solution.
4. Document why it works and its complexity.
5. Revisit later and solve again without hints.

These entries document learning, including coached practice; a published solution does not imply independent mastery. Counts and review results are added only when verified.

Problem descriptions are short paraphrases; links point to the original sources.
