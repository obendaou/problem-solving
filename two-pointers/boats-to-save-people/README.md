# Boats to Save People

[Original problem](https://leetcode.com/problems/boats-to-save-people/)

## Problem

Minimize the boats needed to carry everyone. Each boat carries at most two people and has a weight limit. Weights are positive and every individual fits in a boat.

## My approach

Sort the weights, then keep pointers to the lightest and heaviest remaining people. Every iteration gives the heaviest a boat. If the lightest can share it, advance the left pointer too. Always remove the heaviest and increment the boat count. A final singleton uses one boat.

The published version also handles an empty vector by converting its size to a signed index before subtracting one. It sorts the input in place and uses wider arithmetic for the sum of two weights.

## Why the greedy choice works

If the lightest and heaviest exceed the limit together, no remaining person can share with the heaviest, so the heaviest must go alone.

If they fit, an optimal solution can be rearranged to pair them without adding a boat. If both previously had partners, pair those partners together: the lightest's partner weighs no more than the heaviest, so together with the heaviest's old partner they fit. If either was alone, the rearrangement needs no additional boat. Thus this choice leaves an optimal smaller problem.

## Dry run

For weights [3, 2, 2, 1] and limit 3, sort to [1, 2, 2, 3].

| Remaining | Boat | Reason |
| --- | --- | --- |
| [1, 2, 2, 3] | 3 alone | 1 + 3 exceeds limit |
| [1, 2, 2] | 1 and 2 | They fit |
| [2] | 2 alone | Last person |

Answer: 3.

## Complexity and validation

Sorting takes O(n log n); the inward scan takes O(n), since each pointer passes each person at most once. The scan uses O(1) extra space, excluding the typical O(log n) sorting call stack.

The published C++17 code passed strict warnings and UndefinedBehaviorSanitizer and matched exhaustive optimal-pairing search on 5,000 seeded generated inputs, including empty and singleton cases.

## Practice context

I devised the greedy algorithm; the exchange proof was supplied during coaching. This implementation was reconstructed from the saved approach, with the small robustness changes described above.

## Solution

[Source file](solution.cpp)

```cpp
#include <algorithm>
#include <vector>

// Positive weights, each <= limit; each boat carries at most two people.
int numRescueBoats(std::vector<int>& people, int limit)
{
    std::sort(people.begin(), people.end());
    int left = 0;
    int right = static_cast<int>(people.size()) - 1;
    int boats = 0;
    while (left <= right)
    {
        if (left < right &&
            static_cast<long long>(people[left]) + people[right] <= limit)
            ++left;
        --right;
        ++boats;
    }
    return boats;
}
```

For LeetCode, put the requested method inside its supplied `class Solution`. The two rotated-array source files are standalone alternatives and each defines its own helper; compile them separately.
