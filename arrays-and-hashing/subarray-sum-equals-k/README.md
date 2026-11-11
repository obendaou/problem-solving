# Subarray Sum Equals K

[Original problem](https://leetcode.com/problems/subarray-sum-equals-k/)

Count nonempty contiguous subarrays that sum to k. Negative values and zeros are allowed.

If the running prefix is S and an earlier prefix is P, the subarray between them sums to `S - P`. Therefore, look up `S - k`. Store frequencies because the same sum at different positions gives different starting indices.

Start with frequency 1 for the empty prefix (sum 0), so a subarray beginning at index 0 counts. Look up the complement **before** recording the current prefix; otherwise k = 0 would also count an empty subarray.

For `[1, -1, 1]` and k = 1, the running prefixes are 1, 0, 1. The lookups add 1, 0, and 2 matches, respectively. The answer is 3.

Hash operations give expected O(n) time and O(n) extra space. The implementation uses `int` under the practice bounds (at most 20,000 values of magnitude up to 1,000, and k of magnitude up to 10,000,000). It passed 5,000 comparisons with direct enumeration and the 20,000-zero case.

## Solution

[solution.cpp](solution.cpp)
