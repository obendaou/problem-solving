# 3Sum

[Original problem](https://leetcode.com/problems/3sum/)

Return all distinct value triplets that sum to zero. The three values must come from different indices, but equal values are allowed if they occur at enough indices.

## My approach

I first reduced the problem to Two Sum: fix one value, then search the remaining suffix for a pair whose sum cancels it. The [hash-based version](solution-hash.cpp) checks the complement before inserting the current value so it never reuses the same index. It puts every match in sorted value order before inserting it into a set, so equivalent triplets count only once.

The [sorted two-pointer version](solution.cpp) sorts the input in place, fixes an anchor, then starts the pointers at the two ends of the remaining suffix:

- If the sum is too small, advance the left pointer. No smaller right value can make the current left value work.
- If the sum is too large, move the right pointer inward. No larger left value can make the current right value work.
- On a match, record the triplet and skip repeated values at both pointers. For a fixed anchor and one matched value, its partner is determined, so these repeats cannot produce a new triplet.

Skip repeated anchors too: an earlier occurrence already searched a suffix that included every pair available to the later one.

The pruning check skips an anchor if even the two largest remaining values give a negative sum. The function returns early when there are fewer than three values, and the outer loop only visits anchors with at least two positions after them. This keeps the pruning reads in bounds and avoids unsigned subtraction for short inputs.

## Dry run

For `[-1, 0, 1, 2, -1, -4]`, the sorted input is `[-4, -1, -1, 0, 1, 2]`.

| Anchor | Left | Right | Sum | Action |
| --- | --- | --- | --- | --- |
| -4 | — | — | -1 at most | Skip this anchor |
| -1 | -1 | 2 | 0 | Save `[-1, -1, 2]` |
| -1 | 0 | 1 | 0 | Save `[-1, 0, 1]` |
| second -1 | — | — | — | Skip duplicate anchor |
| 0 | 1 | 2 | 3 | Move right; pointers meet |

## Complexity

- **Two pointers:** O(n²) time. For each anchor, both pointers only move inward. The duplicate-skipping loops move those same pointers, so all pointer moves together take O(n) for that anchor. Sorting takes O(n log n). The scan uses O(1) auxiliary space excluding output; typical `std::sort` implementations also use O(log n) call-stack space.
- **Hash lookup + ordered set:** expected O(n² + m log(k + 1)) time, where m is the number of successful complement lookups and k the number of distinct triplets. The per-anchor hash set uses O(n) space, and the ordered set uses O(k) space in addition to the returned vector.

## Validation

Both versions were reconstructed from my practice notes. The published code preserves the two approaches, adds a short-input guard and safe anchor bound to the sorted version, and uses wider arithmetic for sums and complements.

Both compiled with C++17, strict warnings, and UndefinedBehaviorSanitizer. They matched a brute-force reference on 97,656 arrays of lengths 0–7 over values −2 through 2, plus the dry-run example and a case with extreme integer values. The comparison also checks that neither implementation returns duplicate triplets.
