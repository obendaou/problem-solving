# Search in Rotated Sorted Array

[Original problem](https://leetcode.com/problems/search-in-rotated-sorted-array/)

## Problem

Return a target's index in a rotated ascending array of distinct integers, or -1 when absent. This version handles empty input too.

## My approach

First find the minimum index with logarithmic binary search. This splits a rotated array into two ascending sections.

- If the minimum index is 0, search the whole unrotated array.
- Otherwise, if target > the final value, search [0, minIndex - 1].
- Otherwise, search [minIndex, last].

Then perform ordinary inclusive binary search on the chosen section. The empty-input guard runs before calling the minimum helper.

## Why it works

The minimum helper preserves the minimum in its candidate interval; see [Find Minimum](../find-minimum-in-rotated-sorted-array/README.md).

For a rotated array with distinct values, every value before the pivot is greater than the last value, and every value from the pivot onward is at most the last value. This comparison selects the only section that could contain the target. Equality with the last value belongs in the right section.

Ordinary binary search then preserves a different invariant: if the target exists, it remains inside [start, end]. Exclude a checked midpoint when moving either boundary. When start > end, no candidates remain.

## Dry run

For [4, 5, 6, 7, 0, 1, 2] and target 1:

1. Find minimum index 4.
2. Since 1 <= last value 2, choose indices [4, 6].
3. Middle index 5 holds 1, so return 5.

For target 3, the chosen left section is [0, 3]; ordinary search exhausts it and returns -1.

## Complexity and validation

Two sequential O(log n) searches still take O(log n), not O(log² n). No intervals are copied, and both stages are iterative, so extra space is O(1).

The published C++17 code passed strict warnings and UndefinedBehaviorSanitizer and matched linear search on 48,380 target checks across all rotations of lengths 1–40. Empty-input and integer-extreme checks also passed.

## Practice context

I proposed the two-stage approach. My initial pivot scan was linear; coaching helped replace it with logarithmic minimum finding and clarified boundary and equality cases. The published code preserves my submitted target-search logic, with size conversion and midpoint readability edits. Array length must fit int.

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

int search(const std::vector<int>& nums, int target)
{
    if (nums.empty()) return -1;
    const int minIndex = findMinIndex(nums);
    int start, end;
    const int last = static_cast<int>(nums.size()) - 1;
    if (minIndex == 0) { start = 0; end = last; }
    else if (target > nums[last]) { start = 0; end = minIndex - 1; }
    else { start = minIndex; end = last; }

    while (start <= end)
    {
        const int mid = start + (end - start) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) end = mid - 1;
        else start = mid + 1;
    }
    return -1;
}
```

For LeetCode, put the requested method inside its supplied `class Solution`. The two rotated-array source files are standalone alternatives and each defines its own helper; compile them separately.
