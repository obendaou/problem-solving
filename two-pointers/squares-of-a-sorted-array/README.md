# Squares of a Sorted Array

[Original problem](https://leetcode.com/problems/squares-of-a-sorted-array/)

Return the squares of an ascending array in ascending order. The practice bounds keep squared values in `int`.

Binary-search for the first nonnegative index, p. If all values are negative, p is n. Start left at `p - 1` and right at p. Walk leftward through negative values and rightward through nonnegative ones. The absolute values on either side never decrease in those directions, so the smaller of the two exposed squares is the smallest square still available.

For `[-4, -1, 0, 3, 10]`, the split is at 0. The first comparison is `(-1)²` versus `0²`; choose 0. Then choose 1, 9, 16, and 100. Ties retain both occurrences, one per iteration.

Binary search takes O(log n) and the merge takes O(n). Auxiliary space is O(1) excluding the O(n) output. The repository implementation follows the practiced split-and-merge approach with a half-open lower-bound search. It matched square-then-sort on 5,000 arrays and passed the extreme-value check.

## Solution

[solution.cpp](solution.cpp)
