# Min Stack

[Original problem on LeetCode](https://leetcode.com/problems/min-stack/)

## Problem

Design a stack supporting four operations in O(1) time each:

- `push(value)`: add a value.
- `pop()`: remove the top value.
- `top()`: return the top value.
- `getMin()`: return the smallest value currently stored.

Values can be negative or repeated. The caller must only use `pop()`, `top()`, and `getMin()` when the stack is nonempty.

## My approach

Each stack entry stores two integers:

```text
[value, minimum from the bottom through this entry]
```

The first integer is the pushed value. The second is a snapshot of the minimum for the stack prefix ending at that entry.

When pushing:

1. If the stack is empty, store `[value, value]`.
2. Otherwise, compare the new value with the previous top's stored minimum.
3. Store the new value alongside the smaller of those two numbers.

Popping removes one complete entry. The next entry already stores the correct minimum for the remaining values, so no search or recalculation is necessary.

## Initial alternative

My first idea was to store values in a deque and cache one minimum. If a popped value equaled that minimum, I would scan the remaining values to find the replacement.

That approach can return the right minimum, but such a `pop()` takes O(n), violating the requirement that every operation be O(1). Keeping minimum history during pushes avoids that scan.

## Dry run

Entries are shown from bottom to top.

| Operation | Stack after operation | Top value | Minimum |
| --- | --- | --- | --- |
| `push(5)` | `[5,5]` | 5 | 5 |
| `push(2)` | `[5,5], [2,2]` | 2 | 2 |
| `push(2)` | `[5,5], [2,2], [2,2]` | 2 | 2 |
| `push(7)` | `[5,5], [2,2], [2,2], [7,2]` | 7 | 2 |
| `pop()` | `[5,5], [2,2], [2,2]` | 2 | 2 |
| `pop()` | `[5,5], [2,2]` | 2 | 2 |
| `pop()` | `[5,5]` | 5 | 5 |

Duplicate minima work naturally: removing one `2` leaves another entry with minimum `2`. Removing the last `2` exposes the earlier minimum `5`.

## Why it works

The invariant is: **each entry stores the minimum of all values from the bottom of the stack through that entry**.

- For the first entry, the only value is also the minimum.
- On a push, the new minimum is the smaller of the previous prefix minimum and the pushed value.
- On a pop, the last prefix disappears. All earlier entries remain unchanged, including the minimum stored at the new top.
- Therefore, `getMin()` can always read the minimum of the whole nonempty stack from its top entry.

These snapshots represent every **prefix**, not every possible subarray. After popping the last entry, the stack has no minimum until another value is pushed.

## Solution

[Source file](solution.cpp)

```cpp
#include <algorithm>
#include <stack>
#include <vector>

class MinStack {
public:
    void push(int value) {
        if (s.empty())
            s.push({value, value});
        else
            s.push({value, std::min(s.top()[1], value)});
    }

    void pop() {
        s.pop();
    }

    int top() {
        return s.top()[0];
    }

    int getMin() {
        return s.top()[1];
    }

private:
    std::stack<std::vector<int>> s;
};
```

This preserves my corrected implementation and its `stack<vector<int>>` representation. Formatting, standard headers, and explicit `std::` qualifiers were added for the repository.

Every vector has exactly two integers. A fixed-size `std::array<int, 2>` or a named struct could also represent an entry, but the vector-based version is valid.

## Complexity

Let `n` be the number of values currently stored.

| Operation | Time | Reason |
| --- | --- | --- |
| `push(value)` | O(1) | One comparison and one push of a fixed-size entry |
| `pop()` | O(1) | Remove the top entry |
| `top()` | O(1) | Read the top entry's value |
| `getMin()` | O(1) | Read the top entry's stored minimum |

**Total storage: O(n).** Each value has one associated minimum snapshot. The temporary work per operation uses O(1) space.

The implementation uses the default `std::stack` container, `std::deque`. Each entry's vector stores a fixed two elements; its size does not grow with n.

## Edge cases and validation

Important cases include:

- First push: avoid calling `top()` on an empty stack.
- Duplicate minima: removing one copy must not lose another.
- A larger value pushed after a minimum: retain the previous minimum.
- Negative values and integer limits.
- Popping all entries, then reusing the stack.

The saved practice results report that the corrected implementation was compiled with C++17, return-type warnings treated as errors, and UndefinedBehaviorSanitizer. It passed directed checks for duplicate and negative minima, `INT_MIN`/`INT_MAX`, empty-then-reuse behavior, and 10,000 seeded randomized operations checked against a vector plus `min_element` reference.

Those results apply to the implementation preserved here. Publication involved a static review, not a fresh execution.

## What I learned

- A single cached minimum is insufficient to restore older minima in constant time without extra history.
- Saving a small summary with each entry can avoid future searches.
- Prefix minimum snapshots handle duplicate minima without special removal logic.
- Query methods must return their values; merely evaluating `s.top()[0]` does not return it.
- Popping or querying an empty stack is outside this exercise's contract.

## Practice context

The minimum-history design was explained during coached practice. I then implemented it, corrected missing return statements, and explained why popping restores the previous minimum. This entry documents that learning without claiming independent mastery.
