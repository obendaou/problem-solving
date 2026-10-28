# House Robber II

[Original problem](https://leetcode.com/problems/house-robber-ii/)

## Problem

Choose non-adjacent houses for the largest total, but the houses form a circle: the first and last houses are also adjacent.

Amounts are nonnegative. This implementation accepts empty input and assumes the input length and achievable totals fit in `int`.

Example: `[2, 3, 2]` returns **3**. Choosing both houses with value 2 would violate the circular adjacency rule.

## My approach: two linear ranges

I reuse my [House Robber](../house-robber/README.md) rolling DP on two inclusive ranges:

1. `[0, n - 2]`: exclude the last house.
2. `[1, n - 1]`: exclude the first house.

Return the larger result.

I handle empty input and one house before creating either range. With two houses, both ranges contain one house and the answer is their maximum.

## Why the split works

A valid circular selection cannot choose both the first and last houses. Therefore, it excludes at least one endpoint and belongs to at least one of the two linear cases.

Conversely, any valid non-adjacent selection inside either range is valid in the circle because one endpoint is absent. The two cases may overlap, but that is harmless: I take a maximum rather than adding their results.

## Range helper and rolling states

The helper receives start and end indices instead of copying subarrays. Both endpoints are inclusive.

- Range length is `end - start + 1`.
- Length-one and length-two ranges have direct answers.
- Longer ranges initialize the three ending-at-house states relative to start.
- The loop runs through end, including that final index.

For each later house i, use `current = max(a, b) + nums[i]`, then shift the three states. As in the linear problem, each state requires choosing its ending house.

The helper requires a valid nonempty range. The wrapper guarantees this after handling n = 0 and n = 1.

## Dry run

For `[1, 2, 3, 1]`:

| Case | Inclusive range | Values considered | Best total |
| --- | --- | --- | --- |
| Exclude last | [0, 2] | [1, 2, 3] | 4, from 1 + 3 |
| Exclude first | [1, 3] | [2, 3, 1] | 3, from 2 + 1 or 3 |

The answer is `max(4, 3) = 4`.

For `[2, 3, 2]`, each range contains two houses and returns 3. The algorithm never combines both endpoints.

## Solution

[Source file](solution.cpp):

```cpp
#include <algorithm>
#include <vector>

// Nonnegative amounts; input length and achievable totals fit in int.
namespace {
int robRange(const std::vector<int>& nums, int start, int end)
{
    // Precondition: 0 <= start <= end < nums.size().
    const int length = end - start + 1;
    if (length == 1) return nums[start];
    if (length == 2) return std::max(nums[start], nums[start + 1]);

    int a = nums[start];
    int b = nums[start + 1];
    int c = nums[start] + nums[start + 2];
    for (int i = start + 3; i <= end; ++i)
    {
        const int current = std::max(a, b) + nums[i];
        a = b;
        b = c;
        c = current;
    }
    return std::max(b, c);
}
}

int rob(const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    return std::max(robRange(nums, 0, n - 2),
                    robRange(nums, 1, n - 1));
}
```

This repository implementation was reconstructed from the saved description of my corrected range-helper algorithm, with formatting, headers, and a private translation-unit helper added. It is not a verbatim copy of the original chat submission.

For LeetCode, adapt the wrapper to its supplied `class Solution`; keep the helper private or as a separate helper function.

## Complexity

- **Time: O(n).** Two linear scans still take O(n) total time.
- **Extra space: O(1).** The helper stores a fixed number of states and receives the input by const reference.
- Creating two copied subarrays would require O(n) extra space; passing indices avoids those allocations.

## Corrections made during practice

My earlier circular version copied ranges and omitted the empty/singleton guards. The corrected design checks those cases first and uses an inclusive range helper.

Boundary checks must be relative to the helper's range length, not the entire vector. A one-element range can occur even when the whole vector has two elements.

## Validation

The published implementation compiled with C++17, `-Wall -Wextra -Werror`, and UndefinedBehaviorSanitizer. It matched exhaustive circular subset selection on **29,524 arrays** of lengths 0–9 with values 0–2.

Additional checks passed for `[2, 3, 2]`, `[1, 2, 3, 1]`, and a 100,000-element circle of ones, returning 50,000. The reference explicitly rejects choosing both endpoints for n > 1 and allows the lone house for n = 1.

## What I learned

- A circular constraint can sometimes be handled by splitting into linear cases.
- The cases need to cover all valid choices; they do not need to be disjoint when taking a maximum.
- Passing ranges avoids input copies.
- Helper preconditions and wrapper edge cases must agree.

## Practice context

The range-helper design followed coached feedback about copies and missing short-input cases. I implemented the corrected rolling DP. This is assisted practice; independent recall remains a separate goal.
