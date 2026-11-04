# Find Minimum in Rotated Sorted Array

[Original problem](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

## Problem

Find the minimum value in a nonempty ascending sorted array rotated at an unknown index. Values are distinct. An unrotated array is allowed.

During practice I implemented findMinIndex, which returns the minimum's index. The published findMin wrapper returns its value for the original problem.

## My approach

Keep the minimum candidate inside [left, right]. While left < right:

- If nums[mid] > nums[right], the minimum is strictly after mid: left = mid + 1.
- Otherwise, the minimum is at mid or before it: right = mid.

Return the meeting index.

## Why these updates work

When nums[mid] exceeds the right endpoint, that interval crosses the rotation boundary. The minimum is to the right of mid, so mid can be discarded.

When nums[mid] is below the right endpoint, mid belongs to the ascending suffix ending at right. Everything strictly after mid is larger; mid itself could be the minimum, so keep it.

Both updates preserve the minimum and shrink the interval. When only one candidate remains, it must be the answer. Unlike ordinary target search, this loop stops at equality because it has already isolated the candidate.

## Dry run

For [4, 5, 6, 7, 0, 1, 2]:

| left | right | mid | Comparison | Update |
| --- | --- | --- | --- | --- |
| 0 | 6 | 3 | 7 > 2 | left = 4 |
| 4 | 6 | 5 | 1 < 2 | right = 5 |
| 4 | 5 | 4 | 0 < 1 | right = 4 |

The minimum index is 4 and its value is 0.

## Complexity and validation

The candidate range is roughly halved each iteration: O(log n) time and O(1) extra space. Distinctness matters; duplicate-heavy inputs need different boundary reasoning.

The published code passed C++17 strict warnings and UndefinedBehaviorSanitizer. Both index and value were checked on all 820 rotations of lengths 1–40, plus an integer-extreme case.

## Practice context

The helper preserves my submitted logic, with a named midpoint and explicit signed-size conversion added. The value-returning wrapper was added for the repository. The boundary rules and invariant were taught during coached practice. Input length must fit int; empty input is outside this helper's contract.

## Solution

[Source file](solution.cpp)

```cpp
#include <vector>

int findMinIndex(const std::vector<int>& nums)
{
    // Requires a nonempty rotated ascending array of distinct values.
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left < right)
    {
        const int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) left = mid + 1;
        else right = mid;
    }
    return right;
}

// LeetCode asks for the minimum value, not its index.
int findMin(const std::vector<int>& nums)
{
    return nums[findMinIndex(nums)];
}
```

For LeetCode, put the requested method inside its supplied `class Solution`. The two rotated-array source files are standalone alternatives and each defines its own helper; compile them separately.
