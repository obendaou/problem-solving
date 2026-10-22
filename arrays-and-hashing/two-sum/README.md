# Two Sum

[Original problem on LeetCode](https://leetcode.com/problems/two-sum/)

## Problem

Given an integer array and a target, return two different indices whose values add up to the target. For this exercise, exactly one solution exists.

Example: `nums = [3, 2, 4]`, `target = 6` gives indices `[1, 2]` because `2 + 4 = 6`.

## My approach

I use a hash map and scan the array once. For each number, I calculate the missing value as `target - nums[i]` and search for it among the numbers I have already visited.

The map stores **number → earlier index**. If I find the complement, I return its stored index and the current index. Otherwise, I store the current number and its index, then continue.

I search before inserting so that the current element cannot match itself.

## Initial alternative

A straightforward alternative is to try every pair of indices with nested loops. That takes O(n²) time and O(1) extra space. The hash map uses additional memory to avoid repeatedly searching for the complement.

## Dry run

For `nums = [3, 3]` and `target = 6`:

| Index | Current value | Complement | Map before lookup | Action |
| --- | --- | --- | --- | --- |
| 0 | 3 | 3 | Empty | Missing: store `3 → 0` |
| 1 | 3 | 3 | `3 → 0` | Found: return `[0, 1]` |

The repeated values are valid because they have different indices.

## Why it works

At the beginning of each iteration, the map contains indices of previously visited elements only. If the complement exists, its index is different from the current one, and the two values sum to the target.

For any valid pair, when I reach its later index, the earlier value has already been stored. Therefore, the lookup finds a valid pair. Overwriting the stored index for a repeated value is safe here: I only need one earlier index, not every occurrence.

## Solution

```cpp
#include <unordered_map>
#include <vector>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        auto it = seen.find(target - nums[i]);
        if (it != seen.end())
            return {it->second, i};
        seen[nums[i]] = i;
    }
    return {};
}
```

[Source file](solution.cpp)

This version keeps my original algorithm, gives the map a descriptive name, uses the iterator returned by `find`, and makes the index conversion explicit. The `int` arithmetic assumes the exercise's numeric bounds; unrestricted integers would require a wider type for subtraction. For LeetCode, place the function inside its supplied `class Solution`.

## Complexity

- **Expected time: O(n).** Hash lookups and insertions take expected O(1) time. In the worst case, collisions can make the overall algorithm O(n²).
- **Extra space: O(n).** The map can store up to n distinct values.

## Cases to check

- Duplicates: `[3, 3]`, target `6`.
- Zero values: `[0, 0]`, target `0`.
- Negative values: `[-3, 4, 3, 90]`, target `0`.
- An unrelated value between the matching elements: `[3, 2, 4]`, target `6`.

## Run locally

From this directory:

```bash
c++ -std=c++17 -Wall -Wextra -Werror -DTWO_SUM_DEMO solution.cpp -o /tmp/two-sum
/tmp/two-sum
```

The optional demo verifies the four cases above by checking that the returned indices are different, valid, and identify values summing to the target. Without `TWO_SUM_DEMO`, the file provides only the solution function.

## What I learned

- A map's value depends on the task: this problem needs an index.
- Looking up before inserting prevents reusing the same element.
- `find` returns an iterator, so `it->second` avoids a second lookup.
- Expected hash-table performance should be distinguished from worst-case performance.

## Practice context

I wrote the initial C++ implementation during coached practice after discussing the approach and tracing duplicates. The presentation above includes editorial improvements. Solving this again later without hints is a separate learning goal.
