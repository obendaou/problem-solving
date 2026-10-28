# House Robber

[Original problem](https://leetcode.com/problems/house-robber/)

## Problem

Choose houses in a line to maximize the total money collected, without choosing adjacent houses. Amounts are nonnegative. This implementation also accepts empty input and assumes the input length and achievable totals fit in `int`.

Example: `[2, 7, 9, 3, 1]` gives **12**, choosing indices 0, 2, and 4.

## My approach: a state that includes the current house

I define **dp[i] as the largest valid total that must include house i**.

This is different from the largest total available anywhere in the prefix. For example, `dp[1] = nums[1]`, even when house 0 has more money: my state requires choosing house 1.

The base states are:

- `dp[0] = nums[0]`
- `dp[1] = nums[1]`
- `dp[2] = nums[0] + nums[2]`

For i >= 3:

```text
dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i]
```

The answer is the larger of the last two states. Empty, one-house, and two-house inputs are handled separately.

## Why this recurrence works

Choosing house i rules out house i - 1. A valid earlier selection can end at i - 2 or i - 3.

If its last selected house is even earlier, at j <= i - 4, I can add house i - 2 without violating adjacency. Because amounts are nonnegative, this does not reduce the total. Therefore an optimal predecessor can be represented by a state ending at i - 2 or i - 3.

Similarly, an optimal full selection can end at one of the final two houses: if it ended before both, adding the final house would be valid and would not reduce the total.

This reasoning depends on the nonnegative-amount contract. It is not a claim that the same bases and answer rule support arbitrary negative values.

## Dry run

For `[2, 7, 9, 3, 1]`:

| Index | Amount | Calculation | Best total including this house |
| --- | --- | --- | --- |
| 0 | 2 | Base | 2 |
| 1 | 7 | Base | 7 |
| 2 | 9 | 2 + 9 | 11 |
| 3 | 3 | max(7, 2) + 3 | 10 |
| 4 | 1 | max(11, 7) + 1 | 12 |

Return `max(10, 12) = 12`.

## From a table to constant space

The recurrence only uses three earlier positions. Before computing the state for house i, I maintain:

| Variable | Meaning |
| --- | --- |
| a | dp[i - 3] |
| b | dp[i - 2] |
| c | dp[i - 1] |

Compute `current = max(a, b) + nums[i]`, then shift `a = b; b = c; c = current;`.

Although c is not used to calculate the current total, it must be retained because it becomes b for the following iteration. After the loop, return `max(b, c)`.

## Solution

[Constant-space source](solution.cpp):

```cpp
#include <algorithm>
#include <vector>

// Nonnegative amounts; input length and achievable totals fit in int.
int rob(const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return std::max(nums[0], nums[1]);

    int a = nums[0];
    int b = nums[1];
    int c = nums[0] + nums[2];
    for (int i = 3; i < n; ++i)
    {
        const int current = std::max(a, b) + nums[i];
        a = b;
        b = c;
        c = current;
    }
    return std::max(b, c);
}
```

[Table-based source](solution-dp.cpp) implements the same state with O(n) extra space. Its function is named `robWithTable` so both versions can be compared in one test program.

These repository implementations were reconstructed from saved descriptions of my submitted algorithms, with formatting and standard headers added. They preserve my ending-at-house recurrence rather than replacing it with a different DP state. They are not verbatim copies of the original chat submissions.

For LeetCode, place the chosen `rob` method inside its supplied `class Solution`.

## Complexity

| Version | Time | Extra space |
| --- | --- | --- |
| Table-based | O(n) | O(n) |
| Rolling states | O(n) | O(1) |

The input is scanned once and each step performs constant work. The rolling version stores a fixed number of integers.

## Validation

Both published implementations compiled with C++17, `-Wall -Wextra -Werror`, and UndefinedBehaviorSanitizer. Both matched an exhaustive subset-selection reference on **29,524 arrays** of lengths 0–9 with values 0–2.

Checks also covered the example above; the rolling version passed a 100,000-element array of ones, returning 50,000. The exhaustive cases include empty and short arrays, zeros, and ties.

## What I learned

- A DP recurrence must be explained using its exact state definition.
- A state that includes the current house is not automatically the best total for the whole prefix.
- Keeping only the states needed by future steps reduces space.
- Short-input guards must run before indexing base states.

## Practice context

I proposed the ending-at-house recurrence, then refined its state definition and proof with coaching. The rolling-state implementation followed guided discussion of the updates. This entry documents that learning; it does not claim independent mastery.
