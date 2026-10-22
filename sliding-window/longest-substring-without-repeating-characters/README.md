# Longest Substring Without Repeating Characters

[Original problem](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

## Problem

Find the length of the longest contiguous substring containing no repeated characters. Characters are case-sensitive; spaces, digits, and symbols count as characters.

This practice version assumes ASCII input and a length between 0 and 50,000.

Example: `"abcabcbb"` returns **3**, from `"abc"`. A substring must be contiguous, unlike a subsequence.

## My approach

I scan the string once and remember the most recent index of each character. I keep:

- `count`: the length of the longest valid substring ending at the previous position, before processing the current character.
- `best`: the largest valid length found anywhere.
- `seen[c]`: the latest index of character `c`, or `-1` if it has never appeared.

For a character at index `i`:

1. If it is unseen, extend the current substring by one.
2. Otherwise, calculate `gap = i - seen[c]`.
3. If `gap > count`, the previous occurrence is outside the current substring, so extend by one.
4. Otherwise, the previous occurrence is inside it: set `count = gap` to exclude that occurrence.
5. Update the character's latest index and the maximum.

This is a sliding window represented by its length instead of an explicit left index.

## How my approach evolved

I first considered setting the length to the distance from the previous occurrence whenever a character repeated. That fails if the previous occurrence is outside the current valid substring.

For `"abba"`, after the second `b`, the current valid substring is `"b"`. At the final `a`, the old `a` is outside that window. Setting the length to `3 - 0 = 3` would describe `"bba"`, which contains duplicates. My revised condition extends the valid substring to `"ba"`, giving length 2.

I implemented the corrected approach with a hash map, then adapted it to an ASCII table. The sentinel `-1` distinguishes an unseen character from a character last seen at index 0.

## Dry run

For `"abba"`:

| Index | Character | Previous index | Length before | Decision | Length after | Best |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | a | -1 | 0 | Unseen: extend | 1 | 1 |
| 1 | b | -1 | 1 | Unseen: extend | 2 | 2 |
| 2 | b | 1 | 2 | Gap 1 is inside window: shrink | 1 | 2 |
| 3 | a | 0 | 1 | Gap 3 is outside window: extend | 2 | 2 |

At every step, the stored index of the current character is updated.

## Why it works

Assume the previous valid suffix has length `L`, ending at index `i - 1`. It starts at `i - L`.

If the current character's previous index `p` is before that start, adding the character preserves uniqueness, so the new length is `L + 1`. This is equivalent to `i - p > L`.

If `p` is inside the suffix, the new substring must start after `p` to avoid the repeated character. Its length becomes `i - p`. Every other character remains unique because the old suffix was valid.

Therefore, each step finds the longest valid substring ending at the current position. Taking the maximum over all positions gives the answer. An empty string returns 0.

## Solution

[ASCII table implementation](solution.cpp):

```cpp
#include <string>
#include <vector>

// Precondition: ASCII input, length at most 50,000.
int lengthOfLongestSubstring(const std::string& s)
{
    std::vector<int> seen(128, -1);
    int count = 0;
    int best = 0;
    for (int i = 0; i < static_cast<int>(s.length()); ++i)
    {
        const unsigned char character = static_cast<unsigned char>(s[i]);
        if (seen[character] != -1)
        {
            if (i - seen[character] > count)
                count++;
            else
                count = i - seen[character];
        }
        else
            count++;
        seen[character] = i;
        if (count > best)
            best = count;
    }
    return best;
}
```

The table version preserves my length-based update rule. Editorial changes rename `max` to `best`, make the loop's integer conversion explicit, and convert the character to `unsigned char` before indexing. The table still requires ASCII values 0–127; the conversion does not make non-ASCII input supported.

[Original hash-map implementation](solution-map.cpp) preserves my earlier submitted function, with standard headers added. It retains the signed/unsigned loop warning. For LeetCode, place the selected function inside the supplied `class Solution`; the two implementations are alternatives and should not be linked together.

## Complexity

Let `n` be the string length.

| Version | Time | Extra space |
| --- | --- | --- |
| ASCII table | O(n) | O(1): exactly 128 entries |
| Hash map under the same fixed ASCII constraint | Expected O(n) | O(1): at most 128 keys |

Direct indexing avoids hashing and map-node allocation. It changes constant overhead, not the linear scan. Under an expanding alphabet of `k` possible distinct symbols, a hash-map formulation uses O(min(n, k)) space and its collision worst case can degrade to O(n²); the fixed ASCII assumption bounds that alphabet here.

This implementation counts ASCII characters. UTF-8 text would require a separate decision about bytes, Unicode code points, or user-perceived characters.

## Validation

The ASCII table implementation was compiled with C++17, warnings treated as errors, and UndefinedBehaviorSanitizer. It passed:

- Nine targeted cases: empty input, a singleton, all repeated characters, ordinary repeats, `"abba"`, `"tmmzuxt"`, a space, and a repeated space.
- Exhaustive comparison with brute force on all 9,841 strings over `a`, `b`, and `c` of lengths 0–8.
- All 128 ASCII values once and then repeated, giving 128.
- A string of 50,000 repeated characters, giving 1.

These checks validate the stated bounded ASCII contract.

## What I learned

- A previous occurrence matters only if it lies inside the current valid window.
- A sliding window can be represented by its length; an explicit left pointer is not required.
- Every occurrence must update the last-seen index.
- Sentinel values must be distinct from valid indices.
- A fixed alphabet can replace a hash map with a direct lookup table.

## Practice context

I developed this solution through coached debugging and dry runs, wrote the corrected hash-map version, and adapted the approach to an ASCII table. This entry explains that reasoning; independent recall is a separate practice goal.
