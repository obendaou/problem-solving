# Minimum Size Subarray Sum

[Original problem](https://leetcode.com/problems/minimum-size-subarray-sum/)

## Problem

For a positive target and an array of positive integers, return the length of the shortest contiguous subarray whose sum is at least the target. Return 0 if none qualifies.

## My approach

Maintain a half-open window [start, i), its sum, and the best length found.

- If the sum qualifies, record i - start and remove the leftmost element.
- Otherwise, extend the right boundary if input remains.
- Stop only when the sum is too small and no more elements can be added.

The loop permits i == n so the final window can still shrink. The initial best-length sentinel is converted to 0 when no qualifying window exists.

## Why it works

The running sum always represents exactly [start, i). For each right boundary, shrinking explores the qualifying windows until removing another left element makes the sum too small.

Once a start has produced a valid window, keeping that same start for a later right endpoint could only make its length larger. Discarding it therefore cannot lose a shorter answer.

Positivity is essential: extending increases the sum, and shrinking decreases it. With negatives this rule can fail. For target 3 and [1, -1, 3], removing 1 drops the sum below 3 and stops shrinking, even though removing -1 next would expose the optimal [3].

## Dry run

For target 7 and [2, 3, 1, 2, 4, 3]:

| Right boundary i | Current window before shrinking | Best after shrinking |
| --- | --- | --- |
| 4 | [2, 3, 1, 2], sum 8 | 4 |
| 5 | [3, 1, 2, 4], sum 10 | 3 |
| 6 | [2, 4, 3], sum 9 | 2, from [4, 3] |

## Complexity and validation

Each boundary advances at most n times. The combined number of expansions and removals is O(n), even though they happen in the same loop. Extra space is O(1).

The published code matched brute force on 5,000 seeded positive-array/target cases under C++17, strict warnings, and UndefinedBehaviorSanitizer. A large-integer sum case also passed.

## Practice context

This implementation was reconstructed from my saved half-open-window algorithm. The explanation was developed with coaching. The published running sum uses long long rather than int to accommodate larger totals.

## Solution

[Source file](solution.cpp)

```cpp
#include <algorithm>
#include <limits>
#include <vector>

// Positive target and positive array elements; length fits in int.
int minSubArrayLen(int target, const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    int start = 0, i = 0;
    int best = std::numeric_limits<int>::max();
    long long sum = 0;
    while (i <= n)
    {
        if (sum >= target)
        {
            best = std::min(best, i - start);
            sum -= nums[start++];
        }
        else if (i < n)
            sum += nums[i++];
        else
            break;
    }
    return best == std::numeric_limits<int>::max() ? 0 : best;
}
```

For LeetCode, put the requested method inside its supplied `class Solution`. The two rotated-array source files are standalone alternatives and each defines its own helper; compile them separately.
