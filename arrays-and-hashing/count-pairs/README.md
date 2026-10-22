# Count Pairs with a Given Sum

A practice variation of [Two Sum](../two-sum/README.md): return the number of matching index pairs instead of returning one pair of indices. This is a custom exercise, not a claim of a separate LeetCode submission.

## Problem

Given an integer array `nums` and a target, count every pair of indices `(i, j)` such that:

- `i < j`.
- `nums[i] + nums[j] == target`.

The condition `i < j` prevents using an element twice and prevents counting a reversed pair again. Equal values at different indices are separate elements.

For `[3, 3, 3]` with target `6`, the matching index pairs are `(0, 1)`, `(0, 2)`, and `(1, 2)`. The answer is **3**, even though every pair contains the same values.

## My approach

I scan the array once and keep a hash map of **number → frequency among earlier elements**.

For each number:

1. Calculate its complement: `target - num`.
2. Look up that complement in the map.
3. If it exists, add its frequency to the total count.
4. Increment the frequency of the current number.

I count matches before updating the map so that the current element cannot pair with itself.

## How my reasoning evolved

My initial idea was to store a vector of earlier indices for each value. That representation works, but this task only needs how many matching indices exist. Storing their count is sufficient.

| Task | What the map stores | What happens on a match |
| --- | --- | --- |
| Two Sum | Number → earlier index | Return the stored index and current index |
| Count Pairs | Number → earlier frequency | Add the frequency and continue |

## Initial alternative

Two nested loops can check each pair with `j > i`, taking O(n²) time and O(1) extra space. The frequency map avoids examining every pair individually.

## Dry run

For `nums = [1, 5, 5]`, `target = 6`:

| Index | Value | Complement | Earlier complement frequency | Total after counting | Map after insertion |
| --- | --- | --- | --- | --- | --- |
| 0 | 1 | 5 | 0 | 0 | `{1: 1}` |
| 1 | 5 | 1 | 1 | 1 | `{1: 1, 5: 1}` |
| 2 | 5 | 1 | 1 | 2 | `{1: 1, 5: 2}` |

The matching index pairs are `(0, 1)` and `(0, 2)`.

For `[3, 3, 3]`, the contributions are `0 + 1 + 2 = 3`: each new `3` pairs with every earlier `3`.

## Why it works

Before processing an element, the map records exactly the frequencies of earlier elements. Every earlier occurrence of the complement forms one valid pair with the current element, so adding its frequency counts all new pairs ending here.

Each valid pair is counted at its later index. It cannot be counted at its earlier index because the later element has not been inserted yet. Therefore, every pair is counted exactly once.

## Solution

```cpp
#include <unordered_map>
#include <vector>

long long countPairs(const std::vector<int>& nums, int target)
{
    std::unordered_map<int, int> seen;
    long long count = 0;

    for (int num : nums)
    {
        auto it = seen.find(target - num);
        if (it != seen.end())
            count += it->second;
        seen[num]++;
    }
    return count;
}
```

[Source file](solution.cpp)

This keeps my submitted frequency-map algorithm. The index loop is rewritten as a range-based loop because the index is not needed; this also removes a signed/unsigned comparison warning.

### Numeric assumptions

This version assumes `target - num` and each stored frequency fit in `int`, and the total fits in `long long`. Arbitrary full-range `int` inputs can overflow the subtraction; wider complement arithmetic and map keys would be needed for that contract.

The total uses `long long` because 100,000 zeros with target zero form `100000 × 99999 / 2 = 4,999,950,000` pairs, which exceeds a 32-bit signed integer.

## Complexity

Let `n` be the number of elements and `k` the number of distinct values.

- **Expected time: O(n)**, with expected O(1) hash lookups and updates per element.
- **Extra space: O(k)**, at most O(n).
- **Worst-case time: O(n²)** if hash collisions make each operation linear.

The result can be O(n²) in size while expected running time stays O(n). I add a whole frequency in one operation instead of generating every matching pair.

## Validation

The optional demo checks ten cases: repeated equal values, mixed complements, repeated values on both sides, negatives, zeros, no matching pairs, an empty array, a singleton, an ordinary pair, and 100,000 zeros.

From this directory:

```bash
c++ -std=c++17 -Wall -Wextra -Werror -DCOUNT_PAIRS_DEMO solution.cpp -o /tmp/count-pairs
/tmp/count-pairs
```

These ten cases were compiled and executed successfully. An additional temporary check compared the solution against a brute-force implementation on 1,000 generated small arrays; all comparisons passed. Validation used UndefinedBehaviorSanitizer and bounded integer values; it does not establish arbitrary integer-range safety.

## What I learned

- Choose the map's value according to the output: indices for locating pairs, frequencies for counting them.
- Duplicate values can produce multiple distinct index pairs.
- Lookup-before-increment enforces the earlier-index rule naturally.
- A large answer does not necessarily require enumerating every item it counts.

## Practice context

I wrote the initial C++ solution after guided discussion and dry runs. This entry includes editorial improvements and an explanation of complexity. Independent recall remains a separate practice goal.
