# Binary Search

[Original problem on LeetCode](https://leetcode.com/problems/binary-search/)

## Problem

Given an ascending sorted array of distinct integers, return the index of a target value, or `-1` if it does not exist.

This exercise allows an empty array and assumes at most 100,000 elements.

Example: `nums = [-1, 0, 3, 5, 9, 12]`, `target = 9` returns **4**.

## My approach

I keep an inclusive search interval `[start, end]` and repeatedly inspect its middle:

1. If the middle value equals the target, return its index.
2. If the middle value is greater than the target, search the left half.
3. Otherwise, search the right half.
4. If the interval becomes empty, return `-1`.

The array is sorted, so comparing with the middle lets me discard an entire half. I exclude the already checked middle by using `mid - 1` or `mid + 1`.

## Boundaries and termination

| Condition | Meaning |
| --- | --- |
| `start < end` | At least two candidates remain |
| `start == end` | Exactly one candidate remains |
| `start > end` | No candidates remain |

The loop must therefore continue while **start <= end**. A singleton still needs to be checked.

My recursive version initially stopped on `start >= end`, which incorrectly discarded single-element intervals. While converting to iteration, I also confused the recursive stopping condition with the loop continuation condition. They are opposites here: stop when empty, continue while nonempty.

## Dry run: target found

For `nums = [-1, 0, 3, 5, 9, 12]`, `target = 9`:

| Step | start | end | mid | nums[mid] | Action |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 5 | 2 | 3 | Target is greater: start = 3 |
| 2 | 3 | 5 | 4 | 9 | Match: return 4 |

## Dry run: target absent

For `nums = [2, 8]`, `target = 5`:

| Step | start | end | mid | nums[mid] | Action |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 1 | 0 | 2 | Target is greater: start = 1 |
| 2 | 1 | 1 | 1 | 8 | Target is smaller: end = 0 |

Now `start = 1` and `end = 0`. The interval is empty, so the function returns `-1`.

This second trace is an explanatory example for the repository, not a claim that I independently completed the follow-up trace in practice.

## Why it works

The invariant is: **if the target exists, its index remains inside the current search interval**.

Initially, the interval covers the entire array. When the middle value is too small, all values at or before the middle are also too small, so discarding them cannot remove the target. When the middle value is too large, the symmetric argument allows discarding the middle and everything after it.

Each unsuccessful iteration excludes the middle and strictly reduces the number of candidates. Eventually, the target is found or no candidates remain.

## Solution

[Source file](solution.cpp)

```cpp
#include <vector>

// nums is sorted in ascending order, has distinct values,
// and contains at most 100,000 elements.
int binarySearch(const std::vector<int>& nums, int target)
{
    int start = 0;
    int end = static_cast<int>(nums.size()) - 1;

    while (start <= end)
    {
        const int mid = start + (end - start) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] > target)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return -1;
}
```

This preserves my final iterative algorithm, with two editorial improvements:

- Store the midpoint once per iteration instead of repeating its expression.
- Convert the size to `int` **before** subtracting one. For an empty array, `end` becomes `-1` and the loop is skipped. This avoids unsigned subtraction in `nums.size() - 1`; the conversion is safe under the stated size limit.

The midpoint `start + (end - start) / 2` avoids summing the two bounds directly. No new subarrays are created.

For LeetCode, use the required method name `search` inside its supplied `class Solution`.

## Complexity

Let `n` be the array length.

- **Worst-case time: O(log n)** for nonempty arrays. Each step roughly halves the remaining search interval. Empty input takes O(1).
- **Extra space: O(1)** for the iterative version: only a few integer variables.
- A recursive version uses **O(log n)** call-stack space in the worst case without assuming tail-call optimization.

After k halvings, roughly `n / 2^k` candidates remain. Reaching one candidate requires about `log2(n)` halvings.

Doubling the input size adds about one search step: a first halving reduces the doubled interval back to roughly the original size.

## Initial alternative

A linear scan uses O(n) worst-case time and O(1) extra space. Binary search takes advantage of the existing sorted order; it does not include the cost of sorting an unsorted input.

## Edge cases and validation

Important cases include:

- An empty array.
- A singleton with the target present or absent.
- Targets at the first and last positions.
- A target below or above every value.
- A missing target between two existing values.
- Negative integers.

Saved practice results report that my final submitted iterative version passed 26,624 exhaustive sorted-subset/target checks and seven checks on a 100,000-element vector, using C++17 and UndefinedBehaviorSanitizer.

Those executions covered my submitted version, including its original size initialization. The published version adds the portable cast-before-subtraction initialization and the midpoint variable described above. These small edits received static review; the published version was not freshly executed during this update.

## What I learned

- Inclusive boundaries mean equal indices still represent one candidate.
- A loop continuation condition differs from a recursive stopping condition.
- Excluding the checked middle guarantees progress.
- Repeated halving gives logarithmic time.
- Iteration avoids recursive call-stack storage.
- Size arithmetic needs care because container sizes are unsigned.

## Practice context

I proposed binary search, developed recursive and iterative versions, and corrected the boundary conditions through coached feedback. This entry documents that learning and includes editorial cleanup; it does not claim independent mastery.
