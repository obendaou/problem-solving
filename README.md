# Problem Solving in C++

My practice repository for data structures, algorithms, and explaining how I solve problems. Each completed entry includes my reasoning, a dry run, a C++ implementation, complexity analysis, and lessons learned.

## Problems

| Problem | Topic | Approach | Expected time | Extra space |
| --- | --- | --- | --- | --- |
| [Two Sum](arrays-and-hashing/two-sum/README.md) | Arrays and hash maps | One-pass complement lookup | O(n) | O(n) |
| [Count Pairs with a Given Sum](arrays-and-hashing/count-pairs/README.md) | Arrays and hash maps | Count earlier complement frequencies | O(n) | O(k), at most O(n) |
| [Longest Substring Without Repeating Characters](sliding-window/longest-substring-without-repeating-characters/README.md) | Strings and sliding window | Last-seen ASCII table | O(n) | O(1) |

Here, n is the input length and k is the number of distinct values.

## Organization

- `arrays-and-hashing/`: problems involving arrays and hash maps.
- `sliding-window/`: problems involving a moving contiguous range.
- Each problem directory contains a `README.md` and `solution.cpp`.
- `templates/problem-readme.md`: documentation structure for future entries.

## Learning workflow

1. Attempt the problem and explain an initial approach.
2. Trace examples, including edge cases.
3. Implement and check the solution.
4. Document why it works and its complexity.
5. Revisit later and solve again without hints.

These entries document learning, including coached practice; a published solution does not imply independent mastery. Counts and review results are added only when verified.

Problem descriptions are short paraphrases; links point to the original sources.
