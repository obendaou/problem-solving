# Permutation in String

[Original problem](https://leetcode.com/problems/permutation-in-string/)

## Problem

Return whether s2 contains a contiguous substring that is a permutation of s1. Inputs contain lowercase English letters only. This version also accepts an empty s1, which matches an empty window.

## My approach

A permutation has the same length and character frequencies as the original string. I build two 26-entry frequency vectors: one for s1 and one for the first length-s1 window of s2.

If s1 is longer, return false immediately. Compare the vectors for each window. When sliding, decrement the outgoing character and increment the incoming character. Return true on equality, otherwise false after the final window.

## Why it works

For every iteration, the window vector records exactly the characters in the current length-s1 substring. Removing the outgoing character and adding the incoming one preserves this invariant.

Two strings of equal length over the same alphabet are permutations exactly when every character count matches. Scanning all possible starts therefore finds every candidate, including the first and last windows.

## Dry run

For s1 = "ab" and s2 = "eidbaooo":

| Window | Matching frequencies? |
| --- | --- |
| ei | No |
| id | No |
| db | No |
| ba | Yes: one a and one b |

## Complexity and validation

Let m = s1.length() and n = s2.length(). Initialization and scanning take O(m + n) time. Each frequency comparison examines at most 26 counts, which is constant work under the fixed alphabet. The two fixed-size vectors use O(1) extra space.

The published C++17 implementation passed strict warnings, UndefinedBehaviorSanitizer, and 5,000 seeded comparisons with a reference that sorts each candidate substring. Cases include empty strings, repeated letters, and s1 longer than s2.

## Practice context

I proposed the fixed-size frequency window and implemented it after edge-case reminders. The repository version was reconstructed from the saved description, preserving the first-window initialization and inclusive start-index loop.

## Solution

[Source file](solution.cpp)

```cpp
#include <string>
#include <vector>

// Lowercase English letters only; empty s1 matches an empty window.
bool checkInclusion(const std::string& s1, const std::string& s2)
{
    if (s1.size() > s2.size()) return false;
    std::vector<int> target(26, 0), window(26, 0);
    const std::size_t m = s1.size();
    for (std::size_t i = 0; i < m; ++i)
    {
        ++target[s1[i] - 'a'];
        ++window[s2[i] - 'a'];
    }
    for (std::size_t start = 0; start <= s2.size() - m; ++start)
    {
        if (start > 0)
        {
            --window[s2[start - 1] - 'a'];
            ++window[s2[start + m - 1] - 'a'];
        }
        if (target == window) return true;
    }
    return false;
}
```

For LeetCode, put the requested method inside its supplied `class Solution`. The two rotated-array source files are standalone alternatives and each defines its own helper; compile them separately.
